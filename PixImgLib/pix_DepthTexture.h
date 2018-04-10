#pragma once

// maximum numer of frames

#ifndef MAX_IMAGE_TEX
#define MAX_IMAGE_TEX 20000
#endif // MAX_IMAGE_TEX

namespace _pix_plot_img_framework {

class PIXIMGLIB_EXPORT pixq_DepthTexture
{
public:
   pixq_DepthTexture(void);
   ~pixq_DepthTexture(void);

public:
   void Init( void );

   void unloadAll(void);
   void ResetAll( void );
   bool CheckTexture( int iFrame );
   bool GenerateTexture( int nFrames, int iFirstFrame );
   bool CheckGenerateTexture( int nFrames, int iFirstFrame );

   bool FrameLoaded( int iFrame );
   void SetFrameLoaded( int iFrame );
   void ResetFrameLoaded( int iFrame );

   unsigned int getTexture(int iFrame);
   //unsigned int *getTexture( void ) { return m_uiTexture; }

   unsigned long *GetLongBuffer( int iFrame ) { return _ulTexBuffer[iFrame]; }
   unsigned short *GetShortBuffer( int iFrame ) { return _usTexBuffer[iFrame]; }
   unsigned char *GetCharBuffer( int iFrame ) { return _ucTexBuffer[iFrame]; }

private:   
   // actual number of texture generated
   int m_nFrames;

   // first frame number, same as depth shot
   int _iFirstFrame;

   // --- OpenGL texture for instant right image ---
   unsigned int m_uiTexture[MAX_IMAGE_TEX];
 
   // --- true if instant right image is created as the OpenGL texture ---
   bool _bLoaded[MAX_IMAGE_TEX];

   // data buffer to store image read from file
    unsigned long *_ulTexBuffer[MAX_IMAGE_TEX];
    unsigned short *_usTexBuffer[MAX_IMAGE_TEX];
    unsigned char *_ucTexBuffer[MAX_IMAGE_TEX];
};

} // namespace _pix_plot_img_framework
