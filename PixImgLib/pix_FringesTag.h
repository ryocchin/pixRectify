#pragma once

namespace _pix_plot_img_framework {

//
// set(matrix) of fringe tags
// 
// 

#include <piximglib_global.h>

class pixq_FringeTag;

class PIXIMGLIB_EXPORT pixq_FringesTag
{
public:
   pixq_FringesTag(void);
   ~pixq_FringesTag(void);

   // copy constructor
   pixq_FringesTag &operator=(const pixq_FringesTag &that);

private:
   // tag positions to measure color displacement
   vector<pixq_FringeTag> _vTags;

   int _nTagRows;
   int _nTagCols;

   // last transformation method
   // one of ITQF_DepthEnv::ImageTransformationMethod
   // TransformationNone before any transformation is done

   int _iTransformMethod;

   //
   // left to right conversion matrix
   // right               left 
   // | u |   | a b c |   | x |
   // | v | = | d e f | * | y |
   // | w |   | 0 0 1 |   | 1 |
   //  
   //                     | m00 m01 m02 |   | a b c |
   // _dTransform[3][3] = | m10 m11 m12 | = | d e f |
   //                     | m20 m21 m22 |   | 0 0 1 |
   //    

   //
   // left to right conversion matrix
   // left                   right 
   // | x |   | i00 i01 i02 |   | u |
   // | y | = | i10 i11 i12 | * | v |
   // | z |   |    0  0   1 |   | 1 |
   //  
   //                        | x |   | aa bb cc |   | u |
   // _dInvTransform[3][3] = | y | = | dd ee ff | * | v |
   //                        | z |   |  0  0  1 |   | 1 |

   //
   // parameters for projective transformation
   //
   //       m1 * x + m2 * y + m3 
   //  u = ----------------------
   //       m7 * x + m8 * y + 1 
   //
   //       m4 * x + m5 * y + m5 
   //  v = ----------------------
   //       m7 * x + m8 * y + 1 
   //
   //                     | m1 m2 m3 |   | m00 m01 m02 |   | a b c |
   // _dTransform[3][3] = | m4 m5 m6 | = | m10 m11 m12 | = | d e f | 
   //                     | m7 m8  1 |   | m20 m21 m22 |   | g h i |
   //
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
   //

   double _dTransform[3][3];
   double _dInvTransform[3][3];

   // for stereo rectification

   double _dRectify[2][3][3];
   double _dInvRectify[2][3][3];

   // to store the log of processing

   vector<string> _vstrLog;

private:
   //
   // draw control points in screen?
   //
   bool _bDrawControlPnts;

public:
   void deleteTag( int iTag );

   void init( void );

   void setTagRows( int nTagRows ) { _nTagRows = nTagRows; }
   void setTagCols( int nTagCols ) { _nTagCols = nTagCols; }

   int getTagRows(void) { return _nTagRows; }
   int getTagCols(void) { return _nTagCols; }
   
   int getTags(void);
   int getUsedTags(void);
   void setAllUsed(bool bUsed);

   pixq_FringeTag *getNthTag(int iTag);
   pixq_FringeTag *getTag(int iCol, int iRow);
   
   bool getTagRowCol(int iTag, int &iRow, int &iCol);

   void Resize( int nTags );
   
   bool CheckTagInside( int iCol, int iRow );

   void Clear( void );

   bool getTransform(int iTransform);
   bool GetAffineTransform( void ); 
   bool GetProjective4Points( void ); 
   bool GetProjectiveLSM( void ); 
   bool GetProjectiveTransform( void ); 

   void setTransform(int iMethod) { _iTransformMethod = iMethod; }
   int getTransform(void) { return _iTransformMethod; }
   void resetTransform(void) { _iTransformMethod = pixq_Properties::TransformationNone; }

   bool getTransformedRight(const int iX, const int iY, double &dU, double &dV);
   bool GetAffineTransformedRight( const int iX, const int iY, double &dU, double &dV );
   bool GetProjectTransformedRight( const int iX, const int iY, double &dU, double &dV );

   bool getTransformedLeft(const int iU, const int iV, double &dX, double &dY);
   bool GetAffineTransformedLeft( const int iU, const int iV, double &dX, double &dY );
   bool GetProjectTransformedLeft( const int iU, const int iV, double &dX, double &dY );

   void clearSelection(void);

   bool getRectifySide(const int iSide, const double dX, const double dY,
      double &dU, double &dV);
   bool getRectifySide(const int iSide, const int iX, const int iY, double &dU, double &dV);
   
   double getVerticalDisparity(const int iX, const int iY, const  int iU, const int iV);
   double getVerticalDisparity(int iTag);

   pixq_Dbl2D getRectifyDisparity(const int iX, const int iY, const  int iU, const int iV);
   pixq_Dbl2D getRectifyDisparity(int iTag);

   double getMaxRectifyDisparity(int &iMaxTag);
   double getAverageRectifyDisparity(void);

   void ReselectTag( int iTag );
   void AddSelectTag( int iTag );
   void flipReselectTag(int iTag);
   int Selected( void );
   int FirstSelected( void );

   void flipUsedStatus( int iTag );

   void storeRectification(const double dMat0[3][3], const double dMat1[3][3] );

   // Log

   int LogLines( void );
   string GetLog( int iLog );

   void ReturnTransform( double dTransform[3][3] ) { 
      int i, j;
      for( i = 0 ; i < 3 ; i++ ) {
         for( j = 0 ; j < 3 ; j++ ) {
            dTransform[i][j] = _dTransform[i][j];
         }
      }
   }

   void ReturnInvTransform( double dTransform[3][3] ) { 
      int i, j;
      for( i = 0 ; i < 3 ; i++ ) {
         for( j = 0 ; j < 3 ; j++ ) {
            dTransform[i][j] = _dInvTransform[i][j];
         }
      }
   }
   
   void ReturnRectify( int iSide, double dTransform[3][3] ) { 
      int i, j;
      for( i = 0 ; i < 3 ; i++ ) {
         for( j = 0 ; j < 3 ; j++ ) {
            dTransform[i][j] = _dRectify[iSide][i][j];
         }
      }
   }

   void ReturnInvRectify( int iSide, double dTransform[3][3] ) { 
      int i, j;
      for( i = 0 ; i < 3 ; i++ ) {
         for( j = 0 ; j < 3 ; j++ ) {
            dTransform[i][j] = _dInvRectify[iSide][i][j];
         }
      }
   }

   // get common output image size

   bool GetRectifiedImageExtent( int nInWidth, int nInHeight,
      int &nMinCol, int &nMinRow,
      int &nMaxCol, int &nMaxRow ); 
   
public:
   bool getDrawCtrlPoints(void) const { return _bDrawControlPnts; }
   void setDrawCtrlPoints(bool bDraw) { _bDrawControlPnts = bDraw; }
   void switchDrawCtrlPoints(void) { _bDrawControlPnts = !_bDrawControlPnts; }
};

} // namespace _imax_imgtec_qt_framework
