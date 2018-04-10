#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImgSequence.h"

pixq_ImgSequence::pixq_ImgSequence(void)
{
   Init( );
}

pixq_ImgSequence::~pixq_ImgSequence(void)
{
   Init( );
}

//
// initialize all parameters
//
void pixq_ImgSequence::Init( void )
{
   // *** empty file name list ***

   _strImages.clear( );  

   _nImageWidth = -1;
   _nImageHeight = -1;
   _nBitDepth = -1;

   // *** empty all pattern strings ***

   _strPattern.clear( );
   _strExtention.clear( );

   _sFramePattern = FramePatternNone; 
   _iFrameDigit = -1; 

   _iFirstFrame = -1;
   _iLastFrame = -1;

   _iStartFrame = -1;
   _iEndFrame = -1;

   _bSelected = false; 
   _bFrameRange = false; 

   _iSelectionFrame = -1;

   // --- Done ---
   return;
}

//
// check if this file name matches  the image name pattern with frame number
// after file entry name and dot(.) before the frame number
// example IMAGENAME.12345.jpg
//
// returns:
// true or false
//
// notes:
// if this is the pattern, get the frame number from the file
//
static bool CheckPixPatternFrameWithDot( 
      QString  strFile,       // [i] file name
      QString  *szPattern,    // [o] file name pattern with frame number replaced with #
      int      nNumberDigits, // [i] size of the length to frame number
      int      *iFrame )      // [o] frame number
{
   bool bRetCode = false;
   QFileInfo fi;
   QChar szCheck;
   QString szDir, szExt;
   QString szPtnEntry, szNumber, szEntry;
   int iPos, i, nEntryLen;

   // supported number for the width of digits

   if( nNumberDigits < pixq_ImgSequence::MinFrameNumberDigits ) {
      goto PIX_EXIT;
   }
   
   if( nNumberDigits > pixq_ImgSequence::MaxFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   //
   // get file name part in szEntry
   // ex. for file name, szFile = c:\\project\\left\\avatar9876_123456.jpg
   // 
   // drive name, szDrv = "c"
   // directory name, szDir = "\\project\\left\\"
   // file name(entry), szEntry = "avatar9876_123456"
   // extension name, szExt = "jpg"
   //
   fi.setFile( strFile );
   szDir = fi.path( );
   szEntry = fi.completeBaseName( );
   szExt = fi.suffix( );

   //
   // check if this entry name meets the pattern
   //

   nEntryLen = (int)szEntry.size( );
   if( nNumberDigits > nEntryLen ) {
      goto PIX_EXIT;
   }

   // last X-digit must be all number

   for( i = 0 ; i < nNumberDigits ; i++ ) {
      iPos = nEntryLen - nNumberDigits + i;
      szCheck = szEntry.at( iPos );
      if( 0 == szCheck.isDigit( ) ) {
         // not numeric!
         goto PIX_EXIT;
      }
   }

   if( nEntryLen == nNumberDigits ) {
      // file name consists of number only
      // ex. 123456.jpg
      // this is wrong for this type
      goto PIX_EXIT;
   }
   
   // left side of the number part is dot(.)
   // name should look like filename.1234.dpx
   //
   iPos = nEntryLen - nNumberDigits - 1;
   szCheck = szEntry[iPos];
   if( QChar('.') != szCheck ) {
      goto PIX_EXIT;
   }
   
   // --- make pattern ---
   szPtnEntry = szEntry.left(nEntryLen-nNumberDigits);
   szPtnEntry[nEntryLen-nNumberDigits] = '#';

#ifdef _WINDOWS
   *szPattern = szDir + QString("/") + szPtnEntry + QString(".") + szExt;
#else
   *szPattern = szDir + QString("/") + szPtnEntry + QString(".") + szExt;
#endif

   // get frame number 
   szNumber = szEntry.mid(nEntryLen-nNumberDigits, nNumberDigits );
   *iFrame = szNumber.toInt( );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// check if this file name matches  the image name pattern with frame number
// after file entry name without dot(.) before the frame number
// example IMAGENAME12345.jpg
//
// returns:
// true or false
//
// notes:
// if this is the pattern, get the frame number from the file
//
static bool checkPixPatternFrameNoDot( 
      QString strFile,  // [i] file name
      QString *szPattern, // [o] file name pattern with frame number replaced with #
      int nNumberDigits, // [i] size of the length  to frame number
      int *iFrame ) // [o] frame number
{
   bool bRetCode = false;
   QFileInfo fi;
   QChar szCheck;
   QString szDir, szExt;
   QString szPtnEntry, szNumber, szEntry, szFile2;
   int nDirSize, iPos, i, nEntryLen;

   // supported number for the width of digits

   if( nNumberDigits < pixq_ImgSequence::MinFrameNumberDigits ) {
      goto PIX_EXIT;
   }
   
   if( nNumberDigits > pixq_ImgSequence::MaxFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   //
   // get file name part in szEntry
   // ex. for file name, szFile = c:\\project\\left\\avatar9876_123456.jpg
   // 
   // drive name, szDrv = "c"
   // directory name, szDir = "\\project\\left\\"
   // file name(entry), szEntry = "avatar9876_123456"
   // extension name, szExt = "jpg"
   //
   fi.setFile( strFile );
   szDir = fi.path( );
   szEntry = fi.completeBaseName( );
   szExt = fi.suffix( );

   //
   // check if this entry name meets the pattern
   //

   nEntryLen = (int)szEntry.size( );
   if( nNumberDigits > nEntryLen ) {
      goto PIX_EXIT;
   }

   // last X-digit must be all number
   
   for( i = 0 ; i < nNumberDigits ; i++ ) {
      iPos = nEntryLen - nNumberDigits + i;
      szCheck = szEntry.at(iPos);
      if( 0 == szCheck.isDigit( ) ) {
         // not numeric!
         goto PIX_EXIT;
      }
   }

   if( nEntryLen == nNumberDigits ) {
      // file name consists of number only
      // ex. 123456.jpg
      // this is okay
   } else {
      iPos = nEntryLen - nNumberDigits - 1;
      szCheck = szEntry.at(iPos);
      if( 0 != szCheck.isDigit( ) ) {
         // the left side character of the number-part is also numeric!
         goto PIX_EXIT;
      }
   }

   //if( '_' != szEntry[iLen-7] ) {
   //   goto PIX_EXIT;
   //} 
   
   // --- make pattern ---

   szPtnEntry = szEntry.left(nEntryLen-nNumberDigits);
   szPtnEntry[nEntryLen-nNumberDigits] = '#';

   nDirSize = (int)szDir.size( );
   if( 0 >= nDirSize ) {
      goto PIX_EXIT;
   }

   if( '/' == szDir.at( nDirSize-1 ) ) {
      *szPattern = szDir + szPtnEntry + QString(".") + szExt;
   } else {
      *szPattern = szDir + QString("/") + szPtnEntry + QString(".") + szExt;
   }

   // get frame number 
   szNumber = szEntry.mid( nEntryLen-nNumberDigits, nNumberDigits );
   *iFrame = szNumber.toInt( );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// set parameters from command line arguments
 //
bool pixq_ImgSequence::CheckFromArgs( char *szPattern, // [i]
                                     int iFirstFrame, // [i]
                                     int iLastFrame, // [i]
                                     int iFrameDigit, // [i]
                                     short sFramePattern ) // [i]
{
   bool bRetCode = false;
   int iFrame;
   char szFile[FILE_NAME_SIZE];
   QString strPattern;

//fprintf( stdout, "Entered  CheckFromArgs.\n" );
//fprintf( stdout, "szPattern %d....\n", szPattern );

   Init( );
   SetPattern( szPattern );
      
   SetFrameDigit( iFrameDigit );
   SetFirstFrame( iFirstFrame-1 );
   SetLastFrame( iLastFrame-1 );
   SetStartFrame( iFirstFrame-1 );
   SetEndFrame( iLastFrame-1 );
   SetFramePattern( sFramePattern );

   // set image pattern and format
   
   iFrame = GetFirstFrame( );
   if( !NoCheckGetImage( iFrame, szFile ) ) {
      goto PIX_EXIT;
   }
      
   //

   if( !MakeFileList( ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_ImgSequence::SetFrameTemplate( int iFrameDigit, // [i] frame number digit
                                       char *szFrameTemplate ) // [o] frame number template
{
   bool bRetCode = false;

   if( iFrameDigit < MinFrameNumberDigits ) {
      goto PIX_EXIT;
   }
   
   if( iFrameDigit > MaxFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   if( 10 > iFrameDigit ) {
      sprintf( szFrameTemplate, "%%%02dd.\0", iFrameDigit );
   } else {
      sprintf( szFrameTemplate, "%%%03dd.\0", iFrameDigit );
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// CheckPixFileName
// 
// check if the given file name meets one of supported image sequence file name
//
// notes:
// does not check the extension.
// it can be any name. it may not be a valid image.
//
// from real supported image file name, make a image name pattern for Ping's
// analysis programs.
// input image  number must look like "c:\\aaa\\bbb\\XXXXXXX.0077.ext" 
// where "ext" is a valid image extension. for this examples, the output
// image pattern will be "c:\\aaa\\bbb\\XXXXXXX.#.ext"
//
// this function does not check if the input file actually exists.
//
// maximum size of the pattern name should be set to _MAX_PATH(260)
//
bool pixq_ImgSequence::CheckPixFileName( 
      QString  strFile,  // [i] file name
      short    *sPattern, // [o] pattern identifier, one of ImageFramePattern
      int      *iFrameDigit, // [o] frame number digit
      QString  *strPattern, // [o] file name pattern with frame number replaced with #
      int      *iFrame )   // [o] frame number
{
   bool bRetCode = false;
   int k;

   //
   // check all supported image file name patterns
   //

   // X-digit frame number after dot(.)?

#ifdef _DEBUG
   qDebug( ) << "pixq_ImgSequence::CheckPixFileName Entered." << endl;
   qDebug( ) << "... File " << strFile << endl;
#endif

   for( k = MinFrameNumberDigits ; k < MaxFrameNumberDigits ; k++ ) {

      // frame number after dot(.)
      
      if (CheckPixPatternFrameWithDot(strFile, strPattern, k, iFrame)) {
         // sh1234_v01.1234.jpg
         *sPattern = FramePatternFrameAfterDot;
         *iFrameDigit = k;
         bRetCode = true;
         goto PIX_EXIT;
      }   
   
      // frame number with no dot(.)

      if (checkPixPatternFrameNoDot(strFile, strPattern, k, iFrame)) {
         // sh1234_v01_1234.jpg
         *sPattern = FramePatternFrameNoDot;
         *iFrameDigit = k;
         bRetCode = true;
         goto PIX_EXIT;
      }    
   } 

   // did not match any of our supported pattern

   *sPattern = FramePatternNone;
   *iFrameDigit = -1;
   *iFrame = -1;

PIX_EXIT:
#ifdef _DEBUG
   qDebug( ) << "pixq_ImgSequence::CheckPixFileName Leaving...";
   qDebug( ) << "Matched? " << bRetCode;
   qDebug( ) << "sPattern? " << *sPattern;
   qDebug( ) << "iFrameDigit? " << *iFrameDigit;
   qDebug( ) << "iFrame? " << *iFrame;
   qDebug( ) << endl;
#endif
   return bRetCode;
}

//
// get the largest possible frame number
// according to the pattern type
//
// notes:
// returns -1 if pattern is ilegal
//
int pixq_ImgSequence::MaxFrameNumber( int iFrameDigit ) // [i] frame number digit
{  
   int k, nMaxFrame = -1;

   // supported number for the width of digits

   if( iFrameDigit < MinFrameNumberDigits ) {
      goto PIX_EXIT;
   }
   
   if( iFrameDigit > MaxFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   nMaxFrame = 1;
   for( k = 0 ; k < iFrameDigit ; k++ ) {
      nMaxFrame = nMaxFrame * 10;
   }
   nMaxFrame = nMaxFrame - 1; 
  
PIX_EXIT:
   return nMaxFrame;
}

pixq_ImgSequence &pixq_ImgSequence::operator=( const pixq_ImgSequence &that )
{    
   if( this == &that ) {
      goto PIX_EXIT;
   }

   qCopy( that._strImages.begin( ), that._strImages.end( ), _strImages.begin( ) );  

   _nImageWidth     = that._nImageWidth;
   _nImageHeight    = that._nImageHeight;
   _nBitDepth       = that._nBitDepth;

   _strPattern      = that._strPattern;
   _strExtention     = that._strExtention;

   _sFramePattern   = that._sFramePattern;
   _iFrameDigit     = that._iFrameDigit;

   _iFirstFrame     = that._iFirstFrame;
   _iLastFrame      = that._iLastFrame;

   _iStartFrame     = that._iStartFrame;
   _iEndFrame       = that._iEndFrame;

   _bSelected       = that._bSelected;
   _bFrameRange     = that._bFrameRange;
   _iSelectionFrame     = that._iSelectionFrame;
                            
PIX_EXIT:
   return *this;
}

//
// set frame range to view/analyze
//
bool pixq_ImgSequence::SetFrameRange( int iStartFrame, int iEndFrame )
{
   bool bRetCode = false;
   if( _iFirstFrame > iStartFrame ) goto PIX_EXIT;
   if( _iLastFrame < iEndFrame ) goto PIX_EXIT;

   _bFrameRange = true;
   _iStartFrame = iStartFrame;
   _iEndFrame = iEndFrame;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get N-th image entry Name 
//
bool pixq_ImgSequence::GetImageName( int iFrame, // [i] frame number
                                    QString *strName ) // [o] file entry name
{
   bool bRetCode = false;
   QString strFile;
   QFileInfo fi;
  
   if( !GetImageFile( iFrame, &strFile ) ) {
      strName->clear( );
      goto PIX_EXIT;
   }

   fi.setFile( strFile );
   *strName = fi.completeBaseName( );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get position of #. in the image pattern
//
// returns -1 if it dis not in the pattern
//
int pixq_ImgSequence::FrameNumberPosition( void )
{
   QString strPattern;
   int iLoc = -1;

   iLoc = FrameNumberPosition( strPattern );
   
   // --- Done ---
   return iLoc;
}

int pixq_ImgSequence::FrameNumberPosition( QString strPattern )
{
   int iLoc = -1;
   
   // check the pattern string length

   iLoc = strPattern.indexOf( "#" );
   
   // --- Done ---
//PIX_EXIT:
   return iLoc;
}


//
// initialize all parameters and copy 
// important ones from other sequence
//
void pixq_ImgSequence::Init( pixq_ImgSequence *pSrc, // [i] input sequence
                            QString strOutPattern ) // [i] output image template
{
   short sFramePattern;
   int iFrameDigit, iFirstFrame, iLastFrame;
   QString strExt;

   // initialize all parameters once
   Init( );  

   // copy from input parameters

   sFramePattern = pSrc->GetFramePattern( );
   SetFramePattern( sFramePattern ); 

   iFrameDigit = pSrc->GetFrameDigit( );
   SetFrameDigit( iFrameDigit );

   strExt = pSrc->GetExtention( );
   SetExtention( strExt );

   SetPattern( strOutPattern );

   iFirstFrame = pSrc->GetFirstFrame( );
   iLastFrame = pSrc->GetLastFrame( );

   SetFirstFrame( iFirstFrame );
   SetLastFrame( iLastFrame );
   SetStartFrame( iFirstFrame );
   SetEndFrame( iLastFrame );

   SetSelected( false );
   SetFrameRange( true );

   // --- Done ---
   return;
}

//
// check the given file name and set the template, frame pattern and frame range
//

bool pixq_ImgSequence::CheckFromFile( 
      QString strFile,  // [i] file name
      int   *iFrame )   // [o] frame number
{
   short  sPattern;
   int iFrameDigit;
   QString strPattern;
   
   // check the file name and pattern and template
   
   if (!CheckPixFileName(strFile, &sPattern, &iFrameDigit, &strPattern, iFrame)) {
      return false;
   }

   // *** set pattern to the project! ***

   SetPattern( strPattern );
   SetFramePattern( sPattern ); 
   SetFrameDigit( iFrameDigit );

   // if tiff, set depth

   // get frame range 
   SearchFrameRange( );

   return true;
}

bool pixq_ImgSequence::CheckFromFile( QString strFile )  // [i] file name
{
   bool bRetCode = false;
   int iFrame;

   if( !CheckFromFile( strFile, &iFrame ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

// 
// set frame number to the string according to the pattern type
//
// notes:
//
bool pixq_ImgSequence::SetFrameString( short sFramePattern, // [i] frame pattern
                                      int iFrameDigit, // [i] frame number digit
                                      int iFrame,
                                       char *szFrameString ) // [o] frame number template for sprintf
{
   bool bRetCode = false;
   char szFrameTemplate[RECORD_SIZE];

   if( !SetFrameTemplate( iFrameDigit, szFrameTemplate ) ) {
      goto PIX_EXIT;
   }

   sprintf( szFrameString, szFrameTemplate, iFrame );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

// 
// make a sequence of image names by addng a string represeinting a version name 
// at the end of the file entry name.
// for example, if you have ....\sh1234.#.jpg as input sequence
// this function creates a sequence looks like ....\sh1234_v02.#.jpg
// where _v02 is a given version string
// and create a list of all file names 
// 
// returns:
// true or false
//
// notes:
//
bool pixq_ImgSequence::MakeNewVersion( pixq_ImgSequence *pInSeq, // [i] input sequence
                                     string strVersion ) // [i] version string
{
   bool bRetCode = false;
   char szVersion[FILE_NAME_SIZE];
   int nSize;

   nSize = (int)strVersion.size( );
   if( 0 >= nSize ) goto PIX_EXIT;
   if( FILE_NAME_SIZE <= nSize ) goto PIX_EXIT;

   strcpy( szVersion, strVersion.c_str( ) );

   if( !MakeNewVersion( pInSeq, szVersion ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_ImgSequence::MakeNewVersion( pixq_ImgSequence *pInSeq, // [i] input sequence
                                       char *szVersion ) // [i] version string
{
   bool bRetCode = false;
   char *pDest = NULL;
   char szNewPattern[FILE_NAME_SIZE], szTail[FILE_NAME_SIZE];
   char szNumberPattern[FILE_NAME_SIZE], szPattern[FILE_NAME_SIZE], szFramePattern[FILE_NAME_SIZE];
   QString strExt, strPattern;
   short sFramePattern;
   QByteArray buf;
   int iFrameDigit, iLength, iLastFrame, iFirstFrame, nTail, nVersionSize, iLoc;

   // check version string

//fprintf( stdout, "Entered MakeNewVersion....\n" );

   nVersionSize = (int)strlen( szVersion );

//fprintf( stdout, "nVersionSize %d szVersion %s.\n", nVersionSize, szVersion );

   if( 0 >= nVersionSize ) {
      goto PIX_EXIT;
   }
   
   if( FILE_NAME_SIZE <= nVersionSize ) {
      goto PIX_EXIT;
   }

   // get parameters from input sequence

   iFirstFrame = pInSeq->GetFirstFrame( );
   iLastFrame = pInSeq->GetLastFrame( );
   strPattern = pInSeq->GetPattern( );
   sFramePattern = pInSeq->GetFramePattern( );
   iFrameDigit = pInSeq->GetFrameDigit( );
   strExt = pInSeq->GetExtention( );
   
   //buf = strPattern.toAscii( );
   //buf = strPattern.toUtf8();
   buf = strPattern.toLatin1();
   strcpy( szPattern, buf.data( ) );

   iLength = (int)strlen( szPattern );

   // check if there is any file to match the pattern
   
   if (!getFrameStrings(iFrameDigit, szNumberPattern, szFramePattern)) {
      goto PIX_EXIT;
   }

   // generate new image template adding version string at the end of the file entry

   pDest = strstr( szPattern, szFramePattern );
   iLoc = (int)( pDest - szPattern );

   nTail = iLength - iLoc;
   strncpy( szTail, &szPattern[iLoc], nTail );
   szTail[nTail] = '\0';

   switch( sFramePattern ) {
   case FramePatternFrameAfterDot:
      // dot(.) before the frame number -> new vesion string should be 
      // inserted before dot
      strncpy( &szNewPattern[0], szPattern, iLoc-1 );
      szNewPattern[iLoc-1] = '\0';
      strcat( szNewPattern, szVersion );
      szNewPattern[iLoc-1+nVersionSize] = '\0';
      strcat( szNewPattern, "." );
      strcat( szNewPattern, szTail );
      szNewPattern[iLength+nVersionSize] = '\0';
      break;

   case FramePatternFrameNoDot:
      strncpy( &szNewPattern[0], szPattern, iLoc );
      szNewPattern[iLoc] = '\0';
      strcat( &szNewPattern[iLoc], szVersion );
      szNewPattern[iLoc+nVersionSize] = '\0';
      strcat( &szNewPattern[iLoc], szTail );
      szNewPattern[iLength+nVersionSize] = '\0';
      break;
   }

   strPattern = szNewPattern;

   // set parameters for the output sequence and make a list of all image files

   SetFirstFrame( iFirstFrame );
   SetLastFrame( iLastFrame );
   SetPattern( strPattern );
   SetFramePattern( sFramePattern ); 
   SetFrameDigit( iFrameDigit );
   SetExtention( strExt ); 

   if( !MakeFileList( ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// split image pattern to drive, directory, file name and extension parts
//
void pixq_ImgSequence::SplitFilePattern( QString *strDir,  // [o] directory name
                                        QString *strEntry,  // [o] file name
                                        QString *strExt ) // [o] extension name
{
   QFileInfo fi;
   QString strPattern;

   strPattern = GetPattern( );
   fi.setFile( strPattern );
   
   *strDir = fi.path( );
   *strEntry = fi.completeBaseName( );
   *strExt = fi.suffix( );

   return;
}

//
// from the current image sequence
// and new version string, create new image name template
//
// notes:
// image name extention is taken from this sequence
//
bool pixq_ImgSequence::FormOutputNewVersion( 
   QString strOutPath, // [i] output path
   QString strVersion, // [i] new output version name
   QString *strOutPattern ) // [o] output file name template
{
   bool bRetCode = false;
   QString strOutEntry, strDir, strInEntry, strExt;

   // find the position of #. in the input file name part

   SplitFilePattern( &strDir, &strInEntry, &strExt );

   if( !FormOutputNewVersion( strOutPath, strVersion, strExt, strOutPattern ) ) {
      goto PIX_EXIT;
   }
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// from the current image sequence
// and new version string, create new image name template
//
// notes:
// image name extention is specified in the argument
//
bool pixq_ImgSequence::FormOutputNewVersion( 
   QString strOutPath, // [i] output path
   QString strVersion, // [i] new output version name
   QString strExt, // [i] new output version name
   QString *strOutPattern ) // [o] output file name template
{
   bool bRetCode = false;
   short sFramePattern = GetFramePattern( );
   int nPathSize, iLoc;
   QString strNewExt, strOutEntry, strDir, strInEntry;

   // find the position of #. in the input file name part

   SplitFilePattern( &strDir, &strInEntry, &strExt );
   iLoc = FrameNumberPosition( strInEntry );
   if( 0 > iLoc ) {
      goto PIX_EXIT;
   }

   // create file entry name strings
   
   switch( sFramePattern ) {
   case FramePatternFrameNoDot:       
      strOutEntry = strInEntry.left( iLoc );
      strOutEntry = strOutEntry + strVersion;
      break;

   case FramePatternFrameAfterDot:  
      strOutEntry = strInEntry.left( iLoc-1 );
      strOutEntry = strOutEntry + strVersion + QString( "." );
      break;
   }

   strOutEntry.append( "#\0" );
   *strOutPattern = strOutPath;
   
   nPathSize = (int)strOutPath.size( );
   if( 0 >= nPathSize ) {
      goto PIX_EXIT;
   }

   if( '/' != strOutPath.at( nPathSize-1 ) ) {
      *strOutPattern = *strOutPattern + QString( "/" );
   }
   
   // get specified extentsion

   *strOutPattern = *strOutPattern + strOutEntry + QString( "." ) + strExt;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// decide frame number from the file
//
// returns:
// frame number
// -1: file name does not match the pattern 
//
int pixq_ImgSequence::GetFrameNumber( QString szFile )
{
   int iFrame = -1;
   QFileInfo fi;
   QString szNumber, szEntry;
   int iFramePos, iFrameDigit, nEntryLen;

   iFrameDigit = _iFrameDigit;

   //
   // get file name part in szEntry
   // ex. for file name, szFile = c:\\project\\left\\avatar9876_123456.jpg
   // 
   // drive name, szDrv = "c"
   // directory name, szDir = "\\project\\left\\"
   // file name(entry), szEntry = "avatar9876_123456"
   // extension name, szExt = "jpg"
   //
   fi.setFile( szFile );
   szEntry = fi.completeBaseName( );

   //
   // check if this entry name meets the pattern
   //

   nEntryLen = (int)szEntry.size( );
   if( iFrameDigit > nEntryLen ) {
      goto PIX_EXIT;
   }

   if( iFrameDigit > nEntryLen ) {
      goto PIX_EXIT;
   }

   iFramePos = nEntryLen - iFrameDigit;

   // get frame number 
   szNumber = szEntry.mid( iFramePos, iFrameDigit );
   iFrame = szNumber.toInt( );

   // --- Done ---
PIX_EXIT:
   return iFrame;
}

// 
// get template string for frame number parts
// according to the pattern type
//
// notes:
//
bool pixq_ImgSequence::getFrameStrings(short sFramePattern, // [i] frame pattern
                                       int iFrameDigit, // [i] frame number digit
                                       QString *szNumberPattern, // [o] frame number pattern for _stprintf
                                       QString *szFramePattern ) // [o] frame number pattern in the template
{
   bool bRetCode = false;
   int k;
   // supported number for the width of digits

   if( iFrameDigit < MinFrameNumberDigits ) {
      goto PIX_EXIT;
   }
   
   if( iFrameDigit > MaxFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   switch( sFramePattern ) {

   case FramePatternFrameNoDot: 
   case FramePatternFrameAfterDot:
      break;
   
   default:
      goto PIX_EXIT;
   }

   // frame number strings

   //_tcscpy( szFramePattern, _T("#.\0") );
   *szFramePattern = QString("#.\0");

   //_tcscpy( szNumberPattern, _T("\0") );
   *szNumberPattern = QString("\0");

   for( k = 0 ; k < iFrameDigit ; k++ ) {
      //_tcscat( szNumberPattern, _T("?") );
      szNumberPattern->append("?");
   }

   //_tcscat( szNumberPattern, _T(".\0") );
   szNumberPattern->append(".\0");

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_ImgSequence::getFrameStrings(int iFrameDigit, // [i] frame number digit
                                       char *szNumberPattern, // [o] frame number pattern for sprintf
                                       char *szFramePattern ) // [o] frame number pattern in the template
{
   bool bRetCode = false;
   int k;
   // supported number for the width of digits

   if( iFrameDigit < MinFrameNumberDigits ) {
      goto PIX_EXIT;
   }
   
   if( iFrameDigit > MaxFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   // frame number strings

   strcpy( szFramePattern, "#.\0" );

   strcpy( szNumberPattern, "\0" );
   for( k = 0 ; k < iFrameDigit ; k++ ) {
      strcat( szNumberPattern, "?" );
   }
   strcat( szNumberPattern, ".\0" );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// generate search strings for findfile struct
//
bool pixq_ImgSequence::GetFindFileSearchPattern( QString *szPattern ) // [o] pattern strings
{
   bool bRetCode = false;
   QString szFrameTemplate;
   QString szFramePattern;
   QString strPattern, strImage;
   short sFramePattern;
   int  nFrameFormatSize, nFiles, iFrameDigit;
   int iPos;

#ifdef _DEBUG
   qDebug( ) << "GetFindFileSearchPattern entered!";
   qDebug( ) << "_strPattern=" << _strPattern;
   qDebug( ) << "_sFramePattern=" << _sFramePattern;
   qDebug( ) << "_iFrameDigit=" << _iFrameDigit;
#endif

   if( _strPattern.isEmpty( ) ) {
      goto PIX_EXIT;
   }

   // check if there is any file to match the pattern

   strPattern = _strPattern;
   sFramePattern = _sFramePattern;
   iFrameDigit = _iFrameDigit;

   if (!getFrameStrings(sFramePattern, iFrameDigit, &szFrameTemplate, &szFramePattern)) {
      // unrecognized pattern!
      goto PIX_EXIT;
   }

#ifdef _DEBUG
   qDebug( ) << "szFrameTemplate returned " << szFrameTemplate;
   qDebug( ) << "szFramePattern returned " << szFramePattern;
#endif

#ifdef _DEBUG
   qDebug( ) << "strPattern=" << strPattern;
#endif

   iPos = strPattern.indexOf( szFramePattern );

#ifdef _DEBUG
   qDebug( ) << "strPattern=" << strPattern;
#endif

#ifdef _DEBUG
   qDebug( ) << "strPattern=" << strPattern;
   qDebug( ) << "iPos=" << iPos;
#endif

   //iPos = strPattern.find( szFramePattern );
   //if( iPos == QString::npos ) {
   if( 0 > iPos ) {
      nFiles = -1;
      goto PIX_EXIT;
   }

   nFrameFormatSize = (int)szFramePattern.size( ); // length of above frame pattern string
     
   // generate search string for FindFile in szPattern
   // e.g., c:\\projects\\left\sh1234.????.jpg

   strImage = strPattern;
   strImage.replace( iPos, nFrameFormatSize, szFrameTemplate );
   
   *szPattern = strImage;
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get directory for the pattern
//
bool pixq_ImgSequence::GetDriveDir( QString *szDir ) // [o] directory
{
   bool bRetCode = false;
   int nFrameFormatSize, iPos;
   QFileInfo fi;
   QString szExt, szFramePattern, szEntry;
   QString strPattern, strImage;

   if( _strPattern.isEmpty( ) ) {
      goto PIX_EXIT;
   }

   // create pseudo file name for frame 1

   //_tcscpy( szFramePattern, _T("#.\0") );
   szFramePattern = QString("#.\0");

   strPattern = _strPattern;
   //iPos = strPattern.find( szFramePattern );
   iPos = strPattern.indexOf( szFramePattern );
   nFrameFormatSize = (int)szFramePattern.size( ); // length of above frame pattern string

   if( 0 > iPos ) {
      goto PIX_EXIT;
   }

   strImage = strPattern;
   strImage.replace( iPos, nFrameFormatSize, QString("1") );

   // get drive and directory

   fi.setFile( strImage );
   *szDir = fi.path( );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

// 
// search the directory and decide the first and the last frame for the version
// get the first and last frame number to match this file name pattern and set them to the following 
// member variablesm respectively:
// _iFirstFrame
// _iLastFrame
// 
// returns:
// number of files to match this pattern
//
// notes:
// frame file names are created and set in the list regardless of it actually exists or not
// actual range of existing frames are set in _iFirstFrame and _iLastFrame
//
// follwoing member variables must be set before running this function:
// _strPattern
//
// only works on windows
//
int pixq_ImgSequence::SearchFrameRange( void )
{
   int i, iFrame, k, iLastFrame, iFirstFrame, nFiles;
   QFile file;
   QFileInfo fi;
   QDir currentDir;
   QStringList files;
   QString szFile, szPattern, szFullPattern, szDir;

#ifdef _DEBUG
   qDebug( ) << "SearchFrameRange Entered with " << _strPattern;
#endif

   if( _strPattern.isEmpty( ) ) {
      _iFirstFrame = -1;
      _iLastFrame = -1;
      goto PIX_EXIT;
   }
    
   // generate search string for FindFile in szPattern
   // e.g., c:\\projects\\left\sh1234.????.jpg

   if( !GetFindFileSearchPattern( &szFullPattern ) ) {
      _iFirstFrame = -1;
      _iLastFrame = -1;
#ifdef _DEBUG
   qDebug( ) << "GetFindFileSearchPattern Failed!";
#endif
      goto PIX_EXIT;
   }

#ifdef _DEBUG
   qDebug( ) << "GetFindFileSearchPattern returned " << szFullPattern;
#endif

   fi.setFile( szFullPattern );
   szDir = fi.path( );
   szPattern = fi.fileName( );

   // *** start to search the file ***

   currentDir = QDir( szDir );
   files = currentDir.entryList( QStringList( szPattern ), 
      QDir::Files | QDir::NoSymLinks );

   nFiles = (int)files.size( ); 
   if( 0 >= nFiles ) {
      _iFirstFrame = -1;
      _iLastFrame = -1;
      goto PIX_EXIT;
   }
   
   for ( i = 0; i < nFiles ; i++ ) {
      file.setFileName( currentDir.absoluteFilePath( files[i] ) );
      szFile = file.fileName( ); 
      files.replace( i, szFile );   
    }

   szFile = files.at( 0 );
   iFrame = GetFrameNumber( szFile );
   iFrame = iFrame - 1;
   iFirstFrame = iFrame;
   iLastFrame = iFrame;

   // analyze frame range

   for( k = 1 ; k < nFiles ; k++ ) {
      szFile = files.at( k );
      iFrame = GetFrameNumber( szFile );
      iFrame = iFrame - 1;
      iFirstFrame = min( iFirstFrame, iFrame );
      iLastFrame = max( iLastFrame, iFrame );
   }

   _iFirstFrame = iFirstFrame;
   _iLastFrame = iLastFrame;

   // --- Done ---
PIX_EXIT:
   return nFiles;
}

QString pixq_ImgSequence::GetPatternName( void )
{
   QString strPatternType;
   
   strPatternType = pixq_ImgSequence::GetPatternName( _sFramePattern, _iFrameDigit );

   return strPatternType;
}

QString pixq_ImgSequence::GetPatternName( short sPattern, int iFrameDigit )
{
   QString strPatternType;

   switch( sPattern ) {

   case pixq_ImgSequence::FramePatternFrameNoDot: 
      strPatternType.sprintf( "%d-Digit Frame Number without Dot(.)", iFrameDigit );
      break;

   case pixq_ImgSequence::FramePatternFrameAfterDot:
      strPatternType.sprintf( "%d-Digit Frame Number with Dot(.)", iFrameDigit );
      break;

   case pixq_ImgSequence::FramePatternNone:
   default:
      strPatternType = QString("Unknown Pattern");
      break;
   } 

   return strPatternType;
}

void pixq_ImgSequence::GetPatternName( QString *szPattern ) // [o] pattern type in strings
{
   QString strPatternType;

   switch( _sFramePattern ) {

   case pixq_ImgSequence::FramePatternFrameNoDot: 
      szPattern->sprintf( "%d-Digit Frame Number without Dot(.)", _iFrameDigit );
      break;

   case pixq_ImgSequence::FramePatternFrameAfterDot:
      szPattern->sprintf( "%d-Digit Frame Number with Dot(.)", _iFrameDigit );
      break;

   case pixq_ImgSequence::FramePatternNone:
   default:
      *szPattern = QString("Unknown Pattern");
      break;
   } 

   return;
}

//
// make a list of frame files from pattern name and frame range
//
// notes:
// does not check if these files actually exist.
//
bool pixq_ImgSequence::MakeFileList( void ) // [o] list of files to match the patter
{
   bool bRetCode = false;
   QString szFile;
   int i, nFiles, iFrame;

   _bSelected = false; 
   if( _strPattern.isEmpty( ) ) {
      goto PIX_EXIT;
   }

   // *** check frame range ***

   //if( 0 > _iFirstFrame ) goto PIX_EXIT;
   
   if( -1 > _iFirstFrame ) {
      goto PIX_EXIT;
   }
   
   if( 0 > _iLastFrame ) {
      goto PIX_EXIT;
   }

   // --- make a list of first images ---
   
   _strImages.clear( );

   nFiles = _iLastFrame - _iFirstFrame + 1;
   for( i = 1 ; i <= nFiles ; i++ ) {
      
      iFrame = i + _iFirstFrame;

      if( !SetImageName( _strPattern, _sFramePattern, _iFrameDigit, iFrame, &szFile ) ) {
         goto PIX_EXIT;
      }

      _strImages.push_back( szFile );
   }

   // sort file list

   _strImages.sort( );

   // set parameters
   _bSelected = true; 

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// make image file name from pattern and frame number 
//
bool pixq_ImgSequence::SetImageName( QString strPattern, // [i] 
                                    short sFramePattern,  // [i] one of ImageFramePattern
                                    int iFrameDigit,
                                    int iFrame, // [i] frame number
                                    QString *szFile ) // [o] image file name for the frame
const
{
   bool bRetCode = false;
   QString strFile, szNumber;
   QString szFramePattern;
   QString szNumberPattern;
   char szFrameFormat[RECORD_SIZE];

   int nFramePatternSize, nFrameFormatSize, nMinLength, iMinFrame, nMaxFrame, iLoc;
   int iLength = (int)strPattern.size( );

   // check conditions

   if (!getFrameStrings(sFramePattern, iFrameDigit, &szNumberPattern, &szFramePattern)) {
      // unrecognized pattern!
      goto PIX_EXIT;
   }

   // supported number for the width of digits

   if( iFrameDigit < MinFrameNumberDigits ) {
      goto PIX_EXIT;
   }
   
   if( iFrameDigit > MaxFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   switch( sFramePattern ) {
   case FramePatternFrameNoDot:
      nMinLength = iFrameDigit;
      iMinFrame = 0;
      nFramePatternSize = 2; // width of "#."
      //_tcscpy( szFrameFormat, _T("%04d.\0") );
      if( !SetFrameTemplate( iFrameDigit, szFrameFormat ) ) {
         goto PIX_EXIT;
      }
      nFrameFormatSize = nMinLength+1;
      break;

   case FramePatternFrameAfterDot:
      nMinLength = iFrameDigit;
      iMinFrame = 0;
      nFramePatternSize = 2; // width of "#."
      if( !SetFrameTemplate( iFrameDigit, szFrameFormat ) ) {
         goto PIX_EXIT;
      }
      nFrameFormatSize = nMinLength+1;
      break;
   
   case FramePatternNone:
   default:
      // unrecognized pattern!
      goto PIX_EXIT;
      break;
   }

   nMaxFrame = MaxFrameNumber( iFrameDigit );

   // check the pattern string length
   iLength = (int)strPattern.size( );
   if( nMinLength > iLength ) {
      goto PIX_EXIT;
   }

   // check frame range
   if( iMinFrame > iFrame || nMaxFrame < iFrame ) {
      goto PIX_EXIT;
   }

   iLoc = strPattern.indexOf( szFramePattern );
   szNumber.sprintf( szFrameFormat, iFrame );

   strFile = strPattern.left( iLoc );
   strFile.append( szNumber );
   strFile.append( strPattern.mid( iLoc+nFramePatternSize, iLength - iLoc - nFramePatternSize ) );
   
   *szFile = strFile;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
                                    
//
// returns number of frames
//
int pixq_ImgSequence::FrameCount( void ) 
{
   return (int)_strImages.size( ); 
}

//
// initialize frame range to view/analyze
//
void pixq_ImgSequence::InitFrameRange( void )
{
   _bFrameRange = false;
   _iStartFrame = _iFirstFrame;
   _iEndFrame = _iLastFrame;
}

//
// get image size of the shot from the first frame
//
bool pixq_ImgSequence::GetImageSize( void )
{
   bool bRetCode = false;
   QString strFile;
   int nImgWidth, nImgHeight, nBitDepth;

   if( 0 < _nImageWidth ) {
      bRetCode = true;
      goto PIX_EXIT;
   }

   // --- get image resolution from the first image ---  
   // --- and set it to the entire shot data --- 

   if( !GetImageFile( _iFirstFrame, &strFile ) ) {
      goto PIX_EXIT;
   }

   if (!getHeaderInfo_PI(strFile, nImgWidth, nImgHeight, nBitDepth)) {
      goto PIX_EXIT;
   }

   _nImageWidth = nImgWidth;
   _nImageHeight = nImgHeight;
   _nBitDepth = nBitDepth;
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}     


//
// get n-th image file
//
// returns:
// n-th image file name in full
//
// notes:
// return empty string if the version is not selected
//
QString pixq_ImgSequence::GetImage( int iFrame ) // [i] frame number
{ 
   QString strFile;
   
   if( !GetImageFile( iFrame, &strFile ) ) {
      strFile.clear( );
   }

   return strFile;
}

//
// get n-th image file
//
// notes:
// return empty string if the version is not selected
//
bool pixq_ImgSequence::GetImageFile( int iFrame, // [i] frame number
                                QString *strFile )
{
   bool bRetCode = false;
   int iPos;
   
   if( !CheckFrame( iFrame ) ) {
      strFile->clear( );
      goto PIX_EXIT;
   }
     
   iPos = iFrame - _iFirstFrame;
   *strFile = _strImages.at( iPos );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_ImgSequence::GetImageFile( int iFrame, // [i] frame number
                                char *szFile )
{
   bool bRetCode = false;
   QByteArray buf;
   QString strFile;
   
   if( !GetImageFile( iFrame, &strFile ) ) {
      goto PIX_EXIT;
   }
   
   //buf = strFile.toAscii( );
   //buf = strFile.toLatin1();
   buf = strFile.toUtf8();
   strcpy( szFile, buf.data( ) );
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// get n-th image file without checking frame range
//
// notes:
//
bool pixq_ImgSequence::NoCheckGetImage( int iFrame, // [i] frame number
                                       QString *strFile ) const
{
   bool bRetCode = false;
     
   if( !SetImageName( _strPattern, _sFramePattern, _iFrameDigit,
      iFrame+1, strFile ) ) {
         goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_ImgSequence::NoCheckGetImage( int iFrame, // [i] frame number
                                       char *szFile )
{
   bool bRetCode = false;
   QByteArray buf;
   QString strFile;
     
   if( !NoCheckGetImage( iFrame, &strFile ) ) {
      goto PIX_EXIT;
   }
   
   //buf = strFile.toAscii( );
   //buf = strFile.toLatin1();
   buf = strFile.toUtf8();
   strcpy( szFile, buf.data( ) );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

// 
// check if the frame number is valid
// 
bool pixq_ImgSequence::CheckFrame( int iFrame )
const
{
   bool bRetCode = false;
   int nFiles, iPos;

   // --- check current frame number --- 

   if( _iFirstFrame > iFrame ) goto PIX_EXIT;
   if( iFrame > _iLastFrame ) goto PIX_EXIT;
   
   nFiles = (int)_strImages.size( );
   if( 0 >= nFiles ) goto PIX_EXIT;
  
   iPos = iFrame - _iFirstFrame;
   if( iPos >= nFiles ) goto PIX_EXIT;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:   
   return bRetCode;
}

//
// returns true if this sequence has been initialized and is valid
// this is judged by having valid _sFramePattern member
//
// notes:
// _sFramePattern is initialized to FramePatternNone
// and set to some value when sequence is loaded
//
bool pixq_ImgSequence::Valid( void )
{
   bool bRetCode = false;

   switch( _sFramePattern ) {
   case FramePatternNone:
      goto PIX_EXIT;
      break;
   
   case FramePatternFrameNoDot: 
   case FramePatternFrameAfterDot:
   default:
      break;
   }

   if( _iFrameDigit < MinFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   if( _iFrameDigit > MaxFrameNumberDigits ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// return the path
//
bool pixq_ImgSequence::GetImagePath( char *szPath ) // [o]
{
   bool bRetCode = false;
   int iFirstFrame = GetFirstFrame( );
   QFileInfo fi;
   QByteArray buf;
   QString strDir, strFile;

   if( !GetImageFile( iFirstFrame, &strFile ) ) { 
      goto PIX_EXIT;
   }
   
   fi.setFile( strFile );
   strDir = fi.path( );
   
   //buf = strDir.toAscii( );
   //buf = strDir.toLatin1();
   buf = strDir.toUtf8();
   strcpy( szPath, buf.data( ) );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// copy a list of file names to stl vector
//
// notes:
// 
bool pixq_ImgSequence::FileNameVector( vector<string> *vstrFile,
                                      int iFirstFrame,
                                      int iLastFrame ) const
{
   bool bRetCode = false;
   int i;
   string strName;
   QString strFile;

   vstrFile->resize( iLastFrame + 1 );

   strName.clear( );
   for( i = 0 ; i < iFirstFrame ; i++ ) {
      vstrFile->at( i ) = strName;
   }

   for( i = iFirstFrame ; i <= iLastFrame ; i++ ) {
      
      if( 0 > i ) continue;
      
      if( !NoCheckGetImage( i, &strFile ) ) {
         goto PIX_EXIT;
      }

#ifdef WIN32
      // on Windows, change delimiter from / to \\
      // to make it compatible with Windows standard
      // and PathInfo class
      strFile.replace( QChar('/'), QChar('\\'), Qt::CaseInsensitive );
#endif // WIN32
      
      //QByteArray file = strFile.toLatin1();
      //QByteArray file = strFile.toAscii( );
      QByteArray file = strFile.toUtf8( );
      const char *szFile = file.data( );

      vstrFile->at( i ) = szFile;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


bool pixq_ImgSequence::FileNameVector( vector<string> *vstrFile ) const
{
   bool bRetCode = false;
   int iFirstFrame = GetFirstFrame( );
   int iLastFrame = GetLastFrame( );

   if( 0 > iFirstFrame ) goto PIX_EXIT;
   if( 0 > iLastFrame ) goto PIX_EXIT;

   if( !FileNameVector( vstrFile, iFirstFrame, iLastFrame ) ) {
      goto PIX_EXIT;
   }
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

