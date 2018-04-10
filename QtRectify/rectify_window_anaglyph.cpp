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

#include <omp.h>

//
// notes:
// output images must be allocate in advance
//
static
bool createStereoAnaglyph( int iAnaglyphMode, // [i] one of PixImagingDAnaglyphMode
   const pixq_ImageMatrix &inLeftRed, // [i] input left red image
   const pixq_ImageMatrix &inLeftGrn, // [i] input left green image
   const pixq_ImageMatrix &inLeftBlu, // [i] input left blue image
   const pixq_ImageMatrix &inRightRed, // [i] input right red image
   const pixq_ImageMatrix &inRightGrn, // [i] input right green image
   const pixq_ImageMatrix &inRightBlu, // [i] input right blue image
   pixq_ImageMatrix &outAnglyphRed,    // [o] output red image
   pixq_ImageMatrix &outAnglyphGrn,    // [o] output green image
   pixq_ImageMatrix &outAnglyphBlu)    // [o] output blue image
{
   bool bRetCode = false;
   int iPixSum[2], iWhitePixSum;
   long i, j, k, l, m, nOutWidth, nOutHeight, nWidth[2], nHeight[2];
   double dDubois[3][6], dPixel[6], dColors[3];
   unsigned short usInRed[2], usInGrn[2], usInBlu[2], usOutVal[3];

   const pixq_ImageMatrix *inImages[2][3];
   pixq_ImageMatrix *outImages[3];

   int nMaxThreads;

   inImages[0][0] = &inLeftRed;
   inImages[0][1] = &inLeftGrn;
   inImages[0][2] = &inLeftBlu;
   inImages[1][0] = &inRightRed;
   inImages[1][1] = &inRightGrn;
   inImages[1][2] = &inRightBlu;
   outImages[0] = &outAnglyphRed;
   outImages[1] = &outAnglyphGrn;
   outImages[2] = &outAnglyphBlu;

   // --- load depth data into matrix ---
    
   for (k = 0; k < 2; k++) {
      nWidth[k] = inImages[k][0]->getWidth();
      nHeight[k] = inImages[k][0]->getHeight();
   }

   nOutWidth = outImages[0]->getWidth();
   nOutHeight = outImages[0]->getHeight();

   // --- 変換行列 ---

   switch (iAnaglyphMode) {

   case pixq_Properties::Print3DAnaglyphBlueRed:
      dDubois[0][0] = 0.299;
      dDubois[0][1] = 0.587;
      dDubois[0][2] = 0.114;
      dDubois[0][3] = 0.0;
      dDubois[0][4] = 0.0;
      dDubois[0][5] = 0.0;

      dDubois[1][0] = 0.0;
      dDubois[1][1] = 0.0;
      dDubois[1][2] = 0.0;
      dDubois[1][3] = 0.0;
      dDubois[1][4] = 0.0;
      dDubois[1][5] = 0.0;

      dDubois[2][0] = 0.0;
      dDubois[2][1] = 0.0;
      dDubois[2][2] = 0.0;
      dDubois[2][3] = 0.299;
      dDubois[2][4] = 0.587;
      dDubois[2][5] = 0.114;
      break;

   case pixq_Properties::Print3DAnaglyphGray:
      dDubois[0][0] = 0.299;
      dDubois[0][1] = 0.587;
      dDubois[0][2] = 0.114;
      dDubois[0][3] = 0.0;
      dDubois[0][4] = 0.0;
      dDubois[0][5] = 0.0;

      dDubois[1][0] = 0.0;
      dDubois[1][1] = 0.0;
      dDubois[1][2] = 0.0;
      dDubois[1][3] = 0.299;
      dDubois[1][4] = 0.587;
      dDubois[1][5] = 0.114;

      dDubois[2][0] = 0.0;
      dDubois[2][1] = 0.0;
      dDubois[2][2] = 0.0;
      dDubois[2][3] = 0.299;
      dDubois[2][4] = 0.587;
      dDubois[2][5] = 0.114;
      break;

   case pixq_Properties::Print3DAnaglyphColor:
      dDubois[0][0] = 1.0;
      dDubois[0][1] = 0.0;
      dDubois[0][2] = 0.0;
      dDubois[0][3] = 0.0;
      dDubois[0][4] = 0.0;
      dDubois[0][5] = 0.0;

      dDubois[1][0] = 0.0;
      dDubois[1][1] = 0.0;
      dDubois[1][2] = 0.0;
      dDubois[1][3] = 0.0;
      dDubois[1][4] = 1.0;
      dDubois[1][5] = 0.0;

      dDubois[2][0] = 0.0;
      dDubois[2][1] = 0.0;
      dDubois[2][2] = 0.0;
      dDubois[2][3] = 0.0;
      dDubois[2][4] = 0.0;
      dDubois[2][5] = 1.0;
      break;

   case pixq_Properties::Print3DAnaglyphHalfColor:
      dDubois[0][0] = 0.299;
      dDubois[0][1] = 0.587;
      dDubois[0][2] = 0.114;
      dDubois[0][3] = 0.0;
      dDubois[0][4] = 0.0;
      dDubois[0][5] = 0.0;

      dDubois[1][0] = 0.0;
      dDubois[1][1] = 0.0;
      dDubois[1][2] = 0.0;
      dDubois[1][3] = 0.0;
      dDubois[1][4] = 1.0;
      dDubois[1][5] = 0.0;

      dDubois[2][0] = 0.0;
      dDubois[2][1] = 0.0;
      dDubois[2][2] = 0.0;
      dDubois[2][3] = 0.0;
      dDubois[2][4] = 0.0;
      dDubois[2][5] = 1.0;
      break;

   case pixq_Properties::Print3DAnaglyphWoods:
      dDubois[0][0] = 0.0;
      dDubois[0][1] = 0.7;
      dDubois[0][2] = 0.3;
      dDubois[0][3] = 0.0;
      dDubois[0][4] = 0.0;
      dDubois[0][5] = 0.0;

      dDubois[1][0] = 0.0;
      dDubois[1][1] = 0.0;
      dDubois[1][2] = 0.0;
      dDubois[1][3] = 0.0;
      dDubois[1][4] = 1.0;
      dDubois[1][5] = 0.0;

      dDubois[2][0] = 0.0;
      dDubois[2][1] = 0.0;
      dDubois[2][2] = 0.0;
      dDubois[2][3] = 0.0;
      dDubois[2][4] = 0.0;
      dDubois[2][5] = 1.0;
      break;

   case pixq_Properties::Print3DAnaglyphDubois:
      dDubois[0][0] = 0.4561;
      dDubois[0][1] = 0.500484;
      dDubois[0][2] = 0.176381;
      dDubois[0][3] = -0.0434706;
      dDubois[0][4] = -0.0879388;
      dDubois[0][5] = -0.00155529;

      dDubois[1][0] = -0.0400822;
      dDubois[1][1] = -0.0378246;
      dDubois[1][2] = -0.0157589;
      dDubois[1][3] = 0.378476;
      dDubois[1][4] = 0.73364;
      dDubois[1][5] = -0.0184503;

      dDubois[2][0] = -0.0152161;
      dDubois[2][1] = -0.0205971;
      dDubois[2][2] = -0.00546856;
      dDubois[2][3] = -0.0721527;
      dDubois[2][4] = -0.112961;
      dDubois[2][5] = 1.2264;
      break;
   }

   // --- image conversion ---

   nMaxThreads = omp_get_max_threads();
   omp_set_num_threads(nMaxThreads);

   switch (iAnaglyphMode) {

   case pixq_Properties::Print3DAnaglyphGray:
   case pixq_Properties::Print3DAnaglyphColor:
   case pixq_Properties::Print3DAnaglyphHalfColor:
   case pixq_Properties::Print3DAnaglyphWoods:
#pragma omp parallel
      {
#pragma omp for private(i,j,k,l,m,usInRed,usInGrn,usInBlu,dPixel,dColors,usOutVal)   
         for (i = 0; i < nOutHeight; i++) {
            for (j = 0; j < nOutWidth; j++) {

               for (k = 0; k < 2; k++) {
                  usInRed[k] = inImages[k][0]->Get(i, j);
                  usInGrn[k] = inImages[k][1]->Get(i, j);
                  usInBlu[k] = inImages[k][2]->Get(i, j);
               }

               dPixel[0] = (double)usInRed[LEFT];
               dPixel[1] = (double)usInGrn[LEFT];
               dPixel[2] = (double)usInBlu[LEFT];
               dPixel[3] = (double)usInRed[RIGHT];
               dPixel[4] = (double)usInGrn[RIGHT];
               dPixel[5] = (double)usInBlu[RIGHT];

               for (l = 0; l < 3; l++) {
                  dColors[l] = 0.0;
                  for (m = 0; m < 6; m++) {
                     dColors[l] = dColors[l] + dDubois[l][m] * dPixel[m];
                  }
               }

               usOutVal[0] = (unsigned short)dColors[0];
               usOutVal[1] = (unsigned short)dColors[1];
               usOutVal[2] = (unsigned short)dColors[2];

               outImages[0]->Set(i, j, usOutVal[0]);
               outImages[1]->Set(i, j, usOutVal[1]);
               outImages[2]->Set(i, j, usOutVal[2]);
            } // j
         } // i
      }
      break;

   case pixq_Properties::Print3DAnaglyphBlueRed:
   case pixq_Properties::Print3DAnaglyphDubois:
      //iWhitePixSum = 255 * 3;
      iWhitePixSum = (256 * 256 - 1) * 3;
#pragma omp parallel
      {
#pragma omp for private(i,j,k,l,m,usInRed,usInGrn,usInBlu,iPixSum,dPixel,usOutVal) 
         for (i = 0; i < nOutHeight; i++) {
            for (j = 0; j < nOutWidth; j++) {

               for (k = 0; k < 2; k++) {
                  usInRed[k] = inImages[k][0]->Get(i, j);
                  usInGrn[k] = inImages[k][1]->Get(i, j);
                  usInBlu[k] = inImages[k][2]->Get(i, j);
               }

               for (k = 0; k < 2; k++) {
                  iPixSum[k] = (int)usInRed[k] + (int)usInGrn[k] + (int)usInBlu[k];
               }

               if (iPixSum[LEFT] >= iWhitePixSum || iPixSum[RIGHT] >= iWhitePixSum) {
                  usOutVal[0] = 65535;
                  usOutVal[1] = 65535;
                  usOutVal[2] = 65535;
               }
               else {
                  dPixel[0] = (double)usInRed[0];
                  dPixel[1] = (double)usInGrn[0];
                  dPixel[2] = (double)usInBlu[0];
                  dPixel[3] = (double)usInRed[1];
                  dPixel[4] = (double)usInGrn[1];
                  dPixel[5] = (double)usInBlu[1];

                  for (l = 0; l < 3; l++) {
                     dColors[l] = 0.0;
                     for (m = 0; m < 6; m++) {
                        dColors[l] = dColors[l] + dDubois[l][m] * dPixel[m];
                     }
                  }

                  usOutVal[0] = (unsigned short)dColors[0];
                  usOutVal[1] = (unsigned short)dColors[1];
                  usOutVal[2] = (unsigned short)dColors[2];
               }

               outImages[0]->Set(i, j, usOutVal[0]);
               outImages[1]->Set(i, j, usOutVal[1]);
               outImages[2]->Set(i, j, usOutVal[2]);
            } // j
         } // i
      }
      break;
   }
   
   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}


