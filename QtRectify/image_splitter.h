#pragma once

#include <QtWidgets>
#include <QtGui>

class rectify_window;

class ImageSplitter : public QSplitter
{
   Q_OBJECT
 
public:
   ImageSplitter( QWidget * parent = 0 );
   ImageSplitter( Qt::Orientation orientation, QWidget * parent = 0 );
   ~ImageSplitter();

protected:
   void resizeEvent( QResizeEvent* );

public:
   void setMainWindow(rectify_window *pMain) { _pMainWindow = pMain; }
   rectify_window *getMainWindow(void) const  { return _pMainWindow; }

private:
   // pointer to the main window
   rectify_window *_pMainWindow;
};
