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

void rectify_window::getOpenGLInfo(QStringList *strTitles,
                                 QStringList *strValue )
                                 const
{
   char szVersion[STANDARD_BUFFER_SIZE];
   char szVendor[STANDARD_BUFFER_SIZE], szShader[STANDARD_BUFFER_SIZE];
   char szExtensions[STANDARD_BUFFER_SIZE], szRenderer[STANDARD_BUFFER_SIZE];
   QString strData;

   int nTexSize;
    
   strTitles->clear( );
   strValue->clear( );

   //
   
   glGetIntegerv( GL_MAX_TEXTURE_SIZE, &nTexSize );
   strData.sprintf( "%d", nTexSize);

   strncpy( szVendor, (char*)glGetString( GL_VENDOR ), STANDARD_BUFFER_SIZE );
   strncpy( szRenderer, (char*)glGetString( GL_RENDERER ), STANDARD_BUFFER_SIZE );
   strncpy( szVersion, (char*)glGetString( GL_VERSION ), STANDARD_BUFFER_SIZE );
   strncpy( szShader, (char*)glGetString( GL_SHADING_LANGUAGE_VERSION ), STANDARD_BUFFER_SIZE );
   strncpy( szExtensions, (char*)glGetString( GL_EXTENSIONS ), STANDARD_BUFFER_SIZE );
   
   strTitles->push_back( "Vendor" );
   strValue->push_back( szVendor );
   
   strTitles->push_back( "Renderer" );
   strValue->push_back( szRenderer ); 
   
   strTitles->push_back( "OpenGL Version" );
   strValue->push_back( szVersion );
  
   strTitles->push_back( "Shader Version" );
   strValue->push_back( szShader );
   
   strTitles->push_back( "Max Texture Size" );
   strValue->push_back(strData);

   strTitles->push_back( "OpenGL Extensions" );
   strValue->push_back( szExtensions );
   
   return;
}

void rectify_window::listStatistics(QStringList *strTitles,
                                 QStringList *strValue0,
                                 QStringList *strValue1,
                                 QList<int> *iAlignments ) 
const
{    
   pixq_ImageInfo *pInfo0 = getImageInfo( 0 );
   pixq_ImageInfo *pInfo1 = getImageInfo(1);
   pixq_Properties *pEnv = getRectifyEnv();

   strTitles->clear( );
   strValue0->clear( );
   strValue1->clear( );
   iAlignments->clear( );

   if (!validPaneDisplayMode()) {
      strTitles->push_back( "****" );
      strValue0->push_back( "****" );
      strValue1->push_back( "****" );
      iAlignments->push_back( Qt::AlignCenter );
      goto PIX_EXIT;
   }
   
   pInfo0->setStatList(strTitles, strValue0, pEnv);
   pInfo1->setStatList(strTitles, strValue1, iAlignments, pEnv);
   
   // --- Done ---
PIX_EXIT:
   return;
}

//
// list image properties for the current images
//
void rectify_window::getImageProps(QStringList *strTitles, // [i] item na,es
                                 QStringList *strProps0,
                                 QStringList *strProps1,
                                 QList<int> *iAlignments ) 
const
{ 
   pixq_ImageInfo *pInfo0 = getImageInfo( 0 );
   pixq_ImageInfo *pInfo1 = getImageInfo(1);
   pixq_Properties *pEnv = getRectifyEnv();
   
   strTitles->clear( );
   strProps0->clear( );
   strProps1->clear( );
   iAlignments->clear( );
   
   if (!validPaneDisplayMode()) {
      strTitles->push_back( "****" );
      strProps0->push_back( "****" );
      strProps1->push_back( "****" );
      iAlignments->push_back( Qt::AlignCenter );
      goto PIX_EXIT;
   }

   pInfo0->setPropsList(strTitles, strProps0, pEnv);
   pInfo1->setPropsList(strTitles, strProps1, iAlignments,pEnv);
      
PIX_EXIT:
   return;
}



//
// pan the image display so that the selected tag comes t center of screen
//
void rectify_window::centerToTag(int iTag)
{
   int iX, iY;
   pixq_ScreenPara *pScreen = getScreenPara();
   pixq_FringeTag *pTag;
   pixq_FringesTag *pTags = getRectifyTag();
   int nTags = pTags->getTags();
   
   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   if (0 > iTag || nTags <= iTag) {
      goto PIX_EXIT;
   }

   pTag = pTags->getNthTag(iTag);
   iX = (double)pTag->getXTag();
   iY = (double)pTag->getYTag();
   pScreen->JumpToPoint(iX, iY);

   refreshPanes();

PIX_EXIT:
   return;
}


//
// start rectification using current tags
//
bool rectify_window::rectifyCalibrate(void)
{
   bool bRetCode = false;
#ifdef _USE_OPENCV2
   string strMonitor;
   vector<string> vstrMonitors;
   pixq_FringesTag *pTags = getRectifyTag();
   double dH[2][3][3], dRectify[3][3], dInvRectify[3][3];
   int nMinCol, nMaxCol, nTags, k, nWidth, nHeight;

   QString strApplication = _version.getApplication();
   QString strMessage;

   pixq_ImageOpProjective Pro[2];
   
   _bDrvRectified = false;

#ifdef _DEBUG
   char szFileName[FILE_NAME_SIZE];
#endif // _DEBUG2
   
   QApplication::setOverrideCursor(Qt::BusyCursor);

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   // 
   // select checked points on the control panel
   // !MUST do this before getting rotation matrix!
   //

   nTags = pTags->getUsedTags();
   if (7 > nTags) {
      strMessage = getRectifyLabel("Warning", "NoEnoughPoint") + "\n" +
         getRectifyLabel("Warning", "NoRectif");
      QMessageBox::critical(this, strApplication, strMessage);
      goto PIX_EXIT;
   }

   //
   // get rotation matrices from the current set of tags
   //

   nWidth = _ImageInMtx[0][0].getWidth(); 
   nHeight = _ImageInMtx[0][0].getHeight(); 

   if (!rectifyGetRorationMatrix(dH[0], dH[1])) {
      goto PIX_EXIT;
   }

   //  
   
   for (k = 0; k < 2; k++) {
      pTags->ReturnRectify(k, dRectify);
      pTags->ReturnInvRectify(k, dInvRectify);

      Pro[k].Init();
      Pro[k].storeIn(_ImageInMtx[k]); 
      Pro[k].storeOut(_ImageDrvMtx[k]);
      Pro[k].setTransform(dRectify);
      Pro[k].setInvTransform(dInvRectify);
      Pro[k].setMerge(false);
  
      if (!Pro[k].Proc()) {
         QString strApplication = _version.getApplication();
         QMessageBox::warning(this, strApplication, "ERROR! Image Alignment Failed.");
         goto PIX_EXIT;
      }

   }

   if (!createDerivedTexture()) {
      QString strApplication = _version.getApplication();
      QMessageBox::warning(this, strApplication, "ERROR! Failed to Create texture.");
      goto PIX_EXIT;
   }

   setPanesShowImage(rectify_pane::RectifyPaneShowDerived);
   
   _bRectifyHorizontalMarker = true;

   refreshPanes();

   _bDrvRectified = true;
   setRectifyMenuState();

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   QApplication::restoreOverrideCursor();
#endif // _USE_OPENCV2
   return bRetCode;
}


