#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

//
// itf image library
// image and opengl texture
//
//  
// create opengl texture from pixq_Matrix for each channel
//
// no scaling, texture size is same as input image
//
bool createTexture_PI( 
   pixq_Matrix<unsigned short> *pRed, 
   pixq_Matrix<unsigned short> *pGrn, 
   pixq_Matrix<unsigned short> *pBlu,
   pixq_Properties *pEnv )        // [i] gamma lookup table(=NULL)
{
	bool bRetCode = false;
	int nWidth, nHeight, nNumColors, iTexFilter, iTexPara;
   short sType;
   pixq_TextureBuffer WorkBuffer;
  
   // get image parameters

   nWidth = pRed->getWidth();
   nHeight = pRed->getHeight();
   
   if (0 >= nWidth) {
      goto PIX_EXIT;
   }
   
   if (0 >= nHeight) {
      goto PIX_EXIT;
   }

   nNumColors = 4;

   // allocate working buffer 

   sType = pixq_TextureBuffer::BufferVariableUnsignedShortType;
   if (!WorkBuffer.checkAlloc(nWidth, nHeight, nNumColors, sType)) {
      // buffer allocation failed!
      goto PIX_EXIT;
   }

   // --- generate texture ---

   iTexFilter = pEnv->_ImageTextureFilter.getInteger();
   if( pixq_Properties::TextureFilterNearest == iTexFilter ) {
      iTexPara = GL_NEAREST;
   } else {
      iTexPara = GL_LINEAR;
   }

	glEnable( GL_TEXTURE_RECTANGLE_ARB );
   glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, iTexPara );
	glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, iTexPara );
	glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP );	

   // decide how the texture is generated

   // opengl 2.X -> create texture with any size!
   if (!createFreeTexture_PI(pRed, pGrn, pBlu, &WorkBuffer)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   WorkBuffer.Reset( );
   return bRetCode;
}

static void ConvertGrayToPseudo( unsigned short usValue, // [i] input value 0-65535
                           unsigned short *usPseudoRed, // [o] red in pseudo color
                           unsigned short *usPseudoGrn, // [o] green in pseudo color
                           unsigned short *usPseudoBlu ) // [o] blue in pseudo color
{
   double dH = (double)usValue / 65535.0 * 360.0;
   double dS = 1.0;
   double dV = 1.0;
   double dR, dG, dB;

   double dHi = dH / 60;
   int iHi = (int)floor( 0.5 + dHi ) % 6;

   double dF = dHi - (double)iHi;

   double dP = dV * ( 1.0 - dS );
   double dQ = dV * ( 1.0 - dF * dS );

   double dT = dV * ( 1.0 - ( 1.0 - dF ) * dS );

   switch( iHi ) {
   case 0:
      dR = dV;
      dG = dT;
      dB = dP;
      break;
   case 1:
      dR = dQ;
      dG = dV;
      dB = dP;
      break;
   case 2:
      dR = dP;
      dG = dV;
      dB = dT;
      break;
   case 3:
      dR = dP;
      dG = dQ;
      dB = dV;
      break;
   case 4:
      dR = dT;
      dG = dP;
      dB = dV;
      break;
   case 5:
   default:
      dR = dV;
      dG = dP;
      dB = dQ;
      break;
   }

   *usPseudoRed = (unsigned short)floor( 0.5 + dR * 65535.0 );
   *usPseudoGrn = (unsigned short)floor( 0.5 + dG * 65535.0 );
   *usPseudoBlu = (unsigned short)floor( 0.5 + dB * 65535.0 );

   return;
}

