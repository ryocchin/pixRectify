#pragma once

#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

QT_BEGIN_NAMESPACE
class QHelpEngineCore;
QT_END_NAMESPACE;

#define _USE_DOCK 

namespace Ui {
   class rectify_window;
}

class rectify_pane;

class ImageCtrl;
class ImageSplitter;

class rectify_dock;
class rectify_table;
class rectify_search_thread;
class rectify_progress_dialog;


inline int clumpCoo(int iCoo, int nSize)
{
   int iOut = max(0, iCoo);
   iOut = min(iOut, nSize-1);
   return iOut;
}


class rectify_window : public QMainWindow
{
   Q_OBJECT

public:
   // *** DO NOT CHANGE THESE NUMBERS ***
   // Menu Action Stratus Mode
   // This is encedded to QAction Items
   enum {
      // always enabled
      MouseActionItemEnabled = 0, 
      // enabled only when double sequences ares loaded
      MouseActionItemDouble = 2, 
      // always disnabled
      MouseActionItemDisabled = 4, 
   } MouseActionSelectionMode;

   // Left mouse click working mode
   enum {
	   // no job at all
	   MouseLeftClickNone = 0,
	   // hit and match
	   MouseLeftClickNoneHitAndMatch = 1,
   } MouseLeftClickWorkMode;


public:
   //
   // number of pyramid including the source level
   //
   static const int _nPyramidLevel = 4;
   //static const int _nPyramidLevel = 3;

private:
   //
   // *** GUI ***
   //
   ImageSplitter *_ImageSplitter;
   
   // image panes to show stereo images

   rectify_pane *_Image_Pane[2];

   // status bar
   QLabel *_statusLabel[4];
   QProgressBar  *_statusProgress;

   // actions list

   QList<QAction*> _list_menu_actions;

   // image panes to show index image

   rectify_pane *_Index_Pane;
   
   // rectification results

   rectify_table *_rectifyTable;

   // tag positions to measure color displacement

   pixq_FringesTag *_RectifyTags;

   // Pyramid Images for three levels, divided into three channels

   pixq_Matrix<unsigned short> _usPyramidRed[_nPyramidLevel][2];
   pixq_Matrix<unsigned short> _usPyramidGrn[_nPyramidLevel][2];
   pixq_Matrix<unsigned short> _usPyramidBlu[_nPyramidLevel][2];
   pixq_Matrix<unsigned short> _usPyramidGray[_nPyramidLevel][2];

   // Pyramid Images for three levels, divided into three channels and converted to double

   pixq_Matrix<double> _dPyramidRed[_nPyramidLevel][2];
   pixq_Matrix<double> _dPyramidGrn[_nPyramidLevel][2];
   pixq_Matrix<double> _dPyramidBlu[_nPyramidLevel][2];
   pixq_Matrix<double> _dPyramidGray[_nPyramidLevel][2];

   // parameters and data in 3D depth simulator

#ifdef _USE_DOCK
   rectify_dock *_Dock_Index;
   rectify_dock *_Dock_Table;
#endif _USE_DOCK

   //
   // *** program version ***
   //

   pixq_Version _version;

   //
   // *** program ***
   //

   // main windows created?
   bool _bInitialized;

   //
   // files selection
   //

   pixq_ImageDualSet *_pImageDataSet;

   //
   // data
   //

   // OpenGL texture for left and right image
   pixq_DepthTexture *_pImgTexture[2];

   // geometric parameters of page flipping

   pixq_ScreenPara *_pScreenPara;
   pixq_FlipPara *_pIndexPara;

   // environment
   pixq_Properties *_pRectifyEnv;

   // image header Info
   pixq_ImageInfo *_ImageProps[2];

   // image matrix
   pixq_ImageMatrix _ImageInMtx[2][3];
   
   // derive image matrix 
   pixq_ImageMatrix _ImageDrvMtx[2][3];

   // rectified image created
   bool _bDrvRectified;

   // image is currently being loaded
   // set to true, while the image is being loaded/processed 
   // to avoid mouse event on the image pane!
   bool _bImageLoading;

   // what to show in central image pane
   // pixq_ScreenPara::PixPaneShowHorizontalSplit for stereo images
   // or
   // pixq_ScreenPara::PixPaneShowFirst for anaglyph
   short _sPaneContent;

   // left mouse click work mode, one of MouseLeftClickWorkMode;
   short _sLeftMouseMode;

   pixq_HelpViewer *_helpView;

private:
	QCursor _cursor_hit_and_match;

private:
   // last mouse position
   int _nLastMouseY;

   //
   // draw horizontal check line?
   //
   bool _bRectifyHorizontalMarker;

   // to memorize the window position before it goes fullscreen.
   QRect _WinSize;
   QPoint _WinPosition;

   QFont _sys_label_jp;
   QFont _sys_bold_jp;
   QFont _sys_label_en;
   QFont _sys_bold_en;

