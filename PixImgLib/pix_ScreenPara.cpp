#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_FlipPara.h"
#include "pix_ScreenPara.h"

pixq_ScreenPara::pixq_ScreenPara(void)
{
   _sScreenInit = (short)PixPaneShowNone;

   // whole pane as single flip area
   _pSingleFlip = new pixq_PanePara( pixq_PanePara::FlipAreaSingle );
   
   // vetcial split area
   _pLeftFlip = new pixq_PanePara( pixq_PanePara::FlipAreaLeft );
   _pRightFlip = new pixq_PanePara( pixq_PanePara::FlipAreaRight );

   // horizontal split area
   _pLowerFlip = new pixq_PanePara( pixq_PanePara::FlipAreaLower );
   _pUpperFlip = new pixq_PanePara( pixq_PanePara::FlipAreaUpper );

   // set itself as parent

   _pSingleFlip->StoreParent( (pixq_ScreenPara*)this );
   _pLeftFlip->StoreParent( (pixq_ScreenPara*)this );
   _pRightFlip->StoreParent( (pixq_ScreenPara*)this );
   _pLowerFlip->StoreParent( (pixq_ScreenPara*)this );
   _pUpperFlip->StoreParent( (pixq_ScreenPara*)this );
   
   _bLocked = false;

   return;
}

pixq_ScreenPara::~pixq_ScreenPara(void)
{
   if( NULL != _pSingleFlip ) {
      delete _pSingleFlip;
      _pSingleFlip = NULL;
   }
   
   if( NULL != _pLeftFlip ) {
      delete _pLeftFlip;
      _pLeftFlip = NULL;
   }
   
   if( NULL != _pRightFlip ) {
      delete _pRightFlip;
      _pRightFlip = NULL;
   }

   if( NULL != _pLowerFlip ) {
      delete _pLowerFlip;
      _pLowerFlip = NULL;
   }
   
   if( NULL != _pUpperFlip ) {
      delete _pUpperFlip;
      _pUpperFlip = NULL;
   }

   return;
}

void pixq_ScreenPara::DeInit( void )
{
   _dImageWidth = -1.0;
   _dImageHeight = -1.0;

   _pSingleFlip->DeInit( );
   _pLeftFlip->DeInit( );
   _pRightFlip->DeInit( );
   _pLowerFlip->DeInit( );
   _pUpperFlip->DeInit( );

   _sScreenInit = (short)PixPaneShowNone;

   return;
}

bool pixq_ScreenPara::getWholeExtent(void) const
{
   return _pSingleFlip->getWholeExtent();
}

//
// _dOrthoX, _dOrthoX can only be set in here!
//
// set
// _nScreenWidth
// _nScreenHeight
// _dOrthoX[2]
// _dOrthoY[2]
//
void pixq_ScreenPara::setFlipRatio(QSize rect)
{
   short sAreaType = _sScreenInit;
   setFlipRatio(sAreaType, rect.width(), rect.height());

   return;
}

void pixq_ScreenPara::setFlipRatio(short sAreaType, // [i] one of PixPaneShowMode
                                   QSize rect )
{
   setFlipRatio(sAreaType, rect.width(), rect.height());

   return;
}

