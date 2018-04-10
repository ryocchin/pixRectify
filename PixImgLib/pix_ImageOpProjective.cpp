#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImageOp.h"
#include "pix_ImageOpProjective.h"

#include <omp.h>

pixq_ImageOpProjective::pixq_ImageOpProjective(void)
{
   Init( );

   return;
}

void pixq_ImageOpProjective::Init(void)
{
   _dTransform[0][0] = 1.0;
   _dTransform[0][1] = 0.0;
   _dTransform[0][2] = 0.0;
   _dTransform[1][0] = 0.0;
   _dTransform[1][1] = 1.0;
   _dTransform[1][2] = 0.0;
   _dTransform[2][0] = 0.0;
   _dTransform[2][1] = 0.0;
   _dTransform[2][2] = 1.0;

   _dInvTransform[0][0] = 1.0;
   _dInvTransform[0][1] = 0.0;
   _dInvTransform[0][2] = 0.0;
   _dInvTransform[1][0] = 0.0;
   _dInvTransform[1][1] = 1.0;
   _dInvTransform[1][2] = 0.0;
   _dInvTransform[2][0] = 0.0;
   _dInvTransform[2][1] = 0.0;
   _dInvTransform[2][2] = 1.0;

   _bMerge = false;
   
   return;
}

pixq_ImageOpProjective::~pixq_ImageOpProjective(void)
{
   return;
}

void pixq_ImageOpProjective::transform(double dX,
                                       double dY,
                                       double &dU,
                                       double &dV )
{
   double dBtm = _dTransform[2][0] * dX + _dTransform[2][1] * dY + _dTransform[2][2];   

   if( 0.0 == dBtm ) {
      dU = 0.0;
      dV = 0.0;
      goto PIX_EXIT;
   }
   
   dU = ( _dTransform[0][0] * dX + _dTransform[0][1] * dY + _dTransform[0][2] ) / dBtm;
   dV = ( _dTransform[1][0] * dX + _dTransform[1][1] * dY + _dTransform[1][2] ) / dBtm;
  
PIX_EXIT:
   return;
}

void pixq_ImageOpProjective::invTransform(double dU,
                                       double dV,
                                       double &dX,
                                       double &dY )
{
   double dBtm = _dInvTransform[2][0] * dU + _dInvTransform[2][1] * dV + _dInvTransform[2][2];

   if( 0.0 == dBtm ) {
      dU = 0.0;
      dV = 0.0;
      goto PIX_EXIT;
   }

   dX = ( _dInvTransform[0][0] * dU + _dInvTransform[0][1] * dV + _dInvTransform[0][2] ) / dBtm;
   dY = ( _dInvTransform[1][0] * dU + _dInvTransform[1][1] * dV + _dInvTransform[1][2] ) / dBtm;
   
PIX_EXIT:
   return;
}

