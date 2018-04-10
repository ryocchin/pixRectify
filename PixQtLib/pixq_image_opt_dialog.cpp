#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_page_image_options.h"

#include "props_page_image.h"
#include "props_page_compare.h"
#include "props_page_system.h"
#include "props_page_pnt_rectify.h"
#include "props_page_cv_rectify.h"

#include "pixq_image_opt_dialog.h"

pixq_image_opt_dialog::pixq_image_opt_dialog(QWidget *parent)
    : QDialog(parent)
{
   QIcon icon;

   //
   
   icon = QIcon( ":/images/hikari_props.png" );
   //icon =QIcon( ":/images/ehagaki2x_options.png" );
   setWindowIcon( icon );

   //
   
   _opt_common_image    = (props_page_image*)NULL;
   _opt_common_compare = (props_page_compare*)NULL;
   _opt_common_system = (props_page_system*)NULL;
   _opt_common_pnt_rectify = (props_page_pnt_rectify*)NULL;
   _opt_common_cv_rectify = (props_page_cv_rectify*)NULL;

   _optionPanels.clear();

   return;
}

pixq_image_opt_dialog::~pixq_image_opt_dialog(void)
{
   //
   
   if( _opt_common_image ) {
      delete _opt_common_image;
      _opt_common_image = NULL;
   }
   
   if (_opt_common_compare) {
      delete _opt_common_compare;
      _opt_common_compare = NULL;
   }   

   if( _opt_common_system ) {
      delete _opt_common_system;
      _opt_common_system = NULL;
   }
   
   if (_opt_common_pnt_rectify) {
      delete _opt_common_pnt_rectify;
      _opt_common_pnt_rectify = NULL;
   }

   if (_opt_common_cv_rectify) {
      delete _opt_common_cv_rectify;
      _opt_common_cv_rectify = NULL;
   }

   _optionPanels.clear();

   return;
} 

