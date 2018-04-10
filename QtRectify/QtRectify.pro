#-------------------------------------------------
#
# Project created by QtCreator 2011-01-17T12:02:16 
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

CONFIG += app
CONFIG += console
TARGET = QtRectify
TEMPLATE = app

win32:DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _ITF_LIB_QT

win32 {
CONFIG(debug, release|debug):DESTDIR = C:\QtiProjects\debug
CONFIG(release, release|debug):DESTDIR = C:\QtiProjects\release
}

message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(Header : $$[QT_INSTALL_HEADERS])
message(Libraries: $$[QT_INSTALL_LIBS])
message(Binary (executables): $$[QT_INSTALL_BINS])
message(Plugins: $$[QT_INSTALL_PLUGINS])
message(Data files: $$[QT_INSTALL_DATA])

SOURCES += \
    image_splitter.cpp \
    rectify_dock.cpp \
    rectify_main.cpp \
    rectify_pane.cpp \
    rectify_pane_gl.cpp \
    rectify_pane_ut.cpp \
    rectify_table.cpp \
    rectify_version.cpp \
    rectify_window.cpp \
    rectify_window_action.cpp \
    rectify_window_data.cpp \
    rectify_window_tex.cpp \
    rectify_window_ut.cpp \
    rectify_window_rectify.cpp \
    rectify_window_pyramid.cpp \
    rectify_window_feature.cpp \
    rectify_window_match.cpp \
    rectify_pane_tags.cpp \
    rectify_progress_dialog.cpp \
    MatchTemplate_Demo.cpp \
    rectify_compute.cpp \
    rectify_search_thread.cpp \
    rectify_window_anaglyph.cpp \
    rectify_window_thread.cpp \
    rectify_window_label.cpp

HEADERS += \
    image_splitter.h \
    rectify_common.h \
    rectify_cv_common.h \
    rectify_dock.h \
    rectify_pane.h \
    rectify_panes.h \
    rectify_progress_dialog.h \
    rectify_search_thread.h \
    rectify_table.h \
    rectify_window.h

FORMS += \
    rectify_window.ui \
    rectify_progress_dialog.ui

RESOURCES += \
    QtRectify.qrc

OTHER_FILES +=

INCLUDEPATH += .

LIBS += -lopengl32

#
# for PixQtLib
#
INCLUDEPATH += ../PixQtLib
LIBS += -L$$DESTDIR
LIBS += PixQtLib.lib

#
# for PixImgLib
#
INCLUDEPATH += ../PixImgLib
LIBS += -L$$DESTDIR
LIBS += PixImgLib.lib

#
# ImageMagick
#
INCLUDEPATH += $$(IMAGEMAGICKDIR)/ImageMagick
INCLUDEPATH += $$(IMAGEMAGICKDIR)/ImageMagick/Magick++/lib
LIBS += -L$$(IMAGEMAGICKDIR)\VisualMagick\lib

#
# OpenCV
#
INCLUDEPATH += $$quote($(OPENCVDIR)\include)
LIBS += -L$$(OPENCVDIR)\x64\vc12\lib

#
#
# On Windows, use backslashes as directory separators
#
copypwd = $$PWD
copydest = $$DESTDIR
copyplat = $$copydest\platforms
equals(QMAKE_HOST.os, Windows) {
    copypwd ~= s,/,\\,g
    copydest ~= s,/,\\,g
    copyplat ~= s,/,\\,g
}

#
# copy required dlls - ImageMagick
#
CONFIG(debug, debug|release) {
QMAKE_POST_LINK += \
    xcopy /d /y $$quote($(IMAGEMAGICKDIR)\VisualMagick\bin\CORE_DB_*.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(IMAGEMAGICKDIR)\VisualMagick\bin\IM_MOD_DB_*.dll) $$quote($$copydest) &&\
} else {
QMAKE_POST_LINK += \
    xcopy /d /y $$quote($(IMAGEMAGICKDIR)\VisualMagick\bin\CORE_RL_*.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(IMAGEMAGICKDIR)\VisualMagick\bin\IM_MOD_RL_*.dll) $$quote($$copydest) &&\
}

QMAKE_POST_LINK += \
    xcopy /d /y $$quote($(IMAGEMAGICKDIR)\VisualMagick\bin\*.xml) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(IMAGEMAGICKDIR)\VisualMagick\installer\txt\license.rtf) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(IMAGEMAGICKDIR)\VisualMagick\installer\txt\license.sxw) $$quote($$copydest) &&\
    echo ImageMagick dlls COPIED... &&\

#
# copy required dlls - OpenCV
#
CONFIG(debug, debug|release) {
QMAKE_POST_LINK += \
    echo OpenCV dlls COPIED... &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_calib3d2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_contrib2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_core2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_features2d2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_flann2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_highgui2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_imgproc2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_legacy2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_ml2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_objdetect2411d.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_video2411d.dll) $$quote($$copydest) &&\
} else {
QMAKE_POST_LINK += \
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_calib3d2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_contrib2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_core2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_features2d2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_flann2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_highgui2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_imgproc2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_legacy2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_ml2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_objdetect2411.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(OPENCVDIR)\x64\vc12\bin\opencv_video2411.dll) $$quote($$copydest) &&\
}

#
# create necessary directories and copy required dlls - Qt
#

chk_copyplat = $$clean_path($$copyplat)

exists($$chk_copyplat/*) {
QMAKE_POST_LINK += \
    echo deleting $$chk_copyplat &&\
    rmdir /s /q $$quote($$copydest\platforms) &&\
    echo deleted $$chk_copyplat &&\
}

QMAKE_POST_LINK += \
    echo Creating $$quote($$copydest\platforms)... &&\
    mkdir $$quote($$copydest\platforms) &&\


CONFIG(debug, debug|release) {
QMAKE_POST_LINK += \
    echo Copying dlls debug... &&\
    xcopy /d /y $$quote($(QTDIR)\plugins\platforms\qwindowsd.dll) $$quote($$copydest\platforms) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Cored.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Guid.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5OpenGLd.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Widgetsd.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Helpd.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Networkd.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Sqld.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5CLucened.dll) $$quote($$copydest) &&\
} else {
QMAKE_POST_LINK += \
    echo Copying dlls release... &&\
    xcopy /d /y $$quote($(QTDIR)\plugins\platforms\qwindows.dll) $$quote($$copydest\platforms) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Core.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Gui.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5OpenGL.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Widgets.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Help.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Network.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5Sql.dll) $$quote($$copydest) &&\
    xcopy /d /y $$quote($(QTDIR)\bin\Qt5CLucene.dll) $$quote($$copydest) &&\
}


QMAKE_POST_LINK += \
    echo Qt files COPIED...


























































