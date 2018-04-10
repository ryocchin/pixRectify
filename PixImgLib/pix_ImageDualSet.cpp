#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImageDualSet.h"

pixq_ImageDualSet::pixq_ImageDualSet(void)
{
   Clear( );

   return;
}

bool pixq_ImageDualSet::Valid( void ) const 
{
   bool bValid = false;;

   switch( _sSelectMode ) {
   case PixDualSetPair:
   case PixDualSetDirectory:
      bValid = true;
      break;

   case PixDualSetNone:
   default:
      bValid = true;
      break;
   }


   return bValid;
}

pixq_ImageDualSet::~pixq_ImageDualSet( void )
{   
   Clear( );
   
   return;
}

void pixq_ImageDualSet::Clear( void )
{   
   int k;

   _sSelectMode = PixDualSetNone;

   for( k = 0 ; k < 2 ; k++ ) {
      _strImgDirs[k].clear( );
      _strImgFiles[k].clear( );
   }
   
   _iCurrentFrame = -1;

   return;
}


//
// copy constructor
//
pixq_ImageDualSet &pixq_ImageDualSet::operator=( const pixq_ImageDualSet &that )
{   
   int k;

   _sSelectMode = that._sSelectMode;
   
   for( k = 0 ; k < 2 ; k++ ) {
      _strImgDirs[k] = that._strImgDirs[k];
      _strImgFiles[k] = that._strImgFiles[k];
   }

   _iCurrentFrame = that._iCurrentFrame;
   
   // --- Done ---
	return *this;
}


int pixq_ImageDualSet::getFilesSize(int iSide)
const
{
   int nFrame;

   switch( _sSelectMode ) {
      
   case PixDualSetPair:
      nFrame = 1;
      break;

   case PixDualSetDirectory:
      nFrame = _strImgFiles[iSide].size( );
      break;

   case PixDualSetNone:
   default:
      nFrame = -1;
      break;
   }

   return nFrame;
} 

//
// returns the number of frames in the set
// for two dir mode, number of larger list is returned
//
int pixq_ImageDualSet::getFilesSize(void)
const
{
   int nFrames;
   int nFrames0 = getFilesSize(0);
   int nFrames1 = getFilesSize(1);

   switch( _sSelectMode ) {
      
   case PixDualSetPair:
      nFrames = 1;
      break;

   case PixDualSetDirectory:
      nFrames0 = getFilesSize(0);
      nFrames1 = getFilesSize(1);
      nFrames = max( nFrames0, nFrames1 );
      break;

   case PixDualSetNone:
   default:
      nFrames = -1;
      break;
   }

   return nFrames;
} 

bool pixq_ImageDualSet::getCurrentFiles(QString *strFile0, // [o]
                                        QString *strFile1 )// [o] )
                                        const
{
   bool bRetCode = false;

   if (!getCurrentFile(0, strFile0)) {
      goto PIX_EXIT;
   }
   
   if (!getCurrentFile(1, strFile1)) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:   
   return bRetCode;
}

//
// notes:
// in dir mode, if there is no file for the current frame number on this side,
// strFile is set to null
//
bool pixq_ImageDualSet::getCurrentFile(int iSide, // [i] side
                                     QString *strFile ) // [o] file name
