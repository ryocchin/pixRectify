#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_FlipPara.h"

pixq_FlipPara::pixq_FlipPara(void)
{
   DeInit( );
}

pixq_FlipPara::~pixq_FlipPara(void)
{
   ; // empty
}

void pixq_FlipPara::DeInit( void )
{
   _bFlipInit = false;

   _dTextureWidth = -1.0;
   _dTextureHeight = -1.0;
   _dImagWidth = -1.0;
   _dImagHeight = -1.0;

   // vieport geometry
   _nFrameEdge = 0;
   _nDoubleVPXCoo[0] = 0;
   _nDoubleVPXEnd[0] = 0;
   _nDoubleVPXCoo[1] = 0;
   _nDoubleVPXEnd[1] = 0;
   _nDoubleVPYCoo = 0;
   _nDoubleVPYEnd = 0;
   _nDoubleVPWidth = 0;
   _nDoubleVPHeight = 0;

   // conversion parameters
   _bTexDet = false;
   _bVpConversionSet = false;

   _bWholeExtent = false;

   return;
}

//
// move the center of the view area by the _dCenterStep * shift value
//
void pixq_FlipPara::XYViewShift( int iXShift, int iYShift )
{
   double dWidth = _dSrcX[1] - _dSrcX[0];
   double dHeight = _dSrcY[1] - _dSrcY[0];
   
   double dX = ( _dSrcX[0] + _dSrcX[1] ) / 2.0;
   double dY = ( _dSrcY[0] + _dSrcY[1] ) / 2.0;

   dX = dX + dWidth * (double)iXShift * _dCenterStep;
   dY = dY + dHeight * (double)iYShift * _dCenterStep;

   double dXRadius = dWidth / 2.0;
   double dYRadius = dHeight / 2.0;

   _dSrcX[0] = ( dX - dXRadius );
   _dSrcX[1] = ( dX + dXRadius );
   _dSrcY[0] = ( dY - dYRadius );
   _dSrcY[1] = ( dY + dYRadius );

   reshapeFlipSrcRect(); 

   _bWholeExtent = false;

   return; 
}

//
// move the center of the view area by given pixel number
//
void pixq_FlipPara::XYViewStep( int iXShift, int iYShift )
{
   double dWidth = _dSrcX[1] - _dSrcX[0];
   double dHeight = _dSrcY[1] - _dSrcY[0];
   
   double dShiftTexX = (double)iXShift * _dVpXDet[0] * _dTexXDet;
   double dShiftTexY = (double)iYShift * _dVpYDet[0] * _dTexYDet;
                                
   //double dShiftPixX = _dImagWidth * dShiftTexX;
   //double dShiftPixY = _dImagHeight * dShiftTexY;                        
   // non-normalized texture
   double dShiftPixX = dShiftTexX;
   double dShiftPixY = dShiftTexY;

   double dX = ( _dSrcX[0] + _dSrcX[1] ) / 2.0;
   double dY = ( _dSrcY[0] + _dSrcY[1] ) / 2.0;

   dX = dX + dShiftPixX; 
   dY = dY + dShiftPixY;

   double dXRadius = dWidth / 2.0;
   double dYRadius = dHeight / 2.0;

   _dSrcX[0] = ( dX - dXRadius );
   _dSrcX[1] = ( dX + dXRadius );
   _dSrcY[0] = ( dY - dYRadius );
   _dSrcY[1] = ( dY + dYRadius );

   reshapeFlipSrcRect(); 

   _bWholeExtent = false;

   return;
}

//
// display image at same scale
// 1:1 on screen and image
//
void pixq_FlipPara::viewOneToOne(void)
{  
   double dScreenWidth = _dOrthoX[1] - _dOrthoX[0];
   double dScreenHeight = _dOrthoY[1] - _dOrthoY[0];
   
   double dXRadius = dScreenWidth / 2;
   double dYRadius = dScreenHeight / 2;

   double dSrcXCen = ( _dSrcX[0] + _dSrcX[1] ) / 2;
   double dSrcYCen = ( _dSrcY[0] + _dSrcY[1] ) / 2;

   _dSrcX[0] = dSrcXCen - dXRadius;
   _dSrcX[1] = dSrcXCen + dXRadius;
   _dSrcY[0] = dSrcYCen - dYRadius;
   _dSrcY[1] = dSrcYCen + dYRadius;

   reshapeFlipSrcRect();

   _bWholeExtent = false;

   return;
}

