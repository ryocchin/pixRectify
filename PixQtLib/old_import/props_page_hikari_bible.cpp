#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_options_page.h"

#include "props_page_hikari_bible.h"
#include "ui_props_page_hikari_bible.h"

props_page_hikari_bible::props_page_hikari_bible(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::props_page_hikari_bible)
{
   ui->setupUi(this);
   _sPageId = (short)pixq_EnvItem::ItemCategoryHikariBible;
}

props_page_hikari_bible::~props_page_hikari_bible()
{
   delete ui;
}

void props_page_hikari_bible::closeEvent(QCloseEvent * /* event */ )
{
   Check( );

   return;
}

void props_page_hikari_bible::SetData( void )
{
   pixq_Properties *pEnv = GetEnv( );
   bool bEnable;
   int iVersion;
   QTime time;

   // shin-kaiyaku and shin-kyoudouyaku may/may not exist according to the system

   iVersion = pixq_Properties::BibleShinkaiyaku2; 
   bEnable = pixq_Properties::VersionBibleCompressedExist( iVersion );
   ui->hikari_version_shinkai2_radio->setEnabled( bEnable );
   ui->hikari_2nd_version_shinkai2_radio->setEnabled( bEnable );
   ui->search_shinkai2_check->setEnabled( bEnable );
   
   iVersion = pixq_Properties::BibleShinkaiyaku3;
   bEnable = pixq_Properties::VersionBibleCompressedExist( iVersion );
   ui->hikari_version_shinkai3_radio->setEnabled( bEnable );
   ui->hikari_2nd_version_shinkai3_radio->setEnabled( bEnable );
   ui->search_shinkai3_check->setEnabled( bEnable );
   
   iVersion = pixq_Properties::BibleShinKyoudouyaku;
   bEnable = pixq_Properties::VersionBibleCompressedExist( iVersion );
   ui->hikari_version_kyoudou_radio->setEnabled( bEnable );
   ui->hikari_2nd_version_kyoudou_radio->setEnabled( bEnable );
   ui->search_kyoudou_check->setEnabled( bEnable );

   // bible version

   SetBibleVersion( );
   SetSecondBibleVersion( );

   // use this bible version for search?
   
   SetBool( &pEnv->_HikariBibleSearchShinkaiyaku2, ui->search_shinkai2_check );
   SetBool( &pEnv->_HikariBibleSearchShinkaiyaku3, ui->search_shinkai3_check );
   SetBool( &pEnv->_HikariBibleSearchShinkyoudou, ui->search_kyoudou_check );
   SetBool( &pEnv->_HikariBibleSearchKougoyaku, ui->search_kougo_check );
   SetBool(&pEnv->_HikariBibleSearchKingJames, ui->search_kjv_check);
   SetBool(&pEnv->_HikariBibleSearchAmericanKingJames, ui->search_akjv_check);
   SetBool(&pEnv->_HikariBibleSearchIntlStandard, ui->search_isv_check); 
   SetBool( &pEnv->_HikariBibleSearchBungo, ui->search_bungo_check );
   SetBool( &pEnv->_HikariBibleSearchRaguet, ui->search_raguet_check );
   SetBool( &pEnv->_HikariBibleSearchTsukamoto, ui->search_tsukamoto_check );

   return;
}

