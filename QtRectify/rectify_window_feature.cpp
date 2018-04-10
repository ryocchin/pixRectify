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

#include "rectify_window.h"
#include "ui_rectify_window.h"

//
// search for stereo matching feature within the rectangle
// based on ning's feature extraction
//
// pTags = three tags
// at least two tags which are two corners of the rectangle
//
// program selects some stereo features with in the rectanlge
// and choose the one closesst to the ractanlg centre
// and set it as the third tag of the pTags
//
bool rectify_window::searchStereoFeature(vector<pixq_FringeTag> *pTags)
{
   bool bRetCode = false;
#ifdef _DEBUG
   bool bShow = false;
#endif // _DEBUG
   
   int iX0, iX1, iY0, iY1, iX, iY, nTags;
   pixq_FringeTag *pTag;

   QString strMessage;

   nTags = (int)pTags->size();
   if (2 > nTags) {
      goto PIX_EXIT;
   }

   // rectangle area on image

   pTag = (pixq_FringeTag*)&pTags->at(0);
   iX0 = pTag->getXTag();
   iY0 = pTag->getYTag();
   pTag = (pixq_FringeTag*)&pTags->at(1);
   iX1 = pTag->getXTag();
   iY1 = pTag->getYTag();

   if (!searchStereoFeature(iX0, iX1, iY0, iY1, &iX, &iY)) {
      goto PIX_EXIT;
   }

   pTags->resize(3);
   pTag = (pixq_FringeTag*)&pTags->at(2);
   pTag->setTag(iX, iY);
   pTag->setCorrStatus(pixq_FringeTag::CorrMatchTypeNotAnalyzed);

#ifdef _DEBUG
   if (bShow) {
      int iCenX = (iX0 + iX1) / 2;
      int iCenY = (iY0 + iY1) / 2;
      strMessage.sprintf("Feature Selected: Center=(%4d,%4d) -> Feature=(%4d,%4d).",
         iCenX, iCenY, iX, iY);
      qDebug() << strMessage;
   }
#endif // _DEBUG

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

// 
// find the best stereo feature inside the square on the image
//
bool rectify_window::searchStereoFeature(int iX0, // [i] 
   int iX1, // [i]
   int iY0, // [i]
   int iY1, // [i]
   int *iFeatureX, // [o]
   int *iFeatureY) // [o] 
{
   bool bRetCode = false;
   int nCount, iRed, iGrn, iBlu, iLeft, iRight, iTop, iBottom, nCropWidth, nCropHeight;
   int iMinX, iMinY, iCropCenX, iCropCenY;
   int i, j, k, iMapMin, iMapMax, iX, iY, nWidth, nHeight;
   int *pLum = NULL;
   unsigned char *pMask = NULL;
   unsigned short usColor;
   unsigned char ucColor[3];
   int *iMap = NULL;
   double dLength, dMinLength;
   pixq_ImageMatrix CropColors[3];
   pixq_Matrix<unsigned char> Crops[3];

   int iCenterX = (iX0 + iX1) / 2;
   int iCenterY = (iY0 + iY1) / 2;

   // default feature position is center of the area
   *iFeatureX = iCenterX;
   *iFeatureY = iCenterY;

   //ImageMonitor *pMonitor = (ImageMonitor*)GetMonitorPane( );
   //QString strMessage;

   // rectangle area on image

   iTop = min(iY0, iY1);
   iBottom = max(iY0, iY1);
   iLeft = min(iX0, iX1);
   iRight = max(iX0, iX1);

   nHeight = _ImageInMtx[0][0].getHeight();
   nWidth = _ImageInMtx[0][0].getWidth();

   iTop = clumpCoo(iTop, nHeight);
   iBottom = clumpCoo(iBottom, nHeight);
   iLeft = clumpCoo(iLeft, nWidth);
   iRight = clumpCoo(iRight, nWidth);

   for (k = 0; k < 3; k++) {
      if (!_ImageInMtx[0][k].cropImage(iTop, iBottom, iLeft, iRight, &CropColors[k])) { 
         //pMonitor->DisplayMessage( "**** ERROR: Failed to crop the image!" );
         goto PIX_EXIT;
      }
   }

   nCropWidth = CropColors[0].getWidth();
   nCropHeight = CropColors[0].getHeight();
   for (k = 0; k < 3; k++) {
      if (!Crops[k].Alloc(nCropHeight, nCropWidth)) {
         goto PIX_EXIT;
      }
   }

   for (i = 0; i < nCropHeight; i++) {
      for (j = 0; j < nCropWidth; j++) {
         for (k = 0; k < 3; k++) {
            usColor = CropColors[k].Get(i, j);
            ucColor[k] = (usColor >> 8) & 0xFF;
         }
         for (k = 0; k < 3; k++) {
            Crops[k].Set(i, j, ucColor[k]);
         }
      }
   }

   // *** copy the image inside the crop area to temp buffer ***

   pLum = (int*)calloc(nCropWidth * nCropHeight, sizeof(int));
   if (!pLum) {
      //pMonitor->DisplayMessage( "**** ERROR: Failed to allocate temporal buffers!" );
      goto PIX_EXIT;
   }

   pMask = (unsigned char*)calloc(nCropWidth * nCropHeight, sizeof(unsigned char));
   if (!pMask) {
      //pMonitor->DisplayMessage( "**** ERROR: Failed to allocate temporal buffers!" );
      goto PIX_EXIT;
   }

   iMap = (int*)calloc(nCropWidth * nCropHeight, sizeof(int));
   if (!iMap) {
      //pMonitor->DisplayMessage( "**** ERROR: Failed to allocate temporal buffers!" );
      goto PIX_EXIT;
   }

   k = 0;
   for (i = 0; i < nCropHeight; i++) {
      for (j = 0; j < nCropWidth; j++) {

         //lColor = Crop.Get( i, j );

         ucColor[0] = Crops[0].Get(i, j);
         ucColor[1] = Crops[1].Get(i, j);
         ucColor[2] = Crops[2].Get(i, j);

         iRed = (int)(ucColor[0] << 2);
         iGrn = (int)(ucColor[1] << 2);
         iBlu = (int)(ucColor[2] << 2);

         pLum[k] = (int)((iBlu + (iGrn << 1) + iRed) >> 2);
         k++;
      }
   }

   // *** get feature positions ***

   selectMatchFeature(pLum,
      pMask,
      iMap,
      nCropWidth, nCropHeight,
      3, 3, //!< window 7x7
      10,   //!< horizontal distance
      1,    //!< not quite useful
      10); //!< percentage of features 

   // features are marked in the output buffer pMask, as 1

   k = 0;
   nCount = 0;
   iMapMin = iMap[0];
   iMapMax = iMap[0];
   for (i = 0; i < nCropHeight; i++) {
      for (j = 0; j < nCropWidth; j++) {

         if (pMask[k]) {
            //lColor = RGB( 255, 0, 255 );
            ucColor[0] = 255;
            ucColor[1] = 0;
            ucColor[2] = 255;
            nCount++;
         }
         else {
            //lColor = Crop.Get( i, j );    
            ucColor[0] = Crops[0].Get(i, j);
            ucColor[1] = Crops[1].Get(i, j);
            ucColor[2] = Crops[2].Get(i, j);
         }

         //Crop.Set( i, j, lColor );
         Crops[0].Set(i, j, ucColor[0]);
         Crops[1].Set(i, j, ucColor[1]);
         Crops[2].Set(i, j, ucColor[2]);

         iMapMin = min(iMap[k], iMapMin);
         iMapMax = max(iMap[k], iMapMax);

         k++;
      }
   }

   if (0 >= nCount) {
      //pMonitor->DisplayMessage( "***No feature selected within the rectangle ***" );
      goto PIX_EXIT;
   }

   //strMessage.sprintf( "Total %d features extracted from %d pixels in the rectangle area.",
   //   nCount, nCropHeight * nCropWidth );
   //pMonitor->DisplayMessage( strMessage );

   // find the closest feature to the center of the area, as iMinX and iMinY

   iCropCenX = nCropWidth / 2;
   iCropCenY = nCropHeight / 2;

   k = 0;
   dMinLength = 2.0 * (double)nCropHeight * (double)nCropWidth;
   dMinLength = dMinLength * dMinLength;

   for (i = 0; i < nCropHeight; i++) {
      for (j = 0; j < nCropWidth; j++) {
         if (pMask[k]) {
            iX = j - iCropCenX;
            iY = i - iCropCenY;
            dLength = (double)iX *  (double)iX + (double)iY *  (double)iY;
            if (dLength < dMinLength) {
               dMinLength = dLength;
               iMinX = j;
               iMinY = i;
            }
         }
         k++;
      }
   }

   // set this feature point as the third of the pTags tags

   *iFeatureX = iLeft + iMinX;
   *iFeatureY = iTop + iMinY;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   if (pLum) {
      free(pLum);
      pLum = NULL;
   }
   if (pMask) {
      free(pMask);
      pMask = NULL;
   }
   if (iMap) {
      free(iMap);
      iMap = NULL;
   }
   for (k = 0; k < 3; k++) {
      CropColors[k].free();
   }
   for (k = 0; k < 3; k++) {
      Crops[k].free();
   }
   return bRetCode;
}