//
// display image at double scale
// 2:1 on screen and image
//
void pixq_FlipPara::ViewOneToTwo( void )
{  
   double dScreenWidth = _dOrthoX[1] - _dOrthoX[0];
   double dScreenHeight = _dOrthoY[1] - _dOrthoY[0];
   
   double dXRadius = dScreenWidth / 4;
   double dYRadius = dScreenHeight / 4;

   double dSrcXCen = ( _dSrcX[0] + _dSrcX[1] ) / 2;
   double dSrcYCen = ( _dSrcY[0] + _dSrcY[1] ) / 2;

   _dSrcX[0] = dSrcXCen - dXRadius;
   _dSrcX[1] = dSrcXCen + dXRadius;
   _dSrcY[0] = dSrcYCen - dYRadius;
   _dSrcY[1] = dSrcYCen + dYRadius;

   reshapeFlipSrcRect(); 

   _bWholeExtent = false;

   return;
}

//
// display image at half scale
// 1:2 on screen and image
//
void pixq_FlipPara::ViewTwoToOne( void )
{  
   double dScreenWidth = _dOrthoX[1] - _dOrthoX[0];
   double dScreenHeight = _dOrthoY[1] - _dOrthoY[0];
   
   double dXRadius = dScreenWidth;
   double dYRadius = dScreenHeight;

   double dSrcXCen = ( _dSrcX[0] + _dSrcX[1] ) / 2;
   double dSrcYCen = ( _dSrcY[0] + _dSrcY[1] ) / 2;

   _dSrcX[0] = dSrcXCen - dXRadius;
   _dSrcX[1] = dSrcXCen + dXRadius;
   _dSrcY[0] = dSrcYCen - dYRadius;
   _dSrcY[1] = dSrcYCen + dYRadius;

   reshapeFlipSrcRect(); 

   _bWholeExtent = false;

   return;
}

//
// screen pixel to texture pixel scale
//
double pixq_FlipPara::ScreenTextureRatio( void )
const
{
   double dScreenWidth, dScreenHeight;
   double dTexCooXSize, dTexCooYSize, dTexWidth, dTexHeight;
   double dTexPixXSize, dTexPixYSize, dXRatio, dYRatio, dRatio;

   dRatio = 0.0;
   
   // get screen:texture ratio

   dScreenWidth = _dScreenPosX[1] - _dScreenPosX[0];
   dScreenHeight = _dScreenPosY[1] - _dScreenPosY[0];

   if( 0.0 >= dScreenWidth ) goto PIX_EXIT;
   if( 0.0 >= dScreenWidth ) goto PIX_EXIT;

   dTexCooXSize = _dTexCooX[1] - _dTexCooX[0];
   dTexCooYSize = _dTexCooY[1] - _dTexCooY[0];

   dTexWidth = _dTextureWidth;
   dTexHeight = _dTextureHeight;

   dTexPixXSize = dTexWidth * dTexCooXSize;
   dTexPixYSize = dTexHeight * dTexCooYSize;

   dXRatio = dTexPixXSize / dScreenWidth;
   dYRatio = dTexPixYSize / dScreenHeight;
   dRatio = ( dXRatio + dYRatio ) / 2;

PIX_EXIT:
   return dRatio;
}

//
// _dOrthoX, _dOrthoX can only be set in here!
//
void pixq_FlipPara::setFlipRatio(QSize rect)
{
   setFlipRatio(rect.width(), rect.height());

   return;
}

void pixq_FlipPara::setFlipRatio(int nScreenWidth, int nScreenHeight)
{
   double dXRadius, dYRadius;
   double dFrame = 0;

   _nScreenWidth = nScreenWidth;
   _nScreenHeight = nScreenHeight;

   dXRadius = (double)_nScreenWidth / 2.0;
   dYRadius = (double)_nScreenHeight / 2.0;

   // *** NOTE! _dOrthoX and _dOrthoY should not changed anywhere else ***

   _dOrthoX[0] = -dXRadius - dFrame + 0.5;
   _dOrthoX[1] = dXRadius + dFrame - 0.5;
   _dOrthoY[0] = -dYRadius - dFrame + 0.5;
   _dOrthoY[1] = dYRadius + dFrame - 0.5;

   // *** NOTE! _dOrthoXSize and _dOrthoYSize should not changed anywhere else ***

   _dOrthoXSize = _dOrthoX[1] - _dOrthoX[0];
   _dOrthoYSize = _dOrthoY[1] - _dOrthoY[0];

   return;
}
   
