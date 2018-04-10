#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_cv_common.h"

#include "rectify_panes.h"
#include "rectify_table.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

#include "rectify_window.h"
#include "ui_rectify_window.h"


using namespace std;
void rectify_window::refreshEpipolarLine(void)
{
   bool bEpipolarDraw = getHorizontalMarker();

   if (!bEpipolarDraw) {
      goto PIX_EXIT;
   }

   _Image_Pane[0]->refreshSingle(); 
   _Image_Pane[1]->refreshSingle(); 
      
PIX_EXIT:
   return;
}

//
// decide the constant grid interval to get the desirted number if points
//
static int getOptimalGrid(int nValidWidth,
   int nValidHeight,
   int nIdealPoints)
{
   int nTags, nTagRows, nTagCols, nGridInterval;
   double dGridInterval, dA, dB, dC, dGrid0, dGrid1;
   bool bStatus;

   dA = 1.0 - (double)nIdealPoints;
   dB = (double)(nValidWidth + nValidHeight);
   dC = (double)(nValidWidth * nValidHeight);
   dGrid0 = (-dB - sqrt(dB * dB - 4.0 * dA * dC)) / 2.0 / dA;
   dGrid1 = (-dB + sqrt(dB * dB - 4.0 * dA * dC)) / 2.0 / dA;

   //dGridInterval = (double)nValidWidth * (double)nValidHeight / (double)nIdealPoints;   
   //dGridInterval = sqrt(dGridInterval);

   dGridInterval = dGrid0;
   nGridInterval = (int)floor(dGridInterval);
   
   nTagCols = 1+(int)floor((double)nValidWidth / (double)nGridInterval);
   nTagRows = 1 + (int)floor((double)nValidHeight / (double)nGridInterval);
   nTags = nTagCols * nTagRows;

   fprintf(stdout, ">>> Grid Interval=%d: Grids=%dW * %dH=%d ( Desired=%d).\n",
      nGridInterval, nTagCols, nTagRows, nTags, nIdealPoints);

   if (nTags >= nIdealPoints) {
      goto PIX_EXIT;
   }

   // get the optimal grid
   //

   bStatus = true;
   while (bStatus) {
      nGridInterval = nGridInterval - 1;

      nTagCols = 1 + (int)floor((double)nValidWidth / (double)nGridInterval);
      nTagRows = 1 + (int)floor((double)nValidHeight / (double)nGridInterval);
      nTags = nTagCols * nTagRows;

      fprintf(stdout, ">>> Grid Interval=%d: Grids=%dW * %dH=%d ( Desired=%d).\n",
         nGridInterval, nTagCols, nTagRows, nTags, nIdealPoints);

      if (nTags >= nIdealPoints) {
         bStatus = false;
      }
   }

PIX_EXIT:
   return nGridInterval;
}