   //
   // point serach thread
   //
   rectify_search_thread *_Search_Rectify_Thread;
   rectify_progress_dialog *_Search_Rectify_Dialog;

public:
   explicit rectify_window(QWidget *parent = 0);
   ~rectify_window();

private:
   Ui::rectify_window *ui;

public:
   void addMenuAction(QAction *pAction, int iSelectMode);

   bool isThreadRunning(void);
   void createRectifyMain(void);
   void createActions( void );
   void createToolBars(void);

   void setImageSplitterWidth(void);

   void setMenuLabels(void);
   void setDockLabels(void);
   
   void switchPaneImage(void);

   //
   // loader thread
   //
private:
   bool startLoaderThread(bool bRectify);

   private slots:
   void searchThreadSearchTag(int iFrame);
   void searchThreadStopPressed(void);
   void searchThreadCompleted(bool bCanceled);

public:
   // mouse mode
   short getLeftMouseMode(void) { return _sLeftMouseMode; }
   void setLeftMouseMode(short sMode);
   void resetLeftMouseMode(void);

   public slots:
   void imageSplitterMoved(int pos, int index);

public:
	QCursor *hitMatchCursor(void) { return &_cursor_hit_and_match; }

private slots:

   //
   // *** Menu - File ***
   //

   void on_action_file_select_image_pair_triggered();
   void on_action_file_save_image_pair_triggered();
   void on_action_file_save_anaglyph_triggered();
   void on_action_file_properties_triggered();
   void on_action_file_exit_triggered();

   //
   // *** Menu - View ***
   //

   void on_action_view_original_image_triggered();
   void on_action_view_rectified_images_triggered();

   //
   // *** Menu - Rectify ***
   //

   void on_action_rectify_all_rectification_triggered();
   void on_action_rectify_generate_control_points_triggered();
   void on_action_rectify_stereo_rectification_triggered();
   void on_action_rectify_show_control_points_triggered();
   void on_action_rectify_horizontal_check_line_triggered();
   void on_action_rectify_hit_and_match_triggered();

   //
   // *** Menu - Zoom ***
   //
   
   void on_action_zoom_real_size_triggered();
   void on_action_zoom_recneter_triggered();
   void on_action_zoom_zoom_up_triggered();
   void on_action_zoom_zoom_down_triggered();
   void on_action_zoom_scroll_up_triggered();
   void on_action_zoom_scroll_down_triggered();
   void on_action_zoom_scroll_left_triggered();
   void on_action_zoom_scroll_right_triggered(); 
   
   //
   // *** Menu - Help ***
   //

   void on_action_help_about_triggered();
   void on_action_help_help_triggered();

protected:
   void closeEvent( QCloseEvent *eve );
   void paintEvent ( QPaintEvent *eve ); 
   void showEvent( QShowEvent *eve );
   void resizeEvent( QResizeEvent *eve );

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

public:
#ifdef _USE_DOCK
   void setTableLabel( QString strLabel ) const;
#endif _USE_DOCK

   void initRectifyData(void);
   void releaseData(void);

   void clearGridSelection(void);
   void resetAllData(void);
   void resetMatch(void);
      
   QString getRectifyLabel(const QString strClass,
      const QString strName, 
      const QString strDefault );
   
   QString getRectifyLabel(const QString strClass, const QString strName );

   short getPanesShowImage(void ) const;
   void setPanesShowImage(short sPaneImage);

   void setPanesShowMode(short sSecondPaneMode);
   void setPanesShowMonoMode(void);
   void setPanesShowStereoMode(void);

   // image load mode
      
   void setFrameStatusBar( void );

   //
   // utility functions
   //
   void restoreWindowPosition(void);
   void StoreWindowPosition( void );
   void fixRectifyPanes(int nPanes);

   bool loadRectifyImages(const QString strFile0, const QString strFile1);

   bool selectLoadImagePair(void);
   bool saveRectifiedRight(void);
   bool saveAnaglyphImage(void);

   bool setProperties(void);
   
   QString getApplication(void);

   // load double images and copy it to each pane
   bool createRectifyBitmaps(void);

   // get image file name according to the mode and side
   bool getSideFile(int iSide, QString *strFile) const;

   // load image into three(rgb) unsigned short matrices

   bool loadRectifyFrame( const QString strFile,
      pixq_ImageInfo *info,
      pixq_ImageMatrix *usRed,
      pixq_ImageMatrix *usGrn,
      pixq_ImageMatrix *usBlu );

   // create image texture for given pane from given image matrix(0/1/2)

   bool CreateIndexTexture(rectify_pane *pPane, int iIMage);

   // create texture on the right pane from the derived image matrices
   bool createLoadedTexture(void);
   bool createDerivedTexture(void);
      
