#pragma once

namespace _pix_plot_qt_framework {
   
enum {
   CooMatrixModeNul = 0,
   CooMatrixMode2D = 1,
   CooMatrixMode3D = 2
};

template <class T> class pixq_CooMatrix
{
private:
   int      _iNrows;
   int      _iNcols;
   int      _iNsize;
   
   short    _sMode;  // coordinate type, 2D or 3D
   int      *_iRowLoc;
   int      *_iID;
   T	      *_CooX;
   T	      *_CooY;
   T	      *_CooZ;

   bool	   _bExtentSet;
   T	      _ExtentMinX;
   T	      _ExtentMaxX;
   T	      _ExtentMinY;
   T	      _ExtentMaxY;
   T	      _ExtentMinZ;
   T	      _ExtentMaxZ;

public:
   pixq_CooMatrix(void);
   pixq_CooMatrix(short sMode);
   ~pixq_CooMatrix(void);

   void     GetExtent(pixq_Dbl2D *pMin, pixq_Dbl2D *pMax, bool bRecalc = true);
   void     GetExtent(pixq_Dbl3D *pMin, pixq_Dbl3D *pMax, bool bRecalc = true);
	void     GetExtentX( T *pMin, T *pMax, bool bRecalc = true );
	void     GetExtentY( T *pMin, T *pMax, bool bRecalc = true );
	void     GetExtentZ( T *pMin, T *pMax, bool bRecalc = true );
	void     GetBuffExtent( int *pIDBuff, T *pBuff, T *pMin, T *pMax );

	bool		alloc( short sMode, int nrows, int ncols );
   void     Clear( void );

   int		ColSize() { return _iNcols; }
   int      RowSize() { return _iNrows; }
   void	   free(void);

	void	   Set( int row, int col, int id, T x, T y );
	void	   Set( int row, int col, int id, T x, T y, T z );
   void     Set(int row, int col, pixq_Dbl2D pnt);
   void     Set(int row, int col, pixq_Dbl3D pnt);

	int      GetID( int row, int col );
	T	      GetX( int row, int col );
	T	      GetY( int row, int col );
	T	      GetZ( int row, int col );
	void	   Get( int row, int col, int *id, T *x, T *y );
	void	   Get( int row, int col, int *id, T *x, T *y, T *z );
   void	   Get(int row, int col, pixq_Dbl2D *pnt);
   void	   Get(int row, int col, pixq_Dbl3D *pnt);

   void Fill(pixq_Dbl3D Pnt);

   bool copy(pixq_CooMatrix<T> *In);
   bool copy(pixq_CooMatrix<T> *Src, int iDestRow, int iDestCol);
   bool expand(int nTopRow, int nBottomRow, int nLeftCol, int nRightCol);
};

} // namespace _pix_plot_qt_framework 

