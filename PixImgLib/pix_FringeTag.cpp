#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_FringeTag.h"

//
// get resample rate for the pyramid level
//
int pixq_FringeTag::resampleRateForPyramid(int iLevel) // [i] pyramid level
{
   int iResample = 1;

   switch( iLevel ) {
   case 0: 
      iResample= 1;
      break;
   case 1:
      iResample= 2;
      break;
   case 2:
      iResample= 4;
      break;
   case 3:
      iResample= 8;
      break;
   case 4:
      iResample= 16;
      break;
   default: 
      iResample = 1;
      break;
   }

   return iResample;
}

pixq_FringeTag::pixq_FringeTag(void)
{
   init( );

   return;
}

pixq_FringeTag::~pixq_FringeTag(void)
{
   ; // empty

   return;
}

void pixq_FringeTag::init(void)
{
   int k;

   _iFringeTagX = 0;
   _iFringeTagY = 0;

   for( k = 0 ; k < _nMaxPyramidLevel ; k++ ) {
      _iLevelFringeTagX[k] = 0;
      _iLevelFringeTagY[k] = 0;
   }

   _iRedFringeX = 0;
   _iRedFringeY = 0;

   _iGrnFringeX = 0;
   _iGrnFringeY = 0;

   _iBluFringeX = 0;
   _iBluFringeY = 0;

   _iRightTagX = 0;
   _iRightTagY = 0;

   for( k = 0 ; k < _nMaxPyramidLevel ; k++ ) {
      _iLevelRightTagX[k] = 0;
      _iLevelRightTagY[k] = 0;
   }

   _dMaxCorrRed = 0.0;
   _dMaxCorrGrn = 0.0;
   _dMaxCorrBlu = 0.0;

   _cRefColor = 0;

   _bUsed = false;
   _bSelected = false;

   _dCorrVal = 0.0;
   _usCorrStatus = CorrMatchTypeUnknown;

   _bRotOutlier = false;

   return;
}

//
// copy constructor
//
pixq_FringeTag &pixq_FringeTag::operator=(const pixq_FringeTag &that)
{
   int k;

   // tag position to measure color displacement

   _iTagID = that._iTagID;

   _iFringeTagX = that._iFringeTagX;
   _iFringeTagY = that._iFringeTagY;

   _iFringeTagOriginalX = that._iFringeTagOriginalX;
   _iFringeTagOriginalY = that._iFringeTagOriginalY;

   for( k = 0 ; k < _nMaxPyramidLevel ; k++ ) {
      _iLevelFringeTagX[k] = that._iLevelFringeTagX[k];
      _iLevelFringeTagY[k] = that._iLevelFringeTagY[k];
   }

   _iRedFringeX = that._iRedFringeX;
   _iRedFringeY = that._iRedFringeY;
                        
   _iGrnFringeX = that._iGrnFringeX;
   _iGrnFringeY = that._iGrnFringeY;
                        
   _iBluFringeX = that._iBluFringeX;
   _iBluFringeY = that._iBluFringeY;
   
   _iRightTagX = that._iRightTagX;
   _iRightTagY = that._iRightTagY;

   for( k = 0 ; k < _nMaxPyramidLevel ; k++ ) {
      _iLevelRightTagX[k] = that._iLevelRightTagX[k];
      _iLevelRightTagY[k] = that._iLevelRightTagY[k];
   }

   _dMaxCorrRed = that._dMaxCorrRed;
   _dMaxCorrGrn = that._dMaxCorrGrn;
   _dMaxCorrBlu = that._dMaxCorrBlu;

   _cRefColor =  that._cRefColor;
   _bUsed     =  that._bUsed;
   _bSelected =  that._bSelected;

   _dCorrVal     =  that._dCorrVal;
   _usCorrStatus =  that._usCorrStatus;

   _bRotOutlier =  that._bRotOutlier;

   _iHorDisparity = that._iHorDisparity;
   _iVerDisparity = that._iVerDisparity;

   // original values

   _iRightTagOriginalX = that._iRightTagOriginalX;
   _iRightTagOriginalY = that._iRightTagOriginalY;
   _dCorrOriginalVal = that._dCorrOriginalVal;
   _usOriginalCorrStatus = that._usOriginalCorrStatus;

   // --- Done ---
	return *this;
}

