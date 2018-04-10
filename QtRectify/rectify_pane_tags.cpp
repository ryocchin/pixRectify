#include <pixqt_common.h>
#include <piximg_common.h>
 
#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_panes.h"
#include "rectify_window.h"
 
#include "rectify_pane.h"

//
// to generate image for the manual
//
#ifdef _DEBUG
#define DRAW_MANUAL_IMAGE  
#endif // _DEBUG

//
// draw tags position
//
void rectify_pane::drawRectifyTags(void)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   int i;

   pixq_FringeTag *pTag;
   pixq_FringesTag *pTags = pMain->getRectifyTag();
   int nTags = pTags->getTags();

   // *** draw source area on index ***

   glDisable(GL_TEXTURE_RECTANGLE_ARB);

   glDisable(GL_LIGHTING); // to show lines in color
   glDisable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

   glDrawBuffer(GL_BACK);

   if (!pTags->getDrawRectifyTag()) {
      goto PIX_EXIT;
   }

   for (i = 0; i < nTags; i++) {
      pTag = pTags->getNthTag(i);
      if (!pTag) continue;
      drawRectifyTag(pTag);
   }

   // --- Done ---
PIX_EXIT:
   return;
}

//
// draw tags position
//
void rectify_pane::drawRectifyTag(pixq_FringeTag *pTag)
{
   short sStatus = (short)pTag->getCorrStatus();

   // *** draw tag according to its status ***

   switch (sStatus) {
   case pixq_FringeTag::CorrMatchTypeUnknown:
   case pixq_FringeTag::CorrMatchTypeNotAnalyzed:
   case pixq_FringeTag::CorrMatchTypeLowTex:
      //drawRectifySquareTag( pTag );
      drawRectifyCrossTag(pTag);
      break;

   case pixq_FringeTag::CorrMatchTypeCorrLow:
   case pixq_FringeTag::CorrMatchTypeCorrHigh:
   case pixq_FringeTag::CorrMatchTypeOutlier:
      drawRectifyCrossTag(pTag);
      break;

   default:
      goto PIX_EXIT;
      break;
   }

   // --- Done ---
PIX_EXIT:
   return;
}

//
// draw tags position
//
void rectify_pane::drawRectifySquareTag(pixq_FringeTag *pTag)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   const pixq_ScreenPara *pScreen = pMain->getScreenPara();
   const pixq_PanePara *pFlip = NULL;

   int k, nPoints, iTagX, iTagY;
   int iSquareX[2], iSquareY[2];
   int iSquareScreenX[4], iSquareScreenY[4];
   float fTagColor[3];

   int iTagRadius = 10;
   bool bSelected = pTag->getSelected();

   unsigned short usStatus = (unsigned short)pTag->getCorrStatus();

   pFlip = pScreen->getLeftFlip();

   // *** draw tag position ***

   switch (_sPaneType) {
   case RectifyPaneSplitLeft:
      iTagX = pTag->getXTag();
      iTagY = pTag->getYTag();
      break;

   case RectifyPaneSplitRight:
      iTagX = pTag->getRightXTag();
      iTagY = pTag->getRightYTag();
      break;
   }

   iSquareX[0] = iTagX - iTagRadius;
   iSquareX[1] = iTagX + iTagRadius;
   iSquareY[0] = iTagY - iTagRadius;
   iSquareY[1] = iTagY + iTagRadius;

   // triangle
   nPoints = 5;
   pFlip->texToScreenCoo(iSquareX[0], iSquareY[0], &iSquareScreenX[0], &iSquareScreenY[0]);
   pFlip->texToScreenCoo(iSquareX[1], iSquareY[0], &iSquareScreenX[1], &iSquareScreenY[1]);
   pFlip->texToScreenCoo(iSquareX[1], iSquareY[1], &iSquareScreenX[2], &iSquareScreenY[2]);
   pFlip->texToScreenCoo(iSquareX[0], iSquareY[1], &iSquareScreenX[3], &iSquareScreenY[3]);
   pFlip->texToScreenCoo(iSquareX[0], iSquareY[0], &iSquareScreenX[4], &iSquareScreenY[4]);

   // 

   pMain->getStatusColor(usStatus, fTagColor);

   if (bSelected) {
      fTagColor[0] = 1.0f;
      fTagColor[1] = 0.0f;
      fTagColor[2] = 1.0f;
   }

   // draw square/triangle at the tag position

   glDisable(GL_TEXTURE_RECTANGLE_ARB);
   if (bSelected) {
      glLineWidth(_fSelectedTagWidth);
   }
   else {
      glLineWidth(_fTagWidth);
   }
   glColor3fv(fTagColor);

   glBegin(GL_LINE_STRIP);
   for (k = 0; k < nPoints; k++) {
      glVertex3i(iSquareScreenX[k], iSquareScreenY[k], 1);
   }
   glEnd();

   // --- Done ---
//PIX_EXIT:
   return;
}

//
// draw tags position
// currently being measured, no alaysis yet
//
void rectify_pane::drawRectifyCrossTag(pixq_FringeTag *pTag)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   const pixq_ScreenPara *pScreen = pMain->getScreenPara();
   const pixq_PanePara *pFlip = NULL;
   pixq_Properties *pEnv = pMain->getRectifyEnv();
   QColor colValue;

   int iBoxX[2], iBoxY[2], iTagRadius, iTagX, iTagY, iCrossScreenX[4], iCrossScreenY[4];
   int iCrossX[2], iCrossY[2], iBoxScreenX[4], iBoxScreenY[4];
   float fTagColor[3];

   unsigned short usStatus = (unsigned short)pTag->getCorrStatus();
   bool bSelected = pTag->getSelected();
   bool bUsed = pTag->getUsed();

   pFlip = pScreen->getLeftFlip();

   // *** draw tag position ***

   iTagRadius = pEnv->_MatchGridSymbolRadius.getInteger();

