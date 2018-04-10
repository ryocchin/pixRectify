#pragma once

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>

class PIXQTLIB_EXPORT pixq_page_options
{
protected:
   // one of ItfEnvItemCategory
   short _sPageId;
   
public:
   pixq_page_options(void);
   virtual ~pixq_page_options(void);

public:
   virtual void setLabels(void) = 0;
   virtual void setData(void) = 0;
   virtual bool check( void ) = 0;

public:  
   void setOptionFont(QWidget *pWidget);  

public:
   void setBool(pixq_EnvItem *pItem, QCheckBox *pEdit);
   void getBool(pixq_EnvItem *pItem, QCheckBox *pEdit);

   void setString(pixq_EnvItem *pItem, QLineEdit *pEdit);
   void getString(pixq_EnvItem *pItem, QLineEdit *pEdit) const;
   
   void setInteger( int iValue, int iMin, int nMax, QLineEdit *pEdit );
   void setInteger(int iValue, QLineEdit *pEdit);
   void setInteger(pixq_EnvItem *pItem, QLineEdit *pEdit);

   bool getInteger(int *iValue, QLineEdit *pEdit);
   bool getInteger(pixq_EnvItem *pItem, QLineEdit *pEdit);

   bool getSpinInteger( pixq_EnvItem *pItem, QSpinBox *pSpin );
   void setSpinInteger( pixq_EnvItem *pItem, QSpinBox *pSpin );

   void set2Double(double dValue, QLineEdit *pEdit);
   void set2Double(pixq_EnvItem *pItem, QLineEdit *pEdit);

   void setDouble(double dValue, QLineEdit *pEdit, const char *szFormat);
   void setDouble(pixq_EnvItem *pItem, QLineEdit *pEdit, const char *szFormat);

   bool getDouble(double *dValue, QLineEdit *pEdit);
   bool getDouble(pixq_EnvItem *pItem, QLineEdit *pEdit);

   void clearItem(QLineEdit *pEdit);
   bool isEmpty(QLineEdit *pEdit) const;
   void focusEdit(QLineEdit *pEdit);

   short GetPageID( void ) { return _sPageId; }
};


} // namespace 

