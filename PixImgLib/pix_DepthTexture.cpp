#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_DepthTexture.h"

pixq_DepthTexture::pixq_DepthTexture(void)
{
   Init( );
}

pixq_DepthTexture::~pixq_DepthTexture(void)
{
   ; // empty
}

void pixq_DepthTexture::Init( void )
{
   m_nFrames = 0;
   _iFirstFrame = 0;

   for( int i = 0 ; i < MAX_IMAGE_TEX ; i++ ) {
      _bLoaded[i] = false; 
      _ulTexBuffer[i] = NULL;
      _usTexBuffer[i] = NULL;
      _ucTexBuffer[i] = NULL;
   }

   return;
}

void pixq_DepthTexture::ResetAll( void )
{
   int i;

   for( i = 0 ; i < MAX_IMAGE_TEX ; i++ ) {
      _bLoaded[i] = false; 

      if( _ulTexBuffer[i] ) {
         delete [] _ulTexBuffer[i];
         _ulTexBuffer[i] = NULL;
      }

      if( _usTexBuffer[i] ) {
         delete [] _usTexBuffer[i];
         _usTexBuffer[i] = NULL;
      }
      
      if( _ucTexBuffer[i] ) {
         delete [] _ucTexBuffer[i];
         _ucTexBuffer[i] = NULL;
      }
   }

   return;
}

void pixq_DepthTexture::unloadAll(void)
{
   int i;

   if( 0 < m_nFrames ) {
      glDeleteTextures( m_nFrames, m_uiTexture );  
   }

   ResetAll( );

   m_nFrames = 0;
   _iFirstFrame = 0;

   for( i = 0 ; i < MAX_IMAGE_TEX ; i++ ) {
      _bLoaded[i] = false; 

      if( _ulTexBuffer[i] ) {
         delete [] _ulTexBuffer[i];
         _ulTexBuffer[i] = NULL;
      }

      if( _usTexBuffer[i] ) {
         delete [] _usTexBuffer[i];
         _usTexBuffer[i] = NULL;
      }
      
      if( _ucTexBuffer[i] ) {
         delete [] _ucTexBuffer[i];
         _ucTexBuffer[i] = NULL;
      }
   }

   return;
}

bool pixq_DepthTexture::CheckTexture( int )
{
   return true; 
}

bool pixq_DepthTexture::GenerateTexture( int nFrames, int iFirstFrame )
{
   if( 0 >= m_nFrames ) {
      glGenTextures( nFrames, m_uiTexture );
      m_nFrames = nFrames;
      _iFirstFrame = iFirstFrame;
   }

   return true;
}

bool pixq_DepthTexture::CheckGenerateTexture( int nFrames, int iFirstFrame )
{
   if( 0 >= m_nFrames ) {
      glGenTextures( nFrames, m_uiTexture );
   } else if( nFrames != m_nFrames ) {
      glDeleteTextures( nFrames, m_uiTexture );
      glGenTextures( nFrames, m_uiTexture );
   }

   m_nFrames = nFrames;
   _iFirstFrame = iFirstFrame;

   return true;
}

bool pixq_DepthTexture::FrameLoaded( int iFrame )
{
   if( _iFirstFrame > iFrame ) return false;

   return _bLoaded[iFrame-_iFirstFrame];
}

void pixq_DepthTexture::SetFrameLoaded( int iFrame )
{
   if( _iFirstFrame > iFrame ) return;
   if( MAX_IMAGE_TEX <= (iFrame - _iFirstFrame) ) return;

   _bLoaded[iFrame-_iFirstFrame] = true;
}

void pixq_DepthTexture::ResetFrameLoaded( int iFrame )
{
   if( _iFirstFrame > iFrame ) return;
   if( MAX_IMAGE_TEX <= (iFrame - _iFirstFrame) ) return;

   _bLoaded[iFrame-_iFirstFrame] = false;
   return;
}

unsigned int pixq_DepthTexture::getTexture(int iFrame)
{
   if( _iFirstFrame > iFrame ) return 0;
   if( MAX_IMAGE_TEX <= (iFrame - _iFirstFrame) ) return 0;

   return m_uiTexture[iFrame-_iFirstFrame];
}

