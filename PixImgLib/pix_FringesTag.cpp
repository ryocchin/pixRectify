#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_FringeTag.h"
#include "pix_FringesTag.h" 

pixq_FringesTag::pixq_FringesTag(void)
{
   init( );

   return;
}

pixq_FringesTag::~pixq_FringesTag(void)
{
   init();

   return;
}

void pixq_FringesTag::Clear(void)
{
   init();

   return;
}

void pixq_FringesTag::init(void)
{
   int k;

   _nTagRows = -1;
   _nTagCols = -1;

   _vTags.clear( );

   //

   resetTransform();

   //

   _dTransform[0][0] = 1.0;
   _dTransform[0][1] = 0.0;
   _dTransform[0][2] = 0.0;
   _dTransform[1][0] = 0.0;
   _dTransform[1][1] = 1.0;
   _dTransform[1][2] = 0.0;
   _dTransform[2][0] = 0.0;
   _dTransform[2][1] = 0.0;
   _dTransform[2][2] = 1.0;

   _dInvTransform[0][0] = 1.0;
   _dInvTransform[0][1] = 0.0;
   _dInvTransform[0][2] = 0.0;
   _dInvTransform[1][0] = 0.0;
   _dInvTransform[1][1] = 1.0;
   _dInvTransform[1][2] = 0.0;
   _dInvTransform[2][0] = 0.0;
   _dInvTransform[2][1] = 0.0;
   _dInvTransform[2][2] = 1.0;

   for( k = 0 ; k < 2 ; k++ ) {
      _dRectify[k][0][0] = 1.0;
      _dRectify[k][0][1] = 0.0;
      _dRectify[k][0][2] = 0.0;
      _dRectify[k][1][0] = 0.0;
      _dRectify[k][1][1] = 1.0;
      _dRectify[k][1][2] = 0.0;
      _dRectify[k][2][0] = 0.0;
      _dRectify[k][2][1] = 0.0;
      _dRectify[k][2][2] = 1.0;
      
      _dInvRectify[k][0][0] = 1.0;
      _dInvRectify[k][0][1] = 0.0;
      _dInvRectify[k][0][2] = 0.0;
      _dInvRectify[k][1][0] = 0.0;
      _dInvRectify[k][1][1] = 1.0;
      _dInvRectify[k][1][2] = 0.0;
      _dInvRectify[k][2][0] = 0.0;
      _dInvRectify[k][2][1] = 0.0;
      _dInvRectify[k][2][2] = 1.0;
   }

   //

   _vstrLog.clear( );

   _bDrawControlPnts = true;

   return;
}

//
// copy constructor
//
pixq_FringesTag &pixq_FringesTag::operator=(const pixq_FringesTag &that)
{
   int k;
   pixq_FringeTag tag;
   int nCount = (int)that._vTags.size( );

   _vTags.resize( nCount );

   for( k = 0 ; k < nCount ; k++ ) {
      tag = that._vTags.at( k );
      _vTags.at( k ) = tag;
   }

   _nTagRows = that._nTagRows;
   _nTagRows = that._nTagRows;
                    

   _nTagRows = that._nTagRows;
   _nTagRows = that._nTagRows;

   // --- Done ---
	return *this;
}


int pixq_FringesTag::getTags(void)
{
   int nTags = (int)_vTags.size( );

   return nTags;
}

//
// number of tags used is true
//
int pixq_FringesTag::getUsedTags(void)
{
   int nTags = (int)_vTags.size( );
   pixq_FringeTag *pTag;
   bool bUsed;
   int nUsedTags, i;

   nUsedTags = 0;
   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
      bUsed = pTag->getUsed();
      if( !bUsed ) continue;
      nUsedTags++;
   }

   return nUsedTags;
}
 
//
// set all tags either used or not used
//
void pixq_FringesTag::setAllUsed(bool bUsed)
{
   int nTags = (int)_vTags.size();
   pixq_FringeTag *pTag;
   int  i;

   for (i = 0; i < nTags; i++) {
      pTag = getNthTag(i);
      pTag->setUsed(bUsed);
   }

   return;
}

pixq_FringeTag *pixq_FringesTag::getNthTag(int iTag)
{
   pixq_FringeTag *pTag = NULL;

   int nTags = getTags();

   if (0 > iTag) {
      goto PIX_EXIT;
   }
   
   if (nTags <= iTag) {
      goto PIX_EXIT;
   }

   pTag = (pixq_FringeTag*)&_vTags.at(iTag);

PIX_EXIT:
   return pTag;
}


pixq_FringeTag *pixq_FringesTag::getTag(int iCol, int iRow)
{
   pixq_FringeTag *pTag = NULL;
   int nTags = getTags();
   int iTag = iRow * _nTagCols + iCol;

   if (0 > iTag) {
      goto PIX_EXIT;
   }
   
   if (nTags <= iTag) {
      goto PIX_EXIT;
   }

   pTag = getNthTag(iTag);

PIX_EXIT:
   return pTag;
}

