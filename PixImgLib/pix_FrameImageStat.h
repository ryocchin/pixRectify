#pragma once

//
// information about image which contains:
// - sample of two images
// - histogram of two images
//

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

namespace _pix_plot_img_framework {

class PIXIMGLIB_EXPORT pixq_FrameImageStat
{
public:
   pixq_FrameImageStat(void);
   ~pixq_FrameImageStat(void);

public:
   void Init( void );
   void Release( void );

private:
   // image pixlel value list to analyze correlation

   vector<unsigned short> _vRed[2];
   vector<unsigned short> _vGrn[2];
   vector<unsigned short> _vBlu[2];
   
   // is image sample value valid?

   vector<bool> _vValid[2];

   // compressed image histogram
   vector<int> _viRedHist[2];
   vector<int> _viGrnHist[2];
   vector<int> _viBluHist[2];
   
   // lower and higher boundary of each bin in uncompressed histogram
   vector<double> _vdBinLow;
   vector<double> _vdBinHigh;
   vector<double> _vdBinCen;

   // number of bins in the compressed histogram
   // must be 2 power n
   static int _nCompressedBin;

   // list of sample positions
   vector<int> _viSampleRows;
   vector<int> _viSampleCols;

   // largest histogram frequency, compressed histogram   
   // for red/green/blue channel between input and derived
   //
   // for three colors, RGB
   int _iColorMax[2][3]; 
   
public:
   int GetHistogramBin( void ) { return _nCompressedBin; }

   int getColorChanMaxFrequency(int iChan, int iColor) const;
   int getColorMaxFrequency(int iColor) const;
   int GetSideMaxFrequency( int iSide ) const;
   
   vector<unsigned short> *getRedPixelList( int iSide ) { return &_vRed[iSide]; }
   vector<unsigned short> *getGrnPixelList( int iSide ) { return &_vGrn[iSide]; }
   vector<unsigned short> *getBluPixelList( int iSide ) { return &_vBlu[iSide]; }
   vector<bool> *getPixelValidList( int iSide ) { return &_vValid[iSide]; }

   vector<int> *GetRedHistogram( int iSide ) { return &_viRedHist[iSide]; }
   vector<int> *GetGrnHistogram( int iSide ) { return &_viGrnHist[iSide]; }
   vector<int> *GetBluHistogram( int iSide ) { return &_viBluHist[iSide]; }
   
   vector<double> *GetBinLowValue( void ) { return &_vdBinLow; }
   vector<double> *GetBinHighValue( void ) { return &_vdBinHigh; }
   vector<double> *GetBinCenValue( void ) { return &_vdBinCen; }

   bool SetSamplePosition( int nImageHeight, int nImageWidth, int nSamplePicth );
   
   bool CreatePixelSample( int iSide, pixq_ImageMatrix *usRedImage,
      pixq_ImageMatrix *usGrnImage,
      pixq_ImageMatrix *usBluImage );

   bool GetImageCorrelation( double *dCorr ) const;
   bool GetImageCorrelation( int iSide0, int iSide1, double *dCorr ) const;

   bool GetRegressionPara( double *dScale, double *dOffset ) const;
   bool GetRegressionPara( int iSide0, int iSide1, double *dScale, double *dOffset ) const;
   
   bool CreateSampleHistogram( void );
};

} // namespace _pix_plot_img_framework

