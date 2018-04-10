#pragma once

namespace _pix_plot_qt_framework {

class pixq_EnvItem;

#include <pixqtlib_global.h>

class PIXQTLIB_EXPORT pixq_Properties
{
public:
   //
   // *** Never change these values! ***
   // Item Category
   //
   enum {
      ItemCategoryUnknown = -1,
      //
      // Common
      //
      ItemCategorySystem = 501,
      ItemCategoryCommonGui = 502,
      ItemCategoryImage = 503,
      ItemCategoryCompare = 504,
      //
      // Scope
      //
      ItemCategoryScope = 301,
      //
      // Rectification
      //
      ItemCategoryPntRectify = 302, // control points
      ItemCategoryCvRectify = 303, // computation
      ItemCategoryMatch = 305,
      ItemCategoryStereo = 306, // stereo viewing method
      //
      // Ortho
      //
      ItemCategoryOrtho = 312,
      //
      // Sampler
      //
      ItemCategoryDftFilter = 401,
      //
      //
      //
   } ItfEnvItemCategory;

   //
   // Do not change these numbers!
   // it is recorded in the registry
   //

   //
   // *** System ***
   //
   
   // Platform
   enum {
      PlatformUnknown = 0,
      PlatformWin32,
      PlatformWin64,
      PlatformAndroid,
   } PixTopoSystemPlatform;

   // language
   // we use QLocale::Language

   enum {
      TextureFilterNearest = 0, // nearest neighbour 
      TextureFilterLinear = 1,
   } TextureMaginificationFilter;

   // *** image alignment transformation method ***
   
   enum {
      TransformationNone = 0,
      // Affine transform
      TransformationAffine,
      // Projective Transform - transform right image to match the left
      TransformationProjective,
      // Stereo Rectification - projective transformation of both images
      TransformationRectification,
      // Color Fringing
      TransformationFringing,
   } ImageTransformationMethod;
   
   // shape of digital image filter
   enum {
      DigitalFilterLowPass = 0, // low-pass filter 
      DigitalFilterHighPass, // high-pass filter 
      DigitalFilterBandPass, // band-pass filter 
      DigitalFilterNotch, // notch filter 
   } DigitalImageFilterShape;

   // color channel
   enum {
      PixImageColorRed = 0, // red
      PixImageColorGreen, // green 
      PixImageColorBlue, // blue 
      PixImageColorGrayscale, // grayscale 
   } PixImageColorChannel;

   // *** Do Not Change Numbers! ***
   // *** Each Entry must have Unique Number ***
   enum {
      SamplerDerivedNone = 0, // no second image created
      //
      // *** derive from single image ***
      // *** Basic *** 
      //
      // same as the first image
      SamplerDerivedOriginal = 101, 
      SamplerDerivedGrayscale = 102,  
      SamplerDerivedMedian = 103,  
      SamplerDerivedRevert = 104, 
      SamplerDerivedGaussian = 106, 
      SamplerDerivedEdge = 108, 
      //
      // FFT/DCT
      SamplerDerivedVisualDftValue = 110, 
      SamplerDerivedVisualDftShape = 111, 
      SamplerDerivedVisualDftFilter = 112, 
      //
      // OpenCV
      SamplerDerivedOpenCvSepia = 130, 
      //
   } SamplerDerivedImageType;

   // method to compute fundamental matrix, see OpenCV findFundamentalMat 
   enum {
      FundamentalMethod7Point = 101,
      FundamentalMethod8Point,
      FundamentalMethodRansac,
      FundamentalMethodLmeds,
   } OpenCvFundamentalMatrixMethod;


   //
   // anaglyph viewing method
   //
   enum  {
      Print3DAnaglyphBlueRed     = 101,
      Print3DAnaglyphGray = 102,
      Print3DAnaglyphColor = 103,
      Print3DAnaglyphHalfColor = 104,
      Print3DAnaglyphWoods = 105,
      Print3DAnaglyphDubois = 106,
   } PixImagingAnaglyphMode;

public:
   pixq_Properties(void);
   ~pixq_Properties(void);

public:
   // **************
   // *** Common ***
   // **************

   // アプリケーションを作成した団体名
   pixq_EnvItem _CommonOrganisationName;

