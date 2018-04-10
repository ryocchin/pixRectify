//
// pixq_ImageMatrix
// 2D image matrix class derived from pixq_Matrix
//
#pragma once

//#include <Magick++.h>
//using namespace Magick;

namespace _pix_plot_img_framework {

class pixq_ImageAccess;

class PIXIMGLIB_EXPORT pixq_ImageMatrix : public pixq_Matrix<unsigned short>
{
private:
   //
   // ファイルから読み込んだ画像のサイズを他の画像に合わせて大きくし
   // 画像データがない部分をダミー値で埋めた場合、元の画像のサイズをここに記録しておく
   //
   int _nValidWidth;
   int _nValidHeight;

public:
	explicit pixq_ImageMatrix( void );
	~pixq_ImageMatrix( void );
 
public:
   int getValidWidth( void ) { return _nValidWidth; }
   int getValidHeight( void ) { return _nValidHeight; }
   
   bool cropImage(int nTopRow, int nBottomRow, int nLeftCol, int nRightCol,
      pixq_ImageMatrix *pDest) const;

   // crop the specific area of the matrix or expand and create new matrix
   virtual bool crop(int nNewHeight, int nNewWidth, unsigned short usFill,
      bool bFromTop ); 

   // allocate matrix
	virtual bool Alloc( int nRows, int nCols );
   virtual bool checkAlloc(int nRows, int nCols);

   // release matrix
   virtual void free(void);

   bool getDouble(const pixq_Matrix<double> *dMtx);

public:
   //
   //
   //
   friend class pixq_ImageAccess;

};

} // namespace _pix_plot_img_framework 
