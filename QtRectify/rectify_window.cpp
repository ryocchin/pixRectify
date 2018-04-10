#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_cv_common.h"

#include "rectify_panes.h"
#include "rectify_table.h"
#include "rectify_window.h"
#include "ui_rectify_window.h"

#include <omp.h>

rectify_window::rectify_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::rectify_window)
{
   int k;
      
   //

   ui->setupUi(this);

   _bInitialized = false;
   setImageLoading(false);

   // read the program version info

   _version = Version();

   // init all widgets

   _ImageSplitter = (ImageSplitter*)NULL;

   for( k = 0 ; k < 2 ; k++ ) {
      _Image_Pane[k] = (rectify_pane*)NULL; 
   }

   _Index_Pane = (rectify_pane*)NULL; 

   // init all data

   for( k = 0 ; k < 2 ; k++ ) {
      _pImgTexture[k]  = (pixq_DepthTexture*)NULL;
   }

   _RectifyTags = (pixq_FringesTag*)NULL;

   _pRectifyEnv = (pixq_Properties*)NULL;
   _pImageDataSet = (pixq_ImageDualSet*)NULL;

   _pScreenPara = (pixq_ScreenPara*)NULL;
   _pIndexPara = (pixq_FlipPara*)NULL;
   
   _ImageProps[0] = (pixq_ImageInfo*)NULL;
   _ImageProps[1] = (pixq_ImageInfo*)NULL;

   _Search_Rectify_Thread = (rectify_search_thread*)NULL;
   _Search_Rectify_Dialog = (rectify_progress_dialog*)NULL;

   // create window    

   initRectifyData();

   createRectifyMain();
   
   // create status bar

   for( k = 0 ; k < 4 ; k++ ) {
      _statusLabel[k] = new QLabel( "pixRectify", this );
      _statusLabel[k]->setFrameStyle( QFrame::Sunken );
   }

   _statusLabel[0]->setText("Coordinate and Color");
   _statusLabel[1]->setText("First Image");
   _statusLabel[2]->setText("Second Image");
   _statusLabel[3]->setText("Frame Position");

   _statusProgress = new QProgressBar( this );
   _statusProgress->setFormat( "%v" );

   statusBar()->addPermanentWidget( _statusLabel[0], 3 );
   statusBar()->addPermanentWidget( _statusLabel[1], 3 );
   statusBar()->addPermanentWidget( _statusLabel[2], 3 );
   statusBar()->addPermanentWidget( _statusLabel[3], 1 );
   statusBar()->addPermanentWidget( _statusProgress, 2 );

   // *** initialize all data ***
   
   resetLeftMouseMode();
      
   resetAllData();
   
   _Image_Pane[0]->Init(rectify_pane::RectifyPaneSplitLeft); 
   _Image_Pane[1]->Init(rectify_pane::RectifyPaneSplitRight); 
   _Index_Pane->Init(rectify_pane::RectifyPaneIndex); 

   // set language
   // this must be done after initRectifyData, env setting....

   setMenuLabels();
   setDockLabels();
   
   // 
   
   for( k = 0 ; k < 2 ; k++ ) {
      _Image_Pane[k]->setAcceptDrops( true );  
   }

   _Index_Pane->setAcceptDrops(false); 
   _Index_Pane->setAcceptDrops(false);

   _rectifyTable->setAcceptDrops(true);
   setAcceptDrops( true );

   // help dialog

   _helpView = NULL;

   //

   fprintf(stdout, "...Number of Available Processors: %d.\n", omp_get_num_procs());
   fprintf(stdout, "...Maximum Number of Threads: %d.\n", omp_get_max_threads());
   
//PIX_EXIT:
   return;
}

rectify_window::~rectify_window()
{
   if (_helpView) {
      delete _helpView;
      _helpView = NULL;
   }

   releaseData();
    
   delete ui;

   return;
}

void rectify_window::closeEvent(QCloseEvent * /*eve*/)
{
   StoreWindowPosition( );

   return;
}

void rectify_window::resizeEvent(QResizeEvent * /*eve*/)
{
   if( !_bInitialized ) {
      goto PIX_EXIT;
   }

 // fixRectifyPanes(  );

PIX_EXIT:
   return;
}

void rectify_window::paintEvent(QPaintEvent * /*eve*/)
{
   if( !_bInitialized ) {
      goto PIX_EXIT;
   }

   refreshPanes( );

PIX_EXIT:
   return;
}

