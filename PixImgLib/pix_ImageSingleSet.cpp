#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImageSingleSet.h"

pixq_ImageSingleSet::pixq_ImageSingleSet(void)
{
   _pImgSequence  = (pixq_ImgSequence*)NULL; 

   Deinit( );

   return;
}

pixq_ImageSingleSet::~pixq_ImageSingleSet( void )
{   
   Deinit( );
   
   return;
}

void pixq_ImageSingleSet::Init( void )
{   
   _sSelectMode = PixSingleSetNone;
   _iCurrentFrame = -1;

   if( _pImgSequence ) { 
      delete _pImgSequence;
      _pImgSequence = NULL; 
   }

   _pImgSequence = new pixq_ImgSequence; 
   _pImgSequence->Init( ); 
   
   _strImgFiles.clear( );
   
   return;
}

void pixq_ImageSingleSet::Deinit( void )
{
   _sSelectMode = PixSingleSetNone;
   _iCurrentFrame = -1;

   if( _pImgSequence ) { 
      delete _pImgSequence;
      _pImgSequence = NULL; 
   }

   _strImgFiles.clear( );

   return;
}

//
// copy constructor
//
pixq_ImageSingleSet &pixq_ImageSingleSet::operator=( const pixq_ImageSingleSet &that )
{   
   _sSelectMode = that._sSelectMode;
   _iCurrentFrame = that._iCurrentFrame;
   
   _pImgSequence = that._pImgSequence;
   _strImgFiles = that._strImgFiles;
      
   // --- Done ---
	return *this;
}


void pixq_ImageSingleSet::SelectFirstFrame( void )
{
   switch( _sSelectMode ) {      
   case PixSingleSetFiles:
      _iCurrentFrame = 0;
      break;

   case PixSingleSetSequence:
      _iCurrentFrame = _pImgSequence->GetFirstFrame( );
      break;

   case PixSingleSetNone:
   default:
      _iCurrentFrame = -1;
      break;
   }
   
   return;
}


int pixq_ImageSingleSet::GetFirstFrame( void )
const
{
   int iFrame = -1;

   switch( _sSelectMode ) {      
   case PixSingleSetFiles:
      iFrame = 0;
      break;

   case PixSingleSetSequence:
      iFrame = _pImgSequence->GetFirstFrame( );
      break;

   case PixSingleSetNone:
   default:
      iFrame = -1;
      break;
   }
   
   return iFrame;
}

int pixq_ImageSingleSet::GetLastFrame( void ) 
const
{
   int iFrame = -1;

   switch( _sSelectMode ) {      
   case PixSingleSetFiles:
      iFrame = (int)_strImgFiles.size( ) - 1;
      break;

   case PixSingleSetSequence:
      iFrame = _pImgSequence->GetLastFrame( );
      break;

   case PixSingleSetNone:
   default:
      iFrame = -1;
      break;
   }

   // --- Done ---
//PIX_EXIT:
   return iFrame;
} 

bool pixq_ImageSingleSet::CheckFrame( int iFrame ) 
const
{
   bool bRetCode = false;
   int nSize;

   switch( _sSelectMode ) {      
    
   case PixSingleSetFiles:
      nSize = (int)_strImgFiles.size( );
      if( 0 > iFrame || nSize <= iFrame )  {
         goto PIX_EXIT;
      } 
      break;

   case PixSingleSetSequence:
      if( !_pImgSequence->CheckFrame( iFrame ) ) {
         goto PIX_EXIT;
      }
      break;

   case PixSingleSetNone:
   default:
      goto PIX_EXIT;
      break;
   }
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:   
   return bRetCode;
}


bool pixq_ImageSingleSet::CheckCurrentFrame( void ) 
const
{
   bool bRetCode = false;
   int iFrame = getCurrentFrame();

   if( !CheckFrame( iFrame ) ) {
      goto PIX_EXIT;
   }
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:   
   return bRetCode;
}

QString pixq_ImageSingleSet::getFrameString(void)
const
{
   int nSize, iFirstFrame, iLastFrame; 
   int iFrame = _iCurrentFrame;
   QString strFrame;

   switch( _sSelectMode ) {
      
   case PixSingleSetFiles:
      nSize = (int)_strImgFiles.size( );
      strFrame.sprintf( "Frame %d-[%d]-%d", 1, iFrame+1, nSize );
      break;

   case PixSingleSetSequence:
      iFirstFrame = _pImgSequence->GetFirstFrame( );
      iLastFrame = _pImgSequence->GetLastFrame( );
      strFrame.sprintf( "Frame %d-[%d]-%d", iFirstFrame+1, iFrame+1,
         iLastFrame+1 );
      break;

   case PixSingleSetNone:
   default:
      strFrame = "--------";
      break;
   }

   return strFrame;
}


