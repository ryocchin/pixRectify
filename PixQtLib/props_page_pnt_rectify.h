#pragma once

#include <QtGui>
#include <QtWidgets>

#include "pixq_page_image_options.h"

namespace Ui {
   class props_page_pnt_rectify;
}

class props_page_pnt_rectify : public QWidget, public pixq_page_image_options
{
    Q_OBJECT

public:
   explicit props_page_pnt_rectify(QWidget *parent = 0);
   ~props_page_pnt_rectify();

private:
   Ui::props_page_pnt_rectify *ui;

public:
   void setLabels(void);
   void setData( void );
   bool check(void);

protected:
   void closeEvent(QCloseEvent *event);

};

