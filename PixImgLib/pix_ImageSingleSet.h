#pragma once

//
// image pair, dual sequences data
//

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

namespace _pix_plot_img_framework {

class PIXIMGLIB_EXPORT pixq_ImageSingleSet	
{
public:
   //
   // image set selection mode
   // (1) set of any files
   // (2) single sequence
   //
   enum {
      PixSingleSetNone = 0,
      //
      // set of any files
      //
      PixSingleSetFiles,
      //
      // single sequence
      //
      PixSingleSetSequence,
   } PixLibSingleSelectionMode;

public:
   pixq_ImageSingleSet(void);
   virtual ~pixq_ImageSingleSet( void );
 
   // copy constructor
	pixq_ImageSingleSet &operator=(const pixq_ImageSingleSet &that);

private:
   // selection mode, single pair or sequences
   // one of PixLibSingleSelectionMode
   short _sSelectMode;

   // current frame / file position
   int _iCurrentFrame;

   // sequence
   pixq_ImgSequence *_pImgSequence;

   // set of files
   QStringList _strImgFiles;

public:
   // initialize all parameters   
   void Init( void );
   void Deinit( void );

   short GetSelectMode( void ) { return _sSelectMode; }
   void SetSelectMode( short sMode ) { _sSelectMode = sMode; }

   pixq_ImgSequence *GetSequence( void ) const { return _pImgSequence; }

   int getCurrentFrame(void) const;
   void SetCurrentFrame( int iCurrentFrame );
   
   int GetFirstFrame( void ) const; 
   int GetLastFrame( void ) const; 
   
   bool CheckFrame( int iFrame ) const; 
   bool CheckCurrentFrame( void ) const; 

   bool getCurrentFile(QString *strFile) const;
   QString getFrameString(void) const;
   
   bool GetImageFile( int iFrame, QString *strFile ) const;
   
   bool CheckSequence( void ) const;
   
   bool ShiftCurrentFrame( int iShift );
   void SelectFirstFrame( void );
   void InitFrame( void );
   
   void SetImageList( QStringList strFiles );
};

} // namespace _pix_plot_img_framework 