//
// transform the second image and create larger image to cover the extent of both
// first input image and transformed second image
//
// +----------+  +----------+
// | In1      |  | In2      | 
// |          |  |          | 
// +----------+  +----------+
//
// +----------+
// | In1      | 
// |  +----------+        
// +--|-------+  |
//    |      Tr2 |
//    +----------+ 
//
// Output Image
// +-------------+
// | In1      |  |
// |  +----------+ 
// |--|-------+  |
// |  |      Tr2 |
// +-------------+ 
//
bool pixq_ImageOpProjective::procMerge(void)
{
   bool bRetCode = false;
   
   //bool bTransform;
   //unsigned short usInValue[3];
   //unsigned short usTransValue[3];

   int iX, iY, i, j, k, nWidth, nHeight;
   int iMinCol, iMinRow, iMaxCol, iMaxRow, nOutCols, nOutRows;
   unsigned short usValue[3];
   double dX, dY, dU, dV, dMinX, dMinY, dMaxX, dMaxY;
   double dCornersX[4], dCornersY[4], dCornersXX[4], dCornersYY[4];

   pixq_ImageMatrix Merge16[3];
   
#ifdef _DEBUG
   QString strFile;
#endif // _DEBUG

   nWidth = _pIn16[0]->getWidth();
   nHeight = _pIn16[0]->getHeight();

   // get the size of output image

   dCornersX[0] = 0.0;
   dCornersY[0] = 0.0;
   dCornersX[1] = (double)nWidth - 1.0;
   dCornersY[1] = 0.0;
   dCornersX[2] = (double)nWidth - 1.0;
   dCornersY[2] = (double)nHeight - 1.0;
   dCornersX[3] = 0.0;
   dCornersY[3] = (double)nHeight - 1.0;

   for( k = 0 ; k < 4 ; k++ ) { 
      invTransform(dCornersX[k], dCornersY[k], dCornersXX[k], dCornersYY[k]);
   }

   dMinX = 0.0;
   dMinY = 0.0;
   dMaxX = (double)nWidth;
   dMaxY = (double)nHeight;
   for( k = 0 ; k < 4 ; k++ ) { 
      dMinX = min( dMinX, dCornersXX[k] );
      dMinY = min( dMinY, dCornersYY[k] );
      dMaxX = max( dMaxX, dCornersXX[k] );
      dMaxY = max( dMaxY, dCornersYY[k] );
   }

   iMinCol = static_cast<int>(floor( 0.5 + dMinX ));
   iMinRow = static_cast<int>(floor( 0.5 + dMinY ));
   iMaxCol = static_cast<int>(floor( 0.5 + dMaxX ));
   iMaxRow = static_cast<int>(floor( 0.5 + dMaxY ));

   nOutCols = iMaxCol - iMinCol + 1;
   nOutRows = iMaxRow - iMinRow + 1;

   if( 0 >= nOutCols ) {
      goto PIX_EXIT;
   }

   if( 0 >= nOutRows ) {
      goto PIX_EXIT;
   }

   for( k = 0 ; k < 3 ; k++ ) { 
      if( !Merge16[k].Alloc( nOutRows, nOutCols ) ) {
         goto PIX_EXIT;
      }
   }

   Merge16[0].Fill( 0xffff );
   Merge16[1].Fill( 0xffff );
   Merge16[2].Fill( 0x0 );

   // blending nof two image
   // blend doesn't work!
/*
   for( i = 0 ; i < nOutRows ; i++ ) {
      for( j = 0 ; j < nOutCols ; j++ ) {
         
         dU = (double)j;
         dV = (double)i;

         // central

         iX = j + iMinCol;
         iY = i + iMinRow;
         bCentral = _pIn2_16[0]->Inside( iX, iY );
         if( bCentral ) {
            for( k = 0 ; k < 3 ; k++ ) { 
               usInValue[k] = _pIn2_16[k]->Get( iY, iX );
            }
         }

         // transformed

         invTransform( dU, dV, dX, dY );

         iX = (int)floor( 0.5 + dX ) - iMinCol;
         iY = (int)floor( 0.5 + dY ) - iMinRow;
      
         bTransform = _pIn16[0]->Inside( iX, iY );
         if( bTransform ) {
            for( k = 0 ; k < 3 ; k++ ) { 
               usTransValue[k] = _pIn16[k]->Get( iY, iX );
            }
         }

         // BLEND    

         if( bCentral && bTransform ) {
            for( k = 0 ; k < 3 ; k++ ) { 
               usValue[k] = ( usInValue[k] + usTransValue[k] ) / 2;
            }
         } else if( bCentral ) {
            for( k = 0 ; k < 3 ; k++ ) { 
               usValue[k] = usInValue[k];
            }
         } else if( bTransform ) {
            for( k = 0 ; k < 3 ; k++ ) { 
               usValue[k] = usTransValue[k];
            }
         }

         for( k = 0 ; k < 3 ; k++ ) { 
            Merge16[k].Set( i, j, usValue[k] );   
         }
      }
   }
*/

   // copy the central(first) image
  
   for( i = 0 ; i < nHeight ; i++ ) {
      for( j = 0 ; j < nWidth ; j++ ) {
      
         iX = j - iMinCol;
         iY = i - iMinRow;
         
         if (!Merge16[0].IsInside(iX, iY)) continue;

         for( k = 0 ; k < 3 ; k++ ) { 
            usValue[k] = _pIn2_16[k]->Get( i, j );
            Merge16[k].Set( iY, iX, usValue[k] );   
         }
      }
   }

   // set the transformed image
 
   for( i = 0 ; i < nOutRows ; i++ ) {
      for( j = 0 ; j < nOutCols ; j++ ) {
         
         dU = (double)j;
         dV = (double)i;

         invTransform(dU, dV, dX, dY);

         iX = (int)floor( 0.5 + dX ) - iMinCol;
         iY = (int)floor( 0.5 + dY ) - iMinRow;

         if (!_pIn16[0]->IsInside(iX, iY)) {
            continue;
         }

         for( k = 0 ; k < 3 ; k++ ) { 
            usValue[k] = _pIn16[k]->Get( iY, iX );
            Merge16[k].Set( i, j, usValue[k] );   
         }
      }
   }

#ifdef _DEBUG
   strFile = "c:\\agent\\proj_match_align_merge.tif\0";
   if (!magickSaveImage_PI(strFile, &Merge16[0], &Merge16[1], &Merge16[2])) {
      goto PIX_EXIT;
   }
#endif // _DEBUG

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   for( k = 0 ; k < 3 ; k++ ) { 
      Merge16[k].free();
   }
   return bRetCode;
}