//
// get tag row and column number from sequence tag ID
//
bool pixq_FringesTag::getTagRowCol(int iTag, // [i] tag sequencetil number
                                  int &iRow, // [o] row number
                                  int &iCol ) // [o] column number
{
   bool bRetCode = false;
   int nTags = getTags();

   if( 0 >= _nTagCols ) {
      goto PIX_EXIT;
   }

   if( 0 > iTag || iTag >= nTags ) {
      goto PIX_EXIT;
   }

   iCol = iTag % _nTagCols;
   iRow = ( iTag - iCol ) / _nTagCols;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

void pixq_FringesTag::Resize(int nTags)
{
   _vTags.resize( nTags );

   return;
}

//
// check if the tag coordinate is valid
//
bool pixq_FringesTag::CheckTagInside(int iCol,
                                   int iRow )
{
   bool bRetCode = false;

   if (0 > iRow) goto PIX_EXIT;
   if (0 > iCol) goto PIX_EXIT;

   if (_nTagRows <= iRow) {
      goto PIX_EXIT;
   }
   
   if (_nTagCols <= iCol) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get affine transformation parameters to transform form left to right
//
bool pixq_FringesTag::GetAffineTransform(void)
{
   bool bRetCode = false;
   bool bUsed;
   int i, nUsedTags, nTags, iX, iY, iU, iV;
   double dResiMax, dX, dU, dV, dY, dUU, dVV;
   double dA, dB, dC, dD, dE, dF;
   double dAA, dBB, dCC, dDD, dEE, dFF, dGG, dHH, dII;
   double dSumX, dSumY, dSumU, dSumV;
   double dSumXX, dSumYY, dSumUU, dSumVV;
   double dSumXY, dSumXU, dSumYU, dSumXV, dSumYV;
   double dResiX, dResiY, dResi, dResiSum, dResiAvr;

   pixq_FringeTag *pTag;

   char szLog[RECORD_SIZE];

   pixq_Matrix<double> Mtx, Inv;
#ifdef _DEBUG
   int j;
   pixq_Matrix<double> Check;
#endif // _DEBUG

   //
   
   resetTransform();

   _vstrLog.clear( );

   // match right image to left

   nTags = getTags();
   if( 4 > nTags ) {
      sprintf( szLog, "Affine Tranformation : Not Enough Points - %d", nTags );
      _vstrLog.push_back( szLog );
      goto PIX_EXIT;
   }

   nUsedTags = getUsedTags();
   if( 4 > nUsedTags ) {
      sprintf( szLog, "Affine Tranformation : Not Enough Used Points - %d", nUsedTags );
      _vstrLog.push_back( szLog );
      goto PIX_EXIT;
   }

   //

   dSumX = 0.0;
   dSumY = 0.0;
   dSumU = 0.0;
   dSumV = 0.0;

   dSumXX = 0.0;
   dSumYY = 0.0;
   dSumUU = 0.0;
   dSumVV = 0.0;

   dSumXY = 0.0;
   dSumXU = 0.0;
   dSumYU = 0.0;
   dSumXV = 0.0;
   dSumYV = 0.0;

   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
      bUsed = pTag->getUsed();
      if( !bUsed ) continue;

      dX = (double)pTag->getXTag();
      dY = (double)pTag->getYTag();

      dU = (double)pTag->getRightXTag();
      dV = (double)pTag->getRightYTag();

      //
      
      dSumX = dSumX + dX;
      dSumY = dSumY + dY;
      dSumU = dSumU + dU;
      dSumV = dSumV + dV;

      dSumXX = dSumXX + dX * dX;
      dSumYY = dSumYY + dY * dY;
      dSumUU = dSumUU + dU * dU;
      dSumVV = dSumVV + dV * dV;

      dSumXY = dSumXY + dX * dY;
      dSumXU = dSumXU + dX * dU;
      dSumYU = dSumYU + dY * dU;
      dSumXV = dSumXV + dX * dV;
      dSumYV = dSumYV + dY * dV;
   }

   if( !Mtx.Alloc( 3, 3 ) ) {
      goto PIX_EXIT;
   }

   Mtx.Set( 0, 0, dSumXX );
   Mtx.Set( 0, 1, dSumXY );
   Mtx.Set( 0, 2, dSumX );
   Mtx.Set( 1, 0, dSumXY );
   Mtx.Set( 1, 1, dSumYY );
   Mtx.Set( 1, 2, dSumY );
   Mtx.Set( 2, 0, dSumX );
   Mtx.Set( 2, 1, dSumY );
   Mtx.Set( 2, 2, (double)nTags );

   if( !Inv.Alloc( 3, 3 ) ) {
      goto PIX_EXIT;
   }

   if (!Mtx.getInverse3x3(&Inv)) {
      goto PIX_EXIT;
   }

#ifdef _DEBUG
   Check.ProductSquare( &Mtx, &Inv );
   for( i = 0 ; i < 3 ; i++ ) {
      for( j = 0 ; j < 3 ; j++ ) {
         dX = Check.Get( i, j );
      }
   }
#endif // _DEBUG

   //
   // get parameters
   // 
   // | u |   | a b c |   | x |
   // | v | = | d e f | * | y |
   // | w |   | 0 0 1 |   | 1 |
   //

   dA = dSumXU * Inv.Get( 0, 0 ) + dSumYU * Inv.Get( 0, 1 ) + dSumU * Inv.Get( 0, 2 );
   dB = dSumXU * Inv.Get( 1, 0 ) + dSumYU * Inv.Get( 1, 1 ) + dSumU * Inv.Get( 1, 2 );
   dC = dSumXU * Inv.Get( 2, 0 ) + dSumYU * Inv.Get( 2, 1 ) + dSumU * Inv.Get( 2, 2 );

   dD = dSumXV * Inv.Get( 0, 0 ) + dSumYV * Inv.Get( 0, 1 ) + dSumV * Inv.Get( 0, 2 );
   dE = dSumXV * Inv.Get( 1, 0 ) + dSumYV * Inv.Get( 1, 1 ) + dSumV * Inv.Get( 1, 2 );
   dF = dSumXV * Inv.Get( 2, 0 ) + dSumYV * Inv.Get( 2, 1 ) + dSumV * Inv.Get( 2, 2 );
   
   // check the result
   
   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
   
      dX = (double)pTag->getXTag();
      dY = (double)pTag->getYTag();

      dU = (double)pTag->getRightXTag();
      dV = (double)pTag->getRightYTag();

      dUU = dX * dA + dY * dB + dC;
      dVV = dX * dD + dY * dE + dF;
   }

   // get the inverse matrix

   Mtx.Set( 0, 0, dA );
   Mtx.Set( 0, 1, dB );
   Mtx.Set( 0, 2, dC );
   Mtx.Set( 1, 0, dD );
   Mtx.Set( 1, 1, dE );
   Mtx.Set( 1, 2, dF );
   Mtx.Set( 2, 0, 0.0 );
   Mtx.Set( 2, 1, 0.0 );
   Mtx.Set( 2, 2, 1.0 );

   if( !Inv.Alloc( 3, 3 ) ) {
      goto PIX_EXIT;
   }

   if (!Mtx.getInverse3x3(&Inv)) {
      goto PIX_EXIT;
   }

   dAA = Inv.Get( 0, 0 );
   dBB = Inv.Get( 0, 1 );
   dCC = Inv.Get( 0, 2 );
   dDD = Inv.Get( 1, 0 );
   dEE = Inv.Get( 1, 1 );
   dFF = Inv.Get( 1, 2 );
   dGG = Inv.Get( 1, 0 );
   dHH = Inv.Get( 1, 1 );
   dII = Inv.Get( 1, 2 );

   // store the matrix

   _dTransform[0][0] = dA;
   _dTransform[0][1] = dB;
   _dTransform[0][2] = dC;
   _dTransform[1][0] = dD;
   _dTransform[1][1] = dE;
   _dTransform[1][2] = dF;
   _dTransform[2][0] = 0.0;
   _dTransform[2][1] = 0.0;
   _dTransform[2][2] = 1.0;

   _dInvTransform[0][0] = dAA;
   _dInvTransform[0][1] = dBB;
   _dInvTransform[0][2] = dCC;
   _dInvTransform[1][0] = dDD;
   _dInvTransform[1][1] = dEE;
   _dInvTransform[1][2] = dFF;
   _dInvTransform[2][0] = 0.0;
   _dInvTransform[2][1] = 0.0;
   _dInvTransform[2][2] = 1.0;

   setTransform(pixq_Properties::TransformationAffine);

   // 
   // *** set the computation Log ***
   // 

   sprintf( szLog, "*** Affine Tranformation : %d Point(s) ***", nTags );
   _vstrLog.push_back( szLog );

   dResiSum = 0.0;
   dResiMax = -1.0;
   nUsedTags = 0;
   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
   
      bUsed = pTag->getUsed();
      if( !bUsed ) { 
         sprintf( szLog, "Tag %03d : Not Used.", i+1 );
         _vstrLog.push_back( szLog );
         continue;
      }
      
      iX = pTag->getXTag();
      iY = pTag->getYTag();
      iU = pTag->getRightXTag();
      iV = pTag->getRightYTag();

      getTransformedRight( iX, iY, dUU, dVV );
      dResiX = dUU - (double)iU;
      dResiY = dVV - (double)iV;
      dResi = sqrt( dResiX * dResiX + dResiY * dResiY );
    
      sprintf( szLog, "Tag %03d : (%04d,%04d) -> (%04d,%04d) Residual %7.3fX | %7.3fY %7.3f",
         i+1, iX, iY,
         iU, iV,
         dResiX, dResiY, dResi );
      _vstrLog.push_back( szLog );

      dResiSum = dResiSum + dResi;
      dResiMax = max( dResiMax, dResi );
      nUsedTags = nUsedTags + 1;
   }

   sprintf( szLog, "---------------------------------------------" );
   _vstrLog.push_back( szLog );

   if( 0 == nUsedTags ) {
      dResiAvr = 0.0;
   } else {
      dResiAvr = dResiSum / (double)nUsedTags;
   }
   sprintf( szLog, "Average Residual: %7.3f pixel[%d points].", dResiAvr, nUsedTags );
   _vstrLog.push_back( szLog );
   sprintf( szLog, "Largest Residual: %7.3f pixel.", dResiMax );
   _vstrLog.push_back( szLog );

   sprintf( szLog, "| u |   | %7.3f %7.3f %7.3f |   | x | ", 
      _dTransform[0][0], _dTransform[0][1], _dTransform[0][2] );
   _vstrLog.push_back( szLog );

   sprintf( szLog, "| v | = | %7.3f %7.3f %7.3f | * | y | ", 
      _dTransform[1][0], _dTransform[1][1], _dTransform[1][2] );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, "| w |   | %7.3f %7.3f %7.3f |   | 1 | ", 
      _dTransform[2][0], _dTransform[2][1], _dTransform[2][2] );
   _vstrLog.push_back( szLog );
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   Mtx.free();
   Inv.free();
