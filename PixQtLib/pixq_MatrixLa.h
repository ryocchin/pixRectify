//
// pixq_Matrix
// basic linear algebra
//

namespace _pix_plot_qt_framework {

//
// get determinant of 3X3 matrix
//
template <class T> bool pixq_Matrix<T>::GetDeterminant3X3( T *tDeterminant )
{
   bool bRetCode = false;
   T tDet;
   int i, j;
   T A[3][3];
   int nWidth = getWidth();
   int nHeight = getHeight();

   if (3 != nWidth) {
      goto PIX_EXIT;
   }
   
   if (3 != nHeight) {
      goto PIX_EXIT;
   }

   for( i = 0 ; i < 3 ; i++ ) {
      for( j = 0 ; j < 3 ; j++ ) {
         A[i][j] = Get( i, j );
      }
   }
  
   tDet = 0;
   tDet += A[0][0] * A[1][1] * A[2][2];
   tDet += A[0][1] * A[1][2] * A[2][0];
   tDet += A[0][2] * A[1][0] * A[2][1];
   
   tDet -= A[2][2] * A[1][0] * A[0][1];
   tDet -= A[2][1] * A[1][2] * A[0][0]; 
   tDet -= A[2][0] * A[1][1] * A[0][2];

   *tDeterminant = tDet;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get inrverse matrix of of 3X3 matrix
//
template <class T> bool pixq_Matrix<T>::getInverse3x3(pixq_Matrix<T> *Inv)
{
   bool bRetCode = false;
   T tDet = 0;
   int i, j;
   T A[3][3];
   T X[3][3];
   T B[3][3]; // the transpose of a matrix A 
   T C[3][3]; // the adjunct matrix of transpose of a matrix A not adjunct of A
   int nWidth = getWidth();
   int nHeight = getHeight( );

   if( 3 != nWidth ) goto PIX_EXIT;
   if( 3 != nHeight ) goto PIX_EXIT;

   // get determinant

   if( !GetDeterminant3X3( &tDet ) ) {
      // not 3X3 matrix
      goto PIX_EXIT;
   }

   if( (T)0 == tDet ) {
      // determinant is 0
      goto PIX_EXIT;
   }

   // The transpose of a matrix A 
   
   for( i = 0 ; i < 3 ; i++ ) {
      for( j = 0 ; j < 3 ; j++ ) {
         A[i][j] = Get( i, j );
      }
   }

   for( i = 0 ; i < 3 ; i++ ) {
      for( j = 0 ; j < 3 ; j++ ) {
         B[i][j] = A[j][i];
      }
   }

   C[0][0] = B[1][1] * B[2][2] - B[2][1] * B[1][2];
   C[0][1] = B[2][0] * B[1][2] - B[1][0] * B[2][2];
   C[0][2] = B[1][0] * B[2][1] - B[2][0] * B[1][1];
     
   C[1][0] = B[2][1] * B[0][2] - B[0][1] * B[2][2];
   C[1][1] = B[0][0] * B[2][2] - B[2][0] * B[0][2];
   C[1][2] = B[2][0] * B[0][1] - B[0][0] * B[2][1];

   C[2][0] = B[0][1] * B[1][2] - B[1][1] * B[0][2];
   C[2][1] = B[1][0] * B[0][2] - B[0][0] * B[1][2];
   C[2][2] = B[0][0] * B[1][1] - B[1][0] * B[0][1];

   // --- The adjunct matrix of transpose of the matrix A ---
   
   for( i = 0 ; i < 3 ; i++ ) {
      for( j = 0 ; j < 3 ; j++ ) {  
         X[i][j] = C[i][j] / tDet;
      }   
   }

   // allocate and set the return matrix

   if( !Inv->Alloc( 3, 3 ) ) {
      goto PIX_EXIT;
   }

   for( i = 0 ; i < 3 ; i++ ) {
      for( j = 0 ; j < 3 ; j++ ) {
         Inv->Set( i, j, X[i][j] );
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// get inrverse matrix of of any N*N matrix
//
//
// matinv.cpp -- inverse of matrix using Gauss-Jordan elimination.
// (C) 2001, C. Bond. All rights reserved.
//
//
// Bare-bones Gauss-Jordan algorithm. Returns '0' on success, '1' if
// matrix is singular (zero diagonal). No pivoting used.
//
// Replaces input matrix with its inverse.
//
template <class T> bool pixq_Matrix<T>::GetInverse( pixq_Matrix<T> *Inv )
{
   bool bRetCode = false;
   int i, j, k, n;
   T tmp;
   T **mtx = NULL;
   T **inv = NULL;
   
   int nWidth = getWidth();
   int nHeight = getHeight();

   if( nHeight != nWidth ) {
      goto PIX_EXIT;
   }

   n = nWidth;

   mtx = new T *[n];
   inv = new T *[n];
   for( i = 0 ; i < n ; i++ ) {
      mtx[i] = new T[n];
      inv[i] = new T[n];
   }

   // Initialize identity matrix
   for( i = 0 ; i < n ; i++ ) {
      for( j = 0 ; j < n ; j++ ) {
            inv[i][j] = 0.0;
            mtx[i][j] = Get( i, j );
        }
        inv[i][i] = 1.0;
    }

    for( k = 0 ; k < n ; k++ ) {
       tmp = mtx[k][k];
       if( 0.0 == tmp ) {
          // singular!
          goto PIX_EXIT;
        }

        for( j = 0 ; j < n ; j++ ) {
           if( j > k ) {
              // Don't bother with previous entries
              mtx[k][j] /= tmp;    
           }
           inv[k][j] /= tmp;
        }

        for( i = 0 ; i < n ; i++) {
           // Loop over rows
           if (i == k) continue;
           tmp = mtx[i][k];
            for( j = 0 ; j < n ; j++ ) {
               if (j > k) {
                  mtx[i][j] -= mtx[k][j] * tmp;
               }
               inv[i][j] -= inv[k][j] * tmp;
            }
        }
    }

   // Copy inverse to source matrix

   if( !Inv->Alloc( n, n ) ) {
      goto PIX_EXIT;
   }

   for ( i = 0 ; i < n ; i++ ) {
      for( j = 0 ; j < n ; j++ ) {
         Inv->Set( i, j, inv[i][j] );
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   for( i = 0 ; i < n ; i++) {
      delete [] mtx[i];
      delete [] inv[i];
    }
   delete[] inv;
   delete[] mtx;
   return bRetCode;
}

//
// make new matrix as product of two square matrix
//
template <class T> bool pixq_Matrix<T>::ProductSquare( 
      pixq_Matrix *pMtx0, 
      pixq_Matrix *pMtx1 )
{
   bool bRetCode = false;
	int nRows, nCols, i, j, k;
	T tVal;

   nRows = pMtx0->getHeight();
   nCols = pMtx0->getWidth();
   
   // must be square matrix!
   
   if( nRows != nCols ) {
      goto PIX_EXIT;
   }

   // two matrices must be same size

   if (nRows != pMtx1->getHeight()) {
      goto PIX_EXIT;;
   }
   
   if (nCols != pMtx1->getWidth()) {
      goto PIX_EXIT;;
   }

   // --- allocate this! ---

   if( !Alloc( nRows, nCols ) ) {
      goto PIX_EXIT;
   }

   // start to calculate!
	
   for( i = 0 ; i < nRows ; i++ ) {
		for( j = 0 ; j < nCols ; j++ ) {
			tVal = (T)0;
			for( k = 0 ; k < nRows ; k++ ) {
            tVal = tVal + pMtx0->Get( i, k ) * pMtx1->Get( k, j );
			}
			Set( i, j, tVal );
		}
	}
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

template <class T> bool pixq_Matrix<T>::sqrProduct(
   pixq_Matrix<T> *Mtx0, 
   pixq_Matrix<T> *Mtx1 )
{
   bool bRetCode = false;
	int i, j, k;
	T tValue;

   int nRows0 = Mtx0->getHeight();
   int nCols0 = Mtx0->getWidth();
   int nRows1 = Mtx1->getHeight();
   int nCols1 = Mtx1->getWidth();

   if (nRows0 != nCols0) {
      goto PIX_EXIT;
   }

   if (nRows1 != nCols1) {
      goto PIX_EXIT;
   }
   
   if (nRows0 != nRows1) {
      goto PIX_EXIT;
   }

   if (!Alloc(nRows0, nRows0)) {
      goto PIX_EXIT;
   }

	for( i = 0 ; i < nRows0 ; i++ ) {
		for( j = 0 ; j < nRows0 ; j++ ) {
			tValue = (T)0;
			for( k = 0 ; k < nRows0 ; k++ ) {
            tValue = tValue + Mtx0->Get( i, k ) * Mtx1->Get( k, j );
			}
			Set( i, j, tValue );
		}
	}

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}

//
// create transpose matrix of the input matrix
// in this matrix
//
template <class T> bool pixq_Matrix<T>::Transpose( pixq_Matrix<T> *pIn )
{
   bool bRetCode = false;
	int i, j;
	T tValue;
   
   int nRows = getHeight();
   int nCols = getWidth( );

   // check the dimension of the input matrix
   
   int nInRows = pIn->getHeight();
   int nInCols = pIn->getWidth();

   if (0 >= nInRows) {
      goto PIX_EXIT;
   }

   if (0 >= nInCols) {
      goto PIX_EXIT;
   }

   // allocate this(output matirx) in necessary

   if( nRows == nInCols && nCols == nInRows  ) {
		// already allocated for the right dimension
   } else {
      free();
      if( !Alloc( nInCols, nInRows ) ) {
		   goto PIX_EXIT;
      }
	}

   // transpose the matrix

	for ( i = 0; i < nInRows; i++ ) {
		for( j = 0 ; j < nInCols ; j++ ) {
			tValue = pIn->Get( i, j );
         Set( j, i, tValue );
		}
	}

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
	return bRetCode;
}

} // namespace _pix_plot_qt_framework 