void pixq_FlipPara::zViewShift(int iZShift)
{
   double dWidth = _dSrcX[1] - _dSrcX[0];
   double dHeight = _dSrcY[1] - _dSrcY[0];
   
   double dX = ( _dSrcX[0] + _dSrcX[1] ) / 2.0;
   double dY = ( _dSrcY[0] + _dSrcY[1] ) / 2.0;

   double dXRadius = ( 1.0 + (double)iZShift * _dZViewStep ) * dWidth / 2.0;
   double dYRadius = ( 1.0 + (double)iZShift * _dZViewStep ) * dHeight / 2.0;

   _dSrcX[0] = ( dX - dXRadius );
   _dSrcX[1] = ( dX + dXRadius );
   _dSrcY[0] = ( dY - dYRadius );
   _dSrcY[1] = ( dY + dYRadius );

   reshapeFlipSrcRect();

   _bWholeExtent = false;

   return;
}

//
// display the area centered at given point
// at the same scale
//
void pixq_FlipPara::JumpToPoint( int iX, int iY )
{
   double dX = (double)iX;
   double dY = (double)iY;

   JumpToPoint( dX, dY );
   
   return;
}

void pixq_FlipPara::JumpToPoint( double dX, double dY )
{
   double dWidth = _dSrcX[1] - _dSrcX[0];
   double dHeight = _dSrcY[1] - _dSrcY[0];
   
   double dXRadius = dWidth / 2.0;
   double dYRadius = dHeight / 2.0;

   _dSrcX[0] = ( dX - dXRadius );
   _dSrcX[1] = ( dX + dXRadius );
   _dSrcY[0] = ( dY - dYRadius );
   _dSrcY[1] = ( dY + dYRadius );

   reshapeFlipSrcRect(); 

   _bWholeExtent = false;

   return;
}

//
// get the center coordinate of the current viewing area
//
void pixq_FlipPara::GetCenter( double *dX, double *dY ) const
{
   *dX = ( _dSrcX[0] + _dSrcX[1] ) / 2.0;
   *dY = ( _dSrcY[0] + _dSrcY[1] ) / 2.0;

   return;
}

void pixq_FlipPara::GetCenter( int *iX, int *iY ) const
{
   double dX, dY;

   GetCenter( &dX, &dY );
   *iX = (int)floor( 0.5 + dX );
   *iY = (int)floor( 0.5 + dY );

   return;
}

