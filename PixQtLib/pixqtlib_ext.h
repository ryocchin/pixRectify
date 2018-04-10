#pragma once

using namespace _pix_plot_qt_framework;

//
// *** Can't USE TCHAR Functions! ***
//

//
// --- Debugging, log, functions for developers ---
// --- pixqf_data_utility.cpp ---
//

PIXQTLIB_EXPORT double value_segment(double, double, double, double, double);
PIXQTLIB_EXPORT double value_segment(int, int, double, double, int);
PIXQTLIB_EXPORT double value_segment(int, int, int, int, int);
PIXQTLIB_EXPORT double value_segment(pixq_Dbl2D*, pixq_Dbl2D*, double, double, pixq_Dbl2D*);

PIXQTLIB_EXPORT double get_anglex_diff(double angle1, double angle2);
PIXQTLIB_EXPORT double GoodRadian_PC(double angle0);

PIXQTLIB_EXPORT void ClearStrings_PC(char *str, int len);
PIXQTLIB_EXPORT int delimitStr_PC(char *buff, char *str[], char dli, int iBuffSize);

PIXQTLIB_EXPORT void ChrTranslate_PC( char *str, char chr0, char chr1);
PIXQTLIB_EXPORT void ChrTranslate_PC( QString *str, QChar chr0, QChar chr1 );
PIXQTLIB_EXPORT void ChrTranslate_PC( QString *str, QChar chr );

PIXQTLIB_EXPORT bool IsIntNumber_PC( const QString strValue );
PIXQTLIB_EXPORT bool IsPositiveIntNumber_PC( const QString strValue );

PIXQTLIB_EXPORT int getMaxValue_PC(int nSize, double *dArray, double *dMaxVal);

// Determines whether an expression is a valid real number type.
PIXQTLIB_EXPORT bool isFloatNumber_PC( char* );

// check if the number if power of two
PIXQTLIB_EXPORT bool IsPowerOfTwo_PC( int iValue, int *iPower );

PIXQTLIB_EXPORT void getFileName_PC( const QString szFile, QString *szName ); 

PIXQTLIB_EXPORT pixq_Dbl3D	PixVectorDiff3(pixq_Dbl3D*, pixq_Dbl3D*);
PIXQTLIB_EXPORT pixq_Dbl3D	PixOuterProduct3(pixq_Dbl3D*, pixq_Dbl3D*);
PIXQTLIB_EXPORT pixq_Dbl3D	PixTriNormalVector3(pixq_Dbl3D*, pixq_Dbl3D*, pixq_Dbl3D*);
PIXQTLIB_EXPORT pixq_Dbl3D	PixTriNormalVector3(pixq_Dbl3D*, pixq_Dbl3D*, pixq_Dbl3D*, double*);

PIXQTLIB_EXPORT void stringToSzBuffer_PC(const QString strBuff, char *szBuff, int nSize);
PIXQTLIB_EXPORT void stringToSzBuffer_PC(const QStringList aryBuff, int iLoc, char *szBuff,
   int nSize);

//
// --- fourier transform ---
// --- pixq_dft.cpp ---
//

// run 1D fft
PIXQTLIB_EXPORT bool Calc1DFftCalc_PI( float *fReal, 
                                        float *fImag,
                                        int nPower, 
                                        bool bInv );

PIXQTLIB_EXPORT bool Calc1DFftCalc_PI( vector<float> *fReal,
                                        vector<float> *fImag, 
                                        bool bInv );

// fft image of the first image in the second image
PIXQTLIB_EXPORT bool Get2DImageFft_PI( pixq_Matrix<float> *fInReal,
                                        pixq_Matrix<float> *fInImag, 
                                        bool bInverse );

PIXQTLIB_EXPORT bool DftAmplitudeImage_PC( pixq_Matrix<float> *fReal, 
                                            pixq_Matrix<float> *fImag,
                                            pixq_Matrix<float> *fDft ); 

PIXQTLIB_EXPORT bool DftAmplitudeImage_PC( vector<float> *fReal, 
                                            vector<float> *fImag,
                                            vector<float> *fDft ); 

//
// --- fiel handling utility ---
// --- pixqf_file_utility.cpp ---
//

PIXQTLIB_EXPORT bool fileExist_PC(const QString strFile);
PIXQTLIB_EXPORT bool createFolder_PC(const QString strPath);

PIXQTLIB_EXPORT QString getFileExtention_PI(const char *szFile);
PIXQTLIB_EXPORT QString getFileExtention_PI(const QString strFile);

PIXQTLIB_EXPORT QString GetTentativeVerXmlFile_PC( int iMode );
PIXQTLIB_EXPORT QString GetLatestVerXmlFile_PC( int iMode );
PIXQTLIB_EXPORT QString GetUpdateVerXmlFile_PC( int iMode );

PIXQTLIB_EXPORT QString GetWebsiteUrl_PC( void );
PIXQTLIB_EXPORT QString GetProjectUrl_PC( int iMode );
PIXQTLIB_EXPORT QString getProjectTopUrl_PC(int iMode);

PIXQTLIB_EXPORT QString getClassLabel_PC(const QString strClass,
   const QString strName,
   int iLanguage = QLocale::English );

//
// --- qt(zip) data compression ---
// --- pixqf_user_interface.cpp ---
//

PIXQTLIB_EXPORT bool FileCompress_PC( const QString strInFile, 
   const QString strCmpFile, 
   int iCompressionLevel ); 

PIXQTLIB_EXPORT bool FileUnCompress_PC( const QString strCmpFile,
   const QString strOutFile );


//
// --- custom user interface ---
// --- pixqf_user_interface.cpp ---
//

PIXQTLIB_EXPORT void showPixAbout_PC(const pixq_Version *pVer);
PIXQTLIB_EXPORT void showPixAbout_PC(const pixq_Version *pVer, const pixq_Properties *pEnv);

PIXQTLIB_EXPORT bool showPixProperty_PC(const QString strOrganisation,
   const QString strApplication, 
   pixq_Properties *pEnv,
   int iMode,
   short sPage );

PIXQTLIB_EXPORT bool showPixProperty_PC(const QString strOrganisation,
                                         const QString strApplication, 
                                         pixq_Properties *pEnv,
                                         int iMode );


PIXQTLIB_EXPORT void showWindowsVersion_PC(void);

PIXQTLIB_EXPORT void checkAccessDatabaseEngine_PC(void);

