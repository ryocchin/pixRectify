#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImageInfo.h"

pixq_ImageInfo::pixq_ImageInfo(void)
{
   clear();

   return;
}

pixq_ImageInfo::~pixq_ImageInfo( void )
{   
   return;
}

void pixq_ImageInfo::clear(void)
{
   _nImgWidth = 0;
   _nImgHeight = 0;
   _nBitDepth = 0;
   _nDepthScale = 1;

   _strFile.clear( );
   _strName.clear( );
   _strExt.clear( );

   _strDesc.clear( );
   _nFileSize = 0;

#ifdef _MAGICK_STATISTICS
#else // _MAGICK_STATISTICS
   for (int k = 0; k < 3; k++) {
      _usMin[k] = 0.0;
      _usMax[k] = 0.0;
      _usAverage[k] = 0.0;
      _usStdDev[k] = 0.0;
   }
#endif // _MAGICK_STATISTICS

   return;
}

void static pushPropsList( QStringList *strTitles, 
                         QStringList *strProps, 
                         QList<int> *iAlignments, 
                         QString strTitle, 
                         QString strProp, 
                         int iAlignment )
{
   strTitles->push_back( strTitle );
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignment );

   return;
}

//
// make a list of items names and values to show on the
// table
//
void pixq_ImageInfo::setPropsList( QStringList *strTitles, 
                                  QStringList *strProps, 
                                  QList<int> *iAlignments, // [o] table item alignment,
                                  const pixq_Properties *pEnv )
{
   QString strTitle, strProp;
   QString strEmpty = "-";
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();
   
   int iAlignLeft = Qt::AlignVCenter | Qt::AlignLeft;
   int iAlignRight = Qt::AlignVCenter | Qt::AlignRight;

   strTitles->clear( );
   strProps->clear( );
   iAlignments->clear( );

   // file info 
   
   strTitle = PixImgLib::getImageLibLabel( "ImageProp", "File", iLang );
   strTitles->push_back( strTitle );
   strProps->push_back( strEmpty );
   iAlignments->push_back( iAlignLeft );
         
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "FileName", iLang);
   strTitles->push_back( strTitle );
   strProps->push_back( _strName );
   iAlignments->push_back( iAlignLeft );
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Format", iLang);
   strTitles->push_back( strTitle );
   strProps->push_back( _strFormat );
   iAlignments->push_back( iAlignLeft );
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "FileSize", iLang);
   strProp.sprintf( "%d", _nFileSize );
   strTitles->push_back( strTitle );
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignRight );
  
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "DateCreated", iLang);
   strProp = _dateCreated.toString( Qt::SystemLocaleShortDate );
   strTitles->push_back( strTitle );
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignLeft );
  
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "DateModified", iLang);
   strProp = _dateModified.toString( Qt::SystemLocaleShortDate );
   strTitles->push_back( strTitle );
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignLeft );
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "DateRead", iLang);
   strProp = _dateRead.toString( Qt::SystemLocaleShortDate );
   strTitles->push_back( strTitle );
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignLeft );
   
   // Image info 
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Image", iLang);
   strTitles->push_back( strTitle );
   strProps->push_back( strEmpty );
   iAlignments->push_back( iAlignLeft );
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Desc", iLang);
   strTitles->push_back( strTitle );
   strProps->push_back( _strDesc );
   iAlignments->push_back( iAlignLeft );
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Width", iLang);
   strTitles->push_back( strTitle );
   strProp.sprintf( "%d", _nImgWidth );
   strProps->push_back( strProp );
   iAlignments->push_back(iAlignRight);
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Height", iLang);
   strTitles->push_back( strTitle );
   strProp.sprintf( "%d", _nImgHeight );
   strProps->push_back( strProp );
   iAlignments->push_back(iAlignRight);
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Depth", iLang);
   strTitles->push_back( strTitle );
   strProp.sprintf( "%d", _nBitDepth );
   strProps->push_back( strProp );
   iAlignments->push_back(iAlignRight);
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "ColorModel", iLang);
   strTitles->push_back( strTitle );
   switch( _color_space ) {
   case UndefinedColorspace:
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Undefined", iLang);
      break;
   case RGBColorspace:                  
      strProp = "RGB";
      break;
   case GRAYColorspace:                 
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Grayscale", iLang);
      break;
   case TransparentColorspace:          
      strProp = "Transparent";
      break;
   case OHTAColorspace:
      strProp = "OHTA";
      break;
   case XYZColorspace:
      strProp = "XYZ";
      break;
   case YCbCrColorspace:
      strProp = "YCbCr";
      break;
   case YCCColorspace:
      strProp = "YCC";
      break;
   case YIQColorspace:
      strProp = "YIQ";
      break;
   case YPbPrColorspace:
      strProp = "YPbPr";
      break;
   case YUVColorspace:            
      strProp = "YUV";
      break;
   case CMYKColorspace:           
      strProp = "CYMK";
      break;
   case sRGBColorspace:
      strProp = "sRGB";
      break;
   default:
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Unknown", iLang);
      break;
   }
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignLeft );

   //

   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Resolution", iLang);
   strTitles->push_back( strTitle );
   strProp.sprintf( "%.1f X %.1f", _dXResolution, _dYResolution );
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignLeft );
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "ResUnit", iLang);
   strTitles->push_back( strTitle );
   switch( _res_type ) {
   case UndefinedResolution:
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Undefined", iLang);
      break;
   case PixelsPerInchResolution:
      strProp = "Dot/Inch";
      break;
   case PixelsPerCentimeterResolution:
      strProp = "Dot/cm";
      break;
   default:
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Unknown", iLang);
      break;
   }
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignLeft );

   //
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Compression", iLang);
   strTitles->push_back( strTitle );
   switch( _compress ) {
   case UndefinedCompression:
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Undefined", iLang);
      break;
   case NoCompression:                  
      strProp = "No compression";
      break;
   case BZipCompression:                 
      strProp = "BZip";
      break;
   case FaxCompression:          
      strProp = "CCITT Group 3 FAX";
      break;
   case Group4Compression:
      strProp = "CCITT Group 4 FAX";
      break;
   case JPEGCompression:
      strProp = "JPEG";
      break;
   case LZWCompression:
      strProp = "Lempel-Ziv-Welch(LZW)";
      break;
#if 0
   case RunlengthEncodedCompression:
      strProp = "Length encoded(RLE)";
      break;
#endif // 0
   case ZipCompression:
      strProp = "Lempel-Ziv compression(LZ77)";
      break;
   default:
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Unknown", iLang);
      break;
   }
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignLeft );

   //
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Orientation", iLang);
   strTitles->push_back( strTitle );
   switch( _compress ) {
   case UndefinedOrientation:
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Undefined", iLang);
      break;
   case TopLeftOrientation:
      strProp = PixImgLib::getImageLibLabel("ImageCommon", "TopLeft", iLang);
      break;
   case TopRightOrientation:          
      strProp = PixImgLib::getImageLibLabel("ImageCommon", "TopRight", iLang);
      break;
   case BottomRightOrientation:
      strProp = PixImgLib::getImageLibLabel("ImageCommon", "BottomRight", iLang);
      break;
   case BottomLeftOrientation:
      strProp = PixImgLib::getImageLibLabel("ImageCommon", "BottomLeft", iLang);
      break;
   case LeftTopOrientation:
      strProp = PixImgLib::getImageLibLabel("ImageCommon", "LeftTop", iLang);
      break;
   case RightTopOrientation:
      strProp = PixImgLib::getImageLibLabel("ImageCommon", "RightTop", iLang);
      break;
   case RightBottomOrientation:
      strProp = PixImgLib::getImageLibLabel("ImageCommon", "RightBottom", iLang);
      break;
   case LeftBottomOrientation:
      strProp = PixImgLib::getImageLibLabel("ImageCommon", "LeftBottom", iLang);
      break;
   default:
      strProp = PixImgLib::getImageLibLabel("ImageProp", "Unknown", iLang);
      break;
   }
   strProps->push_back( strProp );
   iAlignments->push_back( iAlignLeft );

   return;
}

