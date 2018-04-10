#pragma once

#include <QtCore>
#include <QtGui>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

QT_BEGIN_NAMESPACE
class QPushButton;
class QTabWidget;
QT_END_NAMESPACE

class props_page_image;
class props_page_compare;
class props_page_system;
class props_page_pnt_rectify;
class props_page_cv_rectify;

class pixq_image_opt_dialog : public QDialog
{
    Q_OBJECT

public:
   pixq_image_opt_dialog(QWidget *parent = 0);
   ~pixq_image_opt_dialog(void);

private:
    QTabWidget *_tabWidget;

    QPushButton *buttonDefault;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    
public:
   void Init( const QString strOrganisation, const QString strApplication, 
      pixq_Properties *pEnv, int iMode, short sPage );

   pixq_Properties *getEnv(void) { return _pTmpEnv; }
   void Store( pixq_Properties *pEnv ) { _pTmpEnv = pEnv; }
   
   bool SelectPage( short sPage );

private:
   // option panels used for the program mode
   QVector<short> _optionPanels;

   int _iPropMode;
   QString _strOrganisation;
   QString _strApplication;

   pixq_Properties *_pTmpEnv;

    props_page_image    *_opt_common_image;
    props_page_compare  *_opt_common_compare;
    props_page_system   *_opt_common_system;
    props_page_pnt_rectify   *_opt_common_pnt_rectify;
    props_page_cv_rectify   *_opt_common_cv_rectify;

protected:
   void closeEvent(QCloseEvent *event);
   void showEvent(QShowEvent *event);
   
private slots:
   void ButtonDefaultPressed( void );
   void ButtonOkPressed( void );
   void ButtonCancelPressed( void );
   
private:
   void setAllLabels(void);
};