#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtHelp>

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>

#include <QHelpEngine>
#include <QTextBrowser>
   
class PIXQTLIB_EXPORT pixq_HelpBrowser : public QTextBrowser
{
    Q_OBJECT

private:
   static const int _nPointSize = 12;

public:
   pixq_HelpBrowser(QHelpEngine *helpEngine, QWidget *parent = 0);
   virtual QVariant loadResource(int type, const QUrl &url);

private:
    QHelpEngine *_helpEngine;
};

} // namespace 