void pixq_ImageInfo::setPropsList( QStringList *strTitles, 
   QStringList *strProps,
   const pixq_Properties *pEnv )
{
   QList<int> iAlignments;
   
   setPropsList(strTitles, strProps, &iAlignments, pEnv);
   iAlignments.clear( );

   return;
}

//
// make a list of items names and image statistics
// table
//
void pixq_ImageInfo::setStatList( QStringList *strTitles, 
                                  QStringList *strValues, 
                                  QList<int> *iAlignments, // [o] table item alignment
                                  const pixq_Properties *pEnv)
{
   int k;
   QString strColor, strTitle, strValue;
   QString strEmpty = "";
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   QStringList strColors;

#ifdef _MAGICK_STATISTICS
   const Image::ImageStatistics *pStat = getStat();
#endif // _MAGICK_STATISTICS

   //
   // ImageMagick 6.X.X
   //
   const Image::ImageChannelStatistics *pChans[3];
   const Image::ImageChannelStatistics *pChan = NULL;

   //
   // ImageMagick 7.X.X
   //
   //const Magick::ChannelStatistics *pChans[3];
   //const Magick::ChannelStatistics *pChan = NULL;

   int iAlignLeft = Qt::AlignVCenter | Qt::AlignLeft;
   int iAlignRight = Qt::AlignVCenter | Qt::AlignRight;

#ifdef _MAGICK_STATISTICS
   pChans[0] = &pStat->red;
   pChans[1] = &pStat->green;
   pChans[2] = &pStat->blue;
#endif // _MAGICK_STATISTICS

   strColors.clear();
   strColors.push_back(PixImgLib::getImageLibLabel("ImageCommon", "Red", iLang));
   strColors.push_back(PixImgLib::getImageLibLabel("ImageCommon", "Green", iLang));
   strColors.push_back(PixImgLib::getImageLibLabel("ImageCommon", "Blue", iLang));

   strTitles->clear( );
   strValues->clear( );
   iAlignments->clear( );

   // Image info 
         
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "FileName", iLang);
   strTitles->push_back( strTitle );
   strValues->push_back( _strName );
   iAlignments->push_back( iAlignLeft );
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Width", iLang);
   strTitles->push_back( strTitle );
   strValue.sprintf( "%d", _nImgWidth );
   strValues->push_back( strValue );
   iAlignments->push_back(iAlignRight);
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Height", iLang);
   strTitles->push_back( strTitle );
   strValue.sprintf( "%d", _nImgHeight );
   strValues->push_back( strValue );
   iAlignments->push_back(iAlignRight);
   
   strTitle = PixImgLib::getImageLibLabel("ImageProp", "Depth", iLang);
   strTitles->push_back( strTitle );
   strValue.sprintf( "%d", _nBitDepth );
   strValues->push_back( strValue );
   iAlignments->push_back(iAlignRight);
   
   // Statistics 

   for( k = 0 ; k < 3 ; k++ ) {
   
      pChan = pChans[k];
      strColor = strColors.at( k );

      strTitles->push_back( strColor );
      strValues->push_back( strEmpty );
      iAlignments->push_back( iAlignLeft );
         
      strTitle = PixImgLib::getImageLibLabel("ImageProp", "Minimum", iLang);
      strTitles->push_back(strTitle);
#ifdef _MAGICK_STATISTICS
      strValue.sprintf("%.1f", pChan->minimum);
#else // _MAGICK_STATISTICS
      strValue.sprintf("%d", _usMin[k]);
#endif // _MAGICK_STATISTICS
      strValues->push_back( strValue );
      iAlignments->push_back( iAlignRight );
         
      strTitle = PixImgLib::getImageLibLabel("ImageProp", "Maximum", iLang);
      strTitles->push_back(strTitle);
#ifdef _MAGICK_STATISTICS
      strValue.sprintf("%.1f", pChan->maximum);
#else // _MAGICK_STATISTICS
      strValue.sprintf("%d", _usMax[k]);
#endif // _MAGICK_STATISTICS
      strValues->push_back( strValue );
      iAlignments->push_back( iAlignRight );
         
      strTitle = PixImgLib::getImageLibLabel("ImageProp", "Average", iLang);
      strTitles->push_back(strTitle);
#ifdef _MAGICK_STATISTICS
      strValue.sprintf("%.1f", pChan->mean);
#else // _MAGICK_STATISTICS
      strValue.sprintf("%d", _usAverage[k]);
#endif // _MAGICK_STATISTICS
      strValues->push_back( strValue );
      iAlignments->push_back( iAlignRight );
         
      strTitle = PixImgLib::getImageLibLabel("ImageProp", "StDev", iLang);
      strTitles->push_back(strTitle);
#ifdef _MAGICK_STATISTICS
      strValue.sprintf("%.1f", pChan->standard_deviation);
#else // _MAGICK_STATISTICS
      strValue.sprintf("%d", _usStdDev[k]);
#endif // _MAGICK_STATISTICS
      strValues->push_back( strValue );
      iAlignments->push_back( iAlignRight );

#ifdef _MAGICK_STATISTICS
      //strTitle = PixImgLib::getImageLibLabel( "ImageProp", "Variance", iLang );
      //strTitles->push_back( strTitle );
      //strValue.sprintf( "%.1f", pChan->variance );
      //strValues->push_back( strValue );
      //iAlignments->push_back( iAlignRight );
#else // _MAGICK_STATISTICS
#endif // _MAGICK_STATISTICS

#ifdef _MAGICK_STATISTICS
      strTitle = PixImgLib::getImageLibLabel("ImageProp", "Kurtosis", iLang);
      strTitles->push_back( strTitle );
      strValue.sprintf( "%.1f", pChan->kurtosis );
      strValues->push_back( strValue );
      iAlignments->push_back(iAlignRight);
#else // _MAGICK_STATISTICS
#endif // _MAGICK_STATISTICS

#ifdef _MAGICK_STATISTICS
      strTitle = PixImgLib::getImageLibLabel("ImageProp", "Skewness", iLang);
      strTitles->push_back( strTitle );
      strValue.sprintf( "%.1f", pChan->skewness );
      strValues->push_back( strValue );
      iAlignments->push_back(iAlignRight);
#else // _MAGICK_STATISTICS
#endif // _MAGICK_STATISTICS
   }

   return;
}

