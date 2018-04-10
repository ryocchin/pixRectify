#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_page_image_options.h"

#include "props_page_image.h"
#include "ui_props_page_image.h"

props_page_image::props_page_image(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::props_page_image)
{
    ui->setupUi(this);
    _sPageId = (short)pixq_Properties::ItemCategoryImage;

    return;
}

props_page_image::~props_page_image()
{
   delete ui;

   return;
}

void props_page_image::closeEvent(QCloseEvent * /* event */ )
{
   check( );

   return;
}

void props_page_image::setLabels(void)
{
   QString strLabel;
   pixq_Properties *pEnv = getEnv();
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   setOptionFont((QWidget*)this);

   strLabel = getClassLabel_PC("PropImage", "Resampling", iLang);
   ui->resample_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropImage", "Nearest", iLang);
   ui->nearest_radio->setText(strLabel);

   strLabel = getClassLabel_PC("PropImage", "Bilinear", iLang);
   ui->bilinear_radio->setText(strLabel);

   strLabel = getClassLabel_PC("PropImage", "Interval", iLang);
   ui->image_stat_interval_label->setText(strLabel);
   
   return;
}

void props_page_image::setData(void)
{
   pixq_Properties *pEnv = getEnv();
   QString strValue;

   // *** set current data ***
   
   // texture filter
   setTextureFilter();

   // sampling interval for image statistics/histogram
   
   setInteger(&pEnv->_ImageStatSamplePitch, ui->image_stat_interval_edit);

   ui->image_stat_interval_edit->setValidator(new QIntValidator(1, 20, ui->image_stat_interval_edit));
      
   // --- Done ---
   return;
}

   
bool props_page_image::check(void)
{  
   pixq_Properties *pEnv = getEnv();
   bool bRetCode = false;

   // texture filter
      
   // sampling interval for image statistics/histopram

   if (!getInteger(&pEnv->_ImageStatSamplePitch, ui->image_stat_interval_edit)) {
      QMessageBox::critical( this, "ERROR", "Enter Integer Value." );
      goto PIX_EXIT;
   } 
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// set texture style mode
//
void props_page_image::setTextureFilter( void )
{   
   pixq_Properties *pEnv = getEnv();
   int iTexFilter;

   ui->nearest_radio->setChecked(false);
   ui->bilinear_radio->setChecked(false);

   // texture style
   iTexFilter = pEnv->_ImageTextureFilter.getInteger();

   switch( iTexFilter ) {
   case pixq_Properties::TextureFilterNearest:
      ui->nearest_radio->setChecked(true);
      break;
   case pixq_Properties::TextureFilterLinear:
      ui->bilinear_radio->setChecked(true);
      break;
   }
   
   return;
}

void props_page_image::on_nearest_radio_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();

   if (checked) {
      pEnv->_ImageTextureFilter.Set(pixq_Properties::TextureFilterNearest);
   }

   setTextureFilter();

   return;
}

void props_page_image::on_bilinear_radio_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();

   if (checked) {
      pEnv->_ImageTextureFilter.Set(pixq_Properties::TextureFilterLinear);
   }

   setTextureFilter();

   return;
}

