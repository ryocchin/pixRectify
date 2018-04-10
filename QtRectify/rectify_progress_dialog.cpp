#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_cv_common.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

rectify_progress_dialog::rectify_progress_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rectify_progress_dialog)
{
   Qt::WindowFlags flags = windowFlags();

    ui->setupUi(this);
    
    // hide X and ? buttons

    flags = flags | Qt::CustomizeWindowHint;
    flags = flags ^ Qt::WindowCloseButtonHint;
    flags = flags ^ Qt::WindowContextHelpButtonHint;

    setWindowFlags(flags);

    return;
}

rectify_progress_dialog::~rectify_progress_dialog()
{
    delete ui;

    return;
}

void rectify_progress_dialog::init(void)
{
   int nTagRows = _pRectifyTags->getTagRows();
   int nTagCols = _pRectifyTags->getTagCols();
   int nTags = nTagRows * nTagCols;

   QString strValue;
   
   ui->progress_bar->setRange(0, nTags - 1);
   ui->progress_bar->setValue(0);
   
   strValue.sprintf("Searching %d Tags", nTags );   
   ui->loading_frame_label->setText( strValue );

   return;
}

void rectify_progress_dialog::tagEnd(int iTag)
{
   int nTagRows = _pRectifyTags->getTagRows();
   int nTagCols = _pRectifyTags->getTagCols();
   int nTags = nTagRows * nTagCols;
   QString strValue;

   ui->progress_bar->setValue(iTag);
   
   //

   strValue.sprintf("Matched %d/%d Tags", iTag+1, nTags);
   ui->loading_frame_label->setText( strValue );

   update();

   return;
}

void rectify_progress_dialog::on_progress_stop_button_clicked()
{
   qDebug() << "[rectify_progress_dialog::on_progress_stop_button_clicked]Emitting stopPressed";

   emit stopPressed();

   return;
}
