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
// display single(first or second texture) on the pane
//
static void refreshTexture_Rectify(unsigned int uiImgTexture,
   const pixq_FlipPara *pFlip)
{
   int nScreenWidth, nScreenHeight;
   double dOrthoX[2], dOrthoY[2], dTexCooX[2], dTexCooY[2];
   double dScreenPosX[2], dScreenPosY[2];

   dOrthoX[0] = pFlip->GetOrthoX(0);
   dOrthoX[1] = pFlip->GetOrthoX(1);
   dOrthoY[0] = pFlip->GetOrthoY(0);
   dOrthoY[1] = pFlip->GetOrthoY(1);

   dTexCooX[0] = pFlip->GetTexCooX(0);
   dTexCooX[1] = pFlip->GetTexCooX(1);
   dTexCooY[0] = pFlip->GetTexCooY(0);
   dTexCooY[1] = pFlip->GetTexCooY(1);

   dScreenPosX[0] = pFlip->GetScreenPosX(0);
   dScreenPosX[1] = pFlip->GetScreenPosX(1);
   dScreenPosY[0] = pFlip->GetScreenPosY(0);
   dScreenPosY[1] = pFlip->GetScreenPosY(1);

   nScreenWidth = pFlip->GetScreenWidth();
   nScreenHeight = pFlip->GetScreenHeight();
   glViewport(0, 0, nScreenWidth, nScreenHeight);

   //glFlush( );
   glDrawBuffer(GL_BACK);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // non-black bkgr, less ghosting
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(dOrthoX[0], dOrthoX[1], dOrthoY[0], dOrthoY[1], -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // --- get dimension ---

   glDisable(GL_DEPTH_TEST);
   glDisable(GL_DEPTH);
   glEnable(GL_TEXTURE_RECTANGLE_ARB);

   glBindTexture(GL_TEXTURE_RECTANGLE_ARB, uiImgTexture);

   //glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

   glBegin(GL_QUADS);
      glTexCoord2d(dTexCooX[0], dTexCooY[1]);
      glVertex3d(dScreenPosX[0], dScreenPosY[1], 0);

      glTexCoord2d(dTexCooX[0], dTexCooY[0]);
      glVertex3d(dScreenPosX[0], dScreenPosY[0], 0);

      glTexCoord2d(dTexCooX[1], dTexCooY[0]);
      glVertex3d(dScreenPosX[1], dScreenPosY[0], 0);

      glTexCoord2d(dTexCooX[1], dTexCooY[1]);
      glVertex3d(dScreenPosX[1], dScreenPosY[1], 0);
   glEnd();

   return;
}

static void refreshTexture_Rectify(unsigned int uiImgTexture,
   short sPaneType,
   const pixq_ScreenPara *pScreen)
{
   int nScreenWidth, nScreenHeight;
   double dOrthoX[2], dOrthoY[2], dTexCooX[2], dTexCooY[2];
   double dScreenPosX[2], dScreenPosY[2];

   pixq_PanePara *pFlip = (pixq_PanePara*)NULL;

   switch (sPaneType) {
   case rectify_pane::RectifyPaneSplitLeft:
      pFlip = pScreen->getLeftFlip();
      break;
   case rectify_pane::RectifyPaneSplitRight:
      pFlip = pScreen->getRightFlip();
      break;
   default:
      goto PIX_EXIT;
      break;
   }

   dOrthoX[0] = pFlip->GetOrthoX(0);
   dOrthoX[1] = pFlip->GetOrthoX(1);
   dOrthoY[0] = pFlip->GetOrthoY(0);
   dOrthoY[1] = pFlip->GetOrthoY(1);

   dTexCooX[0] = pFlip->GetTexCooX(0);
   dTexCooX[1] = pFlip->GetTexCooX(1);
   dTexCooY[0] = pFlip->GetTexCooY(0);
   dTexCooY[1] = pFlip->GetTexCooY(1);

   dScreenPosX[0] = pFlip->GetScreenPosX(0);
   dScreenPosX[1] = pFlip->GetScreenPosX(1);
   dScreenPosY[0] = pFlip->GetScreenPosY(0);
   dScreenPosY[1] = pFlip->GetScreenPosY(1);

   nScreenWidth = pFlip->GetScreenWidth();
   nScreenHeight = pFlip->GetScreenHeight();
   glViewport(0, 0, nScreenWidth, nScreenHeight);

   //glFlush( );
   glDrawBuffer(GL_BACK);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // non-black bkgr, less ghosting
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(dOrthoX[0], dOrthoX[1], dOrthoY[0], dOrthoY[1], -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // --- get dimension ---

   glDisable(GL_DEPTH_TEST);
   glDisable(GL_DEPTH);
   glEnable(GL_TEXTURE_RECTANGLE_ARB);

   glBindTexture(GL_TEXTURE_RECTANGLE_ARB, uiImgTexture);

   //glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

   glBegin(GL_QUADS);
      glTexCoord2d(dTexCooX[0], dTexCooY[1]);
      glVertex3d(dScreenPosX[0], dScreenPosY[1], 0);

      glTexCoord2d(dTexCooX[0], dTexCooY[0]);
      glVertex3d(dScreenPosX[0], dScreenPosY[0], 0);

      glTexCoord2d(dTexCooX[1], dTexCooY[0]);
      glVertex3d(dScreenPosX[1], dScreenPosY[0], 0);

      glTexCoord2d(dTexCooX[1], dTexCooY[1]);
      glVertex3d(dScreenPosX[1], dScreenPosY[1], 0);
   glEnd();

PIX_EXIT:
   return;
}

bool rectify_pane::initializeOpenGL(void)
{  
   bool bRetCode = false; 
   int nWidth, nHeight;
   QSize rect;

   // --- get dimension ---
   
   rect = size( );
   nWidth = (int)rect.width( );
   nHeight = (int)rect.height( ); 		
				
	// *** DO NOT Enable GL_DEPTH here as it causes ***
   // unknown error while intializing the OpenGL extension ***

   //glEnable( GL_DEPTH );
	glEnable( GL_TEXTURE_RECTANGLE_ARB );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glViewport( 0, 0, nWidth, nHeight );		
												
	glMatrixMode( GL_PROJECTION );		
	glLoadIdentity( );				

	glMatrixMode( GL_MODELVIEW );		
	glLoadIdentity( );
   
   glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); 
   glClear( GL_COLOR_BUFFER_BIT ); 
	glFlush( );

   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

void rectify_pane::refreshSingle(void)
{			   
   rectify_window *pMain = (rectify_window*)getMainWindow();
   
   if( !_bPaneInitialized ) {
      goto PIX_EXIT;
   }
   
   if (!pMain->validPaneDisplayMode()) {
      makeCurrent( );
      refreshClear();
      swapBuffers( );
      goto PIX_EXIT;
   }

   if (pMain->getImageLoading()) {
      //qDebug() << ">>> refreshSingle image is loading...";
      goto PIX_EXIT;
   }
   
   makeCurrent( );
   
   switch( _sPaneType ) {
   case RectifyPaneSplitLeft:
   case RectifyPaneSplitRight:
      refreshTexture( );
      break;

   case RectifyPaneIndex:
      //
      // index
      // draw the first image when images are loaded
      //
      refreshTexture( );
      break;

   default:
      goto PIX_EXIT;
      break;
   }

   // draw misc info over image
   
   switch (_sPaneType) {
   case RectifyPaneSplitLeft:
   case RectifyPaneSplitRight:
      drawRectifyTags();
      drawEpipolarChecker();
      break;

   case RectifyPaneIndex:
      break;
   }

   // draw other information

   switch( _sPaneType ) {
   case RectifyPaneSplitLeft:
   case RectifyPaneSplitRight:
      break;

   case RectifyPaneIndex:
      drawIndexArea( );   
      break;

   default:
      break;
   }
   
   swapBuffers( );

   // --- done ---
PIX_EXIT:
   return;
}


unsigned int rectify_pane::getColorModeTexture(void)
{
   unsigned int uiImgTexture;

   switch( _sPaneType ) {

   case RectifyPaneSplitLeft:
   case RectifyPaneSplitRight:
      switch (_sPaneShowImage) {
      case rectify_pane::RectifyPaneShowInput:
         uiImgTexture = getColorModeTexture(0);
         break;

      case rectify_pane::RectifyPaneShowDerived:
      default:
         uiImgTexture = getColorModeTexture(1);
         break;
      }
      break;
      
   case RectifyPaneIndex:
      uiImgTexture = getColorModeTexture(0);
      goto PIX_EXIT;
      break;

   default:
      break;
   }

PIX_EXIT:
   return uiImgTexture;
}

//
// get the textue id according to the display color mode
//
unsigned int rectify_pane::getColorModeTexture(int iImage) // [i] source or derived image
{
   unsigned int uiTexture = _PaneTexture.getRgbTexture( iImage );

   return uiTexture;
}

//
// draw the currently show area on the index image
//
void rectify_pane::drawIndexArea(void)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   const pixq_ScreenPara *pScreen = pMain->getScreenPara();
   const pixq_FlipPara *pFlip = pMain->getIndexPara();

   const pixq_PanePara *pIndexFlip = NULL;

   if( !_bPaneInitialized ) {
      goto PIX_EXIT;
   }

   //
   // need to fix this for vertical/horizontal split!
   //
      
   double dScreenX0, dScreenX1, dScreenY0, dScreenY1;
   double dTexX0, dTexX1, dTexY0, dTexY1;

   pIndexFlip = pScreen->getLeftFlip();

   // *** draw source area on index ***
   
   glDisable( GL_TEXTURE_RECTANGLE_ARB );
   glDisable( GL_LIGHTING ); // to show lines in color
   glDisable( GL_LIGHT0 );
   glEnable( GL_DEPTH_TEST );

   glLineWidth( _fMinLineWidth );  
   glColor3f( 1.0f, 1.0f, 0.0f );

   dTexX0 = pIndexFlip->GetTexCooX( 0 );
   dTexX1 = pIndexFlip->GetTexCooX( 1 );
   dTexY0 = pIndexFlip->GetTexCooY( 0 );
   dTexY1 = pIndexFlip->GetTexCooY( 1 );
 
   pFlip->texToScreenCoo(dTexX0, dTexY0, &dScreenX0, &dScreenY0);
   pFlip->texToScreenCoo(dTexX1, dTexY1, &dScreenX1, &dScreenY1);
   glBegin( GL_LINE_STRIP );
      glVertex3d( dScreenX0, dScreenY0, 0.1 );
      glVertex3d( dScreenX1, dScreenY0, 0.1 );
      glVertex3d( dScreenX1, dScreenY1, 0.1 );
      glVertex3d( dScreenX0, dScreenY1, 0.1 );
      glVertex3d( dScreenX0, dScreenY0, 0.1 );
   glEnd( );    
  
   // --- done ---
PIX_EXIT:
   return;
}

//
// display single(first or second texture) on the pane
//
void rectify_pane::refreshTexture(void)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   const pixq_ScreenPara *pScreen = pMain->getScreenPara();
   const pixq_FlipPara *pIndexFlip = pMain->getIndexPara();

	unsigned int uiImgTexture; 
   
   if( !_bPaneInitialized ) {
      goto PIX_EXIT;
   }

   if (!pMain->validPaneDisplayMode()) {
      goto PIX_EXIT;
   }
   
   uiImgTexture = getColorModeTexture();
   switch( _sPaneType ) {
   case RectifyPaneSplitLeft:
   case RectifyPaneSplitRight:
      refreshTexture_Rectify(uiImgTexture, _sPaneType, pScreen);
      break;

   case RectifyPaneIndex:
      refreshTexture_Rectify(uiImgTexture, pIndexFlip);
      break;

   default:
      break;
   }
   
   // --- DONE ---
PIX_EXIT:
   return;
}


