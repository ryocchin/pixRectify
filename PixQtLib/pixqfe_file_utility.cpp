#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

//
// check whether the file exists.
//
bool fileExist_PC(const QString strFile)
{
   QFileInfo fi;   
   fi.setFile( strFile );
   return fi.exists( );
}

//
// this is the name of the local file to copy the update file from
// website
//
// name of the xml file storing the latest version info of our software
//
// notes:
// basically, files are in the same directory as the executable file
// NEVER change these name!
//
QString GetLatestVerXmlFile_PC( int iMode )
{
   QString strPath;

   strPath = QFileInfo( QCoreApplication::applicationDirPath( ) ).filePath( );
   
   switch( iMode ) {
   case EnvModeHikari: 
      //
      // no diff for x86/x64
      //
      strPath.append( "/version.xml\0" );
      break;

   case EnvModeScope: 
      strPath.append("/version.xml\0");
      break;
      
   case EnvModeRectify:
      strPath.append("/version.xml\0");
      break;

   case EnvModeOrtho:
      strPath.append("/version.xml\0");
      break;
    
   case EnvModeSampler:
      strPath.append( "/version.xml\0" );
      break;

   case EnvModeBagster:  
   default:
      break;
   }

   return strPath;
}

QString GetTentativeVerXmlFile_PC( int iMode )
{
   QString strPath;

   //strPath = QDesktopServices::storageLocation( QDesktopServices::DataLocation );
   //strPath = QStandardPaths::GenericDataLocation;
   strPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);

   switch( iMode ) {
   case EnvModeHikari:
   case EnvModeScope: 
   case EnvModeRectify:
   case EnvModeOrtho:
   case EnvModeSampler:
      strPath.append( "\\version.xml\0" );
      break;

   case EnvModeBagster:  
   default:
      break;
   }

   return strPath;
}

//
// name of the xml file on the web storing the latest version info of our software
// 
// notes:
// file is updated everytime software's version is updated.
// NEVER change these name!
//
// name for hikari: http://hikari.sourceforge.jp/hikari_version.xml
// 
QString GetUpdateVerXmlFile_PC( int iMode )
{
   QString strPath;

   strPath = GetWebsiteUrl_PC( );
   
   switch( iMode ) {
   case EnvModeHikari:
      strPath.append( "/hikari/hikari_version.xml\0" );
      break;

   case EnvModeScope: 
      strPath.append("/pixdiff/pixdiff_version.xml\0");
      break;

   case EnvModeRectify:
      strPath.append("/rectify/rectify_version.xml\0");
      break;

   case EnvModeOrtho:
      strPath.append("/ortho/version.xml\0");
      break;
    
   case EnvModeSampler:
   case EnvModeBagster:  
   default:
      break;
   }

   return strPath;
}

//
// return URL of our website
//
QString GetWebsiteUrl_PC( void )
{
   QString strPath = "http://hikari.sourceforge.jp";
   //QString strPath = "http://www.pixtopo.com/hikari";

   return strPath;
}

//
// return URL of our website for each project
//
QString GetProjectUrl_PC( int iMode )
{
   QString strPath;

   strPath = GetWebsiteUrl_PC( );
   
   switch( iMode ) {
   case EnvModeHikari:
      strPath.append( "/hikari\0" );
      break;

   case EnvModeScope:
      strPath.append("/pixdiff\0");
      break;

   case EnvModeRectify:
      strPath.append("/rectify\0");
      break;

   case EnvModeOrtho:
      strPath.append("/ortho\0");
      break;
    
   case EnvModeSampler:
      strPath.append( "/sampler\0" );
      break;

   case EnvModeBagster:  
   default:
      break;
   }

   return strPath;
}

