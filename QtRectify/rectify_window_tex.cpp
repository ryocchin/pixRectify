#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_panes.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

#include "rectify_table.h"
#include "rectify_window.h"

//
// load double images and copy it to each pane
//
bool rectify_window::createRectifyBitmaps(void)
{
   bool bRetCode = false;
   bool bExpand;
	QString strImageFile[2], strFrame, strMessage;
   int i, k, nWidth, nHeight, iLevel, nImgXSize[2], nImgYSize[2];

   const int nPanes = 3;
   rectify_pane *pPanes[nPanes];
   pixq_ImageOpGray Op;
      
   QSize rect;
      
   short sPaneMode = pixq_ScreenPara::PixPaneShowHorizontalSplit;
   pixq_ScreenPara *pScreen = getScreenPara();
   pixq_FlipPara *pIndex = getIndexPara();
   
   unsigned short usFill = 65536 / 2 - 1;
   unsigned short usGray = 65536 / 4 - 1;   
   bool bGrayOutput = false;

   //qDebug( ) << "Entered createRectifyBitmaps().";
   
   pScreen->Lock( );

#ifdef _DEBUG
   unsigned short usMin[2][3], usMax[2][3], usMean[2][3], usStd[2][3];
#endif // _DEBUG

   pPanes[0] = (rectify_pane*)_Image_Pane[0]; 
   pPanes[1] = (rectify_pane*)_Image_Pane[1]; 
   pPanes[2] = (rectify_pane*)_Index_Pane;

   for( k = 0 ; k < 2 ; k++ ) {
      if( !getSideFile( k, &strImageFile[k] ) ) {
         goto PIX_EXIT; 
      }
   }

   // --- initialize viewport ---
   // --- init image texture ---
   for (k = 0; k < nPanes; k++) {
      pPanes[k]->setCurrentViewport( );
      pPanes[k]->initTexture();
   }

   // *** load image and change to 3-channel and 8-bit depth ***
   
   for( k = 0 ; k < 2 ; k++ ) {      
      for( i = 0 ; i < 3 ; i++ ) {
         _ImageInMtx[k][i].free();
      }

      if( strImageFile[k].isEmpty( ) ) {
         nImgXSize[k] = 0;
         nImgYSize[k] = 0;
         continue;
      }
      
      //qDebug( ) << "Calling loadRectifyFrame()." << k;

      if (!loadRectifyFrame( strImageFile[k], _ImageProps[k],
         &_ImageInMtx[k][0], 
         &_ImageInMtx[k][1], 
         &_ImageInMtx[k][2])) {
            QString strApplication = _version.getApplication();
            strMessage = QString( "Failed to Load Image: " ) +  strImageFile[k];
            QMessageBox::warning(this, strApplication, strMessage);
            goto PIX_EXIT; 
      }
  
      nImgXSize[k] = _ImageInMtx[k][0].getWidth();
      nImgYSize[k] = _ImageInMtx[k][0].getHeight();
   }


#ifdef _DEBUG
for( k = 0 ; k < 2 ; k++ ) {
   for( i = 0 ; i < 3 ; i++ ) {
      _ImageInMtx[k][i].Statistics( &usMin[k][i], &usMax[k][i], &usMean[k][i], 
         &usStd[k][i] );
   }
}
#endif // _DEBUG

   // --- set the image size to global ---
     
   nWidth = max( nImgXSize[0], nImgXSize[1] );
   nHeight = max( nImgYSize[0], nImgYSize[1] );
      
   // --- if the size of two images don't match, set them to the larger one ---

   for( k = 0 ; k < 2 ; k++ ) {
      bExpand = false;
      if( nWidth != nImgXSize[k] ) {
         bExpand = true;
      }

      if( nHeight != nImgYSize[k] ) {
         bExpand = true;
      }

      // --- image must be resized here if two image are not same size ---
      
      if( !bExpand ) {
         continue;
      }

      strMessage.sprintf( "Expanding Image to %dW * %dH.", nWidth, nHeight );
         
      for( i = 0 ; i < 3 ; i++ ) {
         // if one image is shorter(in row) thatn others
         // fill it with gray value from top
         // set 'bFromTop' to false - don't change it!
         _ImageInMtx[k][i].crop(nHeight, nWidth, usFill, false);
      }
   }

   // create double-precision image
   // --- create pyramid images ---
   
   for (iLevel = 0; iLevel < _nPyramidLevel; iLevel++) {
      //qDebug() << "...Generating Image Pyramids: " << iLevel + 1 << "/" << _nPyramidLevel;
      if (!createBasePyramid(iLevel)) {
         qDebug() << "ERROR! Pyramid Images...Failed!";
         goto PIX_EXIT;
      }
   }

   // --- prepare derived images ---

   for (k = 0; k < 2; k++) {

      // allocate derived images

      for (i = 0; i < 3; i++) {
         if (!_ImageDrvMtx[k][i].Alloc(nHeight, nWidth)) {
            goto PIX_EXIT;
         }
      }
            
      if (bGrayOutput) {
         
         // set grayscale version of input image as derived image

         Op.storeIn(_ImageInMtx[k]);
         Op.storeOut(_ImageDrvMtx[k]);

         if (!Op.Proc()) {
            for (i = 0; i < 3; i++) {
               if (!_ImageDrvMtx[k][i].copy(&_ImageInMtx[k][i])) {
                  goto PIX_EXIT;
               }
            }
         }
      }
      else {
         for (i = 0; i < 3; i++) {
            _ImageDrvMtx[k][i].Fill(usGray);
         }
      }
   }

#ifdef _DEBUG
for( k = 0 ; k < 2 ; k++ ) {
   for( i = 0 ; i < 3 ; i++ ) {
      _ImageInMtx[k][i].Statistics( &usMin[k][i], &usMax[k][i], &usMean[k][i], 
         &usStd[k][i] );
   }
}
#endif // _DEBUG

   if (!createLoadedTexture()) { 
      goto PIX_EXIT;
   }

   if (!createDerivedTexture()) {
      goto PIX_EXIT;
   }

   // index

   if (!CreateIndexTexture(pPanes[2], 0)) {
      goto PIX_EXIT;
   }

   // --- initialize texture copy parameters ---

   rect = _Image_Pane[0]->size( );   
   pScreen->SetFlipRatio( sPaneMode, rect ); 
   pScreen->InitFlip( nWidth, nHeight ); 
   pScreen->setSingleViewports();
   pScreen->SetSingleConversion( ); 

   rect = _Index_Pane->size( );  
   pIndex->SetFlipRatio( rect );  
   pIndex->InitFlip( nWidth, nHeight, nWidth, nHeight );  
   pIndex->setSingleViewports(rect);
   pIndex->SetSingleConversion( );  
   
   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   pScreen->Unlock( );
   return bRetCode;
}

