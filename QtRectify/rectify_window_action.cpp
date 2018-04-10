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


void rectify_window::createRectifyMain(void)
{
	int iHotX, iHotY, k;
   QIcon icon;
   QString strCompany, strVersion, strProgram, strHeader, strLabel;
   QString strGothic;
   QMenu *control_menu = ui->menuControl;

   control_menu->addSeparator();

   // fonts

   strGothic = getClassLabel_PC("Control", "Gothic");

   _sys_label_jp.setFamily(strGothic);
   _sys_label_jp.setPointSize(8);
   _sys_label_jp.setBold(false);
   _sys_label_jp.setItalic(false);
   _sys_label_jp.setUnderline(false);
   _sys_label_jp.setStrikeOut(false);
   _sys_label_jp.setKerning(true);

   _sys_bold_jp.setFamily(strGothic);
   _sys_bold_jp.setPointSize(8);
   _sys_bold_jp.setBold(true);
   _sys_bold_jp.setItalic(false);
   _sys_bold_jp.setUnderline(false);
   _sys_bold_jp.setStrikeOut(false);
   _sys_bold_jp.setKerning(true);

   _sys_label_en.setFamily("Arial");
   _sys_label_en.setPointSize(8);
   _sys_label_en.setBold(false);
   _sys_label_en.setItalic(false);
   _sys_label_en.setUnderline(false);
   _sys_label_en.setStrikeOut(false);
   _sys_label_en.setKerning(true);

   _sys_bold_en.setFamily("Arial");
   _sys_bold_en.setPointSize(8);
   _sys_bold_en.setBold(true);
   _sys_bold_en.setItalic(false);
   _sys_bold_en.setUnderline(false);
   _sys_bold_en.setStrikeOut(false);
   _sys_bold_en.setKerning(true);

   // windows

   _ImageSplitter = new ImageSplitter( Qt::Horizontal );

   _ImageSplitter->setOrientation( Qt::Horizontal );
   _ImageSplitter->setMainWindow(this);

   for( k = 0 ; k < 2 ; k++ ) {
      _Image_Pane[k] = new rectify_pane; 
      _Image_Pane[k]->setMainWindow(this); 
   }
   
   _ImageSplitter->insertWidget(0, _Image_Pane[0]); 
   _ImageSplitter->insertWidget(1, _Image_Pane[1]); 
   _ImageSplitter->setChildrenCollapsible( false );

   _ImageSplitter->setCollapsible(0, true);
   _ImageSplitter->setCollapsible(1, true);

   setCentralWidget( _ImageSplitter );

   connect( _ImageSplitter, SIGNAL( splitterMoved(int,int)),
      this, SLOT(imageSplitterMoved(int, int)));
   
   _Image_Pane[0]->show(); 
   _Image_Pane[1]->show(); 

   // *** control pane ***

   // index 

#ifdef _USE_DOCK
   strLabel = getRectifyLabel("View", "Index");
   _Dock_Index = new rectify_dock(strLabel, this);
   _Dock_Index->setType((short)rectify_dock::RectifyDockIndex);
   _Dock_Index->setAllowedAreas(Qt::BottomDockWidgetArea);
#endif _USE_DOCK

   _Index_Pane = new rectify_pane; 
   _Index_Pane->setMainWindow(this); 

#ifdef _USE_DOCK
    _Dock_Index->setWidget( _Index_Pane );  
    addDockWidget(Qt::BottomDockWidgetArea, _Dock_Index);
    control_menu->addAction(_Dock_Index->toggleViewAction());

    _Dock_Index->setMinimumWidth( 350 );  
    _Dock_Index->setMaximumWidth( 350 ); 
    _Dock_Index->setMinimumHeight( 200 );  
    _Dock_Index->setMaximumHeight( 250 ); 

    _Dock_Index->setFloating( false ); 
    _Dock_Index->show();
#endif _USE_DOCK
        
    // table

#ifdef _USE_DOCK
    strLabel = getRectifyLabel("View", "Points");
    _Dock_Table = new rectify_dock(strLabel, this);
    _Dock_Table->setType((short)rectify_dock::RectifyDockMonitor);
    _Dock_Table->setAllowedAreas(Qt::BottomDockWidgetArea);
#endif _USE_DOCK
   
   _rectifyTable = new rectify_table(this);
   _rectifyTable->setParent((rectify_window*)this);

#ifdef _USE_DOCK
   _Dock_Table->setWidget(_rectifyTable);
   addDockWidget(Qt::BottomDockWidgetArea, _Dock_Table);
   control_menu->addAction(_Dock_Table->toggleViewAction());

    _Dock_Table->setFloating( false );
    _Dock_Table->show( );
#endif _USE_DOCK
     
   // *** create meanu and actions

   createActions();
   createToolBars();
   
   //
   // create custom cursor
   // 

   QPixmap pixHitMatch = QPixmap(":/images/cursor_hit_and_match.png");

   iHotX = pixHitMatch.height() / 2;
   iHotY = pixHitMatch.width() / 2;
   _cursor_hit_and_match = QCursor(pixHitMatch, iHotX, iHotY);
   
   // window title bars

   strCompany = _version.GetCompany();
   strProgram = _version.getApplication();
   strVersion.sprintf("%d.%d", _version.GetMajorVersion(),
      _version.GetMinorVersion());

   strHeader = strCompany + tr(" - ") + strProgram + tr(" ") + strVersion;
   setWindowTitle( strHeader );

   qDebug() << strHeader;

   icon = QIcon(":/images/rectify1.png");
   setWindowIcon( icon );   
      
   return;
}

