//
// pixq_Matrix
// 2D matrix class, data utility
//

namespace _pix_plot_qt_framework {

template <class T> bool pixq_Matrix<T>::copy( const pixq_Matrix<T> *pSrc )
{
   bool bRetCode = false;
   int i, j;
   bool bDiff = true;

   int nRows = _iNrows;
   int nCols = _iNcols;
   
   int nSrcRows = pSrc->_iNrows;
   int nSrcCols = pSrc->_iNcols;
   
   // check if this matrix is already assigned as the same size as source 

   bDiff = false;
   if (nRows != nSrcRows) {
      bDiff = true;
   }
   
   if (nCols != nSrcCols) {
      bDiff = true;
   }

   // realloc the matrix if necessary

   if( bDiff ) {
      free();
      if( !Alloc( nSrcRows, nSrcCols ) ) {
         goto PIX_EXIT;
      }
   }

   // copy all data

   for( i = 0 ; i < _iNrows ; i++ ) {
      for( j = 0 ; j < _iNcols ; j++ ) {
         _Data[i][j] = pSrc->_Data[i][j];
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// absolute difference, mtx0 - mtx1
//
template <class T> bool pixq_Matrix<T>::AbsoluteDiff( pixq_Matrix<T> *pMtx0,  // [i]
                                                      pixq_Matrix<T> *pMtx1 ) // [i]
{
   bool bRetCode = false;
   int i, j;
   bool bDiff = true;
   T tVal[2], tDiff;

   int nSrcRows[2];
   int nSrcCols[2];

   int nRows = _iNrows;
   int nCols = _iNcols;
   
   nSrcRows[0] = pMtx0->_iNrows;
   nSrcRows[1] = pMtx1->_iNrows;

   nSrcCols[0] = pMtx0->_iNcols;
   nSrcCols[1] = pMtx1->_iNcols;


   // check if two input matrices are same size 
   
   bDiff = false;
   if( nSrcRows[0] != nSrcRows[1] ) bDiff = true;
   if( nSrcCols[0] != nSrcCols[1] ) bDiff = true;

   if( bDiff ) {
      goto PIX_EXIT;
   }

   // realloc the matrix if necessary

   bDiff = false;
   if( nRows != nSrcRows[0] ) bDiff = true;
   if( nCols != nSrcCols[0] ) bDiff = true;

   if( bDiff ) {
      free();
      if( !Alloc( nSrcRows[0], nSrcCols[0] ) ) {
         goto PIX_EXIT;
      }
   }

   // copy all data

   for( i = 0 ; i < _iNrows ; i++ ) {
      for( j = 0 ; j < _iNcols ; j++ ) {
         tVal[0] = pMtx0->_Data[i][j];
         tVal[1] = pMtx1->_Data[i][j];
         if( tVal[0] >= tVal[1] ) {
            tDiff = tVal[0] - tVal[1];
         } else {
            tDiff = tVal[1] - tVal[0];
         }
         _Data[i][j] = tDiff;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
} 

//
// check the validity of the row number
//
template <class T> 
bool pixq_Matrix<T>::CheckRow( int iRow ) // [i] row number
const
{
   bool bRetCode = false;

   if( 0 > iRow ) goto PIX_EXIT;
   if( iRow >= _iNrows  ) goto PIX_EXIT;
      
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// check the validity of the column number
//
template <class T> 
bool pixq_Matrix<T>::CheckCol( int iCol ) // [i] column number
const
{
   bool bRetCode = false;

   if( 0 > iCol ) goto PIX_EXIT;
   if( iCol >= _iNcols ) goto PIX_EXIT;
      
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// check the validity of the row range
//
template <class T> bool pixq_Matrix<T>::CheckRowRange( int iRow0, // [i] first row number
                                                      int iRow1 ) // [i] second row number
const
{
   bool bRetCode = false;

   if( !CheckRow( iRow0 )  ) goto PIX_EXIT;
   if( !CheckRow( iRow1 )  ) goto PIX_EXIT;
   if( iRow0 > iRow1 ) goto PIX_EXIT;
      
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// check the validity of the column range
//
template <class T> bool pixq_Matrix<T>::CheckColRange( int iCol0, // [i] first column number
                                                      int iCol1 ) // [i] second column number
const
{
   bool bRetCode = false;

   if( !CheckCol( iCol0 ) ) goto PIX_EXIT;
   if( !CheckCol( iCol1 ) ) goto PIX_EXIT;
   if( iCol0 > iCol1 ) goto PIX_EXIT;
      
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// check if the given row and column is inside the valid matrix extent
// not including the frame area
//
template <class T> bool pixq_Matrix<T>::IsInside( 
   int iX, 
   int iY )
   const
{
   bool bRetCode = false;

   if (0 > iX || iX >= _iNcols) {
      goto PIX_EXIT;
   }
   
   if (0 > iY || iY >= _iNrows) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

template <class T> 
bool pixq_Matrix<T>::IsInside(
   float fX,
   float fY) 
   const
{
	int iX = (int)floor( 0.5 + fX );
	int iY = (int)floor( 0.5 + fY );

   return IsInside( iX, iY );
}

template <class T> bool pixq_Matrix<T>::IsInside( 
   double dX,
   double dY) 
   const
{
	int iX = (int)floor( 0.5 + dX );
	int iY = (int)floor( 0.5 + dY );

   return IsInside( iX, iY );
}

//
// crop rectangle area of matrix and create new matrix
//
// notes:
// need improvement! using line buffer
//
template <class T> bool pixq_Matrix<T>::crop(
   int nStartRow,  // [i] start row
   int nEndRow,    // [i] end row
   int nStartCol,  // [i] start column
   int nEndCol,    // [i] end column
   T tFill,       // [i] value to fill the outside area
   pixq_Matrix<T>  *pDest )    // [o] destination matrix 
const 
{
   bool bRetCode = false;
   int iRow, iCol, i, j, nOutRows, nOutCols;
   T tValue;

   if( nEndRow < nStartRow ) {
      goto PIX_EXIT;
   }
   
   if( nEndCol < nStartCol ) {
      goto PIX_EXIT;
   }

   pDest->free();

   nOutRows = nEndRow - nStartRow + 1;
   nOutCols = nEndCol - nStartCol + 1;

   if( !pDest->Alloc( nOutRows, nOutCols ) ) {
      goto PIX_EXIT;
   }

   for( i = nStartRow ; i <= nEndRow ; i++ ) {
      iRow = i - nStartRow;
      if( 0 > iRow || iRow >= _iNrows ) {
         for( j = nStartCol ; j <= nEndCol ; j++ ) {
            iCol = j - nStartCol;
            pDest->Set( iRow, iCol, tFill );
         }
         continue;
      }
      
      for( j = nStartCol ; j <= nEndCol ; j++ ) {
         iCol = j - nStartCol;
         if( 0 > iCol || iCol >= _iNcols ) {
            pDest->Set( iRow, iCol, tFill );
            continue;
         }

         tValue = Get( i, j );
         pDest->Set( iRow, iCol, tValue );
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

template <class T> bool pixq_Matrix<T>::crop(
   int nStartRow,  // [i] start row
   int nEndRow,    // [i] end row
   int nStartCol,  // [i] start column
   int nEndCol,    // [i] end column
   pixq_Matrix<T>  *pDest )    // [o] destination matrix 
const 
{
   bool bRetCode = false;
   T tNull = (T)0;
   
   if (!crop(nStartRow, nEndRow, nStartCol, nEndCol, tNull, pDest)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// crop the matrix 
//
// notes:
// matrix is altered
// if the new size is larger, pixels are filled by specifeid value
//
// bFromTop
// when new height is smaller than input height
// new matrix is filled from top if it is tru
// other wise, it is filled from the bottom
//
//  H-1 +-------------+----+    +------------------+
//      |             |////|    |///// bg /////////|
//      |             |////|    +-------------+////|
//      |             |////|    |             |////|
//      |             |////|    |             |////|
//      +-------------+////|    |             |////|
//      |///// bg /////////|    |             |////|
//    0 +------------------+    +-------------+----+
//       true                    false 
// 
template <class T> bool pixq_Matrix<T>::crop(
   int nNewHeight,   // [i] new height
   int nNewWidth,    // [i] new width
   T tFill,          // [o] destination matrix 
   bool bFromTop )   // [i] when new height is smaller than input
{
   bool bRetCode = false;
   int iRow, iRowShift, i, j;
   T tValue;
   pixq_Matrix<T> Dest;

   if( 0 >= nNewHeight ) {
      goto PIX_EXIT;
   }
   
   if( 0 >= nNewWidth ) {
      goto PIX_EXIT;
   }

   if( !Dest.Alloc( nNewHeight, nNewWidth ) ) {
      goto PIX_EXIT;
   }

   if( bFromTop ) {
      iRowShift = nNewHeight - _iNrows;
   } else {
      iRowShift = 0;
   }

   //

   for( i = 0 ; i < nNewHeight ; i++ ) {
      iRow = i - iRowShift;
      if( 0 > iRow || _iNrows <= iRow ) {
         for( j = 0 ; j < nNewWidth ; j++ ) {
            Dest.Set( i, j, tFill );
         }
      } else {
         for( j = 0 ; j < nNewWidth ; j++ ) {
            if( j >= _iNcols ) {
               tValue = tFill;
            } else {
               tValue = Get( iRow, j );
            }
            Dest.Set( i, j, tValue );
         }
      }
   }

   //

   free();
   copy( &Dest );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   Dest.free();
   return bRetCode;
}

} // namespace _pix_plot_qt_framework 

