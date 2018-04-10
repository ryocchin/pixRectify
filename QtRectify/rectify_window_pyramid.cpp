#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_panes.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

#include "rectify_window.h"
#include "ui_rectify_window.h"



//
// get size of resampled image
//
static bool getResampledImageSize(int iLevel,
   int nInWidth,
   int nInHeight,
   int &nResampledWidth,
   int &nResampledHeight)
{
   bool bRetCode = false;

   if (!getResampledValue(iLevel, nInWidth, nResampledWidth)) {
      goto PIX_EXIT;
   }

   if (!getResampledValue(iLevel, nInHeight, nResampledHeight)) {
      goto PIX_EXIT;
   }
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// check if size of two matrices are identical
// and return that size
//
bool rectify_window::checkMatrixSize(int *nInWidth, // [o] common image width
   int *nInHeight) // [o] common image height
{
   bool bRetCode = false;
   int k, nWidth[2], nHeight[2];

   // *** check image matrix ***
   // left and right images must be same dimension

   for (k = 0; k < 2; k++) {
      nWidth[k] = _ImageInMtx[k][0].getWidth(); 
      nHeight[k] = _ImageInMtx[k][0].getHeight(); 
   }

   if (nWidth[0] != nWidth[1]) { 
      goto PIX_EXIT;
   }

   if (nHeight[0] != nHeight[1]) {
      goto PIX_EXIT;
   }

   if (0 >= nWidth[0])  {
      goto PIX_EXIT;
   }

   if (0 >= nHeight[0])  {
      goto PIX_EXIT;
   }
   
   // *** create resampled image value RGB matrix ***

   *nInWidth = nWidth[0];
   *nInHeight = nHeight[0];

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// create pyramid(double number image) just for the base leve; 0 - original size
//
bool rectify_window::createBasePyramid(int iLevel)
{
   bool bRetCode = false;
   int nWidth, nHeight, k;
   int nPyramidWidth, nPyramidHeight, nResample;

   // get size of pyramid image for 2/4/8 resampled level

   if (!checkMatrixSize(&nWidth, &nHeight)) {
      goto PIX_EXIT;
   }

   nResample = pixq_FringeTag::resampleRateForPyramid(iLevel);

   // *** allocate pyramid for each level ***

   // pyramid image size for the level

   if (!getResampledImageSize(iLevel, nWidth, nHeight, nPyramidWidth, nPyramidHeight)) {
      goto PIX_EXIT;
   }
   
#ifdef _DEBUG
   fprintf(stdout, "Image Pyramid...Level %1d/%1d(Resample=%1d): Image Size %04dW X %04dH.\n",
      iLevel, _nPyramidLevel, nResample, nPyramidWidth, nPyramidHeight);
#endif // _DEBUG

   for (k = 0; k < 2; k++) {
      
      // free pyramid images 

      _usPyramidRed[iLevel][k].free();
      _usPyramidGrn[iLevel][k].free();
      _usPyramidBlu[iLevel][k].free();
      _usPyramidGray[iLevel][k].free();

      _dPyramidRed[iLevel][k].free();
      _dPyramidGrn[iLevel][k].free();
      _dPyramidBlu[iLevel][k].free();
      _dPyramidGray[iLevel][k].free();

      _usPyramidRed[iLevel][k].setFrameNumber(-1);
      _usPyramidGrn[iLevel][k].setFrameNumber(-1);
      _usPyramidBlu[iLevel][k].setFrameNumber(-1);
      _usPyramidGray[iLevel][k].setFrameNumber(-1);

      _dPyramidRed[iLevel][k].setFrameNumber(-1);
      _dPyramidGrn[iLevel][k].setFrameNumber(-1);
      _dPyramidBlu[iLevel][k].setFrameNumber(-1);
      _dPyramidGray[iLevel][k].setFrameNumber(-1);

      // re-allocate pyramid images 

      if (!_usPyramidRed[iLevel][k].Alloc(nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }

      if (!_usPyramidGrn[iLevel][k].Alloc(nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }

      if (!_usPyramidBlu[iLevel][k].Alloc(nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }

      if (!_usPyramidGray[iLevel][k].Alloc(nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }

      //

      if (!_dPyramidRed[iLevel][k].Alloc(nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }

      if (!_dPyramidGrn[iLevel][k].Alloc(nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }

      if (!_dPyramidBlu[iLevel][k].Alloc(nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }

      if (!_dPyramidGray[iLevel][k].Alloc(nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }

   }

   // *** create pyramid for each level ***

   for (k = 0; k < 2; k++) {

      // create pyramid images for the level, input value(8-bit and double number)

      if (!resampleRgbMatrix(k, iLevel, nResample, nPyramidHeight, nPyramidWidth)) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// create resampled pixel matrix
//
// notes:
// for grayscale mode, resampled image is set in red matrix
//
bool rectify_window::resampleRgbMatrix(int iSide, // [0] 0 or 1
   int iLevel,
   int nResample,
   int nResampledHeight,
   int nResampledWidth)
{
   bool bRetCode = false;
   double dGray, dRed, dGrn, dBlu;
   double dSumGray, dSumRed, dSumGrn, dSumBlu;
   int i, j, ii, jj, nPix;
   int nWidth, nHeight, iRow0, iRow1, iCol0, iCol1;
   unsigned short usGray, usRed, usGrn, usBlu;
   pixq_Matrix<unsigned short> ValueRed, ValueGrn, ValueBlu; // original image matrix

  // int iCurrentFrame = getCurrentFrame();

#ifdef _DEBUG
   int bStat = false;
   unsigned short usMin[4], usMax[4], usMean[4], usStd[4];
   double dMin[4], dMax[4], dMean[4], dStd[4];
#endif // _DEBUG

 //  if (iCurrentFrame == _usPyramidRed[iLevel][iSide].getFrameNumber()) {
 //     // Pyramid already done for this frame!
 //     bRetCode = true;
 //     goto PIX_EXIT;
 //  }

   // *** create resampled image value RGB matrix ***

   if (0 != iSide && 1 != iSide) {
      goto PIX_EXIT;
   }

   if (0 > iLevel || 3 < iLevel) {
      goto PIX_EXIT;
   }

   nWidth = _ImageInMtx[iSide][0].getWidth(); 
   nHeight = _ImageInMtx[iSide][0].getHeight(); 

   // is this already a pyramid image for the current shot/frame?

   if (!ValueRed.copy(&_ImageInMtx[iSide][0])) { 
      goto PIX_EXIT;
   }

   if (!ValueGrn.copy(&_ImageInMtx[iSide][1])) { 
      goto PIX_EXIT;
   }

   if (!ValueBlu.copy(&_ImageInMtx[iSide][2])) { 
      goto PIX_EXIT;
   }

#ifdef _DEBUG
   if (bStat) {
      ValueRed.Statistics(&usMin[0], &usMax[0], &usMean[0], &usStd[0]);
      ValueGrn.Statistics(&usMin[1], &usMax[1], &usMean[1], &usStd[1]);
      ValueBlu.Statistics(&usMin[2], &usMax[2], &usMean[2], &usStd[2]);
   }
#endif // _DEBUG

   // *** create resampled matrix ***

   // gray pyramid
   // COLOR pyramid

   for (i = 0; i < nResampledHeight; i++) {
      iRow0 = i * nResample;
      iRow1 = min(nHeight - 1, iRow0 + nResample - 1);
      for (j = 0; j < nResampledWidth; j++) {
         iCol0 = j * nResample;
         iCol1 = min(nWidth - 1, iCol0 + nResample - 1);

         nPix = 0;
         dSumRed = 0.0;
         dSumGrn = 0.0;
         dSumBlu = 0.0;
         dSumGray = 0.0;

         for (ii = iRow0; ii <= iRow1; ii++) {
            for (jj = iCol0; jj <= iCol1; jj++) {
               dRed = (double)ValueRed.Get(ii, jj);
               dGrn = (double)ValueGrn.Get(ii, jj);
               dBlu = (double)ValueBlu.Get(ii, jj);

               dSumRed = dSumRed + dRed;
               dSumGrn = dSumGrn + dGrn;
               dSumBlu = dSumBlu + dBlu;

               dGray = 0.299 * dRed + 0.587 * dGrn + 0.114 * dBlu;
               dSumGray = dSumGray + dGray;

               nPix = nPix + 1;
            }
         }

         dSumRed = dSumRed / (double)nPix;
         dSumGrn = dSumGrn / (double)nPix;
         dSumBlu = dSumBlu / (double)nPix;
         dSumGray = dSumGray / (double)nPix;

         usRed = (unsigned short)floor(dSumRed + 0.5);
         usGrn = (unsigned short)floor(dSumGrn + 0.5);
         usBlu = (unsigned short)floor(dSumBlu + 0.5);
         usGray = (unsigned short)floor(dSumGray + 0.5);

         _usPyramidRed[iLevel][iSide].Set(i, j, usRed);
         _usPyramidGrn[iLevel][iSide].Set(i, j, usGrn);
         _usPyramidBlu[iLevel][iSide].Set(i, j, usBlu);
         _usPyramidGray[iLevel][iSide].Set(i, j, usGray);

         _dPyramidRed[iLevel][iSide].Set(i, j, dSumRed);
         _dPyramidGrn[iLevel][iSide].Set(i, j, dSumGrn);
         _dPyramidBlu[iLevel][iSide].Set(i, j, dSumBlu);
         _dPyramidGray[iLevel][iSide].Set(i, j, dSumGray);
      }
   }

#ifdef _DEBUG
   if (bStat) {
      _usPyramidRed[iLevel][iSide].Statistics(&usMin[0], &usMax[0], &usMean[0], &usStd[0]);
      _usPyramidGrn[iLevel][iSide].Statistics(&usMin[1], &usMax[1], &usMean[1], &usStd[1]);
      _usPyramidBlu[iLevel][iSide].Statistics(&usMin[2], &usMax[2], &usMean[2], &usStd[2]);
      _usPyramidGray[iLevel][iSide].Statistics(&usMin[3], &usMax[3], &usMean[3], &usStd[3]);
      //
      _dPyramidRed[iLevel][iSide].Statistics(&dMin[0], &dMax[0], &dMean[0], &dStd[0]);
      _dPyramidGrn[iLevel][iSide].Statistics(&dMin[1], &dMax[1], &dMean[1], &dStd[1]);
      _dPyramidBlu[iLevel][iSide].Statistics(&dMin[2], &dMax[2], &dMean[2], &dStd[2]);
      _dPyramidGray[iLevel][iSide].Statistics(&dMin[3], &dMax[3], &dMean[3], &dStd[3]);

      fprintf(stdout, "...Level %1d Side %1d: %4dW %4dH.\n", iLevel + 1, iSide,
         _dPyramidRed[iLevel][iSide].getWidth(),
         _dPyramidRed[iLevel][iSide].getHeight());
      fprintf(stdout, "...Level %1d Side %1d: Red  %7.1f-%7.1f: Avr=%7.1f : std=%7.1f.\n", iLevel + 1, iSide,
         dMin[0], dMax[0], dMean[0], dStd[0]);
      fprintf(stdout, "...Level %1d Side %1d: Grn  %7.1f-%7.1f: Avr=%7.1f : std=%7.1f.\n", iLevel + 1, iSide,
         dMin[1], dMax[1], dMean[1], dStd[1]);
      fprintf(stdout, "...Level %1d Side %1d: Blu  %7.1f-%7.1f: Avr=%7.1f : std=%7.1f.\n", iLevel + 1, iSide,
         dMin[2], dMax[2], dMean[2], dStd[2]);
      fprintf(stdout, "...Level %1d Side %1d: Gray %7.1f-%7.1f: Avr=%7.1f : std=%7.1f.\n", iLevel + 1, iSide,
         dMin[3], dMax[3], dMean[3], dStd[3]);
      fprintf(stdout, ".......\n");
   }
#endif // _DEBUG

   _usPyramidRed[iLevel][iSide].setFrameNumber(0);
   _usPyramidGrn[iLevel][iSide].setFrameNumber(0);
   _usPyramidBlu[iLevel][iSide].setFrameNumber(0);
   _usPyramidGray[iLevel][iSide].setFrameNumber(0);

   _dPyramidRed[iLevel][iSide].setFrameNumber(0);
   _dPyramidGrn[iLevel][iSide].setFrameNumber(0);
   _dPyramidBlu[iLevel][iSide].setFrameNumber(0);
   _dPyramidGray[iLevel][iSide].setFrameNumber(0);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   ValueRed.free();
   ValueGrn.free();
   ValueBlu.free();
   return bRetCode;
}


//
// create square patch image for each channel
// around the given point and for the given radius
//
// notes:
// if the patch position got beyond the image boundary,
// the area outside image boundary are filled with black
//
bool rectify_window::createMadoImage(int iMadoRadius,
   int iCenterRow,
   int iCenterCol,
   pixq_Matrix<double> *dInRed, // [i] input image, red
   pixq_Matrix<double> *dInGrn, // [i] input image, green
   pixq_Matrix<double> *dInBlu, // [i] input image, blue
   pixq_Matrix<double> *dMadoRed,  // [o] mado around inut pixel, red
   pixq_Matrix<double> *dMadoGrn,  // [o] mado around inut pixel, green
   pixq_Matrix<double> *dMadoBlu ) // [o] mado around inut pixel, blue
{
   bool bRetCode = false;

   // get mado corners

   int iMadoRow0 = iCenterRow - iMadoRadius;
   int iMadoRow1 = iCenterRow + iMadoRadius;
   int iMadoCol0 = iCenterCol - iMadoRadius;
   int iMadoCol1 = iCenterCol + iMadoRadius;

   // *** check if mado is inside the input(resampled) image ***

      if (!dInRed->getPatch(iMadoCol0, iMadoRow0, iMadoCol1, iMadoRow1,
         false, 0, dMadoRed)) {
         goto PIX_EXIT;
      }

      if (!dInGrn->getPatch(iMadoCol0, iMadoRow0, iMadoCol1, iMadoRow1,
         false, 0, dMadoGrn)) {
         goto PIX_EXIT;
      }

      if (!dInBlu->getPatch(iMadoCol0, iMadoRow0, iMadoCol1, iMadoRow1,
         false, 0, dMadoBlu)) {
         goto PIX_EXIT;
      }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool rectify_window::createMadoImage(int iMadoRadius,
   int iCenterRow,
   int iCenterCol,
   pixq_Matrix<double> *dInGray, // [i] input image, blue
   pixq_Matrix<double> *dMadoGray) // [o] mado around input pixel, blue
{
   bool bRetCode = false;

   // get mado corners
   int iMadoRow0 = iCenterRow - iMadoRadius;
   int iMadoRow1 = iCenterRow + iMadoRadius;
   int iMadoCol0 = iCenterCol - iMadoRadius;
   int iMadoCol1 = iCenterCol + iMadoRadius;

   // *** check if mado is inside the input(resampled) image ***

   if (!dInGray->getPatch(iMadoCol0, iMadoRow0, iMadoCol1, iMadoRow1,
      false, 0, dMadoGray)) {
         goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}