void rectify_window::addMenuAction(QAction *pAction, int iSelectMode)
{
   _list_menu_actions.push_back( pAction );
   pAction->setData( QVariant( iSelectMode ) );

   return;
}

//
// store window position in the setting
//
void rectify_window::StoreWindowPosition()
{
   QByteArray sta;
   QByteArray geo;

   QString strApplication = _version.getApplication();
   QString strOrganisation = _version.GetCompany();

   QSettings settings( strOrganisation, strApplication );

   //
  
   geo = saveGeometry( );
   settings.setValue( "geometry", geo );

   //

   sta = saveState( );
   settings.setValue( "windowState", sta );

   return;
}

//
// restore the last window geometry
//
void rectify_window::restoreWindowPosition()
{
   int iCount;
   QByteArray sta;
   QByteArray geo;

   QString strApplication = _version.getApplication();
   QString strOrganisation = _version.GetCompany();

   QSettings settings( strOrganisation, strApplication );

   geo = settings.value("geometry").toByteArray( );
   iCount = geo.count( );
   if( 0 >= iCount ) {
      // first time
      int iLeft = 30;
      int iTop = 30;
      int iWidth = 800;
      int iHeight = 500;
      QSize sz;
      QPoint ps;

      ps.setX ( iLeft );
      ps.setY ( iTop );
      sz.setWidth ( iWidth );
      sz.setHeight ( iHeight );
      move( ps );
      resize( sz );
   } else {
      restoreGeometry( geo );
   }

   //

   sta = settings.value("windowState").toByteArray( );
   iCount = sta.count( );
   if( 0 < iCount ) {
      restoreState ( sta );
   }

   return;
}

static void EnableMenuActions( QList<QAction*> _actions,
                              bool bEnable )
{
   int i, nActions;
   QAction *action;

   nActions = _actions.size( );
   for( i = 0 ; i < nActions ; i++ ) {
      action = (QAction*)_actions.at( i );
      action->setEnabled( bEnable );
   }

   return;
}


