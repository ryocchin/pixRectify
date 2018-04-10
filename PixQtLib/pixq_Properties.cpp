#include <pixqt_common.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include <limits.h>
#include <signal.h>
#include <stddef.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_EnvItem.h"
#include "pixq_Properties.h"

pixq_Properties::pixq_Properties(void)
{
   ; // empty
}

pixq_Properties::~pixq_Properties(void)
{
   ; // empty
}

void pixq_Properties::initAllEnv(void)
{
   initDftFilter();

   // Common

   initCommon();
   initImage();
   initCompare();
   initSystem();

   // Scope

   initScope();

   // Colomari

   initColomari();

   // Rectification

   initPntRectify();
   initCvRectify();
   initMatch(); 
   initStereoView();
   
   // Ortho

   initOrtho();

   return;
}
 
void pixq_Properties::initEnv(QString strOrg, QString strApp)
{
   initAllEnv();
   
   // set organization and application name

   _CommonOrganisationName.Set( strOrg );
   _CommonApplicationName.Set( strApp );

   // restore the last setting from the registry

   getRegEnv( strOrg, strApp );

   return;
}

void pixq_Properties::resetEnv( QString strOrg, QString strApp )
{
   initAllEnv();
   
   // clear organization and application name

   _CommonOrganisationName.Set( strOrg );
   _CommonApplicationName.Set( strApp );

   // restore the last setting from the registry

   setRegEnv(strOrg, strApp);

   return;
}

static QFont InitBagsterHeaderFont( void )
{
   bool bMatch;
   QFont fn;

   // ヘッダー部分のフォント

   fn.setBold( true );
   fn.setStrikeOut( false );
   fn.setItalic( false );
   fn.setOverline( false );
   fn.setUnderline( false );
   
   fn.setFamily( "ＭＳ Ｐゴシック" );

   //fn.setPointSize( 8 );
   fn.setPointSizeF( 12.0 );
   //fn.setPixelSize( -1 );

   fn.setWeight( QFont::Bold );

   fn.setStyle( QFont::StyleNormal );
   fn.setStyleHint( QFont::AnyStyle );

   // members not explicitly set

   //fn.setFixedPitch( bool enable );
   //fn.setCapitalization( Capitalization caps );
   //fn.setKerning( bool enable );
   //fn.setLetterSpacing( SpacingType type, qreal spacing );
   //fn.setRawMode( bool enable );
   //fn.setRawName( const QString & name );
   //fn.setStretch( int factor );
   //fn.setStyleStrategy( StyleStrategy s );
   //fn.setWordSpacing( qreal spacing )

   // Returns true if a window system font exactly matching the settings of this font is available.
   bMatch = fn.exactMatch( );

   return fn;
}  

void pixq_Properties::initCommon(void)
{
   QString strValue;

   short sCat = (short)pixq_Properties::ItemCategoryCommonGui;

   strValue = "PixTopo";
   _CommonApplicationName.Set( sCat, strValue, "Common Application Name" );

   strValue = "PixTopo";
   _CommonOrganisationName.Set( sCat, strValue, "Common Organisation Name" );

   // for sequence selection dialog

   // directory of the last seleced images

#ifdef _WINDOWS
   strValue = "c:/";
#else
   strValue = "~";
#endif
   _CommonLastImage0Dir.Set( sCat, strValue, "ItfTools Common Last First Image Dir" );  
   _CommonLastImage1Dir.Set( sCat, strValue, "ItfTools Common Last Second Image Dir" ); 

   // last selected image

   strValue.clear( );
   _CommonLastImage0File.Set( sCat, strValue, "ItfTools Common Last Selected First Image" );    
   _CommonLastImage1File.Set( sCat, strValue, "ItfTools Common Last Selected Second Image" ); 

   // last selected video

#ifdef _WINDOWS
   strValue = "c:/";
#else
   strValue = "~";
#endif
   _CommonLastVideoDir.Set( sCat, strValue, "ItfTools Common Last Video Dir" );  

   return;
}
 
