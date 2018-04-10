//
// pixq_Matrix
// 2D matrix class
//
#pragma once

namespace _pix_plot_qt_framework {


template <class T> class pixq_Matrix
{
public:
	pixq_Matrix( void );
	~pixq_Matrix( void );

public:
   // matrix height
	int _iNrows;
   
   // matrix width
	int _iNcols;

   // matrix real body

	T **_Data;

   // pointer to top of each row

   T **_pDataRow;
   
   // frame number, additional info used for image frames 
   int _iFrameNumber;

public:
   int getWidth(void) const { return _iNcols; }
   int getHeight(void) const { return _iNrows; }

public:
   // allocate matrix
	virtual bool Alloc( int nRows, int nCols );
   virtual bool checkAlloc(int nRows, int nCols);

   // release matrix
   virtual void free(void);
	
   // *** data handling ***
   // pixq_MatrixData.h

	// set the value at given position

   void Set( int row, int col, T Value );
   
   T Get( int row, int col ) const;
 
   //T (*Get)Get( double dX, double dY );

   // fill the matrix with a given constant value
   void Fill( T Value );

   // get a row of data from the matrix into a one-dimensinal buffer
   bool GetRow( int iRow, T *tBuff ) const; 
   bool GetRow( int iRow, vector<T> *tRow ) const; 
   
   // set a data into the row in the matrix from a one-dimensinal buffer
   bool SetRow( int iRow, T *tBuff ); 

   // get a data from the whole matrix into a one-dimensinal buffer
   bool GetData( T *tBuff ); 

   // set a data into the whole matrix from a one-dimensinal buffer
   bool SetData( T *tBuff ); 

   // get a range of fata from a specified row of the matrix into a one-dimensinal buffer
   bool GetLine( int iRow, int Col0, int iCol1, T *tBuff ) const; 
   bool GetLine( int iRow, int Col0, int iCol1, vector<T> *tRow ) const; 

   // get a rectangle area of data from a specified area of the matrix 
   // into a one-dimensinal buffer
   bool getPatch(int iRow0, int iRow1, int Col0, int iCol1, T *tBuff) const;
   bool getPatch(int iRow0, int iRow1, int Col0, int iCol1, vector<T> *tPatch) const;

   bool getPatch(int iCol0, int iRow0, int iCol1, int iRow1, pixq_Matrix<T> *pPatch);
   bool getPatch(int iCol0, int iRow0, int iCol1, int iRow1,
      bool bFillOut, T tFill, pixq_Matrix<T> *pPatch );

   // *** utility functions ***
   // pixq_MatrixUt.h
      
   bool copy( const pixq_Matrix<T> *pSrc );

   // absolute difference, mtx0 - mtx1
   bool AbsoluteDiff( pixq_Matrix<T> *pMtx0, pixq_Matrix<T> *pMtx1 );

   // check the validity of the row number
   bool CheckRow( int iRow ) const;
   
   // check the validity of the column number
   bool CheckCol( int iCol ) const;

   // check the validity of the row range
   bool CheckRowRange( int iRow0, int iRow1 ) const;
   
   // check the validity of the column range
   bool CheckColRange( int iCol0, int iCol1 ) const;

   // check if the point(row/col) is inside the matrix range
   bool IsInside( int iX, int iY ) const;
   bool IsInside(float fX, float fY) const;
   bool IsInside(double dX, double dY) const;

   // *** matrix analysis ***

   void Statistics( T *vmin, T *vmax ) const;
   void Statistics( T *vmin, T *vmax, T *mean ) const;
   void Statistics( T *vmin, T *vmax, T *mean, T *stdev ) const;

   T mean( void) const;
   T stDev( void) const;

   void Statistics( T *vmin, T *vmax, const pixq_Matrix<bool> *pMask ) const;
   void Statistics( T *vmin, T *vmax, T *mean, const pixq_Matrix<bool> *pMask ) const;
   void Statistics( T *vmin, T *vmax, T *mean, T *stdev, const pixq_Matrix<bool> *pMask ) const;

   // *** linear algebra ***

   // get determinant of 3X3 matrix
   bool GetDeterminant3X3( T *tDet );

   // get inrverse matrix of of 3X3 matrix
   bool getInverse3x3( pixq_Matrix<T> *Inv );

   // get inrverse matrix of of NXN matrix
   bool GetInverse( pixq_Matrix<T> *Inv );

   // create new matrix as a product of two square amtrix
   bool ProductSquare( pixq_Matrix<T> *pMtx0, pixq_Matrix<T> *pMtx1 );

	void Add( int row, int col, T Value );
	void Divide( T Value );

   // product of two matices of equal size

   bool sqrProduct( pixq_Matrix<T> *Mtx0, pixq_Matrix<T> *Mtx1 );

   // crop the specific area of the matrix or expand and create new matrix

   bool crop(int nTopRow, int nBottomRow, int nLeftCol, int nRightCol,
      T tFill, pixq_Matrix<T> *pDest ) const; 

   bool crop(int nTopRow, int nBottomRow, int nLeftCol, int nRightCol,
      pixq_Matrix<T> *pDest ) const; 

   virtual bool crop(int nNewHeight, int nNewWidth, T tFill, bool bFromTop);

   bool Transpose( pixq_Matrix<T> *pIn );

   void resetFrameNumber(void) { _iFrameNumber = -1; }
   void setFrameNumber(int iFrame) { _iFrameNumber = iFrame; }
   int getFrameNumber(void) { return _iFrameNumber; }

public:
   // make identity
   bool Identity(void);
};

} // namespace _pix_plot_qt_framework 

