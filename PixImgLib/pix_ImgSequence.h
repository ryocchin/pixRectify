//
// pixq_ImgSequence
// image sequence handling
//
#pragma once

namespace _pix_plot_img_framework {
  
#include <piximglib_global.h>

class PIXIMGLIB_EXPORT pixq_ImgSequence
{
public:
   // file name pattern format
   // when new pattern is added, 
   // following related functions have to be modfied:
   //
   // ...CheckPixFileName
   // ...SetImageName
   // ...getFrameStrings
   // ...MaxFrameNumber
   // ...SetFrameString
   //
   enum {
      FramePatternNone = 0,
      // X-digit frame number at the end of file entry name, no dot before frame number
      // XXXXXXXXX????.ext
      FramePatternFrameNoDot = 1,
      //
      // X-digit frame number after the file entry name and dot(.)
      // XXXXXXXXX.????.ext
      FramePatternFrameAfterDot = 2,
      //
   } ImageFramePattern;

   enum {
      // minimum number of the frame number digits
      MinFrameNumberDigits = 2,
      // max number of the frame number digits
      MaxFrameNumberDigits = 12,
   } FrameNumberDigitRange;

public:
   pixq_ImgSequence(void);
   ~pixq_ImgSequence(void);

   pixq_ImgSequence &operator=( const pixq_ImgSequence &that );

protected:
   // list of all files in the selected version 

   QStringList _strImages;
   //QVector<QString> _strImages;

   // image dimensions
   // set in GetImageSize from the first image in the sequence
   int _nImageWidth;
   int _nImageHeight;

   // depth per pixel, 1/2/4/8/16
   int _nBitDepth;

private:      
   // version strings 
   QString _strPattern;

   // image extention 
   // must be something supported by ImageMagick
   QString _strExtention;

   // image frame name pattern type, one of ImageFramePattern
   short _sFramePattern;

   // frame number digits, between range in FrameNumberDigitRange
   int _iFrameDigit;

   // data frame range, this is the first and last frame number to match the pattern
   int _iFirstFrame;
   int _iLastFrame;

   // frame range for play back/analysis
   // this is left for the user's decision
   int _iStartFrame;
   int _iEndFrame;

   // if valid image version is selected
   bool _bSelected;

   // frame range selected by user?
   bool _bFrameRange;

   // frame number used when the file in the sequence is selected by user
   // if any
   int _iSelectionFrame;

public:  
   // initialize all parameters   
   void Init( void );

   // set frame range to view/analyze
   bool SetFrameRange( int iStartFrame, int iEndFrame );

   // get position of #. in the image pattern
   int FrameNumberPosition( void );
   int FrameNumberPosition( QString strPattern );

   // initialize all parameters and copy 
   // important ones from other sequence
   void Init( pixq_ImgSequence *pSrc, QString strOutPattern );

   // make a sequence of image names by addng a string represeinting a version name 
   // at the end of the file entry name.
   // for example, if you have ....\sh1234.#.jpg as input sequence
   // this function creates a sequence looks like ....\sh1234_v02.#.jpg
   bool MakeNewVersion( pixq_ImgSequence *pInSeq, string strVersion );
   bool MakeNewVersion( pixq_ImgSequence *pInSeq, char *szVersion );

   // set frame number to the string according to the pattern type
   static bool SetFrameString( short sFramePattern, int iFrameDigit, 
      int iFrame, char *szFrameString );

   // check the given file name and set the template, frame pattern and frame range

   bool CheckFromFile( QString strFile, int *iFrame );
   bool CheckFromFile( QString strFile );


   // split image pattern to drive, directory, file name and extension parts

   void SplitFilePattern( QString *strDir, QString *strEntry, QString *strExt );

   bool FormOutputNewVersion( QString strOutPath, QString strVersion,
      QString *strOutPattern );

   bool FormOutputNewVersion( QString strOutPath, QString strVersion,
      QString strExt, QString *strOutPattern );

   // *******************
   // *** data access ***
   // *******************

   int GetBitDepth( void ) { return _nBitDepth; }
   void SetBitDepth( int nBitDepth ) { _nBitDepth = nBitDepth; }
   
   bool getSelected(void) { return _bSelected; }
   void SetSelected( bool bSelected ) { _bSelected = bSelected; }
   
   bool GetFrameRange( void ) {return _bFrameRange; }
   void SetFrameRange( bool bFrameRange ) { _bFrameRange = bFrameRange; }