static QFont InitBagsterHikariJpFont( void )
{
   bool bMatch;
   QFont fn;

   fn.setBold( false );
   fn.setStrikeOut( false );
   fn.setItalic( false );
   fn.setOverline( false );
   fn.setUnderline( false );
   
   fn.setFamily( "ＭＳ Ｐゴシック" );

   //fn.setPointSize( 8 );
   fn.setPointSizeF( 11 );
   //fn.setPixelSize( -1 );

   fn.setWeight( QFont::Normal );

   fn.setStyle( QFont::StyleNormal );
   fn.setStyleHint( QFont::AnyStyle );

   // members not explicitly set

   //fn.setFixedPitch( bool enable );
   //fn.setCapitalization( Capitalization caps );
   //fn.setKerning( bool enable );
   //fn.setLetterSpacing( SpacingType type, qreal spacing );
   //fn.setRawMode( bool enable );
   //fn.setRawName( const QString & name );
   //fn.setStretch( int factor );
   //fn.setStyleStrategy( StyleStrategy s );
   //fn.setWordSpacing( qreal spacing )

   // Returns true if a window system font exactly matching the settings of this font is available.
   bMatch = fn.exactMatch( );

   return fn;
}

static QFont InitBagsterHikariEnFont( void )
{
   bool bMatch;
   QFont fn;

   fn.setBold( false );
   fn.setStrikeOut( false );
   fn.setItalic( false );
   fn.setOverline( false );
   fn.setUnderline( false );
   
   fn.setFamily( "Ariel" );

   //fn.setPointSize( 8 );
   fn.setPointSizeF( 11 );
   //fn.setPixelSize( -1 );

   fn.setWeight( QFont::Normal );

   fn.setStyle( QFont::StyleNormal );
   fn.setStyleHint( QFont::AnyStyle );

   // members not explicitly set

   //fn.setFixedPitch( bool enable );
   //fn.setCapitalization( Capitalization caps );
   //fn.setKerning( bool enable );
   //fn.setLetterSpacing( SpacingType type, qreal spacing );
   //fn.setRawMode( bool enable );
   //fn.setRawName( const QString & name );
   //fn.setStretch( int factor );
   //fn.setStyleStrategy( StyleStrategy s );
   //fn.setWordSpacing( qreal spacing )

   // Returns true if a window system font exactly matching the settings of this font is available.
   bMatch = fn.exactMatch( );

   return fn;
}

void pixq_Properties::initCompare(void)
{
   bool bValue;
   int iValue, iMin, nMax;
   QColor colValue;

   short sCat = pixq_Properties::ItemCategoryCompare;

   // ****************
   // *** Compare ***
   // ****************

   // *** image comparison ***

   // show wiper/box as line
   bValue = true;
   _CompareDrawWiperLine.Set(sCat, bValue, "Compare Draw Wiper Box");

   // wiper/box color   
   colValue.setRgb(255, 255, 0);
   _CompareWiperLineColor.Set(sCat, colValue, "Compare Wiper Box Color");

   // fixed wiper/box color   
   colValue.setRgb(0, 0, 255);
   _CompareFixedWiperLineColor.Set(sCat, colValue, "Compare Fixed Wiper Box Color");

   // box(scope) radius, pixels on screen
   iValue = 100;
   iMin = 20;
   nMax = 600;
   _CompareBoxRadius.Set(sCat, iValue, "Compare Box Radius", iMin, nMax);

   return;
}

