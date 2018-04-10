#pragma once

namespace _pix_plot_img_framework {

#include <piximglib_global.h>

class pixq_DualTexture;

class PIXIMGLIB_EXPORT pixq_PaneTexture
{
public:
   pixq_PaneTexture(void);
   ~pixq_PaneTexture(void);

private:
   // RGB color
   pixq_DualTexture _RgbTexture;

   // Each Color channel
   pixq_DualTexture _RedTexture;
   pixq_DualTexture _GreenTexture;
   pixq_DualTexture _BlueTexture;

   // for Cine file only
   pixq_DualTexture _Rg1bTexture;
   pixq_DualTexture _Green1Texture;

   // Each Color in Pseudo Color
   pixq_DualTexture _RedPseudoTexture;
   pixq_DualTexture _GreenPseudoTexture;
   pixq_DualTexture _BluePseudoTexture;

public:
   void Init( void );
   void Release( void );

   void Delete( void );  
   void initTexture(void);

   //
   // set the texture is created for the mode
   //
   void SetRgbTexture( int iSide, bool bSet ) { _RgbTexture.SetImgTexture( iSide, bSet ); }
   void SetRg1bTexture( int iSide, bool bSet ) { _Rg1bTexture.SetImgTexture( iSide, bSet ); }

   void SetRedTexture( int iSide, bool bSet ) { _RedTexture.SetImgTexture( iSide, bSet ); }
   void SetGreenTexture( int iSide, bool bSet ) { _GreenTexture.SetImgTexture( iSide, bSet ); }
   void SetGreen1Texture( int iSide, bool bSet ) { _Green1Texture.SetImgTexture( iSide, bSet ); }
   void SetBlueTexture( int iSide, bool bSet ) { _BlueTexture.SetImgTexture( iSide, bSet ); }   
   
   void SetRedPseudoTexture( int iSide, bool bSet ) { _RedPseudoTexture.SetImgTexture( iSide, bSet ); }
   void SetGreenPseudoTexture( int iSide, bool bSet ) { _GreenPseudoTexture.SetImgTexture( iSide, bSet ); }
   void SetBluePseudoTexture( int iSide, bool bSet ) { _BluePseudoTexture.SetImgTexture( iSide, bSet ); }

   //
   // check if the texture for the mode already created
   //
   bool GetIsRgbTexture( int iSide ) { return _RgbTexture.GetIsImgTexture( iSide ); }
   bool GetIsRg1bTexture( int iSide ) { return _Rg1bTexture.GetIsImgTexture( iSide ); }
   
   bool GetIsRedTexture( int iSide ) { return _RedTexture.GetIsImgTexture( iSide ); }
   bool GetIsGreenTexture( int iSide ) { return _GreenTexture.GetIsImgTexture( iSide ); }
   bool GetIsGreen1Texture( int iSide ) { return _Green1Texture.GetIsImgTexture( iSide ); }
   bool GetIsBlueTexture( int iSide ) { return _BlueTexture.GetIsImgTexture( iSide ); }
   
   bool GetIsRedPseudoTexture( int iSide ) { return _RedPseudoTexture.GetIsImgTexture( iSide ); }
   bool GetIsGreenPseudoTexture( int iSide ) { return _GreenPseudoTexture.GetIsImgTexture( iSide ); }
   bool GetIsBluePseudoTexture( int iSide ) { return _BluePseudoTexture.GetIsImgTexture( iSide ); }

   //
   // get texture id
   //
   unsigned int getRgbTexture(int iSide) { return _RgbTexture.GetImgTexture(iSide); }
   unsigned int GetRg1bTexture( int iSide ) { return _Rg1bTexture.GetImgTexture( iSide ); }
   
   unsigned int GetRedTexture( int iSide ) { return _RedTexture.GetImgTexture( iSide ); }
   unsigned int GetGrnTexture( int iSide ) { return _GreenTexture.GetImgTexture( iSide ); }
   unsigned int GetGrn1Texture( int iSide ) { return _Green1Texture.GetImgTexture( iSide ); }
   unsigned int GetBluTexture( int iSide ) { return _BlueTexture.GetImgTexture( iSide ); }
  
   unsigned int GetRedPseudoTexture( int iSide ) { return _RedPseudoTexture.GetImgTexture( iSide ); }
   unsigned int GetGrnPseudoTexture( int iSide ) { return _GreenPseudoTexture.GetImgTexture( iSide ); }
   unsigned int GetBluPseudoTexture( int iSide ) { return _BluePseudoTexture.GetImgTexture( iSide ); }
};

} // namespace _pix_plot_img_framework 

