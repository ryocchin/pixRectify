#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

//
// image correlation
//
// notes:
// if bUseZero is true, pixels with value 0.0 are also used in correlatin analysis
// otherwise, pixels with 0.0 is excluded
//
// if all pixels are 0.0 or smaller, correlation is set to zero
//
bool getImageCorrelation_PI(const pixq_Matrix<double> *pImg0, // [i] image 0
                             const pixq_Matrix<double> *pImg1, // [1] image 1
                             const bool bUseZero, // [i] if true, pixels with value 0.0 are also used in correlatin analysis
                             double *dCorr ) // [o] correlation
{
   bool bRetCode = false;
   int nAllPixels, nPixels, i, j, k, nRows, nCols;
   double dCor, dValue[2], dMean[2], dDiff[2], dTopDiv, dLowDiv[2];
   double dPixels, dLow;
   double *dPix0 = NULL;
   double *dPix1 = NULL;

   // *** check patch size ***

   nRows = pImg0->getHeight();
   nCols = pImg0->getWidth();

   if (1 > nRows) {
      goto PIX_EXIT;
   }
   
   if (1 > nCols) {
      goto PIX_EXIT;
   }
   
   if (nRows != pImg1->getHeight())  {
      goto PIX_EXIT;
   }

   if (nCols != pImg1->getWidth()) {
      goto PIX_EXIT;
   }

   nAllPixels = nRows * nCols;
   
   dPix0 = new double[nAllPixels];
   if (!dPix0)  {
      goto PIX_EXIT;
   }

   dPix1 = new double[nAllPixels];
   if (!dPix1)  {
      goto PIX_EXIT;
   }

   // --- make temp vector ---
   
   if( bUseZero ) {

      k = 0;
      for( i = 0 ; i < nRows ; i++ ) {
         for( j = 0 ; j < nCols ; j ++ ) {
            dValue[0] = (double)pImg0->Get( i, j );
            dValue[1] = (double)pImg1->Get( i, j );
            dPix0[k] = dValue[0];
            dPix1[k] = dValue[1];
            k++;
         }
      }
      nPixels = k;

   } else {
      
      k = 0;
      for( i = 0 ; i < nRows ; i++ ) {
         for( j = 0 ; j < nCols ; j ++ ) {
            dValue[0] = (double)pImg0->Get( i, j );
            dValue[1] = (double)pImg1->Get( i, j );
            if ( 0.0 >= dValue[0] ) continue;
            if ( 0.0 >= dValue[1] ) continue;
            dPix0[k] = dValue[0];
            dPix1[k] = dValue[1];
            k++;
         }
      }
      nPixels = k;

   }

   if( 0 >= nPixels ) {
      *dCorr = 0.0;
      bRetCode = true;
      goto PIX_EXIT;
   }

   dPixels = (double)nPixels;

   // --- get average ---

   dMean[0] = 0.0;
   dMean[1] = 0.0;
   for( k = 0 ; k < nPixels ; k++ ) {
      dMean[0] = dMean[0] + dPix0[k];
      dMean[1] = dMean[1] + dPix1[k];
   }

   dMean[0] = dMean[0] / dPixels;
   dMean[1] = dMean[1] / dPixels;
   
   // --- get corr ---

   dTopDiv = 0.0;
   dLowDiv[0] = 0.0;
   dLowDiv[1] = 0.0;
   for( k = 0 ; k < nPixels ; k++ ) {
      dDiff[0] = dPix0[k] - dMean[0];
      dDiff[1] = dPix1[k] - dMean[1];
      
      dTopDiv = dTopDiv + dDiff[0] * dDiff[1];
      dLowDiv[0] = dLowDiv[0] + dDiff[0] * dDiff[0];
      dLowDiv[1] = dLowDiv[1] + dDiff[1] * dDiff[1];
   }

   dLow = dLowDiv[0] * dLowDiv[1];
   if( 0.0 >= dLow ) {
      *dCorr = 0.0;
      bRetCode = true;
      goto PIX_EXIT;
   }

   dLow = sqrt( dLow );
   dCor = dTopDiv / dLow;   
   *dCorr = dCor;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   if( dPix0 ) { 
      delete[] dPix0;
      dPix0 = NULL; 
   }
   if( dPix1 ) {
      delete[] dPix1;
      dPix1 = NULL; 
   }
   return bRetCode;
}
  
