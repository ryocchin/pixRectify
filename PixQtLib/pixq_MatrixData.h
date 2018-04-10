//
// pixq_Matrix
// 2D matrix class, data handing
//

// matrix data handling functions

namespace _pix_plot_qt_framework {

//
// set a value at the specific element of the matrix
//
template <class T>
void pixq_Matrix<T>::Set( int iRow, // [i] row
                         int iCol, // [i] col
                         T tValue ) // [i] value
{   
   *(_pDataRow[iRow]+iCol) = tValue;
}

//
// get a value at the specific element of the matrix
//
template <class T>
T pixq_Matrix<T>::Get( int iRow, int iCol ) const
{
   return *(_pDataRow[iRow]+iCol);
}

//
// fill the matrix with a given constant value
//
template <class T> void pixq_Matrix<T>::Fill( T Value )
{
   int i, j;

   for( i = 0 ; i < _iNrows ; i++ ) {
      for( j = 0 ; j < _iNcols ; j++ ) {
         _Data[i][j] = Value;
      }
   }

   return;
}

//
// get a row of data from the matrix into a one-dimensinal buffer
//
// returns:
// true or false
//
// notes:
// output buffer must be allocated 
// vector<T> is allocated iside this function
// frame area are not copied.
// frame area are not changed by this operation.
//
template <class T> bool pixq_Matrix<T>::GetRow( 
   int iRow,  // [i] row number 
   T *tBuff ) // [o] buffer to contain the row in the matrix 
   const
{
   bool bRetCode = false;
   T *pIn = NULL;
   T *pOut = NULL;

   if( !CheckRow( iRow ) ) goto PIX_EXIT;
   
   // copy row to buffer

   pIn = _pDataRow[iRow];
   pOut = tBuff;
   //for( i = 0 ; i < _iNcols ; i++ ) {      
   //   *pOut++ = *pIn++;
   //}
   memcpy( pOut, pIn, _iNcols * sizeof( T ) );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

template <class T> bool	pixq_Matrix<T>::GetRow( 
	int iRow, // [i] row number
   vector<T> *tBuff ) // [o] buffer to contain the row in the matrix 
   const
{
   bool bRetCode = false;
   int i;
   T *pIn = NULL;

   // check row number
   if( !CheckRow( iRow ) ) goto PIX_EXIT;

   // alloc vector
   //tBuff->resize( _iNcols );
   tBuff->clear( );

   // copy row to vector
   
   pIn = _pDataRow[iRow];
   for( i = 0 ; i < _iNcols ; i++ ) {
      //tBuff->at( i ) = *pIn++;
      tBuff->push_back( *pIn++ );
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// set a data into the row in the matrix from a one-dimensinal buffer
//
// returns:
// true or false
//
// notes:
// frame area are not copied.
// frame area are not changed by this operation.
//
template <class T> bool pixq_Matrix<T>::SetRow( 
   int iRow, // [i] row number
   T *tBuff ) // [i] buffer to contain the row in the matrix 
{
   bool bRetCode = false;
   T *pIn = NULL;
   T *pOut = NULL;
   
   // check row number
   if( !CheckRow( iRow ) ) goto PIX_EXIT;
   
   // copy row to vector
   
   pIn = tBuff;
   pOut = _pDataRow[iRow];
   memcpy( pOut, pIn, _iNcols * sizeof( T ) );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get a data from the whole matrix from a one-dimensinal buffer
//
// notes:
// tBuff must be allocate for the size of the matrix
//
template <class T> bool pixq_Matrix<T>::GetData( T *tBuff ) // [i] buffer for the whole matrix
{
   bool bRetCode = false;
   int i;
      
   // copy row to vector
   
   for( i = 0 ; i < _iNrows ; i++ ) {
      if( !GetRow( i, &tBuff[i*_iNcols] ) ) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
} 

//
// set a data into the whole matrix from a one-dimensinal buffer
//
template <class T> bool pixq_Matrix<T>::SetData( T *tBuff ) // [i] buffer for the whole matrix
{
   bool bRetCode = false;
   int i;
      
   // copy row to vector
   
   for( i = 0 ; i < _iNrows ; i++ ) {
      if( !SetRow( i, &tBuff[i*_iNcols] ) ) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
} 

//
// get a range of data from a specified row of the matrix into a one-dimensinal buffer
//
// returns:
// true or false
//
// notes:
// output buffer must be allocated beforehand.
// vector<T> is allocated iside this function
// frame area are not copied.
// frame area are not changed by this operation.
//
template <class T> bool pixq_Matrix<T>::GetLine( 
   int iRow,  // [i] row number 
   int iCol0, // [i] start column number
   int iCol1, // [i] end column number
   T *tBuff ) // [o] buffer to contain the row in the matrix 
const
{
   bool bRetCode = false;
   int i;
   T *pIn = NULL;
   T *pOut = NULL;

   if( !CheckRow( iRow ) ) goto PIX_EXIT;
   if( !CheckColRange( iCol0, iCol1 ) ) goto PIX_EXIT;
   
   // copy row to buffer

   pIn = (T*)&_pDataRow[iRow][iCol0];
   pOut = tBuff;
   for( i = iCol0 ; i <= iCol1 ; i++ ) {      
      *pOut++ = *pIn++;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

template <class T> bool pixq_Matrix<T>::GetLine( 
   int iRow,  // [i] row number 
   int iCol0, // [i] start column number
   int iCol1, // [i] end column number
   vector<T> *tRow ) // [o] buffer to contain the row in the matrix 
const
{
   bool bRetCode = false;
   //int nBufferSize;
   int i;
   T *pIn = NULL;

   if( !CheckRow( iRow ) ) goto PIX_EXIT;
   if( !CheckColRange( iCol0, iCol1 ) ) goto PIX_EXIT;
   
   // copy row to buffer
   
   pIn = _pDataRow[iRow] + iCol0;
   tRow->clear( );
   for( i = iCol0 ; i <= iCol1 ; i++ ) {      
      //tRow->at( i-iCol0 ) = *pIn++;
      tRow->push_back( *pIn++ );
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get a rectangle area of data from a specified area of the matrix into a one-dimensinal buffer
//
// returns:
// true or false
//
// notes:
// output buffer must be allocated beforehand.
// vector<T> is allocated iside this function
// output Matrix is allocated inside this function
// frame area are not copied.
// frame area are not changed by this operation.
//
// notes:
// out buffer must be allocated for the approproiate size in advance
// nPathWidth = iCol1 - iCol0
// nPathHeight = iRow1 - iRow0
// nPathSize = nPathWidth * nPathHeight
//
template <class T> bool pixq_Matrix<T>::getPatch(
   int iRow0,  // [i] row number 
   int iRow1,  // [i] row number 
   int iCol0, // [i] start column number
   int iCol1, // [i] end column number
   T *tBuff ) // [o] buffer to contain the row in the matrix 
const
{
   bool bRetCode = false;
   int i, j;
   T *pIn = NULL;
   T *pOut = NULL;

   if( !CheckRowRange( iRow0, iRow1 ) ) goto PIX_EXIT;
   if( !CheckColRange( iCol0, iCol1 ) ) goto PIX_EXIT;
   
   // copy row to buffer
   
   pOut = tBuff;
   for( i = iRow0 ; i <= iRow1 ; i++ ) {
      pIn = (T*)&_pDataRow[i][iCol0];      
      for( j = iCol0 ; j <= iCol1 ; j++ ) {      
         *pOut++ = *pIn++;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

template <class T> bool pixq_Matrix<T>::getPatch(
   int iRow0,  // [i] row number 
   int iRow1,  // [i] row number 
   int iCol0, // [i] start column number
   int iCol1, // [i] end column number
   vector<T> *tPatch ) // [o] buffer to contain the row in the matrix 
const
{
   bool bRetCode = false;
   int nRows, nCols, nBufferSize;
   int i, j, k;
   T *pIn = NULL;

   if( !CheckRowRange( iRow0, iRow1 ) ) goto PIX_EXIT;
   if( !CheckColRange( iCol0, iCol1 ) ) goto PIX_EXIT;
   
   // allocate vector
   
   nCols = iCol1 - iCol0 + 1;
   nRows = iRow1 - iRow0 + 1;
   nBufferSize = nCols * nRows;
   tPatch->resize( nBufferSize );
   //tPatch->clear( );

   // copy row to buffer
   
   k = 0;
   for( i = iRow0 ; i <= iRow1 ; i++ ) {
      pIn = (T*)&_pDataRow[i][iCol0];      
      
      for( j = iCol0 ; j <= iCol1 ; j++ ) {      
         //tPatch->push_back( *pIn++ );
         tPatch->at( k ) = *pIn++;
         k++;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// cut small patch area from matrix
//
// notes:
// output patch matrix must be allocated in advance
// returns error if patch range are not inside the input matrix
// start row must be smaller than or equal to the end row
// start column must be smaller than or equal to the end column
//
// if bFillOut is true, if the whole area of the patch is not inside
// matrix, pixels not included in the matrix are  filled by the value tFill.
// if bFillOut is false and if some oart of the patch goes outside of
// the matrix, it retuens false
//
template <class T> bool pixq_Matrix<T>::getPatch(int iCol0, // [i] patch start column
                                                 int iRow0, // [i] patch start row
                                                 int iCol1, // [i] patch end column
                                                 int iRow1, // [i] patch end row
                                                 pixq_Matrix<T> *pPatch ) // [o] 
{
   bool bRetCode = false;
   T tFill = Get( 0, 0 );

   if (!getPatch(iCol0, iRow0, iCol1, iRow1, false, tFill, pPatch)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}

//
// no check for the area position
// if the part of the patch is aout of matrix extent,
// thhet part is filled out with blank value
//
// notes:
// if bFillOut is set to true,
// area utside the matrix extent is filled with tFill
// otherwise, function returs error if some part of the patch is out of the matrix
//
template <class T> bool pixq_Matrix<T>::getPatch(int iCol0, // [i] patch start column
                                                 int iRow0, // [i] patch start row
                                                 int iCol1, // [i] patch end column
                                                 int iRow1, // [i] patch end row
                                                 bool bFillOut, // [i] outside processed?
                                                 T tFill, // [i]
                                                 pixq_Matrix<T> *pPatch ) // [o] 
{
   bool bRetCode = false;
   int nPatchWidth, nPatchHeight, nAreaHeight, nAreaWidth;
   int i, j, iRow, iCol;
   T tValue;

   // *** check area ***

   if (iCol0 > iCol1) {
      goto PIX_EXIT;
   }
   
   if (iRow0 > iRow1) {
      goto PIX_EXIT;
   }

   nPatchWidth = pPatch->getWidth();
   nPatchHeight = pPatch->getHeight();

   nAreaWidth = iCol1 - iCol0 + 1;
   nAreaHeight = iRow1 - iRow0 + 1;

   if( nPatchHeight < nAreaHeight || nPatchWidth < nAreaWidth ) {
      // patch matrix is not allocated for the correct size
      goto PIX_EXIT;
   }

   if( bFillOut ) {
      
      pPatch->Fill( tFill );

      int iRowStart = max( 0, iRow0 );
      int iRowEnd = min( _iNrows-1, iRow1 );
      int iColStart = max( 0, iCol0 );
      int iColEnd = min( _iNcols-1, iCol1 );

      for( i = iRowStart ; i <= iRowEnd ; i++ ) {
         iRow = i - iRow0;
         for( j = iColStart ; j <= iColEnd ; j++ ) {
            iCol = j - iCol0;            
            tValue = Get( i, j );
            pPatch->Set( iRow, iCol, tValue );
         }
      }

   } else {

      // all pixels of the patch must be inside the matrix

      if( 0 > iCol0 ) goto PIX_EXIT;
      if( 0 > iRow0 ) goto PIX_EXIT;
      if( _iNcols <= iCol1 ) goto PIX_EXIT;
      if( _iNrows <= iRow1 ) goto PIX_EXIT;

      for( i = 0 ; i < nAreaHeight ; i++ ) {
         iRow = iRow0 + i;
         for( j = 0 ; j < nAreaWidth ; j++ ) {
            iCol = iCol0 + j;
            tValue = Get( iRow, iCol );
            pPatch->Set( i, j, tValue );
         }
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}

//
// add a value to the specific item in the matrix
//
template <class T> void pixq_Matrix<T>::Add( int	iRow, // [i] row
                                           int   iCol, // [i] col
                                           T tValue )	// [i] value
{
   *(_pDataRow[iRow]+iCol) = *(_pDataRow[iRow]+iCol) + tValue;

	return;
}

template <class T> void pixq_Matrix<T>::Divide( T tDivide )
{
	int i, j;
   T tValue;
   T *pRow = NULL;

   if( (T)0 == tDivide ) {
      goto PIX_EXIT;
   }
   
   for( i = 0 ; i < _iNrows ; i++ ) {
      pRow = _pDataRow[i];
      for( j = 0 ; j < _iNcols ; j++ ) {
         tValue = *pRow;
	      *pRow = tValue / tDivide;
         *pRow++;
      }
   }

PIX_EXIT:
	return;
}

} // namespace _pix_plot_qt_framework 
