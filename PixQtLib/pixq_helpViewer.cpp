#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework; 

#include "pixq_HelpBrowser.h"
#include "pixq_HelpViewer.h"

pixq_HelpViewer::pixq_HelpViewer(const QString strHelp, const QString strID, QWidget *parent) :
    QDialog(parent)
{
   QIcon icon;
   QString strLabel;  

   _bInit = false;
   _strHelp = strHelp;
   _strID = strID;

   //

   strLabel = getClassLabel_PC("Control", "Help");
   setWindowTitle(strLabel);

   icon = QIcon(":/images/help-browser.png");
   setWindowIcon(icon);
   
    return;
}

pixq_HelpViewer::~pixq_HelpViewer()
{
   return;
}

//
// strHelp: name of the collection file
// strID: Id of the page to be shown at first
//
// notes:
// Id of the first page to show is set in qhp file as
//
// <keywords>
//    <keyword name="plants" id="plants" ref="plants.html" />
//    <keyword name="temperature" id="temperature" ref="temperature.html" />
//    <keyword name="rain" id="rain" ref="rain.html" />
//    <keyword name="time" id="time" ref="time.html" />
//    <keyword name="amount" id="amount" ref="amount.html" />
//    <keyword name="source" id="source" ref="source.html" />
//    <keyword name="filtering" id="filtering" ref="filter.html" />
// < /keywords>
//
void pixq_HelpViewer::setHelp( void )
{
   pixq_HelpBrowser *helpBrowser = NULL;
   QHelpContentWidget *contentWidget = NULL;
   QHelpIndexModel *indexModel = NULL;

   QList<int> sizes;
   int nWidth[2], nTotal;
   QString strLabel;

   //QString strHelp;
   //strHelp = QFileInfo(QCoreApplication::applicationDirPath()).filePath();
   //strHelp += QDir::separator();
   //strHelp += QLatin1String("hikari_index.qhc");

   _helpEngine = new QHelpEngine(_strHelp);

   if (_helpEngine->setupData()) {
      qDebug() << "setupData OK";
   }
   else {
      qDebug() << "setupData Failed!";
      QString strError;
      strError = "Failed to Read " + _strHelp;
      QMessageBox::information(NULL, "Help", strError);
   }

   contentWidget = _helpEngine->contentWidget();
   indexModel = _helpEngine->indexModel();
   helpBrowser = new pixq_HelpBrowser(_helpEngine);

   _splitter = new QSplitter(Qt::Horizontal);
   //splitter->setFixedSize(1000, 800);

   _splitter->addWidget(contentWidget);
   _splitter->addWidget(helpBrowser);

   //_splitter->insertWidget(0, contentWidget);
   //_splitter->insertWidget(1, helpBrowser);
    
   nTotal = _splitter->width();
   nWidth[0] = nTotal * 25 / 100;
   nWidth[1] = nTotal - nWidth[0];
   sizes.clear();
   sizes.push_back(nWidth[0]);
   sizes.push_back(nWidth[1]);
   _splitter->setSizes(sizes);

   QObject::connect( _helpEngine->contentWidget(), SIGNAL(linkActivated(const QUrl &)),
      helpBrowser, SLOT(setSource(const QUrl &)));

   _splitter->show();
   
   // find the first page to show
   // it is thepage that has the specified ID

   if (!_strID.isEmpty()) {
      QMap<QString, QUrl> links = _helpEngine->linksForIdentifier(_strID);
      int nCount = links.count();
      if (0 < nCount) {
         QString strValue = (links.constBegin().value()).toString();
         helpBrowser->setSource(links.constBegin().value());
      }
   }

   // set menu

   strLabel = getClassLabel_PC("Control", "Menu");
   _fileMenu = new QMenu(strLabel, this);

   strLabel = getClassLabel_PC("Menu", "Close");
   _closeAction = _fileMenu->addAction(strLabel);

   connect(_closeAction, SIGNAL(triggered()), this, SLOT(hide()));

   _menuBar = new QMenuBar;
   _menuBar->addMenu(_fileMenu);

   //

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->setMenuBar(_menuBar);
   mainLayout->addWidget(_splitter);

   setLayout(mainLayout);

   return;
}


void pixq_HelpViewer::showEvent(QShowEvent * /* event */)
{
   if (_bInit) {
      goto PIX_EXIT;
   }
   
   // set help

   setHelp();
   _bInit = true;

PIX_EXIT:
   return;
}