void pixq_Properties::initSystem( void )
{
   int iValue;
   QString strLanguage;
   short sCat = pixq_Properties::ItemCategorySystem;

   qDebug() << "sysLocale:";
   qDebug() << "Name" << QLocale::system().name();
   qDebug() << "Country" << QLocale::system().country();
   qDebug() << "Language" << QLocale::system().language();
   qDebug() << "native Country" << QLocale::system().nativeCountryName();
   qDebug() << "native Language" << QLocale::system().nativeLanguageName();

   strLanguage = QLocale::system().nativeLanguageName();

   // **************
   // *** system ***
   // **************

   // interface language
   // must be one of QLocale::​Language
   // now supports:
   // QLocale::English
   // QLocale::Japanese

   if (0 == strLanguage.compare("Japanese", Qt::CaseInsensitive)) {
      //
      // japanese
      //
      iValue = (int)QLocale::Japanese;
   }
   else if (0 == strLanguage.compare("English", Qt::CaseInsensitive)) {
      //
      // english
      //
      iValue = (int)QLocale::English;
   }
   else {
      //
      // default language
      //
      iValue = (int)QLocale::English;
   }

   _SystemInterfaceLanguage.Set(sCat, iValue, "System Interface Language");
   
   // screen number to use for dual view configuration, 0(left) or 1(right)
   iValue = (int)0;
   _SystemMonitorPosition.Set( sCat, iValue, "System Monitors Screen Position" );

   return;
}

 
void pixq_Properties::initScope(void)
{
   QString strValue;

   short sCat = pixq_Properties::ItemCategoryScope;

   // **************
   // *** scope ***
   // **************

   // directory of the last selected images

#ifdef _WINDOWS
   strValue = QString::fromLatin1("c:\\");
#else
   strValue = QString::fromLatin1("/home");
#endif
   _ScopeLastImage0Dir.Set( sCat, strValue, "Scope Last Selected Image 0 Dir" );
   _ScopeLastImage1Dir.Set( sCat, strValue, "Scope Last Selected Image 1 Dir" );
   
   // last seleced path
   
#ifdef _WINDOWS
   strValue = QString::fromLatin1("c:\\");
#else
   strValue = QString::fromLatin1("/home");
#endif
   _ScopeLastImage0Path.Set( sCat, strValue, "Scope Last Selected Image 0 Path" );
   _ScopeLastImage1Path.Set( sCat, strValue, "Scope Last Selected Image 1 Path" );
   
   return;
}


void pixq_Properties::initColomari(void)
{
   QString strValue;

   short sCat = pixq_Properties::ItemCategoryScope;

   // ****************
   // *** Colomari ***
   // ****************

   // directory of the last selected images

#ifdef _WINDOWS
   strValue = QString::fromLatin1("c:\\");
#else
   strValue = QString::fromLatin1("/home");
#endif
   _ColomariLastImageDir.Set(sCat, strValue, "Colomari Last Selected Image Dir");

   return;
}

void pixq_Properties::initMatch(void)
{
   int iValue;
   bool bValue;
   QString strValue;
   QColor colValue;

   short sCat = pixq_Properties::ItemCategoryMatch;

   // ***********************
   // *** Stereo Matching ***
   // ***********************

   // *** matching parameter ***

   // match grayscale image(true) or RGB three channels
   bValue = true;
   _MatchGrayScale.Set(sCat, bValue, "Matching Image GrayScale Image");

   // *** result display/edit ***

   // point display symbol size, on image
   iValue = 45;
   _MatchGridSymbolRadius.Set(sCat, iValue, "Matching Results Grid Symbol Radius");

   // grid selection radius, on image
   iValue = 35;
   _MatchGridSelectRange.Set(sCat, iValue, "Matching Results Grid Selection Range Radius");

   // *** symbols colors by matching status ***

   // color to draw point with high correlation
   colValue.setRgb(0, 191, 255);
   _MatchHighCorrColor.Set(sCat, colValue, "Matching Results High Correlation Color");

   // color to draw point with low correlation
   colValue.setRgb(255, 63, 0);
   _MatchLowCorrColor.Set(sCat, colValue, "Matching Results Low Correlation Color");

   // color to draw point with low texture
   colValue.setRgb(191, 0, 255);
   _MatchLowTexureColor.Set(sCat, colValue, "Matching Result Low Texture Color");

   // color to draw point with no result yet
   colValue.setRgb(191, 191, 191);
   _MatchNotAnalyzedColor.Set(sCat, colValue, "Matching Point Not Analyzed Color");

   // color to draw outlier point
   colValue.setRgb(197, 0, 11);
   _MatchOutlierColor.Set(sCat, colValue, "Matching Point Outlier Color");

   // color to draw unused point, regardless of point status
   colValue.setRgb(127, 127, 127);
   _MatchUnusedColor.Set(sCat, colValue, "Matching Point Unused Color");

   return;
}

