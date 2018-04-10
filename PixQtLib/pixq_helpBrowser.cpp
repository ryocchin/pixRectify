#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework; 

#include "pixq_HelpBrowser.h"

pixq_HelpBrowser::pixq_HelpBrowser(QHelpEngine *helpEngine, QWidget *parent)
   : QTextBrowser(parent)
{
   QFont fn;
   int nPointSize;

   _helpEngine = helpEngine;

   fn = font();
   nPointSize = fn.pointSize();
   fn.setPointSize( _nPointSize );
   setFont(fn);

   return;
}

QVariant pixq_HelpBrowser::loadResource(int type, const QUrl &url)
{
   qDebug() << url.toString();

   QTextBrowser::loadResource(type, url);

   if (url.scheme() == "qthelp") {
      return QVariant(_helpEngine->fileData(url));
   }
   else {
      return QTextBrowser::loadResource(type, url);
   }
}

