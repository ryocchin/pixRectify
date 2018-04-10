#pragma once

#include <QtCore>
#include <QtGui>
#include <QApplication>
//#include <QtOpenGL>

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>

#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

class rectify_search_thread : public QThread
{
   Q_OBJECT

private:
   pixq_FringesTag *_pRectifyTags;

private:

   volatile bool _bIsPaused;

private:
   volatile bool _bSearchStopped;

   QMutex _search_mutex;

   QWaitCondition _searching_condition;
   
   bool _bRectify;

public:
   explicit rectify_search_thread(QObject *parent = 0);
   ~rectify_search_thread(void);

   void setMessage( const QString &strMessage );
   void stop( void );

   void store(pixq_FringesTag *pTags) { _pRectifyTags = pTags; }

   void restart( void );
   void pause(void);
   void resume(void);
   void setRectify(bool bRectify) {
      _bRectify = bRectify;
   }
   bool getRectify(void ) const { return _bRectify; }
   
   bool isPaused(void) const { return _bIsPaused; }

signals:
   void searchNextTag(int);
   void searchCompleted(bool bCanceled);
   
protected:
   void run( void );
};
