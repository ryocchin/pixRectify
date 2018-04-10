#pragma once

#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QApplication>

#include <Magick++.h>
using namespace Magick;

namespace Ui {
    class sequence_select_dialog;
}

#include <pixqtlib.h>
#include <piximglib.h>

class sequence_select_dialog : public QDialog
{
   Q_OBJECT

public:
   explicit sequence_select_dialog( QWidget *parent = NULL );
   ~sequence_select_dialog( void );
   
private:
   Ui::sequence_select_dialog *ui;

private slots:
   void ClickOkButton( void );
   void ClickCancelButton( void );

   void ClickClearHistoryButton( void );

   void ClickSelect0Image( void );
   void ClickSelect1Image( void );

   void Combo0FileActivated( int iIndex );
   void Combo1FileActivated( int iIndex );

protected:
   bool eventFilter( QObject *obj, QEvent *ev );

private:
   
   // for QSetting
   QString _strOrganisation;
   QString _strApplication; 
   
   pixq_Properties *_pDepthEnv;
   pixq_ImgSequence *m_pImgSequence[2];

private:
   void ComboReturnPressed( int iSide );

   void ComboFileActivated( int iSide, int iIndex );
   void ComboKeyPressed( int iSide, QKeyEvent *eve );

   bool SelectSingleImage( int iSide, QString *szFile );

   bool ImageSelected( int iSide, QString strFile, bool bSelectAdded );
   
   // check if the selected image format is supported

   bool CheckImageFormat( pixq_ImgSequence *pSeq );
   
   // check the image sequence and set required data
   bool CheckSequence( int iSide ); 

   void SetRecentFileList( int iSide );
   void AddToRecentDirList( int iSide, QString strPattern, bool bSelectAdded );
   void RemoveFromRecentDirList( int iSide, QString strPattern );
   
   void RemoveAllFromRecentDirList( int iSide );

   QString SetKeyString( int iSide, int iNumber );
   QString GetLastDirectory( int iSide );
   QString GetLastFile( int iSide );

   void StoreLastDirectory( int iSide, QString strFile );   
   void StoreLastFile( int iSide, QString strFile );

public:   
   pixq_Properties *getEnv(void) { return _pDepthEnv; }
   pixq_ImgSequence *GetImgSequence( int iSide ) { return m_pImgSequence[iSide]; }

   void SelectImage( int iSide );
   
   void Init( const QString strOrganisation, const QString strApplication,
      pixq_Properties *pEnv, 
      pixq_ImgSequence *pSeq );

   void Init( const QString strOrganisation, const QString strApplication,
       pixq_Properties *pEnv, 
      pixq_ImgSequence *pSeq0,
      pixq_ImgSequence *pSeq1 );

   void Init( const QString strOrganisation, const QString strApplication,
       pixq_Properties *pEnv, 
      pixq_ImgSequence *pSeq0,
      pixq_ImgSequence *pSeq1,
      bool bDouble );
};