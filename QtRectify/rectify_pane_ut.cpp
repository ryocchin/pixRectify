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

void rectify_pane::Init(short sSide)
{
   _sPaneType = sSide;

   setBackgroundRole( QPalette::Base );
   setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

   setMinimumSize( 50, 50 );

   setFocusPolicy( Qt::StrongFocus );
   setMouseTracking( true );

   _PaneTexture.Init( );

   _bMouseDragging = false;

   ResetPane( );

   //
   // pane parameters
   //

   initializeOpenGL();
   _bPaneInitialized = true;

   return;
}

void rectify_pane::DeInit(void)
{   
   ResetPane( );
}

void rectify_pane::ResetPane(void)
{   
   _PaneTexture.Delete( ); 

   // --- DOne ---
   return;
}

void rectify_pane::setCurrentViewport(void)
{
   QSize rect = size( );
   
   glClearColor( 0.0, 0.0, 0.0, 1.0 );
	//glViewport( rect.left, rect.top, rect.right, rect.bottom );
	glViewport( 0, 0, rect.width( ), rect.height( ) );

   return;
}

void rectify_pane::ChangeScreenSize(void)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   pixq_ScreenPara *pScreen = pMain->getScreenPara();
   pixq_FlipPara *pIndex = pMain->getIndexPara();
   QSize rect = size( );

   if (!pMain->validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   if( pScreen->IsLocked( ) ) { 
      goto PIX_EXIT;
   }

   // --- initialize texture copy parameters ---
   // --- initialize view point parameters ---   
  
   setCurrentViewport();
   
   // --- set current screen size ---

	switch( _sPaneType ) {
   case rectify_pane::RectifyPaneSplitLeft:
   case rectify_pane::RectifyPaneSplitRight:
      pScreen->resizeWindow(rect);
      break;

   case rectify_pane::RectifyPaneIndex:
      pIndex->resizeWindow(rect);
		break;

   case rectify_pane::RectifyPaneUnknown:
   default:
      goto PIX_EXIT;
      break;
   }

   update( );

PIX_EXIT:
   return;
}

//
// create opengl texture from rgb matrix
//
// notes:
// 
bool rectify_pane::createPaneTexture(pixq_Matrix<unsigned short> *usRed, // [i] image data in matrix
                                    pixq_Matrix<unsigned short> *usGrn, // [i] image data in matrix
                                    pixq_Matrix<unsigned short> *usBlu, // [i] image data in matrix
                                    int iImage ) // [i] 0 or 1
{
	bool bRetCode = false;
   rectify_window *pMain = (rectify_window*)getMainWindow();
   pixq_Properties *pEnv = pMain->getRectifyEnv();
   int iTexPara, iTexFilter;
   short sDisplayColor;
   unsigned int uiTexture;
   
#ifdef _DEBUG
unsigned short usMin[3], usMax[3], usMean[3];
#endif // _DEBUG

   // get the current mag filter

   iTexFilter = pEnv->_ImageTextureFilter.getInteger();
   if( pixq_Properties::TextureFilterNearest == iTexFilter ) {
      iTexPara = GL_NEAREST;
   } else {
      iTexPara = GL_LINEAR;
   }
      
   // bind the texture
   
   makeCurrent( ); 
   glEnable( GL_TEXTURE_RECTANGLE_ARB );

   uiTexture = getColorModeTexture( iImage );
   glBindTexture( GL_TEXTURE_RECTANGLE_ARB, uiTexture );      
   
   // !!! THIS HAS TO BE DONE AFTER glBindTexture !!!

	glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, iTexPara );
	glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, iTexPara );
	
   //glTexEnvi is deprecated
   //glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );

   // opengl 2.X -> create texture with any size!
   
   sDisplayColor = PixImageDisplayColorRgb;

#ifdef _DEBUG
usRed->Statistics( &usMin[0], &usMax[0], &usMean[0] );
usGrn->Statistics( &usMin[1], &usMax[1], &usMean[1] );
usBlu->Statistics( &usMin[2], &usMax[2], &usMean[2] );
#endif // _DEBUG

   if (!createFreeTexture_PI(usRed, usGrn, usBlu, sDisplayColor)) {
      _PaneTexture.SetRgbTexture(iImage, false);
      goto PIX_EXIT; 
   }
  
   // set the texture flag

   _PaneTexture.SetRgbTexture(iImage, true);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:   
   return bRetCode;
}


void rectify_pane::initTexture(void)
{  
   _PaneTexture.initTexture();
   
   return;
}

void rectify_pane::setModeCursor(void)
{
	rectify_window *pMain = (rectify_window*)getMainWindow();
	short sLeftMode = pMain->getLeftMouseMode();
	QCursor *pCursor = pMain->hitMatchCursor( );

   if( _bMouseDragging ) {
      setCursor( Qt::ClosedHandCursor );
      goto PIX_EXIT;
   }

   switch (sLeftMode) {
   case rectify_window::MouseLeftClickNone:
	   setCursor(Qt::ArrowCursor);
	   break;

   case rectify_window::MouseLeftClickNoneHitAndMatch:
	   setCursor(*pCursor);
	   break;

   default:
	   setCursor(Qt::ArrowCursor);
	   break;
   }

PIX_EXIT:
   return;
}