//
// reshape the source area of the image to be copied to be 
// geometrically similar to the destination
//
void pixq_FlipPara::reshapeFlipSrcRect(void)
{
   double dX, dY, dRate, dImgCenter, dImgX, dImgY, dImgRate;
   double dOrtho, dDet, dTexXSize, dTexYSize;

   // --- reshape the area, so that the displayed image area and ---
	// --- DC are geometrically similar ---

   _dScreenPosX[0] = _dOrthoX[0]; 
   _dScreenPosX[1] = _dOrthoX[1];
   _dScreenPosY[0] = _dOrthoY[0];
   _dScreenPosY[1] = _dOrthoY[1];

   dX = _dOrthoX[1] - _dOrthoX[0];
   dY = _dOrthoY[1] - _dOrthoY[0];
	if( 0.0 >= dX || 0.0 >= dY ) goto PIX_EXIT;

	dRate = dY / dX;
   dImgX = _dSrcX[1] - _dSrcX[0];
   dImgY = _dSrcY[1] - _dSrcY[0];
	if( 0.0 >= dImgX || 0.0 >= dImgY ) goto PIX_EXIT;

   dImgRate = dImgY / dImgX;

	if( dRate > dImgRate ) {
		dImgY = ( dImgX * dRate ) / 2.0;
		dImgCenter = ( _dSrcY[1] + _dSrcY[0] ) / 2.0;
		_dSrcY[0] = dImgCenter - dImgY;
		_dSrcY[1] = dImgCenter + dImgY;
	} else {
		dImgX = ( dImgY / dRate ) / 2.0;
		dImgCenter = ( _dSrcX[0] + _dSrcX[1] ) / 2.0;
		_dSrcX[0] = dImgCenter - dImgX;
		_dSrcX[1] = dImgCenter + dImgX;
	}
   	
   // --- set adjustment src rectangle ---
	_dAdjustedSrcX[0] = _dSrcX[0];
	_dAdjustedSrcX[1] = _dSrcX[1];
	_dAdjustedSrcY[0] = _dSrcY[0];
	_dAdjustedSrcY[1] = _dSrcY[1];
      
   // --- do not allow src rectangle goes beyond the texture area --- 
   
   if( 0 > _dAdjustedSrcY[0] ) {
      dDet = ( _dOrthoY[1] - _dOrthoY[0] ) / ( _dSrcY[1] - _dSrcY[0] );
      dOrtho = -_dSrcY[0] * dDet + _dOrthoY[0];
      _dAdjustedSrcY[0] = 0;
      _dScreenPosY[0] = dOrtho;
   } 
   
   if ( _dAdjustedSrcY[1] >= _dTextureHeight ) {
      dDet = ( _dOrthoY[1] - _dOrthoY[0] ) / ( _dSrcY[1] - _dSrcY[0] );
      dOrtho = ( _dTextureHeight - 1 - _dSrcY[0] ) * dDet + _dOrthoY[0];
      _dAdjustedSrcY[1] = _dTextureHeight - 1;
      _dScreenPosY[1] = dOrtho;
   }

   if( 0 > _dAdjustedSrcX[0] ) {
      dDet = ( _dOrthoX[1] - _dOrthoX[0] ) / ( _dSrcX[1] - _dSrcX[0] );
      dOrtho = -_dSrcX[0] * dDet + _dOrthoX[0];
      _dAdjustedSrcX[0] = 0;
      _dScreenPosX[0] = dOrtho; 
   } 
   
   if ( _dAdjustedSrcX[1] >= _dTextureWidth ) {
      dDet = ( _dOrthoX[1] - _dOrthoX[0] ) / ( _dSrcX[1] - _dSrcX[0] );
      dOrtho = ( _dTextureWidth - 1 - _dSrcX[0] ) * dDet + _dOrthoX[0];
      _dAdjustedSrcX[1] = _dTextureWidth - 1;
      _dScreenPosX[1] = dOrtho;
   }

   // *** get texture coordinate to be copied to the SCREEn ***
   //_dTexCooX[0] = _dAdjustedSrcX[0] / _dTextureWidth;
   //_dTexCooX[1] = _dAdjustedSrcX[1] / _dTextureWidth;
   //_dTexCooY[0] = _dAdjustedSrcY[0] / _dTextureHeight;
   //_dTexCooY[1] = _dAdjustedSrcY[1] / _dTextureHeight;

   // non-normalized texture
   _dTexCooX[0] = _dAdjustedSrcX[0];
   _dTexCooX[1] = _dAdjustedSrcX[1];
   _dTexCooY[0] = _dAdjustedSrcY[0];
   _dTexCooY[1] = _dAdjustedSrcY[1];

   // *** GET screen(ortho) coo <-> texture coo conversion parameter ***
   dTexXSize = _dTexCooX[1] - _dTexCooX[0];
   dTexYSize = _dTexCooY[1] - _dTexCooY[0];
   if( 0.0 >= dTexXSize || 0.0 >= dTexYSize ) {
      _bTexDet = false;
      _dTexXDet = 0.0;
      _dTexYDet = 0.0;
      _dTexXShift = 0.0;
      _dTexYShift = 0.0;
   } else { 
      double dScreenXSize = _dScreenPosX[1] - _dScreenPosX[0];
      double dScreenYSize = _dScreenPosY[1] - _dScreenPosY[0];
      double dDetX = dTexXSize / dScreenXSize;
      double dDetY = dTexYSize / dScreenYSize;
      double dShiftX = ( _dTexCooX[1] * _dScreenPosX[0] - _dTexCooX[0] * _dScreenPosX[1] ) / dTexXSize;
      double dShiftY = ( _dTexCooY[1] * _dScreenPosY[0] - _dTexCooY[0] * _dScreenPosY[1] ) / dTexYSize;
      _dTexXDet = dDetX;
      _dTexYDet = dDetY;
      _dTexXShift = dShiftX;
      _dTexYShift = dShiftY;
      _bTexDet = true;
   }

   // ---reset viewpoint -> texture coordinate conversion ***
   setVpTexConversion();

   // --- Done ---
PIX_EXIT:
	return;
}

//
// full screen - double view port
//
void pixq_FlipPara::setDoubleViewports(int nScreenWidth, int nScreenHeight)
{
   int nWidth, nHeight;
   int nFrame2Edge;

   // *** frame edge width ***
   //_nFrameEdge = 2;
   _nFrameEdge = 0;

   // *** size of half screen ***
   nFrame2Edge = _nFrameEdge * 2;
   nWidth = nScreenWidth / 2 - nFrame2Edge;
   nHeight = nScreenHeight - nFrame2Edge; 	

   _nDoubleVPXCoo[0] = _nFrameEdge;
   _nDoubleVPXEnd[0] = nScreenWidth / 2 - _nFrameEdge;
   _nDoubleVPXCoo[1] = nScreenWidth / 2 + _nFrameEdge;
   _nDoubleVPXEnd[1] = nScreenWidth - _nFrameEdge;
   _nDoubleVPYCoo = _nFrameEdge;
   _nDoubleVPYEnd = nScreenHeight - _nFrameEdge;

   _nDoubleVPWidth = nWidth;
   _nDoubleVPHeight = nHeight;
     
   // *** reshape image area ***
   reshapeFlipImageRect(_nDoubleVPWidth, _nDoubleVPHeight);

   return;
}

