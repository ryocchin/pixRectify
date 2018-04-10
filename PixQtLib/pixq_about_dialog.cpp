#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "website_label_widget.h"
#include "pixq_about_dialog.h"

pixq_about_dialog::pixq_about_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pixq_about_dialog)
{
    ui->setupUi(this);

    _pVer = (pixq_Version*)NULL;

    return;
}

pixq_about_dialog::~pixq_about_dialog()
{
    delete ui;
}

void pixq_about_dialog::on_ok_button_clicked()
{
   close( );
}

void pixq_about_dialog::Init(const pixq_Version *pVer)
{
   int iLanguage = QLocale::English;
   Init(pVer, iLanguage);

   return;
}

void pixq_about_dialog::Init(const pixq_Version *pVer,
      int iLanguage )
{
   QString strHeader, strValue, strDate, strProgram, strVersion, strProduct;
   QString strPlatform;
   QDate date;
   short usRelease;
   unsigned short sPlatform;

   //

   _pVer = pVer;

   //
   // notes:
   // release number=0の場合は画面に表示しない
   //

   usRelease = pVer->GetReleaseNumber( );
   if( 0 >= usRelease ) {
      strVersion.sprintf( "%d.%d", pVer->GetMajorVersion( ),
         pVer->GetMinorVersion( ) );
   } else {
      strVersion.sprintf( "%d.%d.%d", pVer->GetMajorVersion( ),
         pVer->GetMinorVersion( ),
         usRelease );
   }

   sPlatform = pVer->GetPlatform( );
   switch( sPlatform ) {
   case pixq_Properties::PlatformWin32:
      strPlatform = "[x86]";
      break;
   case pixq_Properties::PlatformWin64:
      strPlatform = "[x64]";
      break;
   case pixq_Properties::PlatformUnknown:
   default:
      strPlatform.clear( );
      break;
   }

   strValue = pVer->getApplication();
   if( !strPlatform.isEmpty( ) ) {
      strValue = strValue + strPlatform;
   }
   strValue = strValue + tr(" ") + strVersion;
   ui->application_label->setText( strValue );

   //

   date = pVer->GetReleaseDate( );
   strDate.sprintf( "%d.%d.%d", date.year( ), date.month( ), date.day( ) );
   ui->release_date_label->setText( strDate );

   switch (iLanguage) {
   case QLocale::Japanese:
      strValue = pVer->GetJpDescription();
      break;
   case QLocale::English:
   default:
      strValue = pVer->GetEnDescription();
      break;
   }
   ui->description_label->setText( strValue );

   strValue = pVer->GetCompany( );
   ui->company_label->setText( strValue );

   strValue = pVer->GetContact( );
   ui->contact_label->setText( strValue );
   ui->contact_label->SetMode( website_label_widget::WebsiteLabelMailAddress );
   
   strValue = pVer->getWebSite( );
   ui->website_label->setText( strValue );
   ui->website_label->SetMode( website_label_widget::WebsiteLabelUrlAddress );

   strValue = pVer->getDevBlog();
   ui->devblog_label->setText(strValue);
   ui->devblog_label->SetMode(website_label_widget::WebsiteLabelBlogAddress);
   
   // 
   
   strProduct = pVer->GetProductName( );
   strHeader = strProduct + tr(" - ") + strVersion;
   setWindowTitle( strHeader );

   return;
}

void pixq_about_dialog::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event);

   return;
}

void pixq_about_dialog::showEvent(QShowEvent *event)
{
   QString strValue;
   QPixmap in_pix, scaled_pix;
   QSize view_size, in_size, scaled_size;
   short sModule;

   QGraphicsScene *scn = new QGraphicsScene( ui->logo_view );

   Q_UNUSED(event);

   if (!_pVer) {
      sModule = pixq_Version::ProgramTypeDefault;
   } else {
      sModule = _pVer->getModule();
   }

   // set image

   view_size = ui->logo_view->viewport()->size( );
   
   scn->setSceneRect( ui->logo_view->rect() );
   ui->logo_view->setScene( scn );

   switch (sModule) {
   case pixq_Version::ProgramTypeBible:
      in_pix = QPixmap(":/images/about_bible.bmp");
      break;
   case pixq_Version::ProgramTypeImage:
      in_pix = QPixmap(":/images/about_image.bmp");
      break;
   case pixq_Version::ProgramTypeDefault:
   default:
      in_pix = QPixmap(":/images/about_default.bmp");
      break;
   }   
   
   in_size = in_pix.size( );
   scaled_pix = in_pix.scaled( view_size );
   scaled_size = scaled_pix.size( );

   scn->addPixmap( scaled_pix );

//PIX_EXIT:
   return;
}
