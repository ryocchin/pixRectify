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

//
// color to draw selected fringing tags
//
void rectify_window::getSelectedColor(float *fTagColor) 
const
{
   fTagColor[0] = 1.0f;
   fTagColor[1] = 0.0f;
   fTagColor[2] = 1.0f;

   return;
}


//
// color to draw fringing tags
// according to the status, and used/not-used
//
void rectify_window::getStatusColor(const unsigned short usStatus, // [i]
   float *fTagColor) 
   const
{
   pixq_Properties *pEnv = getRectifyEnv();
   QColor colValue;

   switch (usStatus) {
   case pixq_FringeTag::CorrMatchTypeLowTex:
      colValue = pEnv->_MatchLowTexureColor.getColor();
      fTagColor[0] = (float)colValue.redF();
      fTagColor[1] = (float)colValue.greenF();
      fTagColor[2] = (float)colValue.blueF();
      break;

   case pixq_FringeTag::CorrMatchTypeCorrLow:
      colValue = pEnv->_MatchLowCorrColor.getColor();
      fTagColor[0] = (float)colValue.redF();
      fTagColor[1] = (float)colValue.greenF();
      fTagColor[2] = (float)colValue.blueF();
      break;

   case pixq_FringeTag::CorrMatchTypeCorrHigh:
      colValue = pEnv->_MatchHighCorrColor.getColor();
      fTagColor[0] = (float)colValue.redF();
      fTagColor[1] = (float)colValue.greenF();
      fTagColor[2] = (float)colValue.blueF();
      break;

   case pixq_FringeTag::CorrMatchTypeOutlier:
      colValue = pEnv->_MatchOutlierColor.getColor();
      fTagColor[0] = (float)colValue.redF();
      fTagColor[1] = (float)colValue.greenF();
      fTagColor[2] = (float)colValue.blueF();
      break;

   case pixq_FringeTag::CorrMatchTypeUnknown:
      fTagColor[0] = 1.0f;
      fTagColor[1] = 1.0f;
      fTagColor[2] = 1.0f;
      break;

   case pixq_FringeTag::CorrMatchTypeNotAnalyzed:
      colValue = pEnv->_MatchNotAnalyzedColor.getColor();
      fTagColor[0] = (float)colValue.redF();
      fTagColor[1] = (float)colValue.greenF();
      fTagColor[2] = (float)colValue.blueF();
      break;

   default:
      fTagColor[0] = 1.0f;
      fTagColor[1] = 1.0f;
      fTagColor[2] = 1.0f;
      break;
   }

   return;
}

void rectify_window::getStatusColor(const bool bUsed,  // [i] point used?
   const unsigned short usStatus, // [i]
   float *fTagColor) 
   const
{
   pixq_Properties *pEnv = getRectifyEnv();
   QColor colValue;

   if (pixq_FringeTag::CorrMatchTypeOutlier == usStatus) {
      colValue = pEnv->_MatchOutlierColor.getColor();
      fTagColor[0] = (float)colValue.redF();
      fTagColor[1] = (float)colValue.greenF();
      fTagColor[2] = (float)colValue.blueF();
   }
   else {

      if (bUsed) {
         getStatusColor(usStatus, fTagColor);
      }
      else {
         colValue = pEnv->_MatchUnusedColor.getColor();
         fTagColor[0] = (float)colValue.redF();
         fTagColor[1] = (float)colValue.greenF();
         fTagColor[2] = (float)colValue.blueF();
      }
   }

   return;
}


