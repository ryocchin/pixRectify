#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImageMatrix.h"

pixq_ImageMatrix::pixq_ImageMatrix( void )
{
   _nValidWidth = 0;
   _nValidHeight = 0;
   return;
}

pixq_ImageMatrix::~pixq_ImageMatrix( void )
{
   return;
}

bool pixq_ImageMatrix::Alloc( int nRows, // [i] Height of the matrix
                            int nCols ) // [i] Width of the matrix
{
	bool bRetCode = false;
   
   if( !pixq_Matrix::Alloc( nRows, nCols ) ) {
      goto PIX_EXIT;
   }
   
   _nValidWidth = nCols;
   _nValidHeight = nRows;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}

bool pixq_ImageMatrix::checkAlloc(int nRows,  // [i] Height of the matrix
                                 int nCols ) // [i] Width of the matrix
{
	bool bRetCode = false;

   if (!pixq_Matrix::checkAlloc(nRows, nCols)) {
      goto PIX_EXIT;
   }
   
   // valid width, height are not updated by alloc
   _nValidWidth = nCols;
   _nValidHeight = nRows;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}

void pixq_ImageMatrix::free(void)
{   
   // free the matrix data

   pixq_Matrix::free();
   
   // then reset the image size of original data
   _nValidWidth = 0;
   _nValidHeight = 0;


   return;
}

//
// convert double image matrix to pixq_ImageMatrix
//
bool pixq_ImageMatrix::getDouble(const pixq_Matrix<double> *dMtx)
{
   bool bRetCode = false;
   int i, j;
   unsigned short usValue;
   double dValue;
   double dMax = 65535.0;

   int nWidth = dMtx->getWidth();
   int nHeight = dMtx->getHeight();

   if (0 >= nWidth) {
      goto PIX_EXIT;
   }

   if (0 >= nHeight) {
      goto PIX_EXIT;
   }

   if (!Alloc(nHeight, nWidth)) {
      goto PIX_EXIT;
   }

   for (i = 0; i < nHeight; i++) {
      for (j = 0; j < nWidth; j++) {
         dValue = dMtx->Get(i, j);
         if (0.0 > dValue) {
            usValue = 0;
         }
         else  if (dMax < dValue) {
            usValue = 65535;
         }
         else {
            usValue = (unsigned short)dValue;
         }

         Set(i, j, usValue);
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// crop rectangle area of matrix and create new matrix
//
// notes:
// need improvement! using line buffer
//
bool pixq_ImageMatrix::cropImage(
   int nStartRow,  // [i] start row
   int nEndRow,    // [i] end row
   int nStartCol,  // [i] start column
   int nEndCol,    // [i] end column
   pixq_ImageMatrix  *pDest)    // [o] destination matrix 
   const
{
   bool bRetCode = false;
   int iRow, iCol, i, j, nOutRows, nOutCols;
   unsigned short usValue;

   unsigned short usNull = 0;

   if (nEndRow < nStartRow) {
      goto PIX_EXIT;
   }

   if (nEndCol < nStartCol) {
      goto PIX_EXIT;
   }

   pDest->free();
   nOutRows = nEndRow - nStartRow + 1;
   nOutCols = nEndCol - nStartCol + 1;

   if (!pDest->Alloc(nOutRows, nOutCols)) {
      goto PIX_EXIT;
   }

   for (i = nStartRow; i <= nEndRow; i++) {
      iRow = i - nStartRow;
      if (0 > iRow || iRow >= _iNrows) {
         for (j = nStartCol; j <= nEndCol; j++) {
            iCol = j - nStartCol;
            pDest->Set(iRow, iCol, usNull);
         }
         continue;
      }

      for (j = nStartCol; j <= nEndCol; j++) {
         iCol = j - nStartCol;
         if (0 > iCol || iCol >= _iNcols) {
            pDest->Set(iRow, iCol, usNull);
            continue;
         }

         usValue = Get(i, j);
         pDest->Set(iRow, iCol, usValue);
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_ImageMatrix::crop(int nNewHeight,
   int nNewWidth,
   unsigned short usFill,
   bool bFromTop)
{
   bool bRetCode = false;
   int nValidWidth = getWidth();
   int nValidHeight = getHeight();

   if (!pixq_Matrix::crop(nNewHeight, nNewWidth, usFill, bFromTop)) {
      goto PIX_EXIT;
   }

   _nValidWidth = nValidWidth;
   _nValidHeight = nValidHeight;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