void pixq_image_opt_dialog::Init(const QString strOrganisation,
   const QString strApplication, 
   pixq_Properties *pEnv,
   int iMode, // [i] program mode, one of DepthEnvModeSetting
   short sPage )
{
   QSpacerItem *horizontalSpacer;
   QString strLabel;
   int iLang, k, nPanels;
   short sPanel;
   QString strMsgProgram = "Common";

   QHBoxLayout *buttonsLayout = new QHBoxLayout;
   QVBoxLayout *mainLayout = new QVBoxLayout;

   _iPropMode = iMode;
   _strOrganisation = strOrganisation;
   _strApplication = strApplication;

   _pTmpEnv = pEnv;

   iLang = pEnv->_SystemInterfaceLanguage.getInteger();

   //

   _optionPanels.clear();

   switch( iMode ) {

   case EnvModeScope:  
      strLabel = getClassLabel_PC("Option", "Scope", iLang);
      //
      _optionPanels.push_back((short)pixq_Properties::ItemCategorySystem);
      _optionPanels.push_back((short)pixq_Properties::ItemCategoryImage);
      _optionPanels.push_back((short)pixq_Properties::ItemCategoryCompare);
      break;

   case EnvModeRectify:
      strLabel = getClassLabel_PC("Option", "Rectify", iLang);
      //
      _optionPanels.push_back((short)pixq_Properties::ItemCategorySystem);
      _optionPanels.push_back((short)pixq_Properties::ItemCategoryImage);
      //_optionPanels.push_back((short)pixq_Properties::ItemCategoryCompare);
      _optionPanels.push_back((short)pixq_Properties::ItemCategoryPntRectify);
      _optionPanels.push_back((short)pixq_Properties::ItemCategoryCvRectify);
      break;
      
   case EnvModeSampler:
      strLabel = getClassLabel_PC("Option", "Sampler", iLang);
      //
      _optionPanels.push_back((short)pixq_Properties::ItemCategorySystem);
      _optionPanels.push_back((short)pixq_Properties::ItemCategoryImage);
      _optionPanels.push_back((short)pixq_Properties::ItemCategoryCompare);
      break;

   default:
      goto PIX_EXIT;
      break;
   }

   setWindowTitle(strLabel);

   // create and add all panels

   _tabWidget = new QTabWidget;

   nPanels = (int)_optionPanels.size();
   for (k = 0; k < nPanels; k++) {
      sPanel = (short)_optionPanels.at(k);
      switch (sPanel) {

      case pixq_Properties::ItemCategorySystem:
         _opt_common_system = new props_page_system(this);
         _opt_common_system->Store(pEnv);
         //
         strLabel = getClassLabel_PC("PropTabs", "System", iLang);
         _tabWidget->addTab(_opt_common_system, strLabel);
         break;

      case pixq_Properties::ItemCategoryImage:
         _opt_common_image = new props_page_image(this);
         _opt_common_image->Store(pEnv);
         //
         strLabel = getClassLabel_PC("PropTabs", "Image", iLang);
         _tabWidget->addTab(_opt_common_image, strLabel);
         break;

      case pixq_Properties::ItemCategoryCompare:
         _opt_common_compare = new props_page_compare(this);
         _opt_common_compare->Store(pEnv);
         //
         strLabel = getClassLabel_PC("PropTabs", "Compare", iLang);
         _tabWidget->addTab(_opt_common_compare, strLabel);
         break;

      case pixq_Properties::ItemCategoryPntRectify:
         _opt_common_pnt_rectify = new props_page_pnt_rectify(this);
         _opt_common_pnt_rectify->Store(pEnv);
         //
         strLabel = getClassLabel_PC("PropTabs", "RectPoints", iLang);
         _tabWidget->addTab(_opt_common_pnt_rectify, strLabel);
         break;
         
      case pixq_Properties::ItemCategoryCvRectify:
         _opt_common_cv_rectify = new props_page_cv_rectify(this);
         _opt_common_cv_rectify->Store(pEnv);
         //
         strLabel = getClassLabel_PC("PropTabs", "RectCompute", iLang);
         _tabWidget->addTab(_opt_common_cv_rectify, strLabel);
         break;

      default:
         goto PIX_EXIT;
         break;
      }
   }
   
   // buttons control area
   
   horizontalSpacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );

   strLabel = getClassLabel_PC("Control", "Default", iLang);
   buttonDefault = new QPushButton( strLabel );

   buttonOk = new QPushButton( tr("OK") );
   
   strLabel = getClassLabel_PC("Control", "Cancel", iLang);
   buttonCancel = new QPushButton( strLabel );
   
   connect( buttonDefault, SIGNAL(clicked()), this, SLOT(ButtonDefaultPressed()));
   connect( buttonOk, SIGNAL(clicked()), this, SLOT(ButtonOkPressed()));
   connect( buttonCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelPressed()));
 
   //QHBoxLayout *buttonsLayout = new QHBoxLayout;
   buttonsLayout->addSpacerItem( horizontalSpacer );
   buttonsLayout->addWidget( buttonDefault );
   buttonsLayout->addWidget( buttonOk );
   buttonsLayout->addWidget( buttonCancel );

   buttonDefault->setDefault(false);
   buttonOk->setDefault(true);
   buttonCancel->setDefault(false);

   //QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget( _tabWidget );
   mainLayout->addLayout( buttonsLayout );
   setLayout( mainLayout );
   
   // set all labels amd fonts according to language
   
   setAllLabels();
   
   // open the specific page if specified

   if( 0 < sPage ) {
      SelectPage( sPage );
   }

PIX_EXIT:
   return;
}

