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

#ifdef _DEBUG
#pragma comment ( lib, "opencv_calib3d2411d.lib" )
#pragma comment ( lib, "opencv_contrib2411d.lib" )
#pragma comment ( lib, "opencv_core2411d.lib" )
#pragma comment ( lib, "opencv_features2d2411d.lib" )
#pragma comment ( lib, "opencv_flann2411d.lib" )
#pragma comment ( lib, "opencv_highgui2411d.lib" )
#pragma comment ( lib, "opencv_imgproc2411d.lib" )
#pragma comment ( lib, "opencv_legacy2411d.lib" )
#pragma comment ( lib, "opencv_ml2411d.lib" )
#pragma comment ( lib, "opencv_objdetect2411d.lib" )
#pragma comment ( lib, "opencv_video2411d.lib" )
#else // _DEBUG
#pragma comment ( lib, "opencv_calib3d2411.lib" )
#pragma comment ( lib, "opencv_contrib2411.lib" )
#pragma comment ( lib, "opencv_core2411.lib" )
#pragma comment ( lib, "opencv_features2d2411.lib" )
#pragma comment ( lib, "opencv_flann2411.lib" )
#pragma comment ( lib, "opencv_highgui2411.lib" )
#pragma comment ( lib, "opencv_imgproc2411.lib" )
#pragma comment ( lib, "opencv_legacy2411.lib" )
#pragma comment ( lib, "opencv_ml2411.lib" )
#pragma comment ( lib, "opencv_objdetect2411.lib" )
#pragma comment ( lib, "opencv_video2411.lib" )
#endif // _DEBUG

int main(int argc, char *argv[])
{
   Q_INIT_RESOURCE(QtRectify);

   QApplication app( argc, argv );

   // Initialize ImageMagick install location for Windows
   InitializeMagick( *argv );
   
   rectify_window mainWin;

   mainWin.show( );
   
   return app.exec( );
}
