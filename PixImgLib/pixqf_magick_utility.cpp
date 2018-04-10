#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

//
// make a list of supporrted image formats by ImageMagick
//
// notes:
// make a list of explanation for each format
// exttention( desciption), redable, writable, multiframe
//
void listSupportedFormat_PI(QStringList *strList)
{
   QString strFormat;
   QStringList strFormats;
   QStringList strDesc;
   QList<bool> bReadble; 
   QList<bool> bWritable;
   QList<bool> bMultiFrame;
   int k, nFormats;

   // make a list
   
   listSupportedFormat_PI(&strFormats, &strDesc, &bReadble, &bWritable,
      &bMultiFrame );
   nFormats = (int)strFormats.size( );

   strList->clear( );
   for( k = 0 ; k < nFormats ; k++ ) {
      strFormat = strFormats.at( k );
      strFormat = strFormat + "(" + strDesc.at( k ) + ")";
      strFormat = strFormat + " : ";
      strFormat = strFormat + "Read=" + ( bReadble.at( k ) ? 'Y' : 'N' );
      strFormat = strFormat + ", ";
      strFormat = strFormat + "Write=" + ( bWritable.at( k ) ? 'Y' : 'N' );
      strFormat = strFormat + ", ";
      strFormat = strFormat + "MultiFrame=" + ( bMultiFrame.at( k ) ? 'Y' : 'N' );

      strList->push_back( strFormat );
   }

   return;
}

void listSupportedFormat_PI(QStringList *strFormats, // [o] format names
                            QStringList *strDesc, // [o] format description
                            QList<bool> *bReadble, // [o] readbale? for each format
                            QList<bool> *bWritable, // [o] writable? for each format
                            QList<bool> *bMultiFrame ) // [o] multiframe? for each format
{
   QString strFormat;
   
   CoderInfo::MatchType isReadable;
   CoderInfo::MatchType isWritable;
   CoderInfo::MatchType isMultiFrame;

   //
   
   isReadable = CoderInfo::AnyMatch;
   isWritable = CoderInfo::AnyMatch; 
   //isReadable = CoderInfo::TrueMatch;
   //isWritable = CoderInfo::TrueMatch;
   isMultiFrame = CoderInfo::AnyMatch; // Don't care about multi-frame support

   std::list<CoderInfo> coderList;
   try {
      coderInfoList( &coderList, isReadable, isWritable, isMultiFrame ); 
   }

   catch( Exception e ) {
      e.what( );
   };

   // make a list
   
   strFormats->clear( );
   strDesc->clear( );
   bReadble->clear( );
   bWritable->clear( );
   bMultiFrame->clear( );

   list<CoderInfo>::iterator entry = coderList.begin();
   while( entry != coderList.end( ) ) {
      strFormats->push_back( entry->name( ).c_str( ) );
      strDesc->push_back( entry->description( ).c_str( ) );
      bReadble->push_back( entry->isReadable( ) ? true : false );
      bWritable->push_back( entry->isWritable( ) ? true : false );
      bMultiFrame->push_back( entry->isWritable( ) ? true : false );
      
      entry++;
   }

   return;
}

//
// make filter string for QFileDialog to get supported image files 
// string.
//
// Returns:
// nothing
//
void imageMagickFileFilter_PI(bool bRead, // [i] true for read, false for write
   QStringList &strFilters )	// [o]
{
   QString strAllExt, strFilterExt, strExt, strExt2, strDesc, strFilter;
   bool bReadable, bWritable;
   int k, nCount;
   CoderInfo::MatchType isReadable;
   CoderInfo::MatchType isWritable;
   CoderInfo::MatchType isMultiFrame;
   
   string strext, strdesc;

   //

   isReadable = CoderInfo::TrueMatch;
   isWritable = CoderInfo::TrueMatch;
   //isReadable = CoderInfo::AnyMatch;
   //isWritable = CoderInfo::AnyMatch; 
   isMultiFrame = CoderInfo::AnyMatch; // Don't care about multi-frame support

   std::list<CoderInfo> coderList;
   try {
      coderInfoList( &coderList, isReadable, isWritable, isMultiFrame ); 
   }

   catch( Exception e ) {
      e.what( );
   };

   // make a list of all supported format

	strFilters.clear( );
   strAllExt.clear( );
   
   nCount = (int)coderList.size( );

   list<CoderInfo>::iterator entry = coderList.begin();
 
   k = 0;
   while( entry != coderList.end( ) ) {

      strdesc = entry->description();
      bReadable = entry->isReadable();
      bWritable = entry->isWritable();
      strext = entry->name();

      strExt = entry->name( ).c_str( );
      strExt = strExt.toLower( );
      strDesc = entry->description( ).c_str( );
       
      // special handling for tiff
      // add "tif" to the extantion

      if( 0 == strExt.compare( "TIFF", Qt::CaseInsensitive ) ) {
         strFilterExt = "*." + strExt + " *.tif";
      } else {
         strFilterExt = "*." + strExt;
      }
      strFilter = strDesc + " (" + strFilterExt + ")";
      
      
      if( bRead ) {         
         if( bReadable ) {
            strFilters.append( strFilter );
            strAllExt = strAllExt + strFilterExt + " ";
         }
      } else {  
         if( bWritable ) {
            strFilters.append( strFilter );
            strAllExt = strAllExt + strFilterExt + " ";
         }
      }

      entry++;
   }
   
   // all format 
   
   strFilter = "All Formats (" + strAllExt + ")";
   strFilters.insert( 0, strFilter );

   // all files

   strFilter = "All Files(*.*)";
   strFilters.insert( 0, strFilter );

   // general formats

   strFilter = "Image Files(";
   strFilter += "*.jpg ";
   strFilter += "*.tif ";
   strFilter += "*.tiff ";
   strFilter += "*.sgi ";
   strFilter += "*.cin ";
   strFilter += "*.dpx ";
   strFilter += "*.bmp ";
   strFilter += ")";
   strFilters.insert( 0, strFilter );
   
   return;
}