   // 起動中のアプリケーション名 
   pixq_EnvItem _CommonApplicationName;
   
   // for sequence selection dialog
   // directory of the last seleced images

   pixq_EnvItem _CommonLastImage0Dir;
   pixq_EnvItem _CommonLastImage1Dir;

   // last selected image

   pixq_EnvItem _CommonLastImage0File;
   pixq_EnvItem _CommonLastImage1File;

   // last selected video

   pixq_EnvItem _CommonLastVideoDir;

   // *************
   // *** Image ***
   // *************

   // openGL texture magnification filter, nearest or linear, one of TextureMaginificationFilter
   pixq_EnvItem _ImageTextureFilter;

   // sampling interval for image statistics/histopram
   pixq_EnvItem _ImageStatSamplePitch;
   
   // ****************
   // *** Compare ***
   // ****************
   
   // *** image comparison ***

   // show wiper/box as line
   pixq_EnvItem _CompareDrawWiperLine;

   // wiper/box color
   pixq_EnvItem _CompareWiperLineColor;
  
   // fixed wiper/box color
   pixq_EnvItem _CompareFixedWiperLineColor;

   // box(scope) radius, pixels on screen
   pixq_EnvItem _CompareBoxRadius;

   // **************
   // *** System ***
   // **************

   // interface language
   // must be one of QLocale::​Language stored as integer
   // now supports:
   // QLocale::English
   // QLocale::Japanese
   pixq_EnvItem _SystemInterfaceLanguage;

   // screen number to use for dual view configuration, 0(left) or 1(right)
   pixq_EnvItem _SystemMonitorPosition;

   // *************
   // *** Scope ***
   // *************
   
   // directory of the last selected images

   pixq_EnvItem _ScopeLastImage0Dir;
   pixq_EnvItem _ScopeLastImage1Dir;
   
   // last seleced path in "select two directories"

   pixq_EnvItem _ScopeLastImage0Path;
   pixq_EnvItem _ScopeLastImage1Path;

   // ****************
   // *** Colomari ***
   // ****************

   // directory of the last selected images

   pixq_EnvItem _ColomariLastImageDir;

   // last seleced path 

   pixq_EnvItem _ColomariLastImagePath;

   // ********************************
   // *** Rectify - control points ***
   // ********************************
   
   // *** conditions to gerenare sample control points ****

   // ideal control point numbers
   // grid intervals are determined to abtain the control points as close as possible to this
   pixq_EnvItem _RectifyControlPointNumber;
   
   // *** pixels to exclude at edges ***

   // width of the area of image not to be included in matching, in pixels on original image
   // %-age to the width of the image
   pixq_EnvItem _RectifyExcludeRateEdge;
   
   // snap input point to nearest feature point?
   pixq_EnvItem _RectifySnapFeaturePoint;

   // radius of search rectangle to select stereo feature near the given point
   pixq_EnvItem _RectifyFeatureSearchRange;
      
   // *** conditions for matching left to right ****

   // Use Image pyramid for stereo matching
   pixq_EnvItem _RectifyMatchUsePyramid;
   
   // Correlation window radius, on resampled image
   pixq_EnvItem _RectifySoukanMadoRadius;

   // minimum value for standard deviation to analyze correlation
   pixq_EnvItem _RectifyMinStdDev;

   // match grayscale image or RGB three channels
   pixq_EnvItem _RectifyGrayScale;
   
   // Correlation value, boundary between middle and high correlation
   pixq_EnvItem _RectifySoukanHighBoundary;

   // max horizontal disparity, pixel number on original image
   pixq_EnvItem _RectifyMaxHorizontalDisparity;

   // max vertical disparity, pixel number on original image
   pixq_EnvItem _RectifyMaxVerticalDisparity;
   
   // *********************************
   // *** Rectify - rotation matrix ***
   // *********************************

   // *** rectification method - OpenCV ***

   // algorithm to compute fundamental matrix, one of OpenCvFundamentalMatrixMethod
   pixq_EnvItem _RectifyCvFundamentalMethod;

   // max distance from point to epipolar line in pixels
   // used in ransac
   pixq_EnvItem _RectifyCvFundamentalDistance;

   // desirable level of confidence(probability) that estimaed matrix is correct
   // used in ransac and lmeds
   pixq_EnvItem _RectifyCvFundamentalConfidence;

