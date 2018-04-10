#pragma once

#include <QtWidgets>

class website_label_widget : public QLabel
{
    Q_OBJECT

public:
   // mode....what to show
   enum {
      // nothing special
      WebsiteLabelNone = 0,
      // URL address
      WebsiteLabelUrlAddress = 1,
      // Mail address
      WebsiteLabelMailAddress=2,
      // Dev Blog address
      WebsiteLabelBlogAddress=3,
   } WebsiteLabelWidgetMode;

public:
    website_label_widget(QWidget *parent = 0);

private:
    QCursor _defCursor;

    // must be one of WebsiteLabelWidgetMode
    short _sMode;

public:
   void SetMode( short sMode ) { _sMode = sMode; }

protected:
   void mousePressEvent(QMouseEvent *event);
   void enterEvent( QEvent * event );
   void leaveEvent( QEvent * event );
};
