#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImageAccess.h"

static float clump(float fIn)
{
   float fOut = max(fIn, 0.0f);
   fOut = min(fOut, 65535.0f);
   return fOut;
}

pixq_ImageAccess::pixq_ImageAccess(void)
{
   int k;
      
   for (k = 0; k < 3; k++) {
      _pInImg[k] = NULL;
      _pIn2Img[k] = NULL;
      _pOutImg[k] = NULL;
   }

   return;
}

pixq_ImageAccess::~pixq_ImageAccess(void)
{
   int k;

   for (k = 0; k < 3; k++) {
      _pInImg[k] = NULL;
      _pIn2Img[k] = NULL;
      _pOutImg[k] = NULL;
   }

   return;
}

void pixq_ImageAccess::setInRgb(const pixq_ImageMatrix *pRgb[3])
{
   int k;

   //_bConst = true;

   for (k = 0; k < 3; k++) {
      _pInImg[k] = pRgb[k];
   }

   return;
}

void pixq_ImageAccess::setIn2Rgb(const pixq_ImageMatrix *pRgb[3])
{
   int k;
   
   for (k = 0; k < 3; k++) {
      _pIn2Img[k] = pRgb[k];
   }

   return;
}

void pixq_ImageAccess::setInRgb(const pixq_ImageMatrix *pRed,
   const pixq_ImageMatrix *pGrn,
   const pixq_ImageMatrix *pBlu)
{
   //_bConst = true;

   _pInImg[0] = pRed;
   _pInImg[1] = pGrn;
   _pInImg[2] = pBlu;

   return;
}


void pixq_ImageAccess::setIn2Rgb(const pixq_ImageMatrix *pRed,
   const pixq_ImageMatrix *pGrn,
   const pixq_ImageMatrix *pBlu)
{
   _pIn2Img[0] = pRed;
   _pIn2Img[1] = pGrn;
   _pIn2Img[2] = pBlu;

   return;
}

void pixq_ImageAccess::setOutRgb(pixq_ImageMatrix *pRed,
   pixq_ImageMatrix *pGrn,
   pixq_ImageMatrix *pBlu)
{
   //_bConst = false;

   _pOutImg[0] = pRed;
   _pOutImg[1] = pGrn;
   _pOutImg[2] = pBlu;

   return;
}

void pixq_ImageAccess::setOutRgb(pixq_ImageMatrix *pRgb[3])
{
   int k;

   //_bConst = false;

   for (k = 0; k < 3; k++) {
      _pOutImg[k] = pRgb[k];
   }

   return;
}


