#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_panes.h"
#include "image_splitter.h"
#include "rectify_window.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

class rectify_window;

ImageSplitter::ImageSplitter( Qt::Orientation orientation, 
                             QWidget*parent )
                             : QSplitter( orientation, parent)
{
   return;
}

ImageSplitter::~ImageSplitter()
{
   return;
}

//
// two image panes must be of same width!
//
void ImageSplitter::resizeEvent( QResizeEvent * /*ev*/ )
{
   rectify_window *pMain = (rectify_window*)getMainWindow();
   
   pMain->setImageSplitterWidth();

   return;
}
