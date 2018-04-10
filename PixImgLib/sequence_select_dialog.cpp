#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "sequence_select_dialog.h"
#include "ui_sequence_select_dialog.h"

// combo box for file selection

#define REGKEY_RECENT0_IMAGE "Recent 0 Image - %03d"
#define REGKEY_RECENT1_IMAGE "Recent 1 Image - %03d"

#define REGKEY_RECENT_DISPARITY "Recent Disparity - %03d"

QString sequence_select_dialog::SetKeyString( int iSide, // [i] 0 or 1
                                                int iNumber ) // [i] number
{
   QString strKey;
   strKey.clear( );

   if( 0 == iSide ) {
      strKey.sprintf( REGKEY_RECENT0_IMAGE, iNumber );
   } else {
      strKey.sprintf( REGKEY_RECENT1_IMAGE, iNumber );
   }

   return strKey;
}

QString sequence_select_dialog::GetLastDirectory( int iSide ) // [i] 0 or 1
{
   QString strLastDir;
   pixq_Properties *pEnv = getEnv();

   strLastDir.clear( );

   if( 0 == iSide ) {
      strLastDir = pEnv->_CommonLastImage0Dir.getString();
   } else {
      strLastDir = pEnv->_CommonLastImage1Dir.getString();
   }

   return strLastDir;
}

void sequence_select_dialog::StoreLastDirectory( int iSide, // [i] side, 0 or 1
                                                QString strFile ) // [i] file name to extract path name
{   
   pixq_Properties *pEnv = getEnv();
   QFileInfo finfo;
   QString strPath;

   // *** extract the path name from file name and memorize it ***
   
   finfo.setFile( strFile );
   strPath = finfo.path( );
   
      if( 0 == iSide ) {
         pEnv->_CommonLastImage0Dir.Set( strPath );
      } else {
         pEnv->_CommonLastImage1Dir.Set( strPath );
      }
   
   // store the changed env

      pEnv->setRegEnv(_strOrganisation, _strApplication);

   return;
}


QString sequence_select_dialog::GetLastFile( int iSide ) // [i] 0 or 1
{
   pixq_Properties *pEnv = getEnv();
   QString strLastFile;

   strLastFile.clear( );

      if( 0 == iSide ) {
         strLastFile = pEnv->_CommonLastImage0File.getString();
      } else {
         strLastFile = pEnv->_CommonLastImage1File.getString();
      }

   return strLastFile;
}

//
// store the image as the LAST image
//
void sequence_select_dialog::StoreLastFile( int iSide, // [i] side, 0 or 1
                                            QString strFile ) // [i] file name to extract path name
{   
   pixq_Properties *pEnv = getEnv();

   // *** extract the path name from file name and memorize it ***
    
      if( 0 == iSide ) {
         pEnv->_CommonLastImage0File.Set( strFile );
      } else {
         pEnv->_CommonLastImage1File.Set( strFile );
      }
   
      pEnv->setRegEnv(_strOrganisation, _strApplication);

   return;
}

sequence_select_dialog::sequence_select_dialog( QWidget *parent ) : 
   QDialog( parent ),
    ui(new Ui::sequence_select_dialog)
{ 
    ui->setupUi(this);

   // init conditions

   _pDepthEnv = (pixq_Properties*)NULL;

   _strOrganisation.clear( );
   _strApplication.clear( ); 

   return;
}
   
sequence_select_dialog::~sequence_select_dialog(void)
{
    delete ui;
}

void sequence_select_dialog::Init( const QString strOrganisation, 
                                  const QString strApplication, 
                                  pixq_Properties *pEnv, 
                                  pixq_ImgSequence *pSeq )
{ 
   Init( strOrganisation, strApplication, pEnv, pSeq, pSeq, false );

   return;
}


void sequence_select_dialog::Init( const QString strOrganisation, 
                                  const QString strApplication, 
                                  pixq_Properties *pEnv, 
                                  pixq_ImgSequence *pSeq0, 
                                  pixq_ImgSequence *pSeq1 )
{ 
   Init( strOrganisation, strApplication, pEnv, pSeq0, pSeq1, true );

   return;
}

