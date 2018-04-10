#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_PanePara.h"

pixq_PanePara::pixq_PanePara(void)
{
   DeInit( );

   _pParent = (pixq_ScreenPara*)NULL;
   _sFileArea = FlipAreaNone;

   return;
}

pixq_PanePara::pixq_PanePara( short sArea )
{
   DeInit( );
   
   _sFileArea = sArea;
   _pParent = (pixq_ScreenPara*)NULL;

   return;
}

pixq_PanePara::~pixq_PanePara(void)
{
   ; // empty
}

void pixq_PanePara::DeInit( void )
{
   _bTexDet = false;
   _bWholeExtent = false; 

   return;
}

//
// move the center of the view area by the _dCenterStep * shift value
//
void pixq_PanePara::XYViewShift( int iXShift, int iYShift )
{
   double dWidth = _dSrcX[1] - _dSrcX[0];
   double dHeight = _dSrcY[1] - _dSrcY[0];
   double dCenterStep = _pParent->GetCenterStep( );
   double dX = ( _dSrcX[0] + _dSrcX[1] ) / 2.0;
   double dY = ( _dSrcY[0] + _dSrcY[1] ) / 2.0;

   dX = dX + dWidth * (double)iXShift * dCenterStep;
   dY = dY + dHeight * (double)iYShift * dCenterStep;

   double dXRadius = dWidth / 2.0;
   double dYRadius = dHeight / 2.0;

   _dSrcX[0] = ( dX - dXRadius );
   _dSrcX[1] = ( dX + dXRadius );
   _dSrcY[0] = ( dY - dYRadius );
   _dSrcY[1] = ( dY + dYRadius );

   reshapeFlipSrcRect( ); 

   _bWholeExtent = false;

   return; 
}

//
// display the whole extent of the image to the source area
//
void pixq_PanePara::flipRecenter(void)
{   
   ShowWholeImage( );
   
   reshapeFlipSrcRect();

   _bWholeExtent = true;

   return;
}