bool pixq_image_opt_dialog::SelectPage(short sPage)
{
   bool bRetCode = false;
   bool bFound;
   short sID;
   int i;
   int nPages = _tabWidget->count( );
   pixq_page_options *pPage;

   bFound = false;
   for( i = 0 ; i < nPages ; i++ ) {
      pPage = (pixq_page_options*)_tabWidget->widget(i);
      sID = pPage->GetPageID( );
      if( sID != sPage ) continue;
      _tabWidget->setCurrentIndex( i );
      bFound = true;
   }

   if( !bFound ) {
      goto PIX_EXIT;
   }

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


void pixq_image_opt_dialog::showEvent(QShowEvent * /* event */)
{    
   return;
}


void pixq_image_opt_dialog::closeEvent(QCloseEvent * /* event */)
{
   return;
}

void pixq_image_opt_dialog::ButtonDefaultPressed(void)
{
   int nPanels, iTab;
   short sPanel;

   // which tab is shown?
   
   iTab = _tabWidget->currentIndex( ); 
   
   nPanels = (int)_optionPanels.size();
   if (0 > iTab || iTab >= nPanels) {
      goto PIX_EXIT;
   }

   //

   sPanel = (short)_optionPanels.at(iTab);
   switch (sPanel) {
      
   case pixq_Properties::ItemCategorySystem:
      _pTmpEnv->initSystem();
      _opt_common_system->setData();
      break;

   case pixq_Properties::ItemCategoryImage:
      _pTmpEnv->initImage();
      _opt_common_image->setData();
      break;

   case pixq_Properties::ItemCategoryCompare:
      _pTmpEnv->initCompare();
      _opt_common_compare->setData();
      break;

   case pixq_Properties::ItemCategoryPntRectify:
      _pTmpEnv->initPntRectify();
      _opt_common_pnt_rectify->setData();
      break;

   case pixq_Properties::ItemCategoryCvRectify:
      _pTmpEnv->initCvRectify();
      _opt_common_cv_rectify->setData();
      break;

   case pixq_Properties::ItemCategoryMatch:
      _pTmpEnv->initMatch();
      //_opt_common_cv_rectify->setData();
      break;

   case pixq_Properties::ItemCategoryStereo:
      _pTmpEnv->initStereoView();
      //_opt_common_cv_rectify->setData();
      break;

   default:
      goto PIX_EXIT;
      break;
   }

PIX_EXIT:
   return;
}

void pixq_image_opt_dialog::ButtonOkPressed(void)
{
   bool bCheck;
   int k, nPanels;
   short sPanel;

   nPanels = (int)_optionPanels.size();
   for (k = 0; k < nPanels; k++) {
      sPanel = (short)_optionPanels.at(k);
      switch (sPanel) {
         
      case pixq_Properties::ItemCategorySystem:
         bCheck = _opt_common_system->check();
         break;

      case pixq_Properties::ItemCategoryImage:
         bCheck = _opt_common_image->check();
         break;

      case pixq_Properties::ItemCategoryCompare:
         bCheck = _opt_common_compare->check();
         break;

      case pixq_Properties::ItemCategoryPntRectify:
         bCheck = _opt_common_pnt_rectify->check();
         break;

      case pixq_Properties::ItemCategoryCvRectify:
         bCheck = _opt_common_cv_rectify->check();
         break;

      default:
         goto PIX_EXIT;
         break;
      }

      if (!bCheck) {
         _tabWidget->setCurrentIndex(k);
         goto PIX_EXIT;
      }
   }

   accept( );
   
PIX_EXIT:
   return;
}

void pixq_image_opt_dialog::ButtonCancelPressed(void)
{
   reject( );

   return;
}


void pixq_image_opt_dialog::setAllLabels(void)
{
   int k, nPanels;
   short sPanel;

   nPanels = (int)_optionPanels.size();
   for (k = 0; k < nPanels; k++) {
      sPanel = (short)_optionPanels.at(k);
      switch (sPanel) {
         
      case pixq_Properties::ItemCategorySystem:
         _opt_common_system->setLabels();
         break;

      case pixq_Properties::ItemCategoryImage:
         _opt_common_image->setLabels();
         break;

      case pixq_Properties::ItemCategoryCompare:
         _opt_common_compare->setLabels();
         break;

      case pixq_Properties::ItemCategoryPntRectify:
         _opt_common_pnt_rectify->setLabels();
         break;

      case pixq_Properties::ItemCategoryCvRectify:
         _opt_common_cv_rectify->setLabels();
         break;

      default:
         continue;
         break;
      }
   }

//PIX_EXIT:
   return;
}