void pixq_Properties::initStereoView(void)
{
   int iValue;
   QString strValue;

   short sCat = pixq_Properties::ItemCategoryStereo;

   // **********************
   // *** Stereo Viewing ***
   // **********************

   // anallyph method. one of Print3DAnaglyphMode
   iValue = Print3DAnaglyphBlueRed; 
   iValue = Print3DAnaglyphHalfColor;
   _StereoAnaglyphMethod.Set(sCat, iValue, "Storeo View Anaglyph Method");

   // default suffix to be added to anaglyph file 
   strValue = "_anaglyph";
   _StereoAnaglyphFileSuffix.Set(sCat, strValue, "Storeo View Suffix Anaglyph File");
   
   return;
}

void pixq_Properties::initPntRectify(void)
{
   bool bValue;
   int iValue, iMinValue, nMaxValue;
   double dValue;
   QString strValue;

   short sCat = pixq_Properties::ItemCategoryPntRectify;

   // ********************************
   // *** Rectify - control points ***
   // ********************************

   // *** conditions to gerenare sample control points ****
   
   // ideal control point numbers
   // grid intervals are determined to abtain the control points as close as possible to this

   iValue = 50;
   iValue = 40;
   _RectifyControlPointNumber.Set(sCat, iValue, "Rectify Ideal Control Point Number");
   
   // snap input point to nearest feature point?
   bValue = true;
   _RectifySnapFeaturePoint.Set(sCat, bValue, "Rectify Snap To Feature Before Match");

   // radius of search rectangle to select stereo feature near the given point
   iValue = 80;
   _RectifyFeatureSearchRange.Set(sCat, iValue, "Rectify Feature Search Range");
   
   // width of the area of image not to be included in matching, left, in pixels on original image
   iValue = 5;
   iMinValue = 4;
   nMaxValue = 20;
   _RectifyExcludeRateEdge.Set(sCat, iValue, "Rectify Excluded Area Rate From Edges",
      iMinValue, nMaxValue);

   // *** conditions for matching left to right ****

   // Use Image pyramid for stereo matching
   bValue = true;
   _RectifyMatchUsePyramid.Set(sCat, bValue, "Rectify Match Use Image Pyraqmid");

   // Correlation window radius
   iValue = 40;
   iValue = 25;
   _RectifySoukanMadoRadius.Set(sCat, iValue, "Rectify Image Corr Mado Radius");

   // max value for standard deviation to analyze correlation
   dValue = 1.0;
   dValue = 500.0;
   _RectifyMinStdDev.Set(sCat, dValue, "Rectify Image Min Standard Deviation");

   // match grayscale image or RGB three channels
   bValue = true;
   _RectifyGrayScale.Set(sCat, bValue, "Rectify Image GrayScale Image");

   // Correlation value, boundary between middle and high correlation
   dValue = 0.8;
   _RectifySoukanHighBoundary.Set(sCat, dValue, "Rectify Image Correlation High Boundary");
  
   // max horizontal disparity, pixel number on original image
   iValue = 30;
   iValue = 200;
   iValue = 120;
   iValue = 250;
   _RectifyMaxHorizontalDisparity.Set(sCat, iValue, "Rectify Image Max Horizontal Disparity");

   // max vertical disparity, pixel number on original image
   iValue = 10;
   iValue = 125;
   iValue = 100;
   iValue = 200;
   _RectifyMaxVerticalDisparity.Set(sCat, iValue, "Rectify Image Max Vertical Disparity");

   return;
}