#ifdef DRAW_MANUAL_IMAGE
   iTagRadius = 75;
#endif // DRAW_MANUAL_IMAGE

   switch (_sPaneType) {
   case RectifyPaneSplitLeft:
      iTagX = pTag->getXTag();
      iTagY = pTag->getYTag();
      break;

   case RectifyPaneSplitRight:
      iTagX = pTag->getRightXTag();
      iTagY = pTag->getRightYTag();
      break;
   }

   iCrossX[0] = iTagX - iTagRadius;
   iCrossX[1] = iTagX + iTagRadius;
   iCrossY[0] = iTagY - iTagRadius;
   iCrossY[1] = iTagY + iTagRadius;

   if (bSelected) {
      iBoxX[0] = iTagX - iTagRadius * 2;
      iBoxX[1] = iTagX + iTagRadius * 2;
      iBoxY[0] = iTagY - iTagRadius * 2;
      iBoxY[1] = iTagY + iTagRadius * 2;
   }

   pFlip->texToScreenCoo(iCrossX[0], iTagY, &iCrossScreenX[0], &iCrossScreenY[0]);
   pFlip->texToScreenCoo(iCrossX[1], iTagY, &iCrossScreenX[1], &iCrossScreenY[1]);
   pFlip->texToScreenCoo(iTagX, iCrossY[0], &iCrossScreenX[2], &iCrossScreenY[2]);
   pFlip->texToScreenCoo(iTagX, iCrossY[1], &iCrossScreenX[3], &iCrossScreenY[3]);

   if (bSelected) {
      pFlip->texToScreenCoo(iBoxX[0], iBoxY[0], &iBoxScreenX[0], &iBoxScreenY[0]);
      pFlip->texToScreenCoo(iBoxX[1], iBoxY[0], &iBoxScreenX[1], &iBoxScreenY[1]);
      pFlip->texToScreenCoo(iBoxX[1], iBoxY[1], &iBoxScreenX[2], &iBoxScreenY[2]);
      pFlip->texToScreenCoo(iBoxX[0], iBoxY[1], &iBoxScreenX[3], &iBoxScreenY[3]);
   }

   //pMain->getStatusColor( usStatus, fTagColor );
   pMain->getStatusColor(bUsed, usStatus, fTagColor);

   // draw square/triangle at the tag position

   glDisable(GL_TEXTURE_RECTANGLE_ARB);

   glLineWidth(_fTagWidth);

#ifdef DRAW_MANUAL_IMAGE
   glLineWidth(5.0);
#endif // DRAW_MANUAL_IMAGE

   glColor3fv(fTagColor);

   glBegin(GL_LINES);
      glVertex3i(iCrossScreenX[0], iCrossScreenY[0], 1);
      glVertex3i(iCrossScreenX[1], iCrossScreenY[1], 1);
      glVertex3i(iCrossScreenX[2], iCrossScreenY[2], 1);
      glVertex3i(iCrossScreenX[3], iCrossScreenY[3], 1);
      glVertex3i(iCrossScreenX[0], iCrossScreenY[0], 1);
   glEnd();

   // draw square around the selected tag!

   if (bSelected) {
      glLineWidth(_fSelectedTagWidth);
      pMain->getSelectedColor(fTagColor);
      glColor3fv(fTagColor);

      glBegin(GL_LINE_STRIP);
         glVertex3i(iBoxScreenX[0], iBoxScreenY[0], 1);
         glVertex3i(iBoxScreenX[1], iBoxScreenY[1], 1);
         glVertex3i(iBoxScreenX[2], iBoxScreenY[2], 1);
         glVertex3i(iBoxScreenX[3], iBoxScreenY[3], 1);
         glVertex3i(iBoxScreenX[0], iBoxScreenY[0], 1);
      glEnd();
   }

   // --- Done ---
   return;
}

//
// draw epipolar (horizontal) line
//
void rectify_pane::drawEpipolarChecker(void)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   const pixq_ScreenPara *pScreen = pMain->getScreenPara();

   const pixq_PanePara *pFlip = NULL;
   double dScreenWiperY, dOrthoX[2], dOrthoY[2];
   double dSkima = 0.0;
   bool bDraw = pMain->getHorizontalMarker();
   int iMouseY = pMain->getLastMousePos();

   if (!bDraw) {
      goto PIX_EXIT;
   }

   switch (_sPaneType) {
   case RectifyPaneSplitLeft:
   case RectifyPaneSplitRight:
      break;

   default:
      goto PIX_EXIT;
   }

   pFlip = pScreen->getLeftFlip();

   // *** wiper poosition in viewport/texture ***

   pFlip->viewportToScreenY(iMouseY, &dScreenWiperY);

   // *** draw source area on index ***

   glDrawBuffer(GL_BACK);

   glDisable(GL_TEXTURE_RECTANGLE_ARB);

   glLineWidth(_fMinLineWidth);

#ifdef DRAW_MANUAL_IMAGE
   glLineWidth(6.0);   
#endif // DRAW_MANUAL_IMAGE

   glColor3f(1.0f, 1.0f, 0.0f);

   dOrthoX[0] = pFlip->GetOrthoX(0) + dSkima;
   dOrthoX[1] = pFlip->GetOrthoX(1) - dSkima;
   dOrthoY[0] = pFlip->GetOrthoY(0);
   dOrthoY[1] = pFlip->GetOrthoY(1);

   glBegin(GL_LINES);
   glVertex3d(dOrthoX[0], dScreenWiperY, 0.1);
   glVertex3d(dOrthoX[1], dScreenWiperY, 0.1);
   glEnd();

   // --- done ---
PIX_EXIT:
   return;
}