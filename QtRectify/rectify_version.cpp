#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_panes.h"
#include "rectify_window.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

//
// Version History:
//

pixq_Version Version( void )
{
   pixq_Version ver;
   short sPlatform;
   QString strFile = ":/Files/rectify_version.xml";
   
   // read software info from xml

   if (!ver.readXml(strFile)) {
      ver.Clear( );
      ver.SetCompany( "PixTOPO" );
      ver.SetProductName( "pixRectify" );
   }

#ifdef WIN64
   sPlatform = pixq_Properties::PlatformWin64;
#else // WIN64
   sPlatform = pixq_Properties::PlatformWin32; 
#endif // WIN64 
   ver.SetPlatform(sPlatform);

   return ver;
}