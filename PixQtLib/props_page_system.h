#pragma once

#include <QtCore>
#include <QtGui>

#include "pixq_page_image_options.h"

namespace Ui {
    class props_page_system;
}

class props_page_system : public QWidget, public pixq_page_image_options
{
    Q_OBJECT

public:
    explicit props_page_system(QWidget *parent = 0);
    ~props_page_system();
    
private:
    Ui::props_page_system *ui;
    
private:
   void SetMonitorPosition(void);
   void setLanguage(void);

public:
   void setLabels(void);
   void setData(void);
   bool check(void);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_language_english_radio_clicked(bool checked);
    void on_language_japanese_radio_clicked(bool checked);
    void on_fullscreen_side_left_radio_clicked(bool checked);
    void on_fullscreen_side_right_radio_clicked(bool checked);
};
