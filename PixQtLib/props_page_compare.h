#pragma once

#include <QtCore>
#include <QtGui>

#include "pixq_page_image_options.h"

namespace Ui {
   class props_page_compare;
}

class props_page_compare : public QWidget, public pixq_page_image_options
{
    Q_OBJECT

public:
   explicit props_page_compare(QWidget *parent = 0);
   ~props_page_compare();

private:
   Ui::props_page_compare *ui;

public:
   void setWiperLineColor(void);
   
public:
   void setLabels(void);
   void setData(void);
   bool check(void);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
   void on_WiperBoxColorButton_clicked();
   void on_WiperBoxFixedColorButton_clicked();
};
