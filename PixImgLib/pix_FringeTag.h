#pragma once

namespace _pix_plot_img_framework {

#include <piximglib_global.h>

//
// tag point to analyze the color fringing
// tag point to analyze the stereo correspondance
// 

class PIXIMGLIB_EXPORT pixq_FringeTag
{
public:
   // type of grid points classified by correlation results
   enum {
      // unknown
      CorrMatchTypeUnknown = 0,
      // not matched yet
      CorrMatchTypeNotAnalyzed,
      // low deviation = not enough texture
      CorrMatchTypeLowTex,
      // correlation low
      CorrMatchTypeCorrLow, 
      // correlation high
      CorrMatchTypeCorrHigh,
      // outlier
      CorrMatchTypeOutlier,
   } CorrMatchTypes;

public:
   pixq_FringeTag(void);
   ~pixq_FringeTag(void);

   // copy constructor
   pixq_FringeTag &operator=(const pixq_FringeTag &that);

   static int nMaxPyramidLevel( void ) { return _nMaxPyramidLevel; }

public:
   static const int _nMaxPyramidLevel = 4;

private:
   int _iTagID;

   // tag position to measure color displacement
   // or left coordinate in stereo correspondance
   int _iFringeTagX;
   int _iFringeTagY;

   // tag coordinate, original, used to save the original value during interactive editing
   int _iFringeTagOriginalX;
   int _iFringeTagOriginalY;

   // tag positions for lower pyramid level
   int _iLevelFringeTagX[_nMaxPyramidLevel];
   int _iLevelFringeTagY[_nMaxPyramidLevel];

   // color displacement at this point for red channel, in pixels
   int _iRedFringeX;
   int _iRedFringeY;

   // color displacement at this point for green channel, in pixels
   int _iGrnFringeX;
   int _iGrnFringeY;

   // color displacement at this point for vlue channel, in pixels
   int _iBluFringeX;
   int _iBluFringeY;

   // right coordinate in stereo correspondance
   int _iRightTagX;
   int _iRightTagY;

   // matched tag positions for lower pyramid level
   int _iLevelRightTagX[_nMaxPyramidLevel];
   int _iLevelRightTagY[_nMaxPyramidLevel];

   // max correlation used to determine the displacement in each color
   double _dMaxCorrRed;
   double _dMaxCorrGrn;
   double _dMaxCorrBlu;

   // reference channel used, 0=red, 1=green, 2=blue
   char _cRefColor;

   // whether this poins should be used in displacement
   bool _bUsed;

   // this tags is currently selected
   bool _bSelected;

   // grid correlation, -1...1, grayscale
   double _dCorrVal; 

   // grid type by correlation results, one of CorrMatchTypes
   unsigned short _usCorrStatus; 

   // disparities

   int _iHorDisparity;
   int _iVerDisparity;

   // right coordinate, original, used to save the original value during interactive editing
   int _iRightTagOriginalX;
   int _iRightTagOriginalY;

   double _dCorrOriginalVal; 
   unsigned short _usOriginalCorrStatus; 

   // outliers?
   // get the result from OpenCV rotation matrix computation

   bool _bRotOutlier;

public:
   static int resampleRateForPyramid( int iLevel );

   // initialize parameters
   void init( void );

   void setTagID( int iID ) { _iTagID = iID; }
   int getTagID(void) { return _iTagID; }

   // set tag coordinate

   int getXTag( void ) const { return _iFringeTagX; }
   int getYTag(void) const { return _iFringeTagY; }

   int getTagOriginalX(void) { return _iFringeTagOriginalX; }
   int getTagOriginalY(void) { return _iFringeTagOriginalY; }

   void setXTag( int iTagX ) { _iFringeTagX = iTagX; }
   void setYTag(int iTagY) { _iFringeTagY = iTagY; }

   void setTag( int iTagX, int iTagY ) {
      setXTag(iTagX);
      setYTag(iTagY);
   }

   void shiftXTag( int iShift ) { 
      _iFringeTagX = _iFringeTagX + iShift;
   }

   void shiftYTag( int iShift ) { 
      _iFringeTagY = _iFringeTagY + iShift;
   }

   void shiftTag( int iShiftX, int iShiftY ) { 
      shiftXTag(iShiftX);
      shiftYTag(iShiftY);
      setDisparity();
   }

   //
   
   int getLevelTagX( int iLevel ) const { return _iLevelFringeTagX[iLevel]; }
   int getLevelTagY(int iLevel) const { return _iLevelFringeTagY[iLevel]; }

   void setXLevelTag( int iLevel, int iTagX ) { _iLevelFringeTagX[iLevel] = iTagX; }
   void setYLevelTag( int iLevel, int iTagY ) { _iLevelFringeTagY[iLevel] = iTagY; }

   void setLevelTag( int iLevel, int iTagX, int iTagY ) {
      setXLevelTag( iLevel, iTagX );
      setYLevelTag( iLevel, iTagY );
   }

   //

   int getRightXTag(void) { return _iRightTagX; }
   int getRightYTag(void) { return _iRightTagY; }

   int getRightTagOriginalX( void ) { return _iRightTagOriginalX; }
   int getRightTagOriginalY(void) { return _iRightTagOriginalY; }

