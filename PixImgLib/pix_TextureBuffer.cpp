#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_TextureBuffer.h"

pixq_TextureBuffer::pixq_TextureBuffer( void )
{
   m_Buffer = (void*)NULL;
   
   Reset( );

   return;
}

pixq_TextureBuffer::~pixq_TextureBuffer(void)
{
   Reset( );

   return;
}

void pixq_TextureBuffer::Reset( void )
{
   if( m_Buffer ) {
      delete[] m_Buffer;
      m_Buffer = (void*)NULL;
   }

   m_nHeight = -1;
   m_nWidth = -1;
   m_nColors = -1;
   
   m_sType = BufferVariableUnknownType;

   return;
}

//
// allocate buffer 
//
bool pixq_TextureBuffer::Alloc( int nWidth, // [i] texture width
                               int nHeight, // [i] texture height
                               int nColors, // [i] number of colors
                               short sType ) // [i] one of BufferVariableType
{
   bool bRetCode = false;
   int nBufferSize;

   m_nWidth  = nWidth;
   m_nHeight = nHeight;
   if( nColors > -1 ) m_nColors = nColors;
   if( sType > -1 ) m_sType = sType;

   // reallocate texture
      
   if( m_Buffer ) {
      delete [] m_Buffer;
      m_Buffer = NULL;
   }

   nBufferSize = m_nWidth * m_nHeight * m_nColors;
   switch( sType ) {
   case BufferVariableUnsignedCharType:
      m_Buffer = new unsigned char[nBufferSize];
      break;

   case BufferVariableUnsignedShortType:
      m_Buffer = new unsigned short[nBufferSize];
      break;

   case BufferVariableUnsignedLongType:
      m_Buffer = new unsigned long[nBufferSize];
      break;

   case BufferVariableUnknownType:
   default:
      goto PIX_EXIT;
   }

   if( !m_Buffer ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// reallocate the buffer only if the buffer dimension is changed
//
bool pixq_TextureBuffer::checkAlloc(int nWidth, // [i] texture width
                               int nHeight, // [i] texture height
                               int nColors,  // [i] number of colors
                               short sType ) // [i] one of BufferVariableType
{
   bool bRetCode = false;
   bool bRealloc = false;

   if( nWidth != m_nWidth ) bRealloc = true;
   if( nHeight != m_nHeight ) bRealloc = true;
   if( nColors > -1 && nColors != m_nColors ) bRealloc = true;
   if( sType > -1 && sType != m_sType ) bRealloc = true;

   if( bRealloc ) {
      if( !Alloc( nWidth, nHeight, nColors, sType ) ) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

pixq_TextureBuffer &pixq_TextureBuffer::operator=( const pixq_TextureBuffer &that )
{  
   int nBandSize, nBufferSize;

   if( this == &that ) {
      goto PIX_EXIT;
   }

   m_nHeight = that.m_nHeight;
   m_nWidth = that.m_nWidth;
   m_nColors = that.m_nColors;
   m_sType = that.m_sType;
   
   if( m_Buffer ) {
      delete [] m_Buffer;
      m_Buffer = (void*)NULL;
   }

   if( 0 > m_nHeight ) {
      goto PIX_EXIT;
   }

   nBandSize = m_nWidth * m_nHeight * m_nColors;
   switch( m_sType ) {
   case BufferVariableUnsignedCharType:
      nBufferSize = nBandSize * sizeof( unsigned char );
      break;

   case BufferVariableUnsignedShortType:
      nBufferSize = nBandSize * sizeof( unsigned short );
      break;

   case BufferVariableUnsignedLongType:
      nBufferSize = nBandSize * sizeof( unsigned long );
      break;

   case BufferVariableUnknownType:
   default:
      goto PIX_EXIT;
   }

   if( !m_Buffer ) {
      goto PIX_EXIT;
   }

   memcpy( m_Buffer, that.m_Buffer, nBufferSize );

PIX_EXIT:
   return *this;            
}