bool getImageCorrelation_PI(const vector<unsigned char> *vcValue0,
                             const vector<unsigned char> *vcValue1,
                             const bool bUseZero, // [i] if true, pixels with value 0.0 are also used in correlatin analysis
                              double *dCorr ) // [o] correlation
{
   bool bRetCode = false;
   int i, nSize, nSize1;
   vector<double> vdValue0, vdValue1;

   // *** check patch size ***

   nSize = (int)vcValue0->size( );
   nSize1 = (int)vcValue1->size( );

   if( 1 > nSize ) goto PIX_EXIT;
   if( nSize != nSize1 ) goto PIX_EXIT;
   
   vdValue0.resize( nSize );
   vdValue1.resize( nSize );

   for( i = 0 ; i < nSize ; i++ ) {
      vdValue0.at( i ) = (double)vcValue0->at( i );
      vdValue1.at( i ) = (double)vcValue1->at( i );
   }

   if (!getImageCorrelation_PI(&vdValue0, &vdValue1, bUseZero, dCorr)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   vdValue0.clear( );
   vdValue1.clear( );
   return bRetCode;
}
  
bool getImageCorrelation_PI(const vector<unsigned short> *vsValue0,
                             const vector<unsigned short> *vsValue1,
                             const bool bUseZero, // [i] if true, pixels with value 0.0 are also used in correlatin analysis
                              double *dCorr ) // [o] correlation
{
   bool bRetCode = false;
   int i, nSize, nSize1;
   vector<double> vdValue0, vdValue1;

   // *** check patch size ***

   nSize = (int)vsValue0->size( );
   nSize1 = (int)vsValue1->size( );

   if( 1 > nSize ) goto PIX_EXIT;
   if( nSize != nSize1 ) goto PIX_EXIT;
   
   vdValue0.resize( nSize );
   vdValue1.resize( nSize );

   for( i = 0 ; i < nSize ; i++ ) {
      vdValue0.at( i ) = (double)vsValue0->at( i );
      vdValue1.at( i ) = (double)vsValue1->at( i );
   }

   if (!getImageCorrelation_PI(&vdValue0, &vdValue1, bUseZero, dCorr)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   vdValue0.clear( );
   vdValue1.clear( );
   return bRetCode;
}

//
// notes:
// vsValid0 is set to true for the item vsValue0 has the valid value
// vsValid1 is set to true for the item vsValue1 has the valid value
//
bool getImageCorrelation_PI(const vector<unsigned short> *vsValue0,
                             const vector<unsigned short> *vsValue1,
                              const vector<bool> *vsValid0, 
                              const vector<bool> *vsValid1, 
                             const bool bUseZero, // [i] if true, pixels with value 0.0 are also used in correlatin analysis
                              double *dCorr ) // [o] correlation
{
   bool bRetCode = false;
   int k, i, nSize0, nSize1, nTotal;
   bool bValid0, bValid1;
   vector<double> vdValue0, vdValue1;

   // *** check patch size ***

   nSize0 = (int)vsValue0->size( );
   nSize1 = (int)vsValue1->size( );

   if( 1 > nSize0 ) goto PIX_EXIT;
   if( nSize0 != nSize1 ) goto PIX_EXIT;
   
   vdValue0.clear( );
   vdValue1.clear( );

   for( i = 0, k = 0 ; i < nSize0 ; i++ ) {
      bValid0 = vsValid0->at( i );
      bValid1 = vsValid1->at( i );
      if( !bValid0 ) continue;
      if( !bValid1 ) continue;

      vdValue0.push_back( (double)vsValue0->at( i ) );
      vdValue1.push_back( (double)vsValue1->at( i ) );
      k++;
   }

   nTotal = (int)vdValue0.size( );

   if (!getImageCorrelation_PI(&vdValue0, &vdValue1, bUseZero, dCorr)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   vdValue0.clear( );
   vdValue1.clear( );
   return bRetCode;
}

bool getImageCorrelation_PI(const vector<double> *vdValue0,
                             const vector<double> *vdValue1,
                             const bool bUseZero, // [i] if true, pixels with value 0.0 are also used in correlatin analysis
                              double *dCorr ) // [o] correlation
{
   bool bRetCode = false;
   int nPixels, i, k, nSize, nSize1;
   double dCor, dValue[2], dMean[2], dDiff[2], dTopDiv, dLowDiv[2];
   double dPixels, dLow;
   double *dPix0 = NULL;
   double *dPix1 = NULL;

   // *** check patch size ***

   nSize = (int)vdValue0->size( );
   nSize1 = (int)vdValue1->size( );

   if( 1 > nSize ) goto PIX_EXIT;
   if( nSize != nSize1 ) goto PIX_EXIT;
   
   dPix0 = new double[nSize];
   if( !dPix0 ) goto PIX_EXIT;

   dPix1 = new double[nSize];
   if( !dPix1 ) goto PIX_EXIT;

   // --- make temp vector ---
   
   if( bUseZero ) {

      for( i = 0 ; i < nSize ; i++ ) {
         dPix0[i] = (double)vdValue0->at( i );
         dPix1[i] = (double)vdValue1->at( i );
      }
      nPixels = nSize;

   } else {
      
      k = 0;
      for( i = 0 ; i < nSize ; i++ ) {
         dValue[0] = (double)vdValue0->at( i );
         dValue[1] = (double)vdValue1->at( i );
         if ( 0.0 >= dValue[0] ) continue;
         if ( 0.0 >= dValue[1] ) continue;
         dPix0[k] = dValue[0];
         dPix1[k] = dValue[1];
         k++;
      }
      nPixels = k;

   }

   if( 0 >= nPixels ) {
      *dCorr = 0.0;
      bRetCode = true;
      goto PIX_EXIT;
   }

   dPixels = (double)nPixels;

   // --- get average ---

   dMean[0] = 0.0;
   dMean[1] = 0.0;
   for( k = 0 ; k < nPixels ; k++ ) {
      dMean[0] = dMean[0] + dPix0[k];
      dMean[1] = dMean[1] + dPix1[k];
   }

   dMean[0] = dMean[0] / dPixels;
   dMean[1] = dMean[1] / dPixels;
   
   // --- get corr ---

   dTopDiv = 0.0;
   dLowDiv[0] = 0.0;
   dLowDiv[1] = 0.0;
   for( k = 0 ; k < nPixels ; k++ ) {
      dDiff[0] = dPix0[k] - dMean[0];
      dDiff[1] = dPix1[k] - dMean[1];
      
      dTopDiv = dTopDiv + dDiff[0] * dDiff[1];
      dLowDiv[0] = dLowDiv[0] + dDiff[0] * dDiff[0];
      dLowDiv[1] = dLowDiv[1] + dDiff[1] * dDiff[1];
   }

   dLow = dLowDiv[0] * dLowDiv[1];
   if( 0.0 >= dLow ) {
      *dCorr = 0.0;
      bRetCode = true;
      goto PIX_EXIT;
   }

   dLow = sqrt( dLow );
   dCor = dTopDiv / dLow;   
   *dCorr = dCor;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   if( dPix0 ) { 
      delete[] dPix0;
      dPix0 = NULL;
   }
   if( dPix1 ) { 
      delete[] dPix1; 
      dPix1 = NULL;
   }
   return bRetCode;
}


bool getImageCorrelation_PI(const double *dRefBuffer,
                             const double *dCheckBuffer, 
                             const int nBufferSize,
                             const bool bUseZero, // [i] if true, pixels with value 0.0 are also used in correlatin analysis
                              double *dCorr ) // [o] correlation
{
   bool bRetCode = false;
   int nPixels, i, k;
   double dCor, dValue[2], dMean[2], dDiff[2], dTopDiv, dLowDiv[2];
   double dPixels, dLow;
   double *dPix0 = NULL;
   double *dPix1 = NULL;

   // *** check patch size ***
   
   dPix0 = new double[nBufferSize];
   if( !dPix0 ) goto PIX_EXIT;

   dPix1 = new double[nBufferSize];
   if( !dPix1 ) goto PIX_EXIT;

   // --- make temp vector ---
   
   if( bUseZero ) {

      for( i = 0 ; i < nBufferSize ; i++ ) {
         dPix0[i] = dRefBuffer[i];
         dPix1[i] = dCheckBuffer[i];
      }
      nPixels = nBufferSize;

   } else {
      
      k = 0;
      for( i = 0 ; i < nBufferSize ; i++ ) {
         dValue[0] = dRefBuffer[i];
         dValue[1] = dCheckBuffer[i];
         if ( 0.0 >= dValue[0] ) continue;
         if ( 0.0 >= dValue[1] ) continue;
         dPix0[k] = dValue[0];
         dPix1[k] = dValue[1];
         k++;
      }
      nPixels = k;

   }

   if( 0 >= nPixels ) {
      *dCorr = 0.0;
      bRetCode = true;
      goto PIX_EXIT;
   }

   dPixels = (double)nPixels;

   // --- get average ---
   dMean[0] = 0.0;
   dMean[1] = 0.0;
   for( k = 0 ; k < nPixels ; k++ ) {
      dMean[0] = dMean[0] + dPix0[k];
      dMean[1] = dMean[1] + dPix1[k];
   }

   dMean[0] = dMean[0] / dPixels;
   dMean[1] = dMean[1] / dPixels;
   
   // --- get corr ---
   dTopDiv = 0.0;
   dLowDiv[0] = 0.0;
   dLowDiv[1] = 0.0;
   for( k = 0 ; k < nPixels ; k++ ) {
      dDiff[0] = dPix0[k] - dMean[0];
      dDiff[1] = dPix1[k] - dMean[1];
      
      dTopDiv = dTopDiv + dDiff[0] * dDiff[1];
      dLowDiv[0] = dLowDiv[0] + dDiff[0] * dDiff[0];
      dLowDiv[1] = dLowDiv[1] + dDiff[1] * dDiff[1];
   }

   dLow = dLowDiv[0] * dLowDiv[1];
   if( 0.0 >= dLow ) {
      *dCorr = 0.0;
      bRetCode = true;
      goto PIX_EXIT;
   }

   dLow = sqrt( dLow );
   dCor = dTopDiv / dLow;   
   *dCorr = dCor;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   if( dPix0 ) { delete[] dPix0; dPix0 = NULL; }
   if( dPix1 ) { delete[] dPix1; dPix1 = NULL; }
   return bRetCode;
}

//
// for the given pair of values, do the regression analysis
// and return the estimated parameter for
// y = a * x + b
// a= scale, b = offset
//
bool getRegressionPara_PI(const vector<double> *vdX, // [i] list of x
                           const vector<double> *vdY, // [i] list of y
                           double *dScale, // [o] scale = a
                           double *dOffset ) // [o] offset = b
{
   bool bRetCode = false;
   int k, nSize, nSize1;
   double *dX = NULL;
   double *dY = NULL;

   // *** check patch size ***

   nSize = (int)vdY->size( );
   nSize1 = (int)vdX->size( );

   if( 1 > nSize ) goto PIX_EXIT;
   if( nSize != nSize1 ) goto PIX_EXIT;

   dX = new double[nSize];
   if( !dX ) goto PIX_EXIT;

   dY = new double[nSize];
   if( !dY ) goto PIX_EXIT;

   // --- make temp vector ---
   
   for( k = 0 ; k < nSize ; k++ ) {
      dX[k] = (double)vdX->at( k );
      dY[k] = (double)vdY->at( k );
   }
   
   // --- get corr ---

   if (!getRegressionPara_PI(dX, dY, nSize, dScale, dOffset)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   if( dX ) { 
      delete[] dX; 
      dX = NULL;
   }
   if( dY ) { 
      delete[] dY;
      dY = NULL;
   }
   return bRetCode;
}

bool getRegressionPara_PI(const vector<unsigned short> *vusX, // [i] list of x
                           const vector<unsigned short> *vusY, // [i] list of y
                           double *dScale, // [o] scale = a
                           double *dOffset ) // [o] offset = b
{
   bool bRetCode = false;
   int k, nSize, nSize1;
   double *dX = NULL;
   double *dY = NULL;

   // *** check patch size ***

   nSize = (int)vusX->size( );
   nSize1 = (int)vusY->size( );

   if( 1 > nSize ) goto PIX_EXIT;
   if( nSize != nSize1 ) goto PIX_EXIT;

   dX = new double[nSize];
   if( !dX ) goto PIX_EXIT;

   dY = new double[nSize];
   if( !dY ) goto PIX_EXIT;

   // --- make temp vector ---
   
   for( k = 0 ; k < nSize ; k++ ) {
      dX[k] = (double)vusX->at( k );
      dY[k] = (double)vusY->at( k );
   }
   
   // --- get corr ---

   if (!getRegressionPara_PI(dX, dY, nSize, dScale, dOffset)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   if( dX ) { 
      delete[] dX; 
      dX = NULL;
   }
   if( dY ) { 
      delete[] dY;
      dY = NULL;
   }
   return bRetCode;
}


bool getRegressionPara_PI(const double *dX,
                           const double *dY,
                           const int nSize,
                           double *dScale, // [o] scale = a
                           double *dOffset ) // [o] offset = b
{
   bool bRetCode = false;
   int k;
   double dXSum, dDet, dXXSum, dYSum, dXYSum, dAA, dBB, dCC, dDD;

   if( 1 > nSize ) goto PIX_EXIT;
   
   // --- get corr ---

   dXSum = 0.0;
   dYSum = 0.0;
   dXXSum = 0.0;
   dXYSum = 0.0;

   for( k = 0 ; k < nSize ; k++ ) {
      dXSum = dXSum + dX[k];
      dYSum = dYSum + dY[k];
      
      dXXSum = dXXSum + dX[k] * dX[k];
      dXYSum = dXYSum + dX[k] * dY[k];
   }

   dDet = dXXSum * (double)nSize - dXSum * dXSum;
   if( 0.0 == dDet ) {
      // determinant is zero
      goto PIX_EXIT;
   }

   dAA = (double)nSize;
   dBB = -dXSum;
   dCC = -dXSum;
   dDD = dXXSum;

   *dScale = ( dAA * dXYSum + dBB * dYSum ) / dDet;
   *dOffset = ( dCC * dXYSum + dDD * dYSum) / dDet;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