bool pixq_ImageOpProjective::procClip(void)
{
   bool bRetCode = false;
   int iX, iY, i, j, k, nWidth, nHeight, nAdd, nClipWidth;
   int nMinCol, nMaxCol, nOutCol0, nOutCol1;
   unsigned short usValue[3];
   double dX, dY, dU, dV, dMinU, dMinV, dMaxU, dMaxV;
   double dCorX[4], dCorY[4], dCorU[4], dCorV[4];

   int nMaxThreads;
      
   nWidth = _pIn16[0]->getWidth();
   nHeight = _pIn16[0]->getHeight();

   // get output image extent

   dCorX[0] = 0.0;
   dCorY[0] = 0.0;
   dCorX[1] = (double)nWidth - 1.0;
   dCorY[1] = 0.0;
   dCorX[2] = (double)nWidth - 1.0;
   dCorY[2] = (double)nHeight - 1.0;
   dCorX[3] = 0.0;
   dCorY[3] = (double)nHeight - 1.0;
   
   for( k = 0 ; k < 4 ; k++ ) {
      transform( dCorX[k], dCorY[k], dCorU[k], dCorV[k] );
   }

   dMinU = dCorU[0];
   dMinV = dCorV[0];
   dMaxU = dCorU[0];
   dMaxV = dCorV[0];
   for( k = 0 ; k < 4 ; k++ ) {
      dMinU = min( dMinU, dCorU[k] );
      dMinV = min( dMinV, dCorV[k] );
      dMaxU = max( dMaxU, dCorU[k] );
      dMaxV = max( dMaxV, dCorV[k] );
   }

   // output width should be same as the input image

   nMinCol = (int)floor(0.5 + dMinU);
   nMaxCol = (int)floor(0.5 + dMaxU);
   nClipWidth = nMaxCol - nMinCol + 1;
   
   if (nClipWidth < nWidth) {
      nAdd = (nWidth - nClipWidth) / 2;
      nOutCol0 = nMinCol - nAdd;
      nOutCol1 = nMinCol + nWidth - 1; 
   }
   else {
      nAdd = (nClipWidth - nWidth) / 2;
      nOutCol0 = nMinCol + nAdd;
      nOutCol1 = nMinCol + nWidth - 1;
   }
      
   //

   _pOut16[0]->Fill(0x0);
   _pOut16[1]->Fill(0x0);
   _pOut16[2]->Fill( 0x0 );

   nMaxThreads = omp_get_max_threads();
   omp_set_num_threads(nMaxThreads);

#pragma omp parallel
   {
#pragma omp for private(i,j,dU,dV,dX,dY,iX,iY,k,usValue)   
      for (i = 0; i < nHeight; i++) {

#ifdef _DEBUG
//fprintf(stdout, "Processing Row %d/%d...\n", i + 1, nHeight);
#endif // _DEBUG
         
         for (j = 0; j < nWidth; j++) {

            dU = (double)j + nOutCol0;
            dV = (double)i;
            invTransform(dU, dV, dX, dY);
            iX = (int)floor(0.5 + dX);
            iY = (int)floor(0.5 + dY);

            if (!_pIn16[0]->IsInside(iX, iY)) {
               continue;
            }

            for (k = 0; k < 3; k++) {
               usValue[k] = _pIn16[k]->Get(iY, iX);
               _pOut16[k]->Set(i, j, usValue[k]);
            }
         }
      }
   }
   
   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

bool pixq_ImageOpProjective::procCpu(void)
{
   bool bRetCode = false;

   if( _bMerge ) {
      if (!procMerge()) {
         goto PIX_EXIT;
      }
   } else {
      if (!procClip()) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_ImageOpProjective::procCuda(void)
{
   bool bRetCode = false;

   //
   // not ready yet!
   //

   if (!procCpu()) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// do the real work
//
bool pixq_ImageOpProjective::Proc(void)
{
   bool bRetCode = false;
   bool bUseCuda = false;

   if( bUseCuda ) {
      if (!procCuda()) {
         goto PIX_EXIT;
      }
   } else {
      if (!procCpu()) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}