const
{
   bool bRetCode = false;
   int nFrames, iFrame;
   
   strFile->clear( );

   switch( iSide ) {
   case 0:
   case 1:
      break;
   default:
      goto PIX_EXIT;
   }

   switch( _sSelectMode ) {      
   case PixDualSetPair:
      *strFile = _strImgFiles[iSide].at( 0 );
      break;

   case PixDualSetDirectory:
      iFrame = _iCurrentFrame;

      nFrames = _strImgFiles[iSide].size( );
      if( 0 > iFrame || iFrame >= nFrames ) {
         strFile->clear( );
      } else {
         *strFile = _strImgFiles[iSide].at( iFrame );
      }
      break;

   case PixDualSetNone:
   default:
      strFile->clear( );
      goto PIX_EXIT;
      break;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}


//
// notes:
// in dir mode, if there is no file for the current frame number on this side,
// strFile is set to null
//
bool pixq_ImageDualSet::getFrameFile(int iSide, // [i] side
                                     int iFrame, // [i] frame number
                                     QString *strFile ) // [o] file name
const
{
   bool bRetCode = false;
   int nFrames;

   strFile->clear( );

   switch( iSide ) {
   case 0:
   case 1:
      break;
   default:
      goto PIX_EXIT;
   }

   switch( _sSelectMode ) {      
   case PixDualSetPair:
   case PixDualSetDirectory:
      nFrames = _strImgFiles[iSide].size( );
      if( 0 > iFrame || iFrame >= nFrames ) {
         goto PIX_EXIT;
      } 
      *strFile = _strImgFiles[iSide].at( iFrame );
      break;

   case PixDualSetNone:
   default:
      goto PIX_EXIT;
      break;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}

QString pixq_ImageDualSet::getFrameString(void)
const
{
   int nFrames;
   QString strFrame;

   switch( _sSelectMode ) {
      
   case PixDualSetPair:
      strFrame = "Image Pair";
      break;

   case PixDualSetDirectory:
      nFrames = getFilesSize();
      strFrame.sprintf( "Two Dirs: Frame %d-[%d]-%d", 1, _iCurrentFrame+1,
         nFrames+1 );
      break;

   case PixDualSetNone:
   default:
      strFrame = "--------";
      break;
   }

   return strFrame;
}

bool pixq_ImageDualSet::ShiftCurrentFrame( int iShift ) // [i] frame number increment
                                 
{
   bool bRetCode = false;
   int iNewFrame, iCurrentFrame, nFrames;   

   // --- check conditions --- 
   
   switch( _sSelectMode ) {  
   case PixDualSetDirectory:
      break;

   case PixDualSetPair:
   case PixDualSetNone:
   default:
      goto PIX_EXIT;
      break;
   }

   //
   
   iCurrentFrame = getCurrentFrame();
   nFrames = getFilesSize();

   if( 0 > iCurrentFrame ) {
      goto PIX_EXIT;
   }
  
   iNewFrame = iCurrentFrame + iShift;
   if( 0 > iNewFrame ) {
      iNewFrame = nFrames - 1;
   }

   if( nFrames <= iNewFrame ) {
      iNewFrame = 0;
   }

   SetCurrentFrame( iNewFrame );

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}

bool pixq_ImageDualSet::SetCurrentFrame( int iFrame ) 
                                 
{
   bool bRetCode = false;
   int nFrames;   

   // --- check conditions --- 
   
   switch( _sSelectMode ) {  
   case PixDualSetDirectory:
   case PixDualSetPair:
      break;

   case PixDualSetNone:
   default:
      goto PIX_EXIT;
      break;
   }

   //
   
   nFrames = getFilesSize();

   if( 0 > iFrame ) {
      goto PIX_EXIT;
   }

   if( nFrames <= iFrame ) {
      goto PIX_EXIT;
   }

   _iCurrentFrame = iFrame;

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}
   
void pixq_ImageDualSet::setImagePair(const QString strFile0,
                                     const QString strFile1 )
{
   _sSelectMode = PixDualSetPair;

   _iCurrentFrame = 0;
   
   _strImgFiles[0].clear( );
   _strImgFiles[1].clear( );

   _strImgFiles[0].push_back( strFile0 );
   _strImgFiles[1].push_back( strFile1 );
      
   _strImgDirs[0].clear( );
   _strImgDirs[1].clear( );

   return;
}

//
// make lists of all image files in selected directories
//
bool pixq_ImageDualSet::setImageDirs( const QString strDir0, 
                                     const QString strDir1 )
{
   bool bRetCode = false;
   QStringList nameFilters;
   QFileInfoList files[2];
   QFileInfo info;
   QString strFile;
   QDir path[2];
   int k, i, nFiles[2];
   
   path[0].setPath( strDir0 );
   path[1].setPath( strDir1 );
   imageMagickDirFilter_PI(true, nameFilters);

   // make list of all image files in both dir

   for( k = 0 ; k < 2 ; k++ ) { 
      files[k] = path[k].entryInfoList( nameFilters, 
         QDir::Files | QDir::Readable,
         QDir::Name ); 

      nFiles[k] = (int)files[k].size( );

      // set the list of files in data
      
      qDebug() << path[k].absolutePath( ) << "--------";

      _strImgFiles[k].clear( );      
      for( i = 0 ; i < nFiles[k] ; i++ ) {
         info = files[k].at( i );
         strFile = info.absoluteFilePath( );
         _strImgFiles[k].push_back( strFile );

         qDebug() << k << i+1 << "/" << nFiles[k] << ":" << strFile;
      }

      // sort list by file name

      _strImgFiles[k].sort( Qt::CaseSensitive );
   }

   qDebug() << "Number of Files in Dirs: " << nFiles[0] << "," << nFiles[1];

   //

   if( 0 >= nFiles[0] || 0 >= nFiles[1] ) {
      // no file in one or both directories
      _sSelectMode = PixDualSetNone;
      _iCurrentFrame = -1;
      goto PIX_EXIT;
   }
   
   //
   
   _strImgDirs[0] = strDir0;
   _strImgDirs[1] = strDir1;

   _sSelectMode = PixDualSetDirectory;
   _iCurrentFrame = 0;
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}