void sequence_select_dialog::Init( const QString strOrganisation, 
                                  const QString strApplication, 
                                  pixq_Properties *pEnv, 
                                  pixq_ImgSequence *pSeq0, 
                                  pixq_ImgSequence *pSeq1,
                                  bool bDouble )
{ 
   QString strLastFile, strEmpty;

   _strOrganisation = strOrganisation;
   _strApplication = strApplication; 
   _pDepthEnv = pEnv; 
   m_pImgSequence[0] = pSeq0; 
   m_pImgSequence[1] = pSeq1; 

   // first sequence

   ui->m_File0Combo->setEditable( true );
   ui->m_File0Combo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

   ui->m_Brows0Button->setDefault( false );

   ui->m_Template0Edit->setReadOnly( true );
   ui->m_Template0Label->setBuddy( ui->m_Template0Edit );

   ui->m_Pattern0Edit->setReadOnly( true );
   ui->m_Pattern0Label->setBuddy( ui->m_Pattern0Edit );

   ui->m_Frames0Edit->setReadOnly( true );
   ui->m_Frames0Label->setBuddy( ui->m_Frames0Edit );

   // second sequence

   ui->m_File1Combo->setEditable( true );
   ui->m_File1Combo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

   ui->m_Brows1Button->setDefault( false );

   ui->m_Template1Edit->setReadOnly( true );
   ui->m_Template1Label->setBuddy( ui->m_Template1Edit );

   ui->m_Pattern1Edit->setReadOnly( true );
   ui->m_Pattern1Label->setBuddy( ui->m_Pattern1Edit );

   ui->m_Frames1Edit->setReadOnly( true );
   ui->m_Frames1Label->setBuddy( ui->m_Frames1Edit );

   // enable/dsiable second images according to the mode

   ui->m_Group0Box->setEnabled( true );
   ui->m_File0Label->setEnabled( true );
   ui->m_File0Combo->setEnabled( true );
   ui->m_Brows0Button->setEnabled( true );
   ui->m_Template0Label->setEnabled( true );
   ui->m_Template0Edit->setEnabled( true );
   ui->m_Pattern0Label->setEnabled( true );
   ui->m_Pattern0Edit->setEnabled( true );
   ui->m_Frames0Label->setEnabled( true );
   ui->m_Frames0Edit->setEnabled( true );

   ui->m_Group1Box->setEnabled( bDouble );
   ui->m_File1Label->setEnabled( bDouble );
   ui->m_File1Combo->setEnabled( bDouble );
   ui->m_Brows1Button->setEnabled( bDouble );
   ui->m_Template1Label->setEnabled( bDouble );
   ui->m_Template1Edit->setEnabled( bDouble );
   ui->m_Pattern1Label->setEnabled( bDouble );
   ui->m_Pattern1Edit->setEnabled( bDouble );
   ui->m_Frames1Label->setEnabled( bDouble );
   ui->m_Frames1Edit->setEnabled( bDouble );

   // bottom lines

   ui->m_OkButton->setEnabled( true );
   ui->m_CancelButton->setEnabled( true );
   ui->m_ClearHistoryButton->setEnabled( true );

   ui->m_OkButton->setDefault( false );
   ui->m_CancelButton->setDefault( false );
   ui->m_ClearHistoryButton->setDefault( false );
   
   // dummy button
   ui->m_DummyButton->setEnabled( true );
   ui->m_DummyButton->setDefault( true );
   ui->m_DummyButton->setVisible( false );

   // *** decorate window ***

   setWindowTitle( tr("Select Seuqence") );

   // *** set last selected file ***

   SetRecentFileList( 0 );
   SetRecentFileList( 1 );

   // clear 

   strEmpty.clear( );
   
   ui->m_Template0Edit->setText( strEmpty );
   ui->m_Pattern0Edit->setText( strEmpty );
   ui->m_Frames0Edit->setText( strEmpty );

   ui->m_Template1Edit->setText( strEmpty );
   ui->m_Pattern1Edit->setText( strEmpty );
   ui->m_Frames1Edit->setText( strEmpty );

   // *** set button action ***
   // set button actions after all initial setting is done!
   // to avoid unnecessary actions

   connect( ui->m_Brows0Button, SIGNAL( clicked( ) ), this, SLOT( ClickSelect0Image( ) ) ); 
   connect( ui->m_Brows1Button, SIGNAL( clicked( ) ), this, SLOT( ClickSelect1Image( ) ) );  

   connect( ui->m_OkButton, SIGNAL( clicked( ) ), this, SLOT( ClickOkButton( ) ) );
   connect( ui->m_CancelButton, SIGNAL( clicked( ) ), this, SLOT( ClickCancelButton( ) ) );
   connect( ui->m_ClearHistoryButton, SIGNAL( clicked( ) ), this, SLOT( ClickClearHistoryButton( ) ) );
   
   connect( ui->m_File0Combo, SIGNAL( activated( int ) ), this, SLOT( Combo0FileActivated( int ) ) ); 
   connect( ui->m_File1Combo, SIGNAL( activated( int ) ), this, SLOT( Combo1FileActivated( int ) ) );

   ui->m_File0Combo->installEventFilter( this );
   ui->m_File1Combo->installEventFilter( this );

   // set focus on the first combo

   ui->m_File0Combo->setFocus( );

   return;
}
   
