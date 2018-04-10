//
// class:
// pixq_TextureBuffer
//
// working buffer to copy image data to opengl texture
// notes:
//
// history:
// was called ITF_DepthTexture in DepthCommon
//

#pragma once

namespace _pix_plot_img_framework {

class PIXIMGLIB_EXPORT pixq_TextureBuffer
{
public:
   enum {
      BufferVariableUnknownType = 0,
      // BYTE
      BufferVariableUnsignedCharType,
      // WORD
      BufferVariableUnsignedShortType,
      // unsigned long
      BufferVariableUnsignedLongType,

   } BufferVariableType;

public:
   pixq_TextureBuffer(void);
   ~pixq_TextureBuffer(void);

   pixq_TextureBuffer &operator=( const pixq_TextureBuffer &that );

public:
   void Reset( void );

   bool Alloc( int nWidth, int nHeight, int nColors, short sType );
   bool checkAlloc(int nWidth, int nHeight, int nColors = -1, short sType = -1);

   // return as BYTE
   unsigned char *ucGetBuffer( void ) { return (unsigned char*)m_Buffer; }

   // return WORD
   unsigned short *usGetBuffer( void ) { return (unsigned short*)m_Buffer; }

   // return unsigned long
   unsigned long *ulGetBuffer( void ) { return (unsigned long*)m_Buffer; }

private:  
   // buffer to be given to opengl texture functions
   void *m_Buffer;

   // texture size
   int m_nHeight;
   int m_nWidth;

   // number of colors
   int m_nColors;

   // variabe type, one of BufferVariableType
   short m_sType;
};

} // namespace _pix_plot_img_framework 

