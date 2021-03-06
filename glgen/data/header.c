/*
 * GLCaml - Objective Caml interface for OpenGL 1.1, 1.2, 1.3, 1.4, 1.5, 2.0 and 2.1
 * plus extensions:
 *
 * Copyright (C) 2007, 2008 Elliott OTI
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice, this list of conditions
 *    and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - The name Elliott Oti may not be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/bigarray.h>

#if defined(USE_GLEW) && defined(USE_DYNAMIC_EXT)
#error "bad option"
#endif
#if defined(USE_DYNAMIC) && !defined(USE_DYNAMIC_EXT)
#error "bad option"
#endif

#if defined(USE_GLEW)
#include <GL/glew.h>
#elif !defined(USE_DYNAMIC)
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#if !defined(USE_DYNAMIC_EXT)
#ifdef __APPLE__
#include <OpenGL/glext.h>
#else
#include <GL/glext.h>
#endif
#endif
#endif

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
#if !defined(__gl_h_) && !defined(__GLEW_H__)
typedef char GLbyte;
#endif
typedef short GLshort;
typedef int GLint;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef char GLchar;
#if !defined(__gl_h_)
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
#endif
typedef const unsigned char* GLstring;

#if defined(__GLEW_H__)
#define DECLARE_FUNCTION(func, args, ret)
#define LOAD_FUNCTION(func)
#define CALL_FUNCTION(func) func
#define DECLARE_FUNCTION_EXT(func, args, ret)
#define LOAD_FUNCTION_EXT(func)
#define CALL_FUNCTION_EXT(func) func
#else

#if defined(USE_DYNAMIC_EXT)

#ifdef _WIN32
#include <windows.h>

static HMODULE lib=NULL;

static void init_lib()
{
        if(lib)return;
        lib = LoadLibrary("opengl32.dll");
        if(lib == NULL) failwith("error loading opengl32.dll");
}

static void *get_proc_address(char *fname)
{
        return GetProcAddress(lib, fname);
}

#endif

#ifdef __unix__
#ifndef APIENTRY
#define APIENTRY
#endif
#include <dlfcn.h>
#include <stdio.h>

static void* lib=NULL;

static void init_lib()
{
        if(lib)return;
        lib = dlopen("libGL.so.1",RTLD_LAZY);
        if(lib == NULL) failwith("error loading libGL.so.1");
}

static void *get_proc_address(char *fname)
{
        return dlsym(lib, fname);
}

#endif

#if defined(__APPLE__) && defined(__GNUC__)
#ifndef APIENTRY
#define APIENTRY
#endif
#include <dlfcn.h>
#include <stdio.h>

static void* lib=NULL;

static void init_lib()
{
        if(lib)return;
        lib = dlopen("libGL.dylib",RTLD_LAZY);
        if(lib == NULL) lib = dlopen("/System/Library/Frameworks/OpenGL.framework/Libraries/libGL.dylib", RTLD_LAZY);
        if(lib == NULL) failwith("error loading libGL.dylib");
}

static void *get_proc_address(char *fname)
{
        return dlsym(lib, fname);
}
#endif

#define DECLARE_FUNCTION_EXT(func, args, ret)                           \
typedef ret APIENTRY (*pstub_##func)args;                               \
static pstub_##func stub_##func = NULL;                                 \
static int loaded_##func = 0;

#define LOAD_FUNCTION_EXT(func)                                         \
        if(!loaded_##func)                                              \
        {                                                               \
                init_lib ();                                            \
                stub_##func = (pstub_##func)get_proc_address(#func);    \
                if(stub_##func)                                         \
                {                                                       \
                        loaded_##func = 1;                              \
                }                                                       \
                else                                                    \
                {                                                       \
                        char fn[256], buf[300];                         \
                        strncpy(fn, #func, 255);                        \
                        sprintf(buf, "Unable to load %s", fn);          \
                        caml_failwith(buf);                             \
                }                                                       \
        }

#define CALL_FUNCTION_EXT(func) (*stub_##func)

#else
#define DECLARE_FUNCTION_EXT(func, args, ret)
#define LOAD_FUNCTION_EXT(func)
#define CALL_FUNCTION_EXT(func) func
#endif

#if defined(USE_DYNAMIC)
#define DECLARE_FUNCTION DECLARE_FUNCTION_EXT
#define LOAD_FUNCTION LOAD_FUNCTION_EXT
#define CALL_FUNCTION CALL_FUNCTION_EXT
#else
#define DECLARE_FUNCTION(func, args, ret)
#define LOAD_FUNCTION(func)
#define CALL_FUNCTION(func) func
#endif

#endif

value unsafe_coercion(value v)
{
        CAMLparam1(v);
        CAMLreturn(v);
}