   //

   void setRightXTag(int iTagX) { _iRightTagX = iTagX; }
   void setRightYTag(int iTagY) { _iRightTagY = iTagY; }

   void setRightTag(int iTagX, int iTagY) {
      setRightXTag(iTagX);
      setRightYTag( iTagY );
   }
   
   // original position

   void storeOriginalPosition( void ) {
      _iFringeTagOriginalX = _iFringeTagX;
      _iFringeTagOriginalY = _iFringeTagY;
      _iRightTagOriginalX = _iRightTagX;
      _iRightTagOriginalY = _iRightTagY;
      setDisparity();
      _dCorrOriginalVal = _dCorrVal;
      _usOriginalCorrStatus = _usCorrStatus;
   }

   void restoreOriginalTag( void ) { 
      _iFringeTagX = _iFringeTagOriginalX;
      _iFringeTagY = _iFringeTagOriginalY;
      setDisparity();
      //_dCorrVal = _dCorrOriginalVal;
      //_usCorrStatus = _usOriginalCorrStatus;
   }

   void restoreRightOriginalTag( void ) { 
      _iRightTagX = _iRightTagOriginalX;
      _iRightTagY = _iRightTagOriginalY;
      setDisparity();
      //_dCorrVal = _dCorrOriginalVal;
      //_usCorrStatus = _usOriginalCorrStatus;
   }

   // shift

   void shiftRightXTag(int iShift) {
      _iRightTagX = _iRightTagX + iShift;
   }

   void shiftRightYTag(int iShift) {
      _iRightTagY = _iRightTagY + iShift;
   }

   void shiftRightTag(int iShiftX, int iShiftY) {
      shiftRightXTag(iShiftX);
      shiftRightYTag(iShiftY);
      setDisparity();
   }

   //

   int getLevelRightTagX( int iLevel ) { return _iLevelRightTagX[iLevel]; }
   int getLevelRightTagY(int iLevel) { return _iLevelRightTagY[iLevel]; }

   void setRightXLevelTag(int iLevel, int iTagX) { _iLevelRightTagX[iLevel] = iTagX; }
   void setRightYLevelTag(int iLevel, int iTagY) { _iLevelRightTagY[iLevel] = iTagY; }

   void setRightLevelTag(int iLevel, int iTagX, int iTagY) {
      setRightXLevelTag(iLevel, iTagX);
      setRightYLevelTag(iLevel, iTagY);
   }

   //

   int GetHorDisparity( void ) const { return _iHorDisparity; }
   int GetVerDisparity( void ) const { return _iVerDisparity; }

   void setDisparity(void) {
      _iHorDisparity = _iRightTagX - _iFringeTagX;
      _iVerDisparity = _iRightTagY - _iFringeTagY;
   }

   void SetHorDisparity( int iHorDisparity ) { _iHorDisparity = iHorDisparity; }
   void SetVerDisparity( int iVerDisparity ) { _iVerDisparity = iVerDisparity; }

   // set discplacement in red channel coordinate
   void SetRedFringe( int iX, int iY );
   void SetRedFringe( int iX, int iY, double dCorr );
   
   // set discplacement in green channel coordinate
   void SetGreenFringe( int iX, int iY );
   void SetGreenFringe( int iX, int iY, double dCorr );
   
   // set discplacement in blue channel coordinate
   void SetBlueFringe( int iX, int iY );
   void SetBlueFringe( int iX, int iY, double dCorr );
   
   // get color displacement for the color
   int getColorFringeX(int iColor);
   int getColorFringeY(int iColor);

   // set ref color
   void SetRefColor( char cColor ) { _cRefColor = cColor; }
   char GetRefColor( void ) { return _cRefColor; }

   void setUsed(bool bUsed) { _bUsed = bUsed; }
   bool getUsed( void ) { return _bUsed; }
   void FlipUsed( void ) { _bUsed = !_bUsed; }

   void SetSelected( bool bSelected ) { _bSelected = bSelected; }
   bool getSelected(void) { return _bSelected; }
   void FlipSelection( void ) { _bSelected = !_bSelected; }
   
   // grid correlation, -1...1, grayscale
   
   void SetCorrVal( double dCorr ) { _dCorrVal = dCorr; }
   double getCorrVal(void) { return _dCorrVal; }

   // 
   void SetRotOutlier( bool bRotOutlier ) { _bRotOutlier = bRotOutlier; }
   bool GetRotOutlier( void ) const { return _bRotOutlier; }

   void SetCorrOriginalVal( double dCorr ) { _dCorrOriginalVal = dCorr; }
   double GetCorrOriginalVal( void ) { return _dCorrOriginalVal; }

   // grid type by correlation results, one of CorrMatchTypes
   
   void setCorrStatus(unsigned short usCorrTypeMtx) { _usCorrStatus = usCorrTypeMtx; }
   unsigned short getCorrStatus(void) const { return _usCorrStatus; }

   static QString getMatchStatusString( unsigned short usStatus );
   QString getMatchStatusString(void);

   void setLevelTags( void );

};

} // namespace _pix_plot_img_framework
