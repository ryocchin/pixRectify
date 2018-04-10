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
QT += opengl
QT += help

configure += console

TARGET = PixImgLib
TEMPLATE = lib

DEFINES += PIXIMGLIB_EXPORTS
DEFINES += _USE_IMAGE_MAGICK

win32 {
CONFIG(debug, release|debug):DESTDIR = C:\QtiProjects\debug
CONFIG(release, release|debug):DESTDIR = C:\QtiProjects\release
}

SOURCES += \
    pix_DepthTexture.cpp \
    pix_DualTexture.cpp \
    pix_FlipPara.cpp \
    pix_FrameImageStat.cpp \
    pix_FringesTag.cpp \
    pix_FringeTag.cpp \
    pix_ImageAccess.cpp \
    pix_ImageDualSet.cpp \
    pix_ImageInfo.cpp \
    pix_ImageMatrix.cpp \
    pix_ImageOp.cpp \
    pix_ImageOpGray.cpp \
    pix_ImageOpProjective.cpp \
    pix_ImageSingleSet.cpp \
    pix_ImgSequence.cpp \
    pix_PanePara.cpp \
    pix_PaneTexture.cpp \
    pix_ScreenPara.cpp \
    pix_TextureBuffer.cpp \
    piximglib.cpp \
    pixqf_gl_utility.cpp \
    pixqf_image_gl.cpp \
    pixqf_image_interface.cpp \
    pixqf_image_match.cpp \
    pixqf_image_ut.cpp \
    pixqf_magick_utility.cpp \
    sequence_select_dialog.cpp

HEADERS += \
    pix_DepthTexture.h \
    pix_DualTexture.h \
    pix_FlipPara.h \
    pix_FrameImageStat.h \
    pix_FringesTag.h \
    pix_FringeTag.h \
    pix_ImageAccess.h \
    pix_ImageDualSet.h \
    pix_ImageInfo.h \
    pix_ImageMatrix.h \
    pix_ImageOp.h \
    pix_ImageOpGray.h \
    pix_ImageOpProjective.h \
    pix_ImageSingleSet.h \
    pix_ImgSequence.h \
    pix_PanePara.h \
    pix_PaneTexture.h \
    pix_ScreenPara.h \
    pix_TextureBuffer.h \
    piximg_common.h \
    piximglib.h \
    piximglib_def.h \
    piximglib_ext.h \
    piximglib_global.h \
    sequence_select_dialog.h

FORMS += \
    sequence_select_dialog.ui

RESOURCES += \
    PixImgLib.qrc

OTHER_FILES += \
    Files/msg_imglib.xml

INCLUDEPATH += .

#
# OpenGL
#
LIBS += -lopengl32

#
# PixQtLib
#
INCLUDEPATH += ../PixQtLib
LIBS += -L$$DESTDIR
LIBS += PixQtLib.lib

#
# ImageMagick
#
INCLUDEPATH += $$(IMAGEMAGICKDIR)/ImageMagick
INCLUDEPATH += $$(IMAGEMAGICKDIR)/ImageMagick/Magick++/lib
LIBS += -L$$(IMAGEMAGICKDIR)\VisualMagick\lib


message("---------------------------------------------")
message("IMAGEMAGICKDIR=" $$(IMAGEMAGICKDIR))
message("DESTDIR=" $$DESTDIR)
message("INCLUDEPATH=" $$INCLUDEPATH)
message("LIBS=" $$LIBS)