//
// set conversion parameter between ortho coordinate in flip para
// and screen coordinates, double viewport
//
// ortho.x = _dVpXDet[k] * ( screen.x - _dVpXShift[k] )
// ortho.y = _dVpYDet[k] * ( screen.y - _dVpYShift[k] )
//
void pixq_FlipPara::setDoubleConversion(void)
{
   int k, nScreenWidth, nScreenHeight;
   double dXDet, dYDet, dXShift[2], dYShift[2], dX, dY;

   // --- get dimension ---
   nScreenWidth = _nDoubleVPXEnd[0] - _nDoubleVPXCoo[0];
   nScreenHeight = _nDoubleVPYEnd - _nDoubleVPYCoo;  
   dX = GetOrthoXSize( );
   dY = GetOrthoYSize( );

   dXDet = dX / (double)nScreenWidth;
   dYDet = dY / (double)nScreenHeight;

   for( k = 0 ; k < 2 ; k++ ) {
      dXShift[k] = _nDoubleVPXCoo[k] - GetOrthoX( 0 ) / dXDet;
      dYShift[k] = _nDoubleVPYCoo - GetOrthoY( 0 ) / dYDet;
   }

   for( k = 0 ; k < 2 ; k++ ) {
      _dVpXDet[k] = dXDet;
      _dVpYDet[k] = dYDet;
      _dVpXShift[k] = dXShift[k];
      _dVpYShift[k] = dYShift[k];
   }

   _bVpConversionSet = true;
   setVpTexConversion();

   return;
}

//
// set viewport -> texture conversion parameter
//
void pixq_FlipPara::setVpTexConversion(void)
{
   if( !_bVpConversionSet ) goto PIX_EXIT;

   for( int k = 0 ; k < 2 ; k++ ) {
      _dVpXTexDet[k] = _dTexXDet * _dVpXDet[k];
      _dVpYTexDet[k] = _dTexYDet * _dVpYDet[k];

      _dVpXTexShift[k] = _dTexXDet * ( _dVpXDet[0] * _dVpXShift[0] + _dTexXShift );
      _dVpYTexShift[k] = _dTexYDet * ( _dVpYDet[0] * _dVpYShift[0] + _dTexYShift );
   }
   
   // --- Done ---
PIX_EXIT:
	return;
}

//
// initialize the flip!
// show the whole image extent
//
void pixq_FlipPara::InitFlip( int nTexWidth, // [i] width of the OpenGL Texture
                            int nTexHeight, // [i] height of the OpenGL Texture
                            int nImgWidth, // [i] image width, -1 if same as texture
                            int nImgHeight ) // [i] image height, -1 if same as texture
{
   if( 0 < _dTextureWidth ) return;
   
   _dTextureWidth  = (double)nTexWidth;
   _dTextureHeight = (double)nTexHeight;   
   _dImagWidth  = (double)nImgWidth;
   _dImagHeight = (double)nImgHeight;

   flipRecenter();

   _dCenterStep = 0.01;
   _dZViewStep = 0.01;

   _bFlipInit = true;
   _bWholeExtent = true;

   return;
}

void pixq_FlipPara::InitFlip( int nImgWidth, // [i] image width, -1 if same as texture
                            int nImgHeight ) // [i] image height, -1 if same as texture
{   
   InitFlip( nImgWidth, nImgHeight, nImgWidth, nImgHeight );
   
   return;
}

//
// show the whole image extent
//
void pixq_FlipPara::flipRecenter(void)
{   
   if( 0.0 > _dImagWidth ) {
      // image size is same as texture
      _dSrcX[0] = -0.5;
      _dSrcX[1] = _dTextureWidth - 0.5;
      _dSrcY[0] = -0.5;
      _dSrcY[1] = _dTextureHeight - 0.5; 
   } else {
      double dXTexCen = ( _dTextureWidth - 1.0 ) / 2.0;
      double dYTexCen = ( _dTextureHeight - 1.0 ) / 2.0;
      double dXImgRad = _dImagWidth / 2.0;
      double dYImgRad = _dImagHeight / 2.0;
      _dSrcX[0] = max( dXTexCen - dXImgRad, -0.5 );
      _dSrcX[1] = min( dXTexCen + dXImgRad, _dTextureWidth - 0.5 );
      _dSrcY[0] = max( dYTexCen - dYImgRad, -0.5 );
      _dSrcY[1] = min( dYTexCen + dYImgRad, _dTextureHeight - 0.5 );
   }

   reshapeFlipSrcRect(); 

   _bWholeExtent = true;

   return;
}


