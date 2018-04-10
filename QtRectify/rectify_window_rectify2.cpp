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

#include "rectify_table.h"
#include "rectify_window.h"

#include <omp.h>

static bool checkMadoStdev(int nChan,
   double dMinStdDev,
   const pixq_Matrix<double> dMadoCol[3] )
{
   bool bMinDev = false;
   bool bMatchStDev[3];
   double dMatchStDev[3];
   int k;

   for (k = 0; k < nChan; k++) {
      dMatchStDev[k] = dMadoCol[k].stDev();
      bMatchStDev[k] = (dMatchStDev[k] > dMinStdDev) ? true : false;
   }

   bMinDev = false;
   for (k = 0; k < nChan; k++) {
      if (bMatchStDev[k]) {
         bMinDev = true;
      }
   }

   return bMinDev;
}

bool rectify_window::rectifyMatchSingleTagPointLevel(
   const int iLevel,       // [i] level
   const int iCol,         // [i] left image column at the level
   const int iRow,         // [i] left image row at the level
   int &iRightCol,         // [i/o]
   int &iRightRow,         // [i/o]
   unsigned short &usCorr, // [o] correlation type, one of pixq_FringeTag::CorrMatchTypes
   double &dCorr,          // [o]
   bool &bUsed,            // [o]
   bool bUsePyramid )
{
   bool bRetCode = false;
   bool bChecked, bMatchDev, bOriginDev, bMatchGray;
   int nChecked, iLastLevel, iMadoRadius, i, k, iX, iY, iXPos, iYPos;
   int iMaxCorr, iMadoSize, nHorDisparity, nVerDisparity;
   int iOriginalMadoRadius, nOriginHorDisparity, nOriginVerDisparity;
   int nLeftDisparity, nRightDisparity, nAboveDisparity, nBelowDisparity;
   int nChan, iMaxCol, iMaxRow, iOrigin, iMatch, nSourceWidth, nSourceHeight;
   int nLevelWidth, nLevelHeight;
   int nSearchCols, nSearchRows, iSearchCol, iSearchRow;

   double dMinStdDev, dMaxCorr;
   double dHighBound;
   double  dColCorr[3], dPntCorr;

   int iInRightCol = iRightCol;
   int iInRightRow = iRightRow;

   //bool bMatchStDev[3], bStDev[3];
   //double dStDev[3], dMatchStDev[3];

#ifdef _DEBUG
   //QString strLeftFile, strRightFile, strLeftMado, strRightMado;
#endif // _DEBUG
   
   pixq_Matrix<double> dMado2Col[2][3];
   pixq_Matrix<double> *dResample2Col[2][3];

   pixq_Matrix<double> dMtxCorr;
   pixq_Matrix<bool> bMtxChecked;

   pixq_Properties *pEnv = getRectifyEnv();

   int nMaxThreads;

   nMaxThreads = omp_get_max_threads();
   omp_set_num_threads(nMaxThreads);

   // initial setting 

   bMatchGray = pEnv->_MatchGrayScale.getBool();
   
   // match right image to left

   iOrigin = 0;
   iMatch = 1;

   if (bMatchGray) {
      nChan = 1;
      for (k = 0; k < 2; k++) {
         dResample2Col[k][0] = &_dPyramidGray[iLevel][k];
      }
   }
   else {
      nChan = 3;
      for (k = 0; k < 2; k++) {
         dResample2Col[k][0] = &_dPyramidRed[iLevel][k];
         dResample2Col[k][1] = &_dPyramidGrn[iLevel][k];
         dResample2Col[k][2] = &_dPyramidBlu[iLevel][k];
      }
   }

   nSourceWidth = _dPyramidRed[0][0].getWidth();
   nSourceHeight = _dPyramidRed[0][0].getHeight();
   nLevelWidth = dResample2Col[0][0]->getWidth();
   nLevelHeight = dResample2Col[0][0]->getHeight();

   // *** get and check matching parameters ***

   // max disparity = search range

   nOriginHorDisparity = pEnv->_RectifyMaxHorizontalDisparity.getInteger();
   nOriginVerDisparity = pEnv->_RectifyMaxVerticalDisparity.getInteger();

   if (bUsePyramid) {
      //
      // using pyramid
      // disparity at the lowest pyramid is used at all level
      //
      iLastLevel = _nPyramidLevel - 1;
      if (!getResampledValue(iLastLevel, nOriginHorDisparity, nHorDisparity)) {
         goto PIX_EXIT;
      }

      if (!getResampledValue(iLastLevel, nOriginVerDisparity, nVerDisparity)) {
         goto PIX_EXIT;
      }
   }
   else {
      //
      // matcing at the source image, no pyramid used
      // use the full search range (disparity)
      //
      nHorDisparity = nOriginHorDisparity;
      nVerDisparity = nOriginVerDisparity;
   }

   nLeftDisparity = (int)ceil((double)nHorDisparity);
   nRightDisparity = (int)ceil((double)nHorDisparity);
   nAboveDisparity = (int)ceil((double)nVerDisparity);
   nBelowDisparity = (int)ceil((double)nVerDisparity);

   //
   // correlation window
   //

   iOriginalMadoRadius = pEnv->_RectifySoukanMadoRadius.getInteger();

   if (!getResampledValue(iLevel, iOriginalMadoRadius, iMadoRadius)) {
      goto PIX_EXIT;
   }

   //iMadoRadius = (int)ceil((double)iOriginalMadoRadius);
   iMadoRadius = max(1, iMadoRadius);

   if (0 >= iMadoRadius) {
      goto PIX_EXIT;
   }

   iMadoSize = iMadoRadius * 2 + 1;
   
   // *** allocate mado template ***

   for (k = 0; k < 2; k++) {
      for (i = 0; i < nChan;i++) {
         if (!dMado2Col[k][i].Alloc(iMadoSize, iMadoSize)) {
            goto PIX_EXIT;
         }
      }
   }
   
   // create input(left) mado image - template

   if (bMatchGray) {
      if (!createMadoImage(iMadoRadius, iRow, iCol,
         dResample2Col[iOrigin][0], &dMado2Col[iOrigin][0])) {
            goto PIX_EXIT;
      }
   }
   else {
      if (!createMadoImage(iMadoRadius, iRow, iCol,
         dResample2Col[iOrigin][0], dResample2Col[iOrigin][1], dResample2Col[iOrigin][2],
         &dMado2Col[iOrigin][0], &dMado2Col[iOrigin][1], &dMado2Col[iOrigin][2])) {
            goto PIX_EXIT;
      }
   }
   
   // *** get standard deviation for each template ***
   // *** check if the standard deviation inside template image is large enough ***

   dMinStdDev = pEnv->_RectifyMinStdDev.getDouble();   
   bOriginDev = checkMadoStdev(nChan, dMinStdDev, dMado2Col[iOrigin]);
      
   if (!bOriginDev) {
      // standard deviation too low in all channels => not enough texture
      //pTag->setCorrStatus( pixq_FringeTag::CorrMatchTypeLowTex );
      usCorr = pixq_FringeTag::CorrMatchTypeLowTex;
      iRightCol = iInRightCol;
      iRightRow = iInRightRow;
      dCorr = 0.0;
      bUsed = false;
      // no texture in the correlation window -> this is kind of result!
      bRetCode = true;
      goto PIX_EXIT;
   }

   // *** search for the position of max correlation ***

   nSearchCols = nRightDisparity + nLeftDisparity + 1;
   nSearchRows = nAboveDisparity + nBelowDisparity + 1;

   if (!dMtxCorr.Alloc(nSearchRows, nSearchCols)) {
      goto PIX_EXIT;
   }

   dMtxCorr.Fill(0.0);

   if (!bMtxChecked.Alloc(nSearchRows, nSearchCols)) {
      goto PIX_EXIT;
   }

   bMtxChecked.Fill(false);

   // get correlation at all pixels in serach range

//#pragma omp parallel
//   {
//#pragma omp for private(iX,iY,iXPos,iYPos,iSearchCol,iSearchRow,dMado2Col) 
      for (iX = -nLeftDisparity; iX <= nRightDisparity; iX++) {
         for (iY = -nBelowDisparity; iY <= nAboveDisparity; iY++) {

            iXPos = iInRightCol + iX;
            iYPos = iInRightRow + iY;

            iSearchCol = iX + nLeftDisparity;
            iSearchRow = iY + nBelowDisparity;

            // create right mado image

            if (bMatchGray) {
               if (!createMadoImage(iMadoRadius, iYPos, iXPos, dResample2Col[iMatch][0],
                  &dMado2Col[iMatch][0])) {
                     continue;
               }
            }
            else {
               if (!createMadoImage(iMadoRadius, iYPos, iXPos,
                  dResample2Col[iMatch][0], dResample2Col[iMatch][1], dResample2Col[iMatch][2],
                  &dMado2Col[iMatch][0], &dMado2Col[iMatch][1], &dMado2Col[iMatch][2])) {
                     continue;
               }
            }

            // check standard deviation
            
            bMatchDev = checkMadoStdev(nChan, dMinStdDev, dMado2Col[iMatch]);
            if (!bMatchDev) {
               continue;
            }

            // get image correlation for each channel 

            for (k = 0; k < nChan; k++) {
               if (!getImageCorrelation_PI(&dMado2Col[iOrigin][k], &dMado2Col[iMatch][k], false, &dColCorr[k])) {
                  continue;
               }
            }

            iMaxCorr = getMaxValue_PC(nChan, dColCorr, &dPntCorr);

            dMtxCorr.Set(iSearchRow, iSearchCol, dPntCorr);
            bMtxChecked.Set(iSearchRow, iSearchCol, true);
         }
      }
  // }

   // find the max corr

   dMaxCorr = -10000.0;
   nChecked = 0;
   for (iX = -nLeftDisparity; iX <= nRightDisparity; iX++) {
      for (iY = -nBelowDisparity; iY <= nAboveDisparity; iY++) {

         iSearchCol = iX + nLeftDisparity;
         iSearchRow = iY + nBelowDisparity;

         bChecked=bMtxChecked.Get(iSearchRow, iSearchCol);
         if (!bChecked) continue;

         dPntCorr = dMtxCorr.Get(iSearchRow, iSearchCol);

         nChecked = nChecked + 1;

         if (dMaxCorr < dPntCorr) {
            iMaxCol = iX;
            iMaxRow = iY;
            dMaxCorr = dPntCorr;
         }
      }
   }

   if (0 >= nChecked) {
      // standard deviation too low in all mado's
      usCorr = pixq_FringeTag::CorrMatchTypeLowTex;
      iRightCol = iInRightCol;
      iRightRow = iInRightRow;
      dCorr = 0.0;
      bUsed = false;
      // no texture in the correlation window -> this is kind of result!
      bRetCode = true;
      goto PIX_EXIT;
   }

   // set the tag with maximum correlation         

   iRightCol = iInRightCol + iMaxCol;
   iRightRow = iInRightRow + iMaxRow;

   // set the tag's status
   // set USED to true onlyu if the correlation range is high! 

   dCorr = dMaxCorr;
   dHighBound = pEnv->_RectifySoukanHighBoundary.getDouble();

   if (dCorr < dHighBound) {
      usCorr = pixq_FringeTag::CorrMatchTypeCorrLow;
   }
   else {
      usCorr = pixq_FringeTag::CorrMatchTypeCorrHigh;
   }

   switch (usCorr) {
   case pixq_FringeTag::CorrMatchTypeCorrHigh:
      bUsed = true;
      break;

   default:
      bUsed = false;
      break;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   for (k = 0; k < nChan; k++) {
      for (i = 0; i < 2; i++) {
         dMado2Col[i][k].free();
      }
   }
   dMtxCorr.free( );
   bMtxChecked.free();
   return bRetCode;
}