//
// handle key input
//
// returns:
// true: key input in handled
//
bool rectify_window::processKeyEvent(short sPane, int iKey)
{
   bool bProc = false;
   pixq_ScreenPara *pScreen = getScreenPara();

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

	switch( sPane ) {
   case rectify_pane::RectifyPaneSplitLeft:
   case rectify_pane::RectifyPaneSplitRight:
		break;

   case rectify_pane::RectifyPaneUnknown:
   case rectify_pane::RectifyPaneIndex:
   default:
      goto PIX_EXIT;
      break;
   }

	switch( iKey ) {
      
   // Scroll
   
   case Qt::Key_1: // 1 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->XYViewShift( 1, 1 );
         refreshPanes( );
      }
      bProc = true;
      break;

   case Qt::Key_2: // 2 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->XYViewShift( 0, 1 );
         refreshPanes( );
      }
      bProc = true;
      break;

   case Qt::Key_3: // 3 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->XYViewShift( -1, 1 );
         refreshPanes( );
      }
      break;

   case Qt::Key_4: // 4 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->XYViewShift( 1, 0 );
         refreshPanes( );
      }
      bProc = true;
      break;

   case Qt::Key_6: // 6 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->XYViewShift( -1, 0 );
         refreshPanes( );
      }
      bProc = true;
      break;

   case Qt::Key_7: // 7 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->XYViewShift( 1, -1 );
         refreshPanes( );
      }
      bProc = true;
      break;

   case Qt::Key_8: // 8 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->XYViewShift( 0, -1 );
         refreshPanes( );
      }
      bProc = true;
      break;

   case Qt::Key_9: // 9 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->XYViewShift( -1, -1 );
         refreshPanes( );
      }
      bProc = true;
      break;

   // ZOOM

   case Qt::Key_5: // 5 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->flipRecenter();
         refreshPanes();
      }
      bProc = true;
      break;

   case Qt::Key_Home:
   case Qt::Key_0: // 0 on NumPad
      if (validPaneDisplayMode()) {
         pScreen->viewOneToOne();
         refreshPanes( );
      }
      bProc = true;
      break;

	case Qt::Key_Plus: // + on NumPad
      if (validPaneDisplayMode()) {
         pScreen->zViewShift( -1 );
         refreshPanes( );
      }
      bProc = true;
      break;

   case Qt::Key_Minus:	// - on NumPad
      if (validPaneDisplayMode()) {
         pScreen->zViewShift(1);
         refreshPanes( );
      }
      bProc = true;
      break;
         
   // functions

   case Qt::Key_Escape:
      if (validPaneDisplayMode()) {
         _bRectifyHorizontalMarker = false;
         setRectifyMenuState();
         refreshPanes();
      }
      resetLeftMouseMode();
      bProc = true;
      break;
	}

PIX_EXIT:
   return bProc;
}

//
// reaction to mouse button press on panes
//
void rectify_window::switchPaneImage(void)
{
   short sPaneShowImage = getPanesShowImage();

   if (!_bDrvRectified) {
      goto PIX_EXIT;
   }

   // switch viewing method according to the mode

   switch (sPaneShowImage) {

   case rectify_pane::RectifyPaneShowInput:
      // toggle input / derived image
      setPanesShowImage((short)rectify_pane::RectifyPaneShowDerived);
      break;

   case rectify_pane::RectifyPaneShowDerived:
      // toggle input / derived image
      setPanesShowImage((short)rectify_pane::RectifyPaneShowInput);
      break;

   case rectify_pane::RectifyPaneShowNone:
   default:
      break;
   }

PIX_EXIT:
   return;
}


bool rectify_window::processWheelEvent(short sPane,
                                     int iDelta )
{
   bool bProc = false;
   int iShift;   
   pixq_ScreenPara *pScreen = getScreenPara();
   //pixq_FlipPara *pFlip = NULL;  

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

	switch( sPane ) {
   case rectify_pane::RectifyPaneSplitLeft:
   case rectify_pane::RectifyPaneSplitRight:
      break;

   case rectify_pane::RectifyPaneIndex:
   case rectify_pane::RectifyPaneUnknown:
   default:
      goto PIX_EXIT;
      break;
   }

   iShift = (int)-iDelta / 10;
   pScreen->zViewShift(iShift);
   refreshPanes( );

PIX_EXIT:
   return bProc;
}

