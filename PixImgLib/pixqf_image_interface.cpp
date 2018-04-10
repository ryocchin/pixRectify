#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

//
// custom widgets
//

#include "sequence_select_dialog.h"

//
// select single sequence of images
//
bool selectSingleSequence_PI(const QString strOrganisation,
                               const QString strApplication, 
                               pixq_Properties *pEnv,
                               pixq_ImgSequence *pSeq )
{
   bool bRetCode = false;
   sequence_select_dialog dlg;

   dlg.Init( strOrganisation, strApplication, pEnv, pSeq );

   if( QDialog::Accepted != dlg.exec( ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool selectSingleSequence_PI(const QString strOrganisation,
                              const QString strApplication, 
                              pixq_Properties *pEnv,
                              pixq_ImageSingleSet *pData )
{
   bool bRetCode = false;
   sequence_select_dialog dlg;
   short sMode = (short)pixq_ImageSingleSet::PixSingleSetSequence;

   pixq_ImgSequence *pSeq = pData->GetSequence(  );

   dlg.Init( strOrganisation, strApplication, pEnv, pSeq );

   if( QDialog::Accepted != dlg.exec( ) ) {
      goto PIX_EXIT;
   }

   pData->SetSelectMode( sMode );
   pData->SelectFirstFrame( );

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool selectDualSequences_PI(const QString strOrganisation,
                               const QString strApplication, 
                               pixq_Properties *pEnv,
                               pixq_ImgSequence *pSeq0,
                               pixq_ImgSequence *pSeq1 )
{
   bool bRetCode = false;
   sequence_select_dialog dlg;

   dlg.Init( strOrganisation, strApplication, pEnv, pSeq0, pSeq1 );

   if( QDialog::Accepted != dlg.exec( ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
