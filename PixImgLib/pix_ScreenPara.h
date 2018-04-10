#pragma once

//
// set of filpping parameters synchronized on the same programs
//

//
// screen geometric parameter for imaging allplication
// there is one pane (wiper or single image, scope mode) or 
// two panes(vertical or horizonral split)
// 
// on horizontal /vertical split viewing, two images are shown on
// eaxh pane
// 
// +---------------+  +---------------+  +-------++-------+
// |               |  |               |  |       ||       |
// |               |  |               |  |       ||       |
// |               |  +---------------+  |       ||       |
// |               |  +---------------+  |       ||       |
// |               |  |               |  |       ||       |
// |               |  |               |  |       ||       |
// +---------------+  +---------------+  +-------++-------+
//

namespace _pix_plot_img_framework {

class pixq_PanePara;

class PIXIMGLIB_EXPORT pixq_ScreenPara 
{
public:
   // image display mode for the second(right) pane
   enum {
      // no image loaded   
      PixPaneShowNone = 0,
      //
      PixPaneShowFirst = 11,
      PixPaneShowSecond,
      //
      // wiper style view
      PixPaneShowWiper,
      //
      // box-style view, input image inside
      PixPaneShowInBox,
      // box-style view, output image inside
      PixPaneShowOutBox,
      //
      PixPaneShowHorizontalSplit,
      PixPaneShowVerticalSplit,
   } PixPaneShowMode;

public:
   pixq_ScreenPara(void);
   ~pixq_ScreenPara(void);

private:
   // lock it when you don't want resizeevent to alter it
   bool _bLocked;

   // indicate how the geometry is set up
   // must be one of PixPaneShowMode
   // until it is implicitly set up, it is PixPaneShowNone
   short _sScreenInit;

   // whole pane as single flip area
   pixq_PanePara *_pSingleFlip;

   // horizontal split area
   pixq_PanePara *_pLeftFlip;
   pixq_PanePara *_pRightFlip;
   
   // vetcial split area
   pixq_PanePara *_pLowerFlip;
   pixq_PanePara *_pUpperFlip;
   
   // movement icrement
   double _dCenterStep;
   double _dZViewStep;

   // size of the image copied to the texture atwhen it was initialized
   double _dImageWidth;
   double _dImageHeight;

   // size of the whole screen to display single/double images
   //int _nScreenHeight;
   //int _nScreenWidth;

   // --- position of the client area (screen=ortho) to draw pictures ---
   // --- left and right position in pixels ---
   // *** must only be set in setFlipRatio ***
   //double _dOrthoX[2];

   // --- position of the client area (screen=ortho) to draw pictures ---
   // --- top and bottom position in pixels ---
   // *** must exclusively be set in setFlipRatio ***
   //double _dOrthoY[2];  

public:
   pixq_PanePara *getSingleFlip( void ) const { return _pSingleFlip; } 
   pixq_PanePara *getLeftFlip(void) const { return _pLeftFlip; }
   pixq_PanePara *getRightFlip(void) const { return _pRightFlip; }
   pixq_PanePara *getUpperFlip(void) const { return _pUpperFlip; }
   pixq_PanePara *getLowerFlip(void) const { return _pLowerFlip; }

   //int GetScreenHeight( void ) const { return _nScreenHeight; }
   //int GetScreenWidth( void ) const { return _nScreenWidth; }

   // size of the image copied to the texture atwhen it was initialized
   double getImageWidth(void) const { return _dImageWidth; }
   double getImageHeight(void) const { return _dImageHeight; }

   double GetCenterStep( void ) const { return _dCenterStep; }
   double GetZViewStep( void ) const { return _dZViewStep; }

   bool valid(void) const;
   void DeInit( void );

   void JumpToPoint(int iX, int iY);
   void JumpToPoint(double dX, double dY);

   //double GetOrthoX( int iSide ) const { return _dOrthoX[iSide]; }
   //double GetOrthoY( int iSide ) const { return _dOrthoY[iSide]; }

   // display the whole extent of the image to the source area
   void flipRecenter(void);

   void SwitchAreaType( short sAreaType, QSize rect );
   
   void viewOneToOne( void );
   void XYViewShift( int iXShift, int iYShift );
   void XYViewStep( int iXShift, int iYShift );
   void zViewShift(int iZShift);

   // full screen - double view port
   void setSingleViewports(void);
   
   void InitFlip( int nImgWidth, int nImgHeight );

   void setFlipRatio(QSize rect);
   void setFlipRatio(short sAreaType, QSize rect);
   void setFlipRatio(short sAreaType, int nScreenWidth, int nScreenHeight);
   
   bool getWholeExtent(void) const;
   
   void resizeWindow(QSize rect);
   void SetSingleConversion( void );  

   void Lock( void ) { _bLocked = true; }
   void Unlock( void ) { _bLocked = false; }
   bool IsLocked( void ) const { return _bLocked; }
};

} // namespace _pix_plot_img_framework 
