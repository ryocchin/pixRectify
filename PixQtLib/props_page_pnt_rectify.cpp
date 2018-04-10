#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_page_image_options.h"

#include "props_page_pnt_rectify.h"
#include "ui_props_page_pnt_rectify.h"

props_page_pnt_rectify::props_page_pnt_rectify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::props_page_pnt_rectify)
{
    ui->setupUi(this);    
    _sPageId = pixq_Properties::ItemCategoryPntRectify;

    return;
}

props_page_pnt_rectify::~props_page_pnt_rectify()
{
   delete ui;

   return;
}

void props_page_pnt_rectify::setLabels(void)
{
   QString strLabel;
   pixq_Properties *pEnv = getEnv();
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();
   
   setOptionFont((QWidget*)this);

   // contriol points

   strLabel = getClassLabel_PC("PropPntRectify", "Points", iLang);
   ui->control_points_group_box->setTitle(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Number", iLang);
   ui->rectify_point_number_label->setText(strLabel);

   //strLabel = getClassLabel_PC("PropPntRectify", "Exclude", iLang);
   //ui->rectify_exclude_rate_edge_label->setText(strLabel);

   //strLabel = getClassLabel_PC("PropPntRectify", "ExcludeTip", iLang);
   //ui->rectify_exclude_rate_edge_edit->setToolTip(strLabel);

   // strLabel = getClassLabel_PC("PropPntRectify", "Feature", iLang);
   // ui->stereo_feature_group_box->setTitle(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Before", iLang);
   ui->rectify_snap_feature_point_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Snap", iLang);
   ui->rectify_snap_feature_point_check->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Search", iLang);
   ui->rectify_feature_search_range_label->setText(strLabel);
      
   // matching

   strLabel = getClassLabel_PC("PropPntRectify", "Matching", iLang);
   ui->matching_group_box->setTitle(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Pyramid", iLang);
   ui->rectify_use_pyramid_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Use", iLang);
   ui->rectify_use_pyramid_check->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Mado", iLang);
   ui->rectify_soukan_mado_radius_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Stdev", iLang);
   ui->rectify_min_stdev_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Gray", iLang);
   ui->rectify_gray_scale_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "GraCheck", iLang);
   ui->rectify_gray_scale_check->setText(strLabel);
   
   //strLabel = getClassLabel_PC("PropPntRectify", "Low", iLang);
   //ui->rectify_soukan_low_bnd_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "High", iLang);
   ui->rectify_soukan_high_bnd_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Horizontak", iLang);
   ui->rectify_max_hor_disparity_label->setText(strLabel);

   strLabel = getClassLabel_PC("PropPntRectify", "Vertical", iLang);
   ui->rectify_max_ver_disparity_label->setText(strLabel);

   return;
}

void props_page_pnt_rectify::closeEvent(QCloseEvent * /* event */)
{
   check();

   return;
}

//
// set current data
//
void props_page_pnt_rectify::setData(void)
{
   pixq_Properties *pEnv = getEnv();

   // *** set current data ***

   // --- control points ---

   // rectification control grid intervals

   setInteger(&pEnv->_RectifyControlPointNumber, ui->rectify_point_number_edit);

   // width of the area of image not to be included in matching, in pixels on original image
   // %-age to the width of the image

   //setInteger(&pEnv->_RectifyExcludeRateEdge, ui->rectify_exclude_rate_edge_edit);

   // --- stereo features ---

   // snap input point to nearest feature point?
    
   setBool(&pEnv->_RectifySnapFeaturePoint, ui->rectify_snap_feature_point_check);

   // radius of search rectangle to select stereo feature near the given point   
   setInteger(&pEnv->_RectifyFeatureSearchRange, ui->rectify_feature_search_range_edit);

   // *** conditions for matching left to right ****

   // Use Image pyramid for stereo matching
   setBool(&pEnv->_RectifyMatchUsePyramid, ui->rectify_use_pyramid_check);
      
   // Correlation window radius, on resampled image   
   setInteger(&pEnv->_RectifySoukanMadoRadius, ui->rectify_soukan_mado_radius_edit);

   // minimum value for standard deviation to analyze correlation
   set2Double(&pEnv->_RectifyMinStdDev, ui->rectify_min_stdev_edit);

   // match grayscale image or RGB three channels
   setBool(&pEnv->_RectifyGrayScale, ui->rectify_gray_scale_check);

   // Correlation value, boundary between low and middle correlation
   set2Double(&pEnv->_RectifySoukanHighBoundary, ui->rectify_soukan_high_bnd_edit);

   // max disparity to the left, pixel number on original image
   setInteger(&pEnv->_RectifyMaxHorizontalDisparity, ui->rectify_max_hor_disparity_edit);
   setInteger(&pEnv->_RectifyMaxVerticalDisparity, ui->rectify_max_ver_disparity_edit);

   // --- Done ---
   return;
}
   
bool props_page_pnt_rectify::check(void)
{  
   bool bRetCode = false;
   pixq_Properties *pEnv = getEnv();
   
   // *********************
   // *** rectification ***
   // *********************

   // *** conditions to gerenare sample control points ****

   // rectification control grid intervals

   if (!getInteger(&pEnv->_RectifyControlPointNumber, ui->rectify_point_number_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Integer Value.");
      ui->rectify_point_number_edit->setFocus(Qt::MouseFocusReason);
      goto PIX_EXIT;
   } 

   // width of the area of image not to be included in matching, in pixels on original image
   // %-age to the width of the image

   //if (!getInteger(&pEnv->_RectifyExcludeRateEdge, ui->rectify_exclude_rate_edge_edit)) {
   //   if (pEnv->_RectifyExcludeRateEdge.getRange()) {
   //      int iMinValue = pEnv->_RectifyExcludeRateEdge.getIntMin();
   //      int iMaxValue = pEnv->_RectifyExcludeRateEdge.getIntMax();
   //      QMessageBox::critical(this, "ERROR", "Enter Integer Value within Value Range.");
   //   }
   //   else {
   //      QMessageBox::critical(this, "ERROR", "Enter Integer Value.");
   //   }
   //   goto PIX_EXIT;
   //} 
   
   // --- stereo features ---

   // snap input point to nearest feature point?
    
   getBool(&pEnv->_RectifySnapFeaturePoint, ui->rectify_snap_feature_point_check);

   // radius of search rectangle to select stereo feature near the given point
   
   if (!getInteger(&pEnv->_RectifyFeatureSearchRange, ui->rectify_feature_search_range_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Integer Value.");
      goto PIX_EXIT;
   } 

   // *** conditions for matching left to right ****

   // Use Image pyramid for stereo matching

   getBool(&pEnv->_RectifyMatchUsePyramid, ui->rectify_use_pyramid_check);

   // Radius of Matching window to match control points
   
   if (!getInteger(&pEnv->_RectifySoukanMadoRadius, ui->rectify_soukan_mado_radius_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Integer Value.");
      goto PIX_EXIT;
   } 

   // max value for standard deviation to analyze correlation
      
   if (!getDouble(&pEnv->_RectifyMinStdDev, ui->rectify_min_stdev_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Real Value.");
      goto PIX_EXIT;
   } 

   // match grayscale image or RGB three channels
   
   getBool(&pEnv->_RectifyGrayScale, ui->rectify_gray_scale_check);

   // Correlation value, boundary between middle and high correlation
   
   if (!getDouble(&pEnv->_RectifySoukanHighBoundary, ui->rectify_soukan_high_bnd_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Real Value.");
      goto PIX_EXIT;
   } 

   // max horizontal disparity, pixel number on original image
     
   if (!getInteger(&pEnv->_RectifyMaxHorizontalDisparity, ui->rectify_max_hor_disparity_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Integer Value.");
      goto PIX_EXIT;
   } 

   // max vertical disparity, pixel number on original image
   
   if (!getInteger(&pEnv->_RectifyMaxVerticalDisparity, ui->rectify_max_ver_disparity_edit)) {
      QMessageBox::critical(this, "ERROR", "Enter Integer Value.");
      goto PIX_EXIT;
   }
            
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