bool sequence_select_dialog::eventFilter( QObject *obj, QEvent *eve )
{
   bool bConsumed = false;

   // get the return key pressed on file combo
   
   if ( ui->m_File0Combo == obj ) {
      if( eve->type() == QEvent::KeyPress ) {
         QKeyEvent *keyEvent = static_cast<QKeyEvent*>(eve);
         int iKey = keyEvent->key();
         
         switch( iKey ) {
         case Qt::Key_Enter:
         case Qt::Key_Return:
            ComboReturnPressed( 0 );
            bConsumed = true;
            break;

         case Qt::Key_Escape:
         case Qt::Key_Up:
         case Qt::Key_Down:
         case Qt::Key_Home:
         case Qt::Key_End:
         case Qt::Key_PageUp:
         case Qt::Key_PageDown:
            break;
        }
      }

   } else if( ui->m_File1Combo == obj ) {
      if( eve->type() == QEvent::KeyPress ) {
         QKeyEvent *keyEvent = static_cast<QKeyEvent*>(eve);
         int iKey = keyEvent->key();
         
         switch( iKey ) {
         case Qt::Key_Enter:
         case Qt::Key_Return:
            ComboReturnPressed( 1 );
            bConsumed = true;
            break;
        }
      }
   }

   if( bConsumed ) {
      return true;
   } 

   // pass the event on to the parent class
   return QDialog::eventFilter( obj, eve );   
}

void sequence_select_dialog::ComboFileActivated( int iSide, int iIndex )
{
   QString strFile;
   
   if( 0 == iSide ) {
      strFile = ui->m_File0Combo->itemText( iIndex );
   } else {
      strFile = ui->m_File1Combo->itemText( iIndex );
   }

   // --- check the selected file ---

   if( !ImageSelected( iSide, strFile, false ) ) { // ComboFileActivated
      goto PIX_EXIT;
   }

   if( !CheckSequence( iSide ) ) {
      goto PIX_EXIT;
   }

   if( 0 == iSide ) {
    //  ui->m_File0Combo->setEditText( strFile );
      ui->m_File0Combo->clearEditText( );
      ui->m_File0Combo->setCurrentIndex( iIndex );
   } else {
   //   ui->m_File1Combo->setEditText( strFile );
      ui->m_File1Combo->clearEditText( );
      ui->m_File1Combo->setCurrentIndex( iIndex );
   }

PIX_EXIT:
   return;
}

void sequence_select_dialog::ClickOkButton( void )
{
   accept( );

   return;
}
   
//
// Cancel button pressed
//
void sequence_select_dialog::ClickCancelButton( void )
{
   reject( );

   return;
}
 
void sequence_select_dialog::ClickClearHistoryButton( void )
{
   RemoveAllFromRecentDirList( 0 );
   RemoveAllFromRecentDirList( 1 );

   return;
}

void sequence_select_dialog::RemoveAllFromRecentDirList( int iSide ) 
{
   bool bFound;
   QString strKey;
   int i;
   QComboBox *pCombo = NULL;
   QSettings settings( _strOrganisation, _strApplication );
   
   if( 0 == iSide ) {
      pCombo = ui->m_File0Combo;
   } else {
      pCombo = ui->m_File1Combo;
   }

   // get a list of recently selected shot directories in 

   bFound = true;
   i = 0;
   while( bFound ) {

      strKey = SetKeyString( iSide, i );

      if( settings.contains( strKey ) ) {
         settings.remove( strKey );
      } else {
         bFound = false;
      }
      i++;
   }

   // clear the combo box

   pCombo->clear( );

   // --- Done ---
//PIX_EXIT:
   return;
}

