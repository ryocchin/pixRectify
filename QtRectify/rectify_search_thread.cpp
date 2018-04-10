#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

rectify_search_thread::rectify_search_thread(QObject *parent) :
    QThread(parent)
{
   _bSearchStopped = false;
   _bIsPaused = false;

   _bRectify = false;

   return;
}

rectify_search_thread::~rectify_search_thread(void)
{
   _search_mutex.lock();
   _searching_condition.wakeOne();
   _search_mutex.unlock();

   wait();

   return;
} 

void rectify_search_thread::restart(void)
{
   _searching_condition.wakeOne();

   return;
}

void rectify_search_thread::stop(void)
{
   _search_mutex.unlock();
   _searching_condition.wakeOne();

   _bSearchStopped = true;

   return; 
}

void rectify_search_thread::pause(void)
{
   _search_mutex.lock();
   
   _bIsPaused = true;

   return;
} 

void rectify_search_thread::resume(void)
{
   _search_mutex.unlock();
   
   _bIsPaused = false;

   return;
}

void rectify_search_thread::run(void)
{
   int iTag, i, j;
   int nTagRows = _pRectifyTags->getTagRows();
   int nTagCols = _pRectifyTags->getTagCols();

   _bSearchStopped = false;

   // --- show progress panel ---

   for (i = 0; i < nTagRows; i++) {
      for (j = 0; j < nTagCols; j++) {

         iTag = i * nTagCols + j;

         _search_mutex.lock();
         emit searchNextTag(iTag);
         _searching_condition.wait(&_search_mutex);

         _search_mutex.unlock();

         if (_bSearchStopped) {
            // end
            goto DMR_EXIT;
         }
      }
   }

DMR_EXIT:
   emit searchCompleted(_bSearchStopped);
   return;
}
