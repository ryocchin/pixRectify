#pragma once

#include <QtCore>
#include <QtGui>

#include "pixq_page_image_options.h"

namespace Ui {
    class props_page_image;
}

class props_page_image : public QWidget, public pixq_page_image_options
{
    Q_OBJECT

public:
    explicit props_page_image(QWidget *parent = 0);
    ~props_page_image();

private:
   void setTextureFilter(void);

private:
    Ui::props_page_image *ui;
    
public:
   void setLabels(void);
   void setData( void );
   bool check( void );

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_nearest_radio_clicked(bool checked);
    void on_bilinear_radio_clicked(bool checked);
};
