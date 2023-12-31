#ifndef __OPENGLLIBINCLUDE_H__
#define __OPENGLLIBINCLUDE_H__


#pragma once




// ---------------------------------------------------------------------------------------------------------------------
// SDL and OPENGL
// -------------------------------------------------------------------------------------------------------------------
#ifdef __linux__
    //#include <GL/gl.h>
    //#include <GL/glu.h>

#define GLEW_STATIC
#include <GL/glew.h>

#else
    //#include <OpenGL/gl.h>
    //#include <OpenGL/glu.h>

#ifdef GLEW_STATIC
#  define GLEWAPI extern
#else
#  ifdef GLEW_BUILD
#    define GLEWAPI extern __declspec(dllexport)
#  else
#    define GLEWAPI extern __declspec(dllimport)
#  endif
#endif
    //#define GLEW_STATIC // Depending on how you built/installed GLEW, you may want to change this
//#include <GL/glew.h>

#endif



#ifdef _WIN32



#ifndef NOMINMAX
#define NOMINMAX // prevent windows redefining min/max
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>


#include "GL/glew.h"
#include "GLFW/glfw3.h"

//#define GLFW_INCLUDE_NONE
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//




# elif __APPLE__
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#else
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif


#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>




//#ifdef WIN32
//
//#ifdef _WIN32
//#ifndef NOMINMAX
//#define NOMINMAX // prevent windows redefining min/max
//#endif
//
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif
//
////#pragma comment( lib, "version.lib" )
//
//#include <windows.h>
//#endif //_WIN32
//
//
//#endif



#endif // __OPENGLLIBINCLUDE_H__