namespace _pix_plot_qt_framework {

//
// default constrcutor 
//
template <class T> pixq_CooMatrix<T>::pixq_CooMatrix(void)
{
   _iNrows = 0;
   _iNcols = 0;
   _iNsize = 0;
   _sMode = CooMatrixModeNul;  // coordinate type, 2D or 3D
   _iRowLoc = NULL;
   _iID = NULL;
   _CooX = NULL;
   _CooY = NULL;
   _CooZ = NULL;
   _bExtentSet = false;
}

template <class T> pixq_CooMatrix<T>::pixq_CooMatrix(short sMode)
{
   _iNrows = 0;
   _iNcols = 0;
   _iNsize = 0;
   _sMode = sMode;  // coordinate type, 2D or 3D
   _iRowLoc = NULL;
   _iID = NULL;
   _CooX = NULL;
   _CooY = NULL;
   _CooZ = NULL;
   _bExtentSet = false;
}

//
// default destructor 
//
template <class T> pixq_CooMatrix<T>::~pixq_CooMatrix()
{
   _iNrows = 0;
   _iNcols = 0;
   _sMode = CooMatrixModeNul;  // coordinate type, 2D or 3D
   _iRowLoc = NULL;
   _iID = NULL;
   _CooX = NULL;
   _CooY = NULL;
   _CooZ = NULL;
   _bExtentSet = false;
}

//
// get the extent of coordinate matrix 
//

template <class T> void pixq_CooMatrix<T>::GetExtent(
   pixq_Dbl2D  *pMin,
   pixq_Dbl2D  *pMax,
      bool bRecalc /* = true */ )
{
   T xMin, xMax, yMin, yMax;
   GetExtentX( &xMin, &xMax, bRecalc );
   GetExtentY( &yMin, &yMax, bRecalc );
   pMin->Set( 0, (double)xMin, (double)yMin );
   pMax->Set( 0, (double)xMax, (double)yMax ); 
   return;
}

template <class T> void pixq_CooMatrix<T>::GetExtent(pixq_Dbl3D *pMin, 
   pixq_Dbl3D *pMax, 
   bool bRecalc /* = true */)
{
   T xMin, xMax, yMin, yMax, zMin, zMax;
   GetExtentX( &xMin, &xMax, bRecalc );
   GetExtentY( &yMin, &yMax, bRecalc );
   GetExtentZ( &zMin, &zMax, bRecalc );
   pMin->Set( 0, (double)xMin, (double)yMin, (double)zMin );
   pMax->Set( 0, (double)xMax, (double)yMax, (double)zMax ); 
   return;
}

template <class T> void pixq_CooMatrix<T>::GetExtentX(
   T        *pMin,      // [o] extent, min
   T        *pMax,      // [o] extent, max
   bool     bRecalc )
{
   if (!bRecalc && _bExtentSet) {
      *pMin = _ExtentMinX;
      *pMax = _ExtentMaxX;
   } else {
      GetBuffExtent(_iID, _CooX, pMin, pMax);
      _ExtentMinX = *pMin;
      _ExtentMaxX = *pMax;
   }
   return;
}

template <class T> void pixq_CooMatrix<T>::GetExtentY(
   T        *pMin,      // [o] extent, min
   T        *pMax,      // [o] extent, max
   bool     bRecalc )
{
   if (!bRecalc && _bExtentSet) {
      *pMin = _ExtentMinY;
      *pMax = _ExtentMaxY;
   } else {
      GetBuffExtent(_iID, _CooY, pMin, pMax);
      _ExtentMinY = *pMin;
      _ExtentMaxY = *pMax;
   }
   return;
}


template <class T> void pixq_CooMatrix<T>::GetExtentZ(
   T        *pMin,      // [o] extent, min
   T        *pMax,      // [o] extent, max
   bool     bRecalc )
{
   if (!bRecalc && _bExtentSet) {
      *pMin = _ExtentMinZ;
      *pMax = _ExtentMaxZ;
   } else {
      if (CooMatrixMode3D == _sMode) {
         GetBuffExtent(_iID, _CooZ, pMin, pMax);
      } else {
         *pMin = 0.0;
         *pMax = 0.0;
      }
      _ExtentMinZ = *pMin;
      _ExtentMaxZ = *pMax;
   }
   return;
}



template <class T> void pixq_CooMatrix<T>::GetBuffExtent(
   int      *pIDBuff,   // [i] ID buffer
   T        *pBuff,     // [i] data buffer
   T        *pMin,      // [o] extent, max
   T        *pMax )     // [o] extent, max
{
   int i;
	short sFound;
   T vMin, vMax;

	sFound = false;
   for (i = 0; !sFound && i < _iNsize; i++) {
	   if( 1 != pIDBuff[i] ) continue;
		vMin = pBuff[i];
		vMax = pBuff[i];
      sFound = true;
	}

   if( !sFound ) { 
		vMin = NODATA;
		vMax = NODATA;
      goto PIX_EXIT;
   }

   for (i = 0; i < _iNsize; i++) {
	   if( 1 != pIDBuff[i] ) continue;
		vMin = min( pBuff[i], vMin );
		vMax = max( pBuff[i], vMax );
	}

   *pMin = vMin;
   *pMax = vMax;
   
   // --- Done ---
PIX_EXIT:
   return;
}

template <class T> bool pixq_CooMatrix<T>::alloc(
   short sMode,
   int	nrows, 
   int	ncols )
{
   bool bRetCode = false;
   int iLoc;

   if( CooMatrixMode2D != sMode && CooMatrixMode3D != sMode ) goto PIX_EXIT;

   _sMode = sMode;
   _iNrows = nrows;
   _iNcols = ncols;
   _iNsize = nrows * ncols;
   _bExtentSet = false;

   _iRowLoc = new int[nrows];
   if (NULL == _iRowLoc) {
      goto PIX_EXIT;
   }

	iLoc = 0;
   for( int i = 0 ; i < nrows ; i++ ) {
      _iRowLoc[i] = iLoc;
      iLoc = iLoc + ncols;
	}

   _iID = new int[_iNsize];
   if (NULL == _iID) {
      goto PIX_EXIT;
   }

   _CooX = new T[_iNsize];
   if (NULL == _CooX) {
      goto PIX_EXIT;
   }

   _CooY = new T[_iNsize];
   if (NULL == _CooY) {
      goto PIX_EXIT;
   }

   if( CooMatrixMode3D == sMode ) {
      _CooZ = new T[_iNsize];
      if (NULL == _CooZ) {
         goto PIX_EXIT;
      }
   }

   // --- clear all id ---
   Clear( );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}


//
// 全点のIDをゼロにセットすることでデータが入ってないことを示す
//
template <class T> void pixq_CooMatrix<T>::Clear(void)
{
   // --- clear all id ---

   for (int i = 0; i < _iNsize; i++) {
      _iID[i] = 0;
   }

	return;
}


template <class T> void pixq_CooMatrix<T>::free(void)
{	
   if (NULL != _iRowLoc) {
      delete[] _iRowLoc;
      _iRowLoc = NULL;
   }
   
   if (NULL != _iID) {
      delete[] _iID;
      _iID = NULL;
   }
   
   if (NULL != _CooX) {
      delete[] _CooX;
      _CooX = NULL;
   }
   
   if (NULL != _CooY) {
      delete[] _CooY;
      _CooY = NULL;
   }
   
   if (NULL != _CooZ) {
      delete[] _CooZ;
      _CooZ = NULL;
   }
   
   _bExtentSet = false;

   return;
}


template <class T> void pixq_CooMatrix<T>::Set(
int	      row,	   // [i] row
int         col,	   // [i] col
int         id,      // [i] id
T	         x,	      // [i] x coordinate
T	         y )	   // [i] y coordinate
{
   int iLoc = _iRowLoc[row] + col;
   _iID[iLoc] = id;
   _CooX[iLoc] = x;
   _CooY[iLoc] = y;

	return;
}

template <class T> void pixq_CooMatrix<T>::Set(
int	      row,	   // [i] row
int         col,	   // [i] col
int         id,      // [i] id
T	         x,	      // [i] x coordinate
T	         y, 	   // [i] y coordinate
T	         z )	   // [i] z coordinate
{
   int iLoc = _iRowLoc[row] + col;
   _iID[iLoc] = id;
   _CooX[iLoc] = x;
   _CooY[iLoc] = y;

   if (CooMatrixMode3D == _sMode) {
      _CooZ[iLoc] = z;
   }
   
   return;
}

template <class T> void pixq_CooMatrix<T>::Set(
int	      row,	   // [i] row
int         col,	   // [i] col
pixq_Dbl3D     pnt)    // [i] 3D coo
{
   int id;
   T x, y, z;
   id = pnt._iID;
   x = (T)pnt._dX;
   y = (T)pnt._dY;
   z = (T)pnt._dZ;
   Set( row, col, id, x, y, z );
	return;
}

template <class T> void pixq_CooMatrix<T>::Set(
int	      row,	   // [i] row
int         col,	   // [i] col
pixq_Dbl2D     pnt)    // [i] 3D coo
{
   int id;
   T x, y, z;
   id = pnt._iID;
   x = (T)pnt._dX;
   y = (T)pnt._dY;
   Set( row, col, id, x, y );
	return;
}


template <class T> int pixq_CooMatrix<T>::GetID(
int row,	// [i] row
int col ) // [i] col
{
   int iLoc = _iRowLoc[row] + col;
   return _iID[iLoc];
}

template <class T> T pixq_CooMatrix<T>::GetX(
int row, // [i] row
int col ) // [i] col
{
   int iLoc = _iRowLoc[row] + col;
   return _CooX[iLoc];
}


template <class T> T pixq_CooMatrix<T>::GetY(
int row, // [i] row
int col ) // [i] col
{
   int iLoc = _iRowLoc[row] + col;
   return _CooY[iLoc];
}

template <class T> T pixq_CooMatrix<T>::GetZ(
int row, // [i] row
int col ) // [i] col
{
   int iLoc = _iRowLoc[row] + col;
   return _CooZ[iLoc];
}


template <class T> void pixq_CooMatrix<T>::Get(
int	      row,	   // [i] row
int         col,	   // [i] col
int         *id,     // [o] id
T	         *x,	   // [o] x coordinate
T	         *y ) 	   // [o] y coordinate
{
   int iLoc = _iRowLoc[row] + col;
   *id = _iID[iLoc];
   *x = _CooX[iLoc];
   *y = _CooY[iLoc];
	return;
}


template <class T> void pixq_CooMatrix<T>::Get(
int	      row,	   // [i] row
int         col,	   // [i] col
int         *id,     // [o] id
T	         *x,	   // [o] x coordinate
T	         *y, 	   // [o] y coordinate
T	         *z )	   // [o] z coordinate
{
   int iLoc = _iRowLoc[row] + col;
   *id = _iID[iLoc];
   *x = _CooX[iLoc];
   *y = _CooY[iLoc];
   *z = (CooMatrixMode3D == _sMode) ? _CooZ[iLoc] : 0.0;
	return;
}


template <class T> void pixq_CooMatrix<T>::Get(
int	      row,	   // [i] row
int         col,	   // [i] col
pixq_Dbl2D     *pnt)
{
   int id;
   T x, y; 
   Get( row, col, &id, &x, &y );
   pnt->Set( id, (double)x, (double)y );
	return;
}

template <class T> void pixq_CooMatrix<T>::Get(
int	      row,	   // [i] row
int         col,	   // [i] col
pixq_Dbl3D *pnt)
{
   int id;
   T x, y, z; 
   Get( row, col, &id, &x, &y, &z );
   pnt->Set( id, (double)x, (double)y, (double)z );
	return;
}

template <class T> bool pixq_CooMatrix<T>::copy(pixq_CooMatrix<T> *Src)
{
   bool bRetCode = false;

   int i;
   int nRows = Src->_iNrows;
   int nCols = Src->_iNcols;
   _bExtentSet = false;
   
   if (!alloc(Src->_sMode, nRows, nCols)) {
      goto PIX_EXIT;
   }

   if (CooMatrixMode2D == _sMode) {
      for (i = 0; i < _iNsize; i++) {
         if (1 != Src->_iID[i]) continue;
         _iID[i] = Src->_iID[i];
         _CooX[i] = Src->_CooX[i];
         _CooY[i] = Src->_CooY[i];
	   }
   } else {
      for (i = 0; i < _iNsize; i++) {
         if (1 != Src->_iID[i]) continue;
         _iID[i] = Src->_iID[i];
         _CooX[i] = Src->_CooX[i];
         _CooY[i] = Src->_CooY[i];
         _CooZ[i] = Src->_CooZ[i];
	   }
   }
   // --- Done ---
   bRetCode = true;

PIX_EXIT:
   return bRetCode;
}

template <class T> bool pixq_CooMatrix<T>::copy(
   pixq_CooMatrix<T>  *Src,       // [i] source matrix
   int               iDestRow,   // [i] destination row, lower left coordinate
   int               iDestCol )  // [i] destination column lower left coordinate
{
   bool bRetCode = false;

	T x, y, z;
   int id, i, j, iRow, iCol;
   int nSrcRows = Src->_iNrows;
   int nSrcCols = Src->_iNcols;
   int nDestRows = _iNrows;
   int nDestCols = _iNcols;
   _bExtentSet = false;
   
   if (CooMatrixMode2D == _sMode) {
		for( i = 0 ; i < nSrcRows ; i++ ) {
			iRow = i + iDestRow;
         if( 0 > iRow || iRow >= nDestRows ) continue;
         for( j = 0 ; j < nSrcCols ; j++ ) {
			   iCol = j + iDestCol;
            if( 0 > iCol || iCol >= nDestCols ) continue;
				
            Src->Get( i, j, &id, &x, &y );
            if( 1 != id ) continue;
				Set( iRow, iCol, id, x, y );
			}
		}
   } else {
		for( i = 0 ; i < nSrcRows ; i++ ) {
			iRow = i + iDestRow;
         if( 0 > iRow || iRow >= nDestRows ) continue;
         for( j = 0 ; j < nSrcCols ; j++ ) {
			   iCol = j + iDestCol;
            if( 0 > iCol || iCol >= nDestCols ) continue;
				
            Src->Get( i, j, &id, &x, &y, &z );
            if( 1 != id ) continue;
				Set( iRow, iCol, id, x, y, z );
			}
		}
   }

   // --- Done ---
   bRetCode = true;

//PIX_EXIT:
   return bRetCode;
}



template <class T> bool pixq_CooMatrix<T>::expand(
   int   nTopRow,       // [i] number of rows to be added to the top, must be >0.
   int   nBottomRow,    // [i] number of rows to be added to the bottom, must be >0.
   int   nLeftCol,      // [i] number of columns to be added to the left, must be >0.
   int   nRightCol )    // [i] number of columns to be added to the right, must be >0.
{
   bool bRetCode = false;
	T x, y, z;
   int id;
   pixq_CooMatrix<T> Tmp;

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

   if (!alloc(_sMode, nDestRows, nDestCols)) {
      goto PIX_EXIT;
   }
   
   _bExtentSet = false;
   
   // --- copy input matrix to the patch ---
	for( i = 0 ; i < nSrcRows ; i++ ) {
		iRow = i + nBottomRow;
      for( j = 0 ; j < nSrcCols ; j++ ) {
		   iCol = j + nLeftCol;
         Tmp.Get( i, j, &id, &x, &y, &z );
			if( 1 != id ) continue;
         Set( iRow, iCol, id, x, y, z );
		}
	}
  
   // --- fill the rest of the new matrix with nil value ---
	id = 0;
   x = y = z = (T)0;
   for( i = 0 ; i < nBottomRow ; i++ ) {
      for( j = 0 ; j < nDestCols ; j++ ) {
			Set( i, j, id, x, y, z );
		}
	}

	iStartRow = nBottomRow + nSrcRows;
   for( i = iStartRow ; i < nDestRows ; i++ ) {
      for( j = 0 ; j < nDestCols ; j++ ) {
			Set( i, j, id, x, y, z );
		}
	}

	iStartCol = nLeftCol + nSrcCols;
	for( i = nBottomRow ; i < iStartRow ; i++ ) {
      for( j = 0 ; j < nLeftCol ; j++ ) {
			Set( i, j, id, x, y, z );
		}

      for( j = iStartCol ; j < nDestCols ; j++ ) {
			Set( i, j, id, x, y, z );
		}
	}

   // --- Done ---
   bRetCode = true;

PIX_EXIT:
   Tmp.free();
   return bRetCode;
}


template <class T> void pixq_CooMatrix<T>::Fill(pixq_Dbl3D Pnt)     // [i] value to fill
{
   int i, j;
   for (i = 0; i < _iNrows; i++) {
      for (j = 0; j < _iNcols; j++) {
	      Set( i, j, Pnt );
      }
	}
}

} // namespace _pix_plot_qt_framework 
