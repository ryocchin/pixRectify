#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_Version.h"

pixq_Version::pixq_Version(void)
{
   Clear( );
}

pixq_Version::~pixq_Version(void)
{
   return;
}

void pixq_Version::Clear( void )
{
   _strCompany.clear( );
   _strProductName.clear( );
   _strApplication.clear();

   _strJpDescription.clear();
   _strEnDescription.clear();

   _usMajorVersion = 0;
   _usMinorVersion = 0;
   _usReleaseNumber = 0;

   _ReleaseDate = QDate( 0, 0, 0 );

   _strContact.clear();
   _strWebSite.clear();
   _strDevBlog.clear();

   _sPlatform = pixq_Properties::PlatformUnknown;
   _sModule = ProgramTypeDefault;

   return;
}

pixq_Version &pixq_Version::operator=( const pixq_Version &that )
{    
   if( this == &that ) {
      goto PIX_EXIT;
   }

   _strCompany       = that._strCompany;
   _strProductName   = that._strProductName;
   _strApplication = that._strApplication;
   _strJpDescription = that._strJpDescription;
   _strEnDescription = that._strEnDescription;
                            
   _usMajorVersion   = that._usMajorVersion;
   _usMinorVersion   = that._usMinorVersion;
   _usReleaseNumber  = that._usReleaseNumber;

   _ReleaseDate      = that._ReleaseDate;
                            
   _strContact = that._strContact;
   _strWebSite = that._strWebSite;
   _strDevBlog = that._strDevBlog;

   _sPlatform = that._sPlatform;
   _sModule = that._sModule;

PIX_EXIT:
   return *this;
}
//
// check whter this version is newer than "that"
//
// returns:
// true when this version is newer than "that"
//
bool pixq_Version::operator>( const pixq_Version &that )
const
{    
   bool bNew = false;

   if( _usMajorVersion < that._usMajorVersion ) {
      bNew = false;
      goto PIX_EXIT;
   } else if( _usMajorVersion > that._usMajorVersion ) {
      bNew = true;
      goto PIX_EXIT;
   }

   // same major version

   if( _usMinorVersion < that._usMinorVersion ) {
      bNew = false;
      goto PIX_EXIT;
   } else if( _usMinorVersion > that._usMinorVersion ) {
      bNew = true;
      goto PIX_EXIT;
   }

   // same major and minor version

   if( _usReleaseNumber < that._usReleaseNumber ) {
      bNew = false;
      goto PIX_EXIT;
   } else if( _usReleaseNumber > that._usReleaseNumber ) {
      bNew = true;
      goto PIX_EXIT;
   } else {
      // totall same version
      bNew = false;
      goto PIX_EXIT;
   }

PIX_EXIT:
   return bNew;
}

QString pixq_Version::GetVersionString( void )
const
{ 
   QString strVersion;

   strVersion.sprintf( "%d.%d.%d", _usMajorVersion, _usMinorVersion, 
      _usReleaseNumber );
   
   return strVersion;
}


//
// check whter this version is same or newer than that
//
// returns:
// true when this version is same or newer than "that"
//
bool pixq_Version::operator>=( const pixq_Version &that )
const
{    
   bool bNew = false;

   if( _usMajorVersion < that._usMajorVersion ) {
      bNew = false;
      goto PIX_EXIT;
   } else if( _usMajorVersion > that._usMajorVersion ) {
      bNew = true;
      goto PIX_EXIT;
   }

   // same major version

   if( _usMinorVersion < that._usMinorVersion ) {
      bNew = false;
      goto PIX_EXIT;
   } else if( _usMinorVersion > that._usMinorVersion ) {
      bNew = true;
      goto PIX_EXIT;
   }

   // same major and minor version

   if( _usReleaseNumber < that._usReleaseNumber ) {
      bNew = false;
      goto PIX_EXIT;
   } else if( _usReleaseNumber > that._usReleaseNumber ) {
      bNew = true;
      goto PIX_EXIT;
   } else {
      // totall same version
      bNew = true;
      goto PIX_EXIT;
   }

PIX_EXIT:
   return bNew;
}

