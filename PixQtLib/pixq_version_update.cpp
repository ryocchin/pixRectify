#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_version_update.h"

pixq_version_update::pixq_version_update(void)
{
   _UpdateXmlQnam = (QNetworkAccessManager*)NULL;
   _UpdateXmlReply = (QNetworkReply*)NULL;

   return;
}

pixq_version_update::~pixq_version_update()
{
   return;
}

bool pixq_version_update::read( int iMode )
{
   bool bRetCode = false;
   QString strWebFile, strTmpFile;
   QUrl url;
   QNetworkRequest req;
   QString strLabel = "Program Update";

   if (!_UpdateXmlQnam) {
      _UpdateXmlQnam = new QNetworkAccessManager;
   }

   if (_UpdateXmlReply) {
      _UpdateXmlReply->deleteLater();
      _UpdateXmlReply = (QNetworkReply*)NULL;
   }

   _iProgramMode = iMode;

   // get version file name on the net

   strWebFile = GetUpdateVerXmlFile_PC(iMode);

   // get the tentative xml file name to copy the from the web

   strTmpFile = GetTentativeVerXmlFile_PC(iMode);
   
   if (QFile::exists(strTmpFile)) {
      if (!QFile::remove(strTmpFile)) {
         QString strMessage = getClassLabel_PC("Update", "ErrRemove") + "\n" + strTmpFile;
         QMessageBox::critical(NULL, strLabel, strMessage);
         goto PIX_EXIT;
      }
   }


   // download the xml file from the net to the local file

   url.setUrl(strWebFile);

   req.setUrl(url);
   _UpdateXmlReply = _UpdateXmlQnam->get(req);

   connect(_UpdateXmlReply, SIGNAL(finished()), this, SLOT(httpFinished()));
   connect(_UpdateXmlReply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// read file content from the web and save it in the temporary file
//
void pixq_version_update::httpReadyRead(void)
{
   QFile *file = NULL;
   QString strTmpFile;
   QString strLabel = "Program Update";

   strTmpFile = GetTentativeVerXmlFile_PC(_iProgramMode);

   file = new QFile(strTmpFile);
   if (!file->open(QIODevice::Append)) {
      QString strMessage = getClassLabel_PC("Update", "ErrWrite") + "\n" + strTmpFile;
      QMessageBox::information(NULL, strLabel, strMessage);
      goto PIX_EXIT;
   }

   //
   // this slot gets called every time the QNetworkReply has new data.
   // We read all of its new data and write it into the file.
   // That way we use less RAM than when reading it at the finished()
   // signal of the QNetworkReply
   //

   if (!file) {
      QString strMessage = getClassLabel_PC("Update", "ErrWrite") + "\n" + strTmpFile;
      QMessageBox::information(NULL, strLabel, strMessage);
      goto PIX_EXIT;
   }

   file->write(_UpdateXmlReply->readAll());
   file->flush();
   file->close();

PIX_EXIT:
   if (file) {
      delete file;
      file = NULL;
   }
   return;
}

//
// reading XML(latest version) on the web is finished
//
void pixq_version_update::httpFinished(void)
{
   pixq_Version *current_ver = _pCurrent;
   pixq_Version latest_ver;
   QIcon icon = QIcon(":/images/info.png");

   QString strUrl = getProjectTopUrl_PC(_iProgramMode);
   QString strTmpFile = GetTentativeVerXmlFile_PC(_iProgramMode);

   QString strLabel = "Program Update";

   // disconnect signals and slots

   disconnect(_UpdateXmlReply, SIGNAL(finished()), this, NULL);
   disconnect(_UpdateXmlReply, SIGNAL(readyRead()), this, NULL);

   if (_UpdateXmlReply->error()) {
      QString strError = _UpdateXmlReply->errorString();
      QString strMessage = getClassLabel_PC("Update", "ErrConnect") + "\n" + strError;
      QMessageBox::critical(NULL, strLabel, strMessage);
      goto PIX_EXIT;
   }

   // latest version info saved in temporary file

   if (!latest_ver.readXml(strTmpFile)) {
      QString strMessage = getClassLabel_PC("Update", "ErrRead") + "\n" + strTmpFile;
      QMessageBox::critical(NULL, strLabel, strMessage);
      goto PIX_EXIT;
   }

   //
   // check whether the latest version from the file is newer than
   // that of the program that is currently used
   //

   if (*current_ver >= latest_ver) {
      // this is the latest version!
      QMessageBox msgBox;
      QString strVersion = current_ver->GetVersionString();
      QString strMessage = getClassLabel_PC("Update", "HaveLatest");

      msgBox.addButton(QMessageBox::Ok);
      msgBox.setInformativeText(strVersion);
      msgBox.setWindowIcon(icon);
      msgBox.setIcon(QMessageBox::Information);
      msgBox.setText(strMessage);
      msgBox.setWindowTitle(strLabel);
      msgBox.exec();
   }
   else {

      int iReply;

      QMessageBox msgBox;
      QString strVersion;
      QString strCurVersion = current_ver->GetVersionString();
      QString strNewVersion = latest_ver.GetVersionString();
      QString strMessage = getClassLabel_PC("Update", "GetLatest");

      msgBox.addButton(QMessageBox::Ok);

      strVersion = getClassLabel_PC("Update", "LatestVer");
      strVersion = strVersion + strNewVersion;
      strVersion = strVersion + "\n";
      strVersion = strVersion + getClassLabel_PC("Update", "UsedVer");
      strVersion = strVersion + strCurVersion;
      strVersion = strVersion + "\n";
      strVersion = strVersion + "\n";
      strVersion = strVersion + "\n";
      strVersion = strVersion + getClassLabel_PC("Update", "CanGetFromSite");

      msgBox.setInformativeText(strVersion);
      msgBox.setWindowIcon(icon);
      msgBox.setIcon(QMessageBox::Information);
      msgBox.setText(strMessage);
      msgBox.setWindowTitle(strLabel);

      msgBox.setStandardButtons(QMessageBox::Open | QMessageBox::Cancel);

      iReply = msgBox.exec();
      if (QMessageBox::Open == iReply) {
         QDesktopServices::openUrl(QUrl(strUrl));
      }
   }

   //
PIX_EXIT:
   if (_UpdateXmlReply) {
      _UpdateXmlReply->deleteLater();
      _UpdateXmlReply = (QNetworkReply*)NULL;
   }
   if (_UpdateXmlQnam) {
      delete _UpdateXmlQnam;
      _UpdateXmlQnam = (QNetworkAccessManager*)NULL;
   }
   QApplication::restoreOverrideCursor();
   return;
}