//
// move the center of the view area by given pixel number
//
void pixq_PanePara::XYViewStep( int iXShift, int iYShift )
{
   double dWidth = _dSrcX[1] - _dSrcX[0];
   double dHeight = _dSrcY[1] - _dSrcY[0];
   
   double dShiftTexX = (double)iXShift * _dVpXDet * _dTexXDet;
   double dShiftTexY = (double)iYShift * _dVpYDet * _dTexYDet;
                                
   //double dShiftPixX = _dImageWidth * dShiftTexX;
   //double dShiftPixY = _dImageHeight * dShiftTexY;                        
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
   
void pixq_PanePara::viewOneToOne(void)
{  
   double dOrthoX0 = GetOrthoX( 0 );
   double dOrthoX1 = GetOrthoX( 1 );
   double dOrthoY0 = GetOrthoY( 0 );
   double dOrthoY1 = GetOrthoY( 1 );

   double dScreenWidth, dScreenHeight;

   switch( _sFileArea ) {
   case FlipAreaNone:
      return;
   case FlipAreaSingle:
   case FlipAreaLeft:
   case FlipAreaRight: 
   case FlipAreaUpper: 
   case FlipAreaLower:
      dScreenWidth = dOrthoX1 - dOrthoX0;
      dScreenHeight = dOrthoY1 - dOrthoY0;  
      break;
   default:
      dScreenWidth = 0.0;
      dScreenHeight = 0.0;
      break;
   }

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
 
void pixq_PanePara::zViewShift(int iZShift)
{
   double dWidth = _dSrcX[1] - _dSrcX[0];
   double dHeight = _dSrcY[1] - _dSrcY[0];
   double dZViewStep = _pParent->GetZViewStep( );
   double dX = ( _dSrcX[0] + _dSrcX[1] ) / 2.0;
   double dY = ( _dSrcY[0] + _dSrcY[1] ) / 2.0;

   double dXRadius = ( 1.0 + (double)iZShift * dZViewStep ) * dWidth / 2.0;
   double dYRadius = ( 1.0 + (double)iZShift * dZViewStep ) * dHeight / 2.0;

   _dSrcX[0] = ( dX - dXRadius );
   _dSrcX[1] = ( dX + dXRadius );
   _dSrcY[0] = ( dY - dYRadius );
   _dSrcY[1] = ( dY + dYRadius );

   reshapeFlipSrcRect();

   _bWholeExtent = false;

   return;
}

void pixq_PanePara::CopySrc( double *dSrcX, double *dSrcY )
{
   _dSrcX[0] = dSrcX[0];
   _dSrcX[1] = dSrcX[1];
   _dSrcY[0] = dSrcY[0];
   _dSrcY[1] = dSrcY[1];

   reshapeFlipSrcRect(); // CopySrc

   _bWholeExtent = false;

   return;
}

//
// display the area centered at given point
// at the same scale
//
void pixq_PanePara::JumpToPoint( int iX, int iY )
{
   double dX = (double)iX;
   double dY = (double)iY;

   JumpToPoint( dX, dY );
   
   return;
}

void pixq_PanePara::JumpToPoint( double dX, double dY )
{
   double dWidth = _dSrcX[1] - _dSrcX[0];
   double dHeight = _dSrcY[1] - _dSrcY[0];
   
   double dXRadius = dWidth / 2.0;
   double dYRadius = dHeight / 2.0;

   _dSrcX[0] = ( dX - dXRadius );
   _dSrcX[1] = ( dX + dXRadius );
   _dSrcY[0] = ( dY - dYRadius );
   _dSrcY[1] = ( dY + dYRadius );

   reshapeFlipSrcRect(); // JumpToPoint

   _bWholeExtent = false;

   return;
}

//
// get the center coordinate of the current viewing area
//
void pixq_PanePara::GetCenter( double *dX, double *dY )
{
   *dX = ( _dSrcX[0] + _dSrcX[1] ) / 2.0;
   *dY = ( _dSrcY[0] + _dSrcY[1] ) / 2.0;

   return;
}

void pixq_PanePara::GetCenter( int *iX, int *iY )
{
   double dX, dY;

   GetCenter( &dX, &dY );
   *iX = (int)floor( 0.5 + dX );
   *iY = (int)floor( 0.5 + dY );

   return;
}
      
//
// get screen and texture coordinate  of drawing range quickly
//
// notes:
//
void pixq_PanePara::ImageCornersCoordinate( 
      double *dTexXCoo, // [o] four corners of the texture, x 
      double *dTexYCoo, // [o] four corners of the texture, y
      double *dScreenXPos, // [o] four corners of the screen, x 
      double *dScreenYPos ) // [o] four corners of the screen, y
{

   //
   //        |            |
   //    ----+------------+---- 1 i
   //        |[0]      [3]|
   //        |            |
   //        |            |
   //        |            |
   //        |[1]      [2]|
   //    ----+------------+---- 0 ii
   //        |            |
   //        0            1
   //        jj           j
   //        

   dTexXCoo[0] = _dTexCooX[0];       
   dTexXCoo[1] = _dTexCooX[0];        
   dTexXCoo[2] = _dTexCooX[1];         
   dTexXCoo[3] = _dTexCooX[1]; 

   dTexYCoo[0] = _dTexCooY[1]; 
   dTexYCoo[1] = _dTexCooY[0]; 
   dTexYCoo[2] = _dTexCooY[0];   
   dTexYCoo[3] = _dTexCooY[1];                                  

   dScreenXPos[0] = _dScreenPosX[0]; 
   dScreenXPos[1] = _dScreenPosX[0]; 
   dScreenXPos[2] = _dScreenPosX[1]; 
   dScreenXPos[3] = _dScreenPosX[1];

   dScreenYPos[0] = _dScreenPosY[1];
   dScreenYPos[1] = _dScreenPosY[0];
   dScreenYPos[2] = _dScreenPosY[0];
   dScreenYPos[3] = _dScreenPosY[1];

   return;
}

bool pixq_PanePara::getPaneInit(void) 
const
{
   bool bRetCode = false;

   switch( _sFileArea ) {
   case FlipAreaNone:
      goto PIX_EXIT;
      break;
      
   case FlipAreaSingle:
   case FlipAreaLeft:
   case FlipAreaRight:
   case FlipAreaUpper:
   case FlipAreaLower:
      break;
   }
      
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


// ortho.x = _dVpXDet[k] * ( screen.x - _dVpXShift[k] )
// ortho.y = _dVpYDet[k] * ( screen.y - _dVpYShift[k] )

double pixq_PanePara::PaneToScreenX(int iPaneX)
{
   double dScreenX = 0.0;

   if (!getPaneInit()) {
      goto PIX_EXIT;
   }

   dScreenX = _dVpXDet * ( (double)iPaneX - _dVpXShift );   
      
PIX_EXIT:
   return dScreenX;
}

double pixq_PanePara::PaneToScreenY(int iPaneY)
{
   double dScreenY = 0.0;

   if (!getPaneInit()) {
      goto PIX_EXIT;
   }

   dScreenY = _dVpYDet * ( (double)iPaneY - _dVpYShift );   
      
PIX_EXIT:
   return dScreenY;
}

//
// convert viewport coordinate to ortho screen coordinate
//
bool pixq_PanePara::viewportToPixelCoo(int iVpX, // [i] viewport x coordinate
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
   //*iPixX = (int)floor( _dImageWidth * dTexX + 0.5 );
   //*iPixY = (int)floor( _dImageHeight * dTexY + 0.5 );
   *iPixX = (int)floor( dTexX + 0.5 );
   *iPixY = (int)floor( dTexY + 0.5 );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_PanePara::viewportToPixelCoo(int iVpX, // [i] viewport x coordinate
                                       int iVpY, 
                                       double *dPixX, 
                                       double *dPixY ) // [o] ortho x coordinate
const
{
   bool bRetCode = false;

   if (!getPaneInit()) {
      goto PIX_EXIT;
   }

   *dPixX = _dVpXTexDet * (double)iVpX - _dVpXTexShift; 
   *dPixY = _dVpYTexDet * (double)iVpY - _dVpYTexShift;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


bool pixq_PanePara::viewportToScreenCoo(int iVpX,
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

bool pixq_PanePara::viewportToScreenCoo(int iVpX,
                                        int iVpY,
                                        double *dScreenX, 
                                        double *dScreenY )
const
{
   bool bRetCode = false;

   if (!getPaneInit()) {
      goto PIX_EXIT;
   }

   *dScreenX = _dVpXDet * ( (double)iVpX - _dVpXShift );
   *dScreenY = _dVpYDet * ( (double)iVpY - _dVpYShift );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
//
// convert viewport coordinate to ortho screen coordinate
//
bool pixq_PanePara::viewportToScreenX(int iVpX,
   double *dScreenX)
   const
{
   bool bRetCode = false;

   if (!getPaneInit()) {
      goto PIX_EXIT;
   }

   *dScreenX = _dVpXDet * ((double)iVpX - _dVpXShift);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_PanePara::viewportToScreenY(int iVpY,
   double *dScreenY)
   const
{
   bool bRetCode = false;

   if (!getPaneInit()) {
      goto PIX_EXIT;
   }

   *dScreenY = _dVpYDet * ((double)iVpY - _dVpYShift);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// convert texture x coordinate to screen coordinate
//
double pixq_PanePara::texToScreenXCoo(double dTexX)
const
{   
   double dScreenX = dTexX / _dTexXDet + _dTexXShift;

   return dScreenX;
}

//
// convert texture y coordinate to screen coordinate
//
double pixq_PanePara::texToScreenYCoo(double dTexY)
const
{
   double dScreenY = dTexY / _dTexYDet + _dTexYShift;

   return dScreenY;
}

//
// convert texture coordinate to screen coordinate
//
void pixq_PanePara::texToScreenCoo(double dTexX,
                                  double dTexY, 
                                  double *dScreenX, 
                                  double *dScreenY )
                                  const
{
   *dScreenX = texToScreenXCoo( dTexX );
   *dScreenY = texToScreenYCoo(dTexY);

   return;
}

//
// convert texture coordinate to screen coordinate
//
void pixq_PanePara::texToScreenCoo(int iTexX,
   int iTexY,
   int *iScreenX,
   int *iScreenY)
   const
{
   *iScreenX = (int)floor(0.5 + texToScreenXCoo((double)iTexX));
   *iScreenY = (int)floor(0.5 + texToScreenYCoo((double)iTexY));

   return;
}

void pixq_PanePara::setFlipRatio(QSize rect)
{
   setFlipRatio(rect.width(), rect.height());

   return;
}

void pixq_PanePara::setFlipRatio(int nScreenWidth,
                                   int nScreenHeight )
{
   double dXRadius, dYRadius;
   double dFrame = 0.0;

   _nScreenHeight = nScreenHeight;
   _nScreenWidth = nScreenWidth;

   switch( _sFileArea ) {
   // single area for the whole screen
   case FlipAreaSingle:
   case FlipAreaLeft:
   case FlipAreaRight:
   case FlipAreaUpper:
   case FlipAreaLower:
      _nDoubleVPXCoo = 0;
      _nDoubleVPXEnd = nScreenWidth-1;
      _nDoubleVPYCoo = 0;
      _nDoubleVPYEnd = nScreenHeight-1;
      break;

   default:
      goto PIX_EXIT;
      break;
   }

   //
   
   dXRadius = (double)nScreenWidth / 2.0;
   dYRadius = (double)nScreenHeight / 2.0;

   // *** NOTE! _dOrthoX and _dOrthoY should not changed anywhere else ***

   _dOrthoX[0] = -dXRadius - dFrame + 0.5;
   _dOrthoX[1] = dXRadius + dFrame - 0.5;
   _dOrthoY[0] = -dYRadius - dFrame + 0.5;
   _dOrthoY[1] = dYRadius + dFrame - 0.5;
   
PIX_EXIT:
   return;
}

//
// initialize flip parameter to display the whole image extent
// _dImageWidth, _dImageHeight can only be set in here!
//
void pixq_PanePara::InitFlip( void )
{
   ShowWholeImage( ); 

   _bWholeExtent = true;

   return;
}

//
// display the whole extent of the image to the source area
//
void pixq_PanePara::ShowWholeImage( void ) 
{   
   double dImageWidth = _pParent->getImageWidth();
   double dImageHeight = _pParent->getImageHeight();

   double dXTexCen = ( dImageWidth - 1.0 ) / 2.0;
   double dYTexCen = ( dImageHeight - 1.0 ) / 2.0;
   double dXImgRad = dImageWidth / 2.0;
   double dYImgRad = dImageHeight / 2.0;
   
   _dSrcX[0] = max( dXTexCen - dXImgRad, -0.5 );
   _dSrcX[1] = min( dXTexCen + dXImgRad, dImageWidth - 0.5 );
   _dSrcY[0] = max( dYTexCen - dYImgRad, -0.5 );
   _dSrcY[1] = min( dYTexCen + dYImgRad, dImageHeight - 0.5 );
   
   return;
}

//
// transform the shape of source area to be similar to the same
// aspect as the screen
//
void pixq_PanePara::setSingleViewports(void)
{
	double dDetX, dDetY, dX, dY, dLastX, dLastY, dRadiusX, dRadiusY;
   double dCutL, dCutR, dCutT, dCutB, dLastRadiusX, dLastRadiusY;
   double dLastImgX, dLastImgY, dLastImgL, dLastImgT;
   double dNewImageL, dNewImageR, dNewImageT, dNewImageB;
   double dLastX0, dLastX1, dLastY0, dLastY1;

   double dOrthoX0 = GetOrthoX( 0 );
   double dOrthoX1 = GetOrthoX( 1 );
   double dOrthoY0 = GetOrthoY( 0 );
   double dOrthoY1 = GetOrthoY( 1 );

   // --- last screen aspect ---

   dLastX0 = dOrthoX0;
   dLastX1 = dOrthoX1;
   dLastY0 = dOrthoY0;
   dLastY1 = dOrthoY1;
   
   dLastX = dLastX1 - dLastX0;
   dLastY = dLastY1 - dLastY0;

   // --- set current screen size ---

   dX = dOrthoX1 - dOrthoX0;
   dY = dOrthoY1 - dOrthoY0;
	if( 0.0 >= dX || 0.0 >= dY ) {
		goto PIX_EXIT;
	}

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

//
// reshape the source area of the image to be copied to be 
// geometrically similar to the destination
//
// notes:
// following members are set exclusively in this function
// _dScreenPosX[2]
// _dScreenPosY[2]
// _dTexCooX[2]
// _dTexCooY[2]
//
// following members are modified in this function
// _dSrcX[2]
// _dSrcY[2]
//
void pixq_PanePara::reshapeFlipSrcRect(void)
{
   double dX, dY, dRate, dImgCenter, dImgX, dImgY, dImgRate;
   double dOrtho, dDet;
   double dOrthoX[2], dOrthoY[2];

   double dOrthoX0 = GetOrthoX( 0 );
   double dOrthoX1 = GetOrthoX( 1 );
   double dOrthoY0 = GetOrthoY( 0 );
   double dOrthoY1 = GetOrthoY( 1 );

   double dImageWidth = _pParent->getImageWidth();
   double dImageHeight = _pParent->getImageHeight();

   // area in image to display on screen adjusted to match the shape of the screen ---
   // left and right position in pixels
   double dAdjustedSrcX[2];
   // top and bottom position in pixels
   double dAdjustedSrcY[2];

   // --- reshape the area, so that the displayed image area and ---
	// --- DC are geometrically similar ---

   switch( _sFileArea ) {
   case FlipAreaSingle:
   case FlipAreaLeft:
   case FlipAreaRight:
   case FlipAreaUpper:
   case FlipAreaLower:
      _dScreenPosX[0] = dOrthoX0;
      _dScreenPosX[1] = dOrthoX1;
      _dScreenPosY[0] = dOrthoY0;
      _dScreenPosY[1] = dOrthoY1;
      break;

   default:
      goto PIX_EXIT;
      break;
   }

   dOrthoX[0] = _dScreenPosX[0]; 
   dOrthoX[1] = _dScreenPosX[1];
   dOrthoY[0] = _dScreenPosY[0];
   dOrthoY[1] = _dScreenPosY[1];

   dX = dOrthoX[1] - dOrthoX[0];
   dY = dOrthoY[1] - dOrthoY[0];
	if( 0.0 >= dX || 0.0 >= dY ) {
      goto PIX_EXIT;
   }

	dRate = dY / dX;
   dImgX = _dSrcX[1] - _dSrcX[0];
   dImgY = _dSrcY[1] - _dSrcY[0];
	if( 0.0 >= dImgX || 0.0 >= dImgY ) {
      goto PIX_EXIT;
   }

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

	dAdjustedSrcX[0] = _dSrcX[0];
	dAdjustedSrcX[1] = _dSrcX[1];
	dAdjustedSrcY[0] = _dSrcY[0];
	dAdjustedSrcY[1] = _dSrcY[1];
      
   // --- do not allow src rectangle goes beyond the texture area --- 
   
   if( 0 > dAdjustedSrcY[0] ) {
      dDet = ( dOrthoY[1] - dOrthoY[0] ) / ( _dSrcY[1] - _dSrcY[0] );
      dOrtho = -_dSrcY[0] * dDet + dOrthoY[0];
      dAdjustedSrcY[0] = 0;
      _dScreenPosY[0] = dOrtho;
   } 
   
   if ( dAdjustedSrcY[1] >= dImageHeight ) {
      dDet = ( dOrthoY[1] - dOrthoY[0] ) / ( _dSrcY[1] - _dSrcY[0] );
      dOrtho = ( dImageHeight - 1 - _dSrcY[0] ) * dDet + dOrthoY[0];
      dAdjustedSrcY[1] = dImageHeight - 1;
      _dScreenPosY[1] = dOrtho;
   }

   if( 0 > dAdjustedSrcX[0] ) {
      dDet = ( dOrthoX[1] - dOrthoX[0] ) / ( _dSrcX[1] - _dSrcX[0] );
      dOrtho = -_dSrcX[0] * dDet + dOrthoX[0];
      dAdjustedSrcX[0] = 0;
      _dScreenPosX[0] = dOrtho; 
   } 
   
   if ( dAdjustedSrcX[1] >= dImageWidth ) {
      dDet = ( dOrthoX[1] - dOrthoX[0] ) / ( _dSrcX[1] - _dSrcX[0] );
      dOrtho = ( dImageWidth - 1 - _dSrcX[0] ) * dDet + dOrthoX[0];
      dAdjustedSrcX[1] = dImageWidth - 1;
      _dScreenPosX[1] = dOrtho;
   }

   // set the area on the texture to be copied to the screen(ortho)
   // non-normalized texture

   _dTexCooX[0] = dAdjustedSrcX[0];
   _dTexCooX[1] = dAdjustedSrcX[1];
   _dTexCooY[0] = dAdjustedSrcY[0];
   _dTexCooY[1] = dAdjustedSrcY[1];

   // --- set viewpoint <-> screen(ortho) <-> texture coordinate conversion ***

   SetSingleConversion( );

   // --- Done ---
PIX_EXIT:
	return;
}

void pixq_PanePara::resizeWindow(QSize rect)
{
   int k, nCurScreenHeight, nCurScreenWidth;
   double dCurSrcX[2], dCurSrcY[2], dCurOrthoX[2], dCurOrthoY[2];
   double dOrthoX[2], dOrthoY[2], dCenX, dCenY, dScaleX, dScaleY;
   double dCurSrcExtentX, dCurSrcExtentY;
   double dSrcExtentX, dSrcExtentY, dSrcRadiusX, dSrcRadiusY;
   double dCurOrthoExtentX, dCurOrthoExtentY;
   double dOrthoExtentX, dOrthoExtentY;

#ifdef _DEBUG
   static  int iCount = 0;
#endif // _DEBUG
   
   nCurScreenHeight = _nScreenHeight;
   nCurScreenWidth = _nScreenWidth;

   for (k = 0; k < 2; k++) {
      dCurSrcX[k] = _dSrcX[k];
      dCurSrcY[k] = _dSrcY[k];
      dCurOrthoX[k] = _dOrthoX[k];
      dCurOrthoY[k] = _dOrthoY[k];
   }
   
   // change the viewing area so that the center and the scale of the image remains same

   dCenX = ( dCurSrcX[0] + dCurSrcX[1] ) / 2.0;
   dCenY = (dCurSrcY[0] + dCurSrcY[1]) / 2.0;

   dCurSrcExtentX = dCurSrcX[1] - dCurSrcX[0];
   dCurSrcExtentY = dCurSrcY[1] - dCurSrcY[0];

   dCurOrthoExtentX = dCurOrthoX[1] - dCurOrthoX[0];
   dCurOrthoExtentY = dCurOrthoY[1] - dCurOrthoY[0];

   if (0.0 >= dCurSrcExtentX||  0.0 >= dCurSrcExtentY) {
      goto PIX_EXIT;
   }

   if (0.0 >= dCurOrthoExtentX || 0.0 >= dCurOrthoExtentY) {
      goto PIX_EXIT;
   }

   dScaleX = dCurOrthoExtentX / dCurSrcExtentX;
   dScaleY = dCurOrthoExtentY / dCurSrcExtentY;

   // set new windows size

   setFlipRatio(rect);

   for (k = 0; k < 2; k++) {
      dOrthoX[k] = _dOrthoX[k];
      dOrthoY[k] = _dOrthoY[k];
   }

   dOrthoExtentX = dOrthoX[1] - dOrthoX[0];
   dOrthoExtentY = dOrthoY[1] - dOrthoY[0];
   
   dSrcExtentX = dOrthoExtentX / dScaleX;
   dSrcExtentY = dOrthoExtentY / dScaleY;

   dSrcRadiusX = dSrcExtentX / 2.0;
   dSrcRadiusY = dSrcExtentY / 2.0;

   dCurSrcX[0] = dCenX - dSrcRadiusX;
   dCurSrcX[1] = dCenX + dSrcRadiusX;
   dCurSrcY[0] = dCenY - dSrcRadiusY;
   dCurSrcY[1] = dCenY + dSrcRadiusY;

   for (k = 0; k < 2; k++) {
      _dSrcX[k] = dCurSrcX[k];
      _dSrcY[k] = dCurSrcY[k];
   }

   //setPaneViewports();

   reshapeFlipSrcRect();

   // show the scale and cente

#ifdef _DEBUG
   dCenX = (_dSrcX[0] + _dSrcX[1]) / 2.0;
   dCenY = (_dSrcY[0] + _dSrcY[1]) / 2.0;
   
   dScaleX = (_dOrthoX[1] - _dOrthoX[0]) / (_dSrcX[1] - _dSrcX[0]);
   dScaleY = (_dOrthoY[1] - _dOrthoY[0]) / (_dSrcY[1] - _dSrcY[0]);

   fprintf( stdout, "resizeWin [%1d]: Cen(%8.2f,%8.2f) Scale (%7.3f,%7.3f) %4d.\n",
      _sFileArea, dCenX, dCenY, dScaleX, dScaleY, iCount);
   iCount++;
#endif // _DEBUG

PIX_EXIT:
   return;
}

//
// set conversion parameters between viewpoint <-> screen(ortho) <-> texture coordinate
//
// ortho.x = _dVpXDet[k] * ( screen.x - _dVpXShift[k] )
// ortho.y = _dVpYDet[k] * ( screen.y - _dVpYShift[k] )
//
void pixq_PanePara::SetSingleConversion( void )
{
   int nScreenWidth, nScreenHeight;
   double dXDet, dYDet, dXShift, dYShift, dX, dY, dTexXSize, dTexYSize;

   double dOrthoX0 = GetOrthoX( 0 );
   double dOrthoX1 = GetOrthoX( 1 );
   double dOrthoY0 = GetOrthoY( 0 );
   double dOrthoY1 = GetOrthoY( 1 );

   // screen(ortho) coo <--> texture geometric conversion parameters

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

   // viewport <--> screen(Ortho) geometric conversion parameters

   nScreenWidth = _nDoubleVPXEnd - _nDoubleVPXCoo;
   nScreenHeight = _nDoubleVPYEnd - _nDoubleVPYCoo;  
   dX = dOrthoX1 - dOrthoX0;
   dY = dOrthoY1 - dOrthoY0;

   dXDet = dX / (double)nScreenWidth;
   dYDet = dY / (double)nScreenHeight;

   dXShift = _nDoubleVPXCoo - dOrthoX0 / dXDet;
   dYShift = _nDoubleVPYCoo - dOrthoY0 / dYDet;

   _dVpXDet = dXDet;
   _dVpYDet = dYDet;
   _dVpXShift = dXShift;
   _dVpYShift = dYShift;

   // viewport <--> texture geometric conversion parameters
   
   if( _bTexDet ) {
      _dVpXTexDet = _dTexXDet * _dVpXDet;
      _dVpYTexDet = _dTexYDet * _dVpYDet;

      _dVpXTexShift = _dTexXDet * ( _dVpXDet * _dVpXShift + _dTexXShift );
      _dVpYTexShift = _dTexYDet * ( _dVpYDet * _dVpYShift + _dTexYShift );
   } else {
      _dVpXTexDet = 0.0;
      _dVpYTexDet = 0.0;

      _dVpXTexShift = 0.0;
      _dVpYTexShift = 0.0;
   }

   return;
}