#ifdef _DEBUG
   Check.free();
#endif // _DEBUG
   return bRetCode;
}

//
// get projective transformation parameters from 4 points
//
// notes:
// this function should only be called from GetProjectiveTransform
//
bool pixq_FringesTag::GetProjective4Points(void)
{
   bool bRetCode = false;
   bool bUsed;
   int i, j, k, nUsedTags, nTags;
   double dX[4], dU[4], dV[4], dY[4];
   double dTrans[8][8], dPara[9], dVec[8];
   double dA, dB, dC, dD, dE, dF, dG, dH, dI;

   pixq_FringeTag *pTag;

   char szLog[RECORD_SIZE];

   pixq_Matrix<double> Mtx, Inv;

#ifdef _DEBUG
   pixq_Matrix<double> Check;
   double dVal[8];
   char szRecord[RECORD_SIZE];
#endif // _DEBUG

   // match right image to left

   nTags = getTags();
   nUsedTags = getUsedTags();
   if( 4 != nUsedTags ) {
      sprintf( szLog, "Projective Tranformation : Not Enough Used Points - %d", nUsedTags );
      _vstrLog.push_back( szLog );
      goto PIX_EXIT;
   }

   //

   k = 0;
   for( i = 0 ; i < nTags ; i++ ) {
      if( k >= 4 ) continue;

      pTag = getNthTag(i);
      bUsed = pTag->getUsed();
      if( !bUsed ) continue;

      dX[k] = (double)pTag->getXTag();
      dY[k] = (double)pTag->getYTag();

      dU[k] = (double)pTag->getRightXTag();
      dV[k] = (double)pTag->getRightYTag();
      k++;
   }

   //
   
   dTrans[0][0] = dX[0];
   dTrans[0][1] = dY[0];
   dTrans[0][2] = 1.0;
   dTrans[0][3] = 0.0;
   dTrans[0][4] = 0.0;
   dTrans[0][5] = 0.0;
   dTrans[0][6] = -dU[0] * dX[0];
   dTrans[0][7] = -dU[0] * dY[0];
                  
   dTrans[1][0] = dX[1];
   dTrans[1][1] = dY[1];
   dTrans[1][2] = 1.0;
   dTrans[1][3] = 0.0;
   dTrans[1][4] = 0.0;
   dTrans[1][5] = 0.0;
   dTrans[1][6] = -dU[1] * dX[1];
   dTrans[1][7] = -dU[1] * dY[1];
                  
   dTrans[2][0] = dX[2];
   dTrans[2][1] = dY[2];
   dTrans[2][2] = 1.0;
   dTrans[2][3] = 0.0;
   dTrans[2][4] = 0.0;
   dTrans[2][5] = 0.0;
   dTrans[2][6] = -dU[2] * dX[2];
   dTrans[2][7] = -dU[2] * dY[2];
                  
   dTrans[3][0] = 0.0;
   dTrans[3][1] = 0.0;
   dTrans[3][2] = 0.0;
   dTrans[3][3] = dX[0]; 
   dTrans[3][4] = dY[0]; 
   dTrans[3][5] = 1.0;
   dTrans[3][6] = -dV[0] * dX[0];
   dTrans[3][7] = -dV[0] * dY[0];
                 
   dTrans[4][0] = 0.0;
   dTrans[4][1] = 0.0;
   dTrans[4][2] = 0.0;
   dTrans[4][3] = dX[1]; 
   dTrans[4][4] = dY[1]; 
   dTrans[4][5] = 1.0;
   dTrans[4][6] = -dV[1] * dX[1];
   dTrans[4][7] = -dV[1] * dY[1];
                 
   dTrans[5][0] = 0.0;
   dTrans[5][1] = 0.0;
   dTrans[5][2] = 0.0;
   dTrans[5][3] = dX[2]; 
   dTrans[5][4] = dY[2]; 
   dTrans[5][5] = 1.0;
   dTrans[5][6] = -dV[2] * dX[2];
   dTrans[5][7] = -dV[2] * dY[2];
                
   dTrans[6][0] = dX[3];
   dTrans[6][1] = dY[3];
   dTrans[6][2] = 1.0;
   dTrans[6][3] = 0.0;
   dTrans[6][4] = 0.0;
   dTrans[6][5] = 0.0;
   dTrans[6][6] = -dU[3] * dX[3];
   dTrans[6][7] = -dU[3] * dY[3];
                    
   dTrans[7][0] = 0.0;
   dTrans[7][1] = 0.0;
   dTrans[7][2] = 0.0;
   dTrans[7][3] = dX[3]; 
   dTrans[7][4] = dY[3]; 
   dTrans[7][5] = 1.0;
   dTrans[7][6] = -dV[3] * dX[3];
   dTrans[7][7] = -dV[3] * dY[3];
   
   dVec[0] = dU[0];
   dVec[1] = dU[1];
   dVec[2] = dU[2];
   dVec[3] = dV[0];
   dVec[4] = dV[1];
   dVec[5] = dV[2];
   dVec[6] = dU[3];
   dVec[7] = dV[3];

   if( !Mtx.Alloc( 8, 8 ) ) {
      goto PIX_EXIT;
   }

   for( i = 0 ; i < 8 ; i++ ) {
      for( j = 0 ; j < 8 ; j++ ) {
         Mtx.Set( i, j, dTrans[i][j] );
      }
   }

   if( !Mtx.GetInverse( &Inv ) ) {
      goto PIX_EXIT;
   }

#ifdef _DEBUG
   Check.ProductSquare( &Mtx, &Inv );
   for( i = 0 ; i < 8 ; i++ ) {
      for( j = 0 ; j < 8 ; j++ ) {
         dVal[j] = Check.Get( i, j );
      }
      sprintf( szRecord, "%2d : %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f", i, 
         dVal[0], dVal[1], dVal[2], dVal[3], dVal[4], dVal[5], dVal[6], dVal[7] ); 
   }
#endif // _DEBUG

   for( i = 0 ; i < 8 ; i++ ) {
      dPara[i] = 0.0;
      for( j = 0 ; j < 8 ; j++ ) {
         dPara[i] = dPara[i] + Inv.Get( i, j ) * dVec[j];
      }
   }
      
   //
   // get parameters for projective transformation
   //
   //       m1 * x + m2 * y + m3 
   //  u = ----------------------
   //       m7 * x + m8 * y + 1 
   //
   //       m4 * x + m5 * y + m5 
   //  v = ----------------------
   //       m7 * x + m8 * y + 1 
   //
   // | m1 m2 m3 |   | m00 m01 m02 |   | a b c |
   // | m4 m5 m6 | = | m10 m11 m12 | = | d e f |
   // | m7 m8  1 |   | m20 m21 m22 |   | g h 1 |

   _dTransform[0][0] = dPara[0];
   _dTransform[0][1] = dPara[1];
   _dTransform[0][2] = dPara[2];
   _dTransform[1][0] = dPara[3];
   _dTransform[1][1] = dPara[4];
   _dTransform[1][2] = dPara[5];
   _dTransform[2][0] = dPara[6];
   _dTransform[2][1] = dPara[7];
   _dTransform[2][2] = 1.0;

   // set inverse matrix
   
   //      ( ei - fh ) * u + ( ch - bi ) * v + ( bf - ce )
   // x = ------------------------------------------------- 
   //      ( dh - ge ) * u + ( bg - ah ) * v + ( ae - bd )
   //
   //      ( fg - di ) * u + ( ai - cg ) * v + ( cd - af )
   // y = ------------------------------------------------- 
   //      ( dh - ge ) * u + ( bg - ah ) * v + ( ae - bd )
   //
   //                        | ( ei - fh ) ( ch - bi ) ( bf - ce ) |
   // _dInvTransform[3][3] = | ( fg - di ) ( ai - cg ) ( cd - af ) |
   //                        | ( dh - ge ) ( bg - ah ) ( ae - bd ) |
   
   dA = _dTransform[0][0];
   dB = _dTransform[0][1];
   dC = _dTransform[0][2];
   dD = _dTransform[1][0];
   dE = _dTransform[1][1];
   dF = _dTransform[1][2];
   dG = _dTransform[2][0];
   dH = _dTransform[2][1];
   dI = _dTransform[2][2];

   _dInvTransform[0][0] = dE * dI - dF * dH;
   _dInvTransform[0][1] = dC * dH - dB * dI;
   _dInvTransform[0][2] = dB * dF - dC * dE;
   _dInvTransform[1][0] = dF * dG - dD * dI;
   _dInvTransform[1][1] = dA * dI - dC * dG;
   _dInvTransform[1][2] = dC * dD - dA * dF;
   _dInvTransform[2][0] = dD * dH - dG * dE;
   _dInvTransform[2][1] = dB * dG - dA * dH;
   _dInvTransform[2][2] = dA * dE - dB * dD;

   setTransform(pixq_Properties::TransformationProjective);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   Mtx.free();
   Inv.free();
#ifdef _DEBUG
   Check.free();
#endif // _DEBUG
   return bRetCode;
}

