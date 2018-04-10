#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_panes.h"
#include "rectify_dock.h"
#include "rectify_window.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

class rectify_window;

rectify_dock::rectify_dock(const QString &title,
                         QWidget *parent )
                         : QDockWidget( title, parent )
{
   _pMainWindow = (rectify_window*)parent;

   _bInit = false;
   _sType = RectifyDockNone;

   return;
}

rectify_dock::rectify_dock(QWidget *parent)
: QDockWidget( parent)
{
   return;
}

rectify_dock::~rectify_dock()
{
   return;
}

//
// two image panes must be of same width!
//
void rectify_dock::resizeEvent(QResizeEvent * /*ev*/)
{
   return;
}

void rectify_dock::moveEvent(QMoveEvent * /* eve */)
{
   return;
}

void rectify_dock::showEvent(QShowEvent * /*eve*/)
{
   return;
}