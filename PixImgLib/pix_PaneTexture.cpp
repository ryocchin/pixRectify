#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

// *** OpenGL ***

#include "pix_DualTexture.h"
#include "pix_PaneTexture.h"

pixq_PaneTexture::pixq_PaneTexture(void)
{
   Init( );
}

pixq_PaneTexture::~pixq_PaneTexture(void)
{
   Release( );
}

void pixq_PaneTexture::Init( void )
{
   _RgbTexture.Init( );
   _Rg1bTexture.Init( );

   _RedTexture.Init( );
   _GreenTexture.Init( );
   _Green1Texture.Init( );
   _BlueTexture.Init( );

   _RedPseudoTexture.Init( );
   _GreenPseudoTexture.Init( );
   _BluePseudoTexture.Init( );

   return;
}

void pixq_PaneTexture::Release( void )
{
   _RgbTexture.Release( );
   _Rg1bTexture.Release( );

   _RedTexture.Release( );
   _GreenTexture.Release( );
   _Green1Texture.Release( );
   _BlueTexture.Release( );

   _RedPseudoTexture.Release( );
   _GreenPseudoTexture.Release( );
   _BluePseudoTexture.Release( );
   return;
}

void pixq_PaneTexture::Delete( void ) 
{
   _RgbTexture.Delete( ); 
   _Rg1bTexture.Delete( ); 

   _RedTexture.Delete( ); 
   _GreenTexture.Delete( ); 
   _Green1Texture.Delete( ); 
   _BlueTexture.Delete( ); 

   _RedPseudoTexture.Delete( ); 
   _GreenPseudoTexture.Delete( ); 
   _BluePseudoTexture.Delete( ); 

   return;
}

void pixq_PaneTexture::initTexture(void)
{  
   _RgbTexture.initTexture();
   _Rg1bTexture.initTexture();

   _RedTexture.initTexture();
   _GreenTexture.initTexture();
   _Green1Texture.initTexture();
   _BlueTexture.initTexture();

   _RedPseudoTexture.initTexture();
   _GreenPseudoTexture.initTexture();
   _BluePseudoTexture.initTexture();

   return;
}