//
// generate automatic tag points at regular (dense) grid
// parameters taken from property settings
//
// generate fringing tags at regular grid on the left image
// then, move each pointo to the closest stere feature
//
// notes:
// bRectify:
// true: after points are matched, image rectification is done too
// false: image matching only, no recitfication
//
bool rectify_window::rectifyGenerateControlPoints(bool bRectify)
{
   bool bRetCode = false;
   int nMadoRadius, nGridInterval;
   int nTags,  nTagRows, nTagCols, i, j, iY, iX, iSrcX,iSrcY;
   int nValidHeight, nValidWidth, nAreaHeight, nAreaWidth, nIdealPoints;
   int iExcludeEdge, iExcludeRateEdge;
   int k,  nWidth, nHeight, nMaxSide, nImgXSize[2], nImgYSize[2];

   rectify_table *pTab = getTablePane();
   pixq_Properties *pEnv = getRectifyEnv();
   pixq_FringesTag *pTags = getRectifyTag();

   vector<int> viTagRows, viTagCols;
   pixq_FringeTag *pTag;
   pixq_FringeTag Tag;

   QString strMessage;

   if (!validPaneDisplayMode()) {
      qDebug() << "Select two image sequences.!";
      goto PIX_EXIT;
   }

   qDebug() << "*** Rectification : Matching Grids ****";

   // *** init fringing control points ***
   // i.e. automatically generated tags at regular grid 

   // generate regular grids on left
   // clear tag positions

   pTags->init();
   pTags->setDrawRectifyTag(true);
   
   // get general parameters
   
   // get the optimal grid interval

   for (k = 0; k < 2; k++) {
      nImgXSize[k] = _ImageInMtx[k][0].getWidth();
      nImgYSize[k] = _ImageInMtx[k][0].getHeight();
   }

   nWidth = max(nImgXSize[0], nImgXSize[1]);
   nHeight = max(nImgYSize[0], nImgYSize[1]);

   nMaxSide = max(nWidth, nHeight);

   nIdealPoints = pEnv->_RectifyControlPointNumber.getInteger();
   if (0 >= nIdealPoints) {
      goto PIX_EXIT;
   }

   nMadoRadius = pEnv->_RectifySoukanMadoRadius.getInteger();

   iExcludeRateEdge = pEnv->_RectifyExcludeRateEdge.getInteger();
   iExcludeEdge = nMaxSide * iExcludeRateEdge / 100;

   //nValidWidth = nWidth - 2 * nMadoRadius - 2 * iFeatureSearch - 2 * iExcludeEdge;
   //nValidHeight = nHeight - 2 * nMadoRadius - 2 * iFeatureSearch - 2 * iExcludeEdge;
   nValidWidth = nWidth - 2 * nMadoRadius - 2 * iExcludeEdge;
   nValidHeight = nHeight - 2 * nMadoRadius - 2 * iExcludeEdge;

   qDebug() << "*** Control Points:";
   qDebug() << "*** Ideal point number:" << nIdealPoints;
   qDebug() << "*** Area excluded from the edge:" << iExcludeEdge;
   qDebug() << "*** Image Width and Height:" << nWidth << "," << nHeight;
   qDebug() << "*** Valid Image Width and Height:" << nValidWidth << "," << nValidHeight;

   nGridInterval = getOptimalGrid(nValidWidth, nValidHeight, nIdealPoints);
   
   qDebug() << "*** Grid Interval:" << nGridInterval << "X" << nGridInterval;
   
   // list x positions

   nTags = (int)floor((double)nValidWidth / (double)nGridInterval);
   nAreaWidth = nTags * nGridInterval;
   viTagCols.resize(1+nTags);
   for (i = 0; i <= nTags; i++) {
      iX = nWidth / 2 - nAreaWidth / 2 + i * nGridInterval;
      iX = clumpCoo(iX, nWidth);
      viTagCols.at(i) = iX;
   }

   // list y positions

   nTags = (int)floor((double)nValidHeight / (double)nGridInterval);
   nAreaHeight = nTags * nGridInterval;
   viTagRows.resize(1+nTags);
   for (i = 0; i <= nTags; i++) {
      iY = nHeight / 2 - nAreaHeight / 2 + i * nGridInterval;
      iY = clumpCoo(iY, nHeight);
      viTagRows.at(i) = iY;
   }

   //
   // init tag pos matrix
   //

   nTagRows = (int)viTagRows.size();
   nTagCols = (int)viTagCols.size();
   nTags = nTagRows * nTagCols;
   
   qDebug() << "*** Control Points:" << nTagRows << "(vertical) X " << nTagCols<<"(horizontal)="<<nTags;

   pTags->Resize(nTags);
   pTags->setTagRows(nTagRows);
   pTags->setTagCols(nTagCols);

   //
   // snap to feature points
   //
   
   for (i = 0; i < nTagRows; i++) {
      for (j = 0; j < nTagCols; j++) {

         iSrcX = viTagCols.at(j);
         iSrcY = viTagRows.at(i);

         pTag = pTags->getTag(j, i);
         rectifyInitSingleTag(pTag, iSrcX, iSrcY);

#ifdef _DEBUG
         fprintf(stdout, "Tag %2d,%2d: Src (%4d,%4d) -> feature (%4d,%4d).\n",j,i,
            pTag->getXTag(), pTag->getYTag(),
            pTag->getRightXTag(), pTag->getRightYTag());
#endif // _DEBUG
      }
   }

   // show the results!

   pTab->setTableContents();
   refreshPanes();
   
   //bRetCode = true;
   //goto PIX_EXIT;
   
   //
   // start tags matching thread!!
   //

   if (!startLoaderThread( bRectify)) {
      goto PIX_EXIT;
   }
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// run the matching for the current frame ***
//
// do the matching for all tags in the tag list
// at the given pyramid level
//
// only use the top level pyramid
//
bool rectify_window::rectifyImageMatchTag(int iTag)
{
   bool bRetCode = false;
   pixq_FringeTag *pTag;

   pixq_FringesTag *pTags = getRectifyTag();
   int nTags = pTags->getTags();

   if (0 > iTag || nTags <= iTag) {
      goto PIX_EXIT;
   }

   // *** draw grid on screen ***

   pTags->setDrawRectifyTag(true);
   pTag = pTags->getNthTag(iTag);

   if (!rectifyImageMatchTag(pTag)) {
      goto PIX_EXIT;
   }

   refreshPanes();

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   QApplication::restoreOverrideCursor();
   return bRetCode;
}

bool rectify_window::rectifyImageMatchTag(pixq_FringeTag *pTag)
{
   bool bRetCode = false;
   int iCol, iRow, iRightCol, iRightRow;
   unsigned short usCorr;
   double dCorr;
   bool bUsed;

   bool bUsePyramid = false;      
   int iLevel = 0;
   pixq_Properties *pEnv = getRectifyEnv();
   
   QApplication::setOverrideCursor(Qt::BusyCursor);

   // *** get correlation ***
   
   bUsePyramid = pEnv->_RectifyMatchUsePyramid.getBool();

   iCol = pTag->getLevelTagX(iLevel);
   iRow = pTag->getLevelTagY(iLevel);
   iRightCol = pTag->getLevelRightTagX(iLevel);
   iRightRow = pTag->getLevelRightTagY(iLevel);
   usCorr = pTag->getCorrStatus();

#ifdef _DEBUG
   //iCol = iRightCol = 1765;
   //iRow = iRightRow = 1847;
#endif // _DEBUG

   if (bUsePyramid) {
      if (!rectifyMatchSingleTagPointPyr(iCol, iRow, iRightCol, iRightRow,
         usCorr, dCorr, bUsed)) {
            goto PIX_EXIT;
      }
   }
   else {
      //
      // no pyramid
      //
      if (!rectifyMatchSingleTagPointTop(iCol, iRow, iRightCol, iRightRow,
         usCorr, dCorr, bUsed)) {
            goto PIX_EXIT;
      }
   }

   // set the results to vector of tags

   pTag->setRightXLevelTag(iLevel, iRightCol);
   pTag->setRightYLevelTag(iLevel, iRightRow);

   pTag->setXTag(iCol);
   pTag->setYTag(iRow);
   pTag->setRightTag(iRightCol, iRightRow);
   pTag->setDisparity();

   pTag->setCorrStatus(usCorr);
   pTag->SetCorrVal(dCorr);
   pTag->setUsed(bUsed);
   pTag->SetSelected(false);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   QApplication::restoreOverrideCursor();
   return bRetCode;
}

//
// notes:
// iMatching must be one of ITQF_DepthEnv::PurposeForMatching
// only use the top level (source) image, no pyramid
//
// returns:
// true - computation end, with any result, could be bUsed=false;
// false - something went wrong
//
bool rectify_window::rectifyMatchSingleTagPointPyr(
   const int iLeftCol,     // [i] left image column, coo at the original level
   const int iLeftRow,     // [i] left image row, coo at the original level
   int &iRightCol,         // [i/o] right(matched)  image column, coo at the original level
   int &iRightRow,         // [i/o] right(matched)  image row, coo at the original level
   unsigned short &usCorr, // [o] correlation type, one of pixq_FringeTag::CorrMatchTypes
   double &dCorr,          // [o] correlation, 0.0 - 1.0
   bool &bUsed)            // [o]
{
   bool bRetCode = false;
   bool bUsePyramid = true;
   bool bLevelUsed;
   unsigned short usLevelCorr;
   double dLevelCorr;
   int nAllLevels, k, iLevel, iLevelLeftCol, iLevelLeftRow, iLevelRightCol, iLevelRightRow;
   vector<int> iAllLevels;

   // list of levels

   iAllLevels.clear();
   for (k = _nPyramidLevel - 1; k >=0 ; k--) {
      iAllLevels.push_back(k);
   }
      
#ifdef _DEBUG
   fprintf(stdout, ">>> rectifyMatchSingleTagPointPyr <<<\n");
   fprintf(stdout, "...Source: L(%4d,%4d) -> R (%4d,%4d).\n",
      iLeftCol, iLeftRow, iRightCol, iRightRow);
#endif // _DEBU

   nAllLevels = (int)iAllLevels.size();
   for (k = 0; k < nAllLevels; k++) {
      iLevel = iAllLevels.at(k);

      // left target point at the level pyramid image
      if (!getResampledValue(iLevel, iLeftCol, iLevelLeftCol)) {
         goto PIX_EXIT;
      }

      if (!getResampledValue(iLevel, iLeftRow, iLevelLeftRow)) {
         goto PIX_EXIT;
      }

      if (0 == k) {
         //
         // the first level 
         // set the initial value as the left
         //
         if (!getResampledValue(iLevel, iRightCol, iLevelRightCol)) {
            goto PIX_EXIT;
         }

         if (!getResampledValue(iLevel, iRightRow, iLevelRightRow)) {
            goto PIX_EXIT;
         }
      }
      else {
         // 
         // from the second level
         // use the estiate at the lower level as the initial value
         //
         iLevelRightCol = iLevelRightCol * 2;
         iLevelRightRow = iLevelRightRow * 2;
      }

#ifdef _DEBUG
      //fprintf(stdout, "...Level %d:\n", iLevel);
      //fprintf(stdout, "...Level %d: In L(%4d,%4d) -> R(%4d,%4d).\n", iLevel,
      //   iLevelLeftCol, iLevelLeftRow, iLevelRightCol, iLevelRightRow);
#endif // _DEBUG

      if (!rectifyMatchSingleTagPointLevel(iLevel, iLevelLeftCol, iLevelLeftRow, 
         iLevelRightCol, iLevelRightRow,
         usLevelCorr, dLevelCorr, bLevelUsed, bUsePyramid)) {
            goto PIX_EXIT;
      }

      if (!bLevelUsed) {
#ifdef _DEBUG
         fprintf(stdout, "...Level %d: Matching aborted(%d).\n", iLevel, usLevelCorr);
#endif // _DEBUG
         bRetCode = true; 
         usCorr = usLevelCorr;
         dCorr = dLevelCorr;
         bUsed = bLevelUsed;
      }

#ifdef _DEBUG
      fprintf(stdout, "...Level %d: Out L(%4d,%4d) -> R(%4d,%4d) : Corr=%7.3f(%1d).\n", iLevel,
         iLevelLeftCol, iLevelLeftRow, iLevelRightCol, iLevelRightRow, 
         dLevelCorr, usLevelCorr);
#endif // _DEBU

   }

   iRightCol = iLevelRightCol;
   iRightRow = iLevelRightRow;

   usCorr = usLevelCorr;
   dCorr = dLevelCorr;
   bUsed = bLevelUsed;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// notes:
// iMatching must be one of ITQF_DepthEnv::PurposeForMatching
// only use the top level (source) image, no pyramid
//
bool rectify_window::rectifyMatchSingleTagPointTop(
   const int iCol,         // [i] left image column, coo at the top
   const int iRow,         // [i] left image row, coo at the top
   int &iRightCol,         // [i/o] right image column, estimate and matched, coo at the top
   int &iRightRow,         // [i/o] right image row, estimate and matched, coo at the top
   unsigned short &usCorr, // [o]
   double &dCorr,          // [o]
   bool &bUsed)            // [o]
{
   bool bRetCode = false;
   int iLevel = 0;
   bool bUsePyramid = false;

   if (!rectifyMatchSingleTagPointLevel(iLevel, iCol, iRow, iRightCol, iRightRow,
      usCorr, dCorr, bUsed, bUsePyramid)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// start rectification using current tags
//
bool rectify_window::rectifyAnalyzeTagPoints(bool bItration) // [i] do the iteration until the max disparity is obtained
{
   bool bRetCode = false;
   pixq_Properties *pEnv = getRectifyEnv();
   QString strMessage;
   double dAvrResidual, dMaxResidual;
   int nTags, iMaxTag, i, k;
   rectify_table *pTab = getTablePane();
   pixq_FringesTag *pTags = getRectifyTag();
   pixq_FringeTag *pTag;

   unsigned short usGray = 65536 / 4 - 1;

#ifdef _USE_OPENCV2
   int nUsedTags;
   double dH0[3][3], dH1[3][3];
   
   if (!validPaneDisplayMode()) {
      qDebug() << "Select two image sequences.!";
      goto PIX_EXIT;
   }

   nTags = pTags->getTags();

   if (bItration) {
      //
      // repeat the compuation until desired disparity is obtained
      //
      double dResiThres = pEnv->_RectifyCvRectifyThreshold.getDouble();
      bool bStatus;
      int iIteration;

      // 
      // select checked points on the control panel
      // !MUST do this before getting rotation matrix!
      //

      iIteration = 0;
      bStatus = true;
      while (bStatus) {

         nUsedTags = pTags->getUsedTags();
         if (7 > nUsedTags) {
            pTags->setAllUsed(false);
            qDebug() << "ERROR! Need more rectification tags.";
            QString strApplication = _version.getApplication();
            strMessage = getRectifyLabel("Warning", "NoEnoughPoint") + "\n" +
               getRectifyLabel("Warning", "NoRectif");
            QMessageBox::critical(this, strApplication, strMessage);
            goto PIX_EXIT;
         }

         //
         // get rotation matrices from the current set of tags
         //

         if (!rectifyGetRorationMatrix(dH0, dH1)) {
            goto PIX_EXIT;
         }

         dAvrResidual = pTags->getAverageRectifyDisparity();
         dMaxResidual = pTags->getMaxRectifyDisparity(iMaxTag);
         if (0 > iMaxTag) {
            goto PIX_EXIT;
         }

         fprintf(stdout, ">>> Iteration %2d: Used Tags %2d/%2d: Avr Residual=%11.5f Max Residual %11.5f at %d(Thres=%f).\n", 
            iIteration, nUsedTags, nTags, dAvrResidual, dMaxResidual, iMaxTag, dResiThres);
         
         //if (dAvrResidual > dResiThres) {
         if (dMaxResidual > dResiThres) {
            //
            // remove the tag with larget residual and redo the compuation!
            //
            pTag = pTags->getNthTag(iMaxTag);
            pTag->setCorrStatus(pixq_FringeTag::CorrMatchTypeOutlier);
            pTag->setUsed(false);
            iIteration = iIteration + 1;
         }
         else {
            //
            // target residual obtained!
            //
            bStatus = false;
            continue;
         }
      }

   }
   else {
      // 
      // select checked points on the control panel
      // !MUST do this before getting rotation matrix!
      //

      nUsedTags = pTags->getUsedTags();
      if (7 > nUsedTags) {
         qDebug() << "ERROR! Need more rectification tags.";
         goto PIX_EXIT;
      }

      //
      // get rotation matrices from the current set of tags
      //

      if (!rectifyGetRorationMatrix(dH0, dH1)) {
         goto PIX_EXIT;
      }
   }

   // clear thderived image

   for (k = 0; k < 2; k++) {
      for (i = 0; i < 3; i++) {
         _ImageDrvMtx[k][i].Fill(usGray);
      }
   }

   if (!createDerivedTexture()) {
      goto PIX_EXIT;
   }

   // show the result on the list and image

   pTab->setTableContents();
   refreshPanes();

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
#endif // _USE_OPENCV2
   return bRetCode;
}


//
// start rectification using current tags
//
#ifdef _USE_OPENCV2
bool rectify_window::rectifyGetRorationMatrix(double dH0[3][3], // [o] projective transformation for image 0
   double dH1[3][3]) // [o] projective transformation for image 1

{
   bool bRetCode = false;
   //QString strMessage;
   string strLog;
   vector<uchar> status;
   vector<Point2f> imgPoints0;
   vector<Point2f> imgPoints1;
   double dF[3][3];
   Point2f check_pnt[2];

   pixq_Properties *pEnv = getRectifyEnv();
   pixq_FringesTag *pTags = getRectifyTag();

   Mat cameraMatrix[2], distCoeffs[2];

   pixq_Matrix<double> MatH0, MatH1, MatH0Inv, MatH0InvH1;

   QString strMessage, strHead[3];

   Mat F; // F Matrix, conversion matrix for stereo rectification
   Mat H0;
   Mat H1;
   Mat R1, R2, P1, P2, Q;

   int nWidth = _ImageInMtx[0][0].getWidth(); 
   int nHeight = _ImageInMtx[0][0].getHeight(); 

   bool bUsed;
   int iDiff, nUsedTags;
   int nLogs, iCvMethod, iX[2], iY[2], i, j, k, nTags, nInputTags;
   pixq_FringeTag *pTag;

   Size img_size;
   Point2f pnt0, pnt1;
   Mat ptMat0, ptMat1; // matrix to store the pairs of tags 

   QString strApplication = _version.getApplication();

   // paraeters

   int iMethod = pEnv->_RectifyCvFundamentalMethod.getInteger();
   double dParam1 = pEnv->_RectifyCvFundamentalDistance.getDouble();
   double dParam2 = pEnv->_RectifyCvFundamentalConfidence.getDouble();
   double dThres = pEnv->_RectifyCvRectifyThreshold.getDouble();

   // set image points to opencv buffer

   nInputTags = (int)pTags->getTags();
   if (8 > nInputTags) {
      strMessage = getRectifyLabel("Warning", "NoEnoughPoint");
      QMessageBox::critical(this, strApplication, strMessage);
      goto PIX_EXIT;
   }

   imgPoints0.clear();
   imgPoints1.clear();

   //

   nUsedTags = 0;
   iDiff = 0.0;
   for (i = 0; i < nInputTags; i++) {
      pTag = (pixq_FringeTag*)pTags->getNthTag(i);

      bUsed = pTag->getUsed();

      // *** Do not use this selection! 
      // *** points must be all over the image??

      if (!bUsed) continue;

      iX[0] = pTag->getXTag();
      iY[0] = pTag->getYTag();
      iX[1] = pTag->getRightXTag();
      iY[1] = pTag->getRightYTag();

      nUsedTags++;
   }

   k = 0;
   for (i = 0; i < nInputTags; i++) {
      pTag = (pixq_FringeTag*)pTags->getNthTag(i);

      bUsed = pTag->getUsed();

      // *** Do not use this selection! 
      // *** points must be all over the image??

      if (!bUsed) continue;

      iX[0] = pTag->getXTag();
      iY[0] = pTag->getYTag();
      iX[1] = pTag->getRightXTag();
      iY[1] = pTag->getRightYTag();

      pnt0.x = (float)iX[0];
      pnt0.y = (float)(iY[0]);
      imgPoints0.push_back(pnt0);

      pnt1.x = (float)iX[1];
      pnt1.y = (float)iY[1];
      imgPoints1.push_back(pnt1);

      k++;
   }

   nTags = (int)imgPoints1.size();

   // show the parameters

   strMessage.sprintf("Calculating the fundamental Matrix from %d[/%d] Points....",
      nTags, nInputTags);
   qDebug() << strMessage;

   strMessage = tr("---> Method: ");
   strMessage = strMessage + tr((pEnv->FundamentalMethodName()).c_str());
   qDebug() << strMessage;

   strMessage.sprintf("---> Max Distance: %.2f", dParam1);
   qDebug() << strMessage;

   strMessage.sprintf("---> Confidence Level: %.2f", dParam2);
   qDebug() << strMessage;

   strMessage.sprintf("---> Accuracy Threshold: %.2f", dThres);
   qDebug() << strMessage;

   //
   // calculate rotation matrix
   // 
   // F = fundamental matrix, 3X3.
   //
   // status = The output array of N elements, every element of which is set to 0 for outliers
   //          and to 1 for the other points. 
   //          The array is computed only in RANSAC and LMedS methods. 
   //          For other methods it is set to all 1's
   //
   // H1 = The output rectification homography matrices for the first images, 3X3.
   // H2 = The output rectification homography matrices for the second images, 3X3.

   nTags = (int)imgPoints0.size();
   ptMat0 = Mat(imgPoints0);
   ptMat1 = Mat(imgPoints1);

   switch (iMethod) {
   case pixq_Properties::FundamentalMethod7Point:
      iCvMethod = CV_FM_7POINT;
      if (7 != nTags) {
         strMessage = getRectifyLabel("Warning", "Seven");
         QMessageBox::critical(this, strApplication, strMessage);
         qDebug() << strMessage;
         goto PIX_EXIT;
      }
      break;
   case pixq_Properties::FundamentalMethod8Point:
      iCvMethod = CV_FM_8POINT;
      if (8 > nTags) {
         strMessage = getRectifyLabel("Warning", "Eight");
         QMessageBox::critical(this, strApplication, strMessage);
         qDebug() << strMessage;
         goto PIX_EXIT;
      }
      break;
   case pixq_Properties::FundamentalMethodRansac:
      iCvMethod = CV_FM_RANSAC;
      if (8 > nTags) {
         strMessage = getRectifyLabel("Warning", "Eight");
         QMessageBox::critical(this, strApplication, strMessage);
         qDebug() << strMessage;
         goto PIX_EXIT;
      }
      break;
   case pixq_Properties::FundamentalMethodLmeds:
      iCvMethod = CV_FM_LMEDS;
      if (8 > nTags) {
         strMessage = getRectifyLabel("Warning", "Eight");
         QMessageBox::critical(this, strApplication, strMessage);
         qDebug() << strMessage;
         goto PIX_EXIT;
      }
      break;
   }

   try {
      F = cv::findFundamentalMat(ptMat0, ptMat1, status, iCvMethod, dParam1, dParam2);
   }

   catch (const std::exception &e) {
      QString strMessage1 = getRectifyLabel("Warning", "MatFail");
      QString strMessage2 = getRectifyLabel("Warning", "MethodFail");
      QString strError = e.what();
      QString strWarning = strMessage1 + "\n" + strMessage2 + "\n\n" + strError;
      QMessageBox::critical(NULL, strApplication, strWarning);
      goto PIX_EXIT;
   }

   img_size.height = nHeight;
   img_size.width = nWidth;
   
   try {
      cv::stereoRectifyUncalibrated(ptMat0, ptMat1, F, img_size, H0, H1, dThres);
   }

   catch (const std::exception &e) {
      QString strMessage1 = getRectifyLabel("Warning", "RectifyFail");
      QString strMessage2 = getRectifyLabel("Warning", "MethodFail");
      QString strError = e.what();
      QString strWarning = strMessage1 + "\n" + strMessage2 + "\n\n" + strError;
      QMessageBox::critical(NULL, strApplication, strWarning);
      goto PIX_EXIT;
   }

   //
   // *** computation is done ***
   //

   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
         dF[i][j] = (double)F.at<double>(i, j);
         dH0[i][j] = (double)H0.at<double>(i, j);
         dH1[i][j] = (double)H1.at<double>(i, j);
      }
   }

   //
   // show the result and check disparity
   //

   fprintf(stdout, "F - Fundamental Matrix:\n");

   for (i = 0; i < 3; i++) {
      fprintf(stdout, "| %11.5f %11.5f %11.5f |\n", dF[i][0], dF[i][1], dF[i][2]);
   }

   fprintf(stdout, "Parameters for projective transformation:\n");
   fprintf(stdout, " u = [ m1 * x + m2 * y + m3 ] / [ m7 * x + m8 * y + m9]\n");
   fprintf(stdout, " v = [ m4 * x + m5 * y + m5 ] / [ m7 * x + m8 * y + m9]\n");

   //

   fprintf(stdout,"H1/H2: Homography Matrices Uncalibrated:\n");

   i = 0;
   fprintf(stdout, "| m1 m2 m3 |   | %7.3f %7.3f %7.3f |   | %7.3f %7.3f %7.3f |\n", 
      dH0[i][0], dH0[i][1], dH0[i][2], dH1[i][0], dH1[i][1], dH1[i][2]);
   i = 1;
   fprintf(stdout, "| m4 m5 m6 | = | %7.3f %7.3f %7.3f | * | %7.3f %7.3f %7.3f |\n",
      dH0[i][0], dH0[i][1], dH0[i][2], dH1[i][0], dH1[i][1], dH1[i][2]);
   i = 2;
   fprintf(stdout, "| m7 m8 m9 |   | %7.3f %7.3f %7.3f |   | %7.3f %7.3f %7.3f |\n", 
      dH0[i][0], dH0[i][1], dH0[i][2], dH1[i][0], dH1[i][1], dH1[i][2]);


   nTags = (int)imgPoints0.size();
   for (k = 0; k < nTags; k++) {
      unsigned char ucStat = status.at(k);
      pTag = (pixq_FringeTag*)pTags->getNthTag(i);
      pTag->SetRotOutlier((0 == ucStat) ? true : false);
   }

   //
   // convert H0,H1 to I,H0(-1)*H1
   // H0' - Identity Matrix
   // H1' - Inverse of H0 * H1 
   // Ning's suggestion
   //

   MatH0.Alloc(3, 3);
   MatH1.Alloc(3, 3);
   MatH0Inv.Alloc(3, 3);
   MatH0InvH1.Alloc(3, 3);

   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
         MatH0.Set(i, j, dH0[i][j]);
         MatH1.Set(i, j, dH1[i][j]);
      }
   }

   if (!MatH0.getInverse3x3(&MatH0Inv)) {
      goto PIX_EXIT;
   }

   MatH0InvH1.sqrProduct(&MatH0Inv, &MatH1);

   MatH0.Identity();
   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
         dH0[i][j] = (float)MatH0.Get(i, j);
         dH1[i][j] = (float)MatH0InvH1.Get(i, j);
      }
   }

   fprintf(stdout, "H1/H2: Homography Matrices Normalized:\n");

   i = 0;
   fprintf(stdout, "| m1 m2 m3 |   | %7.3f %7.3f %7.3f |   | %7.3f %7.3f %7.3f |\n", 
      dH0[i][0], dH0[i][1], dH0[i][2], dH1[i][0], dH1[i][1], dH1[i][2]);
   i = 1;
   fprintf(stdout, "| m4 m5 m6 | = | %7.3f %7.3f %7.3f | * | %7.3f %7.3f %7.3f |\n",
      dH0[i][0], dH0[i][1], dH0[i][2], dH1[i][0], dH1[i][1], dH1[i][2]);
   i = 2;
   fprintf(stdout, "| m7 m8 m9 |   | %7.3f %7.3f %7.3f |   | %7.3f %7.3f %7.3f |\n", 
      dH0[i][0], dH0[i][1], dH0[i][2], dH1[i][0], dH1[i][1], dH1[i][2]);
   
   //
   // set the projective transformation matrics in tag list
   //

   pTags->storeRectification(dH0, dH1);

   nLogs = pTags->LogLines();
   for (i = 0; i < nLogs; i++) {
      strLog = pTags->GetLog(i);
      qDebug() << strLog.c_str();
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
#endif // _USE_OPENCV2