   // get N-th image's entry Name 
   bool GetImageName( int iFrame, QString *strName );

   // returns true if this sequence has been initialized and is valid
   // this is judged by having valid _sFramePattern member
   bool Valid( void );

   // *******************
   // *** data access ***
   // *******************

public:  
   int GetStartFrame( void ) { return _iStartFrame; }
   int GetEndFrame( void ) { return _iEndFrame; }
   void SetStartFrame( int iStartFrame ) { _iStartFrame = iStartFrame; }
   void SetEndFrame( int iEndFrame ) { _iEndFrame = iEndFrame; }

   short GetFramePattern( void ) { return _sFramePattern; }
   void SetFramePattern( short sPattern ) { _sFramePattern = sPattern; }

   int GetFrameDigit( void ) { return _iFrameDigit; }
   void SetFrameDigit( int iFrameDigit ) { _iFrameDigit = iFrameDigit; }

   int GetSelectionFrame( void ) { return _iSelectionFrame; }
   void SetSelectionFrame( int iSelectionFrame ) { _iSelectionFrame = iSelectionFrame; }

   // search the directory and decide the first and the last frame for the version
   // then make a list of frame files

   int SearchFrameRange( void );

   // generate search strings for findfile struct
   bool GetFindFileSearchPattern( QString *szPattern );

   // get template string for frame number parts
   // according to the pattern type
   static bool getFrameStrings(short sFramePattern, int iFrameDigit, QString *szPattern,
      QString *szFramePattern );

   static bool getFrameStrings(int iFrameDigit, char *szPattern, char *szFramePattern);

   // get drive and directory for the pattern

   bool GetDriveDir( QString *szDir );

   // return the path
   bool GetImagePath( char *szPath );

   // decide frame number from the file
   int GetFrameNumber( QString szFile );

   // returns name to indicate pattern name
   QString GetPatternName( void );
   static QString GetPatternName( short sPattern, int iFrameDigit );
   void GetPatternName( QString *szPattern );

   int GetFirstFrame( void ) const { return _iFirstFrame; } 
   int GetLastFrame( void ) const { return _iLastFrame; } 

   void SetFirstFrame( int iFirstFrame ) { _iFirstFrame = iFirstFrame; }
   void SetLastFrame( int iLastFrame ) { _iLastFrame = iLastFrame; }

   // make a list of file names
   bool MakeFileList( void );

   // make image file name from pattern and frame number 
   bool SetImageName( QString strPattern, short sFramePattern, int iFrameDigit,
      int iFrame, QString *szFile ) const;

   static bool SetFrameTemplate( int iFrameDigit, char *szFrameTemplate );

   // get the largest possible frame number according to the pattern type
   static int MaxFrameNumber( int iFrameDigit );

   // returns number of frames 
   int FrameCount( void );

   QString GetPattern(void) const { return _strPattern; }
   void SetPattern( QString strPattern ) { _strPattern = strPattern; }

   QString GetExtention(void)const  { return _strExtention; }
   void SetExtention( QString strExtention ) { _strExtention = strExtention; }

   // initialize frame range to view/analyze

   void InitFrameRange( void );

   int getImageWidth(void) const { return _nImageWidth; }
   void SetImageWidth( int nImageWidth ) { _nImageWidth = nImageWidth; }

   int getImageHeight(void) const { return _nImageHeight; }
   void SetImageHeight( int nImageHeight ) { _nImageHeight = nImageHeight; }

   // get and set image dimension of the shot from the first frame

   bool GetImageSize( void );  

   static bool CheckPixFileName(QString strFile, short *sPattern, int *iFrameDigit,
      QString *strPattern, int *iFrame );

   bool CheckFromArgs( char *szPattern, int iFirstFrame, int iLastFrame, 
      int iFrameDigit, short sFramePattern );

   // get N-th File Name 
   QString GetImage( int i );

   bool GetImageFile( int iFrame, QString *strFile );
   bool GetImageFile( int iFrame, char *szFile );

   // get N-th File Name without checking frame range
   bool NoCheckGetImage( int iFrame, QString *strFile ) const;
   bool NoCheckGetImage( int iFrame, char *szFile );

   // check if the frame number is valid
   bool CheckFrame( int iFrame ) const;  

   // make a list of file in vector
   bool FileNameVector( vector<string> *vstrFile ) const;
   bool FileNameVector( vector<string> *vstrFile, int iFirstFrame,
      int iLastFrame ) const;

};

} // namespace _pix_plot_img_framework