   void getOpenGLInfo( QStringList *strTitles, QStringList *strValue ) const;
      
   void listStatistics(QStringList *strTitles, QStringList *strValue0,
      QStringList *strValue1, QList<int> *iAlignments ) const;

   void getImageProps( QStringList *strTitles, QStringList *strProps0, 
      QStringList *strProps1, QList<int> *iAlignments ) const;

public:
   void centerToTag(int iTag);

public:
   bool getHorizontalMarker(void) const { return _bRectifyHorizontalMarker; }

public:
   void setImageLoading(bool bLoading) { _bImageLoading = bLoading; }
   bool getImageLoading(void) const { return _bImageLoading; }

   pixq_Version *getVersion(void) { return &_version; }

public:
   void storeEnv(void);
   void setRectifyMenuState(void);
   void getColor(int iSide, int iMouseX, int iMouseY);
   bool validPaneDisplayMode(void) const;

   rectify_table *getTablePane(void) const { return _rectifyTable; }

   // get texture ID for the side/frame
   unsigned int getTexture(int iSide, int iFrame);
   
   void refreshPanes( void );

   void setPanesCursor(QCursor cur);

   // handle key input on pane
   bool processKeyEvent(short sPane, int iKey);
   
   bool processWheelEvent(short sPane, int iDelta);
   bool processScrollEvent( short sPane, int iX, int iY );
   
   pixq_ImageInfo *getImageInfo( int iSide ) const { return _ImageProps[iSide]; }  
   
   // *** data ***

   pixq_Properties *getRectifyEnv(void) const  { return _pRectifyEnv; }
   pixq_ScreenPara *getScreenPara(void) const { return _pScreenPara; }
   pixq_FlipPara *getIndexPara(void) const  { return _pIndexPara; }
   pixq_ImageDualSet *getImageData( void ) const { return _pImageDataSet; }  
   
public:
     bool rectifyAnalyzeTagPoints(bool bItrationse);

public:
   bool rectifyHitAndMatch(int iMouseX, int iMouseY);
   bool rectifyInitSingleTag(pixq_FringeTag *pTag,
      int iSrcX, int iSrcY);

private:
   //
   // rectify
   //
   bool rectifyGenerateControlPoints(bool bRectify);
      
#ifdef _USE_OPENCV2
   bool rectifyGetRorationMatrix(double dH0[3][3], double dH1[3][3]);
#endif // _USE_OPENCV2

   bool rectifyMatchSingleTagPointLevel(const int iLevel,
      const int iCol, const int iRow,
      int &iRightCol, int &iRightRow,
      unsigned short &usCorr, double &dCorr, bool &bUsed, bool bUsePyramid);

   bool rectifyMatchSingleTagPointTop(const int iCol, const int iRow,
      int &iRightCol, int &iRightRow,
      unsigned short &usCorr, double &dCorr, bool &bUsed);

   bool rectifyMatchSingleTagPointPyr(const int iCol, const int iRow,
      int &iRightCol, int &iRightRow,
      unsigned short &usCorr, double &dCorr, bool &bUsed);

   bool rectifyCalibrate(void);

private:

   bool rectifyImageMatchTag(int iTag);
   bool rectifyImageMatchTag(pixq_FringeTag *pTag);

   bool searchStereoFeature(vector<pixq_FringeTag> *pTags);
   bool searchStereoFeature(int iLeft, int iRight, int iTop, int iBottom,
      int *iX, int *iY);

   //
   // pyramid
   //
   bool createBasePyramid(int iLevel);
   bool checkMatrixSize(int *nWidth, int *nHeight);

   bool resampleRgbMatrix(int iSide, int iLevel, int nResample,
      int nResampledHeight, int nResampledWidth);

   bool createMadoImage(int iMadoRadius, int iCenterRow, int iCenterCol,
      pixq_Matrix<double> *InRed,
      pixq_Matrix<double> *InGrn,
      pixq_Matrix<double> *InBlu,
      pixq_Matrix<double> *MadoRed,
      pixq_Matrix<double> *MadoGrn,
      pixq_Matrix<double> *MadoBlu);
   
   bool createMadoImage(int iMadoRadius, int iCenterRow, int iCenterCol,
      pixq_Matrix<double> *InGray,
      pixq_Matrix<double> *MadoGray);

public:
   pixq_FringesTag *getRectifyTag(void) { return _RectifyTags; }
   
public:
   void getStatusColor(const unsigned short usStatus, float *fTagColor) const;
   void getStatusColor(const bool bUsed, const unsigned short usStatus, float *fTagColor) const;
   void getSelectedColor(float *fTagColor) const;

public:
   void refreshEpipolarLine(void);
   void setLastMousePos(int iY) { _nLastMouseY = iY; }
   int getLastMousePos(void) const { return _nLastMouseY; }

   short getPaneContent(void) const { return _sPaneContent; }
};
