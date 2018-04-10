#pragma once

#include <QtCore>
#include <QtGui>
#include <QtHelp>
#include <QtWidgets>

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>

class PIXQTLIB_EXPORT pixq_HelpViewer : public QDialog
{
    Q_OBJECT

private:
   QMenu *_fileMenu;
   QMenuBar *_menuBar;
   QAction *_closeAction;

   QString _strHelp;
   QString _strID;

private:
   bool _bInit;

   QSplitter *_splitter;
   QHelpEngine *_helpEngine;

public:
   explicit pixq_HelpViewer(const QString strHelp, const QString strID, QWidget *parent = 0);
   ~pixq_HelpViewer();
   
   void setFile(QString strHelp) {
      _strHelp = strHelp;
   }

private: 
   void setHelp(void);   

protected:
   void showEvent(QShowEvent *event);
};

} // namespace 


