#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

// 
// functions related to DFT
//

//
// reverse data array
//
static void Reverse1DData( float *fData, // [i] 1D data array 
                         int nLength, // [i] data size, power of two
                         int nPower, // [i] data size in exponential expression, nLength 2**nPower
                         float *fWork ) // [w] work area, same size as the input array
{
   int iBit, i, ii, k;

   for( i = 0 ; i < nLength ; i++ ) {
      for( k = 0, ii = i, iBit = 0 ; ; iBit<<=1, ii>>=1 ) {
         iBit = ( ii & 1 ) | iBit;
         if( ++k == nPower ) {
            break;
         }
      }

      fWork[i] = fData[iBit];
   }
   
   for( i = 0 ; i < nLength ; i++ ) {
      fData[i] = fWork[i];
   }

   // --- Done ---
   return;
}

//
// core part of the 1D fft
//
//
static void FftCoreCalc( 
   float *fReal, // [i/o] real part 
   float *fImag, // [i/o] imagenary part
   int nLength, // [i] data size, power of two
   int nPower, // [i] data size in exponential expression, nLength 2**nPower
   float *fSin, // [i] sine table
   float *fCos, // [i] cosine table 
   float *fWork ) // [w] work area, same size as the input array
{
   int timb, w, i, j, k, j1, j2, numb, lenb;
   float fNormal, fXr, fXi, fYr, fYi;

   bool bOptical = true;

   //bOptical = false;

   // convert to the optical 

   if( bOptical ) {
      for( i = 1 ; i < nLength ; i+=2 ) {
         fReal[i] = -fReal[i];
         fImag[i] = -fImag[i];
      }
   }

   // start the computation
   
   numb = 1;
   lenb = nLength;
   for( i = 0 ; i < nPower ; i++ ) {
      lenb = lenb / 2;
      timb = 0;
      
      for( j = 0 ; j < numb ; j++ ) {
         w = 0;
         for( k = 0 ; k < lenb ; k++ ) {
            j1 = timb + k;
            j2 = j1 + lenb;

            fXr = fReal[j1];
            fXi = fImag[j1];
            fYr = fReal[j2];
            fYi = fImag[j2];

            fReal[j1] = fXr + fYr;
            fImag[j1] = fXi + fYi;

            fXr = fXr - fYr;
            fXi = fXi - fYi;
            fReal[j2] = fXr * fCos[w] - fXi * fSin[w];
            fImag[j2] = fXr * fSin[w] + fXi * fCos[w];

            w = w + numb;
         }

         timb = timb + 2 * lenb;
      }
      numb = numb * 2;
   }

   // revert real data
   Reverse1DData( fReal, nLength, nPower, fWork );

   // revert imaginary data
   Reverse1DData( fImag, nLength, nPower, fWork );

   // convert to the optical 

   if( bOptical ) {
      for( i = 1 ; i < nLength ; i+=2 ) {
         fReal[i] = -fReal[i];
         fImag[i] = -fImag[i];
      }
   }

   fNormal = (float)( 1.0f / sqrt( (float)nLength ) );
   for( i = 0 ; i < nLength ; i++ ) {
      fReal[i] = fReal[i] * fNormal;
      fImag[i] = fImag[i] * fNormal;      
   }

   // --- Done ---
   return;
}

//
// create sin/cosin table
//
static void CreateSinCosTable( 
   int nLength, // [i] data size, power of two
   bool bInv, // [i] true=intversed DFT, false=DFT
   float *fSin, // [o] sine table
   float *fCos ) // [o] cosine table 
{
   int i;
   float fData, fArg;

   fData = (float)( -M_PI * 2.0f ) / (float)nLength;
  
   if( bInv ) {
      fData = -fData;
   }

   for( i = 0 ; i < nLength ; i++ ) {
      fArg = (float)i * fData;
      fSin[i] = (float)sin( fArg );
      fCos[i] = (float)cos( fArg );
   }

   // --- Done ---
   return;
}

//
// run 1D fft
//
// notes:
// bOpt=true -> optical fft(DC element comes center)
// false -> ordinary fft(DC comes at left end)
// 
bool Calc1DFftCalc_PI( 
   float *fReal, // [i/o] real part, 1D buffer
   float *fImag, // [i/o] imagenary part, 1D buffer
   int nPower, // [i] data size in exponential expression, nLength 2**nPower
   bool bInv ) // [i] true=inversed DFT, false=DFT
{
   bool bRetCode = false;
   float *fSin = NULL; // sine table
   float *fCos = NULL; // cosine table 
   float *fWork = NULL; // work area
   int i, nLength;

   // get length from power
   nLength = 1;
   for( i = 0 ; i < nPower ; i++ ) {
      nLength = 2 * nLength;
   }

   fSin = new float[nLength];
   if( !fSin ) goto PIX_EXIT;

   fCos = new float[nLength];
   if( !fCos ) goto PIX_EXIT;
   
   fWork = new float[nLength];
   if( !fWork ) goto PIX_EXIT;

   // create sin/cosine table
   CreateSinCosTable( nLength, bInv, fSin, fCos );

   // calculate fft
   
   FftCoreCalc( fReal, fImag, nLength, nPower, fSin, fCos, fWork );

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   if( fSin ) {
      delete[] fSin;
      fSin = NULL;
   }
   if( fCos ) {
      delete[] fCos;
      fCos = NULL;
   }
   if( fWork ) {
      delete[] fWork;
      fWork = NULL;
   }
   return bRetCode;
}