//
// create a xml file containing the current version info
// this file must be uploaded to the ftp server
//
bool pixq_Version::WriteXml( QString strFile )
{
   bool bRetCode = false;

   QDate date;
   QString strValue, strMessage;

   QFile *file = NULL;
   QXmlStreamWriter writer;

   // create output xml file
   
   if (!createFolder_PC(strFile)) {
      // ERROR! Failed to Create Temporary Path
      goto PIX_EXIT;
   }

   file = new QFile( strFile );
   if ( !file->open( QFile::WriteOnly | QFile::Text ) ) { 
      goto PIX_EXIT;
   }

   writer.setAutoFormatting( true );
   writer.setDevice( file );

   // write contents

   writer.writeStartDocument();

   writer.writeStartElement( "hikari" );
   writer.writeAttribute( "version", "1.0" );
   writer.writeAttribute( "data", "latest" );

   // attibute - latest version

   writer.writeStartElement( "version" );

   writer.writeAttribute( "company", _strCompany );
   writer.writeAttribute( "product", _strProductName );
   writer.writeAttribute( "application", _strApplication );

   writer.writeAttribute("jp_description", _strJpDescription);
   writer.writeAttribute("en_description", _strEnDescription);

   strValue.sprintf( "%d", _usMajorVersion );
   writer.writeAttribute( "major", strValue );

   strValue.sprintf( "%d", _usMinorVersion );
   writer.writeAttribute( "minor", strValue );

   strValue.sprintf( "%d", _usReleaseNumber );
   writer.writeAttribute( "release", strValue );

   //

   date = GetReleaseDate( );

   strValue.sprintf( "%d", date.year( ) );
   writer.writeAttribute( "year", strValue );
   
   strValue.sprintf( "%d", date.month( ) );
   writer.writeAttribute( "month", strValue );

   strValue.sprintf( "%d", date.day( ) );
   writer.writeAttribute( "day", strValue );

   //
   
   writer.writeAttribute("contact", _strContact);
   writer.writeAttribute("website", _strWebSite);
   writer.writeAttribute("devblog", _strDevBlog);

   strValue.sprintf( "%d", _sPlatform );
   writer.writeAttribute( "platform", strValue );

   //

   writer.writeEndElement(); // version

   // end the last section

   writer.writeEndElement(); // hikari

   // create output xml file

   writer.writeEndDocument();

   //
   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   if( file ) {
      file->close( );
      file = NULL;
   }
   return bRetCode;
}

//
// read version infgo from XML file
//
bool pixq_Version::readXml(QString strFile)
{
   bool bRetCode = false;
   bool bOK;
   int iValue, nYear, nMonth, nDay;
   QDate date;
   QString strValue, strMessage;

   QFile *file = NULL;
   QXmlStreamReader reader;
   QXmlStreamAttributes attr;

   // get version file name

   Clear( );

   // create output xml file

   file = new QFile( strFile );
   if ( !file->open( QFile::ReadOnly | QFile::Text ) ) {
      goto PIX_EXIT;
   }

   reader.setDevice( file );

   // read contents

   if( !reader.readNextStartElement( ) ) {
      goto PIX_EXIT;
   }

   if( reader.name() != "pixtopo" ) {
      goto PIX_EXIT;
   }

   if( reader.attributes().value("version") != "1.0") {
      goto PIX_EXIT;
   }

   if( reader.attributes().value("data") != "latest") {
      goto PIX_EXIT;
   }

   // read version attibute - latest version

   if( !reader.readNextStartElement()) {
      goto PIX_EXIT;
   }

   strValue = reader.name().toString( );
   if( "Version" != strValue ) {
      goto PIX_EXIT;
   }

   // read program attribute

   attr = reader.attributes();
   
   _strCompany = attr.value( "company" ).toString();
   _strProductName = attr.value( "product" ).toString();
   _strApplication = attr.value( "application" ).toString();

   _strJpDescription = attr.value("jp_description").toString();
   _strEnDescription = attr.value("en_description").toString();

   // platform info

   strValue = attr.value("platform").toString();
   if ("x86" == strValue) {
      _sPlatform = (short)pixq_Properties::PlatformWin32;
   }
   else if ("x64" == strValue) {
      _sPlatform = (short)pixq_Properties::PlatformWin64;
   }
   else {
      _sPlatform = (short)pixq_Properties::PlatformUnknown;
   }

   // program module info

   strValue = attr.value("module").toString();
   if ("image" == strValue) {
      _sModule = (short)ProgramTypeImage;
   }
   else if ("bible" == strValue) {
      _sModule = (short)ProgramTypeBible;
   }
   else {
      _sModule = (short)ProgramTypeDefault;
   }

   // read version attribute

   strValue = attr.value( "major" ).toString();
   iValue = strValue.toInt( &bOK );
   if( !bOK ) {
      iValue = 0;
      //goto PIX_EXIT;
   }
   _usMajorVersion = (unsigned short)iValue;
   
   strValue = attr.value( "minor" ).toString();
   iValue = strValue.toInt( &bOK );
   if (!bOK) {
      iValue = 0;
      //goto PIX_EXIT;
   }
   _usMinorVersion = (unsigned short)iValue;

   strValue = attr.value( "release" ).toString();
   iValue = strValue.toInt( &bOK );
   if (!bOK) {
      iValue = 0;
      //goto PIX_EXIT;
   }
   _usReleaseNumber = (unsigned short)iValue;

   // date

   strValue = attr.value( "year" ).toString();
   nYear = strValue.toInt( &bOK );
   if (!bOK) {
      nYear = 0;
      //goto PIX_EXIT;
   }

   strValue = attr.value( "month" ).toString();
   nMonth = strValue.toInt( &bOK );
   if (!bOK) {
      nMonth = 0;
      //goto PIX_EXIT;
   }

   strValue = attr.value( "day" ).toString();
   nDay = strValue.toInt( &bOK );
   if (!bOK) {
      nDay = 0;
      //goto PIX_EXIT;
   }
   
   // Qt5
   //_ReleaseDate.setYMD( nYear, nMonth, nDay );
   _ReleaseDate.setDate( nYear, nMonth, nDay );
   // Qt5

   // contact info
   
   _strContact = attr.value("contact").toString();
   _strWebSite = attr.value("website").toString();
   _strDevBlog = attr.value("devblog").toString();
   
   //

   reader.skipCurrentElement();

   //
   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   if( file ) {
      file->close( );
      file = NULL;
   }
   return bRetCode;
}


