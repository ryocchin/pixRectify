#pragma once

namespace _pix_plot_img_framework {

#include <piximglib_global.h>

class PIXIMGLIB_EXPORT pixq_DualTexture
{
public:
   pixq_DualTexture(void);
   ~pixq_DualTexture(void);
   
private:
   // --- OpenGL texture for image ---

   unsigned int _uiImgTexture[2];

   // true when the texture is created and ready to use
   bool _bIsImgTexture[2];

   // true when texture is generated
   bool _bImgInit;

public:
   //
   // data
   //
   unsigned int GetImgTexture( int iSide ) { return _uiImgTexture[iSide]; }

   bool GetIsImgTexture( int iSide ) { return _bIsImgTexture[iSide]; }
   void SetImgTexture( int iSide, bool bSet ) { _bIsImgTexture[iSide] = bSet; }
  
public:
   void Init( void );
   void Release( void );

   void Delete( void ); // HDC hDC, HGLRC hRC );   
   void initTexture(void); // HDC hDC, HGLRC hRC ); 
};

} // namespace _pix_plot_img_framework 