   // allowable max residual among all control points
   // points are taken out one by one until the max residual is smaller than this
   // threshold to filter out the outliers ion OpenCV stereoRectifyUncalibrated function
   pixq_EnvItem _RectifyCvRectifyThreshold;

   // *** file names ***

   // default suffix to be added to output file 
   pixq_EnvItem _RectifyRectifiedFileSuffix;

   // *** path information ****

   // directory of the last selected images

   pixq_EnvItem _RectifyLastLeftImageDir;
   pixq_EnvItem _RectifyLastRightImageDir;

   // ***********************
   // *** Stereo Matching ***
   // ***********************

   // *** image correlation ***
   
   // match grayscale image or RGB three channels
   pixq_EnvItem _MatchGrayScale;
   
   // *** result display/edit ***

   // point display symbol size, on image
   pixq_EnvItem _MatchGridSymbolRadius;

   // grid selection radius, on image
   pixq_EnvItem _MatchGridSelectRange;

   // *** symbols colors by matching status ***

   // color to draw point with high correlation
   pixq_EnvItem _MatchHighCorrColor;

   // color to draw point with low correlation
   pixq_EnvItem _MatchLowCorrColor;

   // color to draw point with low texture
   pixq_EnvItem _MatchLowTexureColor;

   // color to draw point with no result yet
   pixq_EnvItem _MatchNotAnalyzedColor;
   
   // color to draw outlier point
   pixq_EnvItem _MatchOutlierColor;
   
   // color to draw unused point, regardless of point status
   pixq_EnvItem _MatchUnusedColor;

   // **********************
   // *** Stereo Viewing ***
   // **********************

   // anallyph method. one of PixImagingAnaglyphMode
   pixq_EnvItem _StereoAnaglyphMethod;

   // default suffix to be added to anaglyph file 
   pixq_EnvItem _StereoAnaglyphFileSuffix;

   // *************
   // *** Ortho ***
   // *************

   // directory of the last selected image

   pixq_EnvItem _OrthoLastInputImageDir;

   // default suffix to be added to output file 
   pixq_EnvItem _OrthoOutputFileSuffix;

   // *** drawing tags ***

   // ortho tag color
   pixq_EnvItem _OrthoTagColor;

   // ortho selected tag color
   pixq_EnvItem _OrthoSelectedTagColor;


   // ******************
   // *** DFT Filter ***
   // ******************

   // filter DFT visualize sigma range
   // when the results of DFT is visualized, extent of average +/- sigma * range is
   // scaled to 0 - 255
   pixq_EnvItem _DftFilterDftSigmaRange;

   // filter - low/high filter, boundary
   pixq_EnvItem _DftFilterHighLowPassBoundary;

   // filter - band-pass filter, lower boundary
   pixq_EnvItem _DftFilterBandPassLowBoundary;

   // filter - band-pass filter,  higher boundary
   pixq_EnvItem _DftFilterBandPassHighBoundary;

   // filter - filter type, one of DigitalImageFilterShape
   pixq_EnvItem _DftFilterDigitalFiltersShape;

   // filter - channel to analyze for 1D or 2D visualization of DFT results
   // one of PixImageColorChannel
   pixq_EnvItem _DftFilterDftVisualizeColor;

public: 

   // make a list of all env items
   void getEnvItems( vector<pixq_EnvItem*> *pItemsList );

   void initAllEnv(void);
   void initEnv( QString strOrg, QString strApp );
   void resetEnv( QString strOrg, QString strApp );

   // Common

   void initCommon( void );
   void initImage(void);
   void initCompare(void);
   void initSystem(void);

   // Scope

   void initScope(void);
   
   // Colomari

   void initColomari(void);

   // Rectification

   void initPntRectify(void);
   void initCvRectify(void);
   void initMatch(void);
   void initStereoView(void);

   // Ortho

   void initOrtho(void);

   // Sampler

   void initDftFilter( void );

   // 

   void getRegEnv(QString strOrg, QString strApp);
   void setRegEnv(QString strOrg, QString strApp);
   
   // copy constructor
	pixq_Properties &operator=( pixq_Properties &that);

   // returns opencv fundamental matrix method name
   string fundamentalMethodName(void);
};

} // namespace  