//
// get projective transformation parameters using least suqare method
//
// notes:
// this function should only be called from GetProjectiveTransform
//

bool pixq_FringesTag::GetProjectiveLSM(void)
{
   bool bRetCode = false;
   bool bUsed;
   int i, j, nUsedTags, nTags;
   double dX, dU, dV, dY, dTrans[8][8], dPara[9], dVec[8];
   double dA, dB, dC, dD, dE, dF, dG, dH, dI;

   pixq_FringeTag *pTag;

   char szLog[RECORD_SIZE];

   pixq_Matrix<double> Mtx, Inv;

#ifdef _DEBUG
   pixq_Matrix<double> Check;
   double dVal[8];
   char szRecord[RECORD_SIZE];
#endif // _DEBUG

   // match right image to left

   nTags = getTags();
   nUsedTags = getUsedTags();
   if( 4 >= nUsedTags ) {
      sprintf( szLog, "Projective Tranformation : Not Enough Used Points - %d", nUsedTags );
      _vstrLog.push_back( szLog );
      goto PIX_EXIT;
   }

   //

   for( i = 0 ; i < 8 ; i++ ) {
      for( j = 0 ; j < 8 ; j++ ) {
         dTrans[i][j] = 0.0;
      }
      dVec[i] = 0.0;
   }

   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
      bUsed = pTag->getUsed();
      if( !bUsed ) continue;

      dX = (double)pTag->getXTag();
      dY = (double)pTag->getYTag();

      dU = (double)pTag->getRightXTag();
      dV = (double)pTag->getRightYTag();

      //
      
      dTrans[0][0] = dTrans[0][0] + dX * dX;
      dTrans[0][1] = dTrans[0][1] + dX * dY;
      dTrans[0][2] = dTrans[0][2] + dX;
      dTrans[0][3] = dTrans[0][3] + 0.0;
      dTrans[0][4] = dTrans[0][4] + 0.0; 
      dTrans[0][5] = dTrans[0][5] + 0.0; 
      dTrans[0][6] = dTrans[0][6] - dU * dX * dX;  
      dTrans[0][7] = dTrans[0][7] - dU * dX * dY;  
                     
      dTrans[1][0] = dTrans[1][0] + dX * dY;
      dTrans[1][1] = dTrans[1][1] + dY * dY;
      dTrans[1][2] = dTrans[1][2] + dY;
      dTrans[1][3] = dTrans[1][3] + 0.0; 
      dTrans[1][4] = dTrans[1][4] + 0.0;  
      dTrans[1][5] = dTrans[1][5] + 0.0;  
      dTrans[1][6] = dTrans[1][6] - dU * dX * dY;  
      dTrans[1][7] = dTrans[1][7] - dU * dY * dY;  
                     
      dTrans[2][0] = dTrans[2][0] + dX;
      dTrans[2][1] = dTrans[2][1] + dY; 
      dTrans[2][2] = dTrans[2][2] + 1.0; 
      dTrans[2][3] = dTrans[2][3] + 0.0; 
      dTrans[2][4] = dTrans[2][4] + 0.0;  
      dTrans[2][5] = dTrans[2][5] + 0.0;  
      dTrans[2][6] = dTrans[2][6] - dU * dX;  
      dTrans[2][7] = dTrans[2][7] - dU * dY; 
                     
      dTrans[3][0] = dTrans[3][0] + 0.0; 
      dTrans[3][1] = dTrans[3][1] + 0.0;  
      dTrans[3][2] = dTrans[3][2] + 0.0;  
      dTrans[3][3] = dTrans[3][3] + dX * dX; 
      dTrans[3][4] = dTrans[3][4] + dX * dY; 
      dTrans[3][5] = dTrans[3][5] + dX; 
      dTrans[3][6] = dTrans[3][6] - dV * dX * dX;
      dTrans[3][7] = dTrans[3][7] - dV * dX * dY;
                     
      dTrans[4][0] = dTrans[4][0] + 0.0;
      dTrans[4][1] = dTrans[4][1] + 0.0;  
      dTrans[4][2] = dTrans[4][2] + 0.0;  
      dTrans[4][3] = dTrans[4][3] + dX * dY; 
      dTrans[4][4] = dTrans[4][4] + dY * dY; 
      dTrans[4][5] = dTrans[4][5] + dY; 
      dTrans[4][6] = dTrans[4][6] - dV * dX * dY;  
      dTrans[4][7] = dTrans[4][7] - dV * dY * dY;  
                     
      dTrans[5][0] = dTrans[5][0] + 0.0;
      dTrans[5][1] = dTrans[5][1] + 0.0;  
      dTrans[5][2] = dTrans[5][2] + 0.0;  
      dTrans[5][3] = dTrans[5][3] + dX;
      dTrans[5][4] = dTrans[5][4] + dY; 
      dTrans[5][5] = dTrans[5][5] + 1.0;
      dTrans[5][6] = dTrans[5][6] - dV * dX;
      dTrans[5][7] = dTrans[5][7] - dV * dY;
                     
      dTrans[6][0] = dTrans[6][0] - dU * dX * dX; 
      dTrans[6][1] = dTrans[6][1] - dU * dX * dY;  
      dTrans[6][2] = dTrans[6][2] - dU * dX;  
      dTrans[6][3] = dTrans[6][3] - dV * dX * dX;  
      dTrans[6][4] = dTrans[6][4] - dV * dX * dY;
      dTrans[6][5] = dTrans[6][5] - dV * dX; 
      dTrans[6][6] = dTrans[6][6] + dU * dU * dX * dX + dV * dV * dX * dX; 
      dTrans[6][7] = dTrans[6][7] + dU * dU * dX * dY + dV * dV * dX * dY;
                     
      dTrans[7][0] = dTrans[7][0] - dU * dX * dY; 
      dTrans[7][1] = dTrans[7][1] - dU * dY * dY;  
      dTrans[7][2] = dTrans[7][2] - dU * dY;  
      dTrans[7][3] = dTrans[7][3] - dV * dX * dY;  
      dTrans[7][4] = dTrans[7][4] - dV * dY * dY;  
      dTrans[7][5] = dTrans[7][5] - dV * dY;
      dTrans[7][6] = dTrans[7][6] + dU * dU * dX * dY + dV * dV * dX * dY;
      dTrans[7][7] = dTrans[7][7] + dU * dU * dY * dY + dV * dV * dY * dY;
      
      dVec[0] = dVec[0] + dU * dX;
      dVec[1] = dVec[1] + dU * dY;
      dVec[2] = dVec[2] + dU; 
      dVec[3] = dVec[3] + dV * dX; 
      dVec[4] = dVec[4] + dV * dY; 
      dVec[5] = dVec[5] + dV; 
      dVec[6] = dVec[6] - dU * dU * dX - dV * dV * dX; 
      dVec[7] = dVec[7] - dU * dU * dY - dV * dV * dY;
   }

   if( !Mtx.Alloc( 8, 8 ) ) {
      goto PIX_EXIT;
   }

   for( i = 0 ; i < 8 ; i++ ) {
      for( j = 0 ; j < 8 ; j++ ) {
         Mtx.Set( i, j, dTrans[i][j] );
      }
   }

   if( !Mtx.GetInverse( &Inv ) ) {
      goto PIX_EXIT;
   }

