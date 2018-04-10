#-------------------------------------------------
#
# Project created by QtCreator 2011-01-27T16:30:34
#
#-------------------------------------------------

QT += core
QT += gui
QT += widgets
QT += network
QT += sql
QT += help

configure += console

TARGET = PixQtLib
TEMPLATE = lib

DEFINES += PIXQTLIB_EXPORTS

win32 {
CONFIG(debug, release|debug):DESTDIR = C:\QtiProjects\debug
CONFIG(release, release|debug):DESTDIR = C:\QtiProjects\release
}

SOURCES +=  \
    pixq_CooMatrix.cpp \
    pixq_Dbl2D.cpp \
    pixq_Dbl3D.cpp \
    pixq_helpBrowser.cpp \
    pixq_helpViewer.cpp \
    pixq_Int2D.cpp \
    pixq_PntMatrix.cpp \
    pixq_version_update.cpp \
    pixq_Version.cpp \
    pixq_Properties.cpp \
    pixq_Matrix.cpp \
    pixq_ImagePix.cpp \
    pixq_EnvItem.cpp \
    pixq_about_dialog.cpp \
    pixq_StopWatch.cpp \
    pixq_image_opt_dialog.cpp \
    pixq_page_image_options.cpp \
    pixq_page_options.cpp \
    pixqfe_compress.cpp \
    pixqfe_data_utility.cpp \
    pixqfe_dft.cpp \
    pixqfe_file_utility.cpp \
    pixqfe_user_interface.cpp \
    pixqtlib.cpp \
    props_page_system.cpp \
    props_page_image.cpp \
    props_page_compare.cpp \
    props_page_cv_rectify.cpp \
    props_page_pnt_rectify.cpp \
    website_label_widget.cpp

HEADERS += \
    ColorMapsDef.h \
    pixq_Version.h \
    pixq_Properties.h \
    pixq_MatrixUt.h \
    pixq_MatrixStat.h \
    pixq_MatrixLa.h \
    pixq_MatrixData.h \
    pixq_Matrix.h \
    pixq_ImagePix.h \
    pixq_EnvItem.h \
    pixq_about_dialog.h \
    pixq_CooMatrix.h \
    pixq_Dbl2D.h \
    pixq_Dbl3D.h \
    pixq_helpBrowser.h \
    pixq_helpViewer.h \
    pixq_Int2D.h \
    pixq_PntMatrix.h \
    pixq_version_update.h \
    pixq_StopWatch.h \
    pixqt_common.h \
    pixqtlib.h \
    pixqtlib_def.h \
    pixqtlib_ext.h \
    pixqtlib_global.h \
    pixq_image_opt_dialog.h \
    pixq_page_image_options.h \
    pixq_page_options.h \
    props_page_system.h \
    props_page_image.h \
    props_page_compare.h \
    props_page_cv_rectify.h \
    props_page_pnt_rectify.h \
    website_label_widget.h

FORMS += \
    props_page_system.ui \
    props_page_image.ui \
    pixq_about_dialog.ui \
    props_page_compare.ui \
    props_page_cv_rectify.ui \
    props_page_pnt_rectify.ui

RESOURCES += \
    PixQtLib.qrc

INCLUDEPATH += .
















