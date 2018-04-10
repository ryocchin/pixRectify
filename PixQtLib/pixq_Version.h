#pragma once

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>

class PIXQTLIB_EXPORT pixq_Version
{
public:
   //
   // program module
   //
   enum {
      // default, not specified
      ProgramTypeDefault = 0,
      // programs related to bible
      ProgramTypeBible = 1,
      // programs related to image
      ProgramTypeImage = 2,
   } PixTopoProgramModule;

public:
   pixq_Version(void);
   ~pixq_Version(void);

public:
   // copy constructor
	pixq_Version &operator=( const pixq_Version &that );

   // check whter this version is newer than that
	bool operator>=( const pixq_Version &that ) const;
	bool operator>( const pixq_Version &that ) const;

private:
   QString _strCompany;
   QString _strProductName;
   QString _strApplication;
   QString _strJpDescription;
   QString _strEnDescription;

   unsigned short _usMajorVersion;
   unsigned short _usMinorVersion;

   // notes:
   // release numberを使わない場合は0にしておく
   // その場合は画面に表示しない
   //
   unsigned short _usReleaseNumber;

   QDate _ReleaseDate;

   // contact mail address
   QString _strContact;

   // web site for support
   QString _strWebSite;

   // developers blog
   QString _strDevBlog;

   // must be one of pixq_Properties::PixTopoSystemPlatform
   short _sPlatform;

   // program module, one of PixTopoProgramModule
   short _sModule;
   
public:
   void Clear( void );

   void SetCompany( QString strCompany ) { _strCompany = strCompany; }
   void SetProductName( QString strProductName ) { _strProductName = strProductName; }
   void SetApplication( QString strApplication ) { _strApplication = strApplication; }

   void SetJpDescription(QString strDescription) { _strJpDescription = strDescription; }
   void SetEnDescription(QString strDescription) { _strEnDescription = strDescription; }

   void SetMajorVersion( unsigned short usMajorVersion ) { _usMajorVersion = usMajorVersion; }
   void SetMinorVersion( unsigned short usMinorVersion ) { _usMinorVersion = usMinorVersion; }
   void SetReleaseNumber( unsigned short usReleaseNumber ) { _usReleaseNumber = usReleaseNumber; }
   
   void SetReleaseDate( QDate Date ) { _ReleaseDate = Date; }

   void SetContact(QString strContact) { _strContact = strContact; }
   void setWebSite(QString strWebSite) { _strWebSite = strWebSite; }
   void setDevBlog(QString strDevBlog) { _strDevBlog = strDevBlog; }

   void SetPlatform(short sPlatform) { _sPlatform = sPlatform; }
   void setModule(short sModule) { _sModule = sModule; }

   //

   QString GetVersionString( void ) const;

   QString GetCompany(void) const  { return _strCompany; }
   QString GetProductName(void) const { return _strProductName; }
   QString getApplication(void) const { return _strApplication; }
   QString GetJpDescription(void) const { return _strJpDescription; }
   QString GetEnDescription(void) const { return _strEnDescription; }

   unsigned short GetMajorVersion(void) const { return _usMajorVersion; }
   unsigned short GetMinorVersion(void) const { return _usMinorVersion; }
   unsigned short GetReleaseNumber( void ) const { return _usReleaseNumber; }
   
   QDate GetReleaseDate(void) const  { return _ReleaseDate; }

   QString GetContact(void) const  { return _strContact; }
   QString getWebSite(void) const  { return _strWebSite; }
   QString getDevBlog(void) const  { return _strDevBlog; }

   short GetPlatform(void)const   { return _sPlatform; }
   short getModule(void) const   { return _sModule; }

   bool WriteXml( QString strFile );
   bool readXml( QString strFile );

};

} // namespace 

