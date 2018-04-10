#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_DualTexture.h"

pixq_DualTexture::pixq_DualTexture(void)
{
   Init( );
}

pixq_DualTexture::~pixq_DualTexture(void)
{
   Release( );
}

void pixq_DualTexture::Init( void )
{
   int k;
   for( k = 0 ; k < 2 ; k++ ) {
      _uiImgTexture[k] = -1;
      _bIsImgTexture[k] = false;
   }

   _bImgInit = false;

   return;
}

void pixq_DualTexture::Release( void )
{
   int k;
   for( k = 0 ; k < 2 ; k++ ) {
      _uiImgTexture[k] = -1;
      _bIsImgTexture[k] = false;
   }

   _bImgInit = false;
   return;
}

void pixq_DualTexture::Delete( void ) 
{
   int k;

   if( _bImgInit ) {
      //wglMakeCurrent( hDC, hRC );
      glDeleteTextures( 2, _uiImgTexture );
      //wglMakeCurrent( hDC, NULL );
      _bImgInit = false;
   }

   for( k = 0 ; k < 2 ; k++ ) {
      _uiImgTexture[k] = -1;
      _bIsImgTexture[k] = false;
   }

   return;
}

void pixq_DualTexture::initTexture(void)
{  
   // --- init image texture ---

   if( _bImgInit ) {
      goto PIX_EXIT;
   }
  
   //wglMakeCurrent( hDC, hRC );
   glGenTextures( 2, _uiImgTexture );
   //wglMakeCurrent( hDC, NULL );
   
   _bImgInit = true;
   
PIX_EXIT:
   return;
}
