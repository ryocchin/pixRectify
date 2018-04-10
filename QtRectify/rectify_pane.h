#pragma once

#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

class rectify_window;

class rectify_pane : public QGLWidget
{
   Q_OBJECT
  
public:
   enum {
      RectifyPaneUnknown = 0,
      // image pane to show left image
      RectifyPaneSplitLeft=1,
      // image pane to show right image
      RectifyPaneSplitRight=2,
      // image pane to show index image
      RectifyPaneIndex=3,
   } RectifyPaneType;

   // image display mode for the second(right) pane
   enum {
      // no image loaded   
      RectifyPaneShowNone = 0,
      //
      // input image 
      RectifyPaneShowInput,
      // derived image 
      RectifyPaneShowDerived,
   } RectifyPaneShowImage;

public:
   rectify_pane(QWidget *parent = 0);
   ~rectify_pane();

protected:   
   void showEvent( QShowEvent *eve );

private:
   // required resourced initialized
   bool _bPaneInitialized;

   // what kind of pane is this? one of RectifyPaneType
   short _sPaneType;

   // pointer to the main window
   rectify_window *_pMainWindow;
         
   QPoint _MousePoint;
   	      
   // true if mouse is dragging
   bool _bMouseDragging;
     
   // what to show, original or derived
   // one of RectifyPaneShowImage
   short _sPaneShowImage;

   // --- OpenGL texture for image ---

   pixq_PaneTexture _PaneTexture;

   // line width to draw line
   bool _bLineWidthSet;
   float _fMinLineWidth;
   float _fMaxLineWidth;
   float _fTagWidth;
   float _fSelectedTagWidth;

public:
   // what to show on the pane, original or derived
   short getPaneShowImage(void) const { return _sPaneShowImage; }
   void setPaneShowImage(short sMode)  { _sPaneShowImage = sMode; };

   // draw chapters
   void refreshClear( void ) ;
   
   // --- OpenGL finctions ---

   void refreshTexture( void );

   void Init( short sSide );
   void DeInit( void );
   void refreshSingle( void );
   void drawIndexArea(void);

   void setModeCursor( void );

   void ResetPane( void );
   
   void setCurrentViewport(void);
   void ChangeScreenSize(void);

   void setMainWindow(rectify_window *pMain) { _pMainWindow = pMain; }
   rectify_window *getMainWindow(void) const { return _pMainWindow; }
            
   void initTexture(void);

   unsigned int getColorModeTexture(void);
   unsigned int getColorModeTexture(int iImage);
   
   bool initializeOpenGL(void);
   
   bool createPaneTexture( pixq_Matrix<unsigned short> *usRed, 
                           pixq_Matrix<unsigned short> *usGrn, 
                           pixq_Matrix<unsigned short> *usBlu, int iImage );

   //
   // draw fringing tags position
   //
   void drawRectifyTags(void);
   void drawRectifyTag(pixq_FringeTag *pTag);

   void drawEpipolarChecker(void);

   void drawRectifySelectedTag(pixq_FringeTag *pTag);

   void drawRectifySquareTag(pixq_FringeTag *pTag);
   void drawRectifyCrossTag(pixq_FringeTag *pTag);


protected:
   void closeEvent(QCloseEvent *eve);

   void initializeGL( void );
   void paintGL( void );
   
   void paintEvent( QPaintEvent *eve );
   void keyPressEvent( QKeyEvent *eve );
   void mousePressEvent( QMouseEvent *eve );
   void mouseReleaseEvent( QMouseEvent *eve );
   void mouseMoveEvent( QMouseEvent *eve );
   void wheelEvent ( QWheelEvent *eve  ); 
   void resizeEvent( QResizeEvent* );
   
};