//
// convert screen coordinate to texture coordinate
//
void pixq_FlipPara::ScreenToTexCoo( 
      double dScreenX, // [i] screen X coordinate
      double dScreenY, // [i] screen Y coordinate
      double *dTexX, // [o] texture X coordinate
      double *dTexY ) // [o] texture Y coordinate
const
{
   *dTexX = ScreenToTexXCoo( dScreenX );
   *dTexY = ScreenToTexYCoo( dScreenY );

   return;
}

double pixq_FlipPara::ScreenToTexXCoo( double dScreenX ) // [i] screen X coordinate
const
{
   return _dTexXDet * ( dScreenX - _dTexXShift );
}

double pixq_FlipPara::ScreenToTexYCoo( double dScreenY ) // [i] screen Y coordinate
const
{
   return _dTexYDet * ( dScreenY - _dTexYShift );
}

//
// convert texture coordinate to screen coordinate
//
void pixq_FlipPara::texToScreenCoo(double dTexX,
                                  double dTexY, 
                                  double *dScreenX, 
                                  double *dScreenY )
                                  const
{   
   *dScreenX = texToScreenXCoo(dTexX);
   *dScreenY = texToScreenYCoo(dTexY);

   return;
}

//
// convert texture coordinate to screen coordinate
//
void pixq_FlipPara::texToScreenCoo(int iTexX,
                                  int iTexY, 
                                  int *iScreenX, 
                                  int *iScreenY )
                                  const
{   
   *iScreenX = (int)floor(0.5 + texToScreenXCoo((double)iTexX));
   *iScreenY = (int)floor(0.5 + texToScreenYCoo((double)iTexY));

   return;
}

//
// convert texture x coordinate to screen coordinate
//
double pixq_FlipPara::texToScreenXCoo(double dTexX)
const
{   
   return dTexX / _dTexXDet + _dTexXShift;
}

//
// convert texture y coordinate to screen coordinate
//
double pixq_FlipPara::texToScreenYCoo(double dTexY)
const
{   
   return dTexY / _dTexYDet + _dTexYShift;
}

//
// from opengl texture coordinate 0-1, get texture pixel coordinate
//
void pixq_FlipPara::TexCooToPixelCoo( double dTexX, // [i] texture x coordinate
                                    double dTexY,  // [i] texture y coordinate
                                    double *dPixX, // [o] image x coordinate
                                    double *dPixY ) // [o] image y coordinate
                                    const

{
   *dPixX = _dImagWidth * dTexX;
   *dPixY = _dImagHeight * dTexY;    
}
   
void pixq_FlipPara::TexCooToPixelCoo( double dTexX, // [i] texture x coordinate
                                     double dTexY, // [i] texture y coordinate
                                     int *iPixX,  // [o] image x coordinate
                                     int *iPixY ) // [o] image y coordinate
                                     const
{
   double dPixX, dPixY;
   TexCooToPixelCoo( dTexX, dTexY, &dPixX, &dPixY );

   *iPixX = (int)floor( dPixX );
   *iPixY = (int)floor( dPixY );
}