#ifdef _DEBUG
   Check.ProductSquare( &Mtx, &Inv );
   for( i = 0 ; i < 8 ; i++ ) {
      for( j = 0 ; j < 8 ; j++ ) {
         dVal[j] = Check.Get( i, j );
      }
      sprintf( szRecord, "%2d : %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f", i, 
         dVal[0], dVal[1], dVal[2], dVal[3], dVal[4], dVal[5], dVal[6], dVal[7] ); 
   }
#endif // _DEBUG

   for( i = 0 ; i < 8 ; i++ ) {
      dPara[i] = 0.0;
      for( j = 0 ; j < 8 ; j++ ) {
         dPara[i] = dPara[i] + Inv.Get( i, j ) * dVec[j];
      }
   }
      
   //
   // get parameters for projective transformation
   //
   //       m1 * x + m2 * y + m3 
   //  u = ----------------------
   //       m7 * x + m8 * y + 1 
   //
   //       m4 * x + m5 * y + m5 
   //  v = ----------------------
   //       m7 * x + m8 * y + 1 
   //
   // | m1 m2 m3 |   | m00 m01 m02 |   | a b c |
   // | m4 m5 m6 | = | m10 m11 m12 | = | d e f |
   // | m7 m8  1 |   | m20 m21 m22 |   | g h i |

   _dTransform[0][0] = dPara[0];
   _dTransform[0][1] = dPara[1];
   _dTransform[0][2] = dPara[2];
   _dTransform[1][0] = dPara[3];
   _dTransform[1][1] = dPara[4];
   _dTransform[1][2] = dPara[5];
   _dTransform[2][0] = dPara[6];
   _dTransform[2][1] = dPara[7];
   _dTransform[2][2] = 1.0;

   // set inverse matrix
   
   //      ( ei - fh ) * u + ( ch - bi ) * v + ( bf - ce )
   // x = ------------------------------------------------- 
   //      ( dh - ge ) * u + ( bg - ah ) * v + ( ae - bd )
   //
   //      ( fg - di ) * u + ( ai - cg ) * v + ( cd - af )
   // y = ------------------------------------------------- 
   //      ( dh - ge ) * u + ( bg - ah ) * v + ( ae - bd )
   //
   //                        | ( ei - fh ) ( ch - bi ) ( bf - ce ) |
   // _dInvTransform[3][3] = | ( fg - di ) ( ai - cg ) ( cd - af ) |
   //                        | ( dh - ge ) ( bg - ah ) ( ae - bd ) |
   
   dA = _dTransform[0][0];
   dB = _dTransform[0][1];
   dC = _dTransform[0][2];
   dD = _dTransform[1][0];
   dE = _dTransform[1][1];
   dF = _dTransform[1][2];
   dG = _dTransform[2][0];
   dH = _dTransform[2][1];
   dI = _dTransform[2][2];

   _dInvTransform[0][0] = dE * dI - dF * dH;
   _dInvTransform[0][1] = dC * dH - dB * dI;
   _dInvTransform[0][2] = dB * dF - dC * dE;
   _dInvTransform[1][0] = dF * dG - dD * dI;
   _dInvTransform[1][1] = dA * dI - dC * dG;
   _dInvTransform[1][2] = dC * dD - dA * dF;
   _dInvTransform[2][0] = dD * dH - dG * dE;
   _dInvTransform[2][1] = dB * dG - dA * dH;
   _dInvTransform[2][2] = dA * dE - dB * dD;

   setTransform(pixq_Properties::TransformationProjective);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   Mtx.free();
   Inv.free();
#ifdef _DEBUG
   Check.free();
#endif // _DEBUG
   return bRetCode;
}

//
// get projective transformation parameters to transform form left to right
//
// notes:
// based on http://mf-atelier.sakura.ne.jp/mf-atelier/modules/tips/index.php/program/algorithm/a6.html
//
bool pixq_FringesTag::GetProjectiveTransform(void)
{
   bool bRetCode = false;
   bool bUsed;
   int i, nUsedTags, nTags, iX, iY, iU, iV;
   double dResiMax, dResiX, dResiY, dResi;
   double dResiAvr, dResiSum, dUU, dVV;

#ifdef _DEBUG 
   double dBtm, dX, dU, dY, dV;
#endif // _DEBUG

   pixq_FringeTag *pTag;

   char szLog[RECORD_SIZE];

   pixq_Matrix<double> Mtx, Inv;

#ifdef _DEBUG
   pixq_Matrix<double> Check;
   double dXX, dYY;
#endif // _DEBUG

   //
   
   resetTransform();
   _vstrLog.clear( );

   // get the projective transformation parameters

   nTags = getTags();
   if( 4 > nTags ) {
      sprintf( szLog, "Projective Tranformation : Not Enough Points - %d", nTags );
      _vstrLog.push_back( szLog );
      goto PIX_EXIT;
   }

   nUsedTags = getUsedTags();
   if( 4 > nUsedTags ) {
      sprintf( szLog, "Projective Tranformation : Not Enough Used Points - %d", nUsedTags );
      _vstrLog.push_back( szLog );
      goto PIX_EXIT;
   } else if( 4 == nUsedTags ) {
      if( !GetProjective4Points( ) ) {
         sprintf( szLog, "Projective Tranformation : 4 points method failed." );
         _vstrLog.push_back( szLog );      
         goto PIX_EXIT;
      }
   } else {
      if( !GetProjectiveLSM( ) ) {
         sprintf( szLog, "Projective Tranformation : Leasut Square method failed." );
         _vstrLog.push_back( szLog );      
         goto PIX_EXIT;
      }
   }
   
   // check the result

#ifdef _DEBUG 
   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
      bUsed = pTag->getUsed();
      if( !bUsed ) continue; 
   
      dX = (double)pTag->getXTag();
      dY = (double)pTag->getYTag();

      dU = (double)pTag->getRightXTag();
      dV = (double)pTag->getRightYTag();

      dBtm = _dTransform[2][0] * dX + _dTransform[2][1] * dY + _dTransform[2][2];      
      dUU = ( _dTransform[0][0] * dX + _dTransform[0][1] * dY + _dTransform[0][2] ) / dBtm;
      dVV = ( _dTransform[1][0] * dX + _dTransform[1][1] * dY + _dTransform[1][2] ) / dBtm;
      
      dBtm = _dInvTransform[2][0] * dU + _dInvTransform[2][1] * dV + _dInvTransform[2][2];      
      dXX = ( _dInvTransform[0][0] * dU + _dInvTransform[0][1] * dV + _dInvTransform[0][2] ) / dBtm;
      dYY = ( _dInvTransform[1][0] * dU + _dInvTransform[1][1] * dV + _dInvTransform[1][2] ) / dBtm;
   }