bool rectify_window::saveAnaglyphImage(void)
{
   bool bRetCode = false;
   int k, nHeight, nWidth, nImgXSize[2], iAnaglyphMode,  nImgYSize[2];
   pixq_Properties *pEnv = getRectifyEnv();
   pixq_ImageDualSet *pData = getImageData();

   QFileInfo finfo;
   QString strLabel, strDefFile, strFilters, strSelectedFilter, strEntry;
   QString strInPath, strExt, strBase, strMessage, strSuffix, strInFile[2], strOutFile;

   QString strApplication = _version.getApplication();
   QString strOrganisation = _version.GetCompany();

   // derived anaglyph image matrix 
   pixq_ImageMatrix AnaglyphImageMtx[3];

#ifdef _READY
   //
   // 2013.5.16
   // don't use QFileDialog
   // it is too slow
   // 
   QFileDialog dlg(this);
#endif // _READY

   QFileDialog::Options options;

   if (!validPaneDisplayMode()) {
      goto PIX_EXIT;
   }

   if (!_bDrvRectified) {
      goto PIX_EXIT;
   }

   //
   // set default file names
   //

   if (!pData->getCurrentFiles(&strInFile[0], &strInFile[1])) {
      goto PIX_EXIT;
   }

   strSuffix = pEnv->_StereoAnaglyphFileSuffix.getString();

   finfo.setFile(strInFile[0]);
   strInPath = finfo.absolutePath();
   strBase = finfo.completeBaseName();
   strEntry = strBase + strSuffix;
   strExt = finfo.suffix();
   strDefFile = strInPath + "/" + strEntry + "." + strExt;

   //
   // select output anaglyph image
   //

   imageMagickFileFilter_PI(false, strFilters);
   options = 0;
   strLabel = getRectifyLabel("Operation", "Anaglyph");

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

   QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));

   //
   // create anaglyph image
   //

   for (k = 0; k < 2; k++) {
      nImgXSize[k] = _ImageDrvMtx[k][0].getWidth();
      nImgYSize[k] = _ImageDrvMtx[k][0].getHeight();
   }

   nWidth = max(nImgXSize[0], nImgXSize[1]);
   nHeight = max(nImgYSize[0], nImgYSize[1]);

   for (k = 0; k < 3; k++) {
      if (!AnaglyphImageMtx[k].Alloc(nHeight, nWidth)) {
         goto PIX_EXIT;
      }
   }

   iAnaglyphMode = pEnv->_StereoAnaglyphMethod.getInteger();

   if (!createStereoAnaglyph(iAnaglyphMode,
      _ImageDrvMtx[0][0], _ImageDrvMtx[0][1], _ImageDrvMtx[0][2],
      _ImageDrvMtx[1][0], _ImageDrvMtx[1][1], _ImageDrvMtx[1][2],
      AnaglyphImageMtx[0], AnaglyphImageMtx[1], AnaglyphImageMtx[2])) {
      goto PIX_EXIT;
   }

   //
   // save anaglyph image
   //

   if (!magickSaveImage_PI(strOutFile, 
      &AnaglyphImageMtx[0],
      &AnaglyphImageMtx[1], 
      &AnaglyphImageMtx[2])) {
         strMessage = QString("Failed to Save Image: ") + strOutFile;
         QMessageBox::warning(this, strApplication, strMessage);
         goto PIX_EXIT;
   }

   qDebug() << "Rectified Image saved as " << strOutFile;
   
   // --- Done --- 
   bRetCode = true;
PIX_EXIT:
   for (k = 0; k < 3; k++) {
      AnaglyphImageMtx[k].free();
   }
   QApplication::restoreOverrideCursor();
   return bRetCode;
}


