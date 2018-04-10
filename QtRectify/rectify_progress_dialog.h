#pragma once

#include <QtCore>
#include <QDialog>
#include <QtWidgets>

#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "ui_rectify_progress_dialog.h"

namespace Ui {
    class rectify_progress_dialog;
}

class flow_control;

class rectify_progress_dialog : public QDialog
{
    Q_OBJECT

private:
       pixq_FringesTag *_pRectifyTags;

private:
   Ui::rectify_progress_dialog *ui;
   
public:
   explicit rectify_progress_dialog(QWidget *parent = 0);
   ~rectify_progress_dialog();

private slots:
    void on_progress_stop_button_clicked();

signals:
   void stopPressed( void );

public:
   void store(pixq_FringesTag *pTags) { _pRectifyTags = pTags; }
   void tagEnd(int  iCol);
   void init( void );
};


