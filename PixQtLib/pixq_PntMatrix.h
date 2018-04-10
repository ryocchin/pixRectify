#pragma once

namespace _pix_plot_qt_framework {

template <class T> class pixq_PntMatrix
{
private:
   bool	   _bExtentSet;

   int      _iNrows;
   int      _iNcols;
   T	      **_Data;

   T	      _ExtentMin;
   T	      _ExtentMax;

public:
   pixq_PntMatrix(void);
   ~pixq_PntMatrix(void);

   int		ColSize() { return _iNcols; }
   int      RowSize() { return _iNrows; }
   bool		alloc(int nrows, int ncols);
   void	   free(void);
	void	   Set( int row, int col, T Value );
	T	      Get( int row, int col );
	void     GetExtent( T *pMin, T *pMax, bool bRecalc );

   bool copy(pixq_PntMatrix<T> *In);
   bool copy(pixq_PntMatrix<T> *Src, int iDestRow, int iDestCol);
   bool expand( int nTopRow, int nBottomRow, int nLeftCol, int nRightCol, T Value );     
};

//
// default constrcutor 
//
template <class T> pixq_PntMatrix<T>::pixq_PntMatrix()
{
   _iNrows = 0;
   _iNcols = 0;
   _Data = NULL;
   _bExtentSet = false;
}

//
// default destructor 
//
template <class T> pixq_PntMatrix<T>::~pixq_PntMatrix()
{
   _iNrows = 0;
   _iNcols = 0;
   _Data = NULL;
}

//
// get the extent of coordinate matrix 
//
template <class T> void pixq_PntMatrix<T>::GetExtent(
   T        *pMin,      // [o] extent, max
   T        *pMax,      // [o] extent, max
   bool     bRecalc )   // [i] true→以前に計算された範囲がある場合はそれを返す、false→新たに計算しなおす
{
   int i, j;
	T ep;
	short sFound;

   if (!bRecalc && _bExtentSet) {
      *pMin = _ExtentMin;
      *pMax = _ExtentMax;
      goto PIX_EXIT;
   }

	sFound = false;
   for (i = 0; !sFound && i < _iNrows; i++) {
      for (j = 0; !sFound && j < _iNcols; j++) {
         ep = _Data[i][j];
			if( 1 != ep.id ) continue;
         _ExtentMin = ep;
         _ExtentMax = ep;
			sFound = true;
		}
	}

	if( !sFound ) goto PIX_EXIT;

   for (i = 0; i < _iNrows; i++) {
      for (j = 0; j < _iNcols; j++) {
         ep = _Data[i][j];
			if( 1 != ep.id ) continue;
         _ExtentMin.Min(ep, _ExtentMin);
         _ExtentMax.Max(ep, _ExtentMax);
		}
	}

   *pMin = _ExtentMin;
   *pMax = _ExtentMax;
   _bExtentSet = true;
   
   // --- Done ---
PIX_EXIT:
   return;
}

template <class T> bool pixq_PntMatrix<T>::alloc(
int	nrows, 
int	ncols )
{
   _iNrows = nrows;
   _iNcols = ncols;

   _Data = new T*[nrows];
   if (NULL == _Data) return false;

	for( int i = 0 ; i < nrows ; i++ ) {
      _Data[i] = new T[ncols];
      if (NULL == _Data[i]) return false;
	}

   _bExtentSet = false;
	return true;
}


template <class T> void pixq_PntMatrix<T>::free(void)
{
   for (int i = 0; i < _iNrows; i++) {
      if (NULL != _Data[i]) {
         delete[] _Data[i];
      }
   }
	
   if (NULL != _Data) {
      delete[] _Data;
   }
   
   _Data = NULL;
   _bExtentSet = false;
   return;
}


template <class T> void pixq_PntMatrix<T>::Set(
int	      row,	   // [i] row
int         col,	   // [i] col
T	         value )	// [i] value
{
   _Data[row][col] = value;
	return;
}


template <class T> T pixq_PntMatrix<T>::Get(
int		row,	// [i] row
int		col )	// [i] col
{
   return _Data[row][col];
}


template <class T> bool pixq_PntMatrix<T>::copy(pixq_PntMatrix<T> *Src)
{
   bool bRetCode = false;

	T val;
   int i, j;
   int nRows = Src->_iNrows;
   int nCols = Src->_iNcols;
   _bExtentSet = false;
   
   if (!alloc(nRows, nCols)) goto PIX_EXIT;

   for (i = 0; i < _iNrows; i++) {
      for (j = 0; j < _iNcols; j++) {
         if (Src->_Data[i][j].bNull()) continue;
         _Data[i][j] = Src->_Data[i][j];
		}
	}

   // --- Done ---
   bRetCode = true;

PIX_EXIT:
   return bRetCode;
}



template <class T> bool pixq_PntMatrix<T>::copy(
   pixq_PntMatrix<T>  *Src,       // [i] source matrix
   int               iDestRow,   // [i] destination row, lower left coordinate
   int               iDestCol )  // [i] destination column lower left coordinate
{
   bool bRetCode = false;

	T val;
   int i, j, iRow, iCol;
   int nSrcRows = Src->_iNrows;
   int nSrcCols = Src->_iNcols;
   int nDestRows = _iNrows;
   int nDestCols = _iNcols;
   _bExtentSet = false;
   
	for( i = 0 ; i < nSrcRows ; i++ ) {
		iRow = i + iDestRow;
      if( 0 > iRow || iRow >= nDestRows ) continue;
      for( j = 0 ; j < nSrcCols ; j++ ) {
		   iCol = j + iDestCol;
         if( 0 > iCol || iCol >= nDestCols ) continue;
         if (Src->_Data[i][j].bNull()) continue;
         _Data[iRow][iCol] = Src->_Data[i][j];
		}
	}

   // --- Done ---
   bRetCode = true;

//PIX_EXIT:
   return bRetCode;
}

template <class T> bool pixq_PntMatrix<T>::expand(
   int   nTopRow,       // [i] number of rows to be added to the top, must be >0.
   int   nBottomRow,    // [i] number of rows to be added to the bottom, must be >0.
   int   nLeftCol,      // [i] number of columns to be added to the left, must be >0.
   int   nRightCol,     // [i] number of columns to be added to the right, must be >0.
   T     tNilValue )    // [i] destination column lower left coordinate
{
   bool bRetCode = false;
   pixq_PntMatrix<T> Tmp;

   int i, j, iRow, iCol, iStartRow, iStartCol;
   int nSrcRows = _iNrows;
   int nSrcCols = _iNcols;
   int nDestRows = _iNrows + nTopRow + nBottomRow;
   int nDestCols = _iNcols + nLeftCol + nRightCol;

   if( 0 > nTopRow ) goto PIX_EXIT;
   if( 0 > nBottomRow ) goto PIX_EXIT;
   if( 0 > nLeftCol ) goto PIX_EXIT;
   if( 0 > nRightCol ) goto PIX_EXIT;

   Tmp.copy(this);

   free();
   if (!alloc(nDestRows, nDestCols)) {
      goto PIX_EXIT;
   }
   
   _bExtentSet = false;
   
   // --- copy input matrix to the patch ---
	for( i = 0 ; i < nSrcRows ; i++ ) {
		iRow = i + nBottomRow;
      for( j = 0 ; j < nSrcCols ; j++ ) {
		   iCol = j + nLeftCol;
         if (Tmp._Data[i][j].bNull()) continue;
         _Data[iRow][iCol] = Tmp._Data[i][j];
		}
	}
  
   // --- fill the rest of the new matrix with nil value ---
	for( i = 0 ; i < nBottomRow ; i++ ) {
      for( j = 0 ; j < nDestCols ; j++ ) {
         _Data[i][j] = tNilValue;
		}
	}

	iStartRow = nBottomRow + nSrcRows;
   for( i = iStartRow ; i < nDestRows ; i++ ) {
      for( j = 0 ; j < nDestCols ; j++ ) {
         _Data[i][j] = tNilValue;
		}
	}

	iStartCol = nLeftCol + nSrcCols;
	for( i = nBottomRow ; i < iStartRow ; i++ ) {
      for( j = 0 ; j < nLeftCol ; j++ ) {
         _Data[i][j] = tNilValue;
		}

      for( j = iStartCol ; j < nDestCols ; j++ ) {
         _Data[i][j] = tNilValue;
		}
	}

   // --- Done ---
   bRetCode = true;

PIX_EXIT:
   Tmp.free();
   return bRetCode;
}

} // namespace _pix_plot_qt_framework 