bool rectify_window::processScrollEvent(short sPane,
                                      int iX, 
                                      int iY )
{
   bool bProc = false;
   pixq_ScreenPara *pScreen = getScreenPara();

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

	switch( sPane ) {
   case rectify_pane::RectifyPaneSplitLeft:
   case rectify_pane::RectifyPaneSplitRight:
      //pFlip = GetSplitPara( ); 
      break;

   case rectify_pane::RectifyPaneIndex:
   case rectify_pane::RectifyPaneUnknown:
   default:
      goto PIX_EXIT;
      break;
   }

   pScreen->XYViewStep( -iX, iY );
   refreshPanes( );

PIX_EXIT:
   return bProc;
}

void rectify_window::imageSplitterMoved(int /* pos */,
                                      int /* index */ )
{
   setImageSplitterWidth();

   return;
}

void rectify_window::setFrameStatusBar(void)
{
   QString strFrame, strImage0, strImage1;
   pixq_ImageDualSet *pData = getImageData( );

   if (!validPaneDisplayMode()) {
      _statusLabel[1]->setText("First Image");
      _statusLabel[2]->setText("Second Image");
      _statusLabel[3]->setText("Frame Position");
      goto PIX_EXIT;
   }

   if (!pData->getCurrentFiles(&strImage0, &strImage1)) {
      strImage0 = QString("********");
      strImage1 = QString("********");
   }

   if( strImage0.isEmpty( ) ) {
      strImage0 = QString("********");
   }
   
   if( strImage1.isEmpty( ) ) {
      strImage1 = QString("********");
   }

   strFrame = pData->GetFrameString( );

   _statusLabel[1]->setText( strImage0 );
   _statusLabel[2]->setText( strImage1 );
   _statusLabel[3]->setText( strFrame );
      
   _statusLabel[1]->setBackgroundRole( QPalette::Base );
   _statusLabel[2]->setBackgroundRole( QPalette::Base );
   _statusLabel[3]->setBackgroundRole( QPalette::Base );

   //

   _statusProgress->setRange( 0, 1 );
   _statusProgress->setValue( 1 );
   
   update( );

PIX_EXIT:
   return;
}

void rectify_window::setImageSplitterWidth(void)
{
   QList<int> sp_sz;
   int nSize;
   int nWidth, iPaneWidth[2];

   sp_sz = _ImageSplitter->sizes( );
   nSize = (int)sp_sz.size( ); 
   if( 2 != nSize ) {
      goto PIX_EXIT;
   }

   iPaneWidth[0] = sp_sz.at( 0 );
   iPaneWidth[1] = sp_sz.at( 1 );
   nWidth = iPaneWidth[0] + iPaneWidth[1];
   if( 0 >= nWidth ) {
      goto PIX_EXIT;
   }

   iPaneWidth[0] = nWidth / 2;
   iPaneWidth[1] = iPaneWidth[0];

   sp_sz.replace( 0, iPaneWidth[0] );
   sp_sz.replace( 1, iPaneWidth[1] );
   _ImageSplitter->setSizes( sp_sz );

PIX_EXIT:
   return;
}

