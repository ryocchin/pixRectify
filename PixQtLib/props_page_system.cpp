#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_page_image_options.h"

#include "props_page_system.h"
#include "ui_props_page_system.h"

props_page_system::props_page_system(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::props_page_system)
{
    ui->setupUi(this);    
    _sPageId = (short)pixq_Properties::ItemCategorySystem;

    return;
}

props_page_system::~props_page_system()
{
   delete ui;

   return;
}

void props_page_system::closeEvent(QCloseEvent * /* event */ )
{
   check();

   return;
}

void props_page_system::setLabels(void)
{
   QString strLabel;
   pixq_Properties *pEnv = getEnv();
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   setOptionFont((QWidget*)this);

   strLabel = getClassLabel_PC("PropSystem", "Language", iLang);
   ui->language_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropSystem", "English", iLang);
   ui->language_english_radio->setText(strLabel);

   strLabel = getClassLabel_PC("PropSystem", "Japanese", iLang);
   ui->language_japanese_radio->setText(strLabel);

   strLabel = getClassLabel_PC("PropSystem", "Fullscreen", iLang);
   ui->fullscreen_side_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropSystem", "Left", iLang);
   ui->fullscreen_side_left_radio->setText(strLabel);

   strLabel = getClassLabel_PC("PropSystem", "Right", iLang);
   ui->fullscreen_side_right_radio->setText(strLabel);

   return;
}

//
// set current data
//

void props_page_system::setData( void )
{
   // *** set current data ***

   // interface language
   // must be one of QLocale::​Language stored as integer

   setLanguage();

   // screen number to use for dual view configuration, 0(left) or 1(right)
   
   SetMonitorPosition( );

   // --- Done ---
   return;
}
   
bool props_page_system::check( void )
{  
   bool bRetCode = false;

   // interface language
   // must be one of QLocale::​Language stored as integer
   // done

   // screen number to use for dual view configuration, 0(left) or 1(right)
   // done

   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

void props_page_system::setLanguage(void)
{   
   pixq_Properties *pEnv = getEnv();
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   ui->language_english_radio->setChecked(false);
   ui->language_japanese_radio->setChecked(false);
   
   switch (iLang) {
   case QLocale::English:
      ui->language_english_radio->setChecked(true);
      break;
   case QLocale::Japanese:
      ui->language_japanese_radio->setChecked(true);
      break;
   }
   
   return;
}

void props_page_system::SetMonitorPosition(void)
{
   pixq_Properties *pEnv = getEnv();
   int iSide;

   ui->fullscreen_side_left_radio->setChecked(false);
   ui->fullscreen_side_right_radio->setChecked(false);

   iSide = pEnv->_SystemMonitorPosition.getInteger();

   switch (iSide) {
   case 0:
      ui->fullscreen_side_left_radio->setChecked(true);
      break;
   case 1:
      ui->fullscreen_side_right_radio->setChecked(true);
      break;
   }

   return;
}


void props_page_system::on_language_english_radio_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();
   int iLang = QLocale::English;

   if (checked) {
      pEnv->_SystemInterfaceLanguage.Set(iLang);
   }

   setLanguage();

   return;
}

void props_page_system::on_language_japanese_radio_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();
   int iLang = QLocale::Japanese;

   if (checked) {
      pEnv->_SystemInterfaceLanguage.Set(iLang);
   }

   setLanguage();

   return;
}

void props_page_system::on_fullscreen_side_left_radio_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();
   int iSide = 0;

   if (checked) {
      pEnv->_SystemMonitorPosition.Set(iSide);
   }

   SetMonitorPosition();

   return;
}

void props_page_system::on_fullscreen_side_right_radio_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();
   int iSide = 1;

   if (checked) {
      pEnv->_SystemMonitorPosition.Set(iSide);
   }

   SetMonitorPosition();

   return;
}
