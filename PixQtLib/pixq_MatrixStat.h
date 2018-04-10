//
// pixq_Matrix
// 2D matrix class, data statistics
//

// matrix analysis, statistics and histogram, etc

namespace _pix_plot_qt_framework {

//
// calculate basic statistics of the matrix
// such as min and max values, average and standard deviation
//
// notes:
// if null value is set, it is not included in the calculation
//
template <class T> void pixq_Matrix<T>::Statistics(
   T *vmin, // [o] minimum value, excluding null value
   T *vmax ) // [o] maxmum value, excluding null value
const
{
	int i, j;
	T tValue, tMin, tMax;
   T *pRow = NULL;

   // start to get the statistics

	tMin = Get( 0, 0 );
	tMax = Get( 0, 0 );
   for( i = 0 ; i < _iNrows ; i++ ) {
      pRow = _pDataRow[i];
      for( j = 0 ; j < _iNcols ; j++ ) {
		   tValue = *pRow++;
   		if( tValue < tMin ) tMin = tValue;
			if( tValue > tMax ) tMax = tValue;
      }
   }

   // set the obtained values

	*vmin = tMin;
	*vmax = tMax;

//PIX_EXIT:
   return;
}

template <class T> void pixq_Matrix<T>::Statistics( 
   T *vmin,  // [o] minimum value, excluding null value
	T *vmax, // [o] maxmum value, excluding null value
	T *vmean ) // [o] average value, excluding null value
const
{
	double dCount, dMean, dSum;
	int i, j;
   T tValue, tMin, tMax;
   T *pRow = NULL;

   // start to get the statistics
      
	dSum = 0.0;
   tMin = Get( 0, 0 );
	tMax = Get( 0, 0 );
   for( i = 0 ; i < _iNrows ; i++ ) {
      pRow = _pDataRow[i];
      for( j = 0 ; j < _iNcols ; j++ ) {
		   tValue = *pRow++;
   		if( tValue < tMin ) tMin = tValue;
			if( tValue > tMax ) tMax = tValue;
	   	dSum = dSum + (double)tValue;
      }
   }
   
   dCount = (double)( _iNrows * _iNcols );
   if( 0.0 >= dCount ) {
      dMean = 0.0;
   } else {
      dMean = dSum / dCount;
   }

   // set the obtained values

	*vmin = tMin;
	*vmax = tMax;
	*vmean = (T)dMean;

//PIX_EXIT:
   return;
}

template <class T> void pixq_Matrix<T>::Statistics( 
	T *vmin,  // [o] minimum value, excluding null value
	T *vmax, // [o] maxmum value, excluding null value
	T *vmean, // [o] average value, excluding null value
	T *stdev ) // [o] STANDARD DEVIATION, excluding null value
const
{
   T tValue, vmin2, vmax2, vmean2;
	int i, j;
	double dCount, dSum, dStDev, dValue2, dMean;
   T *pRow = NULL;

   // get value range and average

	*vmin = (T)0;
	*vmax = (T)0;
	*vmean = (T)0;
	*stdev = (T)0;
   dStDev = 0.0;

   Statistics( &vmin2, &vmax2, &vmean2 );

   // get stdev

   dMean = (double)vmean2;

   dSum = 0.0;
   for( i = 0 ; i < _iNrows ; i++ ) {
      pRow = _pDataRow[i];
      for( j = 0 ; j < _iNcols ; j++ ) {
      tValue = *pRow++;
	      dValue2 = (double)tValue - dMean;
         dSum = dSum + dValue2 * dValue2;
      }
   }

   dCount = (double)( _iNrows * _iNcols );
   dStDev = sqrt( dSum / dCount );

	*vmin = vmin2;
	*vmax = vmax2;
	*vmean = vmean2;
	*stdev = (T)dStDev;

//PIX_EXIT:
   return;
}

template <class T> T pixq_Matrix<T>::mean( void )
   const
{
   double dCount, dMean, dSum;
   int i, j;
   T tMean, tValue;
   T *pRow = NULL;

   // start to get the statistics

   dSum = 0.0;
   for (i = 0; i < _iNrows; i++) {
      pRow = _pDataRow[i];
      for (j = 0; j < _iNcols; j++) {
         tValue = *pRow++;
         dSum = dSum + (double)tValue;
      }
   }

   dCount = (double)(_iNrows * _iNcols);
   if (0.0 >= dCount) {
      dMean = 0.0;
   }
   else {
      dMean = dSum / dCount;
   }
   
   tMean = (T)dMean;

   return tMean;
}

template <class T> T pixq_Matrix<T>::stDev(void)
   const
{
   T tStdev, tValue;
   int i, j;
   double dCount, dSum, dStDev, dValue2, dMean;
   T *pRow = NULL;

   // get average
   // get stdev

   dMean = (double)mean();

   dSum = 0.0;
   for (i = 0; i < _iNrows; i++) {
      pRow = _pDataRow[i];
      for (j = 0; j < _iNcols; j++) {
         tValue = *pRow++;
         dValue2 = (double)tValue - dMean;
         dSum = dSum + dValue2 * dValue2;
      }
   }

   dCount = (double)(_iNrows * _iNcols);
   dStDev = sqrt(dSum / dCount);
   tStdev = (T)dStDev;

   return tStdev;
}

template <class T> void pixq_Matrix<T>::Statistics(
   T *vmin, // [o] minimum value, excluding null value
   T *vmax, // [o] maxmum value, excluding null value
   const pixq_Matrix<bool> *pMask )
const
{
   bool bMask;
	int i, j, nValid;
	T tValue, tMin, tMax;
   T *pRow = NULL;

   // start to get the statistics
      
   nValid = 0;
	tMin = Get( 0, 0 );
	tMax = Get( 0, 0 );
   for( i = 0 ; i < _iNrows ; i++ ) {
      pRow = _pDataRow[i];
      for( j = 0 ; j < _iNcols ; j++ ) {
		   tValue = *pRow++;
         
         bMask = pMask->Get( i, j );
         if( !bMask ) continue;

   		if( tValue < tMin ) tMin = tValue;
			if( tValue > tMax ) tMax = tValue;
         nValid++;
      }
   }
	
   // set the obtained values

	*vmin = tMin;
	*vmax = tMax;

//PIX_EXIT:
   return;
}

template <class T> void pixq_Matrix<T>::Statistics( 
   T *vmin,  // [o] minimum value, excluding null value
	T *vmax, // [o] maxmum value, excluding null value
	T *vmean, // [o] average value, excluding null value
   const pixq_Matrix<bool> *pMask )
const
{
   bool bMask;
	double dCount, dMean, dSum;
	int nValid, i, j;
   T tValue, tMin, tMax;
   T *pRow = NULL;

   // start to get the statistics
      
   nValid = 0;
	dSum = 0.0;
   tMin = Get( 0, 0 );
	tMax = Get( 0, 0 );
   for( i = 0 ; i < _iNrows ; i++ ) {
      pRow = _pDataRow[i];
      for( j = 0 ; j < _iNcols ; j++ ) {
		   tValue = *pRow++;

         bMask = pMask->Get( i, j );
         if( !bMask ) continue;

   		if( tValue < tMin ) tMin = tValue;
			if( tValue > tMax ) tMax = tValue;
	   	dSum = dSum + (double)tValue;
         nValid++;
      }
   }
   
   dCount = (double)nValid;
   if( 0.0 >= dCount ) {
      dMean = 0.0;
   } else {
      dMean = dSum / dCount;
   }
	
   // set the obtained values

	*vmin = tMin;
	*vmax = tMax;
	*vmean = (T)dMean;

//PIX_EXIT:
   return;
}

template <class T> void pixq_Matrix<T>::Statistics( 
	T *vmin,  // [o] minimum value, excluding null value
	T *vmax, // [o] maxmum value, excluding null value
	T *vmean, // [o] average value, excluding null value
	T *stdev, // [o] STANDARD DEVIATION, excluding null value
   const pixq_Matrix<bool> *pMask )
const
{
   bool bMask;
   T tValue, vmin2, vmax2, vmean2;
	int i, j, nValid;
	double dCount, dSum, dStDev, dValue2, dMean;
   T *pRow = NULL;


   // get value range and average

	*vmin = (T)0;
	*vmax = (T)0;
	*vmean = (T)0;
	*stdev = (T)0;
   dStDev = 0.0;

   Statistics( &vmin2, &vmax2, &vmean2, pMask );

   // get stdev

   dMean = (double)vmean2;

   nValid = 0;
   dSum = 0.0;
   for( i = 0 ; i < _iNrows ; i++ ) {
      pRow = _pDataRow[i];
      for( j = 0 ; j < _iNcols ; j++ ) {
         tValue = *pRow++;
	      
         bMask = pMask->Get( i, j );
         if( !bMask ) continue;
      
         dValue2 = (double)tValue - dMean;
         dSum = dSum + dValue2 * dValue2;
         nValid++;
      }
   }

   dCount = (double)nValid;
   dStDev = sqrt( dSum / dCount );

	*vmin = vmin2;
	*vmax = vmax2;
	*vmean = vmean2;
	*stdev = (T)dStDev;

//PIX_EXIT:
   return;
}

} // namespace _pix_plot_qt_framework 