//
// returns:
// true
// false, if some unacceptale values are set
//
bool props_page_hikari_bible::Check( void )
{
   bool bRetCode = false;
   pixq_Properties *pEnv = GetEnv( );

   // bible version

   // already set by radio

   // use this bible version for search?
   
   GetBool( &pEnv->_HikariBibleSearchShinkaiyaku2, ui->search_shinkai2_check );
   GetBool( &pEnv->_HikariBibleSearchShinkaiyaku3, ui->search_shinkai3_check );   
   GetBool( &pEnv->_HikariBibleSearchShinkyoudou, ui->search_kyoudou_check );
   GetBool(&pEnv->_HikariBibleSearchKougoyaku, ui->search_kougo_check);
   GetBool(&pEnv->_HikariBibleSearchKingJames, ui->search_kjv_check);
   GetBool(&pEnv->_HikariBibleSearchAmericanKingJames, ui->search_akjv_check);
   GetBool( &pEnv->_HikariBibleSearchIntlStandard, ui->search_isv_check ); 
   GetBool( &pEnv->_HikariBibleSearchBungo, ui->search_bungo_check );
   GetBool( &pEnv->_HikariBibleSearchRaguet, ui->search_raguet_check );
   GetBool( &pEnv->_HikariBibleSearchTsukamoto, ui->search_tsukamoto_check );

   // --- DOne ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

//
// set texture style mode
//
void props_page_hikari_bible::SetBibleVersion( void )
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion;
   
   ui->hikari_version_shinkai2_radio->setChecked( false );
   ui->hikari_version_shinkai3_radio->setChecked( false );
   ui->hikari_version_kyoudou_radio->setChecked( false );
   ui->hikari_version_bungo_radio->setChecked( false );
   ui->hikari_version_kougo_radio->setChecked( false );
   ui->hikari_version_raguet_radio->setChecked(false);
   ui->hikari_version_kjv_radio->setChecked(false);
   ui->hikari_version_akjv_radio->setChecked(false);
   ui->hikari_version_isv_radio->setChecked( false );

   // bible version

   iVersion = pEnv->_HikariBibleVersion.GetInt( );

   switch( iVersion ) {
   case pixq_Properties::BibleShinkaiyaku2: 
      ui->hikari_version_shinkai2_radio->setChecked( true );
      break;
   case pixq_Properties::BibleShinkaiyaku3:
      ui->hikari_version_shinkai3_radio->setChecked( true );
      break;
   case pixq_Properties::BibleShinKyoudouyaku:
      ui->hikari_version_kyoudou_radio->setChecked( true );
      break;
   case pixq_Properties::BibleBungo: 
      ui->hikari_version_bungo_radio->setChecked( true );
      break;
   case pixq_Properties::BibleRaguet:
      ui->hikari_version_raguet_radio->setChecked( true );
      break;
   case pixq_Properties::BibleTsukamoto:
      ui->hikari_version_tsukamoto_radio->setChecked( true );
      break;
   case pixq_Properties::BibleKougoyaku:
      ui->hikari_version_kougo_radio->setChecked( true );
      break;
   case pixq_Properties::BibleKingJames:
      ui->hikari_version_kjv_radio->setChecked(true);
      break;
   case pixq_Properties::BibleAmericanKingJames:
      ui->hikari_version_akjv_radio->setChecked(true);
      break;
   case pixq_Properties::BibleIntlStandard: 
      ui->hikari_version_isv_radio->setChecked( true );
      break;
   }

   return;
}

void props_page_hikari_bible::SetSecondBibleVersion( void )
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion;
   
   ui->hikari_2nd_version_shinkai2_radio->setChecked( false );
   ui->hikari_2nd_version_shinkai3_radio->setChecked( false );
   ui->hikari_2nd_version_kyoudou_radio->setChecked( false );
   ui->hikari_2nd_version_bungo_radio->setChecked( false );
   ui->hikari_2nd_version_kougo_radio->setChecked( false );
   ui->hikari_2nd_version_raguet_radio->setChecked(false);
   ui->hikari_2nd_version_kjv_radio->setChecked(false);
   ui->hikari_2nd_version_akjv_radio->setChecked(false);
   ui->hikari_2nd_version_isv_radio->setChecked( false );

   // bible version

   iVersion = pEnv->_HikariBibleSecondVersion.GetInt( );

   switch( iVersion ) {
   case pixq_Properties::BibleShinkaiyaku2: 
      ui->hikari_2nd_version_shinkai2_radio->setChecked( true );
      break;
   case pixq_Properties::BibleShinkaiyaku3:
      ui->hikari_2nd_version_shinkai3_radio->setChecked( true );
      break;
   case pixq_Properties::BibleShinKyoudouyaku:
      ui->hikari_2nd_version_kyoudou_radio->setChecked( true );
      break;
   case pixq_Properties::BibleBungo: 
      ui->hikari_2nd_version_bungo_radio->setChecked( true );
      break;
   case pixq_Properties::BibleRaguet:
      ui->hikari_2nd_version_raguet_radio->setChecked( true );
      break;
   case pixq_Properties::BibleTsukamoto:
      ui->hikari_2nd_version_tsukamoto_radio->setChecked( true );
      break;
   case pixq_Properties::BibleKougoyaku:
      ui->hikari_2nd_version_kougo_radio->setChecked( true );
      break;
   case pixq_Properties::BibleKingJames:
      ui->hikari_2nd_version_kjv_radio->setChecked(true);
      break;
   case pixq_Properties::BibleAmericanKingJames:
      ui->hikari_2nd_version_akjv_radio->setChecked(true);
      break;
   case pixq_Properties::BibleIntlStandard: 
      ui->hikari_2nd_version_isv_radio->setChecked( true );
      break;
   }

   return;
}