void rectify_pane::refreshClear(void)
{
   float fLineRange[2];
   float fRedValue, fGrnValue, fBluValue;
   
   if( !_bPaneInitialized ) {
      goto PIX_EXIT;
   }

   glDisable( GL_CULL_FACE );
   glDisable( GL_LIGHTING );
   glDisable( GL_LIGHT0 );

   glDisable( GL_DEPTH_TEST ); 
   glDisable( GL_DEPTH );
   glDisable( GL_TEXTURE_RECTANGLE_ARB );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity( );

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity( );

   // clear the screen

   switch (_sPaneType) {
   case RectifyPaneSplitLeft:
      fRedValue = 0.380f;
      fGrnValue = 0.380f;
      fBluValue = 0.380f;
      glColor4f(fRedValue, fGrnValue, fBluValue, 1.0f);
      glClearColor(fRedValue, fGrnValue, fBluValue, 1.0f);
      break;

   case RectifyPaneSplitRight:
      fRedValue = 0.380f;
      fGrnValue = 0.380f;
      fBluValue = 0.380f;
      glColor4f(fRedValue, fGrnValue, fBluValue, 1.0f);
      glClearColor(fRedValue, fGrnValue, fBluValue, 1.0f);
      break;

   case RectifyPaneIndex:
      fRedValue = 0.280f;
      fGrnValue = 0.280f;
      fBluValue = 0.280f;
      glColor4f(fRedValue, fGrnValue, fBluValue, 1.0f);
      glClearColor(fRedValue, fGrnValue, fBluValue, 1.0f);
      break;
      
   default:
      fRedValue = 0.80f;
      fGrnValue = 0.80f;
      fBluValue = 0.80f;
      glColor4f( fRedValue, fGrnValue, fBluValue, 1.0f );
      glClearColor( fRedValue, fGrnValue, fBluValue, 1.0f );
      break;
   }
   	
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glFlush( ); 
   
   // set line symbl size
   // this must be done after the pane is initalized

   if (!_bLineWidthSet) {
      glGetFloatv(GL_LINE_WIDTH_RANGE, fLineRange);
      _fMinLineWidth = fLineRange[0];
      _fMaxLineWidth = fLineRange[1];
      _fTagWidth = max(2.0f, fLineRange[0]);
      _fSelectedTagWidth = min(4.0f, _fMaxLineWidth);
      _bLineWidthSet = true;
   }

PIX_EXIT:
   return;
}

 