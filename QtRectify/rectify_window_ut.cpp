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

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

#include "rectify_window.h"
#include "ui_rectify_window.h"

//
// notes:
// this should be only called onece at the start-up!
//
void rectify_window::initRectifyData(void)
{
   int k;
   QString strApplication = _version.getApplication();
   QString strOrganisation = _version.GetCompany();
  
   // clear all data

   _pRectifyEnv = new pixq_Properties;
   _pRectifyEnv->initEnv(strOrganisation, strApplication);
   
   _pImageDataSet = new pixq_ImageDualSet;
   _pImageDataSet->Clear( );
   
   _ImageProps[0] = new pixq_ImageInfo;
   _ImageProps[1] = new pixq_ImageInfo;

   // --- new project and data shot ---

   for( k = LEFT ; k <= RIGHT ; k++ ) {
      
      if( _pImgTexture[k] ) {
         delete _pImgTexture[k];
         _pImgTexture[k] = NULL;
      }

      _pImgTexture[k] = new pixq_DepthTexture;
      _pImgTexture[k]->Init( );   
   }

   //

   if (_RectifyTags) {
      delete _RectifyTags;
      _RectifyTags = NULL;
   }

   _RectifyTags = new pixq_FringesTag;
   _RectifyTags->init();

   // --- init flip parameters ---

   _pScreenPara = new pixq_ScreenPara;
   _pIndexPara = new pixq_FlipPara;
    
   return;
}

void rectify_window::storeEnv(void)
{
   pixq_Properties *pEnv = getRectifyEnv();

   QString strApplication = _version.getApplication();
   QString strOrganisation = _version.GetCompany();

   pEnv->setRegEnv(strOrganisation, strApplication);

   return;
}

void rectify_window::releaseData(void)
{   
   int k, l;
	
   if( NULL != _pScreenPara ) {
      delete _pScreenPara;
      _pScreenPara = NULL;
   }

   if (NULL != _pIndexPara) {
      delete _pIndexPara;
      _pIndexPara = NULL;
   }
   
   if (NULL != _pRectifyEnv) {
      delete _pRectifyEnv;
      _pRectifyEnv = NULL;
   }

   if( NULL != _pImageDataSet ) {
      delete _pImageDataSet;
      _pImageDataSet = NULL;
   }
   
   for( k = 0 ; k <= 1 ; k++ ) {
      if( NULL != _ImageProps[k] ) {
         delete _ImageProps[k];
         _ImageProps[k] = NULL;
      }
   }

   for( k = LEFT ; k <= RIGHT ; k++ ) {
      if( _pImgTexture[k] ) {
         delete _pImgTexture[k];
         _pImgTexture[k] = NULL;
      }
   }

   for( k = 0 ; k < 2 ; k++ ) {
      for( l = 0 ; l < 3 ; l++ ) {
         _ImageInMtx[k][l].free();
      }
   }

   if (_RectifyTags) {
      delete _RectifyTags;
      _RectifyTags = NULL;
   }

   // *** others ***

   resetLeftMouseMode();

   return;
}

//
// notes:
// ResetDocAll
// 
void rectify_window::resetAllData(void)
{
   pixq_ImageDualSet *pData = getImageData();
   short sPaneShowMode = pixq_ScreenPara::PixPaneShowNone;
   int k, l;
   
   // --- init sequences ---
   
   setImageLoading(false);
   
   _RectifyTags->init();
   pData->Clear( );

   for( k = 0 ; k < 2 ; k++ ) {
      _ImageProps[k]->clear( );
      for (l = 0; l < 3; l++) {
         _ImageInMtx[k][l].free();
         _ImageDrvMtx[k][l].free();
      }
   }

   _bDrvRectified = false;

   // *** reset panes ***
   
   setPanesShowMode(sPaneShowMode);
   
   setPanesShowImage(rectify_pane::RectifyPaneShowNone);
   
   resetLeftMouseMode();

   // --- delete texture ---
     
   _pImgTexture[LEFT]->unloadAll( ); 
   _pImgTexture[RIGHT]->unloadAll();
   
   _Image_Pane[0]->ResetPane( );  
   _Image_Pane[1]->ResetPane(); 
   _Index_Pane->ResetPane(); 
   
   // release texture work buffer
   
   _pScreenPara->DeInit();
   _pIndexPara->DeInit();
   
   resetMatch();

   _bRectifyHorizontalMarker = false;

   _sLeftMouseMode = MouseLeftClickNone;

   setRectifyMenuState();
   
//PIX_EXIT:
   return;
}