//
// set menu status according to the conditions
//
void rectify_window::setRectifyMenuState(void)
{
   int i, iSelectMode, nActions;
   bool bEnabled;
   QAction *action;
   pixq_FringesTag *pTags = getRectifyTag();
   bool bRunnningThread;

   bool bLoaded = validPaneDisplayMode();
   short sPaneImage = _Image_Pane[0]->getPaneShowImage(); 
   
   // enable/disable all menus

   nActions = _list_menu_actions.size( );
   for( i = 0 ; i < nActions ; i++ ) {
      action = (QAction*)_list_menu_actions.at( i );
      iSelectMode = ((QVariant)action->data( )).toInt( );

      switch( iSelectMode ) {
      case MouseActionItemEnabled:
         action->setEnabled( true );
         break;

      case MouseActionItemDouble: 
         action->setEnabled( bLoaded );
         break;

      case MouseActionItemDisabled:
      default:
         action->setEnabled( false );
         break;
      }

      // uncheck action
      action->setCheckable( true );
      action->setChecked( false );
   }
   
   // check items - image to show
   
   ui->action_view_original_image->setChecked(false);
   ui->action_view_rectified_images->setChecked(false);

   switch (sPaneImage) {
   case rectify_pane::RectifyPaneShowInput:
      ui->action_view_original_image->setChecked(true);
      break;

   case rectify_pane::RectifyPaneShowDerived:
      ui->action_view_rectified_images->setChecked(true);
      break;

   case rectify_pane::RectifyPaneShowNone:
   default:
      break;
   }
   
   // check items - control points
   
   if (pTags->getDrawRectifyTag()) {
      ui->action_rectify_show_control_points->setChecked(true);
   }
   else {
      ui->action_rectify_show_control_points->setChecked(false);
   }
   
   // check items - horizontal line
   
   if (_bRectifyHorizontalMarker) {
      ui->action_rectify_horizontal_check_line->setChecked(true);
   }
   else {
      ui->action_rectify_horizontal_check_line->setChecked(false);
   }

   //
   // is rectified image created?
   //
   
   if (_bDrvRectified) {
      bEnabled = true;
   }
   else {
      bEnabled = false;
   }

   ui->action_file_save_image_pair->setEnabled(bEnabled);
   ui->action_file_save_anaglyph->setEnabled(bEnabled);
   ui->action_view_rectified_images->setEnabled(bEnabled);

   //
   // during the search thread, all menus are disabled!
   //
   
   if (_Search_Rectify_Thread) {
      
      if (_Search_Rectify_Thread->isRunning()) {
         bRunnningThread = true;
      }
      else {
         bRunnningThread = false;
      }
   }
   else {
      bRunnningThread = false;
   }

   if (bRunnningThread) {
      for (i = 0; i < nActions; i++) {
         action = (QAction*)_list_menu_actions.at(i);
         action->setEnabled(false);
         action->setCheckable(true);
         action->setChecked(false);
      }
   }
   
   return;
}

//
// to maintain left and right image image panes, same width
//
void rectify_window::fixRectifyPanes(int nPanes)
{
   int nSize, iHandle, iPaneSize[2], iSum;
   QList<int> sp_sz;

   iHandle = _ImageSplitter->handleWidth( );

   // only need this when second image pane is shown

   if (!_Image_Pane[1]->isVisible()) { 
      //goto PIX_EXIT;
   }

   sp_sz = _ImageSplitter->sizes( );
   nSize = (int)sp_sz.size( ); 
   if( 2 != nSize ) {
      goto PIX_EXIT;
   }

   // two images panesmust be of same width

   iPaneSize[0] = sp_sz.at( 0 );
   iPaneSize[1] = sp_sz.at( 1 );
   iSum = iPaneSize[0] + iPaneSize[1];
   if( 0 >= iSum ) {
      goto PIX_EXIT;
   }

   if( 1 == nPanes ) {
      iPaneSize[0] = iSum;
      iPaneSize[1] = 0;
      _ImageSplitter->setHandleWidth( 0 );
   } else {
      iPaneSize[0] = iSum / 2;
      iPaneSize[1] = iPaneSize[0];
      _ImageSplitter->setHandleWidth( 1 );
   }

   sp_sz.replace( 0, iPaneSize[0] );
   sp_sz.replace( 1, iPaneSize[1] );
   _ImageSplitter->setSizes( sp_sz );

   _ImageSplitter->handle(1)->setCursor( Qt::ArrowCursor );

PIX_EXIT:
   return;
}

