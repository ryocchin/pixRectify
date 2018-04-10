#pragma once

namespace _pix_plot_img_framework {

#include <piximglib_global.h>

class PIXIMGLIB_EXPORT pixq_FlipPara
{
public:
   pixq_FlipPara(void);
   ~pixq_FlipPara(void);

private:
   bool _bFlipInit;

   double _dCenterStep;
   double _dZViewStep;

   int _nScreenHeight;
   int _nScreenWidth;

   // *** must only be set in reshapeFlipSrcRect ***
   double _dScreenPosX[2];
   double _dScreenPosY[2];

   // --- dimension of the texture, to adjust the image size to the ---
   // --- power of two, sometimes the texture is expanded from real image ---
   double _dTextureWidth;
   double _dTextureHeight;

   // size of the image copied to the texture atwhen it was initialized
   double _dImagWidth;
   double _dImagHeight;

   // area in image to be displayed ( pixels )
   double _dSrcX[2];
   double _dSrcY[2];

   // adjusted area in image to be displayed ( pixels )
   double _dAdjustedSrcX[2];
   double _dAdjustedSrcY[2];

   // area in the client area where adjusted image source is copied
   // *** must only be set in reshapeFlipSrcRect ***
   double _dTexCooX[2];
   double _dTexCooY[2];
   double _dTexXSize;
   double _dTexYSize;
   
   // client area 
   // *** muist only be set in setFlipRatio ***
   double _dOrthoX[2];
   double _dOrthoY[2];   
   double _dOrthoXSize;
   double _dOrthoYSize;

   // *** full screen - double view port ***
   // *** viewports location and size in projector mode ***
  
   int _nFrameEdge;

   int _nDoubleVPXCoo[2]; // left x coo of viewing area
   int _nDoubleVPXEnd[2]; // right x coo of viewing area
   int _nDoubleVPYCoo;
   int _nDoubleVPYEnd;
   int _nDoubleVPWidth;
   int _nDoubleVPHeight;

   // *** viewport -> Ortho coordinate conversion parameters ***
   
   double _dVpXDet[2];
   double _dVpYDet[2];
   double _dVpXShift[2];
   double _dVpYShift[2];
   
   bool _bVpConversionSet;

   // *** texture -> screen(Ortho) coordinate conversion parameters ***
   
   bool _bTexDet;
   
   double _dTexXDet;
   double _dTexYDet;
   double _dTexXShift;
   double _dTexYShift;
   
   // *** screen(Ortho) -> texture coordinate conversion parameters ***
 
   double _dVpXTexDet[2];
   double _dVpYTexDet[2];
   double _dVpXTexShift[2];
   double _dVpYTexShift[2];

   // currently whole image is shown
   bool _bWholeExtent;

public:
   void InitFlip( int nTexWidth, int nTexHeight, int nImgWidth, int nImgHeight );
   void InitFlip( int nImgWidth, int nImgHeight );
   void DeInit( void );

   void resizeWindow(QSize rect);
   void setFlipRatio(QSize rect);
   void setFlipRatio(int nScreenWidth, int nScreenHeight);

   void reshapeFlipSrcRect(void);

   void reshapeFlipImageRect(int nScreenWidth, int nScreenHeight);
   void reshapeFlipImageRect(QSize rect);

   // *** coordinate conversion ***
   void setSingleViewports(int nScreenWidth, int nScreenHeight);
   void setSingleViewports(QSize rect);

   void setDoubleViewports(int nScreenWidth, int nScreenHeight);

   void SetSingleConversion( void );
   void setDoubleConversion(void);
   void setVpTexConversion( void );

public:
   // move/scale
   void XYViewShift( int iXShift, int iYShift );
   void XYViewStep( int iXShift, int iYShift );
   void zViewShift(int iZShift);
   
   void JumpToPoint( int iX, int iY );
   void JumpToPoint( double dX, double dY );

   void viewOneToOne(void);
   void ViewOneToTwo( void );
   void ViewTwoToOne( void );

   // show the whole image extent
   void flipRecenter( void );

public:
   double ScreenTextureRatio( void ) const;

   void GetCenter( double *dX, double *dY ) const;
   void GetCenter( int *iX, int *iY ) const;

   bool getWholeExtent(void) const { return _bWholeExtent; }

   bool GetFlipInit( void ) const { return _bFlipInit; }
   double GetScreenPosX( int iSide ) const { return _dScreenPosX[iSide]; }
   double GetScreenPosY( int iSide ) const { return _dScreenPosY[iSide]; }

   // size of the image copied to the texture atwhen it was initialized
   double getImageWidth(void) const { return _dImagWidth; }
   double getImageHeight(void) const { return _dImagHeight; }

   double GetTexCooX( int iSide ) const { return _dTexCooX[iSide]; }
   double GetTexCooY( int iSide ) const { return _dTexCooY[iSide]; }
   double GetSrcX( int iSide ) const { return _dSrcX[iSide]; }
   double GetSrcY( int iSide ) const { return _dSrcY[iSide]; }
   double GetAdjustedSrcX( int iSide ) const { return _dAdjustedSrcX[iSide]; }
   double GetAdjustedSrcY( int iSide ) const { return _dAdjustedSrcY[iSide]; }

   double GetOrthoX( int iSide ) const { return _dOrthoX[iSide]; }
   double GetOrthoY( int iSide ) const { return _dOrthoY[iSide]; }
   double GetOrthoXSize( void ) const { return _dOrthoXSize; }
   double GetOrthoYSize( void ) const { return _dOrthoYSize; }
      
   double getTextureWidth(void) const { return _dTextureWidth; }
   double getTextureHeight(void) const { return _dTextureHeight; }

   int GetScreenHeight( void ) const { return _nScreenHeight; }
   int GetScreenWidth( void ) const { return _nScreenWidth; }

public:   
   double ScreenToTexXCoo( double dScreenX ) const; 
   double ScreenToTexYCoo( double dScreenY ) const; 
   void ScreenToTexCoo( double dScreenX, double dScreenY, double *dTexX, double *dTexY ) const; 

   double texToScreenXCoo(double dTexX) const;
   double texToScreenYCoo(double dTexY) const;

   void texToScreenCoo(double dTexX, double dTexY, double *dScreenX, double *dScreenY) const;
   void texToScreenCoo(int iTexX, int iTexY, int *iScreenX, int *iScreenY) const;

   bool ViewportToTexCoo( int iVpX, int iVpY, double *dTexX, double *dTexY ) const;
   
   void TexCooToPixelCoo( double dTexX, double dTexY, double *dPixX, double *dPixY ) const;
   void TexCooToPixelCoo( double dTexX, double dTexY, int *iPixX, int *iPixY ) const;

   bool viewportToPixelCoo(int iVpX, int iVpY, int *iPixX, int *iPixY) const;
   bool viewportToPixelCoo(int iVpX, int iVpY, double *dPixX, double *dPixY) const;
   
   bool viewportToScreenCoo(int iVpX, int iVpY, int *iScreenX, int *iScreenY) const;
   bool viewportToScreenCoo(int iVpX, int iVpY, double *dScreenX, double *dScreenY) const;

   bool viewportToScreenX(int iVpX, double *dScreenX) const;
   bool viewportToScreenY(int iVpY, double *dScreenY) const;

   void getDoubleViewport(int iSide, int *iXOrigin, int *iYOrigin, int *iWidth, int *iHeight) const;
};

} // namespace _pix_plot_img_framework 

