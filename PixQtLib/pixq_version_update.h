#pragma once

#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QtWidgets>
#include <QtHelp>

#include <QNetworkAccessManager>
#include <QSqlTableModel>
#include <QSqlDatabase>

namespace _pix_plot_qt_framework {
   
#include <pixqtlib_global.h>
   
class pixq_Version;

class PIXQTLIB_EXPORT pixq_version_update : public QObject
{
    Q_OBJECT

public:
   explicit pixq_version_update(void);
   ~pixq_version_update();


   // for getting XML file from the net
   // to check the sofware update
private:
   QNetworkAccessManager *_UpdateXmlQnam;
   QNetworkReply *_UpdateXmlReply;

   pixq_Version *_pCurrent;

   int _iProgramMode;

private slots:
    void httpFinished( void );
    void httpReadyRead( void );

public:
   bool read(int iMode);
   void setCurrent(pixq_Version *pCur) { _pCurrent = pCur; }

};

} // namespace 


