#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "pix_FrameImageStat.h"

// number of bins in the compressed histogram
// must be 2 power n
//int pixq_FrameImageStat::_nCompressedBin = 512;
int pixq_FrameImageStat::_nCompressedBin = 256;

inline int ThreeMax( int iVal0, int iVal1, int iVal2 )
{
   int nMax = max( iVal0, iVal1 );   
   return max( nMax, iVal2 );
}

pixq_FrameImageStat::pixq_FrameImageStat(void)
{
   Init( );
}

pixq_FrameImageStat::~pixq_FrameImageStat(void)
{
   Init( );
}

void pixq_FrameImageStat::Init( void )
{
   Release( );
}


//
// release samples
//
void pixq_FrameImageStat::Release( void )
{
   int k;

   for( k = 0 ; k < 2 ; k++ ) {
      _vRed[k].clear( );
      _vGrn[k].clear( );
      _vBlu[k].clear( );
      //
      _vValid[k].clear( ); 
      //
      _viRedHist[k].clear( );
      _viGrnHist[k].clear( );
      _viBluHist[k].clear( );
   }

   _vdBinLow.clear( );
   _vdBinHigh.clear( );
   _vdBinCen.clear( );

   _viSampleRows.clear( );
   _viSampleCols.clear( );

   return;
}

