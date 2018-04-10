//
// holds three rgb image matrices
// for quick access
//
// first input image
// second input image
// output image
//
#pragma once

namespace _pix_plot_img_framework {

#include <Magick++.h>
using namespace Magick;

class PIXIMGLIB_EXPORT pixq_ImageAccess
{
private:
   const pixq_ImageMatrix *_pInImg[3];
   const pixq_ImageMatrix *_pIn2Img[3];
   pixq_ImageMatrix *_pOutImg[3];

public:
   pixq_ImageAccess(void);
   virtual ~pixq_ImageAccess(void);
 
public:
   void setInRgb(const pixq_ImageMatrix *pRgb[3]);
   void setIn2Rgb(const pixq_ImageMatrix *pRgb[3]);

   void setOutRgb(pixq_ImageMatrix *pRgb[3]);

   void setInRgb(const pixq_ImageMatrix *pRed,
      const pixq_ImageMatrix *pGrn,
      const pixq_ImageMatrix *pBlu);

   void setIn2Rgb(const pixq_ImageMatrix *pRed,
      const pixq_ImageMatrix *pGrn,
      const pixq_ImageMatrix *pBlu);

   void setOutRgb(pixq_ImageMatrix *pRed,
      pixq_ImageMatrix *pGrn,
      pixq_ImageMatrix *pBlu);

   bool checkAllocOut(int nHeight, int nWidth);

public:
   //
   // image processing
   //
   bool setScaledDifference(double dScale);
   bool setBlending(float *fRatio);

public:
   //
   // cpu 1-d buffer
   //
#ifdef _USE_IMAGE_MAGICK
   bool getMagickBuffer( Magick::Pixels *pix);
   bool setMagickBuffer(Magick::Pixels *pix) const;
#endif // _USE_IMAGE_MAGICK
   
   //
   // get read image buffer to three matrices
   //
   bool getTiffScanLine(bool b16Bit, int iRow,
      int iSamplePerPixel, const unsigned char *ucInBuff);
   
   bool setJpegBuffer( unsigned char *ucBuffer);
};

} // _pix_plot_img_framework 