bool rectify_window::isThreadRunning(void)
{
   bool bRunnningThread = false;

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
   
   return bRunnningThread;
}

//
// cleat matching related data
//
void rectify_window::resetMatch(void)
{
   pixq_FringesTag *pTags = getRectifyTag();
   int iLevel, k;
   
   // release all intermediate matrices

   for (k = 0; k < 2; k++) {

      for (iLevel = 0; iLevel < _nPyramidLevel; iLevel++) {
         _usPyramidRed[iLevel][k].free();
         _usPyramidGrn[iLevel][k].free();
         _usPyramidBlu[iLevel][k].free();
         _usPyramidGray[iLevel][k].free();

         _dPyramidRed[iLevel][k].free();
         _dPyramidGrn[iLevel][k].free();
         _dPyramidBlu[iLevel][k].free();
         _dPyramidGray[iLevel][k].free();

         _usPyramidRed[iLevel][k].setFrameNumber(-1);
         _usPyramidGrn[iLevel][k].setFrameNumber(-1);
         _usPyramidBlu[iLevel][k].setFrameNumber(-1);
         _usPyramidGray[iLevel][k].setFrameNumber(-1);

         _dPyramidRed[iLevel][k].setFrameNumber(-1);
         _dPyramidGrn[iLevel][k].setFrameNumber(-1);
         _dPyramidBlu[iLevel][k].setFrameNumber(-1);
         _dPyramidGray[iLevel][k].setFrameNumber(-1);
      }
   }
   
   //

   pTags->init();

   clearGridSelection();

   return;
}


void rectify_window::clearGridSelection(void)
{
   int i;
   pixq_FringeTag *pTag;
   pixq_FringesTag *pTags = getRectifyTag();
   int nTags = pTags->getTags();

   for (i = 0; i < nTags; i++) {
      pTag = pTags->getNthTag(i);
      pTag->SetSelected(false);
   }

   return;
}

//
// get texture ID for the side/frame
//
unsigned int rectify_window::getTexture(int iSide, // [i] 0 or 1
                                      int iFrame ) // [i] frame number
{
   unsigned int uiImgTexture = _pImgTexture[iSide]->getTexture(iFrame);

   return uiImgTexture;
}

//
// set the "second pane mode" for the second pane
//
// notes:
// second pane mode for the pane0 and the index 0 has no meaning
// 
void rectify_window::setPanesShowMode(short sPaneContent)
{
   pixq_ScreenPara *pScreen = getScreenPara();
   QSize in_rect, out_rect;
   pScreen->Lock( ); 
   
   //

   switch ( sPaneContent) {
   case pixq_ScreenPara::PixPaneShowHorizontalSplit:
      // stereo images
      _sPaneContent = sPaneContent;
      setPanesShowStereoMode();
      break;

   case pixq_ScreenPara::PixPaneShowFirst:
      // anaglyph image
      _sPaneContent = sPaneContent;
      setPanesShowMonoMode();
      break;

   default:
      goto PIX_EXIT;
      break;
   }
   
PIX_EXIT:
   return;
}


