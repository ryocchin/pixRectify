#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class rectify_window;

class rectify_dock : public QDockWidget
{
   Q_OBJECT
 
public:
   enum {
      RectifyDockNone = 0,
      RectifyDockIndex,
      RectifyDockChart,
      RectifyDockProps,
      RectifyDockMonitor,
   } RectifyDockType;

public:
   rectify_dock(const QString & title, QWidget * parent = 0);
   rectify_dock(QWidget * parent = 0);
   ~rectify_dock();
   
public:
   void setMainWindow(rectify_window *pMain) { _pMainWindow = pMain; }
   rectify_window *getMainWindow(void) const { return _pMainWindow; }

private slots:

private:
   // pointer to the main window
   rectify_window *_pMainWindow;
   
   // dock type, one of RectifyDockType
   short _sType;

   // this set to true for the first time when the dock is actually visiable
   bool _bInit;

protected:   
   void resizeEvent( QResizeEvent* );
   void moveEvent( QMoveEvent *eve );
   void showEvent( QShowEvent *eve );
   
public:
   void setType(short sType) { _sType = sType; }


};