void pixq_Properties::initCvRectify(void)
{
   QString strValue;
   int iValue;
   double dValue;

   short sCat = pixq_Properties::ItemCategoryCvRectify;

   // *********************************
   // *** Rectify - rotation matrix ***
   // *********************************

   // *** rectification method - OpenCV ***

   // algorithm to compute fundamental matrix, one of OpenCvFundamentalMatrixMethod

   iValue = (int)FundamentalMethodLmeds;
   iValue = (int)FundamentalMethodRansac;
   _RectifyCvFundamentalMethod.Set(sCat, iValue, "Rectify OpenCV Fundamental Method");

   // max distance from point to epipolar line in pixels
   // used in ransac
   dValue = 2.0;
   _RectifyCvFundamentalDistance.Set(sCat, dValue, "Rectify OpenCV Fundamental Distance");

   // desirable level of confidence(probability) that estimaed matrix is correct
   // used in ransac and lmeds
   dValue = 0.99;
   _RectifyCvFundamentalConfidence.Set(sCat, dValue, "Rectify OpenCV Fundamental Confidence");

   // allowable max residual among all control points
   // points are taken out one by one until the max residual is smaller than this
   dValue = 2.0;
   dValue = 4.0;
   dValue = 2.5;
   _RectifyCvRectifyThreshold.Set(sCat, dValue, "Rectify OpenCV Uncalibrated Threshold");

   // *** file names ***

   // default suffix to be added to output file 
   strValue = "_rectified";
   _RectifyRectifiedFileSuffix.Set(sCat, strValue, "Rectify Suffix For Rectified File");

   // *** path information ****

   // directory of the last selected images

#ifdef _WINDOWS
   strValue = QString::fromLatin1("c:\\");
   strValue.clear();
#else // _WINDOWS
   strValue = QString::fromLatin1("/home");
#endif // _WINDOWS

   _RectifyLastLeftImageDir.Set(sCat, strValue, "Rectify Last Selected Left Image Path");
   _RectifyLastRightImageDir.Set(sCat, strValue, "Rectify Last Selected Right Image Path");

   return;
}

void pixq_Properties::initOrtho(void)
{
   QString strValue;
   int iValue;
   QColor colValue;

   short sCat = pixq_Properties::ItemCategoryOrtho;

   // *************
   // *** Ortho ***
   // *************

   // directory of the last selected files

#ifdef _WINDOWS
   strValue = QString::fromLatin1("c:\\");
   //strValue.clear();
#else
   strValue = QString::fromLatin1("/home");
#endif
   _OrthoLastInputImageDir.Set(sCat, strValue, "Ortho Last Input Image Dir");

   // *** file names ***

   // default suffix to be added to output file 
   strValue = "_ortho";
   _OrthoOutputFileSuffix.Set(sCat, strValue, "Ortho Suffix For Output File");

   // *** drawing tags ***

   // ortho tag color
   colValue.setRgb(0, 191, 255);
   _OrthoTagColor.Set(sCat, colValue, "Ortho Tag Color");
   
   // ortho selected tag color
   colValue.setRgb(255, 0, 191 );
   _OrthoSelectedTagColor.Set(sCat, colValue, "Ortho Selected Tag Color");

   return;
}


void pixq_Properties::initDftFilter(void)
{
   double dValue;
   int iValue;

   short sCat = pixq_Properties::ItemCategoryDftFilter;

   // ******************
   // *** DFT Filter ***
   // ******************

   // filter DFT visualize sigma range
   // when the results of DFT is visualized, extent of average +/- sigma * range is
   // scaled to 0 - 255
   dValue = 2.0;
   _DftFilterDftSigmaRange.Set( sCat, dValue, "Filter DFT Visualize Sigma Range" );

   // filter - low/high filter, boundary
   dValue = 350.0;
   _DftFilterHighLowPassBoundary.Set( sCat, dValue, "Filter High Low Pass Boundary" );

   // filter - band-pass filter, lower boundary
   dValue = 100.0; 
   _DftFilterBandPassLowBoundary.Set( sCat, dValue, "Filter BandPass Lower Boundary" );

   // filter - band-pass filter,  higher boundary 
   dValue = 1000.0;
   _DftFilterBandPassHighBoundary.Set( sCat, dValue, "Filter BandPass Higher Boundary" );

   // filter - filter type, one of DigitalImageFilterShape
   iValue = DigitalFilterLowPass;
   _DftFilterDigitalFiltersShape.Set( sCat, iValue, "Filter Digital Filters Shape" );

   // filter - channel to analyze for 1D or 2D visualization of DFT results
   // one of PixImageColorChannel
   iValue = PixImageColorRed;
   _DftFilterDftVisualizeColor.Set( sCat, iValue, "Filter DFT Visualize Color" );

   return;
}

void pixq_Properties::initImage(void)
{
   int iValue;

   short sCat = pixq_Properties::ItemCategoryImage;

   // *************
   // *** Image ***
   // *************
      
   iValue = (int)TextureFilterNearest;
   _ImageTextureFilter.Set( sCat, iValue, "Image Texture Filter" ); 

   // sampling interval for image statistics/histopram
   iValue = 10;
   _ImageStatSamplePitch.Set( sCat, iValue, "Image Statistics Sampling Pitch" ); 
   
   return;
}