QString pixq_FringeTag::getMatchStatusString(unsigned short usStatus)
{
   QString strStatus;

   switch( usStatus ) {
   case pixq_FringeTag::CorrMatchTypeUnknown:
      strStatus = "***";
      break;
   case pixq_FringeTag::CorrMatchTypeNotAnalyzed:
      strStatus = "N/A";
      break;
   case pixq_FringeTag::CorrMatchTypeLowTex:
      strStatus = "Poor";
      break;
   case pixq_FringeTag::CorrMatchTypeCorrLow:
      strStatus = "Low";
      break;
   case pixq_FringeTag::CorrMatchTypeCorrHigh:
      strStatus = "High";
      break;
   case pixq_FringeTag::CorrMatchTypeOutlier:
      strStatus = "Outlier";
      break;
   default:
      strStatus = "???";
      break;
   }

   return strStatus;
}

QString pixq_FringeTag::getMatchStatusString(void)
{
   QString strStatus = getMatchStatusString(_usCorrStatus);

   return strStatus;
}

//
// set discplacement in red channel coordinate
//
void pixq_FringeTag::SetRedFringe(int iX, int iY)
{
   SetRedFringe( iX, iY, 0.0 );

   return;
}

void pixq_FringeTag::SetRedFringe(int iX, int iY, double dCorr)
{
   _iRedFringeX = iX;
   _iRedFringeY = iY;
   _dMaxCorrRed = dCorr;

   return;
}

//
// set discplacement in red channel coordinate
//
void pixq_FringeTag::SetGreenFringe(int iX, int iY)
{
   SetGreenFringe(iX, iY, 0.0);

   return;
}

void pixq_FringeTag::SetGreenFringe(int iX, int iY, double dCorr)
{
   _iGrnFringeX = iX;
   _iGrnFringeY = iY;
   _dMaxCorrGrn = dCorr;

   return;
}

//
// set discplacement in blue channel coordinate
//

void pixq_FringeTag::SetBlueFringe(int iX, int iY)
{
   SetBlueFringe(iX, iY, 0.0);

   return;
}

void pixq_FringeTag::SetBlueFringe(int iX, int iY, double dCorr)
{
   _iBluFringeX = iX;
   _iBluFringeY = iY;
   _dMaxCorrBlu = dCorr;

   return;
}

//
// get color displacement for the color
//
int pixq_FringeTag::getColorFringeX(int iColor) // [i] 0:red, 1:green, 2:blue
{
   int iX;

   switch( iColor ) {
   case 0:
      iX = _iRedFringeX;
      break;

   case 1:
      iX = _iGrnFringeX;
      break;
      
   case 2:
   default:
      iX = _iBluFringeX;
      break;
   }

   return iX;
}

int pixq_FringeTag::getColorFringeY(int iColor) // [i] 0:red, 1:green, 2:blue
{
   int iY;

   switch( iColor ) {
   case 0:
      iY = _iRedFringeY;
      break;

   case 1:
      iY = _iGrnFringeY;
      break;
      
   case 2:
   default:
      iY = _iBluFringeY;
      break;
   }

   return iY;
}

//
// from the tag positions at the original scale
// get positon at higher pyramid levels
//
void pixq_FringeTag::setLevelTags(void)
{
   int k, nLevels, iX, iY;
   int iPixX = getXTag();
   int iPixY = getYTag();
   double dPyramidScales, dX, dY;

   // set tag positions at lower pyramid levels

   nLevels = pixq_FringeTag::nMaxPyramidLevel();
   for( k = 0 ; k < nLevels ; k++ ) {
      dPyramidScales = (double)resampleRateForPyramid(k);
      dX = (double)iPixX / dPyramidScales;
      dY = (double)iPixY / dPyramidScales;
      iX = (int)floor( 0.5 + dX );
      iY = (int)floor( 0.5 + dY );
      setLevelTag(k, iX, iY);

      // set the right (matched)tag position as the input position
      // this is actually, only used at the first level

      iX = getLevelTagX(k);
      iY = getLevelTagY(k);
      setRightLevelTag(k, iX, iY);
   }

   return;
}
