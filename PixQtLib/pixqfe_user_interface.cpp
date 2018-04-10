#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

//
// custom widgets
//

#include "pixq_about_dialog.h"
#include "pixq_image_opt_dialog.h"

void showPixAbout_PC(const pixq_Version *pVer)
{
   pixq_about_dialog dlg;
   int iLanguage = QLocale::English;

   dlg.Init(pVer, iLanguage);
   dlg.exec( );

   return;
}

void showPixAbout_PC(const pixq_Version *pVer,
   const pixq_Properties *pEnv)
{
   pixq_about_dialog dlg;
   int iLanguage = pEnv->_SystemInterfaceLanguage.getInteger();

   dlg.Init(pVer, iLanguage);
   dlg.exec();

   return;
}

bool showPixProperty_PC(const QString strOrganisation,
                        const QString strApplication, 
                        pixq_Properties *pEnv,
                        int iMode ) // [i] program mode, one of PixEnvModeSetting
{
   bool bRetCode = false;
   short sPage = -1;
   
   if (!showPixProperty_PC(strOrganisation, strApplication, pEnv, iMode, sPage)) {
      ;
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool showPixProperty_PC( const QString strOrganisation, 
                           const QString strApplication, 
                           pixq_Properties *pEnv,                           
                           int iMode, // [i] program mode, one of PixEnvModeSetting
                           short sPage )
{
   bool bRetCode = false;
   pixq_image_opt_dialog dlg;
   int iRet;
   pixq_Properties TmpEnv;

   TmpEnv.initEnv(strOrganisation, strApplication);
   TmpEnv = *pEnv;

   dlg.Init( strOrganisation, strApplication, &TmpEnv, iMode, sPage );

   iRet = dlg.exec( );
   switch( iRet ) {
   case QDialog::Accepted:
      
      break;
   case QDialog::Rejected:
      // canceled
      goto PIX_EXIT;
      break;
   }
   
   // store the changed env

   *pEnv = TmpEnv;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// show windows version and bit
//
void showWindowsVersion_PC(void)
{
   QSysInfo::WinVersion ver = QSysInfo::windowsVersion();
   QString strArch, strMessage, strProc, strVersion;
   short sPa;
   QMessageBox box;
   QIcon icon;
   QPixmap pix;
   QSettings *reg = NULL;

   SYSTEM_INFO si;
   
   // Windows version

   switch (ver) {
   case QSysInfo::WV_32s:
      strVersion = "Windows 3.1 with Win 32s";
      break;
   case QSysInfo::WV_95:
      strVersion = "Windows 95";
      break;
   case QSysInfo::WV_98:
      strVersion = "Windows 98";
      break;
   case QSysInfo::WV_Me:
      strVersion = "Windows Me";
      break;
   case QSysInfo::WV_NT:
      strVersion = "Windows NT (operating system version 4.0)";
      break;
   case QSysInfo::WV_2000:
      strVersion = "Windows 2000 (operating system version 5.0)";
      break;
   case QSysInfo::WV_XP:
      strVersion = "Windows XP (operating system version 5.1)";
      break;
   case QSysInfo::WV_2003:
      strVersion = "Windows Server 2003, Windows Server 2003 R2, Windows Home Server, Windows XP Professional x64 Edition (operating system version 5.2)";
      break;
   case QSysInfo::WV_VISTA:
      strVersion = "Windows Vista, Windows Server 2008 (operating system version 6.0)";
      break;
   case QSysInfo::WV_WINDOWS7:
      strVersion = "Windows 7, Windows Server 2008 R2 (operating system version 6.1)";
      break;
   case QSysInfo::WV_WINDOWS8:
      strVersion = "Windows 8 (operating system version 6.2)";
      break;

      //case QSysInfo::WV_4_0:
      //   strVersion = "Operating system version 4.0, corresponds to Windows NT";
      //   break;
      //case QSysInfo::WV_5_0:
      //   strVersion = "Operating system version 5.0, corresponds to Windows 2000";
      //   break;
      //case QSysInfo::WV_5_1:
      //   strVersion = "Operating system version 5.1, corresponds to Windows XP";
      //   break;
      //case QSysInfo::WV_5_2:
      //   strVersion = "Operating system version 5.2, corresponds to Windows Server 2003, Windows Server 2003 R2, Windows Home Server, and Windows XP Professional x64 Edition";
      //   break;
      //case QSysInfo::WV_6_0:
      //   strVersion = "Operating system version 6.0, corresponds to Windows Vista and Windows Server 2008";
      //   break;
      //case QSysInfo::WV_6_1:
      //   strVersion = "Operating system version 6.1, corresponds to Windows 7 and Windows Server 2008 R2";
      //   break;
      //case QSysInfo::WV_6_2:
      //   strVersion = "Operating system version 6.2, corresponds to Windows 8";
      //   break;   

   case QSysInfo::WV_CE:
      strVersion = "Windows CE";
      break;
   case QSysInfo::WV_CENET:
      strVersion = "Windows CE .NET";
      break;
   case QSysInfo::WV_CE_5:
      strVersion = "Windows CE 5.x";
      break;
   case QSysInfo::WV_CE_6:
      strVersion = "Windows CE 6.x";
      break;

   case QSysInfo::WV_DOS_based:
      strVersion = "MS-DOS-based version of Windows";
      break;
   case QSysInfo::WV_NT_based:
      strVersion = "NT-based version of Windows";
      break;
   case QSysInfo::WV_CE_based:
      strVersion = "CE-based version of Windows";
      break;
   default:
      strVersion.sprintf("Unknown Version of Windows(%d)", (int)ver);
      break;
   }

   // get processor name

   reg = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
      QSettings::NativeFormat);

   strProc = reg->value("Identifier").toString();

   //

   GetNativeSystemInfo(&si);
   sPa = (short)si.wProcessorArchitecture;
   switch (sPa) {
   case PROCESSOR_ARCHITECTURE_AMD64:
      strArch = "x64 (AMD or Intel)";
      break;
   case PROCESSOR_ARCHITECTURE_ARM:
      strArch = "ARM";
      break;
   case PROCESSOR_ARCHITECTURE_IA64:
      strArch = "Intel Itanium-based";
      break;
   case PROCESSOR_ARCHITECTURE_INTEL:
      strArch = "x86";
      break;
   case PROCESSOR_ARCHITECTURE_UNKNOWN:
   default:
      strArch = "Unknown architecture";
      break;
   }

   //

   strMessage = "Windows:";
   strMessage = strMessage + "\n";
   strMessage = strMessage + getClassLabel_PC("Gamen", "WinVersion");
   strMessage = strMessage + ": ";
   strMessage = strMessage + strVersion;
   strMessage = strMessage + "\n";

   strMessage = strMessage + getClassLabel_PC("Gamen", "Processor");
   strMessage = strMessage + ": ";
   strMessage = strMessage + strProc;
   strMessage = strMessage + "\n";
   strMessage = strMessage + "\n";

   strMessage = strMessage + getClassLabel_PC("Gamen", "Architecture");
   strMessage = strMessage + ": ";
   strMessage = strMessage + strArch;

   icon = QIcon(":/images/info.png");
   box.setWindowIcon(icon);

   pix = QPixmap(":/images/info.png");
   box.setIconPixmap(pix);

   box.setWindowTitle("System Information");
   box.setText(strMessage);
   box.exec();

   if (reg) {
      delete reg;
      reg = NULL;
   }
   return;
}

//
// analyze and determine whether the machin has "access database engine" installed
//
void checkAccessDatabaseEngine_PC(void)
{
   QSettings *reg = NULL;
   QString strMessage, strValue, strProducts, strProduct;
   QStringList kids;
   int k, nKids;
   bool bFound;
   QString strAccess = "Microsoft Access database engine";
   QMessageBox box;
   QIcon icon;
   QPixmap pix;
   
   // get processor name

   strProducts = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\Installer\\Products";
   reg = new QSettings(strProducts, QSettings::NativeFormat);

   kids = reg->childGroups();
   nKids = (int)kids.size();

   // check all children of installer\\products

   bFound = false;
   for (k = 0; !bFound && k < nKids; k++) {
      strProduct = strProducts + "\\" + kids.at(k);
      QSettings prod(strProduct, QSettings::NativeFormat);
      strValue = prod.value("ProductName").toString();
      if (0 > strValue.indexOf(strAccess, Qt::CaseInsensitive)) {
         continue;
      }
      bFound = true;
   }

   //

   icon = QIcon(":/images/info.png");
   box.setWindowIcon(icon);

   pix = QPixmap(":/images/info.png");
   box.setIconPixmap(pix);

   box.setWindowTitle("Access Database Engine");

   if (bFound) {
      strMessage = getClassLabel_PC("Gamen", "AdbInstalled");
      box.setText(strMessage);
      box.exec();
      goto PIX_EXIT;
   }

   // access database engine not found

   //box.addButton( getClassLabel_PC( "Gamen", "Install" ), QMessageBox::AcceptRole );
   box.addButton(getClassLabel_PC("Gamen", "Close"), QMessageBox::AcceptRole);

   strMessage = getClassLabel_PC("Gamen", "AdbNotInstalled");
   strMessage = strMessage + "\n\n";
   strMessage = strMessage + getClassLabel_PC("Gamen", "AdbtInstall");
   strMessage = strMessage + "\n\n";
   strMessage = strMessage + getClassLabel_PC("Gamen", "AdbtNowInstall");
   box.setText(strMessage);
   box.exec();

   // --- DONE ---
PIX_EXIT:
   if (reg) {
      delete reg;
      reg = NULL;
   }
   return;
}
