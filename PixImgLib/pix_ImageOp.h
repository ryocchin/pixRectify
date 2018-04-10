#pragma once

//
// image processing operation
//

namespace _pix_plot_img_framework {

class PIXIMGLIB_EXPORT pixq_ImageOp	
{ 
protected:
   // first input images, 16-bit
   pixq_ImageMatrix *_pIn16[3];

   // second input images, 16-bit
   pixq_ImageMatrix *_pIn2_16[3];

   // input images, 16-bit
   pixq_ImageMatrix *_pOut16[3];

   // pointer to the systems property setting
   pixq_Properties *_pDepthEnv;

   // error message
   QString _strErrorMsg;

public:
   pixq_ImageOp(void);
   virtual ~pixq_ImageOp(void);

   // copy constructor
   pixq_ImageOp &operator=(const pixq_ImageOp &that);

public:
   virtual bool procCuda(void) = 0;
   virtual bool procCpu(void) = 0;
   virtual bool Proc( void ) = 0;

   // store pointer to the input images
   void storeIn(int kPos, pixq_ImageMatrix *p16);
   void storeIn(pixq_ImageMatrix p16[]);
   
   // store pointer to the second input images
   void storeIn2(int kPos, pixq_ImageMatrix *p16);
   void storeIn2(pixq_ImageMatrix p16[]);
   
   // store pointer to the output images
   void storeOut(int kPos, pixq_ImageMatrix *p16);
   void storeOut(pixq_ImageMatrix p16[]);

   // store properties
   void storeEnv(pixq_Properties *pEnv) { _pDepthEnv = pEnv; }
   pixq_Properties *GetDepthEnv( void ) const { return _pDepthEnv; }

   // return the image size as the size of the first input matrix
   int getImageWidth(void) const { return _pIn16[0]->getWidth(); }
   int getImageHeight(void) const { return _pIn16[0]->getHeight(); }
};

} // namespace _pix_plot_img_framework 