//
// run 1D fft
//
// notes:
// bOpt=true -> optical fft(DC element comes center)
// false -> ordinary fft(DC comes at left end)
// 
bool Calc1DFftCalc_PI( 
   vector<float> *vfReal, // [i/o] real part, 1D buffer
   vector<float> *vfImag, // [i/o] imagenary part, 1D buffer
   bool bInv ) // [i] true=inversed DFT, false=DFT
{
   bool bRetCode = false;
   float *fReal = NULL; 
   float *fImag = NULL; 
   int i, nPower, nLength;

   // get length from power

   nLength = (int)vfReal->size( );
   if( !IsPowerOfTwo_PC( nLength, &nPower ) ) {
      goto PIX_EXIT;
   }

   fReal = new float[nLength];
   if( !fReal ) goto PIX_EXIT;

   fImag = new float[nLength];
   if( !fImag ) goto PIX_EXIT;

   for( i = 0 ; i < nLength ; i++ ) {
      fReal[i] = vfReal->at( i );
      fImag[i] = vfImag->at( i );
   }

   // calculate fft
   
   if( !Calc1DFftCalc_PI( fReal, fImag, nPower, bInv ) ) {
      goto PIX_EXIT;
   }

   for( i = 0 ; i < nLength ; i++ ) {
      vfReal->at( i ) = fReal[i];
      vfImag->at( i ) = fImag[i];
   }                 

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   if( fReal ) {
      delete[] fReal;
      fReal = NULL;
   }
   if( fImag ) {
      delete[] fImag;
      fImag = NULL;
   }
   return bRetCode;
}

