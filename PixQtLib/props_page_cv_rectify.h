#pragma once

#include <QtGui>
#include <QtWidgets>

#include "pixq_page_image_options.h"

namespace Ui {
    class props_page_cv_rectify;
}

class props_page_cv_rectify : public QWidget, public pixq_page_image_options
{
    Q_OBJECT

public:
   explicit props_page_cv_rectify(QWidget *parent = 0);
   ~props_page_cv_rectify();

private:
   Ui::props_page_cv_rectify *ui;

public:
   void setLabels(void);
   void setData( void );
   bool check(void);

protected:
   void closeEvent(QCloseEvent *event);

private:
   void setFundamentalMethod(void);

private slots:
    void on_radio_fundamental_method_7_point_clicked(bool checked);
    void on_radio_fundamental_method_8_point_clicked(bool checked);
    void on_radio_fundamental_method_ransac_clicked(bool checked);
    void on_radio_fundamental_method_lmeds_clicked(bool checked);
};