//
// set the row and column position to pick up image samples
//
bool pixq_FrameImageStat::SetSamplePosition( int nImageHeight, // [i] int image height
                                               int nImageWidth, // [i] image width
                                               int nSamplePicth ) // [i] sampling pitch
{
   bool bRetCode = false;
   int i, j, nSampleRows, nSampleCols;
   
   // *** create resampled image matrices ***

   if( 0 >= nSamplePicth ) {
      goto PIX_EXIT;
   }
   
   _viSampleRows.clear( );
   _viSampleCols.clear( );

   for( i = 0 ; i < nImageHeight ; i+=nSamplePicth ) {
      _viSampleRows.push_back( i );
   }
   
   for( j = 0 ; j < nImageWidth ; j+=nSamplePicth ) {
      _viSampleCols.push_back( j );
   }

   nSampleRows = (int)_viSampleRows.size( );
   nSampleCols = (int)_viSampleCols.size( );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// set the value sample from the original image matrix
// for statistics and historgram
//
bool pixq_FrameImageStat::CreatePixelSample( int iSide, // [i] 0 or 1
                                            pixq_ImageMatrix *usRedImage, // [i] red image channel
                                            pixq_ImageMatrix *usGrnImage, // [i] green image channel
                                            pixq_ImageMatrix *usBluImage ) // [i] blue image channel
{
   bool bRetCode = false;
   bool bValidRow, bValidCol, bValidPixel;
   int i, j, iSampleRow, iSampleCol, nSampleRows, nSampleCols;
   int nValidWidth, nValidHeight;
   unsigned short usRed, usGrn, usBlu;

   nSampleRows = (int)_viSampleRows.size( );
   nSampleCols = (int)_viSampleCols.size( );
   
   nValidWidth = (int)usRedImage->getValidWidth( );
   nValidHeight = (int)usRedImage->getValidHeight( );

   if( 0 > iSide ) goto PIX_EXIT;
   if( 2 <= iSide ) goto PIX_EXIT;

   _vRed[iSide].clear( );
   _vGrn[iSide].clear( );
   _vBlu[iSide].clear( );
   _vValid[iSide].clear( ); 

   for( i = 0 ; i < nSampleRows ; i++ ) {
      iSampleRow = _viSampleRows.at( i );
      bValidRow = ( iSampleRow >= nValidHeight ) ? false : true;

      for( j = 0 ; j < nSampleCols ; j++ ) {
         iSampleCol = _viSampleCols.at( j );  
         bValidCol = ( iSampleCol >= nValidWidth ) ? false : true;

         usRed = usRedImage->Get( iSampleRow, iSampleCol );
         usGrn = usGrnImage->Get( iSampleRow, iSampleCol );
         usBlu = usBluImage->Get( iSampleRow, iSampleCol );

         _vRed[iSide].push_back( usRed );
         _vGrn[iSide].push_back( usGrn );
         _vBlu[iSide].push_back( usBlu );
         
         // set this value to false if the sample is taken from the outside
         // of the original image
         //
         // this occurs when on of two images is smaller than the others
         bValidPixel = ( bValidRow && bValidCol ) ? true : false;         
         _vValid[iSide].push_back( bValidPixel ); 
      }
   } 

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// create histogram from the image samples in the class
//
bool pixq_FrameImageStat::CreateSampleHistogram( void )
{
   bool bValid;
   int k, i, nSamples[2], iBinStart, iBinEnd, iHist[3];
   int nValid[2], nMaxHist[2][3], iRed, iGrn, iBlu;
   double dScale;

   // init compressed histogram

   for( k = 0 ; k < 2 ; k++ ) {
      _viRedHist[k].resize( _nCompressedBin );
      _viGrnHist[k].resize( _nCompressedBin );
      _viBluHist[k].resize( _nCompressedBin );
      
      for( i = 0 ; i < _nCompressedBin ; i++ ) {
         _viRedHist[k].at( i ) = 0;
         _viGrnHist[k].at( i ) = 0;
         _viBluHist[k].at( i ) = 0;
      }
   }

   _vdBinLow.resize( _nCompressedBin );
   _vdBinHigh.resize( _nCompressedBin );
   _vdBinCen.resize( _nCompressedBin );

   // *** create compressed histogram ***

   dScale = 65536.0 / (double)_nCompressedBin;

   for( k = 0 ; k < 2 ; k++ ) {
      nSamples[k] = (int)_vRed[0].size( );
      nValid[k] = 0;
      for( i = 0 ; i < nSamples[k] ; i++ ) {
         bValid = _vValid[k].at( i ); 
         if( !bValid ) continue;

         nValid[k]++;

         iRed = (int)floor( (double)_vRed[k].at( i ) / dScale );
         iGrn = (int)floor( (double)_vGrn[k].at( i ) / dScale );
         iBlu = (int)floor( (double)_vBlu[k].at( i ) / dScale );
         //
         iHist[0] = _viRedHist[k].at( iRed );
         iHist[1] = _viGrnHist[k].at( iGrn );
         iHist[2] = _viBluHist[k].at( iBlu );
         //
         _viRedHist[k].at( iRed ) = iHist[0] + 1;
         _viGrnHist[k].at( iGrn ) = iHist[1] + 1;
         _viBluHist[k].at( iBlu ) = iHist[2] + 1;
      }
   }
   
   for( i = 0 ; i < _nCompressedBin ; i++ ) {
      iBinStart = i * 65536 / _nCompressedBin;
      iBinEnd = ( i + 1 ) * 65536 / _nCompressedBin - 1;
      
      // histogram bin boundary
      _vdBinLow.at( i ) = (double)iBinStart;
      _vdBinHigh.at( i ) = (double)iBinEnd;
      _vdBinCen.at( i ) = (double)( iBinStart + iBinEnd ) / 2;
   }

   // get the maximum histogram frequency of the whole data(color and side)
   // from compressed histogram

   for( k = 0 ; k < 2 ; k++ ) {
      nMaxHist[k][0] = *max_element( _viRedHist[k].begin( ), _viRedHist[k].end( ) );
      nMaxHist[k][1] = *max_element( _viGrnHist[k].begin( ), _viGrnHist[k].end( ) );
      nMaxHist[k][2] = *max_element( _viBluHist[k].begin( ), _viBluHist[k].end( ) );      
   }

   for( i = 0 ; i < 3 ; i++ ) {
      for( k = 0 ; k < 2 ; k++ ) {
         _iColorMax[k][i] = nMaxHist[k][i];
      }
   }

   // --- Done ---
   return true;
}

bool pixq_FrameImageStat::GetImageCorrelation( double *dCorr )  // [o] three element, correlation in r g b channels 
const
{
   bool bRetCode = false;
   int iSide0 = 0;
   int iSide1 = 1;                                              

   if( !GetImageCorrelation( iSide0, iSide1, dCorr ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FrameImageStat::GetImageCorrelation( int iSide0,
                                              int iSide1, 
                                              double *dCorr )  // [o] three element, correlation in r g b channels 
const
{
   bool bRetCode = false;                                  

   if( 0 > iSide0 || 2 <= iSide0 ) goto PIX_EXIT;
   if( 0 > iSide1 || 2 <= iSide1 ) goto PIX_EXIT;

   if (!getImageCorrelation_PI(&_vRed[iSide0], &_vRed[iSide1],
      &_vValid[iSide0], &_vValid[iSide1], true, &dCorr[0] ) ) {
         goto PIX_EXIT;
   }

   if (!getImageCorrelation_PI(&_vGrn[iSide0], &_vGrn[iSide1],
      &_vValid[iSide0], &_vValid[iSide1], true, &dCorr[1] ) ) {
         goto PIX_EXIT;
   }

   if (!getImageCorrelation_PI(&_vBlu[iSide0], &_vBlu[iSide1],
      &_vValid[iSide0], &_vValid[iSide1], true, &dCorr[2] ) ) {
         goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


int pixq_FrameImageStat::getColorChanMaxFrequency(int iChan,
                                                  int iColor )
const
{
   int nMax = 0;

   if (0 > iChan || 2 <= iChan) {
      goto PIX_EXIT;
   }
   
   if (0 > iColor || 3 <= iColor) {
      goto PIX_EXIT;
   }

   nMax = _iColorMax[iChan][iColor];

PIX_EXIT:
   return nMax; 
}

int pixq_FrameImageStat::getColorMaxFrequency(int iColor)
const
{
   int k;
   int nMax = 0;

   if (0 > iColor || 3 <= iColor) {
      goto PIX_EXIT;
   }

   for( k = 0 ; k < 2 ; k++ ) {
      nMax = max( nMax, _iColorMax[k][iColor] );
   }

PIX_EXIT:
   return nMax; 
}

int pixq_FrameImageStat::GetSideMaxFrequency( int iChan ) 
const
{
   int k;
   int nMax = 0;

   if (0 > iChan || iChan >= 2) {
      goto PIX_EXIT;
   }

   for( k = 0 ; k < 3 ; k++ ) {
      nMax = max( nMax, _iColorMax[iChan][k] );
   }

PIX_EXIT:
   return nMax; 
}

bool pixq_FrameImageStat::GetRegressionPara( double *dScale, 
                                              double *dOffset ) 
const
{
   bool bRetCode = false;
   int iSide0 = 0;
   int iSide1 = 1;                                              

   if( !GetRegressionPara( iSide0, iSide1, dScale, dOffset ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FrameImageStat::GetRegressionPara( int iSide0,
                                              int iSide1, 
                                              double *dScale, 
                                              double *dOffset )  
const
{
   bool bRetCode = false;                                  

   if (0 > iSide0 || 2 <= iSide0) {
      goto PIX_EXIT;
   }
   
   if (0 > iSide1 || 2 <= iSide1) {
      goto PIX_EXIT;
   }

   if (!getRegressionPara_PI(&_vRed[iSide0], &_vRed[iSide1], &dScale[0], &dOffset[0])) {
      goto PIX_EXIT;
   }

   if (!getRegressionPara_PI(&_vGrn[iSide0], &_vGrn[iSide1], &dScale[1], &dOffset[1])) {
      goto PIX_EXIT;
   }

   if (!getRegressionPara_PI(&_vBlu[iSide0], &_vBlu[iSide1], &dScale[2], &dOffset[2])) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}