//
// make a list of all env items
//
void pixq_Properties::getEnvItems(vector<pixq_EnvItem*> *pItemsList)
{
   pItemsList->clear( );
   
   // **************
   // *** Common ***
   // **************

   pItemsList->push_back( (pixq_EnvItem*)&_CommonApplicationName );
   pItemsList->push_back( (pixq_EnvItem*)&_CommonOrganisationName );

   pItemsList->push_back( (pixq_EnvItem*)&_CommonLastImage0Dir );
   pItemsList->push_back( (pixq_EnvItem*)&_CommonLastImage1Dir );

   pItemsList->push_back( (pixq_EnvItem*)&_CommonLastImage0File );
   pItemsList->push_back( (pixq_EnvItem*)&_CommonLastImage1File );

   pItemsList->push_back( (pixq_EnvItem*)&_CommonLastVideoDir );

   // *************
   // *** Image ***
   // *************   

   pItemsList->push_back( (pixq_EnvItem*)&_ImageTextureFilter );
   pItemsList->push_back( (pixq_EnvItem*)&_ImageStatSamplePitch );

   // ****************
   // *** Compare ***
   // ****************

   pItemsList->push_back((pixq_EnvItem*)&_CompareDrawWiperLine);
   pItemsList->push_back((pixq_EnvItem*)&_CompareWiperLineColor);
   pItemsList->push_back((pixq_EnvItem*)&_CompareFixedWiperLineColor);
   pItemsList->push_back((pixq_EnvItem*)&_CompareBoxRadius);
   
   // **************
   // *** system ***
   // **************
   
   pItemsList->push_back((pixq_EnvItem*)&_SystemInterfaceLanguage);
   pItemsList->push_back((pixq_EnvItem*)&_SystemMonitorPosition);

   // *************
   // *** Scope ***
   // *************
   
   pItemsList->push_back( (pixq_EnvItem*)&_ScopeLastImage0Dir );
   pItemsList->push_back( (pixq_EnvItem*)&_ScopeLastImage1Dir );

   pItemsList->push_back( (pixq_EnvItem*)&_ScopeLastImage0Path );
   pItemsList->push_back( (pixq_EnvItem*)&_ScopeLastImage1Path );

   // ****************
   // *** Colomari ***
   // ****************

   pItemsList->push_back((pixq_EnvItem*)&_ColomariLastImageDir);

   // ***********************
   // *** Stereo Matching ***
   // ***********************

   // *** image correlation ***

   pItemsList->push_back((pixq_EnvItem*)&_MatchGrayScale);

   // *** result display/edit ***

   pItemsList->push_back((pixq_EnvItem*)&_MatchGridSymbolRadius);
   pItemsList->push_back((pixq_EnvItem*)&_MatchGridSelectRange);

   // *** symbols colors by matching status ***

   pItemsList->push_back((pixq_EnvItem*)&_MatchHighCorrColor);
   pItemsList->push_back((pixq_EnvItem*)&_MatchLowCorrColor);
   pItemsList->push_back((pixq_EnvItem*)&_MatchLowTexureColor);
   pItemsList->push_back((pixq_EnvItem*)&_MatchNotAnalyzedColor);
   pItemsList->push_back((pixq_EnvItem*)&_MatchOutlierColor);
   pItemsList->push_back((pixq_EnvItem*)&_MatchUnusedColor);

   // **********************
   // *** Stereo Viewing ***
   // **********************

   pItemsList->push_back((pixq_EnvItem*)&_StereoAnaglyphMethod);
   pItemsList->push_back((pixq_EnvItem*)&_StereoAnaglyphFileSuffix);
   
   // ***************
   // *** Rectify ***
   // ***************
   
   // *** conditions to gerenare sample control points ****

   pItemsList->push_back((pixq_EnvItem*)&_RectifyControlPointNumber);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyExcludeRateEdge);
   pItemsList->push_back((pixq_EnvItem*)&_RectifySnapFeaturePoint);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyFeatureSearchRange);

   // *** conditions for matching left to right ****
   
   pItemsList->push_back((pixq_EnvItem*)&_RectifyMatchUsePyramid);
   pItemsList->push_back((pixq_EnvItem*)&_RectifySoukanMadoRadius);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyMinStdDev);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyGrayScale);
   pItemsList->push_back((pixq_EnvItem*)&_RectifySoukanHighBoundary);

   pItemsList->push_back((pixq_EnvItem*)&_RectifyMaxHorizontalDisparity);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyMaxVerticalDisparity);

   // *********************************
   // *** Rectify - rotation matrix ***
   // *********************************

   pItemsList->push_back((pixq_EnvItem*)&_RectifyCvFundamentalMethod);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyCvFundamentalDistance);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyCvFundamentalConfidence);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyCvRectifyThreshold);

   pItemsList->push_back((pixq_EnvItem*)&_RectifyRectifiedFileSuffix);
   
   pItemsList->push_back((pixq_EnvItem*)&_RectifyLastLeftImageDir);
   pItemsList->push_back((pixq_EnvItem*)&_RectifyLastRightImageDir);
   
   // **************
   // *** Ortho ***
   // **************

   pItemsList->push_back((pixq_EnvItem*)&_OrthoLastInputImageDir);
   pItemsList->push_back((pixq_EnvItem*)&_OrthoOutputFileSuffix);
   pItemsList->push_back((pixq_EnvItem*)&_OrthoTagColor);
   pItemsList->push_back((pixq_EnvItem*)&_OrthoSelectedTagColor);

   // ******************
   // *** DFT Filter ***
   // ******************

   pItemsList->push_back( (pixq_EnvItem*)&_DftFilterDftSigmaRange );
   pItemsList->push_back( (pixq_EnvItem*)&_DftFilterHighLowPassBoundary );
   pItemsList->push_back( (pixq_EnvItem*)&_DftFilterBandPassLowBoundary );
   pItemsList->push_back( (pixq_EnvItem*)&_DftFilterBandPassHighBoundary );
   pItemsList->push_back( (pixq_EnvItem*)&_DftFilterDigitalFiltersShape );
   pItemsList->push_back( (pixq_EnvItem*)&_DftFilterDftVisualizeColor );

   // --- Done ---
   return;
}