void rectify_window::setPanesShowMonoMode(void)
{
   pixq_ScreenPara *pScreen = getScreenPara();
   QSize in_rect, out_rect;
   pScreen->Lock();

   //

   in_rect = _Image_Pane[0]->size();

   _Image_Pane[0]->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
   _Image_Pane[1]->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

   _Image_Pane[0]->show();
   _Image_Pane[1]->show();
   _ImageSplitter->setOrientation(Qt::Horizontal);
   _Image_Pane[1]->setFocusPolicy(Qt::StrongFocus);
   _Image_Pane[1]->setMouseTracking(true);
   fixRectifyPanes(2);

   _Image_Pane[0]->setFocusPolicy(Qt::StrongFocus);
   _Image_Pane[0]->setMouseTracking(true);

   // modify geometry of windows

   _ImageSplitter->updateGeometry();
   _ImageSplitter->update();

   _Image_Pane[0]->adjustSize();
   _Image_Pane[1]->adjustSize();
   _Image_Pane[0]->updateGeometry();
   _Image_Pane[1]->updateGeometry();

   _Image_Pane[0]->update();
   _Image_Pane[1]->update();

   out_rect = _Image_Pane[0]->size();
   pScreen->SwitchAreaType(_sPaneContent, out_rect);

   //

   _bRectifyHorizontalMarker = false;

   refreshPanes();
   setRectifyMenuState();

//PIX_EXIT:
   pScreen->Unlock();
   return;
}

void rectify_window::setPanesShowStereoMode(void)
{
   pixq_ScreenPara *pScreen = getScreenPara();
   QSize in_rect, out_rect;
   pScreen->Lock();
   
   //

   in_rect = _Image_Pane[0]->size();

   _Image_Pane[0]->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
   _Image_Pane[1]->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

   _Image_Pane[0]->show();
   _Image_Pane[1]->show();
   _ImageSplitter->setOrientation(Qt::Horizontal);
   _Image_Pane[1]->setFocusPolicy(Qt::StrongFocus);
   _Image_Pane[1]->setMouseTracking(true);
   fixRectifyPanes(2);

   _Image_Pane[0]->setFocusPolicy(Qt::StrongFocus);
   _Image_Pane[0]->setMouseTracking(true);

   // modify geometry of windows

   _ImageSplitter->updateGeometry();
   _ImageSplitter->update();

   _Image_Pane[0]->adjustSize();
   _Image_Pane[1]->adjustSize();
   _Image_Pane[0]->updateGeometry();
   _Image_Pane[1]->updateGeometry();

   _Image_Pane[0]->update();
   _Image_Pane[1]->update();

   out_rect = _Image_Pane[0]->size();
   pScreen->SwitchAreaType(_sPaneContent, out_rect);

   //

   refreshPanes();
   setRectifyMenuState();

//PIX_EXIT:
   pScreen->Unlock();
   return;
}

QString rectify_window::getApplication(void)
{
   pixq_Version *ver = getVersion();
   QString strName = ver->getApplication();

   return strName;
}

