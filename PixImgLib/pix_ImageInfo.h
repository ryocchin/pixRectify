#pragma once

//
// image header information
//

namespace _pix_plot_img_framework {

//
// use Image Magick Image::ImageStatistics
// which include min, max, average, standard deviation Kurtsis and Skewness
//
//#define _MAGICK_STATISTICS
//
// compute basic image statistics
// which include min, max, average and standard deviation
//
#undef _MAGICK_STATISTICS

#include <Magick++.h>
using namespace Magick;

class PIXIMGLIB_EXPORT pixq_ImageInfo	
{
private:
   // file info
   QString _strFile;
   QString _strName;
   QString _strExt;

   int _nFileSize;

   QDateTime _dateCreated;
   QDateTime _dateModified;
   QDateTime _dateRead;

   // image format description
   QString _strFormat;
   QString _strDesc;

   // image info

   int _nImgWidth;
   int _nImgHeight;
   int _nBitDepth;

   ColorspaceType _color_space;
   ResolutionType _res_type;
   double _dXResolution;
   double _dYResolution;

   CompressionType _compress;
   OrientationType _orientation;

   // scale to 16-bit(short)pixel value to original input value)
   int _nDepthScale;

   //
   // image statistics
   //
#ifdef _MAGICK_STATISTICS
   Image::ImageStatistics _stat;
#else // _MAGICK_STATISTICS
   //
   // image basic statistics
   // 
   unsigned short _usMin[3];
   unsigned short _usMax[3];
   unsigned short _usAverage[3];
   unsigned short _usStdDev[3];
#endif // _MAGICK_STATISTICS

public:
   pixq_ImageInfo(void);
   virtual ~pixq_ImageInfo( void );

public:
   bool getMagickInfo(  Image &img, const QString strFile );

   void clear( void );
   
   void setPropsList( QStringList *strTitles, QStringList *strProps,
      const pixq_Properties *pEnv);
   void setPropsList( QStringList *strTitles, QStringList *strProps, 
      QList<int> *iAlignments,
      const pixq_Properties *pEnv);
   
   void setStatList(QStringList *strTitles, QStringList *strValues,
      const pixq_Properties *pEnv);
   void setStatList( QStringList *strTitles, QStringList *strValues, 
      QList<int> *iAlignments,
      const pixq_Properties *pEnv);

#ifdef _MAGICK_STATISTICS 
   Image::ImageStatistics *getStat(void)  { return &_stat; }
#else // _MAGICK_STATISTICS
   void setBasicStat(int iChan, const pixq_ImageMatrix *usPix);
#endif // _MAGICK_STATISTICS

   int getBitDepth(void) const { return _nBitDepth; }
   int getDepthScale(void) const { return _nDepthScale; }

};

} // _pix_plot_img_framework 
