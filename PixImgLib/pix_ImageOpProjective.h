#pragma once

//
// projective transform
//

namespace _pix_plot_img_framework {

class PIXIMGLIB_EXPORT pixq_ImageOpProjective : public pixq_ImageOp
{
public:
   pixq_ImageOpProjective(void);
   ~pixq_ImageOpProjective(void);
   
public:
   bool Proc( void );
   bool procCpu(void);
   bool procCuda(void);

   bool procClip( void );
   bool procMerge( void );

   // *** Op specific parameters ***

protected:
   void transform( double dX, double dY, double &dU, double &dV );
   void invTransform( double dU, double dV, double &dX, double &dY );

private:
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

private:
   //
   // when _bMerge is true, two images are marged to create larger
   // image that covers whole image extent, input image and 
   // transformed second image
   //
   // otherwise, second image intransformed and clipped to the same size as
   // the input image
   //
   bool _bMerge;

public:
   void Init( void );

   void setTransform(double dTransform[3][3]) {
      int i, j;
      for( i = 0 ; i < 3 ; i++ ) {
         for( j = 0 ; j < 3 ; j++ ) {
            _dTransform[i][j] = dTransform[i][j];
         }
      }
   }

   void setInvTransform( double dTransform[3][3] ) { 
      int i, j;
      for( i = 0 ; i < 3 ; i++ ) {
         for( j = 0 ; j < 3 ; j++ ) {
            _dInvTransform[i][j] = dTransform[i][j];
         }
      }
   }

   void setMerge(bool bMerge) { _bMerge = bMerge; }
   
};

} // namespace _pix_plot_img_framework 