void sequence_select_dialog::ClickSelect0Image( void )
{
   SelectImage( 0 );

   return;
}

void sequence_select_dialog::ClickSelect1Image( void )
{
   SelectImage( 1 );
}

//
// select single image from file dialog and set it on the dialog
//
void sequence_select_dialog::SelectImage( int iSide )
{
   QString strFile;

   // select a file in the sequence

   if( !SelectSingleImage( iSide, &strFile ) ) {      
      goto PIX_EXIT;
   }
   
   // --- check the selected file ---

   if( !ImageSelected( iSide, strFile, true ) ) { // SelectImage
      goto PIX_EXIT;
   }

   if( !CheckSequence( iSide ) ) {
      goto PIX_EXIT;
   }

   // --- done ---
PIX_EXIT:
   return;
}

//
// Enter pressed on edit box
//
void sequence_select_dialog::ComboReturnPressed( int iSide )
{
   QString strFile;
   
#ifdef _DEBUG
   fprintf( stdout, "sequence_select_dialog::ComboReturnPressed Entered with %d.\n", iSide );
#endif

   if( 0 == iSide ) {
      strFile = ui->m_File0Combo->currentText( );
   } else {
      strFile = ui->m_File1Combo->currentText( );
   }

#ifdef _DEBUG
   qDebug( ) << "Selected File = " << strFile << endl;
#endif

   // --- check the selected file ---

   if( !ImageSelected( iSide, strFile, true ) ) { // ComboReturnPressed
#ifdef _DEBUG
   qDebug( ) << "ERROR! ImageSelected Failed." << endl;
#endif
      goto PIX_EXIT;
   }

   if( !CheckSequence( iSide ) ) {
      goto PIX_EXIT;
   }

   // set focus on the first combo

   if( 0 == iSide ) {
      ui->m_File1Combo->setFocus( );
   } else {
      ui->m_File0Combo->setFocus( );
   }

PIX_EXIT:
   return;
}