//
// create texture of any size!
// this works only with OpenGL 2.0 or higher
//
// image is not scaled but original size of the image is used.
// size of texture = size of image
// 
bool createFreeTexture_PI(
   pixq_Matrix<unsigned short> *pRed, // [i] red color matrix
   pixq_Matrix<unsigned short> *pGrn, // [i] green color matrix 
   pixq_Matrix<unsigned short> *pBlu, // [i] blue color matrix
   pixq_TextureBuffer *pWorkBuffer,
   short sDisplayColor ) // [i] color mode, = PixImageDisplayColorRgb
{
	bool bRetCode = false;    
   int i, j;
   int nNumColors, nWidth, nHeight, iTextureType, iDataType;
   unsigned short usRed, usGrn, usBlu, usValue, *p;
   unsigned short usMax = 0xFFFF;

   unsigned short *usRedRow = NULL;
   unsigned short *usGrnRow = NULL;
   unsigned short *usBluRow = NULL;

   // --- generate texture ---

   nWidth = pRed->getWidth();
   nHeight = pRed->getHeight();
   
   if (0 >= nWidth) {
      goto PIX_EXIT;
   }
   
   if (0 >= nHeight) {
      goto PIX_EXIT;
   }

   nNumColors = 4;

   // set color parameters according to the color mode

   iTextureType = GL_BGRA_EXT;
   iDataType = GL_UNSIGNED_SHORT;

   // allocate work buffers

   usRedRow = new unsigned short[nWidth];
   if( !usRedRow ) {
      goto PIX_EXIT;
   }

   switch( sDisplayColor ) {
   case PixImageDisplayColorRgb:
      usGrnRow = new unsigned short[nWidth];
      if( !usGrnRow ) {
         goto PIX_EXIT;
      }
      usBluRow = new unsigned short[nWidth];
      if( !usBluRow ) {
         goto PIX_EXIT;
      }
      break;
   }

   // set color matrix to the texture buffer

   p = pWorkBuffer->usGetBuffer( );
   switch( sDisplayColor ) {
   case PixImageDisplayColorRgb:
      for( i = 0 ; i < nHeight ; i++ ) {
         
         pRed->GetRow( i, usRedRow );
		   pGrn->GetRow( i, usGrnRow );
		   pBlu->GetRow( i, usBluRow );

         for( j = 0 ; j < nWidth ; j++ ) {
            *p++ = usBluRow[j];
            *p++ = usGrnRow[j];
            *p++ = usRedRow[j];
            //*p++ = pBlu->Get( i, j );
            //*p++ = pGrn->Get( i, j );
            //*p++ = pRed->Get( i, j );
            *p++ = usMax;
         }
      }
      break;

	case PixImageDisplayColorRed: 
      for( i = 0 ; i < nHeight ; i++ ) {
         pRed->GetRow( i, usRedRow );
         for( j = 0 ; j < nWidth ; j++ ) {
            usValue = usRedRow[j];
            *p++ = usValue;
            *p++ = usValue;
            *p++ = usValue;
            *p++ = usMax;
         }
      }
      break;

	case PixImageDisplayColorGreen:
      for( i = 0 ; i < nHeight ; i++ ) {
         pGrn->GetRow( i, usRedRow );
         for( j = 0 ; j < nWidth ; j++ ) {
            usValue = usRedRow[j];
            *p++ = usValue;
            *p++ = usValue;
            *p++ = usValue;
            *p++ = usMax;
         }
      }
      break;

   case PixImageDisplayColorBlue:
      for( i = 0 ; i < nHeight ; i++ ) {
         pBlu->GetRow( i, usRedRow );
         for( j = 0 ; j < nWidth ; j++ ) {
            usValue = usRedRow[j];
            *p++ = usValue;
            *p++ = usValue;
            *p++ = usValue;
            *p++ = usMax;
         }
      }
      break;

	case PixImageDisplayColorPseudoRed:
      for( i = 0 ; i < nHeight ; i++ ) {
         pRed->GetRow( i, usRedRow );
         for( j = 0 ; j < nWidth ; j++ ) {
            usValue = usRedRow[j];
            ConvertGrayToPseudo( usValue, &usRed, &usGrn, &usBlu );
            *p++ = usBlu;
            *p++ = usGrn;
            *p++ = usRed;
            *p++ = usMax;
         }
      }
      break;

	case PixImageDisplayColorPseudoGreen:
      for( i = 0 ; i < nHeight ; i++ ) {
         pGrn->GetRow( i, usRedRow );
         for( j = 0 ; j < nWidth ; j++ ) {
            usValue = usRedRow[j];
            ConvertGrayToPseudo( usValue, &usRed, &usGrn, &usBlu );
            *p++ = usBlu;
            *p++ = usGrn;
            *p++ = usRed;
            *p++ = usMax;
         }
      }
      break;

	case PixImageDisplayColorPseudoBlue:
      for( i = 0 ; i < nHeight ; i++ ) {
         pBlu->GetRow( i, usRedRow );
         for( j = 0 ; j < nWidth ; j++ ) {
            usValue = usRedRow[j];
            ConvertGrayToPseudo( usValue, &usRed, &usGrn, &usBlu );
            *p++ = usBlu;
            *p++ = usGrn;
            *p++ = usRed;
            *p++ = usMax;
         }
      }
      break;

   default:
      goto PIX_EXIT;
      break;
   }

   // *** set image buffer to the texture ***

   p = pWorkBuffer->usGetBuffer( );
   try {
      glTexImage2D( GL_TEXTURE_RECTANGLE_ARB,
         0,
         nNumColors, 
         nWidth, nHeight,
         0,
         iTextureType,
         iDataType, 
         (GLvoid*)p );  
   } 
   
   catch (...) {
      goto PIX_EXIT;    
	}
  
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   if( usRedRow ) {
      delete[] usRedRow;
      usRedRow = NULL;
   }
   if( usGrnRow ) {
      delete[] usGrnRow;
      usGrnRow = NULL;
   }
   if( usBluRow ) {
      delete[] usBluRow;
      usBluRow = NULL;
   }
   return bRetCode;
}

bool createFreeTexture_PI(
   pixq_Matrix<unsigned short> *pRed, // [i] red color matrix
   pixq_Matrix<unsigned short> *pGrn, // [i] green color matrix 
   pixq_Matrix<unsigned short> *pBlu, // [i] blue color matrix
   short sDisplayColor ) // [i] color mode, = PixImageDisplayColorRgb
{
	bool bRetCode = false;    
   short sType;
   int nNumColors, nWidth, nHeight;
   pixq_TextureBuffer WorkBuffer;

   // --- generate texture ---

   nWidth = pRed->getWidth();
   nHeight = pRed->getHeight();

   if (0 >= nWidth) {
      goto PIX_EXIT;
   }
   
   if (0 >= nHeight) {
      goto PIX_EXIT;
   }

   nNumColors = 4;
   sType = pixq_TextureBuffer::BufferVariableUnsignedShortType;

   // allocate working buffer 

   if (!WorkBuffer.checkAlloc(nWidth, nHeight, nNumColors, sType)) {
      // buffer allocation failed!
      goto PIX_EXIT;
   }
  
   if (!createFreeTexture_PI(pRed, pGrn, pBlu, &WorkBuffer, sDisplayColor)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   WorkBuffer.Reset( );
   return bRetCode;
}