//
// Image processing in matrix:
// fft image of the first image in the second image
//
// notes:
// 
bool Get2DImageFft_PI( 
   pixq_Matrix<float> *fInReal, // [i/o] real part, input image matrix
   pixq_Matrix<float> *fInImag, // [i/o] imagery part, image matrix
   bool bInverse ) // [i] true for inverse DFT
{
   bool bRetCode = false;
   int i, j, nWidth, nHeight, nExWidth, nExHeight;
   float fR, fI;

   pixq_Matrix<float> fTrnReal, fTrnImag;
   pixq_Matrix<float> fTmpReal, fTmpImag;

   float *hsin_tbl = NULL; // horizontal sine table
   float *hcos_tbl = NULL; // horizontal cosine table
   float *vsin_tbl = NULL; // vertical sine table
   float *vcos_tbl = NULL; // vertical cosine table
   float *buf_x = NULL; // work buffer, horizontal
   float *buf_y = NULL; // work buffer, vertical

   float *fHorReal = NULL;
   float *fHorImag = NULL;
   float *fVerReal = NULL;
   float *fVerImag = NULL;

   nWidth = fInReal->getWidth();
   nHeight = fInReal->getHeight();

   if (0 >= nWidth || 0 >= nHeight) {
      goto PIX_EXIT;
   }

   if( !IsPowerOfTwo_PC( nWidth, &nExWidth ) ) {
      goto PIX_EXIT;
   }
   
   if( !IsPowerOfTwo_PC( nHeight, &nExHeight ) ) {
      goto PIX_EXIT;
   }

   // allocate work buffers

   // real part
   if( !fTrnReal.Alloc( nWidth, nHeight ) ) {
      goto PIX_EXIT;
   }

   // imagenary part
   if( !fTrnImag.Alloc( nWidth, nHeight ) ) {
      goto PIX_EXIT;
   }

   hsin_tbl = new float[nWidth];
   if( !hsin_tbl ) goto PIX_EXIT;

   hcos_tbl = new float[nWidth];
   if( !hcos_tbl ) goto PIX_EXIT;

   vsin_tbl = new float[nHeight];
   if( !vsin_tbl ) goto PIX_EXIT;

   vcos_tbl = new float[nHeight];   
   if( !vcos_tbl ) goto PIX_EXIT;

   buf_x = new float[nWidth];
   if( !buf_x ) goto PIX_EXIT;

   buf_y = new float[nHeight];
   if( !buf_y ) goto PIX_EXIT;

   fHorReal = new float[nWidth];
   if( !fHorReal ) goto PIX_EXIT;
   
   fHorImag = new float[nWidth];
   if( !fHorImag ) goto PIX_EXIT;

   fVerReal = new float[nHeight];
   if( !fVerReal ) goto PIX_EXIT;
   
   fVerImag = new float[nHeight];
   if( !fVerImag ) goto PIX_EXIT;

   if( !fTmpReal.Alloc( nHeight, nWidth ) ) {
      goto PIX_EXIT;
   }

   if( !fTmpImag.Alloc( nHeight, nWidth ) ) {
      goto PIX_EXIT;
   }

   // convert to float matrix

   for( i = 0 ; i < nHeight ; i++ ) {
      for( j = 0 ; j < nWidth ; j++ ) {
         fR = fInReal->Get( i, j );
         fI = fInImag->Get( i, j );

         fTmpReal.Set( i, j, fR );
         fTmpImag.Set( i, j, fI );
      }
   }

   // create sin/cosine tables

   CreateSinCosTable( nWidth, bInverse, hsin_tbl, hcos_tbl );
   CreateSinCosTable( nHeight, bInverse, vsin_tbl, vcos_tbl );

   // horizontal fft

   for( i = 0 ; i < nHeight ; i++ ) {
      // copy one scanline of the matrix to buffer
      for( j = 0 ; j < nWidth ; j++ ) {
         fHorReal[j] = fTmpReal.Get( i, j );
         fHorImag[j] = fTmpImag.Get( i, j );
      }
      // 1D horizontal FFT
      FftCoreCalc( fHorReal, fHorImag, nWidth, nExWidth, hsin_tbl, hcos_tbl, buf_x );
      // revert buffer to the scanline of the matrix
      for( j = 0 ; j < nWidth ; j++ ) {
         fTmpReal.Set( i, j, fHorReal[j] );
         fTmpImag.Set( i, j, fHorImag[j] );
      }
   }

   // make transpose matrix

   fTrnReal.Transpose( &fTmpReal );
   fTrnImag.Transpose( &fTmpImag );

   // vertical fft

   for( j = 0 ; j < nWidth ; j++ ) {
      for( i = 0 ; i < nHeight ; i++ ) {
      // copy one column line of the matrix to buffer
      
         fVerReal[i] = fTrnReal.Get( j, i );
         fVerImag[i] = fTrnImag.Get( j, i );
      }

      // 1D horizontal FFT
      FftCoreCalc( fVerReal, fVerImag, nHeight, nExHeight, vsin_tbl, vcos_tbl, buf_y );
      
      // revert buffer to the scanline of the matrix
      for( i = 0 ; i < nHeight ; i++ ) {
         fTrnReal.Set( j, i, fVerReal[i] );
         fTrnImag.Set( j, i, fVerImag[i] );
      }
   }

   // make transpose matrix

   fInReal->Transpose( &fTrnReal );
   fInImag->Transpose( &fTrnImag );
  
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   fTrnReal.free();
   fTrnImag.free();
   fTmpReal.free();
   fTmpImag.free();
   if( hsin_tbl ) { delete[] hsin_tbl; hsin_tbl = NULL; }
   if( hcos_tbl ) { delete[] hcos_tbl; hcos_tbl = NULL; }
   if( vsin_tbl ) { delete[] vsin_tbl; vsin_tbl = NULL; }
   if( vcos_tbl ) { delete[] vcos_tbl; vcos_tbl = NULL; }
   if( buf_x ) { delete[] buf_x; buf_x = NULL; }
   if( buf_y ) { delete[] buf_y; buf_y = NULL; }
   if( fHorReal ) { delete[] fHorReal; fHorReal = NULL; }
   if( fHorImag ) { delete[] fHorImag; fHorImag = NULL; }
   if( fVerReal ) { delete[] fVerReal; fVerReal = NULL; }
   if( fVerImag ) { delete[] fVerImag; fVerImag = NULL; }
   return bRetCode;
}

//
// from real and imagery part of DFT image
// create amplitude image
//
bool DftAmplitudeImage_PC( pixq_Matrix<float> *fReal, // [i] real part
                            pixq_Matrix<float> *fImag,  // [i] imagery part
                            pixq_Matrix<float> *fDft ) // [o] amplitude image
{
   bool bRetCode = false;
   int i, j, nWidth, nHeight;
   float fR, fI, fNorm;

   nWidth = fReal->getWidth();
   nHeight = fReal->getHeight();

   if( !fDft->Alloc( nHeight, nWidth ) ) {
      goto PIX_EXIT;
   }

   for( i = 0 ; i < nHeight ; i++ ) {

      for( j = 0 ; j < nWidth ; j++ ) {
         // calculate amplitude
         fR = fReal->Get( i, j );
         fI = fImag->Get( i, j );
         fNorm = fR * fR + fI * fI; 
         if( 0.0f != fNorm ) {
            fNorm = log( fNorm ) / 2.0f;
         } 
         fDft->Set( i, j, fNorm );
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool DftAmplitudeImage_PC( vector<float> *vfReal, // [i] real part
                               vector<float> *vfImag,  // [i] imagery part
                               vector<float> *vfDft ) // [o] amplitude image
{
   bool bRetCode = false;
   int i, nLength;
   float fR, fI, fNorm;

   nLength = (int)vfReal->size( );

   vfDft->resize( nLength );

   for( i = 0 ; i < nLength ; i++ ) {
      // calculate amplitude
      fR = vfReal->at( i );
      fI = vfImag->at( i );
      fNorm = fR * fR + fI * fI; 
      if( 0.0f != fNorm ) {
         fNorm = log( fNorm ) / 2.0f;
      } 
      
      vfDft->at( i ) = fNorm;
   }

   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}