//
// select single image in the sequence
// from file dialog
//
bool sequence_select_dialog::SelectSingleImage( int iSide, // [i] side, 0 or 1
                                             QString *strFile ) // [o] file selected 
{
   bool bRetCode = false;
   //pixq_Properties *pEnv = getEnv( );
   //QFileDialog dialog( this );

   QSettings settings( _strOrganisation, _strApplication );
   QString strLastDir, strLabel;
   //QStringList fileNames;
   
   QFileDialog::Options options;

   //QString strEmpty,strLastDir;
   //QString strPath, strFilter;
   //QString strFileName;
   //QString szFilter;

   //QStringList fileFilters;
   QString fileFilters, strSelectedFilter;

   // get last file path

   strLastDir = GetLastDirectory( iSide );
   if( strLastDir.isEmpty( ) ) {
      strLastDir = QDir::currentPath( );
   }

   // set filter and label

   strLabel = tr("Select Image");
   imageMagickFileFilter_PI(true, fileFilters);
   
 //  dialog.setNameFilters( fileFilters );
//   dialog.setLabelText( QFileDialog::LookIn, strLabel );  
 //  dialog.setDirectory( strLastDir );
  
 //  dialog.setAcceptMode( QFileDialog::AcceptOpen );
 //  dialog.setFileMode( QFileDialog::ExistingFile );

 //  if( QDialog::Accepted != dialog.exec( ) ) {
//      goto PIX_EXIT;
//   }

 //  fileNames = dialog.selectedFiles( );
//   nSize = fileNames.size( );
//   if( 1 > nSize ) {
//      goto PIX_EXIT;
 //  }

//   *strFile = fileNames.at( 0 );
   
   options = QFileDialog::ReadOnly;
   *strFile = QFileDialog::getOpenFileName( this, 
      strLabel,
      strLastDir,
      fileFilters );

   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

void sequence_select_dialog::SetRecentFileList( int iSide )
{
   // TODO: Add your control notification handler code here

   //pixq_Properties *pEnv = getEnv( );
   bool bFound;
   QStringList strListRecent;
   QString strLastFile, strEmpty, strRecent, strKey;   
   int iCurrent, i, nRecent;
   QComboBox *pCombo = NULL;
   QSettings settings( _strOrganisation, _strApplication );

   if( 0 == iSide ) {
      pCombo = ui->m_File0Combo;
   } else {
      pCombo = ui->m_File1Combo;
   }

   // get a list of recently selected shot directories

   strListRecent.clear( );
   bFound = true;
   i = 0;
   while( bFound ) {
      
      strKey = SetKeyString( iSide, i );
      //
      if( settings.contains( strKey ) ) {
         // value exists!
         strRecent = settings.value( strKey, strEmpty ).toString( );
         strListRecent.push_back( strRecent );
      } else {
         bFound = false;
      }
      i++;
   }

   nRecent = (int)strListRecent.size( );
   strListRecent.removeDuplicates( );
   strListRecent.sort( );

   // set the list to combo box
   
   pCombo->clear( );
   //pCombo->addItems( &strListRecent );
   nRecent = (int)strListRecent.size( );
   for( i = 0 ; i < nRecent ; i++ ) {
      strRecent = strListRecent.at( i );
      pCombo->addItem( strRecent );
   }

   pCombo->setEditable( true );
   pCombo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

   // *** get the last selected file and set on the combo ***

   strLastFile = GetLastFile( iSide );
   if( !strLastFile.isEmpty( ) ) {
      // select it from combo
      iCurrent = -1;
      for( i = 0 ; i < nRecent ; i++ ) {
         strRecent = strListRecent.at( i );
         if( 0 == strLastFile.compare( strRecent ) ) {
            iCurrent = i;
         }
      }
      if( 0 <= iCurrent ) {
         pCombo->setCurrentIndex( iCurrent );
      }
   }

   return;
}

//
// add a file name pattern to the bottom of the list of recent patterns
// it is recorded in the registery
//
void sequence_select_dialog::AddToRecentDirList( int iSide, 
                                                QString strFile, // [i] pattern
                                                bool bSelectAdded ) // [i] to avoid index is reselected 
{
   bool bFound;
   QStringList strListRecent;
   QString strEmpty, strRecent, strKey, strSource;   
   int iCurrent, i, nRecent;
   QComboBox *pCombo = NULL;
   QSettings settings( _strOrganisation, _strApplication );
   
   if( 0 == iSide ) {
      pCombo = ui->m_File0Combo;
   } else {
      pCombo = ui->m_File1Combo;
   }

   // get a list of recently selected shot directories in 

   strEmpty.clear( );
   
   strListRecent.clear( );
   bFound = true;
   i = 0;
   while( bFound ) {

      strKey = SetKeyString( iSide, i );

      //
      if( settings.contains( strKey ) ) {
         // value exists!
         strRecent = settings.value( strKey, strEmpty ).toString( );
         strListRecent.push_back( strRecent );
      } else {
         bFound = false;
      }
      i++;
   }

   // push back this file

   strListRecent.push_back( strFile );

   // clearn up settings

   nRecent = (int)strListRecent.size( );
   for( i = 0 ; i < nRecent ; i++ ) {
      strKey = SetKeyString( iSide, i );
      if( !settings.contains( strKey ) ) continue;
      settings.remove( strKey );
   }

   // reove duplicate, if any

   strListRecent.removeDuplicates( );
   strListRecent.sort( );

   // remember the data in registry again

   nRecent = (int)strListRecent.size( );
   for( i = 0 ; i < nRecent ; i++ ) {
      strSource = strListRecent.at( i );

      // store to the setting
      
      strKey = SetKeyString( iSide, i );
      settings.setValue( strKey, strSource );
   }

   // set the data to the combo box

   pCombo->clear( );
   pCombo->addItems( strListRecent );

   if( bSelectAdded ) {
      iCurrent = -1;
      for( i = 0 ; 0 > iCurrent && i < nRecent ; i++ ) {
         strSource = strListRecent.at( i );
         if( 0 == strSource.compare( strFile ) ) {
            iCurrent = i;
         }
      }
      pCombo->setCurrentIndex( iCurrent );
   }

   // --- Done ---
//PIX_EXIT:
   return;
}

void sequence_select_dialog::RemoveFromRecentDirList( int iSide, 
                                                QString strFile ) // [i] pattern
{
   bool bFound;
   QStringList strListRecent;
   QString strEmpty, strRecent, strKey, strSource;
   int iRemovePos, i, nRecent;
   QComboBox *pCombo = NULL;
   QSettings settings( _strOrganisation, _strApplication );
   
   if( 0 == iSide ) {
      pCombo = ui->m_File0Combo;
   } else {
      pCombo = ui->m_File1Combo;
   }

   // get a list of recently selected shot directories in 

   strEmpty.clear( );   
   strListRecent.clear( );
   bFound = true;
   iRemovePos = -1;
   i = 0;
   while( bFound ) {
      strKey = SetKeyString( iSide, i );
      //
      if( settings.contains( strKey ) ) {
         // value exists!
         strRecent = settings.value( strKey, strEmpty ).toString( );
         strListRecent.push_back( strRecent );
         //
         if( 0 == strRecent.compare( strFile ) ) {
            iRemovePos = i;
         }
      } else {
         bFound = false;
      }
      i++;
   }

   if( 0 > iRemovePos ) {
      // the is not in the list!
      goto PIX_EXIT;
   }

   // clearn up settings

   nRecent = (int)strListRecent.size( );
   for( i = 0 ; i < nRecent ; i++ ) {      
      strKey = SetKeyString( iSide, i );

      if( !settings.contains( strKey ) ) continue;
      settings.remove( strKey );
   }

   // remove this file

   strListRecent.removeAt( iRemovePos );

   // remove this file

   strListRecent.removeDuplicates( );
   strListRecent.sort( );

   // remember the data in registry again

   nRecent = (int)strListRecent.size( );
   for( i = 0 ; i < nRecent ; i++ ) {
      strSource = strListRecent.at( i );

      // store to the setting
      
      strKey = SetKeyString( iSide, i );
      settings.setValue( strKey, strSource );
   }

   // set the data to the combo box

   pCombo->clear( );
   pCombo->addItems( strListRecent );

   // --- Done ---
PIX_EXIT:
   return;
}

//
// one image file, which belongs to the sequence is selected
// analyze the file, set the image name pattern
//
// notes:
// bSelectAdded:
// if this is true, given image is also selected on the combo box
//
bool sequence_select_dialog::ImageSelected( int iSide, 
                                      QString strFile, // [i] image file name
                                      bool bSelectAdded )
{   
   bool bRetCode = false;
   int nFrames, iFrame, nLen, iFirstFrame, iLastFrame, iFrameDigit;  
   short sPattern;
   QFile file;
   QString szPatternType, strExt;
   QString strError, strFrames, strPattern;

   QLineEdit *pTemplateEdit;
   QLineEdit *pPatternEdit;
   QLineEdit *pFramesEdit;

   pixq_ImgSequence *pSeq = GetImgSequence( iSide );

   if( 0 == iSide ) {
      pTemplateEdit = ui->m_Template0Edit;
      pPatternEdit = ui->m_Pattern0Edit;
      pFramesEdit = ui->m_Frames0Edit;
   } else {
      pTemplateEdit = ui->m_Template1Edit;
      pPatternEdit = ui->m_Pattern1Edit;
      pFramesEdit = ui->m_Frames1Edit;
   }

   // *** check empty ***
   nLen = (int)strFile.size( );
   if( 0 >= nLen ) {
      bRetCode = true;
      goto PIX_EXIT;
   }

   //pMonitor->DisplayMessage( "===> Image Sequence Side %1d", iSide );

   // check if the file exists

   file.setFileName( strFile );
   if( !file.exists( ) ) {
      strError = QString( "ERROR! The file does not exist!\n\n" ) + strFile;
      QMessageBox::warning( this, _strApplication, strError );
      RemoveFromRecentDirList( iSide, strFile );
      goto PIX_EXIT;
   }

   // --- get the first image pattern from file name ---

   pSeq->Init( );

   // check if this is one of our supported image sequence file
   // get pattern strings from file name

   if (!pixq_ImgSequence::CheckPixFileName(strFile, &sPattern, &iFrameDigit,
      &strPattern, &iFrame ) ) {
         strError = QString( "ERROR! This is not valid Image name " ) + strFile;
         QMessageBox::warning( this, _strApplication, strError );
         goto PIX_EXIT;
   }

#ifdef _DEBUG
   qDebug( ) << "pixq_ImgSequence::CheckPixFileName OK";
   qDebug( ) << "sPattern: " << sPattern;
   qDebug( ) << "iFrameDigit: " << iFrameDigit;
   qDebug( ) << "iFrame: " << iFrame;
#endif

   // *** set pattern to the project! ***

   pSeq->SetPattern( strPattern );
   pSeq->SetFramePattern( sPattern ); 
   pSeq->SetFrameDigit( iFrameDigit );
   pSeq->SetSelectionFrame( iFrame-1 );

   strExt = getFileExtention_PI( strFile );
   pSeq->SetExtention( strExt );

   // get frame range 

   pSeq->SearchFrameRange( );

   // *** add this File to the recent list and show it on combo box ***

   AddToRecentDirList( iSide, strFile, bSelectAdded );

   // *** Set data on dialog ***

   pSeq->GetPatternName( &szPatternType );
   pTemplateEdit->setText( strPattern );
   pPatternEdit->setText( szPatternType );
   
   iFirstFrame = pSeq->GetFirstFrame( );
   iLastFrame = pSeq->GetLastFrame( );
   nFrames = iLastFrame - iFirstFrame + 1;
   strFrames.sprintf( "%d-%d(%d frames)", iFirstFrame+1, iLastFrame+1, nFrames );
   pFramesEdit->setText( strFrames );

   // *** memorize the directory and image

   StoreLastDirectory( iSide, strFile );
   StoreLastFile( iSide, strFile );

   // --- done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
 
//
// check if the selected image format is supported
//
bool sequence_select_dialog::CheckImageFormat( pixq_ImgSequence *pSeq )
{
   bool bRetCode = false;
   QString strExt = pSeq->GetExtention( );

   // --- check image format ---
   
   if (!checkImageFormat_PI(true, strExt)) {
      goto PIX_EXIT;
   }

   // --- done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// check the image sequence and set required data
//
bool sequence_select_dialog::CheckSequence( int iSide )
{
   bool bRetCode = false;
   int nFrames, nWidth, nHeight;
   QString strMessage;
   pixq_ImgSequence *pSeq = GetImgSequence( iSide );

   // --- check image format ---
   
   if( !CheckImageFormat( pSeq ) ) {
      goto PIX_EXIT;
   }

   // --- make a list of all files ---

   if( !pSeq->MakeFileList( ) ) {
      strMessage = QString("ERROR! Failed to make a list of images" );
      QMessageBox::warning( this, _strApplication, strMessage );
      goto PIX_EXIT;
   }

   nFrames = pSeq->FrameCount( );
   if( 0 >= nFrames ) {
      strMessage = QString( "ERROR! No Valid Image for ") + pSeq->GetPattern( );
      QMessageBox::warning( this, _strApplication, strMessage );
      goto PIX_EXIT;
   }

   if( MAX_IMAGE_TEX <= nFrames ) {
      strMessage.sprintf( "ERROR! Number of Frames exceeds the limit. %d>=%d(=MAX_IMAGE_TEX).", 
         nFrames, MAX_IMAGE_TEX );
      QMessageBox::warning( this, _strApplication, strMessage );
      goto PIX_EXIT;
   }

   // set image size for the image sequence

   if( !pSeq->GetImageSize( ) ) {
         strMessage = QString("ERROR! Failed to get image size for the shot!" );
         QMessageBox::warning( this, _strApplication, strMessage );
         goto PIX_EXIT;
      }

   // --- init frame range ---

   pSeq->InitFrameRange( );

   // message
   
   nWidth = pSeq->getImageWidth();
   nHeight = pSeq->getImageHeight( );
   strMessage.sprintf( "Sequence Side %d, Image Size %dW * %dH", iSide+1, nWidth, nHeight );
   ui->_MessageLabel->setText( strMessage );
      
   // --- done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

void sequence_select_dialog::Combo0FileActivated( int iIndex )
{
   ComboFileActivated( 0, iIndex );
}

void sequence_select_dialog::Combo1FileActivated( int iIndex )
{
   ComboFileActivated( 1, iIndex );
}
