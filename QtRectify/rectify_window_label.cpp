#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_panes.h"
#include "rectify_table.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

#include "rectify_window.h"
#include "ui_rectify_window.h"

//
// get label for given key word(class) from xml file
//
QString rectify_window::getRectifyLabel(const QString strClass, // [i] class name to search
   const QString strName, // [i] label(text) name to search
   const QString strDefault) // [i] default in case the label couldn't be found
{
   QString strWord;
   bool bLabel, bClass;
   QString strLang, strHeader, strValue;
   QFile *file = NULL;
   QXmlStreamReader reader;
   QXmlStreamAttributes attr;

   QString strFile = ":/Files/msg_rectify.xml";

   pixq_Properties *pEnv = getRectifyEnv();
   int iLanguage = pEnv->_SystemInterfaceLanguage.getInteger();

   switch (iLanguage) {
   case QLocale::Japanese:
      strLang = "Jp";
      break;

   case QLocale::English:
   default:
      strLang = "En";
      break;
   }
   //

   strWord = strDefault;
   file = new QFile(strFile);
   if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
      // file does not exist
      goto PIX_EXIT;
   }

   //
   // check xml file
   //

   reader.setDevice(file);

   if (!reader.readNextStartElement()) {
      goto PIX_EXIT;
   }

   if (reader.name() != "pixtopo") {
      goto PIX_EXIT;
   }

   if (reader.attributes().value("version") != "1.0") {
      goto PIX_EXIT;
   }

   //

   bClass = true;
   while (bClass) {
      if (reader.atEnd()) {
         bClass = false;
         continue;
      }

      if (!reader.readNextStartElement()) {
         bClass = false;
         continue;
      }

      strHeader = reader.name().toString();
      if ("Class" != strHeader) {
         continue;
      }

      attr = reader.attributes();
      strValue = attr.value("ID").toString();
      if (strValue != strClass) {
         reader.skipCurrentElement();
         continue;
      }

      // class found! find the label

      bLabel = true;
      while (bLabel) {
         if (!reader.readNextStartElement()) {
            bLabel = false;
            bClass = false;
            continue;
         }

         strHeader = reader.name().toString();
         if ("Label" != strHeader) {
            continue;
         }

         attr = reader.attributes();
         strValue = attr.value("ID").toString();
         if (strValue != strName) {
            reader.skipCurrentElement();
            continue;
         }

         strWord = attr.value(strLang).toString();
         bLabel = false;
         bClass = false;
         continue;
      }
   }

PIX_EXIT:
   if (file) {
      file->close();
      file = NULL;
   }
   return strWord;
}

//
// same as above except that default label is same as label name
//
QString rectify_window::getRectifyLabel( const QString strClass, // [i] class name to search
   const QString strName) // [i] label(text) name to search
{
   QString strWord = getRectifyLabel(strClass, strName, strName);

   return strWord;
}

void rectify_window::setMenuLabels(void)
{
   // file

   ui->menuFile->setTitle(getRectifyLabel("MenuFile", "Header"));

   ui->action_file_select_image_pair->setText(getRectifyLabel("MenuFile", "Image"));
   ui->action_file_save_image_pair->setText(getRectifyLabel("MenuFile", "Save"));
   ui->action_file_save_anaglyph->setText(getRectifyLabel("MenuFile", "Anaglyph"));
   ui->action_file_properties->setText(getRectifyLabel("MenuFile", "Option"));
   ui->action_file_exit->setText(getRectifyLabel("MenuFile", "Exit"));
   
   // view

   ui->menuView->setTitle(getRectifyLabel("MenuView", "Header"));

   ui->action_view_original_image->setText(getRectifyLabel("MenuView", "Original"));
   ui->action_view_rectified_images->setText(getRectifyLabel("MenuView", "Rectified"));

   // zoom

   ui->menuZoom->setTitle(getRectifyLabel("MenuZoom", "Header"));

   ui->action_zoom_recneter->setText(getRectifyLabel("MenuZoom", "Recenter"));
   ui->action_zoom_real_size->setText(getRectifyLabel("MenuZoom", "Real"));
   ui->action_zoom_zoom_up->setText(getRectifyLabel("MenuZoom", "Zoom+"));
   ui->action_zoom_zoom_down->setText(getRectifyLabel("MenuZoom", "Zoom-"));
   ui->action_zoom_scroll_up->setText(getRectifyLabel("MenuZoom", "Up"));
   ui->action_zoom_scroll_down->setText(getRectifyLabel("MenuZoom", "Down"));
   ui->action_zoom_scroll_left->setText(getRectifyLabel("MenuZoom", "Left"));
   ui->action_zoom_scroll_right->setText(getRectifyLabel("MenuZoom", "Right"));
   
   // Rectify

   ui->menuRectify->setTitle(getRectifyLabel("MenuRectify", "Header"));

   ui->action_rectify_all_rectification->setText(getRectifyLabel("MenuRectify", "All"));
   ui->action_rectify_show_control_points->setText(getRectifyLabel("MenuRectify", "Points"));
   ui->action_rectify_horizontal_check_line->setText(getRectifyLabel("MenuRectify", "Epipolar"));

   ui->menuRectifyAnalyze->setTitle(getRectifyLabel("MenuRectify", "menuRectifyAnalyze"));
   ui->action_rectify_generate_control_points->setText(getRectifyLabel("MenuRectify", "Control"));
   ui->action_rectify_stereo_rectification->setText(getRectifyLabel("MenuRectify", "Rectify"));
   ui->action_rectify_hit_and_match->setText(getRectifyLabel("MenuRectify", "HitMatch"));

   // Control

   ui->menuControl->setTitle(getRectifyLabel("MenuControl", "Header"));

   // Help

   ui->menuHelp->setTitle(getRectifyLabel("MenuHelp", "Header"));

   ui->action_help_about->setText(getRectifyLabel("MenuHelp", "About"));
   ui->action_help_help->setText(getRectifyLabel("MenuHelp", "Help"));
   
   return;
}


void rectify_window::setDockLabels(void)
{
   pixq_Properties *pEnv = getRectifyEnv();
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   QString strLabel;
   QFont *sys_label;
   QFont *sys_bold;

   // index 

#ifdef _USE_DOCK
   strLabel = getRectifyLabel("View", "Index");
   _Dock_Index->setWindowTitle(strLabel);
#endif _USE_DOCK
   
   // table

#ifdef _USE_DOCK
   strLabel = getRectifyLabel("View", "Points");
   _Dock_Table->setWindowTitle(strLabel);
#endif _USE_DOCK

   // set fonts

   switch (iLang) {
   case QLocale::Japanese:
      sys_label = &_sys_label_jp;
      sys_bold = &_sys_bold_jp;
      break;

   case QLocale::English:
   default:
      sys_label = &_sys_label_en;
      sys_bold = &_sys_bold_en;
      break;
   }

   _statusLabel[0]->setFont(*sys_bold);
   _statusLabel[1]->setFont(*sys_label);
   _statusLabel[2]->setFont(*sys_label);
   _statusLabel[3]->setFont(*sys_label);
   
   return;
}



