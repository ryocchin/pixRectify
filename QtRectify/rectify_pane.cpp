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

rectify_pane::rectify_pane(QWidget *parent)
    : QGLWidget(parent)
{
   _bPaneInitialized = false;
   _bLineWidthSet = false;

   _sPaneType = RectifyPaneUnknown;
   _pMainWindow = (rectify_window*)NULL;

   _bMouseDragging = false;
   _PaneTexture.Init( );

   _sPaneShowImage = RectifyPaneShowNone;

   return;
}

rectify_pane::~rectify_pane()
{
   return;
}

void rectify_pane::showEvent(QShowEvent * /*eve*/)
{
   updateGL( );

   return;
}

void rectify_pane::initializeGL(void)
{
   glEnable( GL_LIGHTING );
   glEnable( GL_LIGHT0 );
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_NORMALIZE );

   glClearColor( 0.0f, 0.0f, 0.0f, 1.0f ); 

   return;
}

void rectify_pane::paintGL(void)
{
   update( );

   return;
}

void rectify_pane::paintEvent(QPaintEvent * /* event */)
{
   if( !_bPaneInitialized ) {
      goto PIX_EXIT;
   }
   
   refreshSingle( );

PIX_EXIT:
   return;
}

void rectify_pane::resizeEvent(QResizeEvent * /*eve*/)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();

   if (!pMain->validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   // set viewport

   ChangeScreenSize( );

PIX_EXIT:
   return;
}

void rectify_pane::keyPressEvent(QKeyEvent *eve)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   
   if (!pMain->validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   int iKey = eve->key( );

   if (pMain->processKeyEvent(_sPaneType, iKey)) {
      goto PIX_EXIT;
   }

   QGLWidget::keyPressEvent( eve );

PIX_EXIT:
   return;
}

void rectify_pane::wheelEvent(QWheelEvent *eve)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   int iDelta;

   if (!pMain->validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   switch( _sPaneType ) {
   case RectifyPaneSplitLeft:
   case RectifyPaneSplitRight:
      break;

   case RectifyPaneIndex:
      goto PIX_EXIT;
      break;
   }

   iDelta = eve->delta( );
   if (pMain->processWheelEvent(_sPaneType, iDelta)) {
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

//
// mouse button pressed
//
void rectify_pane::mousePressEvent(QMouseEvent *eve)
{
	rectify_window *pMain = (rectify_window*)getMainWindow();
	short sLeftMouseMode = pMain->getLeftMouseMode();
   bool bRunnningThread = pMain->isThreadRunning();

   QSize rect = size();
   int iMouseX = eve->x();
   int iMouseY = rect.height() - eve->y();

   if (!pMain->validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   if (bRunnningThread) {
      goto PIX_EXIT;
   }

   switch( eve->button( ) ) {
   //
   // Left Click
   //
   case Qt::LeftButton:   
		switch (_sPaneType) {
	   case RectifyPaneSplitLeft:
		   // 
         // left pane
         //
		   switch (sLeftMouseMode) {
		   case rectify_window::MouseLeftClickNone:
            //
            // switch between input and output 
            //
            pMain->switchPaneImage();
			   update();
			   break;

		   case rectify_window::MouseLeftClickNoneHitAndMatch:
            //
            // hit on left image and do the matching
            //
			   pMain->rectifyHitAndMatch( iMouseX, iMouseY);
			   break;
			   
         default:
            //
            // switch in / output image
            //
            pMain->switchPaneImage();
			   update();
			   break;
		   }
		   break;

	   case RectifyPaneSplitRight:
         //
		   // switch between input and output 
         //
         pMain->switchPaneImage();
         update();
         break;

      case RectifyPaneIndex:
         update( );
         break;
      }
      break;

   //
   // Right Click
   //
   case Qt::RightButton:      
      _bMouseDragging = true;
      _MousePoint = eve->pos();
      update( );
      break;
   }

   //QGLWidget::mousePressEvent( eve );

PIX_EXIT:
   return;
}

//
// mouse button released
//
void rectify_pane::mouseReleaseEvent(QMouseEvent *eve)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();

   if (!pMain->validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   // right button

   if( Qt::RightButton == eve->button( ) ) {
      _bMouseDragging = false;
      goto PIX_EXIT;
   }

   //QGLWidget::mouseReleaseEvent( eve );

PIX_EXIT:
   return;
}

void rectify_pane::mouseMoveEvent(QMouseEvent *eve)
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   QSize rect = size();
   bool bEpipolarDraw = pMain->getHorizontalMarker();

   int iMouseX = eve->x();
   int iMouseY = rect.height( ) - eve->y();

   if (!pMain->validPaneDisplayMode()) {
      QGLWidget::mouseMoveEvent( eve );
      goto PIX_EXIT;
   }

   // right button pressed down
   // --- drag the image ---

   if( Qt::RightButton == eve->button( ) ) {
      // right mouse button is being pressed
       setCursor( Qt::DragMoveCursor );
      // setCursor( Qt::MoveCursor );
      _bMouseDragging = true;
   }
   
   // --- display coordinate ---

   pMain->getColor(_sPaneType, iMouseX, iMouseY);
   
   // --- drag the image ---

   if( _bMouseDragging ) {
      int iX = eve->x() - _MousePoint.x( );
      int iY = eve->y() - _MousePoint.y( );
      pMain->processScrollEvent(_sPaneType, iX, iY);
   }
   
   _MousePoint.setX( eve->x() );
   _MousePoint.setY( eve->y() );

   // mouse position

   if (bEpipolarDraw) {
      pMain->setLastMousePos(iMouseY);
   }

   if (bEpipolarDraw) {
      pMain->refreshEpipolarLine();
   }

PIX_EXIT:
   return;
}

void rectify_pane::closeEvent(QCloseEvent * /*eve*/)
{
   DeInit( );
   
   return;
}