bool rectify_window::rectifyInitSingleTag(pixq_FringeTag *pTag,
   int iSrcX,
   int iSrcY)
{
   bool bRetCode = false;
   bool bSnapFeature;
   int k, nWidth, nHeight, nImgXSize[2], nImgYSize[2];
   int iFeatureSearch, iTop, iBottom, iLeft, iRight, iX, iY;
   pixq_Properties *pEnv = getRectifyEnv();
   vector<pixq_FringeTag> vFeaturesTags;
   pixq_FringeTag *pFeaturesTag;

   //

   for (k = 0; k < 2; k++) {
      nImgXSize[k] = _ImageInMtx[k][0].getWidth();
      nImgYSize[k] = _ImageInMtx[k][0].getHeight();
   }

   nWidth = max(nImgXSize[0], nImgXSize[1]);
   nHeight = max(nImgYSize[0], nImgYSize[1]);

   //

   bSnapFeature = pEnv->_RectifySnapFeaturePoint.getBool();
   if (bSnapFeature) {
      iFeatureSearch = pEnv->_RectifyFeatureSearchRange.getInteger();
      if (0 >= iFeatureSearch) {
         bSnapFeature = false;
         iFeatureSearch = 0;
      }
   }
   else {
      iFeatureSearch = 0;
   }

   //

   iX = iSrcX;
   iY = iSrcY;

   //
   // define square around this grid position
   // and find good feature inside the square
   //

   pTag->init();

   if (bSnapFeature) {
      iX = iSrcX;
      iY = iSrcY;

      //
      // define square around this grid position
      // and find good feature inside the square
      //

      iTop = iY - iFeatureSearch;
      iBottom = iY + iFeatureSearch;
      iLeft = iX - iFeatureSearch;
      iRight = iX + iFeatureSearch;

      iTop = clumpCoo(iTop, nHeight);
      iBottom = clumpCoo(iBottom, nHeight);
      iLeft = clumpCoo(iLeft, nWidth);
      iRight = clumpCoo(iRight, nWidth);

      vFeaturesTags.resize(3);

      pFeaturesTag = (pixq_FringeTag*)&vFeaturesTags.at(0);
      pFeaturesTag->setTag(iLeft, iTop);

      pFeaturesTag = (pixq_FringeTag*)&vFeaturesTags.at(1);
      pFeaturesTag->setTag(iRight, iBottom);

      if (searchStereoFeature(&vFeaturesTags)) {
         pFeaturesTag = (pixq_FringeTag*)&vFeaturesTags.at(2);
         iX = pFeaturesTag->getXTag();
         iY = pFeaturesTag->getYTag();
      }
      else {
         iX = iSrcX;
         iY = iSrcY;
      }

      pTag->setTag(iX, iY);
      pTag->setRightTag(iX, iY);
   }
   else {
      pTag->setTag(iSrcX, iSrcY);
      pTag->setRightTag(iSrcX, iSrcY);
   }

   pTag->setCorrStatus(pixq_FringeTag::CorrMatchTypeNotAnalyzed);
   pTag->setLevelTags();

#ifdef _DEBUG
   //fprintf(stdout, "Src (%4d,%4d) -> feature (%4d,%4d).\n", 
   //   pTag->getXTag(), pTag->getYTag(),
   //   pTag->getRightXTag(), pTag->getRightYTag());
#endif // _DEBUG

   //
   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

// 
// a point on left image is hit!
// now match on the right image
//
bool rectify_window::rectifyHitAndMatch(int iMouseX, int iMouseY)
{
	bool bRetCode = false;
	const pixq_ScreenPara *pScreen = getScreenPara();
	const pixq_PanePara *pFlip = pScreen->getLeftFlip();
   int iSrcX, iSrcY, iFeatureX, iFeatureY;
   int iLeftX, iLeftY, iRightX, iRightY;
   double dCorr, dPixX, dPixY;
   unsigned short usCorr;
   pixq_FringeTag *pTag;

   rectify_table *pTab = getTablePane();
   pixq_FringesTag *pTags = getRectifyTag();
   QString strStatus;
   QByteArray buf;
   
   if (!validPaneDisplayMode()) {
      qDebug() << "Select two image sequences.!";
      goto PIX_EXIT;
   }
   
   // coordinate   

	pFlip->viewportToPixelCoo(iMouseX, iMouseY, &dPixX, &dPixY);
   iSrcX = (int)floor(dPixX);
   iSrcY = (int)floor(dPixY);

   qDebug() << "Hit! Image coordinate " << iSrcX << "," << iSrcY;
	
   //

   pTags->init();
   pTags->setDrawRectifyTag(true);
   pTags->Resize(1);
   pTags->setTagRows(1);
   pTags->setTagCols(1);
   
   //

   pTag = pTags->getNthTag(0);
   rectifyInitSingleTag(pTag, iSrcX, iSrcY);

   iFeatureX = pTag->getXTag();
   iFeatureY = pTag->getYTag();

#ifdef _DEBUG
   fprintf(stdout, "Hit Match: Hit (%4d,%4d) -> feature point (%4d,%4d).\n",
      iSrcX, iSrcY, iFeatureX, iFeatureY);
#endif // _DEBUG

   pTab->setTableContents();
   refreshPanes();

   // match!

   if (!rectifyImageMatchTag(pTag)) {
      goto PIX_EXIT;
   }

   refreshPanes();

   //
   // show results
   //

   iLeftX = pTag->getXTag();
   iLeftY = pTag->getYTag();
   iRightX = pTag->getRightXTag();
   iRightY = pTag->getRightYTag();
   dCorr = pTag->getCorrVal();

   usCorr = pTag->getCorrStatus();
   strStatus = pTag->getMatchStatusString();
   buf = strStatus.toLatin1();

   fprintf(stdout, "Matched L(%4d,%4d) - >R(%4d,%4d) : Corr=%5.2f(%s).\n",
      iLeftX, iLeftY, iRightX, iRightY, dCorr, buf.data());

   // set this point is the list and draw the point

   pTab->setTableContents();
   refreshPanes();

   //
	// --- Done ---
   bRetCode = true;
PIX_EXIT:
   resetLeftMouseMode();
   return bRetCode;
}