void imageMagickFileFilter_PI(bool bRead, // [i] true for read, false for write
                         QString &strFilter )	// [o]
{
   int i, nBufferSize, nFormats;
   QString strFormat;
   QStringList strFilters;

   strFilters.clear( );

   imageMagickFileFilter_PI(bRead, strFilters);
   
   nFormats = (int)strFilters.size( );
   nBufferSize = 0;
   for( i = 0 ; i < nFormats ; i++ ) {
      strFormat = strFilters.at( i );  
      if( 0 < i ) {
         nBufferSize = nBufferSize + 2;
      }
      nBufferSize = nBufferSize + (int)strFormat.size( );
   } 
      
   strFilter.clear( );
   strFilter.reserve( nBufferSize + 10 );
   for( i = 0 ; i < nFormats ; i++ ) {
      strFormat = strFilters.at( i );  
      if( 0 < i ) {
         strFilter.push_back( ";;" );
      }
      strFilter.push_back( strFormat );
   }
   
   return;
}

//
// make a list of image properties to display 
//
// returns:
// true on success or false
//
bool getImageProps_PI(  Image &img, 
                      const QString strFile, 
                      pixq_ImageInfo *info )
{
   bool bRetCode = false;
   
   if( !info->getMagickInfo( img, strFile ) ) {
      goto PIX_EXIT;
   }

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// load image using imagemagick library
//
bool magickLoadImage_PI(const QString strFile,
   pixq_ImageMatrix *usRed,
   pixq_ImageMatrix *usGrn,
   pixq_ImageMatrix *usBlu)
{
   bool bRetCode = false;
   //QByteArray file = strFile.toLatin1();
   QByteArray file = strFile.toUtf8();
   const char *szFile = file.data();

   int nHeight, nWidth;
   string strFormat;
   Magick::Pixels *pix = NULL;

   pixq_ImageAccess ImgMatrix;
   Image in;

   //
   // read the entire image
   //

   try {
      in.read(szFile);
   }

   catch (Exception & /* err */) {
      fprintf(stderr, "ERROR! Failed to Read Image(magickLoadImage_PI).\n");
      goto PIX_EXIT;
   }

   nHeight = (int)in.rows();
   nWidth = (int)in.columns();

   // set image header info

   if (!usRed->checkAlloc(nHeight, nWidth)) {
      goto PIX_EXIT;
   }

   if (!usGrn->checkAlloc(nHeight, nWidth)) {
      goto PIX_EXIT;
   }

   if (!usBlu->checkAlloc(nHeight, nWidth)) {
      goto PIX_EXIT;
   }

   // read the pixels

   pix = new Magick::Pixels(in);

   ImgMatrix.setOutRgb(usRed, usGrn, usBlu);
   if (!ImgMatrix.checkAllocOut(nHeight, nWidth)) {
      fprintf(stderr, "ERROR! Memory Allocation Failed(magickLoadImage_ITF).\n");
      goto PIX_EXIT;
   }

   if (!ImgMatrix.getMagickBuffer(pix)) {
      fprintf(stderr, "ERROR! Failed to create Magick::Image(magickLoadImage_ITF).\n");
      goto PIX_EXIT;
   }
   
   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   if (pix) {
      delete pix;
      pix = NULL;
   }
   return bRetCode;
}


bool magickLoadImage_PI(const QString strFile,
                        pixq_ImageInfo *info, 
                        pixq_ImageMatrix *usRed, 
                        pixq_ImageMatrix *usGrn, 
                        pixq_ImageMatrix *usBlu )
{
   bool bRetCode = false;      

   //QByteArray file = strFile.toLatin1();
   QByteArray file = strFile.toUtf8();

   const char *szFile = file.data();
   
   int nHeight, nWidth, nDepth;
   string strFormat;
   Magick::Pixels *pix = NULL;
   
   pixq_ImageAccess ImgMatrix;
   Image in;

#define _LOAD_REPORT_TIME
#ifdef _LOAD_REPORT_TIME
   pixq_StopWatch watch;
   watch.InitTime();
   watch.ResetTime();
   watch.ResetAllTime();
   watch.SetLabel(0, "[magickLoadImage_PI]read");
   watch.SetLabel(1, "[magickLoadImage_PI]allocate");
   watch.SetLabel(2, "[magickLoadImage_PI]set buffer");
   watch.SetLabel(3, "[magickLoadImage_PI]post");
   watch.SetLabel(4, "[magickLoadImage_PI]All");
#endif // _LOAD_REPORT_TIME

   //
   // read the entire image
   //

   try {
      in.read( szFile );
   }
   
   catch (Exception &err) {
      qDebug() << "ERROR! Failed to Read Image(magickLoadImage_PI):" << err.what();
      qDebug() << "ERROR!" << strFile;
      //goto PIX_EXIT;
   }
   
   nHeight = (int)in.rows( );
   nWidth = (int)in.columns( );
   nDepth = (int)in.depth( );

#ifdef _LOAD_REPORT_TIME
   watch.AddElapsed(0);
#endif // _LOAD_REPORT_TIME

   // set image header info

   if (!usRed->checkAlloc(nHeight, nWidth)) {
      goto PIX_EXIT;
   }

   if (!usGrn->checkAlloc(nHeight, nWidth)) {
      goto PIX_EXIT;
   }

   if (!usBlu->checkAlloc(nHeight, nWidth)) {
      goto PIX_EXIT;
   }

#ifdef _LOAD_REPORT_TIME
   watch.AddElapsed(1);
#endif // _LOAD_REPORT_TIME

   // read the pixels

   pix = new Magick::Pixels(in); 

   ImgMatrix.setOutRgb(usRed, usGrn, usBlu);
   if (!ImgMatrix.checkAllocOut(nHeight, nWidth)) {
      fprintf(stderr, "ERROR! Memory Allocation Failed(magickLoadImage_ITF).\n");
      goto PIX_EXIT;
   }

#ifdef _LOAD_REPORT_TIME
   watch.AddElapsed(1);
#endif // _LOAD_REPORT_TIME

   if (!ImgMatrix.getMagickBuffer(pix)) {
      fprintf(stderr, "ERROR! Failed to create Magick::Image(magickLoadImage_ITF).\n");
      goto PIX_EXIT;
   }

#ifdef _LOAD_REPORT_TIME
   watch.AddElapsed(2);
#endif // _LOAD_REPORT_TIME

   // get image header info
      
   if( !info->getMagickInfo( in, strFile ) ) {
      goto PIX_EXIT;
   }

#ifdef _MAGICK_STATISTICS
#else // _MAGICK_STATISTICS
   info->setBasicStat(0, usRed);
   info->setBasicStat(1, usGrn);
   info->setBasicStat(2, usBlu);
#endif // _MAGICK_STATISTICS

#ifdef _LOAD_REPORT_TIME
   //
   // most times in this function is spent for read
   //
   // 4k sample
   // 0 read       : 671 ms (75%)
   // 1 allocate   : 78 ms
   // 2 set buffer : 63 ms
   // 3 get info   : 93 ms
   // 4 all        : 905 ms
   //
   // takes almost 1 second to read one image
   //
   watch.AddElapsed(3);
   watch.SetAllElapsed(4);
   watch.PrintTime(stdout, 5);
#endif // _SCOPE_REPORT_TIME
#undef _LOAD_REPORT_TIME

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   if( pix ) {
      delete pix;
      pix = NULL;
   }
   return bRetCode;
}


bool magickSaveImage_PI(const QString strFile,
   const pixq_ImageMatrix *usRed,
   const pixq_ImageMatrix *usGrn,
   const pixq_ImageMatrix *usBlu)
{
   bool bRetCode = false;
   //QByteArray file = strFile.toLatin1();
   QByteArray file = strFile.toUtf8();
   const char *szFile = file.data();

   int  nHeight, nWidth;
   Magick::Pixels *pix = NULL;
   Image *out = NULL;

   pixq_ImageAccess ImgMatrix;

   nWidth = usRed->getWidth();
   nHeight = usRed->getHeight();

   out = new Image(Geometry(nWidth, nHeight), "white");
   if (!out) {
      fprintf(stderr, "ERROR! Failed to allocate Magick::Image.\n");
      goto PIX_EXIT;
   }

   pix = new Magick::Pixels(*out);

   // read the pixels

   ImgMatrix.setInRgb(usRed, usGrn, usBlu);

   if (!ImgMatrix.setMagickBuffer(pix)) {
      fprintf(stderr, "ERROR! Failed to create Magick::Image.\n");
      goto PIX_EXIT;
   }

   // write

   if (!createFolder_PC(strFile)) {
      goto PIX_EXIT;
   }

   try {
      out->write(szFile);
   }

   catch (Exception &err) {
      qDebug() << "ERROR! Failed to Write Image(magickLoadImage_PI):" << err.what();
      qDebug() << "ERROR!" << strFile;
      goto PIX_EXIT;
   }

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   if (pix) {
      delete pix;
      pix = NULL;
   }
   return bRetCode;
}


bool magickSaveImage_PI(const QString strFile,
   const pixq_Matrix<double> *dRed,
   const pixq_Matrix<double> *dGrn,
   const pixq_Matrix<double> *dBlu)
{
   bool bRetCode = false;
   pixq_ImageMatrix usRed;
   pixq_ImageMatrix usGrn;
   pixq_ImageMatrix usBlu;

   if (!usRed.getDouble(dRed)) {
      goto PIX_EXIT;
   }

   if (!usGrn.getDouble(dGrn)) {
      goto PIX_EXIT;
   }

   if (!usBlu.getDouble(dBlu)) {
      goto PIX_EXIT;
   }

   if (! magickSaveImage_PI( strFile, &usRed, &usGrn, &usBlu)) {
      goto PIX_EXIT;
   }

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// load image using imagemagick library
//
bool getHeaderInfo_PI(const QString strFile,
                      int &nImgWidth,
                      int &nImgHeight,
                      int &nBitDepth )
{
   bool bRetCode = false;
   //QByteArray file = strFile.toAscii( );
   //QByteArray file = strFile.toLatin1();
   QByteArray file = strFile.toUtf8();
   const char *szFile = file.data( );
   
   Image in;

   try {
      in.read( szFile );
   }
   
   catch( Exception & /* err */  ) {
      goto PIX_EXIT;
   }

   nImgHeight = (int)in.rows( );
   nImgWidth = (int)in.columns( );
   nBitDepth = (int)in.depth( );

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// check whether the image extention is supported by ImageMagick
// 
//
// Returns:
// true or false
//
bool checkImageFormat_PI( bool bRead, // [i] true for read, false for write
                          const QString strExtention )	// [i]
{
   bool bRetCode = false;
   QString strAllExt, strFilterExt, strExt, strExt2, strDesc, strFilter;
   bool bCheck, bStatus, bFound, bReadable, bWritable;
   QString strExtention2;
   CoderInfo::MatchType isReadable;
   CoderInfo::MatchType isWritable;
   CoderInfo::MatchType isMultiFrame;

   std::list<CoderInfo> coderList;
   list<CoderInfo>::iterator entry;

   //

   if( strExtention.isEmpty( ) ) {
      goto PIX_EXIT;
   }

   isReadable = CoderInfo::TrueMatch;
   isWritable = CoderInfo::TrueMatch;
   isMultiFrame = CoderInfo::AnyMatch; // Don't care about multi-frame support

   try {
      coderInfoList( &coderList, isReadable, isWritable, isMultiFrame ); 
   }

   catch( Exception e ) {
      e.what( );
   };

   // need special handling for tiff

   strExtention2 = strExtention;
   if( 3 == (int)strExtention2.size( ) ) {
      if( 0 == strExtention2.compare( "tif", Qt::CaseInsensitive ) ) {
         strExtention2 = "TIFF";
      }
   }

   // make a list of all supported format

   entry = coderList.begin();
   bStatus = true;
   bFound = false;
   while( bStatus ) {

      if( entry == coderList.end( ) ) {
         bStatus = false;
         continue;
      }
      
      bCheck = false;
      bReadable = entry->isReadable( );
      bWritable = entry->isWritable( );
      if( bRead ) {         
         if( bReadable ) {
            bCheck = true;
         }
      } else {  
         if( bWritable ) {
            bCheck = true;
         }
      }

      if( bCheck ) {
         strExt = entry->name( ).c_str( );
         if( 0 == strExt.compare( strExtention2, Qt::CaseInsensitive ) ) {
            bFound = true;
            bStatus = false;
            continue;
         }
      }

      entry++;
   }
	
   if( !bFound ) {
      goto PIX_EXIT;
   }

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// QDir::entryListなどで使う、画像ファイル一覧を得るためのフィルター文字列を生成
//
// QStringList filters;
// filters << "*.cpp" << "*.cxx" << "*.cc";
// dir.setNameFilters(filters);
//
void imageMagickDirFilter_PI(bool bRead, // [i] true for read, false for write
                             QStringList &strFilters )	// [o]
{
   QString strExt, strFilter;
   bool bReadable, bWritable;
   int k;
   CoderInfo::MatchType isReadable;
   CoderInfo::MatchType isWritable;
   CoderInfo::MatchType isMultiFrame;
   
#ifdef _DEBUG
   int nFiles;
#endif // _DEBUG
   //

   isReadable = CoderInfo::TrueMatch;
   isWritable = CoderInfo::TrueMatch;
   //isReadable = CoderInfo::AnyMatch;
   //isWritable = CoderInfo::AnyMatch; 
   isMultiFrame = CoderInfo::AnyMatch; // Don't care about multi-frame support

   std::list<CoderInfo> coderList;
   try {
      coderInfoList( &coderList, isReadable, isWritable, isMultiFrame ); 
   }

   catch( Exception e ) {
      e.what( );
   };

   // make a list of all supported format

	strFilters.clear( );
   list<CoderInfo>::iterator entry = coderList.begin();
 
   k = 0;
   while( entry != coderList.end( ) ) {
      
      strExt = entry->name( ).c_str( );
      strExt = strExt.toLower( );
      strFilter = "*." + strExt;

      //

      bReadable = entry->isReadable( );
      bWritable = entry->isWritable( );
      
      if( bRead ) {         
         if( bReadable ) {
            strFilters.append( strFilter );
         }
      } else {  
         if( bWritable ) {
            strFilters.append( strFilter );
         }
      }
      
      // special handling for tiff
      // add "tif" to the extantion

      if( 0 == strExt.compare( "TIFF", Qt::CaseInsensitive ) ) {
         strFilter = "*.tif";
         if( bRead ) {         
            if( bReadable ) {
               strFilters.append( strFilter );
            }
         } else {  
            if( bWritable ) {
               strFilters.append( strFilter );
            }
         }
      }

      entry++;
   }
   
#ifdef _DEBUG
   nFiles = strFilters.size( );
   for( k = 0 ; k < nFiles ; k++ ) {
      strFilter = strFilters.at( k );
      //qDebug() << k+1 << "/" << nFiles << ": " << strFilter;
   }
#endif // _DEBUG

   return;
}

//
// make a list of image properties to display 
//
// returns:
// true on success or false
//
bool getImageProps_PI( const QString strFile, 
                      QStringList *strPropNames, 
                      QStringList *strProps )
{
   bool bRetCode = false;
   int nFileSize;
   //QByteArray file = strFile.toAscii( );
   //QByteArray file = strFile.toLatin1();
   QByteArray file = strFile.toUtf8();
   const char *szFile = file.data( );
   QString strPropName, strProp, strName, strExt;
   QFileInfo fi;
   QByteArray buf;   
   CoderInfo ci; 

   Image in;
   
   strPropNames->clear( );
   strProps->clear( );

   try {
      in.read( szFile );
   }
   
   catch( Exception & /* err */  ) {
      goto PIX_EXIT;
   }
   
   // file name
   
   fi.setFile( strFile );
   strName = fi.fileName( );
   strExt = fi.suffix( ); 
   nFileSize = fi.size( );

   strPropName = "File Name";
   strProp = strName;
   
   strPropNames->push_back( strPropName );
   strProps->push_back( strProp );

   // file description

   buf = strExt.toLatin1( ); 
   ci = CoderInfo( buf.data( ) );
   strProp = (ci.description( )).c_str( );
   
   strPropName = "Description";

   strPropNames->push_back( strPropName );
   strProps->push_back( strProp );
   
   // file size

   strPropName = "File Size";
   strProp.sprintf( "%d", nFileSize );

   //

   //nImgHeight = (int)in.rows( );
   //nImgWidth = (int)in.columns( );
  // nBitDepth = (int)in.depth( );

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
