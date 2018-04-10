#include <QtGui>
#include <QDesktopServices>
#include <QUrl>

#include "website_label_widget.h"

website_label_widget::website_label_widget(QWidget *parent)
    : QLabel(parent)
{
   _defCursor = cursor( );
   _sMode = WebsiteLabelNone;
}

void website_label_widget::mousePressEvent( QMouseEvent * event ) 
{
   Q_UNUSED(event);
   QString strSite;
   QString strUrl = text( );

   switch( _sMode ) {
   case WebsiteLabelUrlAddress:
      // open the site with standard browser
      strSite = "http://" + strUrl;
      QDesktopServices::openUrl( QUrl( strSite ) );
      break;

   case WebsiteLabelMailAddress:
      // send e-mail using standard mail client
      strSite = "mailto:" + strUrl + "?subject=Re:PixTOPO";
      QDesktopServices::openUrl( QUrl( strSite ) );
      break;

   case WebsiteLabelBlogAddress:
      // open the site with standard browser
      strSite = "http://" + strUrl;
      QDesktopServices::openUrl(QUrl(strSite));
      break;      
   }

   return;
}

void website_label_widget::enterEvent ( QEvent * event )
{
   Q_UNUSED(event);

   _defCursor = cursor( );
   setCursor( Qt::PointingHandCursor );

   return;
}

void website_label_widget::leaveEvent ( QEvent * event ) 
{
   Q_UNUSED(event);

   setCursor( _defCursor );

   return;
}