#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>

PixImgLib::PixImgLib()
{
   Q_INIT_RESOURCE( PixImgLib );
      
   return;
}

PixImgLib::~PixImgLib()
{
   return;
}


//
// get label for given key word(class) from xml file
//
QString PixImgLib::getImageLibLabel( const QString strClass, // [i] class name to search
                                      const QString strName, // [i] label(text) name to search
                                      const QString strDefault, // [i] default in case the label couldn't be found,
                                      int iLanguage ) // [i] default = Locale::English
{    
   QString strWord;   
   bool bLabel, bClass;
   QString strLang, strHeader, strValue; 
   QFile *file = NULL;
   QXmlStreamReader reader;
   QXmlStreamAttributes attr;
   
   QString strFile = ":/Files/msg_imglib.xml";

   switch (iLanguage) {
   case QLocale::Japanese:
      strLang = "Jp";
      break;

   case QLocale::English:
   default:
      strLang = "En";
      break;
   }

   strWord = strDefault;   
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

   if( reader.attributes().value("version") != "1.0" ) {
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

         strWord = attr.value( strLang ).toString( );
         bLabel = false;
         bClass = false;
         continue;
      }
   }

PIX_EXIT:
   if( file ) {
      file->close( );
      file = NULL;
   }
   return strWord;
}

//
// same as above except that default label is same as label name
//
QString PixImgLib::getImageLibLabel( const QString strClass, // [i] class name to search
                                      const QString strName, // [i] label(text) name to search
                                      int iLanguage ) // [i] default = Locale::English
{        
   return getImageLibLabel(strClass, strName, strName, iLanguage);
}