namespace _pix_plot_qt_framework {

template <class T> pixq_Matrix<T>::pixq_Matrix( void )
{
	_iNrows = 0;
	_iNcols = 0;

   _Data = (T**)NULL;	
   _pDataRow = (T**)NULL;		

   _iFrameNumber = -1;

   return;
}

template <class T> pixq_Matrix<T>::~pixq_Matrix( void )
{
   free();

   _Data = (T**)NULL;	
   _pDataRow = (T**)NULL;

   return;
}

//
// allocate matrix with no frame
//
template <class T> bool pixq_Matrix<T>::Alloc( 
   int nRows, // [i] Height of the matrix
   int nCols ) // [i] Width of the matrix
{
	bool bRetCode = false;
   int i;
   bool bRealloc;

   if( 0 >= nRows ) goto PIX_EXIT;
   if( 0 >= nCols ) goto PIX_EXIT;


   // check if realloc is required
   bRealloc = false;
   if( !_Data ) {
      bRealloc = true;
   }

   if( !bRealloc ) {
      if( _iNrows != nRows ) {
         bRealloc = true;
      }
      
      if( _iNcols != nCols ) {
         bRealloc = true;
      }
   }

   if( !bRealloc ) {
      // no need to re allocation, same as current size!
      bRetCode = true;
      goto PIX_EXIT;
   }

   free();

   _iNrows = nRows;
	_iNcols = nCols;

	_Data = new T*[_iNrows];
   if( !_Data ) {
      goto PIX_EXIT;
   }

   for( i = 0 ; i < _iNrows ; i++ ) {
      _Data[i] = new T[_iNcols];
      if( !_Data[i] ) {
         goto PIX_EXIT;
      }
   }

   // --- set row/col top position table excluding frames  ---

	_pDataRow = new T*[_iNrows];
	if( NULL == _pDataRow ) goto PIX_EXIT;

   for( i = 0 ; i < _iNrows ; i++ ) {
      _pDataRow[i] = (T*)( _Data[i] );
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}

//
// allocate matrix with no frame
// check if the current dimension is same as new dimension
// if identicall return as it is
// if not, release and allocate new matrices
//
template <class T> bool pixq_Matrix<T>::checkAlloc(
   int nRows,  // [i] Height of the matrix
   int nCols ) // [i] Width of the matrix
{
	bool bRetCode = false; 

   if( nRows == _iNrows && nCols == _iNcols ) {
      bRetCode = true;
      goto PIX_EXIT;
   }

   free();

   if( !Alloc( nRows, nCols ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}

//
// release matrix
//
template <class T> void pixq_Matrix<T>::free(void)
{
   int i;

   if( 0 >= _iNrows || 0 >= _iNcols ) {
	   _iNrows = 0;
	   _iNcols = 0;
      return;
   }

   for( i = 0 ; i < _iNrows ; i++ ) {
      if( _Data[i] ) {
         delete[] _Data[i];
         _Data[i] = NULL;
      }
   }

   if( _Data ) {
      delete[] _Data;
      _Data = NULL;
   }

   if( _pDataRow ) {
      delete[] _pDataRow;
      _pDataRow = (T**)NULL;
   }

   _iNrows = 0;
   _iNcols = 0;

   _iFrameNumber = -1;

   return;
}

//
// make identity matrix
//
// notes:
// it fails if matrix is not square
//
template <class T> bool pixq_Matrix<T>::Identity(void)
{
   bool bRetCode = false;
   int k;

   if (_iNrows != _iNcols) {
      goto PIX_EXIT;
   }

   Fill((T)0);

   for (k = 0; k < _iNrows; k++) {
      Set(k, k, (T)1);
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


} // namespace _pix_plot_qt_framework 

// matrix data handling functions
#include "pixq_MatrixData.h"

// matrix analysis, statistics and histogram, etc
#include "pixq_MatrixStat.h"

// matrix processing utility
#include "pixq_MatrixUt.h"

// basic linear algebra
#include "pixq_MatrixLa.h"