#endif // _DEBUG

   // 
   // *** set the computation Log ***
   // 

   sprintf( szLog, "*** Projective Tranformation : %d Point(s) ***", nTags );
   _vstrLog.push_back( szLog );

   dResiSum = 0.0;
   dResiMax = -1.0;
   nUsedTags = 0;
   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
   
      bUsed = pTag->getUsed();
      if( !bUsed ) { 
         sprintf( szLog, "Tag %03d : Not Used.", i+1 );
         _vstrLog.push_back( szLog );
         continue;
      }
      
      iX = pTag->getXTag();
      iY = pTag->getYTag();
      iU = pTag->getRightXTag();
      iV = pTag->getRightYTag();

      getTransformedRight(iX, iY, dUU, dVV);

      dResiX = dUU - (double)iU;
      dResiY = dVV - (double)iV;
      dResi = sqrt( dResiX * dResiX + dResiY * dResiY );
    
      sprintf( szLog, "Tag %03d : (%04d,%04d) -> (%04d,%04d) Residual %7.3fX | %7.3fY %7.3f",
         i+1, iX, iY,
         iU, iV,
         dResiX, dResiY, dResi );
      _vstrLog.push_back( szLog );

      dResiSum = dResiSum + dResi;
      dResiMax = max( dResiMax, dResi );
      nUsedTags = nUsedTags + 1;
   }

   sprintf( szLog, "---------------------------------------------" );
   _vstrLog.push_back( szLog );

   if( 0 == nUsedTags ) {
      dResiAvr = 0.0;
   } else {
      dResiAvr = dResiSum / (double)nUsedTags;
   }

   sprintf( szLog, "Average Residual: %7.3f pixel[%d points].", dResiAvr, nUsedTags );
   _vstrLog.push_back( szLog );
   sprintf( szLog, "Largest Residual: %7.3f pixel.", dResiMax );
   _vstrLog.push_back( szLog );

   sprintf( szLog, "Parameters for projective transformation:" );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, "      m1 * x + m2 * y + m3           m4 * x + m5 * y + m5" );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, " u = ---------------------- ,   v = ----------------------" );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, "      m7 * x + m8 * y + 1            m7 * x + m8 * y + 1" ); 
   _vstrLog.push_back( szLog );
      
   sprintf( szLog, " | m1 m2 m3 |   | %7.3f %7.3f %7.3f |", _dTransform[0][0], _dTransform[0][1], _dTransform[0][2] );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, " | m4 m5 m6 | = | %7.3f %7.3f %7.3f |", _dTransform[1][0], _dTransform[1][1], _dTransform[1][2] );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, " | m7 m8  1 |   | %7.3f %7.3f %7.3f |", _dTransform[2][0], _dTransform[2][1], _dTransform[2][2] );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, "\n" );
   _vstrLog.push_back( szLog );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get affine transformation parameters to transform form left to right