void rectify_window::showEvent(QShowEvent * /*eve*/)
{
   if( _bInitialized ) {
      goto PIX_EXIT;
   }

   restoreWindowPosition();
   
   setPanesShowMode(pixq_ScreenPara::PixPaneShowNone);
   refreshPanes( );
   
   _bInitialized = true;

PIX_EXIT:
   return;
}

void rectify_window::dragEnterEvent(QDragEnterEvent *event)
{
   setBackgroundRole(QPalette::Highlight);

   event->acceptProposedAction();
   
   return;
}

void rectify_window::dragMoveEvent(QDragMoveEvent *event)
{
   event->acceptProposedAction();
   
   return;
}

void rectify_window::dragLeaveEvent(QDragLeaveEvent *event)
{
   //clear();
   event->accept();
    
   return;
}

void rectify_window::dropEvent(QDropEvent *eve)
{
   const QMimeData *data = eve->mimeData( );
   QList<QUrl> urls = data->urls( );
   bool bIsFile[2], bIsDir[2];
   int k;
   int nUrls = (int)urls.size( );
   QString strMessage, strPath[2];
   QFileInfo fi;

   if( !_bInitialized ) {
      goto PIX_EXIT;
   }

   if( 2 != nUrls ) {
      QString strApplication = _version.getApplication();
      strMessage = getRectifyLabel("Warning", "DropWrong");
      QMessageBox::warning(this, strApplication, strMessage);
      resetAllData();
      goto PIX_EXIT;
   }
   
   for( k = 0 ; k < 2 ; k++ ) {
      QUrl url = urls.at( k );
      strPath[k] = url.toLocalFile( );
      fi.setFile( strPath[k] );
      bIsDir[k] = fi.isDir( );
      bIsFile[k] = fi.isFile( );
      strPath[k] = fi.absoluteFilePath( );
   }

   if( bIsFile[0] && bIsFile[1] ) {
      // two files dropped!
      resetAllData();
      if (!loadRectifyImages(strPath[0], strPath[1])) {
         goto PIX_EXIT;
      }  
   } else {
      QString strApplication = _version.getApplication();
      strMessage = getRectifyLabel("Warning", "DropWrong");
      QMessageBox::warning(this, strApplication, strMessage);
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

//
// *** Menu - File ***
//

void rectify_window::on_action_file_select_image_pair_triggered()
{
   if (!selectLoadImagePair()) {
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

void rectify_window::on_action_file_save_image_pair_triggered()
{
   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }
   
   if (!_bDrvRectified) {
      goto PIX_EXIT;
   }

   if (!saveRectifiedRight()) {
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

void rectify_window::on_action_file_save_anaglyph_triggered()
{
   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   if (!_bDrvRectified) {
      goto PIX_EXIT;
   }

   if (!saveAnaglyphImage()) {
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}


void rectify_window::on_action_file_properties_triggered()
{
   if( !setProperties( ) ) {
      goto PIX_EXIT;
   }

   refreshPanes();

PIX_EXIT:
    return;
}

void rectify_window::on_action_file_exit_triggered()
{
   close( );

   return;
}

//
// *** Menu - View ***
//

void rectify_window::on_action_view_original_image_triggered()
{
   short sPaneShowMode = pixq_ScreenPara::PixPaneShowHorizontalSplit;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   setPanesShowMode(sPaneShowMode);
   setPanesShowImage(rectify_pane::RectifyPaneShowInput);

   refreshPanes();
   setRectifyMenuState();

PIX_EXIT:
   return;
}

void rectify_window::on_action_view_rectified_images_triggered()
{
   short sPaneShowMode = pixq_ScreenPara::PixPaneShowHorizontalSplit;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   if (!_bDrvRectified) { 
      goto PIX_EXIT;
   }

   setPanesShowMode(sPaneShowMode);
   setPanesShowImage(rectify_pane::RectifyPaneShowDerived);

   refreshPanes();
   setRectifyMenuState();

PIX_EXIT:
   return;
}

//
// *** Menu - Rectify ***
//

void rectify_window::on_action_rectify_all_rectification_triggered()
{
    if (!validPaneDisplayMode()) {
       goto PIX_EXIT;
    }

    // start to generate control points and then do the rectification

    if (!rectifyGenerateControlPoints(true)) {
       goto PIX_EXIT;
    }
    
PIX_EXIT:
   return;
}

void rectify_window::on_action_rectify_generate_control_points_triggered()
{
   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   // start to generate control points

   if (!rectifyGenerateControlPoints(false)) {
      goto PIX_EXIT;
   }
   
PIX_EXIT:
   return;
}

void rectify_window::on_action_rectify_stereo_rectification_triggered()
{
   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   if (!rectifyCalibrate()) {
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}


void rectify_window::on_action_rectify_show_control_points_triggered()
{
   pixq_FringesTag *pTags = getRectifyTag();

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   pTags->switchDrawRectifyTag();

   setRectifyMenuState();
   refreshPanes();

PIX_EXIT:
   return;
}

void rectify_window::on_action_rectify_hit_and_match_triggered()
{
	if (!validPaneDisplayMode()) {
		goto PIX_EXIT;
	}

	setLeftMouseMode((short)MouseLeftClickNoneHitAndMatch);
	refreshPanes();

PIX_EXIT:
	return;
}

void rectify_window::on_action_rectify_horizontal_check_line_triggered()
{
   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   _bRectifyHorizontalMarker = !_bRectifyHorizontalMarker;

   setRectifyMenuState();
   refreshPanes();

PIX_EXIT:
   return;
}

//
// *** Menu - Zoom ***
//

void rectify_window::on_action_zoom_real_size_triggered()
{
   short sPane = rectify_pane::RectifyPaneSplitLeft;
   int iKey = Qt::Key_Home;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   processKeyEvent(sPane, iKey);

PIX_EXIT:
   return;
}

void rectify_window::on_action_zoom_recneter_triggered()
{
   short sPane = rectify_pane::RectifyPaneSplitLeft;
   int iKey = Qt::Key_5;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   processKeyEvent(sPane, iKey);

PIX_EXIT:
   return;
}

void rectify_window::on_action_zoom_zoom_up_triggered()
{
   short sPane = rectify_pane::RectifyPaneSplitLeft;
   int iKey = Qt::Key_Plus;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   processKeyEvent(sPane, iKey);

PIX_EXIT:
   return;
}

void rectify_window::on_action_zoom_zoom_down_triggered()
{
   short sPane = rectify_pane::RectifyPaneSplitLeft;
   int iKey = Qt::Key_Minus;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   processKeyEvent(sPane, iKey);

PIX_EXIT:
   return;
}

void rectify_window::on_action_zoom_scroll_up_triggered()
{
   short sPane = rectify_pane::RectifyPaneSplitLeft;
   int iKey = Qt::Key_8;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   processKeyEvent(sPane, iKey);

PIX_EXIT:
   return;
}

void rectify_window::on_action_zoom_scroll_down_triggered()
{
   short sPane = rectify_pane::RectifyPaneSplitLeft;
   int iKey = Qt::Key_2;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   processKeyEvent(sPane, iKey);

PIX_EXIT:
   return;
}

void rectify_window::on_action_zoom_scroll_left_triggered()
{
   short sPane = rectify_pane::RectifyPaneSplitLeft;
   int iKey = Qt::Key_4;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   processKeyEvent(sPane, iKey);

PIX_EXIT:
   return;
}

void rectify_window::on_action_zoom_scroll_right_triggered()
{
   short sPane = rectify_pane::RectifyPaneSplitLeft;
   int iKey = Qt::Key_6;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   processKeyEvent(sPane, iKey);

PIX_EXIT:
   return;
}

//
// *** Menu - Help ***
//

void rectify_window::on_action_help_help_triggered()
{
   QString strHelp, strID;
   pixq_Properties *pEnv = getRectifyEnv();
   int iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   strHelp = QFileInfo(QCoreApplication::applicationDirPath()).filePath();
   strHelp += QDir::separator();

   switch (iLang) {
   case QLocale::Japanese:
      strHelp += QLatin1String("pixrectify_jp_index.qhc");
      //strHelp = ":/manual/pixdiff_jp_index.qhc";
      break;

   case QLocale::English:
   default:
      strHelp += QLatin1String("pixrectify_en_index.qhc");
      //strHelp = ":/manual/pixdiff_en_index.qhc";
      break;
   }

   qDebug() << strHelp;

   strID = "pixRectify";

   if (_helpView) {
      delete _helpView;
      _helpView = NULL;
   }

   _helpView = new pixq_HelpViewer(strHelp, strID);
   _helpView->resize(1000, 800);

   _helpView->show();

   return;
}

void rectify_window::on_action_help_about_triggered()
{
   pixq_Properties *pEnv = getRectifyEnv();

   showPixAbout_PC(&_version, pEnv);

   return;
} 