//
// return URL of the top html file of each project
//
QString getProjectTopUrl_PC( int iMode )
{
   QString strPath;

   strPath = GetProjectUrl_PC( iMode );
   
   switch( iMode ) {
   case EnvModeHikari:
      //strPath.append("/index.html\0");
      break;
    
   case EnvModeScope: 
      //strPath.append("/index.html\0");
      break;

   case EnvModeRectify:
      //strPath.append("/index.html\0");
      break;

   case EnvModeOrtho:
      break;

   case EnvModeSampler:
   case EnvModeBagster:  
   default:
      break;
   }

   return strPath;
}

//
// create directory to store strFile recursively
//
// notes:
//
bool createFolder_PC(const QString strFile) // [i] file name, not directory!
{
   bool bRetCode = false;
   QFileInfo fi;
   QString strPath;
   QDir dir;

   if (fileExist_PC(strFile)) {
      bRetCode = true;
      goto PIX_EXIT;
   }

   fi.setFile( strFile );
   //strPath = fi.path( );
   strPath = fi.absolutePath( );

   if( dir.exists( strPath ) ) {
      bRetCode = true;
      goto PIX_EXIT;
   }

   if( !dir.mkdir( strPath ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// returns files extention in upper case
//
QString getFileExtention_PI(const char *szFile)
{
   QString strFile = szFile;
   QString strExt;

   strExt = getFileExtention_PI(strFile);
   
   return strExt;
}

QString getFileExtention_PI(const QString strFile)
{
   QFileInfo fi;
   QString strExt;
   
   fi.setFile( strFile );
   strExt = fi.suffix();
   strExt.toUpper();

	return strExt;
}

//
// get from piuxlib common message xml file
// the label for the given class and name
//
// returns:
// "label name" is returned on error.
//
QString getClassLabel_PC(const QString strClass, // [i] class name
                         const QString strName, // [i] label name
                         int iLanguage ) // [i] default QLocale::English 
{
   bool bLabel, bClass;
   QString strLang, strLabel, strHeader, strValue;
   QFile *file = NULL;
   QXmlStreamReader reader;
   QXmlStreamAttributes attr;
   
   QString strFile = ":/Files/msg_pixlib.xml";

   strLabel = strName;

   switch (iLanguage) {
   case QLocale::Japanese:
      strLang = "Jp";
      break;
      
   case QLocale::English:
   default:
      strLang = "En";
      break;
   }
   
   //

   file = new QFile( strFile );
   if ( !file->open( QIODevice::ReadOnly | QIODevice::Text ) ) {
      // file does not exist
      goto PIX_EXIT;
   }

   //
   // check xml file
   //

   reader.setDevice( file );

   if( !reader.readNextStartElement( ) ) {
      goto PIX_EXIT;
   }

   if( reader.name() != "pixtopo" ) {
      goto PIX_EXIT;
   }

   if( reader.attributes().value("version") != "1.0") {
      goto PIX_EXIT;
   }

   //
   
   bClass = true;
   while( bClass ) {
      
      if( reader.atEnd( ) ) {
         bClass = false;
         continue;
      }

      if( !reader.readNextStartElement()) {
         bClass = false;
         continue;
      }

      strHeader = reader.name().toString( );   
      if( "Class" != strHeader ) {
         continue;
      }

      attr = reader.attributes();
      strValue = attr.value( "ID" ).toString();
      if( strValue != strClass ) {
         reader.skipCurrentElement( );
         continue;
      }

      // class found! find the label

      bLabel = true;
      while( bLabel ) {
         if( !reader.readNextStartElement()) {
            bLabel = false;
            bClass = false;
            continue;
         }
   
         strHeader = reader.name().toString( );   
         if( "Label" != strHeader ) {
            continue;
         }

         attr = reader.attributes();
         strValue = attr.value( "ID" ).toString();
         if( strValue != strName ) {
            reader.skipCurrentElement( );
            continue;
         }

         strLabel = attr.value(strLang).toString();
         bLabel = false;
         bClass = false;
         continue;
      }
   }

   //
PIX_EXIT:
   if( file ) {
      file->close( );
      file = NULL;
   }
   return strLabel;
}
