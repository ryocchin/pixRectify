#pragma once

#include <QtGui>
#include <QtWidgets>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "website_label_widget.h"
#include "ui_pixq_about_dialog.h"

class pixq_about_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit pixq_about_dialog(QWidget *parent = 0);
    ~pixq_about_dialog();
    
private slots:
   void on_ok_button_clicked();

private:
    Ui::pixq_about_dialog *ui;
    
    const pixq_Version *_pVer;

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);

public:
   void Init(const pixq_Version *pVer);
   void Init(const pixq_Version *pVer, int iLanguage);

};