void props_page_hikari_bible::on_hikari_version_shinkai2_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleShinkaiyaku2; 

   pEnv->_HikariBibleVersion.Set( iVersion );
   SetBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_version_shinkai3_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleShinkaiyaku3;

   pEnv->_HikariBibleVersion.Set( iVersion );
   SetBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_version_kyoudou_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleShinKyoudouyaku;

   pEnv->_HikariBibleVersion.Set( iVersion );
   SetSecondBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_version_bungo_radio_clicked()
{
    pixq_Properties *pEnv = GetEnv( );
    int iVersion = pixq_Properties::BibleBungo; 

    pEnv->_HikariBibleVersion.Set( iVersion );
    SetBibleVersion( );

    return;
}

void props_page_hikari_bible::on_hikari_version_raguet_radio_clicked()
{
    pixq_Properties *pEnv = GetEnv( );
    int iVersion = pixq_Properties::BibleRaguet;

    pEnv->_HikariBibleVersion.Set( iVersion );
    SetBibleVersion( );

    return;
}

void props_page_hikari_bible::on_hikari_version_tsukamoto_radio_clicked()
{
    pixq_Properties *pEnv = GetEnv( );
    int iVersion = pixq_Properties::BibleTsukamoto;

    pEnv->_HikariBibleVersion.Set( iVersion );
    SetBibleVersion( );

    return;
}

void props_page_hikari_bible::on_hikari_version_kougo_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleKougoyaku;

   pEnv->_HikariBibleVersion.Set( iVersion );
   SetBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_version_kjv_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleKingJames; 

   pEnv->_HikariBibleVersion.Set( iVersion );
   SetBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_version_akjv_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv();
   int iVersion = pixq_Properties::BibleAmericanKingJames;

   pEnv->_HikariBibleVersion.Set(iVersion);
   SetBibleVersion();

   return;
}

void props_page_hikari_bible::on_hikari_version_isv_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleIntlStandard; 

   pEnv->_HikariBibleVersion.Set( iVersion );
   SetBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_2nd_version_shinkai2_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleShinkaiyaku2; 

   pEnv->_HikariBibleSecondVersion.Set( iVersion );
   SetSecondBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_2nd_version_shinkai3_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleShinkaiyaku3;

   pEnv->_HikariBibleSecondVersion.Set( iVersion );
   SetBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_2nd_version_kyoudou_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleShinKyoudouyaku;

   pEnv->_HikariBibleSecondVersion.Set( iVersion );
   SetSecondBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_2nd_version_bungo_radio_clicked()
{
    pixq_Properties *pEnv = GetEnv( );
    int iVersion = pixq_Properties::BibleBungo; 

    pEnv->_HikariBibleSecondVersion.Set( iVersion );
    SetSecondBibleVersion( );

    return;
}

void props_page_hikari_bible::on_hikari_2nd_version_kougo_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleKougoyaku;

   pEnv->_HikariBibleSecondVersion.Set( iVersion );
   SetSecondBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_2nd_version_raguet_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleRaguet;

   pEnv->_HikariBibleSecondVersion.Set( iVersion );
   SetSecondBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_2nd_version_tsukamoto_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleTsukamoto;

   pEnv->_HikariBibleSecondVersion.Set( iVersion );
   SetSecondBibleVersion( );

   return;
}


void props_page_hikari_bible::on_hikari_2nd_version_kjv_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleKingJames; 

   pEnv->_HikariBibleSecondVersion.Set( iVersion );
   SetSecondBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_2nd_version_isv_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv( );
   int iVersion = pixq_Properties::BibleIntlStandard; 

   pEnv->_HikariBibleSecondVersion.Set( iVersion );
   SetSecondBibleVersion( );

   return;
}

void props_page_hikari_bible::on_hikari_2nd_version_akjv_radio_clicked()
{
   pixq_Properties *pEnv = GetEnv();
   int iVersion = pixq_Properties::BibleAmericanKingJames; 

   pEnv->_HikariBibleSecondVersion.Set(iVersion);
   SetSecondBibleVersion();

   return;
}
