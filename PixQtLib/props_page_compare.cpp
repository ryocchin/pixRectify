#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_page_image_options.h"

#include "props_page_compare.h"
#include "ui_props_page_compare.h"

props_page_compare::props_page_compare(QWidget *parent) :
QWidget(parent),
ui(new Ui::props_page_compare)
{
   ui->setupUi(this);
   _sPageId = (short)pixq_Properties::ItemCategoryCompare;

   return;
}

props_page_compare::~props_page_compare()
{
   delete ui;

   return;
}

void props_page_compare::closeEvent(QCloseEvent * /* event */)
{
   check();

   return;
}

void props_page_compare::setLabels(void)
{
   QString strLabel;
   pixq_Properties *pEnv = getEnv();
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   setOptionFont((QWidget*)this);

   strLabel = getClassLabel_PC("PropCompare", "Draw", iLang);
   ui->draw_line_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropCompare", "Yes", iLang);
   ui->DrawWipeBoxDrawCheck->setText(strLabel);

   strLabel = getClassLabel_PC("PropCompare", "Color", iLang);
   ui->line_color_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropCompare", "Fixed", iLang);
   ui->line_fixed_color_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropCompare", "Radius", iLang);
   ui->scope_radius_label->setText(strLabel);

   return;
}

//
// set current data
//
void props_page_compare::setData(void)
{
   pixq_Properties *pEnv = getEnv();

   // *** set current data ***

   // target frame rate

   // sampling frame number to measure frame rate

   // sleep milliseconds after each frame, manually set to fixed value

   // use fixed sleep time? instead of statically optimized sleep time?

   // tolerance for difference between real frame rate and target 

   // *** 2 ***

   // show wiper/box as line

   setBool(&pEnv->_CompareDrawWiperLine, ui->DrawWipeBoxDrawCheck);

   // wiper/box color

   setWiperLineColor();

   // box(scope) radius, pixels on screen

   setInteger(&pEnv->_CompareBoxRadius, ui->CompareBoxRadiusEdit);
   
   // --- Done ---
   return;
}

bool props_page_compare::check(void)
{
   bool bRetCode = false;
   pixq_Properties *pEnv = getEnv();

   // *** set current data ***

   // target frame rate
   
   // number of frame to get statistics
   
   // sleep milliseconds after each frame, manually set to fixed value
   
   // use fixed sleep time? instead of statically optimized sleep time?
   
   // tolerance for difference between real frame rate and target 
   
   // *** 2 ***

   // show wiper/box as line

   getBool(&pEnv->_CompareDrawWiperLine, ui->DrawWipeBoxDrawCheck);
   
   // wiper/box color

   // already set by button

   // box(scope) radius, pixels on screen

   if (!getInteger(&pEnv->_CompareBoxRadius, ui->CompareBoxRadiusEdit)) {
      QMessageBox::critical(this, "ERROR", "Enter Integer Value.");
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

void props_page_compare::setWiperLineColor(void)
{
   pixq_Properties *pEnv = getEnv();
   QColor colValue;

   // line color
   
   colValue = pEnv->_CompareWiperLineColor.getColor();

   ui->WiperBoxColorBox->setText(colValue.name());
   ui->WiperBoxColorBox->setPalette(QPalette(colValue));
   ui->WiperBoxColorBox->setAutoFillBackground(true);

   // fixed line color

   colValue = pEnv->_CompareFixedWiperLineColor.getColor();

   ui->WiperBoxFixedColorBox->setText(colValue.name());
   ui->WiperBoxFixedColorBox->setPalette(QPalette(colValue));
   ui->WiperBoxFixedColorBox->setAutoFillBackground(true);
    
   return;
}

void props_page_compare::on_WiperBoxColorButton_clicked()
{
   pixq_Properties *pEnv = getEnv();
   int iRet;
   QColorDialog dlg;
   QColor colValue = pEnv->_CompareWiperLineColor.getColor();

   dlg.setCurrentColor(colValue);

   iRet = dlg.exec();
   if (QDialog::Accepted != iRet) {
      goto PIX_EXIT;
   }

   colValue = dlg.currentColor();
   pEnv->_CompareWiperLineColor.Set(colValue);

   setWiperLineColor();

PIX_EXIT:
   return;
}

void props_page_compare::on_WiperBoxFixedColorButton_clicked()
{
   pixq_Properties *pEnv = getEnv();
   int iRet;
   QColorDialog dlg;
   QColor colValue = pEnv->_CompareFixedWiperLineColor.getColor();

   dlg.setCurrentColor(colValue);

   iRet = dlg.exec();
   if (QDialog::Accepted != iRet) {
      goto PIX_EXIT;
   }

   colValue = dlg.currentColor();
   pEnv->_CompareFixedWiperLineColor.Set(colValue);

   setWiperLineColor();

PIX_EXIT:
   return;
}