bool rectify_window::setProperties(void)
{
   bool bRetCode = false;
   pixq_Properties *pEnv = getRectifyEnv();
   int iNewLang, iOldLang, iMode;

   QString strApplication = _version.getApplication();
   QString strOrganisation = _version.GetCompany();

   // show dialog and get the results

   iOldLang = pEnv->_SystemInterfaceLanguage.getInteger();
   iMode = EnvModeRectify;
   if (!showPixProperty_PC(strOrganisation, strApplication, pEnv, iMode)) {
      goto PIX_EXIT;
   }

   storeEnv();

   // change the language if it was changed

   iNewLang = pEnv->_SystemInterfaceLanguage.getInteger();
   if (iNewLang != iOldLang) {
      rectify_table *pTab = getTablePane();
      setMenuLabels();
      setDockLabels();

      pTab->setRectifyTags();
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

void rectify_window::setPanesCursor(QCursor cur)
{
   setCursor( cur );

   _Image_Pane[0]->setCursor( cur ); 
   _Image_Pane[1]->setCursor(cur);
   _Index_Pane->setCursor(cur); 

   QApplication::processEvents( );

   return;
}

void rectify_window::refreshPanes(void)
{
   if (_Image_Pane[0]->isVisible()) {
      _Image_Pane[0]->refreshSingle();
      //_Image_Pane[0]->update();
   }
   
   if (_Image_Pane[1]->isVisible()) {
      _Image_Pane[1]->refreshSingle();
      //_Image_Pane[1]->update();
   }

   if (_Index_Pane->isVisible()) { 
      //_Index_Pane->update(); 
      _Index_Pane->refreshSingle(); 
   }
   
   return;
}

//
// get image file name according to the mode and side
//
// notes:
// strFile maight be null string if this is dir mode
// and there is no file for the current frame number
//
bool rectify_window::getSideFile(int iSide, // [i] 0 or 1
                              QString *strFile )
                              const
{
   bool bRetCode = false;
   pixq_ImageDualSet *pData = getImageData( );

   if( 0 > iSide || 1 < iSide ) {
      goto PIX_EXIT;
   }

   if (!pData->getCurrentFile(iSide, strFile)) {
      goto PIX_EXIT;
   }      

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}

//
// display color under the mouse on status bar
//
void rectify_window::getColor(int iSide, int iMouseX, int iMouseY)
{
   int k, iPixX, iPixY, nScale[2];
   double dPixX, dPixY;

   unsigned short usRed, usGrn, usBlu;
   unsigned short usScaledRed, usScaledGrn, usScaledBlu;
   QString strValue, strCoo, strColor[2];

   pixq_ImageInfo *pInfo[2];
   pInfo[0] = getImageInfo(0);
   pInfo[1] = getImageInfo(1);

   for (k = 0; k < 2; k++) {
      nScale[k] = pInfo[k]->getDepthScale();
   }
   const pixq_ScreenPara *pScreen = getScreenPara();
   const pixq_PanePara *pFlip = NULL; 
   const pixq_FlipPara *pIndex = getIndexPara( );  
   
   if( pScreen->IsLocked( ) ) { 
      // screen is busy
      goto PIX_EXIT;
   }

   // coordinate    
   switch( iSide ) {

   case rectify_pane::RectifyPaneSplitLeft: // left/upper split pane 
      pFlip = pScreen->getLeftFlip();
         pFlip->viewportToPixelCoo(iMouseX, iMouseY, &dPixX, &dPixY);
      iPixX = (int)floor( dPixX );
      iPixY = (int)floor( dPixY );
      break;

   case rectify_pane::RectifyPaneSplitRight: // right split pane 
      pFlip = pScreen->getRightFlip();
      pFlip = pScreen->getRightFlip();
      pFlip->viewportToPixelCoo(iMouseX, iMouseY, &dPixX, &dPixY);
      iPixX = (int)floor( dPixX );
      iPixY = (int)floor( dPixY );
      break;

   case rectify_pane::RectifyPaneIndex:
      pIndex->viewportToPixelCoo(iMouseX, iMouseY, &dPixX, &dPixY);
      iPixX = (int)floor( dPixX );
      iPixY = (int)floor( dPixY );
      break;

   case rectify_pane::RectifyPaneUnknown:
   default:
      goto PIX_EXIT;
   }

   // *** First image -> always display pixel value! ***

   switch( iSide ) {

   case rectify_pane::RectifyPaneSplitLeft: // left split pane 
   case rectify_pane::RectifyPaneSplitRight: // right split pane 
   case rectify_pane::RectifyPaneIndex:
      
      strCoo.sprintf( "Coo(%7.2f,%7.2f)", dPixX, dPixY );
      //strCoo.sprintf( "Coo(%04d,%04d), iPixX, iPixY, usRed );
      
      for( k = 0 ; k < 2 ; k++ ) {
         if( _ImageInMtx[k][0].IsInside( iPixX, iPixY ) ) {
            //
            usRed = _ImageInMtx[k][0].Get( iPixY, iPixX );
            usGrn = _ImageInMtx[k][1].Get( iPixY, iPixX );
            usBlu = _ImageInMtx[k][2].Get( iPixY, iPixX );
            //
            usScaledRed = usRed / nScale[k];
            usScaledGrn = usGrn / nScale[k];
            usScaledBlu = usBlu / nScale[k];
            //
            //strColor[k].sprintf("[%05d,%05d,%05d]", usRed, usGrn, usBlu);
            strColor[k].sprintf("[%d,%d,%d]", usScaledRed, usScaledGrn, usScaledBlu);
         } else {
            strColor[k] = "[**,**,**]";
         }
      }

      strValue = strCoo + ": Color" + strColor[0] + "/" + strColor[1];
      _statusLabel[0]->setText( strValue );

      _statusLabel[0]->setBackgroundRole( QPalette::Base );

      break;
   }

PIX_EXIT:
   return;
}

bool rectify_window::loadRectifyImages(const QString strFile0,
   const QString strFile1)
{
   bool bRetCode = false;
   pixq_Properties *pEnv = getRectifyEnv();
   pixq_ImageDualSet *pData = getImageData();
   QFileInfo finfo;
   QString strFile[2];

   QString strApplication = _version.getApplication();
   QString strOrganisation = _version.GetCompany();

   QStringList forSort;

   short sPaneShowMode = pixq_ScreenPara::PixPaneShowHorizontalSplit;
   
   //

   QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
   setPanesCursor(QCursor(Qt::BusyCursor));

   setImageLoading(true);
   
   // sort dir names by name

   forSort.clear();
   forSort.push_back(strFile0);
   forSort.push_back(strFile1);
   forSort.sort(Qt::CaseSensitive);
   strFile[0] = forSort.at(0);
   strFile[1] = forSort.at(1);

   //

   pData->setImagePair(strFile[0], strFile[1]);

   // --- start to draw! ---  
   
   setPanesShowMode(sPaneShowMode); 
      
   // load input images

   if (createRectifyBitmaps()) {
      setPanesShowImage(rectify_pane::RectifyPaneShowInput);
      setFrameStatusBar();
      setRectifyMenuState();
      refreshPanes();
   }
   else {
      setPanesShowImage(rectify_pane::RectifyPaneShowNone);
      setFrameStatusBar();
      setRectifyMenuState();
      refreshPanes();
      goto PIX_EXIT;
   }

   // *** remember the directory for the next time ***

   finfo.setFile(strFile[0]);
   pEnv->_RectifyLastLeftImageDir.Set(finfo.path());

   finfo.setFile(strFile[1]);
   pEnv->_RectifyLastRightImageDir.Set(finfo.path());

   pEnv->setRegEnv(strOrganisation, strApplication);

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   QApplication::restoreOverrideCursor();
   setPanesCursor(QCursor(Qt::ArrowCursor));
   setImageLoading(false);
   return bRetCode;
}



bool rectify_window::selectLoadImagePair(void)
{
   bool bRetCode = false;
   bool bStatus;
   int nSize, nSelected;
   pixq_Properties *pEnv = getRectifyEnv();
   
   QString strAppPath, strLabel, strLastDir[2], strFilters, strSelectedFilter;
   QString strMessage, strFile[2];
   QStringList fileNames;
   
   QFileDialog::Options options;
     
   // reset data settings
    
   resetAllData();

   // show dialog and get the results
   
   strAppPath = QFileInfo(QCoreApplication::applicationDirPath()).filePath();

   strLastDir[0] = pEnv->_RectifyLastLeftImageDir.getString();
   strLastDir[1] = pEnv->_RectifyLastRightImageDir.getString();

#ifdef _DEBUG
   qDebug() << strAppPath;
#endif // _DEBUG

   if (strLastDir[0].isEmpty()) {
      //strLastDir[0] = QDir::currentPath();
      strLastDir[0] = strAppPath;
      strLastDir[0] += QDir::separator();
      strLastDir[0] += QLatin1String("sample");
   }

   if (strLastDir[1].isEmpty()) {
      strLastDir[1] = strAppPath;
      strLastDir[1] += QDir::separator();
      strLastDir[1] += QLatin1String("sample");
   }

#ifdef _DEBUG
   qDebug() << strLastDir[0];
   qDebug() << strLastDir[1];
#endif // _DEBUG

   imageMagickFileFilter_PI(true, strFilters);
   nSize = (int)strFilters.size( );
  
   //
   // show dialog and select two images
   //
  
   options = QFileDialog::ReadOnly;
   strLabel = tr("Select Two Images");
   nSelected = 0;
   bStatus = true;
   while( bStatus ) {
      fileNames = QFileDialog::getOpenFileNames( this, 
         strLabel,
         strLastDir[nSelected], 
         strFilters, 
         &strSelectedFilter,
         options );

      nSize = fileNames.size( );
      if( 0 == nSize ) {
         // cancelled
         bStatus = false;
         goto PIX_EXIT;
      } else if( 1 == nSize ) {
         // one file selected
         if( 0 == nSelected ) {
            // this is first file - set it as the first file
            strFile[0] = fileNames.at( 0 );
            nSelected = 1;
         } else {
            // this is second file - pair selected!
            strFile[1] = fileNames.at( 0 );
            bStatus = false;
         }
      } else if( 2 == nSize ) {
         // two files selected
         if( 0 == nSelected ) {
            strFile[0] = fileNames.at( 0 );
            strFile[1] = fileNames.at( 1 );
            bStatus = false;
         } else {
            // one file was already selected and was waiting for the second ONE 
            QString strApplication = _version.getApplication();
            strMessage = getRectifyLabel("Warning", "SelectSecond");
            QMessageBox::warning(this, strApplication, strMessage);
            continue;
         }
      } else {
         // more than 2 files selected
         QString strApplication = _version.getApplication();
         strMessage = getRectifyLabel("Warning", "MoreThan2");
         QMessageBox::warning(this, strApplication, strMessage);
         continue;
      }
   }

#ifdef _DEBUG
   qDebug() << strFile[0];
   qDebug() << strFile[1];
#endif // _DEBUG

   if (!loadRectifyImages(strFile[0], strFile[1])) {
      goto PIX_EXIT;
   }
    
   // --- Done --- 
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


bool rectify_window::validPaneDisplayMode(void)
   const
{
   bool bRetCode = false;
   short sPaneShowImagee = getPanesShowImage();
   
   switch (sPaneShowImagee) {
   case rectify_pane::RectifyPaneShowInput:
   case rectify_pane::RectifyPaneShowDerived:
      break;

   case rectify_pane::RectifyPaneShowNone:
      goto PIX_EXIT;
      break;

   default:
      goto PIX_EXIT;
      break;
   }

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


bool rectify_window::saveRectifiedRight(void)
{
   bool bRetCode = false;
   pixq_Properties *pEnv = getRectifyEnv();
   pixq_ImageDualSet *pData = getImageData();

   QFileInfo finfo;
   QString strInPath, strLabel, strDefFile, strFilters, strSelectedFilter, strEntry;
   QString strExt, strBase, strMessage, strSuffix, strLeftFile, strRightFile, strOutFile;

   QString strApplication = _version.getApplication();
   QString strOrganisation = _version.GetCompany();
   
   QFileDialog::Options options;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }
   
   if (!_bDrvRectified) {
      goto PIX_EXIT;
   }
   
   //
   // set default new right file name
   //

   if (!pData->getCurrentFiles(&strLeftFile, &strRightFile)) {
      goto PIX_EXIT;
   }

   strSuffix = pEnv->_RectifyRectifiedFileSuffix.getString();

   finfo.setFile(strRightFile);
   strInPath = finfo.absolutePath();
   strBase = finfo.completeBaseName();
   strEntry = strBase + strSuffix;
   strExt = finfo.suffix();
   strDefFile = strInPath + "/" + strEntry + "." + strExt;
   
   //
   // select output image
   //

   imageMagickFileFilter_PI(false, strFilters);
   //options = QFileDialog::DontConfirmOverwrite;
   options = 0;

   strLabel = getRectifyLabel("Operation", "Save");

   strOutFile = QFileDialog::getSaveFileName(this,
      strLabel, 
      strDefFile,
      strFilters,
      &strSelectedFilter,
      options);

   if (strOutFile.isEmpty()) {
      // cancelled
      qDebug() << "Save Cancelled!";
      goto PIX_EXIT;
   }

   //
   // save images
   //

   QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));

   if (!magickSaveImage_PI( strOutFile,
      &_ImageDrvMtx[1][0],
      &_ImageDrvMtx[1][1],
      &_ImageDrvMtx[1][2])) {
         strMessage = QString("Failed to Save Image: ") + strOutFile;
         QMessageBox::warning(this, strApplication, strMessage);
      goto PIX_EXIT;
   }

   qDebug() << "Rectified Image saved as " << strOutFile;
   
   // --- Done --- 
   bRetCode = true;
PIX_EXIT:
   QApplication::restoreOverrideCursor();
   return bRetCode;
}