void pixq_ImageInfo::setStatList( QStringList *strTitles, 
   QStringList *strValues,
   const pixq_Properties *pEnv)
{
   QList<int> iAlignments;
   
   setStatList(strTitles, strValues, &iAlignments, pEnv);
   iAlignments.clear( );

   return;
}

#ifdef _MAGICK_STATISTICS 
#else // _MAGICK_STATISTICS
//
// get basic statistics and set into members
//
void pixq_ImageInfo::setBasicStat(int iChan,
   const pixq_ImageMatrix *usPix)
{
   if (0 > iChan || 3 <= iChan) {
      goto PIX_EXIT;
   }

   usPix->Statistics(&_usMin[iChan], &_usMax[iChan], &_usAverage[iChan], &_usStdDev[iChan]);
   
PIX_EXIT:
   return;
}
#endif // _MAGICK_STATISTICS

//
// obtain image header info from imagemagick data
//
bool pixq_ImageInfo::getMagickInfo( Image &img, // [i]
                                   const QString strFile ) // [i]
{   
   bool bRetCode = false;
   //QByteArray file = strFile.toLatin1();
   QByteArray file = strFile.toUtf8();
   QByteArray buf;
   CoderInfo ci; 
   QFileInfo fi;

#undef _REMASTER_REPORT_TIME
#ifdef _REMASTER_REPORT_TIME
   pixq_StopWatch watch;
   watch.InitTime();
   watch.ResetTime();
   watch.ResetAllTime();
   watch.SetLabel(0, "[getMagickInfo]param");
   watch.SetLabel(1, "[getMagickInfo]stat");
   watch.SetLabel(2, "[getMagickInfo]All");
#endif // _REMASTER_REPORT_TIME

   // file name
   
   fi.setFile( strFile );
   _strFile = strFile;
   _strName = fi.fileName( );
   _strExt = fi.suffix( ); 
   _nFileSize = fi.size( );
      
   // file description

   buf = _strExt.toLatin1( ); 
   ci = CoderInfo( buf.data( ) );
   _strFormat = (ci.name( )).c_str( );
   _strDesc = (ci.description( )).c_str( );
   
   _dateCreated = fi.created( );
   _dateModified = fi.lastModified( );
   _dateRead = fi.lastRead( );

   //

   _nImgHeight = (int)img.rows( );
   _nImgWidth = (int)img.columns( );

   // WHEN depth is set, scale mjust be set to

   _nBitDepth = (int)img.depth( );

   _nDepthScale = pow(2, 16 - _nBitDepth);
   if (0 >= _nDepthScale) {
      _nDepthScale = 1;
   }

   _color_space = img.colorSpace( );
 
   _res_type = img.resolutionUnits( );
   _dXResolution = img.xResolution( );
   _dYResolution = img.yResolution( );
   
   _compress = img.compressType( );
   _orientation = img.orientation( );

#ifdef _REMASTER_REPORT_TIME
   watch.AddElapsed(0); 
#endif // _REMASTER_REPORT_TIME

   // get image statistics 
   // this stat is not used!

#ifdef _MAGICK_STATISTICS
   img.statistics(&_stat);
#endif // _MAGICK_STATISTICS

#ifdef _REMASTER_REPORT_TIME
   watch.AddElapsed(1);
   watch.SetAllElapsed(2);
   watch.PrintTime(stdout, 3);
#endif // _REMASTER_REPORT_TIME

   // --- DONE ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