bool pixq_ImageSingleSet::getCurrentFile(QString *strFile)// [o] )
const
{
   bool bRetCode = false;
   int iFrame = _iCurrentFrame;

   if( !GetImageFile( iFrame, strFile ) ) {
      goto PIX_EXIT;
   } 

   // --- Done ---
   bRetCode = true;
PIX_EXIT:   
   return bRetCode;
}

bool pixq_ImageSingleSet::GetImageFile( int iFrame, // [i] frame number
                                     QString *strFile ) // [o] file name
const
{
   bool bRetCode = false;
   int nSize; 

   switch( _sSelectMode ) {      
    
   case PixSingleSetFiles:
      nSize = (int)_strImgFiles.size( );
      if( 0 > iFrame || nSize <= iFrame )  {
         goto PIX_EXIT;
      } 
      *strFile = _strImgFiles.at( iFrame );
      break;

   case PixSingleSetSequence:
      if( !_pImgSequence->CheckFrame( iFrame ) ) {
         goto PIX_EXIT;
      }
      if( !_pImgSequence->GetImageFile( iFrame, strFile ) ) {
         goto PIX_EXIT;
      }
      break;

   case PixSingleSetNone:
   default:
      goto PIX_EXIT;
      break;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}

//
// check if the sequence is valid
//
bool pixq_ImageSingleSet::CheckSequence( void ) // [i] side
const
{
   bool bRetCode = false;

   // --- check arguments ---

   switch( _sSelectMode ) {  
   case PixSingleSetSequence:
      if( !_pImgSequence->Valid( ) ) {
         goto PIX_EXIT;
      }
      break;

   case PixSingleSetNone:
   case PixSingleSetFiles:
   default:
      goto PIX_EXIT;
      break;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}

int pixq_ImageSingleSet::getCurrentFrame(void)
const
{
   int iCurrentFrame = -1;

   switch( _sSelectMode ) {  
   case PixSingleSetSequence:
   case PixSingleSetFiles:
      iCurrentFrame = _iCurrentFrame;
      break;

   case PixSingleSetNone:
   default:
      iCurrentFrame = -1;
      break;
   }

   return iCurrentFrame; 
}

void pixq_ImageSingleSet::SetCurrentFrame( int iCurrentFrame ) 
{
   switch( _sSelectMode ) {  
   case PixSingleSetSequence:
   case PixSingleSetFiles:
      _iCurrentFrame = iCurrentFrame;
      break;

   case PixSingleSetNone:
   default:
      _iCurrentFrame = -1;
      break;
   }

   return; 
}

bool pixq_ImageSingleSet::ShiftCurrentFrame( int iShift ) // [i] frame number increment
                                 
{
   bool bRetCode = false;
   int nSize, iNewFrame, iCurrentFrame, iFirstFrame, iLastFrame;   
   pixq_ImgSequence *pSeq = NULL;

   // --- check conditions --- 
   
   switch( _sSelectMode ) {  
   case PixSingleSetSequence:
      iCurrentFrame = getCurrentFrame();
      if( 0 > iCurrentFrame ) {
         goto PIX_EXIT;
      }
      iFirstFrame = pSeq->GetFirstFrame( );
      iLastFrame = pSeq->GetLastFrame( );
      break;

   case PixSingleSetFiles:
      iCurrentFrame = getCurrentFrame();
      if( 0 > iCurrentFrame ) {
         goto PIX_EXIT;
      }
      nSize = (int)_strImgFiles.size( );
      iFirstFrame = 0;
      iLastFrame = nSize - 1;
      break;

   case PixSingleSetNone:
   default:
      goto PIX_EXIT;
      break;
   }

   //

   iNewFrame = iCurrentFrame + iShift;
   if( iFirstFrame > iNewFrame ) {
      iNewFrame = iLastFrame;
   }

   if( iLastFrame < iNewFrame ) {
      iNewFrame = iFirstFrame;
   }

   SetCurrentFrame( iNewFrame );
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}

void pixq_ImageSingleSet::InitFrame( void )
{
   // --- check conditions --- 
   
   switch( _sSelectMode ) {  
   case PixSingleSetSequence:
      _iCurrentFrame = _pImgSequence->GetFirstFrame( );
      break;

   case PixSingleSetFiles:
      _iCurrentFrame = 0;
      break;

   case PixSingleSetNone:
   default:
      goto PIX_EXIT;
      break;
   }

   // --- Done ---
PIX_EXIT:
   return;
}

void pixq_ImageSingleSet::SetImageList( const QStringList strFiles )
{
   int i, nSize;
   QString strFile;

   Deinit( );
   
   nSize = (int)strFiles.size( );
   if( 0 >= nSize ) {
      goto PIX_EXIT;
   }

   _sSelectMode = PixSingleSetFiles;
   _iCurrentFrame = 0;

   _strImgFiles.clear( );
   for( i = 0 ; i < nSize; i++ ) {
      strFile = strFiles.at( i );
      _strImgFiles.push_back( strFile );
   }

   _strImgFiles.sort( );

   // --- Done ---
PIX_EXIT:
   return;
}