#ifdef _USE_IMAGE_MAGICK
//
// get three image matrices from ImageMagick image buffer
// 
// notes:
// _pOutImg must be allocated in advance
//
bool pixq_ImageAccess::getMagickBuffer(Magick::Pixels *pix)
{
   bool bRetCode = false;
   int nHeight, iRow, nWidth, i, j;
   ColorRGB col;
   const PixelPacket *pixels;
   unsigned short usRed, usGrn, usBlu;

   nHeight = _pOutImg[0]->getHeight();
   nWidth = _pOutImg[0]->getWidth();

   if (0 >= nWidth) {
      goto PIX_EXIT;
   }

   if (0 >= nHeight) {
      goto PIX_EXIT;
   }

   pixels = pix->getConst(0, 0, nWidth, nHeight);

   //
   // copy image data to host memory
   //

   for (i = 0; i < nHeight; i++) {
      iRow = nHeight - i - 1;
      for (j = 0; j < nWidth; j++) {
         
         usRed = (unsigned short)pixels->red;
         usGrn = (unsigned short)pixels->green;
         usBlu = (unsigned short)pixels->blue;

         _pOutImg[0]->_Data[iRow][j] = usRed;
         _pOutImg[1]->_Data[iRow][j] = usGrn;
         _pOutImg[2]->_Data[iRow][j] = usBlu;

         pixels++;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
#endif // _USE_IMAGE_MAGICK

#ifdef _USE_IMAGE_MAGICK
//
// set three image matrices in ImageMagick image buffer
// 
bool pixq_ImageAccess::setMagickBuffer(Magick::Pixels *pix)
const
{
   bool bRetCode = false;
   int nHeight, iRow, nWidth, i, j, k;
   double dRed, dGrn, dBlu;
   ColorRGB col;
   PixelPacket *pixels = NULL;

   nHeight = _pInImg[0]->getHeight();
   nWidth = _pInImg[0]->getWidth();

   pixels = pix->get(0, 0, nWidth, nHeight);

   //
   // copy image data to host memory
   //

   k = 0;
   for (i = 0; i < nHeight; i++) {
      iRow = nHeight - i - 1;
      for (j = 0; j < nWidth; j++) {
         dRed = (double)_pInImg[0]->_Data[iRow][j] / 65535.0;
         dGrn = (double)_pInImg[1]->_Data[iRow][j] / 65535.0;
         dBlu = (double)_pInImg[2]->_Data[iRow][j] / 65535.0;

         col = ColorRGB(dRed, dGrn, dBlu);
         pixels[k++] = col;
      }
   }

   // --- Done ---
   bRetCode = true;
   //PIX_EXIT:
   return bRetCode;
}
#endif // _USE_IMAGE_MAGICK

//
// get read image buffer to three matrices
//
// notes:
// ucInBuff is one-dimensional image buffer for one row read by TIFFReadScanline 
// three matrices must be allocated in advance
//
bool pixq_ImageAccess::getTiffScanLine(bool b16Bit, // [i] true 16-bit or false for 8-bit
   int iRow, // [i] row
   int iSamplePerPixel, // [i] 3 or 4
   const unsigned char *ucInBuff)
{
   bool bRetCode = false;
   unsigned short usBits[4];
   int j;
   int nHeight = _pOutImg[0]->getHeight();
   int nWidth = _pOutImg[0]->getWidth();
   const unsigned char *p = NULL;

   p = ucInBuff;

   if (b16Bit) {
      //
      // 16-bit
      //
      switch (iSamplePerPixel) {
      case 3:
         for (j = 0; j < nWidth; j++) {
            memcpy(&usBits[0], p, 2);
            p++;
            p++;
            memcpy(&usBits[1], p, 2);
            p++;
            p++;
            memcpy(&usBits[2], p, 2);
            p++;
            p++;
            _pOutImg[0]->_Data[iRow][j] = usBits[0];
            _pOutImg[1]->_Data[iRow][j] = usBits[1];
            _pOutImg[2]->_Data[iRow][j] = usBits[2];
         }
         break;

      case 4:
         for (j = 0; j < nWidth; j++) {
            memcpy(&usBits[0], p, 2);
            p++;
            p++;
            memcpy(&usBits[1], p, 2);
            p++;
            p++;
            memcpy(&usBits[2], p, 2);
            p++;
            p++;
#ifdef _DEBUG
            // alpha channel
            memcpy(&usBits[3], p, 2);
#endif // _DEBUG
            p++;
            p++;
            _pOutImg[0]->_Data[iRow][j] = usBits[0];
            _pOutImg[1]->_Data[iRow][j] = usBits[1];
            _pOutImg[2]->_Data[iRow][j] = usBits[2];
         }
         break;

      default:
         goto PIX_EXIT;
         break;
      }
   }
   else {
      //
      // 8-bit
      //
      switch (iSamplePerPixel) {
      case 3:
         for (j = 0; j < nWidth; j++) {
            usBits[0] = *p++;
            usBits[1] = *p++;
            usBits[2] = *p++;
            //
            //
            _pOutImg[0]->_Data[iRow][j] = ((usBits[0] << 8) & 0xff00);
            _pOutImg[1]->_Data[iRow][j] = ((usBits[1] << 8) & 0xff00);
            _pOutImg[2]->_Data[iRow][j] = ((usBits[2] << 8) & 0xff00);
         }
         break;

      case 4:
         for (j = 0; j < nWidth; j++) {
            usBits[0] = *p++;
            usBits[1] = *p++;
            usBits[2] = *p++;
            *p++;
            //
            //
            _pOutImg[0]->_Data[iRow][j] = ((usBits[0] << 8) & 0xff00);
            _pOutImg[1]->_Data[iRow][j] = ((usBits[1] << 8) & 0xff00);
            _pOutImg[2]->_Data[iRow][j] = ((usBits[2] << 8) & 0xff00);
         }
         break;

      default:
         goto PIX_EXIT;
         break;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// set one dimensional buffer to writ  to jpeg image
//
// notes:
// ucBuffer must be allocated in advance
//
bool pixq_ImageAccess::setJpegBuffer(unsigned char *ucBuffer)
{
   bool bRetCode = false;
   int i,k,iRow, j;
   int nHeight = _pInImg[0]->getHeight();
   int nWidth = _pInImg[0]->getWidth();
   unsigned char *p = NULL;

   p = ucBuffer;

   k = 0;
   for (i = 0; i < nHeight; i++) {
      iRow = nHeight - i - 1;
      for (j = 0; j < nWidth; j++) {
         *(p++) = (_pInImg[0]->_Data[iRow][j] >> 8) & 0xFF;
         *(p++) = (_pInImg[1]->_Data[iRow][j] >> 8) & 0xFF;
         *(p++) = (_pInImg[2]->_Data[iRow][j] >> 8) & 0xFF;
      }
   }

   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}


bool pixq_ImageAccess::setScaledDifference(double dScale)
{
   bool bRetCode = false;
   int nOutWidth, nOutHeight, nInHeight[2], nInWidth[2], i, j, k;
   int iValue[2][3], iDiff[3];

   int iMax = 65535;

   nInHeight[0] = _pOutImg[0]->getHeight();
   nInWidth[0] = _pOutImg[0]->getWidth();

   nInHeight[1] = _pIn2Img[0]->getHeight();
   nInWidth[1] = _pIn2Img[0]->getWidth();
   
   nOutWidth = _pOutImg[0]->getWidth();
   nOutHeight = _pOutImg[0]->getHeight();

   //
   // copy image data to host memory
   //

   for (k = 0; k < 3; k++) {
      _pOutImg[k]->Fill(0);
   }

   for (i = 0; i < nOutHeight; i++) {
      for (j = 0; j < nOutWidth; j++) {

         for (k = 0; k < 3; k++) {
            iValue[0][k] = (int)_pInImg[k]->_Data[i][j];
            iValue[1][k] = (int)_pIn2Img[k]->_Data[i][j];

            iDiff[k] = min(iMax, (int)(dScale * (double)abs(iValue[0][k] - iValue[1][k])));

            _pOutImg[k]->_Data[i][j] = (unsigned short)iDiff[k];
         }
      }
   }
   
   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}


bool pixq_ImageAccess::setBlending(float *fRatio)
{
   bool bRetCode = false;
   int nOutWidth, nOutHeight, nInHeight[2], nInWidth[2], i, j, k;
   float fBlend[3], fValue[2];
   int iMax = 65535;

   nInHeight[0] = _pOutImg[0]->getHeight();
   nInWidth[0] = _pOutImg[0]->getWidth();

   nInHeight[1] = _pIn2Img[0]->getHeight();
   nInWidth[1] = _pIn2Img[0]->getWidth();

   nOutWidth = _pOutImg[0]->getWidth();
   nOutHeight = _pOutImg[0]->getHeight();

   //
   // copy image data to host memory
   //

   for (k = 0; k < 3; k++) {
      _pOutImg[k]->Fill(0);
   }

   for (i = 0; i < nOutHeight; i++) {
      for (j = 0; j < nOutWidth; j++) {

         for (k = 0; k < 3; k++) {
            fValue[0] = (float)_pInImg[k]->_Data[i][j];
            fValue[1] = (float)_pIn2Img[k]->_Data[i][j];

            fBlend[k] = (float)fValue[0] * fRatio[0] + (float)fValue[1] * fRatio[1];
            fBlend[k] = clump(fBlend[k]);

            _pOutImg[k]->_Data[i][j] = (unsigned short)fBlend[k];
         }
      }
   }

   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}


bool pixq_ImageAccess::checkAllocOut(int nHeight, int nWidth)
{
   bool bRetCode = false;
   int k;

   if (0 >= nWidth) {
      goto PIX_EXIT;
   }

   if (0 >= nHeight) {
      goto PIX_EXIT;
   }

   for (k = 0; k < 3; k++) {
      if (!_pOutImg[k]->checkAlloc(nHeight, nWidth)) {
         fprintf(stderr, "ERROR! Memory Allocation Failed(pixq_ImageAccess::checkAllocOut).\n");
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