//
bool pixq_FringesTag::getTransform(int iTransform)
{
   bool bRetCode = false;

   resetTransform();

   switch( iTransform ) {
   case pixq_Properties::TransformationAffine:
      if( !GetAffineTransform( ) ) {
         goto PIX_EXIT;
      }
      break;

   case pixq_Properties::TransformationProjective:
      if( !GetProjectiveTransform( ) ) {
         goto PIX_EXIT;
      }
      break;

   default:
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FringesTag::getTransformedRight(const int iX,
                                           const int iY,
                                           double &dU,
                                           double &dV )
{
   bool bRetCode = false;
   int iTransform;

   iTransform = getTransform();
   switch( iTransform ) {
   case pixq_Properties::TransformationAffine:
      if( GetAffineTransformedRight( iX, iY, dU, dV ) ) {
         goto PIX_EXIT;
      }
      break;
      
   case pixq_Properties::TransformationProjective:
      if( GetProjectTransformedRight( iX, iY, dU, dV ) ) {
         goto PIX_EXIT;
      }
      break;

   default:
      goto PIX_EXIT;
   }
      
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FringesTag::GetAffineTransformedRight(const int iX,
                                           const int iY,
                                           double &dU,
                                           double &dV )
{
   bool bRetCode = false;
   int iTransform = getTransform();

   if (pixq_Properties::TransformationAffine != iTransform) {
      goto PIX_EXIT;
   }

   double dX = (double)iX;
   double dY = (double)iY;

   dU = dX * _dTransform[0][0] + dY * _dTransform[0][1] + _dTransform[0][2];
   dV = dX * _dTransform[1][0] + dY * _dTransform[1][1] + _dTransform[1][2];
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FringesTag::GetProjectTransformedRight(const int iX,
                                                 const int iY,
                                                 double &dU,
                                                 double &dV )
{
   bool bRetCode = false;
   int iTransform = getTransform();

   if (pixq_Properties::TransformationProjective != iTransform) {
      goto PIX_EXIT;
   }

   double dX = (double)iX;
   double dY = (double)iY;

   double dBtm = _dTransform[2][0] * dX + _dTransform[2][1] * dY + _dTransform[2][2];

   if( 0.0 == dBtm ) {
      goto PIX_EXIT;
   }

   dU = ( _dTransform[0][0] * dX + _dTransform[0][1] * dY + _dTransform[0][2] ) / dBtm;
   dV = ( _dTransform[1][0] * dX + _dTransform[1][1] * dY + _dTransform[1][2] ) / dBtm;
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FringesTag::getTransformedLeft(const int iU,
                                         const int iV,
                                         double &dX,
                                         double &dY )
{
   bool bRetCode = false;
   int iTransform = getTransform();

   switch( iTransform ) {
   case pixq_Properties::TransformationAffine:
      if( GetAffineTransformedLeft( iU, iU, dX, dY ) ) {
         goto PIX_EXIT;
      }
      break;
      
   case pixq_Properties::TransformationProjective:
      if( GetProjectTransformedLeft( iU, iU, dX, dY ) ) {
         goto PIX_EXIT;
      }
      break;

   default:
      goto PIX_EXIT;
   }
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FringesTag::GetAffineTransformedLeft(const int iU,
                                               const int iV,
                                               double &dX,
                                               double &dY )
{
   bool bRetCode = false;
   int iTransform = getTransform();

   if (pixq_Properties::TransformationAffine != iTransform) {
      goto PIX_EXIT;
   }

   double dU = (double)iU;
   double dV = (double)iV;
   
   dX = dU * _dInvTransform[0][0] + dV * _dInvTransform[0][1] + _dInvTransform[0][2];
   dY = dU * _dInvTransform[1][0] + dV * _dInvTransform[1][1] + _dInvTransform[1][2];
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_FringesTag::GetProjectTransformedLeft(const int iU,
                                                const int iV,
                                                double &dX,
                                                double &dY )
{
   bool bRetCode = false;
   int iTransform = getTransform();

   if (pixq_Properties::TransformationProjective != iTransform) {
      goto PIX_EXIT;
   }

   double dU = (double)iU;
   double dV = (double)iV;

   double dBtm = _dInvTransform[2][0] * dU + _dInvTransform[2][1] * dV + _dInvTransform[2][2];

   if( 0.0 == dBtm ) {
      goto PIX_EXIT;
   }

   dX = ( _dInvTransform[0][0] * dU + _dInvTransform[0][1] * dV + _dInvTransform[0][2] ) / dBtm;
   dY = ( _dInvTransform[1][0] * dU + _dInvTransform[1][1] * dV + _dInvTransform[1][2] ) / dBtm;
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// select no tag
//
void pixq_FringesTag::clearSelection(void)
{
   int i;
   int nTags = getTags();
   pixq_FringeTag *pTag;

   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
      pTag->SetSelected( false );
   }

   return;
}

//
// select only one tag
//
void pixq_FringesTag::ReselectTag(int iTag)
{
   int i;
   int nTags = getTags();
   pixq_FringeTag *pTag;

   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
      if( i == iTag ) {
         pTag->SetSelected( true );
      } else {
         pTag->SetSelected( false );
      }
   }

   return;
}

void pixq_FringesTag::deleteTag(int iTag)
{
   int nTags = getTags();

   if (0 > iTag) {
      goto PIX_EXIT;
   }
   
   if (nTags <= iTag) {
      goto PIX_EXIT;
   }

   _vTags.erase( _vTags.begin( ) + iTag );

   clearSelection( );

PIX_EXIT:
   return;
}

//
// select this tag and leave other selection as it is
//
void pixq_FringesTag::AddSelectTag(int iTag)
{
   int i;
   int nTags = getTags();
   pixq_FringeTag *pTag;

   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
      if( i == iTag ) {
         pTag->SetSelected( true );
      }
   }

   return;
}

//
// clear selection
// flip the selection status of this tag
//
void pixq_FringesTag::flipReselectTag(int iTag)
{
   int i;
   int nTags = getTags();
   pixq_FringeTag *pTag;

   if (0 > iTag) {
      goto PIX_EXIT;
   }
   
   if (nTags <= iTag) {
      goto PIX_EXIT;
   }

   // if this tags is selected now, just unselect it -> nothing is selected
   // other wise, select only this tag

   pTag = getNthTag(iTag);
   if (pTag->getSelected()) {
      pTag->SetSelected( false );
   } else {

      for( i = 0 ; i < nTags ; i++ ) {
         pTag = getNthTag(i);
         if( i == iTag ) {
            pTag->SetSelected( true );
         } else {
            pTag->SetSelected( false );
         }
      }
   }

PIX_EXIT:
   return;
}

int pixq_FringesTag::Selected(void)
{
   int i, nSelectedTags;
   int nTags = getTags();
   pixq_FringeTag *pTag;

   nSelectedTags = 0;
   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
      if (pTag->getSelected()) {
         nSelectedTags = nSelectedTags + 1;
      }
   }

   return nSelectedTags;
}

int pixq_FringesTag::FirstSelected(void)
{
   int i, iTag;
   int nTags = getTags();
   pixq_FringeTag *pTag;

   iTag = -1;
   for( i = 0 ; ( 0 > iTag ) && ( i < nTags ) ; i++ ) {
      pTag = getNthTag(i);
      if (pTag->getSelected()) {
         iTag = i;
      }
   }

   return iTag;
}

void pixq_FringesTag::flipUsedStatus(int iTag)
{
   int nTags = getTags();
   pixq_FringeTag *pTag;

   if (0 > iTag) {
      goto PIX_EXIT;
   }
   
   if (nTags <= iTag) {
      goto PIX_EXIT;
   }

   pTag = getNthTag(iTag);
   pTag->FlipUsed( );

PIX_EXIT:
   return;
}

// Log

int pixq_FringesTag::LogLines(void)
{
   int nLines = (int)_vstrLog.size( );
   return nLines;
}

string pixq_FringesTag::GetLog(int iLog)
{
   string strLog;

   int nLines = (int)_vstrLog.size( );
   if( 0 > iLog || iLog >= nLines ) {
      strLog.clear( );
   } else {
      strLog = _vstrLog.at( iLog );
   }

   return strLog;
}


//
// set projective transformation parameters for both images
// obtained from rotation matrix / openCV
//
void pixq_FringesTag::storeRectification(const double dMat0[3][3],
                                         const double dMat1[3][3] )
{
   bool bOutLier, bUsed;
   int i, j, k, nUsedTags, nTags;
   double dDisparityAvr, dDisparity, dDisparitySum, dDisparityMax;
   double dLX, dLY, dLU, dLV, dRX, dRY, dRU, dRV;

   char szLog[RECORD_SIZE];

   pixq_FringeTag *pTag;
   pixq_Matrix<double> Mtx[2], Inv[2];

   //
   
   resetTransform();
   _vstrLog.clear( );

   for( k = 0 ; k < 2 ; k++ ) {
      if( !Mtx[k].Alloc( 3, 3 ) ) {
         goto PIX_EXIT;
      }
   }

   for( i = 0 ; i < 3 ; i++ ) {
      for( j = 0 ; j < 3 ; j++ ) {
         Mtx[0].Set( i, j, dMat0[i][j] );
         Mtx[1].Set( i, j, dMat1[i][j] );
      }
   }

   for( k = 0 ; k < 2 ; k++ ) {
      if( !Mtx[k].GetInverse( &Inv[k] ) ) {
         goto PIX_EXIT;
      }
   }

   for( k = 0 ; k < 2 ; k++ ) {
      for( i = 0 ; i < 3 ; i++ ) {
         for( j = 0 ; j < 3 ; j++ ) {
            _dRectify[k][i][j] = Mtx[k].Get( i, j );
            _dInvRectify[k][i][j] = Inv[k].Get( i, j );
         }
      }
   }

   setTransform(pixq_Properties::TransformationRectification);

   // 
   // *** set the computation Log ***
   // 

   nTags = getTags();
#ifdef _OLD
   sprintf( szLog, "*** Stereo Rectification : %d Point(s) ***", nTags );
   _vstrLog.push_back( szLog );
#endif // _OLD

   dDisparitySum = 0.0;
   dDisparityMax = -1.0;
   nUsedTags = 0;

   for( i = 0 ; i < nTags ; i++ ) {
      pTag = getNthTag(i);
   
      bUsed = pTag->getUsed();
      
      dLX = (double)pTag->getXTag();
      dLY = (double)pTag->getYTag();
      dRX = (double)pTag->getRightXTag();
      dRY = (double)pTag->getRightYTag();

      if( bUsed ) { 
         bOutLier = pTag->GetRotOutlier( );      
         getRectifySide(0, dLX, dLY, dLU, dLV);
         getRectifySide(1, dRX, dRY, dRU, dRV);
         dDisparity = (double)fabs( dLV - dRV );
         dDisparitySum = dDisparitySum + dDisparity;
         dDisparityMax = max( dDisparityMax, dDisparity );
          
         sprintf( szLog, "Tag %03d : (%07.2f,%07.2f)/(%07.2f,%07.2f) : (%07.2f,%07.2f)/(%07.2f,%07.2f) : Disparity=%7.3f : OutLier:%s",
            i+1, 
            dLX, dLY,
            dRX, dRY,
            dLU, dLV,
            dRU, dRV,
            dDisparity, 
            bOutLier ? "Yes" : "No" );
         nUsedTags = nUsedTags + 1;

      } else {
         sprintf( szLog, "Tag %03d : (%07.2f,%07.2f)/(%07.2f,%07.2f) : Not Used.",
            i+1, 
            dLX, dLY,
            dRX, dRY );
      }
      
#ifdef _OLD
      _vstrLog.push_back( szLog );
#endif // _OLD
   }

   sprintf( szLog, "---------------------------------------------" );
   _vstrLog.push_back( szLog );

   if( 0 == nUsedTags ) {
      dDisparityAvr = 0.0;
   } else {
      dDisparityAvr = dDisparitySum / (double)nUsedTags;
   }

   sprintf( szLog, "Average Disparity: %7.3f pixel[%d points].", dDisparityAvr, nUsedTags );
   _vstrLog.push_back( szLog );
   sprintf( szLog, "Largest Disparity: %7.3f pixel.", dDisparityMax );
   _vstrLog.push_back( szLog );

#ifdef _OLD

   sprintf( szLog, "Parameters for projective transformation:" );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, " u = [ m1 * x + m2 * y + m3 ] / [ m7 * x + m8 * y + m9]" );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, " v = [ m4 * x + m5 * y + m5 ] / [ m7 * x + m8 * y + m9]" );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, " | m1 m2 m3 |     | %9.3f %9.3f %9.3f |     | %9.3f %9.3f %9.3f |", 
      _dRectify[0][0][0], _dRectify[0][0][1], _dRectify[0][0][2],
      _dRectify[1][0][0], _dRectify[1][0][1], _dRectify[1][0][2] );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, " | m4 m5 m6 | : L=| %9.3f %9.3f %9.3f | : R=| %9.3f %9.3f %9.3f |",
      _dRectify[0][1][0], _dRectify[0][1][1], _dRectify[0][1][2], 
      _dRectify[1][1][0], _dRectify[1][1][1], _dRectify[1][1][2] );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, " | m7 m8 m9 |     | %9.3f %9.3f %9.3f |     | %9.3f %9.3f %9.3f |",
      _dRectify[0][2][0], _dRectify[0][2][1], _dRectify[0][2][2], 
      _dRectify[1][2][0], _dRectify[1][2][1], _dRectify[1][2][2] );
   _vstrLog.push_back( szLog );
   
   sprintf( szLog, "\n" );
   _vstrLog.push_back( szLog );