void rectify_window::createToolBars(void)
{
   // main tool bar

   ui->mainToolBar->addAction(ui->action_file_select_image_pair);
   ui->mainToolBar->addAction(ui->action_file_save_image_pair);
   ui->mainToolBar->addAction( ui->action_file_properties );

   ui->mainToolBar->addSeparator( );

   // view tool bar

   ui->viewToolBar->addAction(ui->action_view_original_image);
   ui->viewToolBar->addAction(ui->action_view_rectified_images);
   
   ui->viewToolBar->addAction(ui->action_rectify_show_control_points);
   ui->viewToolBar->addAction(ui->action_rectify_horizontal_check_line);

   ui->viewToolBar->addSeparator( );

   // zoom tool bar
   
   ui->zoomFrameToolBar->addAction( ui->action_zoom_recneter );
   ui->zoomFrameToolBar->addAction( ui->action_zoom_real_size );
   ui->zoomFrameToolBar->addAction( ui->action_zoom_zoom_up );
   ui->zoomFrameToolBar->addAction( ui->action_zoom_zoom_down );
   
   return;
}

void rectify_window::createActions(void)
{
   _list_menu_actions.clear( );

   // *** file menu ***

   addMenuAction(ui->action_file_select_image_pair, (int)MouseActionItemEnabled);
   addMenuAction(ui->action_file_save_image_pair, (int)MouseActionItemDouble);
   addMenuAction(ui->action_file_save_anaglyph, (int)MouseActionItemDouble);
   addMenuAction(ui->action_file_properties, (int)MouseActionItemEnabled);
   addMenuAction(ui->action_file_exit, (int)MouseActionItemEnabled);

   // *** View menu ***

   addMenuAction(ui->action_view_original_image, (int)MouseActionItemDouble);
   addMenuAction(ui->action_view_rectified_images, (int)MouseActionItemDouble);
      
   // *** Zoom menu ***

   addMenuAction(ui->action_zoom_recneter, (int)MouseActionItemDouble);
   addMenuAction(ui->action_zoom_real_size, (int)MouseActionItemDouble);
   addMenuAction(ui->action_zoom_zoom_up, (int)MouseActionItemDouble);
   addMenuAction(ui->action_zoom_zoom_down, (int)MouseActionItemDouble);
   addMenuAction(ui->action_zoom_scroll_up, (int)MouseActionItemDouble);
   addMenuAction(ui->action_zoom_scroll_down, (int)MouseActionItemDouble);
   addMenuAction(ui->action_zoom_scroll_left, (int)MouseActionItemDouble);
   addMenuAction(ui->action_zoom_scroll_right, (int)MouseActionItemDouble);

   // *** Rectify menu ***
   
   addMenuAction(ui->action_rectify_all_rectification, (int)MouseActionItemDouble);
   addMenuAction(ui->action_rectify_generate_control_points, (int)MouseActionItemDouble);
   addMenuAction(ui->action_rectify_stereo_rectification, (int)MouseActionItemDouble);
   addMenuAction(ui->action_rectify_hit_and_match, (int)MouseActionItemDouble);
   
   addMenuAction(ui->action_rectify_show_control_points, (int)MouseActionItemDouble);
   addMenuAction(ui->action_rectify_horizontal_check_line, (int)MouseActionItemDouble);

   // *** Help menu ***

   addMenuAction(ui->action_help_about, (int)MouseActionItemEnabled);
   addMenuAction(ui->action_help_help, (int)MouseActionItemEnabled);

   return;
}

void rectify_window::setLeftMouseMode(short sMode)
{
	_sLeftMouseMode = sMode;

	_Image_Pane[0]->setModeCursor();
	_Image_Pane[1]->setCursor(Qt::ArrowCursor);
	_Index_Pane->setCursor(Qt::ArrowCursor);

	return;
}

void rectify_window::resetLeftMouseMode(void)
{
	setLeftMouseMode((short)MouseLeftClickNone);

	return;
}

#ifdef _USE_DOCK
void rectify_window::setTableLabel(QString strLabel)
const
{
   _Dock_Table->setWindowTitle( strLabel );
   
   return;
}
#endif _USE_DOCK