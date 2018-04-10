#pragma once

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

//----------------------------------------------------------------------
//
// --- opengl utlity functions ---
// --- pixqf_gl_utility.cpp ---
//

// check if the version of the opengl is higher than 2.0 
PIXIMGLIB_EXPORT bool OpenGlHigherThanTwo_PI( void );

//----------------------------------------------------------------------
//
// --- texture from/to matrix ---
// --- pixqf_imageio_gl.cpp ---
//

PIXIMGLIB_EXPORT bool createTexture_PI( pixq_Matrix<unsigned short> *pRed, 
                                        pixq_Matrix<unsigned short> *pGrn, 
                                        pixq_Matrix<unsigned short> *pBlu, 
                                        pixq_Properties *pEnv );

PIXIMGLIB_EXPORT bool createFreeTexture_PI(pixq_Matrix<unsigned short> *pRed,
                                            pixq_Matrix<unsigned short> *pGrn,
                                            pixq_Matrix<unsigned short> *pBlu,
                                            short sDisplayColor = PixImageDisplayColorRgb );

PIXIMGLIB_EXPORT bool createFreeTexture_PI(pixq_Matrix<unsigned short> *pRed,
                                            pixq_Matrix<unsigned short> *pGrn,
                                            pixq_Matrix<unsigned short> *pBlu,
                                            pixq_TextureBuffer *pWorkBuffer,
                                            short sDisplayColor = PixImageDisplayColorRgb );

//----------------------------------------------------------------------
//
// --- custom user interface ---
// --- pixqf_image_interface.cpp ---
//

PIXIMGLIB_EXPORT bool selectSingleSequence_PI( const QString strOrganisation, 
                               const QString strApplication, 
                                pixq_Properties *pEnv,
                               pixq_ImgSequence *pSeq );

PIXIMGLIB_EXPORT bool selectSingleSequence_PI(const QString strOrganisation,
                               const QString strApplication, 
                                pixq_Properties *pEnv,
                               pixq_ImageSingleSet *pData );

PIXIMGLIB_EXPORT bool selectDualSequences_PI( const QString strOrganisation, 
                               const QString strApplication, 
                                pixq_Properties *pEnv,
                               pixq_ImgSequence *pSeq0,
                               pixq_ImgSequence *pSeq1 );

//----------------------------------------------------------------------
//
// --- Image Matching ---
// --- pixqf_image_match.cpp ---
//

PIXIMGLIB_EXPORT bool getImageCorrelation_PI(const pixq_Matrix<double> *pImg0,
                                              const pixq_Matrix<double> *pImg1, 
                                              const bool bUseZero, 
                                              double *dCorr );

PIXIMGLIB_EXPORT bool getImageCorrelation_PI(const vector<unsigned char> *vcValue0,
                                              const vector<unsigned char> *vcValue1, 
                                              const bool bUseZero,
                                              double *dCorr );

PIXIMGLIB_EXPORT bool getImageCorrelation_PI(const vector<unsigned short> *vsValue0,
                                              const vector<unsigned short> *vsValue1, 
                                              const bool bUseZero, 
                                              double *dCorr );

PIXIMGLIB_EXPORT bool getImageCorrelation_PI( const vector<unsigned short> *vsValue0,
                                              const vector<unsigned short> *vsValue1, 
                                              const vector<bool> *vsValid0, 
                                              const vector<bool> *vsValid1, 
                                              const bool bUseZero, 
                                              double *dCorr );

PIXIMGLIB_EXPORT bool getImageCorrelation_PI(const vector<double> *vdValue0,
                                              const vector<double> *vdValue1,
                                              const bool bUseZero, 
                                              double *dCorr );

PIXIMGLIB_EXPORT bool getImageCorrelation_PI(const double *dRefBuffer,
                                              const double *dCheckBuffer,
                                              const int nBufferSize,
                                              const bool bUseZero,
                                              double *dCorr );

PIXIMGLIB_EXPORT bool getRegressionPara_PI( const vector<unsigned short> *vusX,
                                           const vector<unsigned short> *vusY, 
                                           double *dScale,
                                           double *dOffset );

PIXIMGLIB_EXPORT bool getRegressionPara_PI(const vector<double> *vdX,
                                           const vector<double> *vdY, 
                                           double *dScale,
                                           double *dOffset );

PIXIMGLIB_EXPORT bool getRegressionPara_PI(const double *dX,
                                           const double *dY,
                                           const int nSize,
                                           double *dScale,
                                           double *dOffset );

//----------------------------------------------------------------------
//
// --- common image handling utility ---
// --- pixqf_image_ut.cpp ---

// decide image file format from file extension 

PIXIMGLIB_EXPORT float grayFromRgb_PI(float fRed, float fGrn, float fBlu);

PIXIMGLIB_EXPORT unsigned short grayFromRgb_PI(unsigned short usRed,
   unsigned short usGrn, unsigned short usBlu);

//
// --- imagemagick ---
// --- pixqf_magick_utility.cpp ---
//

// make filter string for CFileDialog to get supported image files

PIXIMGLIB_EXPORT void imageMagickFileFilter_PI(bool bRead, QStringList &strFilter);
PIXIMGLIB_EXPORT void imageMagickFileFilter_PI(bool bRead, QString &strFilter);

PIXIMGLIB_EXPORT void listSupportedFormat_PI( QStringList *strList );
PIXIMGLIB_EXPORT void listSupportedFormat_PI(QStringList *strFormats,
                                             QStringList *strDesc,
                                             QList<bool> *bReadble,
                                             QList<bool> *bWritable,
                                             QList<bool> *bMultiFrame );

PIXIMGLIB_EXPORT void getMagickVersion_PI(QString &strVersion);

PIXIMGLIB_EXPORT bool magickLoadImage_PI(const QString strFile,
                            pixq_ImageInfo *info, 
                            pixq_ImageMatrix *usRed, 
                            pixq_ImageMatrix *usGrn, 
                            pixq_ImageMatrix *usBlu );

PIXIMGLIB_EXPORT bool magickLoadImage_PI(const QString strFile,
                            pixq_ImageMatrix *usRed, 
                            pixq_ImageMatrix *usGrn, 
                            pixq_ImageMatrix *usBlu );

PIXIMGLIB_EXPORT bool magickSaveImage_PI(const QString strFile,
   const pixq_ImageMatrix *usRed,
   const pixq_ImageMatrix *usGrn,
   const pixq_ImageMatrix *usBlu);

PIXIMGLIB_EXPORT bool magickSaveImage_PI(const QString strFile,
   const pixq_Matrix<double> *dRed,
   const pixq_Matrix<double> *dGrn,
   const pixq_Matrix<double> *dBlu);

PIXIMGLIB_EXPORT bool getImageProps_PI(  Image &img,
                                       const QString strFile, 
                                       pixq_ImageInfo *info );

PIXIMGLIB_EXPORT bool getImageProps_PI( const QString strFile, 
                            QStringList *strPropNames, 
                            QStringList *strProps );

PIXIMGLIB_EXPORT bool getHeaderInfo_PI(const QString strFile,
                                       int &nImgWidth,
                                       int &nImgHeight, 
                                       int &nBitDepth );

PIXIMGLIB_EXPORT bool checkImageFormat_PI(bool bRead, const QString strExtention);

PIXIMGLIB_EXPORT void imageMagickDirFilter_PI( bool bRead, QStringList &strFilter );	

