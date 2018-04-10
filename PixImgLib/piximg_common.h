#pragma once

#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QApplication>
//#pragma warning( disable:4005 )
#include <QtOpenGL>
//#pragma warning( disable:4005 )
#include <QGLWidget>
#include <QMainWindow>

// 
// C:\ProgramData\NVIDIA Corporation\NVIDIA GPU Computing SDK 4.0\C\common\inc\GL/glext.h(393) : warning C4005: 'GL_BLEND_EQUATION_RGB' : macro redefinition
// c:\qt\4.8.0\include\qtopengl\../../src/opengl/qglfunctions.h(1445) : see previous definition of 'GL_BLEND_EQUATION_RGB'
//
#ifdef _WIN32
//#pragma warning( disable:4005 )
#endif // _WIN32

//
// 4.8.0
// qglfunctions.h is not compatible with GLEW, GLEW defines will be undefined
// To use GLEW with Qt, do not include <QtOpenGL> or <QGLFunctions> after glew.h
//
//#include <GL/glext.h>

//
// use image magick
//
#include <Magick++.h>
using namespace Magick;

//#include <MagickCore/MagickCore.h>
//using namespace MagickCore;

#pragma comment (lib, "PixQtLib.lib") 

#ifdef _DEBUG
#pragma comment (lib, "CORE_DB_magick_.lib") 
#pragma comment (lib, "CORE_DB_Magick++_.lib") 
#else // _DEBUG
#pragma comment (lib, "CORE_RL_magick_.lib") 
#pragma comment (lib, "CORE_RL_Magick++_.lib") 
#endif // _DEBUG
