#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_page_options.h"

pixq_page_options::pixq_page_options(void)
{
   return;
}

pixq_page_options::~pixq_page_options(void)
{
   return;
}


void pixq_page_options::setOptionFont(QWidget *pWidget)
{
   QFont fnt = pWidget->font();

   QString strFamily = "Ariel";
   bool bBold = false;
   int iPointSize = 9;
   
   fnt.setBold(bBold);
   fnt.setFamily(strFamily);
      fnt.setItalic(false);
   fnt.setPointSize( iPointSize);

   pWidget->setFont(fnt);

   return;
}


void pixq_page_options::setBool(pixq_EnvItem *pItem,
                                QCheckBox *pCheck )
{
   bool bValue = pItem->getBool();
   pCheck->setCheckState( bValue ? Qt::Checked : Qt::Unchecked );

   return;
}

void pixq_page_options::getBool(pixq_EnvItem *pItem,
                                QCheckBox *pCheck )
{   
   Qt::CheckState cs = pCheck->checkState( );
   bool bValue = ( Qt::Checked == cs ) ? true : false;
   pItem->Set( bValue );

   return;
}

void pixq_page_options::setInteger(int iValue,
                                int iMin, 
                                int nMax, 
                                QLineEdit *pEdit )
{
   QString strValue;
    
   strValue.sprintf( "%d", iValue );
   pEdit->setText( strValue );
   
   pEdit->setValidator( new QIntValidator( iMin, nMax, pEdit ) );
   
   return;
}

void pixq_page_options::setInteger(int iValue,
                                QLineEdit *pEdit )
{    
   QString strValue;
    
   strValue.sprintf( "%d", iValue );
   pEdit->setText( strValue );
   
   return;
}

void pixq_page_options::setInteger(pixq_EnvItem *pItem,
                               QLineEdit *pEdit )
{
   QString strValue;

   bool bRange = pItem->getRange();
   int iValue = pItem->getInteger();

   if( bRange ) {
      int iMin = pItem->getIntMin();
      int nMax = pItem->getIntMax();
      setInteger(iValue, iMin, nMax, pEdit);
   } else {
      setInteger(iValue, pEdit);
   }

   return;
}

void pixq_page_options::setSpinInteger(pixq_EnvItem *pItem,
                                   QSpinBox *pSpin )
{
   QString strValue;
   int iMin;
   int nMax;

   bool bRange = pItem->getRange();
   int iValue = pItem->getInteger();

   if( bRange ) {
      iMin = pItem->getIntMin();
      nMax = pItem->getIntMax();
   } else {
      iMin = -1000;
      nMax = 1000;
   }

   pSpin->setSingleStep( 1 );
   pSpin->setMinimum( iMin );
   pSpin->setMaximum( nMax );
   pSpin->setValue( iValue );

   return;
}

bool pixq_page_options::getSpinInteger(pixq_EnvItem *pItem,
                                    QSpinBox *pSpin )
{
   bool bRetCode = false;
   int iValue;

   iValue = pSpin->value( );

   pItem->Set( iValue );  

   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

bool pixq_page_options::getInteger(int *iValue,
                                 QLineEdit *pEdit )
{   
   bool bRetCode = false;
   bool bOK;
   QString strValue;

   // median filter radius

   strValue = pEdit->text( );
   *iValue = strValue.toInt( &bOK );
   if( !bOK ) {
      pEdit->setFocus( Qt::MouseFocusReason );
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_page_options::getInteger(pixq_EnvItem *pItem,
                                QLineEdit *pEdit )
{   
   bool bRetCode = false;
   int iValue;

   bool bRange = pItem->getRange();

   if (!getInteger(&iValue, pEdit)) {
      pEdit->setFocus( Qt::MouseFocusReason );
      goto PIX_EXIT;
   }

   // check value range

   if (!pItem->checkIntegerRange(iValue)) {
      goto PIX_EXIT;
   }

   pItem->Set( iValue );  

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

void pixq_page_options::set2Double(pixq_EnvItem *pItem,
                               QLineEdit *pEdit )
{
   setDouble(pItem, pEdit, "%.2f");
   
   return;
}

void pixq_page_options::set2Double(double dValue,
                               QLineEdit *pEdit )
{
   setDouble(dValue, pEdit, "%.2f");
   
   return;
}

void pixq_page_options::setDouble(pixq_EnvItem *pItem,
                                  QLineEdit *pEdit, 
                                  const char *szFormat )
{
   double dValue = pItem->getDouble();
   bool bRange = pItem->getRange();

   if( bRange ) {
      //double dMin = pItem->getDoubleMin( );
      //double dMax = pItem->getDoubleMax( );
      //pEdit->setValidator( new QDoubleValidator( dMin, dMax, iDecimals, pEdit ) );
   }

   setDouble(dValue, pEdit, szFormat);
   
   return;
}

void pixq_page_options::setDouble(double dValue,
                               QLineEdit *pEdit, 
                               const char *szFormat )
{
   QString strValue;
   //int iDecimals = 3;

   strValue.sprintf( szFormat, dValue );
   pEdit->setText( strValue ); 
   
   return;
}

bool pixq_page_options::getDouble(double *dValue,
                               QLineEdit *pEdit )
{   
   bool bRetCode = false;
   bool bOK;
   QString strValue;

   // median filter radius

   strValue = pEdit->text( );
   *dValue = strValue.toDouble( &bOK );
   if( !bOK ) {
      pEdit->setFocus( Qt::MouseFocusReason );
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_page_options::getDouble(pixq_EnvItem *pItem,
                               QLineEdit *pEdit )
{   
   bool bRetCode = false;
   double dValue;

   if (!getDouble(&dValue, pEdit)) {
      pEdit->setFocus( Qt::MouseFocusReason );
      goto PIX_EXIT;
   }

   pItem->Set( dValue );  

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

void pixq_page_options::setString(pixq_EnvItem *pItem,
                              QLineEdit *pEdit )
{
   QString strValue = pItem->getString();
   pEdit->setText( strValue ); 
   
   return;
}

void pixq_page_options::getString(pixq_EnvItem *pItem,
                              QLineEdit *pEdit )
                              const
{
   QString strValue = pEdit->text( );

   pItem->Set( strValue ); 
   
   return;
}

//
// is something entered in line edit?
//
// returns:
// true if it is empty
// 
bool pixq_page_options::isEmpty(QLineEdit *pEdit)
   const
{
   bool bRetCode = false;
   QString strValue = pEdit->text();

   if (strValue.isEmpty()) {
      // empty
      pEdit->setFocus(Qt::MouseFocusReason);
   }
   else { 
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

void pixq_page_options::clearItem(QLineEdit *pEdit)
{
   pEdit->clear( );

   return;
}


void pixq_page_options::focusEdit(QLineEdit *pEdit)
{
   pEdit->setFocus(Qt::MouseFocusReason);

   return;
}