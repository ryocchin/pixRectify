#pragma once

namespace _pix_plot_img_framework {

class pixq_ScreenPara;

//
// this pane's geometric pamrameters 
// should only be used as member of ITQF_Screen2Para
//
class PIXIMGLIB_EXPORT pixq_PanePara
{
public:
   // flip area type
   enum {
      FlipAreaNone, // *** not initialized
      FlipAreaSingle, // single area for the whole screen
      FlipAreaLeft, // left side area in the vertical split pane
      FlipAreaRight, // right side area in the vertical split pane
      FlipAreaUpper, // upper side area in the horizontal split pane
      FlipAreaLower, // lower side area in the horizontal split pane
   } FlipAreaType;

public:
   pixq_PanePara(void);
   pixq_PanePara( short sArea );
   ~pixq_PanePara(void);

private:
   // flip are type, one of FlipAreaType
   short _sFileArea;

   // left and right position of the area to display the image on the screen
   // *** must only be set in reshapeFlipSrcRect ***
   double _dScreenPosX[2];
   
   // top and bottom position of the area to display the image on the screen
   // *** must only be set in reshapeFlipSrcRect ***
   double _dScreenPosY[2];

   // --- area in image to display on screen ---
   // --- left and right position in pixels ---
   double _dSrcX[2];
   
   // --- area in image to display on screen ---
   // --- top and bottom position in pixels ---
   double _dSrcY[2];

   // area in the client area(screen) where adjusted image source is copied
   // --- left and right position in pixels ---
   // *** must only be set in reshapeFlipSrcRect ***
   double _dTexCooX[2];
   
   // area in the client area(screen) where adjusted image source is copied
   // --- top and bottom position in pixels ---
   // *** must only be set in reshapeFlipSrcRect ***
   double _dTexCooY[2];
   
   // *** viewport <--> texture geometric conversion parameter ***
   // *** must exclusively be set in SetSingleConversion ***

   int _nDoubleVPXCoo; // left x coo of viewing area
   int _nDoubleVPXEnd; // right x coo of viewing area
   int _nDoubleVPYCoo;
   int _nDoubleVPYEnd;

   // *** viewport -> screen(Ortho) coordinate conversion parameters ***
   // geometric conversion parameters between ortho coordinate 
   // and screen coordinates, single viewport
   // *** must exclusively be set in SetSingleConversion ***

   double _dVpXDet;
   double _dVpYDet;
   double _dVpXShift;
   double _dVpYShift;
   
   // *** texture -> screen(Ortho) coordinate conversion parameters ***
   
   double _dTexXDet;
   double _dTexYDet;
   double _dTexXShift;
   double _dTexYShift;
   
   // *** screen(Ortho) -> texture coordinate conversion parameters ***
   
   double _dVpXTexDet;
   double _dVpYTexDet;
   double _dVpXTexShift;
   double _dVpYTexShift;

   // this is set to true when texture - screen(pane) geometric 
   // conversion parameters are set

   bool _bTexDet;

   // currently whole image is shown
   bool _bWholeExtent;

   // parent screen parameter
   pixq_ScreenPara *_pParent;

   // --- position of the client area (screen=ortho) to draw pictures ---
   // --- left and right position in pixels ---
   // *** must only be set in setFlipRatio ***
   double _dOrthoX[2];

   // --- position of the client area (screen=ortho) to draw pictures ---
   // --- top and bottom position in pixels ---
   // *** must exclusively be set in setFlipRatio ***
   double _dOrthoY[2];  

   // size of the whole screen to display single/double images
   int _nScreenHeight;
   int _nScreenWidth;

public:
   // *** data ***
   bool getTexDet( void ) const { return _bTexDet; }

   bool getPaneInit( void ) const;
   double GetScreenPosX( int iSide ) const { return _dScreenPosX[iSide]; }
   double GetScreenPosY( int iSide ) const { return _dScreenPosY[iSide]; }

   bool getWholeExtent(void) const { return _bWholeExtent; }

   double GetTexCooX( int iSide ) const { return _dTexCooX[iSide]; }
   double GetTexCooY( int iSide ) const { return _dTexCooY[iSide]; }
   double GetSrcX( int iSide ) const { return _dSrcX[iSide]; }
   double GetSrcY( int iSide ) const { return _dSrcY[iSide]; }
      
   double GetOrthoX( int iSide ) const { return _dOrthoX[iSide]; }
   double GetOrthoY( int iSide ) const { return _dOrthoY[iSide]; }

   int GetScreenHeight( void ) const { return _nScreenHeight; }
   int GetScreenWidth( void ) const { return _nScreenWidth; }

   // *** geometric conversion between screen and texture coordinates ***
   
   bool viewportToPixelCoo( int iVpX, int iVpY, int *iPixX, int *iPixY ) const;
   bool viewportToPixelCoo(int iVpX, int iVpY, double *dPixX, double *dPixY) const;
   
   bool viewportToScreenCoo(int iVpX, int iVpY, int *iScreenX, int *iScreenY) const;
   bool viewportToScreenCoo(int iVpX, int iVpY, double *dScreenX, double *dScreenY) const;

   bool viewportToScreenX(int iVpX, double *dScreenX) const;
   bool viewportToScreenY(int iVpY, double *dScreenY) const;

   double texToScreenXCoo(double dTexX) const;
   double texToScreenYCoo(double dTexY) const;
   void texToScreenCoo(double dTexX, double dTexY, double *dScreenX, double *dScreenY) const;
   void texToScreenCoo(int iTexX, int iTexY, int *iScreenX, int *iScreenY) const;

public:
   void StoreParent( pixq_ScreenPara *pParent ) { _pParent = pParent; }

   void DeInit( void );
   void XYViewShift( int iXShift, int iYShift );
   void XYViewStep( int iXShift, int iYShift );
   void zViewShift(int iZShift);
   void CopySrc( double *dSrcX, double *dSrcY );
   void viewOneToOne(void);
   
   // display the whole extent of the image to the source area
   void flipRecenter(void);

   void JumpToPoint( int iX, int iY );
   void JumpToPoint( double dX, double dY );

   void ImageCornersCoordinate( double *dTexXCoo, double *dTexYCoo, double *dScreenXPos, double *dScreenYPos );

   void GetCenter( double *dX, double *dY );
   void GetCenter( int *iX, int *iY );

   double PaneToScreenX(int iPaneX);
   double PaneToScreenY(int iPaneY);

   // *** utility ***

   void ShowWholeImage( void );

   // _dOrthoX, _dOrthoX can only be set in here!
   void setFlipRatio(QSize rect);
   void setFlipRatio(int nScreenWidth, int nScreenHeight);

   // _dImageWidth, _dImageHeight can only be set in here!
   void InitFlip( void );

   // full screen - double view port
   void setSingleViewports(void);

   void reshapeFlipSrcRect(void);

   void resizeWindow(QSize rect);
   void SetSingleConversion( void );  
};

} // namespace _pix_plot_img_framework 
