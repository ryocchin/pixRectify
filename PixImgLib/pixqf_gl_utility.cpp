#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

//
// pixtopo image technology framework
// opengl utlity functions
//

//
// check if current opengl version 2.0 or higher!
//
bool OpenGlHigherThanTwo_PI( void )
{
   bool bRet;
   int nLen = 0;
   const char *szTmp = NULL;
   char szVersion[STANDARD_BUFFER_SIZE];
#ifdef _DEBUG
   char szVendor[STANDARD_BUFFER_SIZE];
   char szExtensions[STANDARD_BUFFER_SIZE], szRenderer[STANDARD_BUFFER_SIZE];
#endif // _DEBUG

#ifdef _DEBUG 
   fprintf( stdout, "===> [OpenGlHigherThanTwo_PI]Entered!\n" );
#endif // _DEBUG

   szTmp = (char*)glGetString( GL_VERSION );
   nLen = (int)strlen( szTmp );
   if( nLen + 1 > STANDARD_BUFFER_SIZE ) {
      bRet = false;
      goto PIX_EXIT;
   }
   
   strcpy( szVersion, szTmp );
   szVersion[nLen] = '\0';
   
   if( '1' == szVersion[0] ) {
      bRet = false;
   } else if( '2' == szVersion[0] ) {
      bRet = true;
   } else if( '3' == szVersion[0] ) {
      bRet = true;
   } else if( '4' == szVersion[0] ) {
      bRet = true;
   } else if( '5' == szVersion[0] ) {
      bRet = true;
   } else if( '6' == szVersion[0] ) {
      bRet = true;
   } else {
      bRet = false;
   }

#ifdef _DEBUG
   strncpy( szVendor, (char*)glGetString( GL_VENDOR ), STANDARD_BUFFER_SIZE );
   strncpy( szRenderer, (char*)glGetString( GL_RENDERER ), STANDARD_BUFFER_SIZE );
   strncpy( szVersion, (char*)glGetString( GL_VERSION ), STANDARD_BUFFER_SIZE );
   strncpy( szExtensions, (char*)glGetString( GL_EXTENSIONS ), STANDARD_BUFFER_SIZE );
#endif // _DEBUG

#ifdef _DEBUG
   fprintf( stdout, "===> OpenGL Vendor: %s.\n", szVendor );
   fprintf( stdout, "===> OpenGL Renderer: %s.\n", szRenderer );
   fprintf( stdout, "===> OpenGL Version: %s.\n", szVersion );
   //fprintf( stdout, "===> OpenGL Extensions: %s.\n", szExtensions );
#endif // _DEBUG

PIX_EXIT:
   return bRet;
}