//
// convert viewport coordinate to ortho screen coordinate
//
bool pixq_FlipPara::viewportToPixelCoo(int iVpX, // [i] viewport x coordinate
                                       int iVpY, 
                                       int *iPixX, 
                                       int *iPixY ) // [o] ortho x coordinate
                                   const    
{
   bool bRetCode = false;
   double dTexX, dTexY;

   if (!viewportToPixelCoo(iVpX, iVpY, &dTexX, &dTexY)) {
      goto PIX_EXIT;
   }

   // TexCooToPixelCoo
   //*iPixX = (int)floor( _dImagWidth * dTexX + 0.5 );
   //*iPixY = (int)floor( _dImagHeight * dTexY + 0.5 );
   *iPixX = (int)floor( dTexX + 0.5 );
   *iPixY = (int)floor( dTexY + 0.5 );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FlipPara::viewportToPixelCoo(int iVpX, // [i] viewport x coordinate
                                       int iVpY, 
                                       double *dPixX, 
                                       double *dPixY ) // [o] ortho x coordinate
                                       const                                       
{
   *dPixX = _dVpXTexDet[0] * (double)iVpX - _dVpXTexShift[0]; 
   *dPixY = _dVpYTexDet[0] * (double)iVpY - _dVpYTexShift[0];

   return true;
}


void pixq_FlipPara::getDoubleViewport(int iSide, // [i] side of the screen, 0 for left or 1 for right
                                     int *iXOrigin, // [o] viewport origin, x
                                     int *iYOrigin, // [o] viewport origin, y
                                     int *iWidth, // [o] viewport width
                                     int *iHeight ) // [o] viewport width
                                     const                                     
{
   if( 0 == iSide ) {
      *iXOrigin = _nDoubleVPXCoo[0];
   } else {
      *iXOrigin = _nDoubleVPXCoo[1];
   }
   *iYOrigin = _nDoubleVPYCoo;
   *iWidth =   _nDoubleVPWidth;
   *iHeight =  _nDoubleVPHeight;

   return;
}

//
// convert viewport coordinate to texture position
//
bool pixq_FlipPara::ViewportToTexCoo( int iVpX, // [i] viewport x coordinate
                                    int iVpY, // [i] viewport y coordinate
                                    double *dTexX, // [o] ortho x coordinate
                                    double *dTexY ) // [o] ortho x coordinate
                                    const
{   
   if( !_bVpConversionSet ) {
      *dTexX = 0.0;
      *dTexY = 0.0;
      return false;
   }

   *dTexX = _dVpXTexDet[0] * (double)iVpX - _dVpXTexShift[0];
   *dTexY = _dVpYTexDet[0] * (double)iVpY - _dVpYTexShift[0];
   return true;
}

//
// full screen - double view port
//
void pixq_FlipPara::setSingleViewports(QSize rect)
{
   setSingleViewports(rect.width(), rect.height());

   return;
}

void pixq_FlipPara::setSingleViewports(int nScreenWidth, int nScreenHeight)
{
   int nWidth, nHeight;
   int nFrame2Edge;

   // *** frame edge width ***
   //_nFrameEdge = 2;
   _nFrameEdge = 0;

   // *** size of half screen ***
   nFrame2Edge = _nFrameEdge * 2;
   nWidth = nScreenWidth - nFrame2Edge;
   nHeight = nScreenHeight - nFrame2Edge; 	

   _nDoubleVPXCoo[0] = _nFrameEdge;
   _nDoubleVPXEnd[0] = nScreenWidth - _nFrameEdge;
   _nDoubleVPXCoo[1] = _nDoubleVPXCoo[0];
   _nDoubleVPXEnd[1] = _nDoubleVPXEnd[0];
   _nDoubleVPYCoo = _nFrameEdge;
   _nDoubleVPYEnd = nScreenHeight - _nFrameEdge;

   _nDoubleVPWidth = nWidth;
   _nDoubleVPHeight = nHeight;
     
   // *** reshape image area ***

   reshapeFlipImageRect(_nDoubleVPWidth, _nDoubleVPHeight);

   return;
}

//
// set conversion parameter between ortho coordinate in flip para
// and screen coordinates, single viewport
//
// ortho.x = _dVpXDet[k] * ( screen.x - _dVpXShift[k] )
// ortho.y = _dVpYDet[k] * ( screen.y - _dVpYShift[k] )
//
void pixq_FlipPara::SetSingleConversion( void )
{
   int k, nScreenWidth, nScreenHeight;
   double dXDet, dYDet, dXShift, dYShift, dX, dY;

   // --- get dimension ---

   nScreenWidth = _nDoubleVPXEnd[0] - _nDoubleVPXCoo[0];
   nScreenHeight = _nDoubleVPYEnd - _nDoubleVPYCoo;  
   dX = GetOrthoXSize( );
   dY = GetOrthoYSize( );

   dXDet = dX / (double)nScreenWidth;
   dYDet = dY / (double)nScreenHeight;

   dXShift = _nDoubleVPXCoo[0] - GetOrthoX( 0 ) / dXDet;
   dYShift = _nDoubleVPYCoo - GetOrthoY( 0 ) / dYDet;
   
   for( k = 0 ; k < 2 ; k++ ) {
      _dVpXDet[k] = dXDet;
      _dVpYDet[k] = dYDet;
      _dVpXShift[k] = dXShift;
      _dVpYShift[k] = dYShift;
   }

   _bVpConversionSet = true;
   setVpTexConversion();

   return;
}

void pixq_FlipPara::reshapeFlipImageRect(int nScreenWidth, int nScreenHeight)
{
	double dDetX, dDetY, dX, dY, dLastX, dLastY, dRadiusX, dRadiusY;
   double dCutL, dCutR, dCutT, dCutB, dLastRadiusX, dLastRadiusY;
   double dLastImgX, dLastImgY, dLastImgL, dLastImgT;
   double dNewImageL, dNewImageR, dNewImageT, dNewImageB;
   double dLastX0, dLastX1, dLastY0, dLastY1;

   // --- last screen aspect - --

   dLastX0 = _dOrthoX[0];
   dLastX1 = _dOrthoX[1];
   dLastY0 = _dOrthoY[0];
   dLastY1 = _dOrthoY[1];
   
   dLastX = dLastX1 - dLastX0;
   dLastY = dLastY1 - dLastY0;

   // --- set current screen size ---

   setFlipRatio(nScreenWidth, nScreenHeight);

   // --- set current screen size ---

   dX = _dOrthoX[1] - _dOrthoX[0];
   dY = _dOrthoY[1] - _dOrthoY[0];
	if( 0.0 >= dX || 0.0 >= dY ) goto PIX_EXIT;

   // 
   dLastRadiusX = dLastX / 2.0;
   dLastRadiusY = dLastY / 2.0;
   dRadiusX = dX / 2.0;
   dRadiusY = dY / 2.0;

   dCutL = dLastRadiusX - dRadiusX;
   dCutR = dLastRadiusX + dRadiusX;
   dCutT = dLastRadiusY - dRadiusY;
   dCutB = dLastRadiusY + dRadiusY;

   // --- last image aspect ---
   dLastImgX = _dSrcX[1] - _dSrcX[0];
   dLastImgY = _dSrcY[1] - _dSrcY[0];
   dLastImgL = _dSrcX[0];
   dLastImgT = _dSrcY[0];

   dDetX = dLastImgX / dLastX;
   dDetY = dLastImgY / dLastY;

   dNewImageL = dDetX * dCutL + dLastImgL;
   dNewImageR = dDetX * dCutR + dLastImgL;
   dNewImageT = dDetY * dCutT + dLastImgT;
   dNewImageB = dDetY * dCutB + dLastImgT;

   _dSrcX[0] = dNewImageL;	
   _dSrcX[1] = dNewImageR;
   _dSrcY[0] = dNewImageT;
	_dSrcY[1] = dNewImageB;
  
   // --- reshape the area, so that the displayed image area and ---
	
   reshapeFlipSrcRect();

   // --- Done ---
PIX_EXIT:
	return;
}

void pixq_FlipPara::reshapeFlipImageRect( QSize rect )
{
   //int nScreenWidth = rect.right( ) - rect.left( ) + 1;
   //int nScreenHeight = rect.bottom( ) - rect.top( ) + 1;

   int nScreenWidth = rect.width( );
   int nScreenHeight = rect.height( );
   
   reshapeFlipImageRect(nScreenWidth, nScreenHeight);
   
   return;
}

//
// convert viewport coordinate to ortho screen coordinate
//
bool pixq_FlipPara::viewportToScreenX(int iVpX,
                                        double *dScreenX ) 
                                        const
{
   bool bRetCode = false;

   if (!GetFlipInit()) {
      goto PIX_EXIT;
   }

   *dScreenX = _dVpXDet[0] * ( (double)iVpX - _dVpXShift[0] );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FlipPara::viewportToScreenY(int iVpY,
                                        double *dScreenY ) 
                                        const
{
   bool bRetCode = false;

   if (!GetFlipInit()) {
      goto PIX_EXIT;
   }

   *dScreenY = _dVpYDet[0] * ( (double)iVpY - _dVpYShift[0] );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FlipPara::viewportToScreenCoo(int iVpX,
                                        int iVpY, 
                                        int *iScreenX,
                                        int *iScreenY ) 
                                        const
{
   bool bRetCode = false;
   double dScreenX, dScreenY;

   if (!viewportToScreenCoo(iVpX, iVpY, &dScreenX, &dScreenY)) {
      goto PIX_EXIT;
   }

   // TexCooToPixelCoo
   *iScreenX = (int)floor( dScreenX + 0.5 );
   *iScreenY = (int)floor( dScreenY + 0.5 );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FlipPara::viewportToScreenCoo(int iVpX,
                                        int iVpY,
                                        double *dScreenX,
                                        double *dScreenY ) 
                                        const
{
   bool bRetCode = false;

   if (!GetFlipInit()) {
      goto PIX_EXIT;
   }

   if (!viewportToScreenX(iVpX, dScreenX)) {
      goto PIX_EXIT;
   }

   if (!viewportToScreenY(iVpY, dScreenY)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

void pixq_FlipPara::resizeWindow(QSize rect)
{
   if (getWholeExtent()) {
      setFlipRatio(rect);
      flipRecenter();
      setSingleViewports(rect);
      SetSingleConversion( );
   } else {
      //setFlipRatio( nScreenWidth, nScreenHeight );
      //setSingleViewports( nScreenWidth, nScreenHeight );
      reshapeFlipImageRect(rect);
   }
   
   return;
}