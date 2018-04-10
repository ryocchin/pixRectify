#pragma once

//
// image pair, dual sequences data
//

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

namespace _pix_plot_img_framework {

class PIXIMGLIB_EXPORT pixq_ImageDualSet	
{
public:
   //
   // file selection mode
   // two files or two sequences
   //
   enum {
      PixDualSetNone = 0,
      //
      // two files
      //
      PixDualSetPair,
      //
      // all files in two directories
      //
      PixDualSetDirectory,
   } PixLibDualSelectionMode;

private:
   // selection mode, single pair or sequences
   // one of PixLibDualSelectionMode
   short _sSelectMode;
      
   // current file number for set of files
   // begins from 0
   // for PixDualSetPair mode, it is always 0 
   int _iCurrentFrame;
   
   // two directories
   QString _strImgDirs[2];
   
   // set of files
   QStringList _strImgFiles[2];

public:
   pixq_ImageDualSet(void);
   virtual ~pixq_ImageDualSet(void);

   // copy constructor
   pixq_ImageDualSet &operator=(const pixq_ImageDualSet &that);

public:
   void Clear( void );

   short GetSelectMode( void ) const { return _sSelectMode; }
   
   int getCurrentFrame(void) const { return _iCurrentFrame; }
   
   int getFilesSize( void ) const; 
   int getFilesSize(int iSide) const;
   
   QString getFrameString(void) const;

   bool getCurrentFiles( QString *strFile0, QString *strFile1 ) const;   
   bool getCurrentFile( int iSide, QString *strFile ) const;
   bool getFrameFile( int iSide, int iFrame, QString *strFile ) const;
   
   bool ShiftCurrentFrame( int iShift );
   bool SetCurrentFrame( int iFrame );
   
   void setImagePair(const QString strFile0, const QString strFile1);
   bool setImageDirs( const QString strDir0, const QString strDir1 );
   
   QString getImgDir( int iSide ) const { return _strImgDirs[iSide]; }

   bool Valid( void ) const;
};

} // namespace _pix_plot_img_framework 