void pixq_ScreenPara::setFlipRatio(short sAreaType, // [i] one of PixPaneShowMode
                                   int nScreenWidth,
                                   int nScreenHeight )
{
   _sScreenInit = sAreaType;

   switch( _sScreenInit ) {
   case PixPaneShowFirst:
   case PixPaneShowSecond:
   case PixPaneShowWiper:
   case PixPaneShowInBox:
   case PixPaneShowOutBox:
      _pSingleFlip->setFlipRatio(nScreenWidth, nScreenHeight);
      break;
      
   case PixPaneShowHorizontalSplit:
      // Never do this!
      //_pSingleFlip->setFlipRatio( nScreenWidth, nScreenHeight );
      if (!_pSingleFlip->getTexDet()) {
         _pSingleFlip->setFlipRatio(nScreenWidth, nScreenHeight);
      }
      _pLeftFlip->setFlipRatio(nScreenWidth, nScreenHeight);
      _pRightFlip->setFlipRatio(nScreenWidth, nScreenHeight);
      break;

   case PixPaneShowVerticalSplit:
      // Never do this!
      //_pSingleFlip->setFlipRatio( nScreenWidth, nScreenHeight );
      if (!_pSingleFlip->getTexDet()) {
         _pSingleFlip->setFlipRatio(nScreenWidth, nScreenHeight);
      }
      _pLowerFlip->setFlipRatio(nScreenWidth, nScreenHeight);
      _pUpperFlip->setFlipRatio(nScreenWidth, nScreenHeight);
      break;

   case PixPaneShowNone:
   default:
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

void pixq_ScreenPara::InitFlip( int nImgWidth, // [i] image width, -1 if same as texture
                               int nImgHeight ) // [i] image height, -1 if same as texture
{
   if( 0 < _dImageWidth ) {
      return;
   }

   _dImageWidth  = (double)nImgWidth;
   _dImageHeight = (double)nImgHeight;

   _dCenterStep = 0.01;
   _dZViewStep = 0.01;
   
   switch( _sScreenInit ) {
   case PixPaneShowFirst:
   case PixPaneShowSecond:
   case PixPaneShowWiper:
   case PixPaneShowInBox:
   case PixPaneShowOutBox:
      _pSingleFlip->InitFlip( );
      break;
      
   case PixPaneShowHorizontalSplit:
      _pSingleFlip->InitFlip( );
      _pLeftFlip->InitFlip( );
      _pRightFlip->InitFlip( );
      break;

   case PixPaneShowVerticalSplit:
      _pSingleFlip->InitFlip( );
      _pLowerFlip->InitFlip( );
      _pUpperFlip->InitFlip( );
      break;

   case PixPaneShowNone:
   default:
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

//
// reshape the image source area
// according to the shape of the pane(to be similar)
//
void pixq_ScreenPara::setSingleViewports(void)
{
   switch( _sScreenInit ) {
   case PixPaneShowFirst:
   case PixPaneShowSecond:
   case PixPaneShowWiper:
   case PixPaneShowInBox:
   case PixPaneShowOutBox:
      _pSingleFlip->setSingleViewports();
      break;
      
   case PixPaneShowHorizontalSplit:
      _pLeftFlip->setSingleViewports();
      _pRightFlip->setSingleViewports();
      break;

   case PixPaneShowVerticalSplit:
      _pLowerFlip->setSingleViewports();
      _pUpperFlip->setSingleViewports();
      break;

   case PixPaneShowNone:
   default:
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

void pixq_ScreenPara::SetSingleConversion( void )
{
   switch( _sScreenInit ) {
   case PixPaneShowFirst:
   case PixPaneShowSecond:
   case PixPaneShowWiper:
   case PixPaneShowInBox:
   case PixPaneShowOutBox:
      _pSingleFlip->SetSingleConversion( );
      break;
      
   case PixPaneShowHorizontalSplit:
      _pLeftFlip->SetSingleConversion( );
      _pRightFlip->SetSingleConversion( );
      break;

   case PixPaneShowVerticalSplit:
      _pLowerFlip->SetSingleConversion( );
      _pUpperFlip->SetSingleConversion( );
      break;

   case PixPaneShowNone:
   default:
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

void pixq_ScreenPara::zViewShift(int iZShift)
{
   int k, nPanes;
   double dCurSrcX[2], dCurSrcY[2];
   pixq_PanePara *pCurPara;
   pixq_PanePara *pNewPara[4];

   //
   // change the single flip
   //

   _pSingleFlip->zViewShift(iZShift);

   pCurPara = getSingleFlip();
   for( k = 0 ; k < 2 ; k++ ) {
      dCurSrcX[k] = pCurPara->GetSrcX( k );
      dCurSrcY[k] = pCurPara->GetSrcY( k );
   }

   // then apply it to vertical/horizontal panes

   nPanes = 4;
   pNewPara[0] = getLeftFlip();
   pNewPara[1] = getRightFlip();
   pNewPara[2] = getUpperFlip();
   pNewPara[3] = getLowerFlip();

   for( k = 0 ; k < nPanes ; k++ ) {
      pNewPara[k]->CopySrc( dCurSrcX, dCurSrcY );
      //pNewPara[k]->setSingleViewports( );
      //pNewPara[k]->SetSingleConversion( );
   }

//PIX_EXIT: 
   return;
}

void pixq_ScreenPara::XYViewStep( int iXShift, int iYShift )
{
   int k, nPanes;
   double dCurSrcX[2], dCurSrcY[2];
   pixq_PanePara *pCurPara;
   pixq_PanePara *pNewPara[4];

   //
   // change the single flip
   //
   
   _pSingleFlip->XYViewStep( iXShift, iYShift );

   pCurPara = getSingleFlip();
   for( k = 0 ; k < 2 ; k++ ) {
      dCurSrcX[k] = pCurPara->GetSrcX( k );
      dCurSrcY[k] = pCurPara->GetSrcY( k );
   }

   // then apply it to vertical/horizontal panes

   nPanes = 4;
   pNewPara[0] = getLeftFlip();
   pNewPara[1] = getRightFlip();
   pNewPara[2] = getUpperFlip();
   pNewPara[3] = getLowerFlip();

   for( k = 0 ; k < nPanes ; k++ ) {
      pNewPara[k]->CopySrc( dCurSrcX, dCurSrcY );
      //pNewPara[k]->setSingleViewports( );
      //pNewPara[k]->SetSingleConversion( );
   }

//PIX_EXIT: 
   return;
}

void pixq_ScreenPara::XYViewShift( int iXShift, int iYShift )
{
   int k, nPanes;
   double dCurSrcX[2], dCurSrcY[2];
   pixq_PanePara *pCurPara;
   pixq_PanePara *pNewPara[4];

   //
   // change the single flip
   //

   _pSingleFlip->XYViewShift( iXShift, iYShift );

   pCurPara = getSingleFlip();
   for( k = 0 ; k < 2 ; k++ ) {
      dCurSrcX[k] = pCurPara->GetSrcX( k );
      dCurSrcY[k] = pCurPara->GetSrcY( k );
   }

   // then apply it to vertical/horizontal panes

   nPanes = 4;
   pNewPara[0] = getLeftFlip();
   pNewPara[1] = getRightFlip();
   pNewPara[2] = getUpperFlip();
   pNewPara[3] = getLowerFlip();

   for( k = 0 ; k < nPanes ; k++ ) {
      pNewPara[k]->CopySrc( dCurSrcX, dCurSrcY );
      //pNewPara[k]->setSingleViewports( );
      //pNewPara[k]->SetSingleConversion( );
   }

//PIX_EXIT: 
   return;
}

//
// display the whole extent of the image to the source area
//
void pixq_ScreenPara::flipRecenter(void)
{   
   _pSingleFlip->flipRecenter();
   _pLeftFlip->flipRecenter();
   _pRightFlip->flipRecenter();
   _pLowerFlip->flipRecenter();
   _pUpperFlip->flipRecenter();

   return;
}

//
// display the area centered at given point
// at the same scale
//
void pixq_ScreenPara::JumpToPoint(int iX, int iY)
{
   _pSingleFlip->JumpToPoint(iX, iY);
   _pLeftFlip->JumpToPoint(iX, iY);
   _pRightFlip->JumpToPoint(iX, iY);
   _pLowerFlip->JumpToPoint(iX, iY);
   _pUpperFlip->JumpToPoint(iX, iY);

   return;
}

void pixq_ScreenPara::JumpToPoint(double dX, double dY)
{
   _pSingleFlip->JumpToPoint(dX, dY);
   _pLeftFlip->JumpToPoint(dX, dY);
   _pRightFlip->JumpToPoint(dX, dY);
   _pLowerFlip->JumpToPoint(dX, dY);
   _pUpperFlip->JumpToPoint(dX, dY);

   return;
}

void pixq_ScreenPara::viewOneToOne(void)
{  
   _pSingleFlip->viewOneToOne();
   _pLeftFlip->viewOneToOne();
   _pRightFlip->viewOneToOne();
   _pLowerFlip->viewOneToOne();
   _pUpperFlip->viewOneToOne();

   return;
}

void pixq_ScreenPara::resizeWindow(QSize rect)
{
   short sCurrentArea = _sScreenInit;

   if (getWholeExtent()) {
      setFlipRatio(rect);
      flipRecenter();
      setSingleViewports();
      // this is called within SetSingleViewports
      //SetSingleConversion();
      goto PIX_EXIT;
   }

   switch (sCurrentArea) {
   case PixPaneShowFirst:
   case PixPaneShowSecond:
   case PixPaneShowWiper:
   case PixPaneShowInBox:
   case PixPaneShowOutBox:
      _pSingleFlip->resizeWindow(rect);
      break;

   case PixPaneShowHorizontalSplit:
      //_pSingleFlip->resizeWindow( rect );
      _pLeftFlip->resizeWindow(rect);
      _pRightFlip->resizeWindow(rect);
      break;

   case PixPaneShowVerticalSplit:
      //_pSingleFlip->resizeWindow( rect );
      _pLowerFlip->resizeWindow(rect);
      _pUpperFlip->resizeWindow(rect);
      break;

   case PixPaneShowNone:
   default:
      goto PIX_EXIT;
      break;
   }   
   
PIX_EXIT:
   return;
}

void pixq_ScreenPara::SwitchAreaType( short sNewArea, QSize rect )
{
   short sCurrentArea = _sScreenInit;

   // need conversion?

   switch( sCurrentArea ) {
   case PixPaneShowFirst:
   case PixPaneShowSecond:
   case PixPaneShowWiper:
   case PixPaneShowInBox:
   case PixPaneShowOutBox:
      switch( sNewArea ) {
      case PixPaneShowFirst:
      case PixPaneShowSecond:
      case PixPaneShowWiper:
      case PixPaneShowInBox:
      case PixPaneShowOutBox:
         goto PIX_EXIT;
         break;
      }
      break;
      
   case PixPaneShowHorizontalSplit:
   case PixPaneShowVerticalSplit:
      if( sCurrentArea == sNewArea ) {
         goto PIX_EXIT;
      }
      break;

   case PixPaneShowNone:
   default:
      goto PIX_EXIT;
      break;
   }

   if (PixPaneShowNone == sNewArea) {
      goto PIX_EXIT;
   }

   // show whole image

   if (getWholeExtent()) {
      // nothing to do
      setFlipRatio(sNewArea, rect);
      flipRecenter();
      setSingleViewports();
      SetSingleConversion( );
      goto PIX_EXIT;
   }

   //

   setFlipRatio(sNewArea, rect);
   setSingleViewports();
   SetSingleConversion( );

PIX_EXIT:
   return;
}