bool rectify_window::loadRectifyFrame(const QString strFile,
                             pixq_ImageInfo *info,
                             pixq_ImageMatrix *usRed, 
                             pixq_ImageMatrix *usGrn, 
                             pixq_ImageMatrix *usBlu )
{
   bool bRetCode = false;
   
   // --- file existence ---

   if (!fileExist_PC(strFile)) {
      goto PIX_EXIT;  
   }

   // load supported image 

   if( !magickLoadImage_PI( strFile, info, usRed, usGrn, usBlu ) ) {
      goto PIX_EXIT;
   }

	// --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// set loade image matrix to inout 
//
bool rectify_window::createLoadedTexture(void)
{
   bool bRetCode = false;
   int iPane;
            
   // *** create image texture for the right pane from the derived image matrices ***
     
   for( iPane = 0 ; iPane < 2 ; iPane++ ) {

      rectify_pane *pPane = _Image_Pane[iPane]; 

      // input image

      if (!pPane->createPaneTexture(&_ImageInMtx[iPane][0],
         &_ImageInMtx[iPane][1], &_ImageInMtx[iPane][2], 0)) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}

bool rectify_window::createDerivedTexture(void)
{
   bool bRetCode = false;
   int iPane;

   // *** create image texture for the right pane from the derived image matrices ***

   for (iPane = 0; iPane < 2; iPane++) {

      rectify_pane *pPane = _Image_Pane[iPane]; 

      // derived image

      if (!pPane->createPaneTexture(&_ImageDrvMtx[iPane][0],
         &_ImageDrvMtx[iPane][1], &_ImageDrvMtx[iPane][2], 1)) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// create image texture for given pane from given image matrix(0/1/2)
//
bool rectify_window::CreateIndexTexture(rectify_pane *pPane, // [i] for which pane?
                                     int iIMage )  // [i] which image matrix to use, 0 or 1
{
   bool bRetCode = false;

   if (!pPane->createPaneTexture(&_ImageInMtx[iIMage][0],
      &_ImageInMtx[iIMage][1], &_ImageInMtx[iIMage][2], iIMage ) ) {
         goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT: 
   return bRetCode;
}

short rectify_window::getPanesShowImage(void)
const
{
   short sImage = _Image_Pane[0]->getPaneShowImage(); 

   return sImage;
}

void rectify_window::setPanesShowImage(short sPaneMode)
{
   _Image_Pane[0]->setPaneShowImage(sPaneMode); 
   _Image_Pane[1]->setPaneShowImage(sPaneMode); 
   _Index_Pane->setPaneShowImage(rectify_pane::RectifyPaneShowInput);
   
   refreshPanes();
   
   setRectifyMenuState();
   
   return;
}
