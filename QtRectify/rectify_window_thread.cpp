#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_cv_common.h"

#include "rectify_panes.h"
#include "rectify_table.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

#include "rectify_window.h"
#include "ui_rectify_window.h"

//
// invoke image loading thread!
//
// notes:
// bRectify:
// true: after points are matched, image rectification is done too
// false: image matching only, no recitfication
//
bool rectify_window::startLoaderThread(bool bRectify)
{
   bool bRetCode = false;
   pixq_FringesTag *pTags = getRectifyTag();

   // create 

   if (_Search_Rectify_Thread) {
      delete _Search_Rectify_Thread;
      _Search_Rectify_Thread = NULL;
   }
   
   _Search_Rectify_Thread = new rectify_search_thread;

   // Connect each Widget to correcponding thread

   connect(_Search_Rectify_Thread, SIGNAL(searchNextTag(int)),
      this, SLOT(searchThreadSearchTag(int)));

   connect(_Search_Rectify_Thread, SIGNAL(searchCompleted(bool)),
      this, SLOT(searchThreadCompleted(bool)));

   _Search_Rectify_Thread->store(pTags);
   _Search_Rectify_Thread->setRectify(bRectify);

   // show progress dialog

   if (!_Search_Rectify_Dialog) {
      _Search_Rectify_Dialog = new rectify_progress_dialog;
      connect(_Search_Rectify_Dialog, SIGNAL(stopPressed()), this,
         SLOT(searchThreadStopPressed()));
   }

   _Search_Rectify_Dialog->show();
   _Search_Rectify_Dialog->raise();
   _Search_Rectify_Dialog->activateWindow();

   _Search_Rectify_Dialog->store(pTags);
   _Search_Rectify_Dialog->init();

   // start the convesion

   _Search_Rectify_Thread->start();

   // to make sure users do not choose unwanted function

   setRectifyMenuState();

   // --- done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

//
// loading thread end
//
void rectify_window::searchThreadCompleted(bool bCanceled)
{
   bool bRectify;

   // hide the dialog

   _Search_Rectify_Dialog->hide();

   if (_Search_Rectify_Thread) {
      bRectify = _Search_Rectify_Thread->getRectify();
      delete _Search_Rectify_Thread;
      _Search_Rectify_Thread = NULL;
   }
   else {
      bRectify = false;
   }

   //
   // enablesearch ins completed
   //
   
   setRectifyMenuState();

   if (bCanceled) {
      qDebug() << "Conversion Processed Cancled by User.";
      goto PIX_EXIT;
   }
   
   //
   // *** get the fundamental matrix and computer disparities
   //

   if (!rectifyAnalyzeTagPoints(true)) {
      goto PIX_EXIT;
   }
   
   if (bRectify) {
      if (!rectifyCalibrate()) {
         goto PIX_EXIT;
      }
   }

PIX_EXIT:
   return;
}

//
// stop button pressed on the progress dialog
//
void rectify_window::searchThreadStopPressed(void)
{
   QString strMessage;

   if (!_Search_Rectify_Thread) {
      goto PIX_EXIT;
   }

   // freeze the thread

   _Search_Rectify_Thread->pause();

   _Search_Rectify_Dialog->lower();
   _Search_Rectify_Dialog->hide();
   _Search_Rectify_Dialog->setVisible(false);

   update();

   // ask user 

   strMessage.sprintf("Do you want to stop matching?");

   if (QMessageBox::Yes == QMessageBox::question(this, getApplication(), strMessage,
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No)) {

      qDebug() << "Loading Canceled....";

      // stop the loading thread and return false

      qDebug() << "Stopping the load thread...";
      _Search_Rectify_Thread->stop();

      qDebug() << "Terminating the load thread...";
      _Search_Rectify_Thread->terminate();

      qDebug() << "Waiting for the load thread...";
      _Search_Rectify_Thread->wait(2500);

      _Search_Rectify_Dialog->hide();
      update();

   }
   else {
      _Search_Rectify_Thread->resume();
      _Search_Rectify_Dialog->show();
      _Search_Rectify_Dialog->raise();
   }

   setRectifyMenuState();

PIX_EXIT:
   return;
}

//
// convert frame and store the output image
// called from loader thread
//
void rectify_window::searchThreadSearchTag(int iTag)
{
   QString strMessage;
   pixq_FringesTag *pTags = getRectifyTag();
   int nTagRows = pTags->getTagRows();
   int nTagCols = pTags->getTagCols();
   int nTags = nTagRows*nTagCols;

#ifdef _DEBUG
   pixq_FringeTag *pTag;
   int iX, iY, iRightX, iRightY;
   double dCorr;
#endif // _DEBUG

   if (!_Search_Rectify_Thread) {
      goto PIX_EXIT;
   }

#ifdef _DEBUG
   //qDebug() << "--- EMIT! Loading Tag " << iTag << "." << nTags << "....";
#endif // _DEBUG

   // load input image into both panes

   // --- move to the frame ---

   if (!rectifyImageMatchTag(iTag)) {
      qDebug() << "ERROR! Failed to Match Tag " << iTag + 1 << "/" << nTags;
      _Search_Rectify_Thread->restart();
      goto PIX_EXIT;
   }

#ifdef _DEBUG
   //
   // show results
   //
   pTag = pTags->getNthTag(iTag);
   iX = pTag->getXTag();
   iY = pTag->getYTag();
   iRightX = pTag->getRightXTag();
   iRightY = pTag->getRightYTag();
   dCorr = pTag->getCorrVal();
   strMessage.sprintf("Matched %2d/%2d : L(%4d,%4d)->R(%4d,%4d) : %5.2f",
      iTag + 1, nTags,
      iX, iY,
      iRightX, iRightY, dCorr);
   qDebug() << strMessage;
#endif // _DEBUG

   // show the progress on dialog

   _Search_Rectify_Dialog->tagEnd(iTag);
   _Search_Rectify_Dialog->update();

   if (_Search_Rectify_Thread->isPaused()) {
      _Search_Rectify_Dialog->lower();
   }
   else {
      _Search_Rectify_Dialog->show();
      _Search_Rectify_Dialog->raise();
   }

   _Search_Rectify_Thread->restart();

   update();

PIX_EXIT:
   return;
}