#endif // _OLD

   // --- Done ---
PIX_EXIT:
   for( k = 0 ; k < 2 ; k++ ) {
      Mtx[k].free();
      Inv[k].free();
   }
   return;
}

//
// get common output image size
//
bool pixq_FringesTag::GetRectifiedImageExtent(int nInWidth, // [i] input image size
                                            int nInHeight, // [i] input image size
                                            int &nMinCol, // [o] output image extent
                                            int &nMinRow, // [o] output image extent 
                                            int &nMaxCol, // [o] output image extent
                                            int &nMaxRow ) // [o] output image extent
{
   bool bRetCode = false;
   int i, k;
   double dMinX, dMinY, dMaxX, dMaxY;
   double dX[4], dY[4], dU[2][4], dV[2][4];  

   if (pixq_Properties::TransformationRectification != _iTransformMethod) {
      goto PIX_EXIT;
   }
   
   dX[0] = 0.0;
   dY[0] = 0.0;
   dX[1] = (double)nInWidth - 1.0;
   dY[1] = 0.0;
   dX[2] = (double)nInWidth - 1.0;
   dY[2] = (double)nInHeight - 1.0;
   dX[3] = 0.0;
   dY[3] = (double)nInHeight - 1.0;
   
   for( i = 0 ; i < 2 ; i++ ) {
      for( k = 0 ; k < 4 ; k++ ) {
         getRectifySide(i, dX[k], dY[k], dU[i][k], dV[i][k]);
      }
   }
   
   dMinX = dU[0][0];
   dMinY = dV[0][0];
   dMaxX = dU[0][0];
   dMaxY = dV[0][0];

   for( i = 0 ; i < 2 ; i++ ) {
      for( k = 0 ; k < 4 ; k++ ) {
         dMinX = min( dMinX, dU[i][k] );
         dMinY = min( dMinY, dV[i][k] );
         dMaxX = max( dMaxX, dU[i][k] );
         dMaxY = max( dMaxY, dV[i][k] );
      }
   }

   nMinCol = (int)floor( 0.5 + dMinX );
   nMinRow = (int)floor( 0.5 + dMinY );
   nMaxCol = (int)floor( 0.5 + dMaxX );
   nMaxRow = (int)floor( 0.5 + dMaxY );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

pixq_Dbl2D pixq_FringesTag::getRectifyDisparity(const int iX,
   const int iY,
   const int iU,
   const int iV)
{
   pixq_Dbl2D dis;
   double dX, dY, dU, dV;
   double dDisparity = -1.0;

   if (!getRectifySide(0, iX, iY, dX, dY)) {
      goto PIX_EXIT;
   }
   
   if (!getRectifySide(1, iU, iV, dU, dV)) {
      goto PIX_EXIT;
   }

   dis.setID(0);
   dis.setX(fabs(dX - dU));
   dis.setY(fabs(dY - dV));

PIX_EXIT:
   return dis;
}

pixq_Dbl2D pixq_FringesTag::getRectifyDisparity(int iTag)
{
   pixq_Dbl2D dis;

   pixq_FringeTag *pTag = getNthTag(iTag);
   if (!pTag) {
      goto PIX_EXIT;
   }

   int iX = pTag->getXTag();
   int iY = pTag->getYTag();
   int iU = pTag->getRightXTag();
   int iV = pTag->getRightYTag();
   
   dis = getRectifyDisparity(iX, iY, iU, iV);
   dis.setID(pTag->getTagID());

PIX_EXIT:
   return dis;
}


//
// 
//
double pixq_FringesTag::getVerticalDisparity(const int iX,
   const int iY,
   const int iU,
   const int iV)
{
   double dX, dY, dU, dV;
   double dDisparity = -1.0;

   if (!getRectifySide(0, iX, iY, dX, dY)) {
      goto PIX_EXIT;
   }

   if (!getRectifySide(1, iU, iV, dU, dV)) {
      goto PIX_EXIT;
   }

   dDisparity = fabs(dY - dV);

PIX_EXIT:
   return dDisparity;
}

double pixq_FringesTag::getVerticalDisparity(int iTag)
{
   double dDisparity = -1.0;

   pixq_FringeTag *pTag = getNthTag(iTag);
   if (!pTag) {
      goto PIX_EXIT;
   }

   int iX = pTag->getXTag();
   int iY = pTag->getYTag();
   int iU = pTag->getRightXTag();
   int iV = pTag->getRightYTag();

   dDisparity = getVerticalDisparity(iX, iY, iU, iV);

PIX_EXIT:
   return dDisparity;
}

//
// get the maximu disparity among points
//
// notes:
// iMaxTag - tag with largest disparity, -1 if something is wrong
//
double pixq_FringesTag::getMaxRectifyDisparity(int &iMaxTag)
{
   double dDisparity;
   int i, nTags;
   bool bUsed;
   double dMaxDisparity = -1.0;
   pixq_FringeTag *pTag;

   nTags = getTags();
   iMaxTag = -1;

   if (0 >= nTags) {
      goto PIX_EXIT;
   }

   for (i = 0; i < nTags; i++) {
      pTag = getNthTag(i);
      bUsed = pTag->getUsed();
      if (!bUsed) continue;

      dDisparity = getVerticalDisparity(i);
      if (0 > iMaxTag) {
         dMaxDisparity = dDisparity;
         iMaxTag = i;
      }
      else {
         if (dDisparity > dMaxDisparity) {
            dMaxDisparity = dDisparity;
            iMaxTag = i;
         }
      }
   }

PIX_EXIT:
   return dMaxDisparity;
}

//
// returns:
// average disparity of valid tags
// -1 if no valid tag existrs
//
double pixq_FringesTag::getAverageRectifyDisparity(void)
{
   double dDisparity;
   int i,nUsedTags,  nTags;
   bool bUsed;
   double dAvrDisparity = -1.0;
   pixq_FringeTag *pTag;

   nTags = getTags();

   if (0 >= nTags) {
      dAvrDisparity = -1.0;
      goto PIX_EXIT;
   }

   dAvrDisparity = 0.0;
   nUsedTags = 0;
   for (i = 0; i < nTags; i++) {
      pTag = getNthTag(i);
      bUsed = pTag->getUsed();
      if (!bUsed) continue;

      dDisparity = getVerticalDisparity(i);
      dAvrDisparity = dAvrDisparity + dDisparity;
      nUsedTags = nUsedTags + 1;
   }

   if (0 >= nUsedTags) {
      dAvrDisparity = -1.0;
      goto PIX_EXIT;
   }

   dAvrDisparity = dAvrDisparity / (double)nUsedTags;

PIX_EXIT:
   return dAvrDisparity;
}

bool pixq_FringesTag::getRectifySide(const int iSide,
   const  int iX,
   const   int iY,
   double &dU, 
   double &dV )
{
   bool bRetCode = false;
   double dX = (double)iX;
   double dY = (double)iY; 

   if (!getRectifySide(iSide, dX, dY, dU, dV)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


bool pixq_FringesTag::getRectifySide(const int iSide,
   const double dX,
   const double dY,
   double &dU, 
   double &dV)                                      
{
   bool bRetCode = false;
   double dBtm;
   int iTransform = getTransform();

   if( 0 > iSide || 1 < iSide ) {
      goto PIX_EXIT;
   }

   if (pixq_Properties::TransformationRectification != iTransform) {
      goto PIX_EXIT;
   }

   dBtm = _dRectify[iSide][2][0] * dX + _dRectify[iSide][2][1] * dY + _dRectify[iSide][2][2];

   if( 0.0 == dBtm ) {
      goto PIX_EXIT;
   }

   dU = ( _dRectify[iSide][0][0] * dX + _dRectify[iSide][0][1] * dY + _dRectify[iSide][0][2] ) / dBtm;
   dV = ( _dRectify[iSide][1][0] * dX + _dRectify[iSide][1][1] * dY + _dRectify[iSide][1][2] ) / dBtm;
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

