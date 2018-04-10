#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_page_image_options.h"

#include "props_page_cv_rectify.h"
#include "ui_props_page_cv_rectify.h"

props_page_cv_rectify::props_page_cv_rectify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::props_page_cv_rectify)
{
    ui->setupUi(this);    
    _sPageId = pixq_Properties::ItemCategoryCvRectify;

    return;
}

props_page_cv_rectify::~props_page_cv_rectify()
{
   delete ui;

   return;
}

void props_page_cv_rectify::setLabels(void)
{
   QString strLabel;
   pixq_Properties *pEnv = getEnv();
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   setOptionFont((QWidget*)this);

   strLabel = getClassLabel_PC("PropCvRectify", "Rotation", iLang);
   ui->roration_group_box->setTitle(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Method", iLang);
   ui->radio_fundamental_method_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Method_7", iLang);
   ui->radio_fundamental_method_7_point->setText(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Method_8", iLang);
   ui->radio_fundamental_method_8_point->setText(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Method_RANSAC", iLang);
   ui->radio_fundamental_method_ransac->setText(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Method_LMEDS", iLang);
   ui->radio_fundamental_method_lmeds->setText(strLabel);
   
   strLabel = getClassLabel_PC("PropCvRectify", "Distance", iLang);
   ui->max_distance_ransac_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Limit", iLang);
   ui->confidence_limit_ransac_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Disparity", iLang);
   ui->disparity_threshold_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Files", iLang);
   ui->files_group_box->setTitle(strLabel);

   strLabel = getClassLabel_PC("PropCvRectify", "Suffix", iLang);
   ui->image_file_suffix_label->setText(strLabel);
   
   return;
}

void props_page_cv_rectify::closeEvent(QCloseEvent * /* event */)
{
   check();

   return;
}

//
// set current data
//
void props_page_cv_rectify::setData(void)
{
   pixq_Properties *pEnv = getEnv();

   // *** rectification method - OpenCV ***

   // algorithm to compute fundamental matrix, one of OpenCvFundamentalMatrixMethod

   setFundamentalMethod( );

   // max distance from point to epipolar line in pixels
   // used in ransac
   set2Double(&pEnv->_RectifyCvFundamentalDistance, ui->max_distance_ransac_edit);

   // desirable level of confidence(probability) that estimaed matrix is correct
   // used in ransac and lmeds
   set2Double(&pEnv->_RectifyCvFundamentalConfidence, ui->confidence_limit_ransac_edit);

   // threshold to filter out the outliers ion OpenCV stereoRectifyUncalibrated function
   set2Double(&pEnv->_RectifyCvRectifyThreshold, ui->disparity_threshold_edit);

   // *** file names ***

   // default suffix to be added to output file 
   setString(&pEnv->_RectifyRectifiedFileSuffix, ui->image_file_suffix_edit);
   
   // --- Done ---
   return;
}
   
bool props_page_cv_rectify::check(void)
{  
   bool bRetCode = false;
   pixq_Properties *pEnv = getEnv();
   
   // *********************
   // *** rectification ***
   // *********************
   
   // *** rectification method - OpenCV ***

   // algorithm to compute fundamental matrix, one of OpenCvFundamentalMatrixMethod
   // set by radio

   // max distance from point to epipolar line in pixels
   // used in ransac

   if (!getDouble(&pEnv->_RectifyCvFundamentalDistance, ui->max_distance_ransac_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Real Value.");
      goto PIX_EXIT;
   }

   // desirable level of confidence(probability) that estimaed matrix is correct
   // used in ransac and lmeds

   if (!getDouble(&pEnv->_RectifyCvFundamentalConfidence, ui->confidence_limit_ransac_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Real Value.");
      goto PIX_EXIT;
   }

   // threshold to filter out the outliers ion OpenCV stereoRectifyUncalibrated function

   if (!getDouble(&pEnv->_RectifyCvRectifyThreshold, ui->disparity_threshold_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Real Value.");
      goto PIX_EXIT;
   }

   // *** file names ***

   // default suffix to be added to output file 
   if (isEmpty(ui->image_file_suffix_edit)) {
      focusEdit(ui->image_file_suffix_edit);
      QMessageBox::critical(this, "ERROR", "Enter Some Suffix.");
      goto PIX_EXIT;
   }

   getString(&pEnv->_RectifyRectifiedFileSuffix, ui->image_file_suffix_edit);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// set texture style mode
//
void props_page_cv_rectify::setFundamentalMethod(void)
{
   pixq_Properties *pEnv = getEnv();
   int iMethod;

   ui->radio_fundamental_method_7_point->setChecked( false );
   ui->radio_fundamental_method_8_point->setChecked( false );
   ui->radio_fundamental_method_ransac->setChecked( false );
   ui->radio_fundamental_method_lmeds->setChecked( false );

   // bible version

   iMethod = pEnv->_RectifyCvFundamentalMethod.getInteger();

   switch( iMethod ) {
   case pixq_Properties::FundamentalMethod7Point:
      ui->radio_fundamental_method_7_point->setChecked( true );
      break;
   case pixq_Properties::FundamentalMethod8Point:
      ui->radio_fundamental_method_8_point->setChecked( true );
      break;
   case pixq_Properties::FundamentalMethodRansac:
      ui->radio_fundamental_method_ransac->setChecked( true );
      break;
   case pixq_Properties::FundamentalMethodLmeds:
      ui->radio_fundamental_method_lmeds->setChecked( true );
      break;
   }

   return;
}

void props_page_cv_rectify::on_radio_fundamental_method_7_point_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();
   int iMethod = pixq_Properties::FundamentalMethod7Point;

   if( checked ) {
      pEnv->_RectifyCvFundamentalMethod.Set( iMethod );
      setFundamentalMethod();
   }

   return;
}

void props_page_cv_rectify::on_radio_fundamental_method_8_point_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();
   int iMethod = pixq_Properties::FundamentalMethod8Point;

   if( checked ) {
      pEnv->_RectifyCvFundamentalMethod.Set( iMethod );
      setFundamentalMethod();
   }

   return;
}

void props_page_cv_rectify::on_radio_fundamental_method_ransac_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();
   int iMethod = pixq_Properties::FundamentalMethodRansac;

   if( checked ) {
      pEnv->_RectifyCvFundamentalMethod.Set( iMethod );
      setFundamentalMethod();
   }

   return;
}

void props_page_cv_rectify::on_radio_fundamental_method_lmeds_clicked(bool checked)
{
   pixq_Properties *pEnv = getEnv();
   int iMethod = pixq_Properties::FundamentalMethodLmeds;

   if( checked ) {
      pEnv->_RectifyCvFundamentalMethod.Set( iMethod );
      setFundamentalMethod();
   }

   return;
}