void pixq_Properties::getRegEnv(QString strOrg, QString strApp)
{
   vector<pixq_EnvItem*> ItemsList;
   pixq_EnvItem *pItem;
   int i, nItems;

   getEnvItems(&ItemsList);

   nItems = (int)ItemsList.size( );
   for( i = 0 ; i < nItems ; i++ ) {
      pItem = (pixq_EnvItem*)ItemsList.at( i );
      pItem->GetReg( strOrg, strApp );
   }

   // --- Done ---
   return;
}

// 
// 環境設定をレジストリーに書き込む
//
void pixq_Properties::setRegEnv( QString strOrg, QString strApp )
{
   vector<pixq_EnvItem*> ItemsList;
   pixq_EnvItem *pItem;
   int i, nItems;

   getEnvItems(&ItemsList);

   nItems = (int)ItemsList.size( );
   for( i = 0 ; i < nItems ; i++ ) {
      pItem = (pixq_EnvItem*)ItemsList.at( i );
      pItem->SetReg( strOrg, strApp );
   }

   // --- Done ---
   return;
}

//
// copy constructor
//
pixq_Properties &pixq_Properties::operator=( pixq_Properties &that )
{
   vector<pixq_EnvItem*> ItemsThis;
   vector<pixq_EnvItem*> ItemsThat;

   pixq_EnvItem *pThisItem, *pThatItem;
   int i, nItems;

   getEnvItems(&ItemsThis);
   that.getEnvItems(&ItemsThat);

   nItems = (int)ItemsThis.size( );
   for( i = 0 ; i < nItems ; i++ ) {
      try {
         pThisItem = (pixq_EnvItem*)ItemsThis.at( i );
         pThatItem = (pixq_EnvItem*)ItemsThat.at( i );
         //
         *pThisItem = *pThatItem;      
      }

      catch ( char * /* message */ ) {
         goto PIX_EXIT;    
	   };
   }
                                        
   // --- Done ---
PIX_EXIT:
   return *this;
}
