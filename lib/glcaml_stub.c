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

#if defined(USE_GLEW)
#include <GL/glew.h>
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
typedef char* GLstring;

#if defined(__GLEW_H__)
#define DECLARE_FUNCTION(func, args, ret)
#define LOAD_FUNCTION(func)
#define CALL_FUNCTION(func) func
#else

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

#define DECLARE_FUNCTION(func, args, ret)                               \
typedef ret APIENTRY (*pstub_##func)args;                               \
static pstub_##func stub_##func = NULL;                                 \
static int loaded_##func = 0;

#define LOAD_FUNCTION(func)                                             \
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

#define CALL_FUNCTION(func) (*stub_##func)

#endif

value unsafe_coercion(value v)
{
        CAMLparam1(v);
        CAMLreturn(v);
}

DECLARE_FUNCTION(glAccum,(GLenum, GLfloat),void);
value glstub_glAccum(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glAccum);
	CALL_FUNCTION(glAccum)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glActiveStencilFaceEXT,(GLenum),void);
value glstub_glActiveStencilFaceEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glActiveStencilFaceEXT);
	CALL_FUNCTION(glActiveStencilFaceEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glActiveTexture,(GLenum),void);
value glstub_glActiveTexture(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glActiveTexture);
	CALL_FUNCTION(glActiveTexture)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glActiveTextureARB,(GLenum),void);
value glstub_glActiveTextureARB(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glActiveTextureARB);
	CALL_FUNCTION(glActiveTextureARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glActiveVaryingNV,(GLuint, GLchar*),void);
value glstub_glActiveVaryingNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	LOAD_FUNCTION(glActiveVaryingNV);
	CALL_FUNCTION(glActiveVaryingNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glAddSwapHintRectWIN,(GLint, GLint, GLsizei, GLsizei),void);
value glstub_glAddSwapHintRectWIN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glAddSwapHintRectWIN);
	CALL_FUNCTION(glAddSwapHintRectWIN)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glAlphaFragmentOp1ATI,(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glAlphaFragmentOp1ATI(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	LOAD_FUNCTION(glAlphaFragmentOp1ATI);
	CALL_FUNCTION(glAlphaFragmentOp1ATI)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glAlphaFragmentOp1ATI_byte(value * argv, int n)
{
	return glstub_glAlphaFragmentOp1ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glAlphaFragmentOp2ATI,(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glAlphaFragmentOp2ATI(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	GLuint lv6 = Int_val(v6);
	GLuint lv7 = Int_val(v7);
	GLuint lv8 = Int_val(v8);
	LOAD_FUNCTION(glAlphaFragmentOp2ATI);
	CALL_FUNCTION(glAlphaFragmentOp2ATI)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glAlphaFragmentOp2ATI_byte(value * argv, int n)
{
	return glstub_glAlphaFragmentOp2ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glAlphaFragmentOp3ATI,(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glAlphaFragmentOp3ATI(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10, value v11)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam2(v10, v11);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	GLuint lv6 = Int_val(v6);
	GLuint lv7 = Int_val(v7);
	GLuint lv8 = Int_val(v8);
	GLuint lv9 = Int_val(v9);
	GLuint lv10 = Int_val(v10);
	GLuint lv11 = Int_val(v11);
	LOAD_FUNCTION(glAlphaFragmentOp3ATI);
	CALL_FUNCTION(glAlphaFragmentOp3ATI)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11);
	CAMLreturn(Val_unit);
}

value glstub_glAlphaFragmentOp3ATI_byte(value * argv, int n)
{
	return glstub_glAlphaFragmentOp3ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11]);
}

DECLARE_FUNCTION(glAlphaFunc,(GLenum, GLclampf),void);
value glstub_glAlphaFunc(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLclampf lv1 = Double_val(v1);
	LOAD_FUNCTION(glAlphaFunc);
	CALL_FUNCTION(glAlphaFunc)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glApplyTextureEXT,(GLenum),void);
value glstub_glApplyTextureEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glApplyTextureEXT);
	CALL_FUNCTION(glApplyTextureEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glAreProgramsResidentNV,(GLsizei, GLuint*, GLboolean*),GLboolean);
value glstub_glAreProgramsResidentNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	GLboolean ret;
	LOAD_FUNCTION(glAreProgramsResidentNV);
	ret = CALL_FUNCTION(glAreProgramsResidentNV)(lv0, lv1, lv2);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glAreTexturesResident,(GLsizei, GLuint*, GLboolean*),GLboolean);
value glstub_glAreTexturesResident(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	GLboolean ret;
	LOAD_FUNCTION(glAreTexturesResident);
	ret = CALL_FUNCTION(glAreTexturesResident)(lv0, lv1, lv2);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glAreTexturesResidentEXT,(GLsizei, GLuint*, GLboolean*),GLboolean);
value glstub_glAreTexturesResidentEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	GLboolean ret;
	LOAD_FUNCTION(glAreTexturesResidentEXT);
	ret = CALL_FUNCTION(glAreTexturesResidentEXT)(lv0, lv1, lv2);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glArrayElement,(GLint),void);
value glstub_glArrayElement(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glArrayElement);
	CALL_FUNCTION(glArrayElement)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glArrayElementEXT,(GLint),void);
value glstub_glArrayElementEXT(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glArrayElementEXT);
	CALL_FUNCTION(glArrayElementEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glArrayObjectATI,(GLenum, GLint, GLenum, GLsizei, GLuint, GLuint),void);
value glstub_glArrayObjectATI(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	LOAD_FUNCTION(glArrayObjectATI);
	CALL_FUNCTION(glArrayObjectATI)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glArrayObjectATI_byte(value * argv, int n)
{
	return glstub_glArrayObjectATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glAsyncMarkerSGIX,(GLuint),void);
value glstub_glAsyncMarkerSGIX(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glAsyncMarkerSGIX);
	CALL_FUNCTION(glAsyncMarkerSGIX)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glAttachObjectARB,(GLuint, GLuint),void);
value glstub_glAttachObjectARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glAttachObjectARB);
	CALL_FUNCTION(glAttachObjectARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glAttachShader,(GLuint, GLuint),void);
value glstub_glAttachShader(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glAttachShader);
	CALL_FUNCTION(glAttachShader)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBegin,(GLenum),void);
value glstub_glBegin(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glBegin);
	CALL_FUNCTION(glBegin)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBeginFragmentShaderATI,(void),void);
value glstub_glBeginFragmentShaderATI(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glBeginFragmentShaderATI);
	CALL_FUNCTION(glBeginFragmentShaderATI)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBeginOcclusionQueryNV,(GLuint),void);
value glstub_glBeginOcclusionQueryNV(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glBeginOcclusionQueryNV);
	CALL_FUNCTION(glBeginOcclusionQueryNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBeginQuery,(GLenum, GLuint),void);
value glstub_glBeginQuery(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBeginQuery);
	CALL_FUNCTION(glBeginQuery)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBeginQueryARB,(GLenum, GLuint),void);
value glstub_glBeginQueryARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBeginQueryARB);
	CALL_FUNCTION(glBeginQueryARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBeginSceneEXT,(void),void);
value glstub_glBeginSceneEXT(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glBeginSceneEXT);
	CALL_FUNCTION(glBeginSceneEXT)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBeginTransformFeedbackNV,(GLenum),void);
value glstub_glBeginTransformFeedbackNV(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glBeginTransformFeedbackNV);
	CALL_FUNCTION(glBeginTransformFeedbackNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBeginVertexShaderEXT,(void),void);
value glstub_glBeginVertexShaderEXT(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glBeginVertexShaderEXT);
	CALL_FUNCTION(glBeginVertexShaderEXT)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindAttribLocation,(GLuint, GLuint, GLchar*),void);
value glstub_glBindAttribLocation(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLchar* lv2 = String_val(v2);
	LOAD_FUNCTION(glBindAttribLocation);
	CALL_FUNCTION(glBindAttribLocation)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindAttribLocationARB,(GLuint, GLuint, GLchar*),void);
value glstub_glBindAttribLocationARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLchar* lv2 = String_val(v2);
	LOAD_FUNCTION(glBindAttribLocationARB);
	CALL_FUNCTION(glBindAttribLocationARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindBuffer,(GLenum, GLuint),void);
value glstub_glBindBuffer(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBindBuffer);
	CALL_FUNCTION(glBindBuffer)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindBufferARB,(GLenum, GLuint),void);
value glstub_glBindBufferARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBindBufferARB);
	CALL_FUNCTION(glBindBufferARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindBufferBaseNV,(GLenum, GLuint, GLuint),void);
value glstub_glBindBufferBaseNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glBindBufferBaseNV);
	CALL_FUNCTION(glBindBufferBaseNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindBufferOffsetNV,(GLenum, GLuint, GLuint, GLintptr),void);
value glstub_glBindBufferOffsetNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLintptr lv3 = Int_val(v3);
	LOAD_FUNCTION(glBindBufferOffsetNV);
	CALL_FUNCTION(glBindBufferOffsetNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindBufferRangeNV,(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr),void);
value glstub_glBindBufferRangeNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLintptr lv3 = Int_val(v3);
	GLsizeiptr lv4 = Int_val(v4);
	LOAD_FUNCTION(glBindBufferRangeNV);
	CALL_FUNCTION(glBindBufferRangeNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindFragDataLocationEXT,(GLuint, GLuint, GLchar*),void);
value glstub_glBindFragDataLocationEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLchar* lv2 = String_val(v2);
	LOAD_FUNCTION(glBindFragDataLocationEXT);
	CALL_FUNCTION(glBindFragDataLocationEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindFragmentShaderATI,(GLuint),void);
value glstub_glBindFragmentShaderATI(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glBindFragmentShaderATI);
	CALL_FUNCTION(glBindFragmentShaderATI)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindFramebufferEXT,(GLenum, GLuint),void);
value glstub_glBindFramebufferEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBindFramebufferEXT);
	CALL_FUNCTION(glBindFramebufferEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindLightParameterEXT,(GLenum, GLenum),GLuint);
value glstub_glBindLightParameterEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint ret;
	LOAD_FUNCTION(glBindLightParameterEXT);
	ret = CALL_FUNCTION(glBindLightParameterEXT)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glBindMaterialParameterEXT,(GLenum, GLenum),GLuint);
value glstub_glBindMaterialParameterEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint ret;
	LOAD_FUNCTION(glBindMaterialParameterEXT);
	ret = CALL_FUNCTION(glBindMaterialParameterEXT)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glBindParameterEXT,(GLenum),GLuint);
value glstub_glBindParameterEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint ret;
	LOAD_FUNCTION(glBindParameterEXT);
	ret = CALL_FUNCTION(glBindParameterEXT)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glBindProgramARB,(GLenum, GLuint),void);
value glstub_glBindProgramARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBindProgramARB);
	CALL_FUNCTION(glBindProgramARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindProgramNV,(GLenum, GLuint),void);
value glstub_glBindProgramNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBindProgramNV);
	CALL_FUNCTION(glBindProgramNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindRenderbufferEXT,(GLenum, GLuint),void);
value glstub_glBindRenderbufferEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBindRenderbufferEXT);
	CALL_FUNCTION(glBindRenderbufferEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindTexGenParameterEXT,(GLenum, GLenum, GLenum),GLuint);
value glstub_glBindTexGenParameterEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint ret;
	LOAD_FUNCTION(glBindTexGenParameterEXT);
	ret = CALL_FUNCTION(glBindTexGenParameterEXT)(lv0, lv1, lv2);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glBindTexture,(GLenum, GLuint),void);
value glstub_glBindTexture(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBindTexture);
	CALL_FUNCTION(glBindTexture)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindTextureEXT,(GLenum, GLuint),void);
value glstub_glBindTextureEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glBindTextureEXT);
	CALL_FUNCTION(glBindTextureEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindTextureUnitParameterEXT,(GLenum, GLenum),GLuint);
value glstub_glBindTextureUnitParameterEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint ret;
	LOAD_FUNCTION(glBindTextureUnitParameterEXT);
	ret = CALL_FUNCTION(glBindTextureUnitParameterEXT)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glBindVertexArray,(GLuint),void);
value glstub_glBindVertexArray(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glBindVertexArray);
	CALL_FUNCTION(glBindVertexArray)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindVertexArrayAPPLE,(GLuint),void);
value glstub_glBindVertexArrayAPPLE(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glBindVertexArrayAPPLE);
	CALL_FUNCTION(glBindVertexArrayAPPLE)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBindVertexShaderEXT,(GLuint),void);
value glstub_glBindVertexShaderEXT(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glBindVertexShaderEXT);
	CALL_FUNCTION(glBindVertexShaderEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBinormalPointerEXT,(GLenum, GLsizei, GLvoid*),void);
value glstub_glBinormalPointerEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glBinormalPointerEXT);
	CALL_FUNCTION(glBinormalPointerEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBitmap,(GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, GLubyte*),void);
value glstub_glBitmap(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLsizei lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLubyte* lv6 = Data_bigarray_val(v6);
	LOAD_FUNCTION(glBitmap);
	CALL_FUNCTION(glBitmap)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glBitmap_byte(value * argv, int n)
{
	return glstub_glBitmap(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glBlendColor,(GLclampf, GLclampf, GLclampf, GLclampf),void);
value glstub_glBlendColor(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLclampf lv0 = Double_val(v0);
	GLclampf lv1 = Double_val(v1);
	GLclampf lv2 = Double_val(v2);
	GLclampf lv3 = Double_val(v3);
	LOAD_FUNCTION(glBlendColor);
	CALL_FUNCTION(glBlendColor)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlendColorEXT,(GLclampf, GLclampf, GLclampf, GLclampf),void);
value glstub_glBlendColorEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLclampf lv0 = Double_val(v0);
	GLclampf lv1 = Double_val(v1);
	GLclampf lv2 = Double_val(v2);
	GLclampf lv3 = Double_val(v3);
	LOAD_FUNCTION(glBlendColorEXT);
	CALL_FUNCTION(glBlendColorEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlendEquation,(GLenum),void);
value glstub_glBlendEquation(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glBlendEquation);
	CALL_FUNCTION(glBlendEquation)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlendEquationEXT,(GLenum),void);
value glstub_glBlendEquationEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glBlendEquationEXT);
	CALL_FUNCTION(glBlendEquationEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlendEquationSeparate,(GLenum, GLenum),void);
value glstub_glBlendEquationSeparate(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glBlendEquationSeparate);
	CALL_FUNCTION(glBlendEquationSeparate)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlendEquationSeparateEXT,(GLenum, GLenum),void);
value glstub_glBlendEquationSeparateEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glBlendEquationSeparateEXT);
	CALL_FUNCTION(glBlendEquationSeparateEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlendFunc,(GLenum, GLenum),void);
value glstub_glBlendFunc(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glBlendFunc);
	CALL_FUNCTION(glBlendFunc)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlendFuncSeparate,(GLenum, GLenum, GLenum, GLenum),void);
value glstub_glBlendFuncSeparate(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glBlendFuncSeparate);
	CALL_FUNCTION(glBlendFuncSeparate)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlendFuncSeparateEXT,(GLenum, GLenum, GLenum, GLenum),void);
value glstub_glBlendFuncSeparateEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glBlendFuncSeparateEXT);
	CALL_FUNCTION(glBlendFuncSeparateEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBlitFramebufferEXT,(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum),void);
value glstub_glBlitFramebufferEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	GLint lv7 = Int_val(v7);
	GLbitfield lv8 = Int_val(v8);
	GLenum lv9 = Int_val(v9);
	LOAD_FUNCTION(glBlitFramebufferEXT);
	CALL_FUNCTION(glBlitFramebufferEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glBlitFramebufferEXT_byte(value * argv, int n)
{
	return glstub_glBlitFramebufferEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

DECLARE_FUNCTION(glBufferData,(GLenum, GLsizeiptr, GLvoid*, GLenum),void);
value glstub_glBufferData(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizeiptr lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glBufferData);
	CALL_FUNCTION(glBufferData)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBufferDataARB,(GLenum, GLsizeiptr, GLvoid*, GLenum),void);
value glstub_glBufferDataARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizeiptr lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glBufferDataARB);
	CALL_FUNCTION(glBufferDataARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBufferSubData,(GLenum, GLintptr, GLsizeiptr, GLvoid*),void);
value glstub_glBufferSubData(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLintptr lv1 = Int_val(v1);
	GLsizeiptr lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glBufferSubData);
	CALL_FUNCTION(glBufferSubData)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glBufferSubDataARB,(GLenum, GLintptr, GLsizeiptr, GLvoid*),void);
value glstub_glBufferSubDataARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLintptr lv1 = Int_val(v1);
	GLsizeiptr lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glBufferSubDataARB);
	CALL_FUNCTION(glBufferSubDataARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCallList,(GLuint),void);
value glstub_glCallList(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glCallList);
	CALL_FUNCTION(glCallList)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCallLists,(GLsizei, GLenum, GLvoid*),void);
value glstub_glCallLists(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glCallLists);
	CALL_FUNCTION(glCallLists)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCheckFramebufferStatusEXT,(GLenum),GLenum);
value glstub_glCheckFramebufferStatusEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum ret;
	LOAD_FUNCTION(glCheckFramebufferStatusEXT);
	ret = CALL_FUNCTION(glCheckFramebufferStatusEXT)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glClampColorARB,(GLenum, GLenum),void);
value glstub_glClampColorARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glClampColorARB);
	CALL_FUNCTION(glClampColorARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClear,(GLbitfield),void);
value glstub_glClear(value v0)
{
	CAMLparam1(v0);
	GLbitfield lv0 = Int_val(v0);
	LOAD_FUNCTION(glClear);
	CALL_FUNCTION(glClear)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearAccum,(GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glClearAccum(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glClearAccum);
	CALL_FUNCTION(glClearAccum)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearColor,(GLclampf, GLclampf, GLclampf, GLclampf),void);
value glstub_glClearColor(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLclampf lv0 = Double_val(v0);
	GLclampf lv1 = Double_val(v1);
	GLclampf lv2 = Double_val(v2);
	GLclampf lv3 = Double_val(v3);
	LOAD_FUNCTION(glClearColor);
	CALL_FUNCTION(glClearColor)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearColorIiEXT,(GLint, GLint, GLint, GLint),void);
value glstub_glClearColorIiEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glClearColorIiEXT);
	CALL_FUNCTION(glClearColorIiEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearColorIuiEXT,(GLuint, GLuint, GLuint, GLuint),void);
value glstub_glClearColorIuiEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	LOAD_FUNCTION(glClearColorIuiEXT);
	CALL_FUNCTION(glClearColorIuiEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearDepth,(GLclampd),void);
value glstub_glClearDepth(value v0)
{
	CAMLparam1(v0);
	GLclampd lv0 = Double_val(v0);
	LOAD_FUNCTION(glClearDepth);
	CALL_FUNCTION(glClearDepth)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearDepthdNV,(GLdouble),void);
value glstub_glClearDepthdNV(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	LOAD_FUNCTION(glClearDepthdNV);
	CALL_FUNCTION(glClearDepthdNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearDepthfOES,(GLclampd),void);
value glstub_glClearDepthfOES(value v0)
{
	CAMLparam1(v0);
	GLclampd lv0 = Double_val(v0);
	LOAD_FUNCTION(glClearDepthfOES);
	CALL_FUNCTION(glClearDepthfOES)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearIndex,(GLfloat),void);
value glstub_glClearIndex(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glClearIndex);
	CALL_FUNCTION(glClearIndex)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClearStencil,(GLint),void);
value glstub_glClearStencil(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glClearStencil);
	CALL_FUNCTION(glClearStencil)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClientActiveTexture,(GLenum),void);
value glstub_glClientActiveTexture(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glClientActiveTexture);
	CALL_FUNCTION(glClientActiveTexture)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClientActiveTextureARB,(GLenum),void);
value glstub_glClientActiveTextureARB(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glClientActiveTextureARB);
	CALL_FUNCTION(glClientActiveTextureARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClientActiveVertexStreamATI,(GLenum),void);
value glstub_glClientActiveVertexStreamATI(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glClientActiveVertexStreamATI);
	CALL_FUNCTION(glClientActiveVertexStreamATI)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClipPlane,(GLenum, GLdouble*),void);
value glstub_glClipPlane(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glClipPlane);
	CALL_FUNCTION(glClipPlane)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glClipPlanefOES,(GLenum, GLfloat*),void);
value glstub_glClipPlanefOES(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glClipPlanefOES);
	CALL_FUNCTION(glClipPlanefOES)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3b,(GLbyte, GLbyte, GLbyte),void);
value glstub_glColor3b(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	LOAD_FUNCTION(glColor3b);
	CALL_FUNCTION(glColor3b)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3bv,(GLbyte*),void);
value glstub_glColor3bv(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3bv);
	CALL_FUNCTION(glColor3bv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3d,(GLdouble, GLdouble, GLdouble),void);
value glstub_glColor3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glColor3d);
	CALL_FUNCTION(glColor3d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3dv,(GLdouble*),void);
value glstub_glColor3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3dv);
	CALL_FUNCTION(glColor3dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3f,(GLfloat, GLfloat, GLfloat),void);
value glstub_glColor3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glColor3f);
	CALL_FUNCTION(glColor3f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3fVertex3fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glColor3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glColor3fVertex3fSUN);
	CALL_FUNCTION(glColor3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColor3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glColor3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glColor3fVertex3fvSUN,(GLfloat*, GLfloat*),void);
value glstub_glColor3fVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glColor3fVertex3fvSUN);
	CALL_FUNCTION(glColor3fVertex3fvSUN)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3fv,(GLfloat*),void);
value glstub_glColor3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3fv);
	CALL_FUNCTION(glColor3fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3hNV,(GLushort, GLushort, GLushort),void);
value glstub_glColor3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glColor3hNV);
	CALL_FUNCTION(glColor3hNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3hvNV,(GLushort*),void);
value glstub_glColor3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3hvNV);
	CALL_FUNCTION(glColor3hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3i,(GLint, GLint, GLint),void);
value glstub_glColor3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glColor3i);
	CALL_FUNCTION(glColor3i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3iv,(GLint*),void);
value glstub_glColor3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3iv);
	CALL_FUNCTION(glColor3iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3s,(GLshort, GLshort, GLshort),void);
value glstub_glColor3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glColor3s);
	CALL_FUNCTION(glColor3s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3sv,(GLshort*),void);
value glstub_glColor3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3sv);
	CALL_FUNCTION(glColor3sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3ub,(GLubyte, GLubyte, GLubyte),void);
value glstub_glColor3ub(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	LOAD_FUNCTION(glColor3ub);
	CALL_FUNCTION(glColor3ub)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3ubv,(GLubyte*),void);
value glstub_glColor3ubv(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3ubv);
	CALL_FUNCTION(glColor3ubv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3ui,(GLuint, GLuint, GLuint),void);
value glstub_glColor3ui(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glColor3ui);
	CALL_FUNCTION(glColor3ui)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3uiv,(GLuint*),void);
value glstub_glColor3uiv(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3uiv);
	CALL_FUNCTION(glColor3uiv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3us,(GLushort, GLushort, GLushort),void);
value glstub_glColor3us(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glColor3us);
	CALL_FUNCTION(glColor3us)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor3usv,(GLushort*),void);
value glstub_glColor3usv(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor3usv);
	CALL_FUNCTION(glColor3usv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4b,(GLbyte, GLbyte, GLbyte, GLbyte),void);
value glstub_glColor4b(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	GLbyte lv3 = Int_val(v3);
	LOAD_FUNCTION(glColor4b);
	CALL_FUNCTION(glColor4b)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4bv,(GLbyte*),void);
value glstub_glColor4bv(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4bv);
	CALL_FUNCTION(glColor4bv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4d,(GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glColor4d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glColor4d);
	CALL_FUNCTION(glColor4d)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4dv,(GLdouble*),void);
value glstub_glColor4dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4dv);
	CALL_FUNCTION(glColor4dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4f,(GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glColor4f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glColor4f);
	CALL_FUNCTION(glColor4f)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4fNormal3fVertex3fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glColor4fNormal3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	GLfloat lv8 = Double_val(v8);
	GLfloat lv9 = Double_val(v9);
	LOAD_FUNCTION(glColor4fNormal3fVertex3fSUN);
	CALL_FUNCTION(glColor4fNormal3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glColor4fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glColor4fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

DECLARE_FUNCTION(glColor4fNormal3fVertex3fvSUN,(GLfloat*, GLfloat*, GLfloat*),void);
value glstub_glColor4fNormal3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glColor4fNormal3fVertex3fvSUN);
	CALL_FUNCTION(glColor4fNormal3fVertex3fvSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4fv,(GLfloat*),void);
value glstub_glColor4fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4fv);
	CALL_FUNCTION(glColor4fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4hNV,(GLushort, GLushort, GLushort, GLushort),void);
value glstub_glColor4hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	LOAD_FUNCTION(glColor4hNV);
	CALL_FUNCTION(glColor4hNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4hvNV,(GLushort*),void);
value glstub_glColor4hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4hvNV);
	CALL_FUNCTION(glColor4hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4i,(GLint, GLint, GLint, GLint),void);
value glstub_glColor4i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glColor4i);
	CALL_FUNCTION(glColor4i)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4iv,(GLint*),void);
value glstub_glColor4iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4iv);
	CALL_FUNCTION(glColor4iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4s,(GLshort, GLshort, GLshort, GLshort),void);
value glstub_glColor4s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glColor4s);
	CALL_FUNCTION(glColor4s)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4sv,(GLshort*),void);
value glstub_glColor4sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4sv);
	CALL_FUNCTION(glColor4sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4ub,(GLubyte, GLubyte, GLubyte, GLubyte),void);
value glstub_glColor4ub(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	LOAD_FUNCTION(glColor4ub);
	CALL_FUNCTION(glColor4ub)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4ubVertex2fSUN,(GLubyte, GLubyte, GLubyte, GLubyte, GLfloat, GLfloat),void);
value glstub_glColor4ubVertex2fSUN(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glColor4ubVertex2fSUN);
	CALL_FUNCTION(glColor4ubVertex2fSUN)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColor4ubVertex2fSUN_byte(value * argv, int n)
{
	return glstub_glColor4ubVertex2fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glColor4ubVertex2fvSUN,(GLubyte*, GLfloat*),void);
value glstub_glColor4ubVertex2fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLubyte* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glColor4ubVertex2fvSUN);
	CALL_FUNCTION(glColor4ubVertex2fvSUN)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4ubVertex3fSUN,(GLubyte, GLubyte, GLubyte, GLubyte, GLfloat, GLfloat, GLfloat),void);
value glstub_glColor4ubVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	LOAD_FUNCTION(glColor4ubVertex3fSUN);
	CALL_FUNCTION(glColor4ubVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glColor4ubVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glColor4ubVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glColor4ubVertex3fvSUN,(GLubyte*, GLfloat*),void);
value glstub_glColor4ubVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLubyte* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glColor4ubVertex3fvSUN);
	CALL_FUNCTION(glColor4ubVertex3fvSUN)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4ubv,(GLubyte*),void);
value glstub_glColor4ubv(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4ubv);
	CALL_FUNCTION(glColor4ubv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4ui,(GLuint, GLuint, GLuint, GLuint),void);
value glstub_glColor4ui(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	LOAD_FUNCTION(glColor4ui);
	CALL_FUNCTION(glColor4ui)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4uiv,(GLuint*),void);
value glstub_glColor4uiv(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4uiv);
	CALL_FUNCTION(glColor4uiv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4us,(GLushort, GLushort, GLushort, GLushort),void);
value glstub_glColor4us(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	LOAD_FUNCTION(glColor4us);
	CALL_FUNCTION(glColor4us)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColor4usv,(GLushort*),void);
value glstub_glColor4usv(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glColor4usv);
	CALL_FUNCTION(glColor4usv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorFragmentOp1ATI,(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glColorFragmentOp1ATI(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	GLuint lv6 = Int_val(v6);
	LOAD_FUNCTION(glColorFragmentOp1ATI);
	CALL_FUNCTION(glColorFragmentOp1ATI)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glColorFragmentOp1ATI_byte(value * argv, int n)
{
	return glstub_glColorFragmentOp1ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glColorFragmentOp2ATI,(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glColorFragmentOp2ATI(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	GLuint lv6 = Int_val(v6);
	GLuint lv7 = Int_val(v7);
	GLuint lv8 = Int_val(v8);
	GLuint lv9 = Int_val(v9);
	LOAD_FUNCTION(glColorFragmentOp2ATI);
	CALL_FUNCTION(glColorFragmentOp2ATI)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glColorFragmentOp2ATI_byte(value * argv, int n)
{
	return glstub_glColorFragmentOp2ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

DECLARE_FUNCTION(glColorFragmentOp3ATI,(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glColorFragmentOp3ATI(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10, value v11, value v12)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam3(v10, v11, v12);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	GLuint lv6 = Int_val(v6);
	GLuint lv7 = Int_val(v7);
	GLuint lv8 = Int_val(v8);
	GLuint lv9 = Int_val(v9);
	GLuint lv10 = Int_val(v10);
	GLuint lv11 = Int_val(v11);
	GLuint lv12 = Int_val(v12);
	LOAD_FUNCTION(glColorFragmentOp3ATI);
	CALL_FUNCTION(glColorFragmentOp3ATI)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11, lv12);
	CAMLreturn(Val_unit);
}

value glstub_glColorFragmentOp3ATI_byte(value * argv, int n)
{
	return glstub_glColorFragmentOp3ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12]);
}

DECLARE_FUNCTION(glColorMask,(GLboolean, GLboolean, GLboolean, GLboolean),void);
value glstub_glColorMask(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLboolean lv0 = Bool_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLboolean lv3 = Bool_val(v3);
	LOAD_FUNCTION(glColorMask);
	CALL_FUNCTION(glColorMask)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorMaskIndexedEXT,(GLuint, GLboolean, GLboolean, GLboolean, GLboolean),void);
value glstub_glColorMaskIndexedEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLboolean lv3 = Bool_val(v3);
	GLboolean lv4 = Bool_val(v4);
	LOAD_FUNCTION(glColorMaskIndexedEXT);
	CALL_FUNCTION(glColorMaskIndexedEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorMaterial,(GLenum, GLenum),void);
value glstub_glColorMaterial(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glColorMaterial);
	CALL_FUNCTION(glColorMaterial)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorPointer,(GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glColorPointer(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glColorPointer);
	CALL_FUNCTION(glColorPointer)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorPointerEXT,(GLint, GLenum, GLsizei, GLsizei, GLvoid*),void);
value glstub_glColorPointerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glColorPointerEXT);
	CALL_FUNCTION(glColorPointerEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorPointerListIBM,(GLint, GLenum, GLint, GLvoid**, GLint),void);
value glstub_glColorPointerListIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glColorPointerListIBM);
	CALL_FUNCTION(glColorPointerListIBM)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorPointervINTEL,(GLint, GLenum, GLvoid**),void);
value glstub_glColorPointervINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glColorPointervINTEL);
	CALL_FUNCTION(glColorPointervINTEL)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorSubTable,(GLenum, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glColorSubTable(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glColorSubTable);
	CALL_FUNCTION(glColorSubTable)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorSubTable_byte(value * argv, int n)
{
	return glstub_glColorSubTable(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glColorSubTableEXT,(GLenum, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glColorSubTableEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glColorSubTableEXT);
	CALL_FUNCTION(glColorSubTableEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorSubTableEXT_byte(value * argv, int n)
{
	return glstub_glColorSubTableEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glColorTable,(GLenum, GLenum, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glColorTable(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glColorTable);
	CALL_FUNCTION(glColorTable)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorTable_byte(value * argv, int n)
{
	return glstub_glColorTable(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glColorTableEXT,(GLenum, GLenum, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glColorTableEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glColorTableEXT);
	CALL_FUNCTION(glColorTableEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorTableEXT_byte(value * argv, int n)
{
	return glstub_glColorTableEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glColorTableParameterfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glColorTableParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glColorTableParameterfv);
	CALL_FUNCTION(glColorTableParameterfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorTableParameterfvSGI,(GLenum, GLenum, GLfloat*),void);
value glstub_glColorTableParameterfvSGI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glColorTableParameterfvSGI);
	CALL_FUNCTION(glColorTableParameterfvSGI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorTableParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glColorTableParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glColorTableParameteriv);
	CALL_FUNCTION(glColorTableParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorTableParameterivSGI,(GLenum, GLenum, GLint*),void);
value glstub_glColorTableParameterivSGI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glColorTableParameterivSGI);
	CALL_FUNCTION(glColorTableParameterivSGI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glColorTableSGI,(GLenum, GLenum, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glColorTableSGI(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glColorTableSGI);
	CALL_FUNCTION(glColorTableSGI)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorTableSGI_byte(value * argv, int n)
{
	return glstub_glColorTableSGI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glCombinerInputNV,(GLenum, GLenum, GLenum, GLenum, GLenum, GLenum),void);
value glstub_glCombinerInputNV(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	LOAD_FUNCTION(glCombinerInputNV);
	CALL_FUNCTION(glCombinerInputNV)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCombinerInputNV_byte(value * argv, int n)
{
	return glstub_glCombinerInputNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glCombinerOutputNV,(GLenum, GLenum, GLenum, GLenum, GLenum, GLenum, GLenum, GLboolean, GLboolean, GLboolean),void);
value glstub_glCombinerOutputNV(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLenum lv6 = Int_val(v6);
	GLboolean lv7 = Bool_val(v7);
	GLboolean lv8 = Bool_val(v8);
	GLboolean lv9 = Bool_val(v9);
	LOAD_FUNCTION(glCombinerOutputNV);
	CALL_FUNCTION(glCombinerOutputNV)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glCombinerOutputNV_byte(value * argv, int n)
{
	return glstub_glCombinerOutputNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

DECLARE_FUNCTION(glCombinerParameterfNV,(GLenum, GLfloat),void);
value glstub_glCombinerParameterfNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glCombinerParameterfNV);
	CALL_FUNCTION(glCombinerParameterfNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCombinerParameterfvNV,(GLenum, GLfloat*),void);
value glstub_glCombinerParameterfvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glCombinerParameterfvNV);
	CALL_FUNCTION(glCombinerParameterfvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCombinerParameteriNV,(GLenum, GLint),void);
value glstub_glCombinerParameteriNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glCombinerParameteriNV);
	CALL_FUNCTION(glCombinerParameteriNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCombinerParameterivNV,(GLenum, GLint*),void);
value glstub_glCombinerParameterivNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glCombinerParameterivNV);
	CALL_FUNCTION(glCombinerParameterivNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCombinerStageParameterfvNV,(GLenum, GLenum, GLfloat*),void);
value glstub_glCombinerStageParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glCombinerStageParameterfvNV);
	CALL_FUNCTION(glCombinerStageParameterfvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCompileShader,(GLuint),void);
value glstub_glCompileShader(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glCompileShader);
	CALL_FUNCTION(glCompileShader)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCompileShaderARB,(GLuint),void);
value glstub_glCompileShaderARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glCompileShaderARB);
	CALL_FUNCTION(glCompileShaderARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCompressedTexImage1D,(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, GLvoid*),void);
value glstub_glCompressedTexImage1D(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glCompressedTexImage1D);
	CALL_FUNCTION(glCompressedTexImage1D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage1D_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glCompressedTexImage1DARB,(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, GLvoid*),void);
value glstub_glCompressedTexImage1DARB(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glCompressedTexImage1DARB);
	CALL_FUNCTION(glCompressedTexImage1DARB)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage1DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage1DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glCompressedTexImage2D,(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, GLvoid*),void);
value glstub_glCompressedTexImage2D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLvoid* lv7 = (Is_long(v7) ? (GLvoid*)Long_val(v7) : ((Tag_val(v7) == String_tag)? (String_val(v7)) : (Data_bigarray_val(v7))));
	LOAD_FUNCTION(glCompressedTexImage2D);
	CALL_FUNCTION(glCompressedTexImage2D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage2D_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glCompressedTexImage2DARB,(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, GLvoid*),void);
value glstub_glCompressedTexImage2DARB(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLvoid* lv7 = (Is_long(v7) ? (GLvoid*)Long_val(v7) : ((Tag_val(v7) == String_tag)? (String_val(v7)) : (Data_bigarray_val(v7))));
	LOAD_FUNCTION(glCompressedTexImage2DARB);
	CALL_FUNCTION(glCompressedTexImage2DARB)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage2DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage2DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glCompressedTexImage3D,(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, GLvoid*),void);
value glstub_glCompressedTexImage3D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLvoid* lv8 = (Is_long(v8) ? (GLvoid*)Long_val(v8) : ((Tag_val(v8) == String_tag)? (String_val(v8)) : (Data_bigarray_val(v8))));
	LOAD_FUNCTION(glCompressedTexImage3D);
	CALL_FUNCTION(glCompressedTexImage3D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage3D_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glCompressedTexImage3DARB,(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, GLvoid*),void);
value glstub_glCompressedTexImage3DARB(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLvoid* lv8 = (Is_long(v8) ? (GLvoid*)Long_val(v8) : ((Tag_val(v8) == String_tag)? (String_val(v8)) : (Data_bigarray_val(v8))));
	LOAD_FUNCTION(glCompressedTexImage3DARB);
	CALL_FUNCTION(glCompressedTexImage3DARB)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage3DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage3DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glCompressedTexSubImage1D,(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, GLvoid*),void);
value glstub_glCompressedTexSubImage1D(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glCompressedTexSubImage1D);
	CALL_FUNCTION(glCompressedTexSubImage1D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage1D_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glCompressedTexSubImage1DARB,(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, GLvoid*),void);
value glstub_glCompressedTexSubImage1DARB(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glCompressedTexSubImage1DARB);
	CALL_FUNCTION(glCompressedTexSubImage1DARB)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage1DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage1DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glCompressedTexSubImage2D,(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, GLvoid*),void);
value glstub_glCompressedTexSubImage2D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLenum lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLvoid* lv8 = (Is_long(v8) ? (GLvoid*)Long_val(v8) : ((Tag_val(v8) == String_tag)? (String_val(v8)) : (Data_bigarray_val(v8))));
	LOAD_FUNCTION(glCompressedTexSubImage2D);
	CALL_FUNCTION(glCompressedTexSubImage2D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage2D_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glCompressedTexSubImage2DARB,(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, GLvoid*),void);
value glstub_glCompressedTexSubImage2DARB(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLenum lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLvoid* lv8 = (Is_long(v8) ? (GLvoid*)Long_val(v8) : ((Tag_val(v8) == String_tag)? (String_val(v8)) : (Data_bigarray_val(v8))));
	LOAD_FUNCTION(glCompressedTexSubImage2DARB);
	CALL_FUNCTION(glCompressedTexSubImage2DARB)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage2DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage2DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glCompressedTexSubImage3D,(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, GLvoid*),void);
value glstub_glCompressedTexSubImage3D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam1(v10);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLenum lv8 = Int_val(v8);
	GLsizei lv9 = Int_val(v9);
	GLvoid* lv10 = (Is_long(v10) ? (GLvoid*)Long_val(v10) : ((Tag_val(v10) == String_tag)? (String_val(v10)) : (Data_bigarray_val(v10))));
	LOAD_FUNCTION(glCompressedTexSubImage3D);
	CALL_FUNCTION(glCompressedTexSubImage3D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage3D_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

DECLARE_FUNCTION(glCompressedTexSubImage3DARB,(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, GLvoid*),void);
value glstub_glCompressedTexSubImage3DARB(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam1(v10);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLenum lv8 = Int_val(v8);
	GLsizei lv9 = Int_val(v9);
	GLvoid* lv10 = (Is_long(v10) ? (GLvoid*)Long_val(v10) : ((Tag_val(v10) == String_tag)? (String_val(v10)) : (Data_bigarray_val(v10))));
	LOAD_FUNCTION(glCompressedTexSubImage3DARB);
	CALL_FUNCTION(glCompressedTexSubImage3DARB)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage3DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage3DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

DECLARE_FUNCTION(glConvolutionFilter1D,(GLenum, GLenum, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glConvolutionFilter1D(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glConvolutionFilter1D);
	CALL_FUNCTION(glConvolutionFilter1D)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionFilter1D_byte(value * argv, int n)
{
	return glstub_glConvolutionFilter1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glConvolutionFilter1DEXT,(GLenum, GLenum, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glConvolutionFilter1DEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glConvolutionFilter1DEXT);
	CALL_FUNCTION(glConvolutionFilter1DEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionFilter1DEXT_byte(value * argv, int n)
{
	return glstub_glConvolutionFilter1DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glConvolutionFilter2D,(GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glConvolutionFilter2D(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glConvolutionFilter2D);
	CALL_FUNCTION(glConvolutionFilter2D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionFilter2D_byte(value * argv, int n)
{
	return glstub_glConvolutionFilter2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glConvolutionFilter2DEXT,(GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glConvolutionFilter2DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glConvolutionFilter2DEXT);
	CALL_FUNCTION(glConvolutionFilter2DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionFilter2DEXT_byte(value * argv, int n)
{
	return glstub_glConvolutionFilter2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glConvolutionParameterf,(GLenum, GLenum, GLfloat),void);
value glstub_glConvolutionParameterf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glConvolutionParameterf);
	CALL_FUNCTION(glConvolutionParameterf)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glConvolutionParameterfEXT,(GLenum, GLenum, GLfloat),void);
value glstub_glConvolutionParameterfEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glConvolutionParameterfEXT);
	CALL_FUNCTION(glConvolutionParameterfEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glConvolutionParameterfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glConvolutionParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glConvolutionParameterfv);
	CALL_FUNCTION(glConvolutionParameterfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glConvolutionParameterfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glConvolutionParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glConvolutionParameterfvEXT);
	CALL_FUNCTION(glConvolutionParameterfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glConvolutionParameteri,(GLenum, GLenum, GLint),void);
value glstub_glConvolutionParameteri(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glConvolutionParameteri);
	CALL_FUNCTION(glConvolutionParameteri)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glConvolutionParameteriEXT,(GLenum, GLenum, GLint),void);
value glstub_glConvolutionParameteriEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glConvolutionParameteriEXT);
	CALL_FUNCTION(glConvolutionParameteriEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glConvolutionParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glConvolutionParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glConvolutionParameteriv);
	CALL_FUNCTION(glConvolutionParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glConvolutionParameterivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glConvolutionParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glConvolutionParameterivEXT);
	CALL_FUNCTION(glConvolutionParameterivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCopyColorSubTable,(GLenum, GLsizei, GLint, GLint, GLsizei),void);
value glstub_glCopyColorSubTable(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glCopyColorSubTable);
	CALL_FUNCTION(glCopyColorSubTable)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCopyColorSubTableEXT,(GLenum, GLsizei, GLint, GLint, GLsizei),void);
value glstub_glCopyColorSubTableEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glCopyColorSubTableEXT);
	CALL_FUNCTION(glCopyColorSubTableEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCopyColorTable,(GLenum, GLenum, GLint, GLint, GLsizei),void);
value glstub_glCopyColorTable(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glCopyColorTable);
	CALL_FUNCTION(glCopyColorTable)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCopyColorTableSGI,(GLenum, GLenum, GLint, GLint, GLsizei),void);
value glstub_glCopyColorTableSGI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glCopyColorTableSGI);
	CALL_FUNCTION(glCopyColorTableSGI)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCopyConvolutionFilter1D,(GLenum, GLenum, GLint, GLint, GLsizei),void);
value glstub_glCopyConvolutionFilter1D(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glCopyConvolutionFilter1D);
	CALL_FUNCTION(glCopyConvolutionFilter1D)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCopyConvolutionFilter1DEXT,(GLenum, GLenum, GLint, GLint, GLsizei),void);
value glstub_glCopyConvolutionFilter1DEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glCopyConvolutionFilter1DEXT);
	CALL_FUNCTION(glCopyConvolutionFilter1DEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCopyConvolutionFilter2D,(GLenum, GLenum, GLint, GLint, GLsizei, GLsizei),void);
value glstub_glCopyConvolutionFilter2D(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	LOAD_FUNCTION(glCopyConvolutionFilter2D);
	CALL_FUNCTION(glCopyConvolutionFilter2D)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCopyConvolutionFilter2D_byte(value * argv, int n)
{
	return glstub_glCopyConvolutionFilter2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glCopyConvolutionFilter2DEXT,(GLenum, GLenum, GLint, GLint, GLsizei, GLsizei),void);
value glstub_glCopyConvolutionFilter2DEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	LOAD_FUNCTION(glCopyConvolutionFilter2DEXT);
	CALL_FUNCTION(glCopyConvolutionFilter2DEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCopyConvolutionFilter2DEXT_byte(value * argv, int n)
{
	return glstub_glCopyConvolutionFilter2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glCopyPixels,(GLint, GLint, GLsizei, GLsizei, GLenum),void);
value glstub_glCopyPixels(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	LOAD_FUNCTION(glCopyPixels);
	CALL_FUNCTION(glCopyPixels)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCopyTexImage1D,(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint),void);
value glstub_glCopyTexImage1D(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	LOAD_FUNCTION(glCopyTexImage1D);
	CALL_FUNCTION(glCopyTexImage1D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexImage1D_byte(value * argv, int n)
{
	return glstub_glCopyTexImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glCopyTexImage1DEXT,(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint),void);
value glstub_glCopyTexImage1DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	LOAD_FUNCTION(glCopyTexImage1DEXT);
	CALL_FUNCTION(glCopyTexImage1DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexImage1DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexImage1DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glCopyTexImage2D,(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint),void);
value glstub_glCopyTexImage2D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLint lv7 = Int_val(v7);
	LOAD_FUNCTION(glCopyTexImage2D);
	CALL_FUNCTION(glCopyTexImage2D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexImage2D_byte(value * argv, int n)
{
	return glstub_glCopyTexImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glCopyTexImage2DEXT,(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint),void);
value glstub_glCopyTexImage2DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLint lv7 = Int_val(v7);
	LOAD_FUNCTION(glCopyTexImage2DEXT);
	CALL_FUNCTION(glCopyTexImage2DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexImage2DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexImage2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glCopyTexSubImage1D,(GLenum, GLint, GLint, GLint, GLint, GLsizei),void);
value glstub_glCopyTexSubImage1D(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	LOAD_FUNCTION(glCopyTexSubImage1D);
	CALL_FUNCTION(glCopyTexSubImage1D)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage1D_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glCopyTexSubImage1DEXT,(GLenum, GLint, GLint, GLint, GLint, GLsizei),void);
value glstub_glCopyTexSubImage1DEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	LOAD_FUNCTION(glCopyTexSubImage1DEXT);
	CALL_FUNCTION(glCopyTexSubImage1DEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage1DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage1DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glCopyTexSubImage2D,(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei),void);
value glstub_glCopyTexSubImage2D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	LOAD_FUNCTION(glCopyTexSubImage2D);
	CALL_FUNCTION(glCopyTexSubImage2D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage2D_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glCopyTexSubImage2DEXT,(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei),void);
value glstub_glCopyTexSubImage2DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	LOAD_FUNCTION(glCopyTexSubImage2DEXT);
	CALL_FUNCTION(glCopyTexSubImage2DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage2DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glCopyTexSubImage3D,(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei),void);
value glstub_glCopyTexSubImage3D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLsizei lv8 = Int_val(v8);
	LOAD_FUNCTION(glCopyTexSubImage3D);
	CALL_FUNCTION(glCopyTexSubImage3D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage3D_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glCopyTexSubImage3DEXT,(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei),void);
value glstub_glCopyTexSubImage3DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLsizei lv8 = Int_val(v8);
	LOAD_FUNCTION(glCopyTexSubImage3DEXT);
	CALL_FUNCTION(glCopyTexSubImage3DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage3DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage3DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glCreateProgram,(void),GLuint);
value glstub_glCreateProgram(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint ret;
	LOAD_FUNCTION(glCreateProgram);
	ret = CALL_FUNCTION(glCreateProgram)();
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glCreateProgramObjectARB,(void),GLuint);
value glstub_glCreateProgramObjectARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint ret;
	LOAD_FUNCTION(glCreateProgramObjectARB);
	ret = CALL_FUNCTION(glCreateProgramObjectARB)();
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glCreateShader,(GLenum),GLuint);
value glstub_glCreateShader(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint ret;
	LOAD_FUNCTION(glCreateShader);
	ret = CALL_FUNCTION(glCreateShader)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glCreateShaderObjectARB,(GLenum),GLuint);
value glstub_glCreateShaderObjectARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint ret;
	LOAD_FUNCTION(glCreateShaderObjectARB);
	ret = CALL_FUNCTION(glCreateShaderObjectARB)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glCullFace,(GLenum),void);
value glstub_glCullFace(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glCullFace);
	CALL_FUNCTION(glCullFace)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCullParameterdvEXT,(GLenum, GLdouble*),void);
value glstub_glCullParameterdvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glCullParameterdvEXT);
	CALL_FUNCTION(glCullParameterdvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCullParameterfvEXT,(GLenum, GLfloat*),void);
value glstub_glCullParameterfvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glCullParameterfvEXT);
	CALL_FUNCTION(glCullParameterfvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glCurrentPaletteMatrixARB,(GLint),void);
value glstub_glCurrentPaletteMatrixARB(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glCurrentPaletteMatrixARB);
	CALL_FUNCTION(glCurrentPaletteMatrixARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteAsyncMarkersSGIX,(GLuint, GLsizei),void);
value glstub_glDeleteAsyncMarkersSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	LOAD_FUNCTION(glDeleteAsyncMarkersSGIX);
	CALL_FUNCTION(glDeleteAsyncMarkersSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteBuffers,(GLsizei, GLuint*),void);
value glstub_glDeleteBuffers(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteBuffers);
	CALL_FUNCTION(glDeleteBuffers)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteBuffersARB,(GLsizei, GLuint*),void);
value glstub_glDeleteBuffersARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteBuffersARB);
	CALL_FUNCTION(glDeleteBuffersARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteFencesAPPLE,(GLsizei, GLuint*),void);
value glstub_glDeleteFencesAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteFencesAPPLE);
	CALL_FUNCTION(glDeleteFencesAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteFencesNV,(GLsizei, GLuint*),void);
value glstub_glDeleteFencesNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteFencesNV);
	CALL_FUNCTION(glDeleteFencesNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteFragmentShaderATI,(GLuint),void);
value glstub_glDeleteFragmentShaderATI(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glDeleteFragmentShaderATI);
	CALL_FUNCTION(glDeleteFragmentShaderATI)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteFramebuffersEXT,(GLsizei, GLuint*),void);
value glstub_glDeleteFramebuffersEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteFramebuffersEXT);
	CALL_FUNCTION(glDeleteFramebuffersEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteLists,(GLuint, GLsizei),void);
value glstub_glDeleteLists(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	LOAD_FUNCTION(glDeleteLists);
	CALL_FUNCTION(glDeleteLists)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteObjectARB,(GLuint),void);
value glstub_glDeleteObjectARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glDeleteObjectARB);
	CALL_FUNCTION(glDeleteObjectARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteOcclusionQueriesNV,(GLsizei, GLuint*),void);
value glstub_glDeleteOcclusionQueriesNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteOcclusionQueriesNV);
	CALL_FUNCTION(glDeleteOcclusionQueriesNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteProgram,(GLuint),void);
value glstub_glDeleteProgram(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glDeleteProgram);
	CALL_FUNCTION(glDeleteProgram)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteProgramsARB,(GLsizei, GLuint*),void);
value glstub_glDeleteProgramsARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteProgramsARB);
	CALL_FUNCTION(glDeleteProgramsARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteProgramsNV,(GLsizei, GLuint*),void);
value glstub_glDeleteProgramsNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteProgramsNV);
	CALL_FUNCTION(glDeleteProgramsNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteQueries,(GLsizei, GLuint*),void);
value glstub_glDeleteQueries(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteQueries);
	CALL_FUNCTION(glDeleteQueries)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteQueriesARB,(GLsizei, GLuint*),void);
value glstub_glDeleteQueriesARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteQueriesARB);
	CALL_FUNCTION(glDeleteQueriesARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteRenderbuffersEXT,(GLsizei, GLuint*),void);
value glstub_glDeleteRenderbuffersEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteRenderbuffersEXT);
	CALL_FUNCTION(glDeleteRenderbuffersEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteShader,(GLuint),void);
value glstub_glDeleteShader(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glDeleteShader);
	CALL_FUNCTION(glDeleteShader)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteTextures,(GLsizei, GLuint*),void);
value glstub_glDeleteTextures(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteTextures);
	CALL_FUNCTION(glDeleteTextures)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteTexturesEXT,(GLsizei, GLuint*),void);
value glstub_glDeleteTexturesEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteTexturesEXT);
	CALL_FUNCTION(glDeleteTexturesEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteVertexArrays,(GLsizei, GLuint*),void);
value glstub_glDeleteVertexArrays(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteVertexArrays);
	CALL_FUNCTION(glDeleteVertexArrays)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteVertexArraysAPPLE,(GLsizei, GLuint*),void);
value glstub_glDeleteVertexArraysAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDeleteVertexArraysAPPLE);
	CALL_FUNCTION(glDeleteVertexArraysAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDeleteVertexShaderEXT,(GLuint),void);
value glstub_glDeleteVertexShaderEXT(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glDeleteVertexShaderEXT);
	CALL_FUNCTION(glDeleteVertexShaderEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDepthBoundsEXT,(GLclampd, GLclampd),void);
value glstub_glDepthBoundsEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampd lv0 = Double_val(v0);
	GLclampd lv1 = Double_val(v1);
	LOAD_FUNCTION(glDepthBoundsEXT);
	CALL_FUNCTION(glDepthBoundsEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDepthBoundsdNV,(GLdouble, GLdouble),void);
value glstub_glDepthBoundsdNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glDepthBoundsdNV);
	CALL_FUNCTION(glDepthBoundsdNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDepthFunc,(GLenum),void);
value glstub_glDepthFunc(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glDepthFunc);
	CALL_FUNCTION(glDepthFunc)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDepthMask,(GLboolean),void);
value glstub_glDepthMask(value v0)
{
	CAMLparam1(v0);
	GLboolean lv0 = Bool_val(v0);
	LOAD_FUNCTION(glDepthMask);
	CALL_FUNCTION(glDepthMask)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDepthRange,(GLclampd, GLclampd),void);
value glstub_glDepthRange(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampd lv0 = Double_val(v0);
	GLclampd lv1 = Double_val(v1);
	LOAD_FUNCTION(glDepthRange);
	CALL_FUNCTION(glDepthRange)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDepthRangedNV,(GLdouble, GLdouble),void);
value glstub_glDepthRangedNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glDepthRangedNV);
	CALL_FUNCTION(glDepthRangedNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDepthRangefOES,(GLclampf, GLclampf),void);
value glstub_glDepthRangefOES(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLclampf lv1 = Double_val(v1);
	LOAD_FUNCTION(glDepthRangefOES);
	CALL_FUNCTION(glDepthRangefOES)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDetachObjectARB,(GLuint, GLuint),void);
value glstub_glDetachObjectARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glDetachObjectARB);
	CALL_FUNCTION(glDetachObjectARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDetachShader,(GLuint, GLuint),void);
value glstub_glDetachShader(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glDetachShader);
	CALL_FUNCTION(glDetachShader)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDetailTexFuncSGIS,(GLenum, GLsizei, GLfloat*),void);
value glstub_glDetailTexFuncSGIS(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glDetailTexFuncSGIS);
	CALL_FUNCTION(glDetailTexFuncSGIS)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDisable,(GLenum),void);
value glstub_glDisable(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glDisable);
	CALL_FUNCTION(glDisable)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDisableClientState,(GLenum),void);
value glstub_glDisableClientState(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glDisableClientState);
	CALL_FUNCTION(glDisableClientState)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDisableIndexedEXT,(GLenum, GLuint),void);
value glstub_glDisableIndexedEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glDisableIndexedEXT);
	CALL_FUNCTION(glDisableIndexedEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDisableVariantClientStateEXT,(GLuint),void);
value glstub_glDisableVariantClientStateEXT(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glDisableVariantClientStateEXT);
	CALL_FUNCTION(glDisableVariantClientStateEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDisableVertexAttribArray,(GLuint),void);
value glstub_glDisableVertexAttribArray(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glDisableVertexAttribArray);
	CALL_FUNCTION(glDisableVertexAttribArray)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDisableVertexAttribArrayARB,(GLuint),void);
value glstub_glDisableVertexAttribArrayARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glDisableVertexAttribArrayARB);
	CALL_FUNCTION(glDisableVertexAttribArrayARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawArrays,(GLenum, GLint, GLsizei),void);
value glstub_glDrawArrays(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	LOAD_FUNCTION(glDrawArrays);
	CALL_FUNCTION(glDrawArrays)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawArraysEXT,(GLenum, GLint, GLsizei),void);
value glstub_glDrawArraysEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	LOAD_FUNCTION(glDrawArraysEXT);
	CALL_FUNCTION(glDrawArraysEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawArraysInstancedEXT,(GLenum, GLint, GLsizei, GLsizei),void);
value glstub_glDrawArraysInstancedEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glDrawArraysInstancedEXT);
	CALL_FUNCTION(glDrawArraysInstancedEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawBuffer,(GLenum),void);
value glstub_glDrawBuffer(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glDrawBuffer);
	CALL_FUNCTION(glDrawBuffer)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawBuffers,(GLsizei, GLenum*),void);
value glstub_glDrawBuffers(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLenum* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDrawBuffers);
	CALL_FUNCTION(glDrawBuffers)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawBuffersARB,(GLsizei, GLenum*),void);
value glstub_glDrawBuffersARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLenum* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDrawBuffersARB);
	CALL_FUNCTION(glDrawBuffersARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawBuffersATI,(GLsizei, GLenum*),void);
value glstub_glDrawBuffersATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLenum* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glDrawBuffersATI);
	CALL_FUNCTION(glDrawBuffersATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawElementArrayAPPLE,(GLenum, GLint, GLsizei),void);
value glstub_glDrawElementArrayAPPLE(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	LOAD_FUNCTION(glDrawElementArrayAPPLE);
	CALL_FUNCTION(glDrawElementArrayAPPLE)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawElementArrayATI,(GLenum, GLsizei),void);
value glstub_glDrawElementArrayATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	LOAD_FUNCTION(glDrawElementArrayATI);
	CALL_FUNCTION(glDrawElementArrayATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawElements,(GLenum, GLsizei, GLenum, GLvoid*),void);
value glstub_glDrawElements(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glDrawElements);
	CALL_FUNCTION(glDrawElements)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawElementsInstancedEXT,(GLenum, GLsizei, GLenum, GLvoid*, GLsizei),void);
value glstub_glDrawElementsInstancedEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glDrawElementsInstancedEXT);
	CALL_FUNCTION(glDrawElementsInstancedEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawPixels,(GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glDrawPixels(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLsizei lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glDrawPixels);
	CALL_FUNCTION(glDrawPixels)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawRangeElementArrayAPPLE,(GLenum, GLuint, GLuint, GLint, GLsizei),void);
value glstub_glDrawRangeElementArrayAPPLE(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glDrawRangeElementArrayAPPLE);
	CALL_FUNCTION(glDrawRangeElementArrayAPPLE)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawRangeElementArrayATI,(GLenum, GLuint, GLuint, GLsizei),void);
value glstub_glDrawRangeElementArrayATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glDrawRangeElementArrayATI);
	CALL_FUNCTION(glDrawRangeElementArrayATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glDrawRangeElements,(GLenum, GLuint, GLuint, GLsizei, GLenum, GLvoid*),void);
value glstub_glDrawRangeElements(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glDrawRangeElements);
	CALL_FUNCTION(glDrawRangeElements)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glDrawRangeElements_byte(value * argv, int n)
{
	return glstub_glDrawRangeElements(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glDrawRangeElementsEXT,(GLenum, GLuint, GLuint, GLsizei, GLenum, GLvoid*),void);
value glstub_glDrawRangeElementsEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glDrawRangeElementsEXT);
	CALL_FUNCTION(glDrawRangeElementsEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glDrawRangeElementsEXT_byte(value * argv, int n)
{
	return glstub_glDrawRangeElementsEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glEdgeFlag,(GLboolean),void);
value glstub_glEdgeFlag(value v0)
{
	CAMLparam1(v0);
	GLboolean lv0 = Bool_val(v0);
	LOAD_FUNCTION(glEdgeFlag);
	CALL_FUNCTION(glEdgeFlag)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEdgeFlagPointer,(GLsizei, GLvoid*),void);
value glstub_glEdgeFlagPointer(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	LOAD_FUNCTION(glEdgeFlagPointer);
	CALL_FUNCTION(glEdgeFlagPointer)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEdgeFlagPointerEXT,(GLsizei, GLsizei, GLboolean*),void);
value glstub_glEdgeFlagPointerEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glEdgeFlagPointerEXT);
	CALL_FUNCTION(glEdgeFlagPointerEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEdgeFlagPointerListIBM,(GLint, GLboolean**, GLint),void);
value glstub_glEdgeFlagPointerListIBM(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLboolean** lv1 = Data_bigarray_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glEdgeFlagPointerListIBM);
	CALL_FUNCTION(glEdgeFlagPointerListIBM)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEdgeFlagv,(GLboolean*),void);
value glstub_glEdgeFlagv(value v0)
{
	CAMLparam1(v0);
	GLboolean* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glEdgeFlagv);
	CALL_FUNCTION(glEdgeFlagv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glElementPointerAPPLE,(GLenum, GLvoid*),void);
value glstub_glElementPointerAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	LOAD_FUNCTION(glElementPointerAPPLE);
	CALL_FUNCTION(glElementPointerAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glElementPointerATI,(GLenum, GLvoid*),void);
value glstub_glElementPointerATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	LOAD_FUNCTION(glElementPointerATI);
	CALL_FUNCTION(glElementPointerATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEnable,(GLenum),void);
value glstub_glEnable(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glEnable);
	CALL_FUNCTION(glEnable)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEnableClientState,(GLenum),void);
value glstub_glEnableClientState(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glEnableClientState);
	CALL_FUNCTION(glEnableClientState)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEnableIndexedEXT,(GLenum, GLuint),void);
value glstub_glEnableIndexedEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glEnableIndexedEXT);
	CALL_FUNCTION(glEnableIndexedEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEnableVariantClientStateEXT,(GLuint),void);
value glstub_glEnableVariantClientStateEXT(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glEnableVariantClientStateEXT);
	CALL_FUNCTION(glEnableVariantClientStateEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEnableVertexAttribArray,(GLuint),void);
value glstub_glEnableVertexAttribArray(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glEnableVertexAttribArray);
	CALL_FUNCTION(glEnableVertexAttribArray)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEnableVertexAttribArrayARB,(GLuint),void);
value glstub_glEnableVertexAttribArrayARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glEnableVertexAttribArrayARB);
	CALL_FUNCTION(glEnableVertexAttribArrayARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEnd,(void),void);
value glstub_glEnd(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glEnd);
	CALL_FUNCTION(glEnd)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEndFragmentShaderATI,(void),void);
value glstub_glEndFragmentShaderATI(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glEndFragmentShaderATI);
	CALL_FUNCTION(glEndFragmentShaderATI)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEndList,(void),void);
value glstub_glEndList(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glEndList);
	CALL_FUNCTION(glEndList)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEndOcclusionQueryNV,(void),void);
value glstub_glEndOcclusionQueryNV(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glEndOcclusionQueryNV);
	CALL_FUNCTION(glEndOcclusionQueryNV)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEndQuery,(GLenum),void);
value glstub_glEndQuery(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glEndQuery);
	CALL_FUNCTION(glEndQuery)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEndQueryARB,(GLenum),void);
value glstub_glEndQueryARB(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glEndQueryARB);
	CALL_FUNCTION(glEndQueryARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEndSceneEXT,(void),void);
value glstub_glEndSceneEXT(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glEndSceneEXT);
	CALL_FUNCTION(glEndSceneEXT)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEndTransformFeedbackNV,(void),void);
value glstub_glEndTransformFeedbackNV(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glEndTransformFeedbackNV);
	CALL_FUNCTION(glEndTransformFeedbackNV)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEndVertexShaderEXT,(void),void);
value glstub_glEndVertexShaderEXT(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glEndVertexShaderEXT);
	CALL_FUNCTION(glEndVertexShaderEXT)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalCoord1d,(GLdouble),void);
value glstub_glEvalCoord1d(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	LOAD_FUNCTION(glEvalCoord1d);
	CALL_FUNCTION(glEvalCoord1d)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalCoord1dv,(GLdouble*),void);
value glstub_glEvalCoord1dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glEvalCoord1dv);
	CALL_FUNCTION(glEvalCoord1dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalCoord1f,(GLfloat),void);
value glstub_glEvalCoord1f(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glEvalCoord1f);
	CALL_FUNCTION(glEvalCoord1f)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalCoord1fv,(GLfloat*),void);
value glstub_glEvalCoord1fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glEvalCoord1fv);
	CALL_FUNCTION(glEvalCoord1fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalCoord2d,(GLdouble, GLdouble),void);
value glstub_glEvalCoord2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glEvalCoord2d);
	CALL_FUNCTION(glEvalCoord2d)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalCoord2dv,(GLdouble*),void);
value glstub_glEvalCoord2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glEvalCoord2dv);
	CALL_FUNCTION(glEvalCoord2dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalCoord2f,(GLfloat, GLfloat),void);
value glstub_glEvalCoord2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glEvalCoord2f);
	CALL_FUNCTION(glEvalCoord2f)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalCoord2fv,(GLfloat*),void);
value glstub_glEvalCoord2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glEvalCoord2fv);
	CALL_FUNCTION(glEvalCoord2fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalMapsNV,(GLenum, GLenum),void);
value glstub_glEvalMapsNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glEvalMapsNV);
	CALL_FUNCTION(glEvalMapsNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalMesh1,(GLenum, GLint, GLint),void);
value glstub_glEvalMesh1(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glEvalMesh1);
	CALL_FUNCTION(glEvalMesh1)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalMesh2,(GLenum, GLint, GLint, GLint, GLint),void);
value glstub_glEvalMesh2(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glEvalMesh2);
	CALL_FUNCTION(glEvalMesh2)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalPoint1,(GLint),void);
value glstub_glEvalPoint1(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glEvalPoint1);
	CALL_FUNCTION(glEvalPoint1)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glEvalPoint2,(GLint, GLint),void);
value glstub_glEvalPoint2(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glEvalPoint2);
	CALL_FUNCTION(glEvalPoint2)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glExecuteProgramNV,(GLenum, GLuint, GLfloat*),void);
value glstub_glExecuteProgramNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glExecuteProgramNV);
	CALL_FUNCTION(glExecuteProgramNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glExtractComponentEXT,(GLuint, GLuint, GLuint),void);
value glstub_glExtractComponentEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glExtractComponentEXT);
	CALL_FUNCTION(glExtractComponentEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFeedbackBuffer,(GLsizei, GLenum, GLfloat*),void);
value glstub_glFeedbackBuffer(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFeedbackBuffer);
	CALL_FUNCTION(glFeedbackBuffer)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFinalCombinerInputNV,(GLenum, GLenum, GLenum, GLenum),void);
value glstub_glFinalCombinerInputNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glFinalCombinerInputNV);
	CALL_FUNCTION(glFinalCombinerInputNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFinish,(void),void);
value glstub_glFinish(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glFinish);
	CALL_FUNCTION(glFinish)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFinishAsyncSGIX,(GLuint*),GLint);
value glstub_glFinishAsyncSGIX(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLint ret;
	LOAD_FUNCTION(glFinishAsyncSGIX);
	ret = CALL_FUNCTION(glFinishAsyncSGIX)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glFinishFenceAPPLE,(GLuint),void);
value glstub_glFinishFenceAPPLE(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glFinishFenceAPPLE);
	CALL_FUNCTION(glFinishFenceAPPLE)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFinishFenceNV,(GLuint),void);
value glstub_glFinishFenceNV(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glFinishFenceNV);
	CALL_FUNCTION(glFinishFenceNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFinishObjectAPPLE,(GLenum, GLint),void);
value glstub_glFinishObjectAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glFinishObjectAPPLE);
	CALL_FUNCTION(glFinishObjectAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFinishTextureSUNX,(void),void);
value glstub_glFinishTextureSUNX(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glFinishTextureSUNX);
	CALL_FUNCTION(glFinishTextureSUNX)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFlush,(void),void);
value glstub_glFlush(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glFlush);
	CALL_FUNCTION(glFlush)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFlushPixelDataRangeNV,(GLenum),void);
value glstub_glFlushPixelDataRangeNV(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glFlushPixelDataRangeNV);
	CALL_FUNCTION(glFlushPixelDataRangeNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFlushRasterSGIX,(void),void);
value glstub_glFlushRasterSGIX(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glFlushRasterSGIX);
	CALL_FUNCTION(glFlushRasterSGIX)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFlushVertexArrayRangeAPPLE,(GLsizei, GLvoid*),void);
value glstub_glFlushVertexArrayRangeAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	LOAD_FUNCTION(glFlushVertexArrayRangeAPPLE);
	CALL_FUNCTION(glFlushVertexArrayRangeAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFlushVertexArrayRangeNV,(void),void);
value glstub_glFlushVertexArrayRangeNV(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glFlushVertexArrayRangeNV);
	CALL_FUNCTION(glFlushVertexArrayRangeNV)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordPointer,(GLenum, GLsizei, GLvoid*),void);
value glstub_glFogCoordPointer(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glFogCoordPointer);
	CALL_FUNCTION(glFogCoordPointer)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordPointerEXT,(GLenum, GLsizei, GLvoid*),void);
value glstub_glFogCoordPointerEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glFogCoordPointerEXT);
	CALL_FUNCTION(glFogCoordPointerEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordPointerListIBM,(GLenum, GLint, GLvoid**, GLint),void);
value glstub_glFogCoordPointerListIBM(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glFogCoordPointerListIBM);
	CALL_FUNCTION(glFogCoordPointerListIBM)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordd,(GLdouble),void);
value glstub_glFogCoordd(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	LOAD_FUNCTION(glFogCoordd);
	CALL_FUNCTION(glFogCoordd)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoorddEXT,(GLdouble),void);
value glstub_glFogCoorddEXT(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	LOAD_FUNCTION(glFogCoorddEXT);
	CALL_FUNCTION(glFogCoorddEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoorddv,(GLdouble*),void);
value glstub_glFogCoorddv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glFogCoorddv);
	CALL_FUNCTION(glFogCoorddv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoorddvEXT,(GLdouble*),void);
value glstub_glFogCoorddvEXT(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glFogCoorddvEXT);
	CALL_FUNCTION(glFogCoorddvEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordf,(GLfloat),void);
value glstub_glFogCoordf(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glFogCoordf);
	CALL_FUNCTION(glFogCoordf)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordfEXT,(GLfloat),void);
value glstub_glFogCoordfEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glFogCoordfEXT);
	CALL_FUNCTION(glFogCoordfEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordfv,(GLfloat*),void);
value glstub_glFogCoordfv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glFogCoordfv);
	CALL_FUNCTION(glFogCoordfv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordfvEXT,(GLfloat*),void);
value glstub_glFogCoordfvEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glFogCoordfvEXT);
	CALL_FUNCTION(glFogCoordfvEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordhNV,(GLushort),void);
value glstub_glFogCoordhNV(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	LOAD_FUNCTION(glFogCoordhNV);
	CALL_FUNCTION(glFogCoordhNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogCoordhvNV,(GLushort*),void);
value glstub_glFogCoordhvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glFogCoordhvNV);
	CALL_FUNCTION(glFogCoordhvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogFuncSGIS,(GLsizei, GLfloat*),void);
value glstub_glFogFuncSGIS(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glFogFuncSGIS);
	CALL_FUNCTION(glFogFuncSGIS)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogf,(GLenum, GLfloat),void);
value glstub_glFogf(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glFogf);
	CALL_FUNCTION(glFogf)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogfv,(GLenum, GLfloat*),void);
value glstub_glFogfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glFogfv);
	CALL_FUNCTION(glFogfv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogi,(GLenum, GLint),void);
value glstub_glFogi(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glFogi);
	CALL_FUNCTION(glFogi)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFogiv,(GLenum, GLint*),void);
value glstub_glFogiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glFogiv);
	CALL_FUNCTION(glFogiv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentColorMaterialEXT,(GLenum, GLenum),void);
value glstub_glFragmentColorMaterialEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glFragmentColorMaterialEXT);
	CALL_FUNCTION(glFragmentColorMaterialEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentColorMaterialSGIX,(GLenum, GLenum),void);
value glstub_glFragmentColorMaterialSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glFragmentColorMaterialSGIX);
	CALL_FUNCTION(glFragmentColorMaterialSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightModelfEXT,(GLenum, GLfloat),void);
value glstub_glFragmentLightModelfEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glFragmentLightModelfEXT);
	CALL_FUNCTION(glFragmentLightModelfEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightModelfSGIX,(GLenum, GLfloat),void);
value glstub_glFragmentLightModelfSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glFragmentLightModelfSGIX);
	CALL_FUNCTION(glFragmentLightModelfSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightModelfvEXT,(GLenum, GLfloat*),void);
value glstub_glFragmentLightModelfvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glFragmentLightModelfvEXT);
	CALL_FUNCTION(glFragmentLightModelfvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightModelfvSGIX,(GLenum, GLfloat*),void);
value glstub_glFragmentLightModelfvSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glFragmentLightModelfvSGIX);
	CALL_FUNCTION(glFragmentLightModelfvSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightModeliEXT,(GLenum, GLint),void);
value glstub_glFragmentLightModeliEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glFragmentLightModeliEXT);
	CALL_FUNCTION(glFragmentLightModeliEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightModeliSGIX,(GLenum, GLint),void);
value glstub_glFragmentLightModeliSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glFragmentLightModeliSGIX);
	CALL_FUNCTION(glFragmentLightModeliSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightModelivEXT,(GLenum, GLint*),void);
value glstub_glFragmentLightModelivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glFragmentLightModelivEXT);
	CALL_FUNCTION(glFragmentLightModelivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightModelivSGIX,(GLenum, GLint*),void);
value glstub_glFragmentLightModelivSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glFragmentLightModelivSGIX);
	CALL_FUNCTION(glFragmentLightModelivSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightfEXT,(GLenum, GLenum, GLfloat),void);
value glstub_glFragmentLightfEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glFragmentLightfEXT);
	CALL_FUNCTION(glFragmentLightfEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightfSGIX,(GLenum, GLenum, GLfloat),void);
value glstub_glFragmentLightfSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glFragmentLightfSGIX);
	CALL_FUNCTION(glFragmentLightfSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glFragmentLightfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFragmentLightfvEXT);
	CALL_FUNCTION(glFragmentLightfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightfvSGIX,(GLenum, GLenum, GLfloat*),void);
value glstub_glFragmentLightfvSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFragmentLightfvSGIX);
	CALL_FUNCTION(glFragmentLightfvSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightiEXT,(GLenum, GLenum, GLint),void);
value glstub_glFragmentLightiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glFragmentLightiEXT);
	CALL_FUNCTION(glFragmentLightiEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightiSGIX,(GLenum, GLenum, GLint),void);
value glstub_glFragmentLightiSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glFragmentLightiSGIX);
	CALL_FUNCTION(glFragmentLightiSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glFragmentLightivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFragmentLightivEXT);
	CALL_FUNCTION(glFragmentLightivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentLightivSGIX,(GLenum, GLenum, GLint*),void);
value glstub_glFragmentLightivSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFragmentLightivSGIX);
	CALL_FUNCTION(glFragmentLightivSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentMaterialfEXT,(GLenum, GLenum, GLfloat),void);
value glstub_glFragmentMaterialfEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glFragmentMaterialfEXT);
	CALL_FUNCTION(glFragmentMaterialfEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentMaterialfSGIX,(GLenum, GLenum, GLfloat),void);
value glstub_glFragmentMaterialfSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glFragmentMaterialfSGIX);
	CALL_FUNCTION(glFragmentMaterialfSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentMaterialfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glFragmentMaterialfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFragmentMaterialfvEXT);
	CALL_FUNCTION(glFragmentMaterialfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentMaterialfvSGIX,(GLenum, GLenum, GLfloat*),void);
value glstub_glFragmentMaterialfvSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFragmentMaterialfvSGIX);
	CALL_FUNCTION(glFragmentMaterialfvSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentMaterialiEXT,(GLenum, GLenum, GLint),void);
value glstub_glFragmentMaterialiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glFragmentMaterialiEXT);
	CALL_FUNCTION(glFragmentMaterialiEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentMaterialiSGIX,(GLenum, GLenum, GLint),void);
value glstub_glFragmentMaterialiSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glFragmentMaterialiSGIX);
	CALL_FUNCTION(glFragmentMaterialiSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentMaterialivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glFragmentMaterialivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFragmentMaterialivEXT);
	CALL_FUNCTION(glFragmentMaterialivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFragmentMaterialivSGIX,(GLenum, GLenum, GLint*),void);
value glstub_glFragmentMaterialivSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glFragmentMaterialivSGIX);
	CALL_FUNCTION(glFragmentMaterialivSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFrameZoomSGIX,(GLint),void);
value glstub_glFrameZoomSGIX(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glFrameZoomSGIX);
	CALL_FUNCTION(glFrameZoomSGIX)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFramebufferRenderbufferEXT,(GLenum, GLenum, GLenum, GLuint),void);
value glstub_glFramebufferRenderbufferEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	LOAD_FUNCTION(glFramebufferRenderbufferEXT);
	CALL_FUNCTION(glFramebufferRenderbufferEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFramebufferTexture1DEXT,(GLenum, GLenum, GLenum, GLuint, GLint),void);
value glstub_glFramebufferTexture1DEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glFramebufferTexture1DEXT);
	CALL_FUNCTION(glFramebufferTexture1DEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFramebufferTexture2DEXT,(GLenum, GLenum, GLenum, GLuint, GLint),void);
value glstub_glFramebufferTexture2DEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glFramebufferTexture2DEXT);
	CALL_FUNCTION(glFramebufferTexture2DEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFramebufferTexture3DEXT,(GLenum, GLenum, GLenum, GLuint, GLint, GLint),void);
value glstub_glFramebufferTexture3DEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	LOAD_FUNCTION(glFramebufferTexture3DEXT);
	CALL_FUNCTION(glFramebufferTexture3DEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glFramebufferTexture3DEXT_byte(value * argv, int n)
{
	return glstub_glFramebufferTexture3DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glFramebufferTextureEXT,(GLenum, GLenum, GLuint, GLint),void);
value glstub_glFramebufferTextureEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glFramebufferTextureEXT);
	CALL_FUNCTION(glFramebufferTextureEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFramebufferTextureFaceEXT,(GLenum, GLenum, GLuint, GLint, GLenum),void);
value glstub_glFramebufferTextureFaceEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	LOAD_FUNCTION(glFramebufferTextureFaceEXT);
	CALL_FUNCTION(glFramebufferTextureFaceEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFramebufferTextureLayerEXT,(GLenum, GLenum, GLuint, GLint, GLint),void);
value glstub_glFramebufferTextureLayerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glFramebufferTextureLayerEXT);
	CALL_FUNCTION(glFramebufferTextureLayerEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFreeObjectBufferATI,(GLuint),void);
value glstub_glFreeObjectBufferATI(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glFreeObjectBufferATI);
	CALL_FUNCTION(glFreeObjectBufferATI)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFrontFace,(GLenum),void);
value glstub_glFrontFace(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glFrontFace);
	CALL_FUNCTION(glFrontFace)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glFrustum,(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glFrustum(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	GLdouble lv5 = Double_val(v5);
	LOAD_FUNCTION(glFrustum);
	CALL_FUNCTION(glFrustum)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glFrustum_byte(value * argv, int n)
{
	return glstub_glFrustum(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glFrustumfOES,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glFrustumfOES(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glFrustumfOES);
	CALL_FUNCTION(glFrustumfOES)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glFrustumfOES_byte(value * argv, int n)
{
	return glstub_glFrustumfOES(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glGenAsyncMarkersSGIX,(GLsizei),GLuint);
value glstub_glGenAsyncMarkersSGIX(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint ret;
	LOAD_FUNCTION(glGenAsyncMarkersSGIX);
	ret = CALL_FUNCTION(glGenAsyncMarkersSGIX)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGenBuffers,(GLsizei, GLuint*),void);
value glstub_glGenBuffers(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenBuffers);
	CALL_FUNCTION(glGenBuffers)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenBuffersARB,(GLsizei, GLuint*),void);
value glstub_glGenBuffersARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenBuffersARB);
	CALL_FUNCTION(glGenBuffersARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenFencesAPPLE,(GLsizei, GLuint*),void);
value glstub_glGenFencesAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenFencesAPPLE);
	CALL_FUNCTION(glGenFencesAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenFencesNV,(GLsizei, GLuint*),void);
value glstub_glGenFencesNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenFencesNV);
	CALL_FUNCTION(glGenFencesNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenFragmentShadersATI,(GLuint),GLuint);
value glstub_glGenFragmentShadersATI(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLuint ret;
	LOAD_FUNCTION(glGenFragmentShadersATI);
	ret = CALL_FUNCTION(glGenFragmentShadersATI)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGenFramebuffersEXT,(GLsizei, GLuint*),void);
value glstub_glGenFramebuffersEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenFramebuffersEXT);
	CALL_FUNCTION(glGenFramebuffersEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenLists,(GLsizei),GLuint);
value glstub_glGenLists(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint ret;
	LOAD_FUNCTION(glGenLists);
	ret = CALL_FUNCTION(glGenLists)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGenOcclusionQueriesNV,(GLsizei, GLuint*),void);
value glstub_glGenOcclusionQueriesNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenOcclusionQueriesNV);
	CALL_FUNCTION(glGenOcclusionQueriesNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenProgramsARB,(GLsizei, GLuint*),void);
value glstub_glGenProgramsARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenProgramsARB);
	CALL_FUNCTION(glGenProgramsARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenProgramsNV,(GLsizei, GLuint*),void);
value glstub_glGenProgramsNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenProgramsNV);
	CALL_FUNCTION(glGenProgramsNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenQueries,(GLsizei, GLuint*),void);
value glstub_glGenQueries(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenQueries);
	CALL_FUNCTION(glGenQueries)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenQueriesARB,(GLsizei, GLuint*),void);
value glstub_glGenQueriesARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenQueriesARB);
	CALL_FUNCTION(glGenQueriesARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenRenderbuffersEXT,(GLsizei, GLuint*),void);
value glstub_glGenRenderbuffersEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenRenderbuffersEXT);
	CALL_FUNCTION(glGenRenderbuffersEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenSymbolsEXT,(GLenum, GLenum, GLenum, GLuint),GLuint);
value glstub_glGenSymbolsEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint ret;
	LOAD_FUNCTION(glGenSymbolsEXT);
	ret = CALL_FUNCTION(glGenSymbolsEXT)(lv0, lv1, lv2, lv3);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGenTextures,(GLsizei, GLuint*),void);
value glstub_glGenTextures(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenTextures);
	CALL_FUNCTION(glGenTextures)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenTexturesEXT,(GLsizei, GLuint*),void);
value glstub_glGenTexturesEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenTexturesEXT);
	CALL_FUNCTION(glGenTexturesEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenVertexArrays,(GLsizei, GLuint*),void);
value glstub_glGenVertexArrays(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenVertexArrays);
	CALL_FUNCTION(glGenVertexArrays)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenVertexArraysAPPLE,(GLsizei, GLuint*),void);
value glstub_glGenVertexArraysAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGenVertexArraysAPPLE);
	CALL_FUNCTION(glGenVertexArraysAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGenVertexShadersEXT,(GLuint),GLuint);
value glstub_glGenVertexShadersEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLuint ret;
	LOAD_FUNCTION(glGenVertexShadersEXT);
	ret = CALL_FUNCTION(glGenVertexShadersEXT)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGenerateMipmapEXT,(GLenum),void);
value glstub_glGenerateMipmapEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glGenerateMipmapEXT);
	CALL_FUNCTION(glGenerateMipmapEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetActiveAttrib,(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*),void);
value glstub_glGetActiveAttrib(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei* lv3 = Data_bigarray_val(v3);
	GLint* lv4 = Data_bigarray_val(v4);
	GLenum* lv5 = Data_bigarray_val(v5);
	GLchar* lv6 = String_val(v6);
	LOAD_FUNCTION(glGetActiveAttrib);
	CALL_FUNCTION(glGetActiveAttrib)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveAttrib_byte(value * argv, int n)
{
	return glstub_glGetActiveAttrib(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glGetActiveAttribARB,(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*),void);
value glstub_glGetActiveAttribARB(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei* lv3 = Data_bigarray_val(v3);
	GLint* lv4 = Data_bigarray_val(v4);
	GLenum* lv5 = Data_bigarray_val(v5);
	GLchar* lv6 = String_val(v6);
	LOAD_FUNCTION(glGetActiveAttribARB);
	CALL_FUNCTION(glGetActiveAttribARB)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveAttribARB_byte(value * argv, int n)
{
	return glstub_glGetActiveAttribARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glGetActiveUniform,(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*),void);
value glstub_glGetActiveUniform(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei* lv3 = Data_bigarray_val(v3);
	GLint* lv4 = Data_bigarray_val(v4);
	GLenum* lv5 = Data_bigarray_val(v5);
	GLchar* lv6 = String_val(v6);
	LOAD_FUNCTION(glGetActiveUniform);
	CALL_FUNCTION(glGetActiveUniform)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveUniform_byte(value * argv, int n)
{
	return glstub_glGetActiveUniform(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glGetActiveUniformARB,(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*),void);
value glstub_glGetActiveUniformARB(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei* lv3 = Data_bigarray_val(v3);
	GLint* lv4 = Data_bigarray_val(v4);
	GLenum* lv5 = Data_bigarray_val(v5);
	GLchar* lv6 = String_val(v6);
	LOAD_FUNCTION(glGetActiveUniformARB);
	CALL_FUNCTION(glGetActiveUniformARB)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveUniformARB_byte(value * argv, int n)
{
	return glstub_glGetActiveUniformARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glGetActiveVaryingNV,(GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*),void);
value glstub_glGetActiveVaryingNV(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei* lv3 = Data_bigarray_val(v3);
	GLsizei* lv4 = Data_bigarray_val(v4);
	GLenum* lv5 = Data_bigarray_val(v5);
	GLchar* lv6 = String_val(v6);
	LOAD_FUNCTION(glGetActiveVaryingNV);
	CALL_FUNCTION(glGetActiveVaryingNV)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveVaryingNV_byte(value * argv, int n)
{
	return glstub_glGetActiveVaryingNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glGetArrayObjectfvATI,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetArrayObjectfvATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetArrayObjectfvATI);
	CALL_FUNCTION(glGetArrayObjectfvATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetArrayObjectivATI,(GLenum, GLenum, GLint*),void);
value glstub_glGetArrayObjectivATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetArrayObjectivATI);
	CALL_FUNCTION(glGetArrayObjectivATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetAttachedObjectsARB,(GLuint, GLsizei, GLsizei*, GLuint*),void);
value glstub_glGetAttachedObjectsARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLuint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetAttachedObjectsARB);
	CALL_FUNCTION(glGetAttachedObjectsARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetAttachedShaders,(GLuint, GLsizei, GLsizei*, GLuint*),void);
value glstub_glGetAttachedShaders(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLuint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetAttachedShaders);
	CALL_FUNCTION(glGetAttachedShaders)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetAttribLocation,(GLuint, GLchar*),GLint);
value glstub_glGetAttribLocation(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	LOAD_FUNCTION(glGetAttribLocation);
	ret = CALL_FUNCTION(glGetAttribLocation)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetAttribLocationARB,(GLuint, GLchar*),GLint);
value glstub_glGetAttribLocationARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	LOAD_FUNCTION(glGetAttribLocationARB);
	ret = CALL_FUNCTION(glGetAttribLocationARB)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetBooleanIndexedvEXT,(GLenum, GLuint, GLboolean*),void);
value glstub_glGetBooleanIndexedvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetBooleanIndexedvEXT);
	CALL_FUNCTION(glGetBooleanIndexedvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetBooleanv,(GLenum, GLboolean*),void);
value glstub_glGetBooleanv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLboolean* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetBooleanv);
	CALL_FUNCTION(glGetBooleanv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetBufferParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glGetBufferParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetBufferParameteriv);
	CALL_FUNCTION(glGetBufferParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetBufferParameterivARB,(GLenum, GLenum, GLint*),void);
value glstub_glGetBufferParameterivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetBufferParameterivARB);
	CALL_FUNCTION(glGetBufferParameterivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetBufferPointerv,(GLenum, GLenum, GLvoid**),void);
value glstub_glGetBufferPointerv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetBufferPointerv);
	CALL_FUNCTION(glGetBufferPointerv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetBufferPointervARB,(GLenum, GLenum, GLvoid**),void);
value glstub_glGetBufferPointervARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetBufferPointervARB);
	CALL_FUNCTION(glGetBufferPointervARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetBufferSubData,(GLenum, GLintptr, GLsizeiptr, GLvoid*),void);
value glstub_glGetBufferSubData(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLintptr lv1 = Int_val(v1);
	GLsizeiptr lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glGetBufferSubData);
	CALL_FUNCTION(glGetBufferSubData)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetBufferSubDataARB,(GLenum, GLintptr, GLsizeiptr, GLvoid*),void);
value glstub_glGetBufferSubDataARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLintptr lv1 = Int_val(v1);
	GLsizeiptr lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glGetBufferSubDataARB);
	CALL_FUNCTION(glGetBufferSubDataARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetClipPlane,(GLenum, GLdouble*),void);
value glstub_glGetClipPlane(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetClipPlane);
	CALL_FUNCTION(glGetClipPlane)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetClipPlanefOES,(GLenum, GLfloat*),void);
value glstub_glGetClipPlanefOES(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetClipPlanefOES);
	CALL_FUNCTION(glGetClipPlanefOES)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTable,(GLenum, GLenum, GLenum, GLvoid*),void);
value glstub_glGetColorTable(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glGetColorTable);
	CALL_FUNCTION(glGetColorTable)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTableEXT,(GLenum, GLenum, GLenum, GLvoid*),void);
value glstub_glGetColorTableEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glGetColorTableEXT);
	CALL_FUNCTION(glGetColorTableEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTableParameterfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetColorTableParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetColorTableParameterfv);
	CALL_FUNCTION(glGetColorTableParameterfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTableParameterfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetColorTableParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetColorTableParameterfvEXT);
	CALL_FUNCTION(glGetColorTableParameterfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTableParameterfvSGI,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetColorTableParameterfvSGI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetColorTableParameterfvSGI);
	CALL_FUNCTION(glGetColorTableParameterfvSGI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTableParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glGetColorTableParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetColorTableParameteriv);
	CALL_FUNCTION(glGetColorTableParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTableParameterivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetColorTableParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetColorTableParameterivEXT);
	CALL_FUNCTION(glGetColorTableParameterivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTableParameterivSGI,(GLenum, GLenum, GLint*),void);
value glstub_glGetColorTableParameterivSGI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetColorTableParameterivSGI);
	CALL_FUNCTION(glGetColorTableParameterivSGI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetColorTableSGI,(GLenum, GLenum, GLenum, GLvoid*),void);
value glstub_glGetColorTableSGI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glGetColorTableSGI);
	CALL_FUNCTION(glGetColorTableSGI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetCombinerInputParameterfvNV,(GLenum, GLenum, GLenum, GLenum, GLfloat*),void);
value glstub_glGetCombinerInputParameterfvNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLfloat* lv4 = Data_bigarray_val(v4);
	LOAD_FUNCTION(glGetCombinerInputParameterfvNV);
	CALL_FUNCTION(glGetCombinerInputParameterfvNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetCombinerInputParameterivNV,(GLenum, GLenum, GLenum, GLenum, GLint*),void);
value glstub_glGetCombinerInputParameterivNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLint* lv4 = Data_bigarray_val(v4);
	LOAD_FUNCTION(glGetCombinerInputParameterivNV);
	CALL_FUNCTION(glGetCombinerInputParameterivNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetCombinerOutputParameterfvNV,(GLenum, GLenum, GLenum, GLfloat*),void);
value glstub_glGetCombinerOutputParameterfvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetCombinerOutputParameterfvNV);
	CALL_FUNCTION(glGetCombinerOutputParameterfvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetCombinerOutputParameterivNV,(GLenum, GLenum, GLenum, GLint*),void);
value glstub_glGetCombinerOutputParameterivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetCombinerOutputParameterivNV);
	CALL_FUNCTION(glGetCombinerOutputParameterivNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetCombinerStageParameterfvNV,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetCombinerStageParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetCombinerStageParameterfvNV);
	CALL_FUNCTION(glGetCombinerStageParameterfvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetCompressedTexImage,(GLenum, GLint, GLvoid*),void);
value glstub_glGetCompressedTexImage(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glGetCompressedTexImage);
	CALL_FUNCTION(glGetCompressedTexImage)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetCompressedTexImageARB,(GLenum, GLint, GLvoid*),void);
value glstub_glGetCompressedTexImageARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glGetCompressedTexImageARB);
	CALL_FUNCTION(glGetCompressedTexImageARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetConvolutionFilter,(GLenum, GLenum, GLenum, GLvoid*),void);
value glstub_glGetConvolutionFilter(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glGetConvolutionFilter);
	CALL_FUNCTION(glGetConvolutionFilter)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetConvolutionFilterEXT,(GLenum, GLenum, GLenum, GLvoid*),void);
value glstub_glGetConvolutionFilterEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glGetConvolutionFilterEXT);
	CALL_FUNCTION(glGetConvolutionFilterEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetConvolutionParameterfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetConvolutionParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetConvolutionParameterfv);
	CALL_FUNCTION(glGetConvolutionParameterfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetConvolutionParameterfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetConvolutionParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetConvolutionParameterfvEXT);
	CALL_FUNCTION(glGetConvolutionParameterfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetConvolutionParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glGetConvolutionParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetConvolutionParameteriv);
	CALL_FUNCTION(glGetConvolutionParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetConvolutionParameterivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetConvolutionParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetConvolutionParameterivEXT);
	CALL_FUNCTION(glGetConvolutionParameterivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetDetailTexFuncSGIS,(GLenum, GLfloat*),void);
value glstub_glGetDetailTexFuncSGIS(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetDetailTexFuncSGIS);
	CALL_FUNCTION(glGetDetailTexFuncSGIS)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetDoublev,(GLenum, GLdouble*),void);
value glstub_glGetDoublev(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetDoublev);
	CALL_FUNCTION(glGetDoublev)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetError,(void),GLenum);
value glstub_glGetError(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum ret;
	LOAD_FUNCTION(glGetError);
	ret = CALL_FUNCTION(glGetError)();
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetFenceivNV,(GLuint, GLenum, GLint*),void);
value glstub_glGetFenceivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFenceivNV);
	CALL_FUNCTION(glGetFenceivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFinalCombinerInputParameterfvNV,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetFinalCombinerInputParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFinalCombinerInputParameterfvNV);
	CALL_FUNCTION(glGetFinalCombinerInputParameterfvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFinalCombinerInputParameterivNV,(GLenum, GLenum, GLint*),void);
value glstub_glGetFinalCombinerInputParameterivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFinalCombinerInputParameterivNV);
	CALL_FUNCTION(glGetFinalCombinerInputParameterivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFloatv,(GLenum, GLfloat*),void);
value glstub_glGetFloatv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetFloatv);
	CALL_FUNCTION(glGetFloatv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFogFuncSGIS,(GLfloat*),void);
value glstub_glGetFogFuncSGIS(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glGetFogFuncSGIS);
	CALL_FUNCTION(glGetFogFuncSGIS)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFragDataLocationEXT,(GLuint, GLchar*),GLint);
value glstub_glGetFragDataLocationEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	LOAD_FUNCTION(glGetFragDataLocationEXT);
	ret = CALL_FUNCTION(glGetFragDataLocationEXT)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetFragmentLightfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetFragmentLightfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFragmentLightfvEXT);
	CALL_FUNCTION(glGetFragmentLightfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFragmentLightfvSGIX,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetFragmentLightfvSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFragmentLightfvSGIX);
	CALL_FUNCTION(glGetFragmentLightfvSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFragmentLightivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetFragmentLightivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFragmentLightivEXT);
	CALL_FUNCTION(glGetFragmentLightivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFragmentLightivSGIX,(GLenum, GLenum, GLint*),void);
value glstub_glGetFragmentLightivSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFragmentLightivSGIX);
	CALL_FUNCTION(glGetFragmentLightivSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFragmentMaterialfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetFragmentMaterialfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFragmentMaterialfvEXT);
	CALL_FUNCTION(glGetFragmentMaterialfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFragmentMaterialfvSGIX,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetFragmentMaterialfvSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFragmentMaterialfvSGIX);
	CALL_FUNCTION(glGetFragmentMaterialfvSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFragmentMaterialivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetFragmentMaterialivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFragmentMaterialivEXT);
	CALL_FUNCTION(glGetFragmentMaterialivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFragmentMaterialivSGIX,(GLenum, GLenum, GLint*),void);
value glstub_glGetFragmentMaterialivSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetFragmentMaterialivSGIX);
	CALL_FUNCTION(glGetFragmentMaterialivSGIX)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetFramebufferAttachmentParameterivEXT,(GLenum, GLenum, GLenum, GLint*),void);
value glstub_glGetFramebufferAttachmentParameterivEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetFramebufferAttachmentParameterivEXT);
	CALL_FUNCTION(glGetFramebufferAttachmentParameterivEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetHandleARB,(GLenum),GLuint);
value glstub_glGetHandleARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint ret;
	LOAD_FUNCTION(glGetHandleARB);
	ret = CALL_FUNCTION(glGetHandleARB)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetHistogram,(GLenum, GLboolean, GLenum, GLenum, GLvoid*),void);
value glstub_glGetHistogram(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glGetHistogram);
	CALL_FUNCTION(glGetHistogram)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetHistogramEXT,(GLenum, GLboolean, GLenum, GLenum, GLvoid*),void);
value glstub_glGetHistogramEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glGetHistogramEXT);
	CALL_FUNCTION(glGetHistogramEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetHistogramParameterfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetHistogramParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetHistogramParameterfv);
	CALL_FUNCTION(glGetHistogramParameterfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetHistogramParameterfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetHistogramParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetHistogramParameterfvEXT);
	CALL_FUNCTION(glGetHistogramParameterfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetHistogramParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glGetHistogramParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetHistogramParameteriv);
	CALL_FUNCTION(glGetHistogramParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetHistogramParameterivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetHistogramParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetHistogramParameterivEXT);
	CALL_FUNCTION(glGetHistogramParameterivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetImageTransformParameterfvHP,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetImageTransformParameterfvHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetImageTransformParameterfvHP);
	CALL_FUNCTION(glGetImageTransformParameterfvHP)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetImageTransformParameterivHP,(GLenum, GLenum, GLint*),void);
value glstub_glGetImageTransformParameterivHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetImageTransformParameterivHP);
	CALL_FUNCTION(glGetImageTransformParameterivHP)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetInfoLogARB,(GLuint, GLsizei, GLsizei*, GLchar*),void);
value glstub_glGetInfoLogARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	LOAD_FUNCTION(glGetInfoLogARB);
	CALL_FUNCTION(glGetInfoLogARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetIntegerIndexedvEXT,(GLenum, GLuint, GLint*),void);
value glstub_glGetIntegerIndexedvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetIntegerIndexedvEXT);
	CALL_FUNCTION(glGetIntegerIndexedvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetIntegerv,(GLenum, GLint*),void);
value glstub_glGetIntegerv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetIntegerv);
	CALL_FUNCTION(glGetIntegerv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetInvariantBooleanvEXT,(GLuint, GLenum, GLboolean*),void);
value glstub_glGetInvariantBooleanvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetInvariantBooleanvEXT);
	CALL_FUNCTION(glGetInvariantBooleanvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetInvariantFloatvEXT,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetInvariantFloatvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetInvariantFloatvEXT);
	CALL_FUNCTION(glGetInvariantFloatvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetInvariantIntegervEXT,(GLuint, GLenum, GLint*),void);
value glstub_glGetInvariantIntegervEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetInvariantIntegervEXT);
	CALL_FUNCTION(glGetInvariantIntegervEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetLightfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetLightfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetLightfv);
	CALL_FUNCTION(glGetLightfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetLightiv,(GLenum, GLenum, GLint*),void);
value glstub_glGetLightiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetLightiv);
	CALL_FUNCTION(glGetLightiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetLocalConstantBooleanvEXT,(GLuint, GLenum, GLboolean*),void);
value glstub_glGetLocalConstantBooleanvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetLocalConstantBooleanvEXT);
	CALL_FUNCTION(glGetLocalConstantBooleanvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetLocalConstantFloatvEXT,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetLocalConstantFloatvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetLocalConstantFloatvEXT);
	CALL_FUNCTION(glGetLocalConstantFloatvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetLocalConstantIntegervEXT,(GLuint, GLenum, GLint*),void);
value glstub_glGetLocalConstantIntegervEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetLocalConstantIntegervEXT);
	CALL_FUNCTION(glGetLocalConstantIntegervEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMapAttribParameterfvNV,(GLenum, GLuint, GLenum, GLfloat*),void);
value glstub_glGetMapAttribParameterfvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetMapAttribParameterfvNV);
	CALL_FUNCTION(glGetMapAttribParameterfvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMapAttribParameterivNV,(GLenum, GLuint, GLenum, GLint*),void);
value glstub_glGetMapAttribParameterivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetMapAttribParameterivNV);
	CALL_FUNCTION(glGetMapAttribParameterivNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMapControlPointsNV,(GLenum, GLuint, GLenum, GLsizei, GLsizei, GLboolean, GLvoid*),void);
value glstub_glGetMapControlPointsNV(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLboolean lv5 = Bool_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glGetMapControlPointsNV);
	CALL_FUNCTION(glGetMapControlPointsNV)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetMapControlPointsNV_byte(value * argv, int n)
{
	return glstub_glGetMapControlPointsNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glGetMapParameterfvNV,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetMapParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMapParameterfvNV);
	CALL_FUNCTION(glGetMapParameterfvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMapParameterivNV,(GLenum, GLenum, GLint*),void);
value glstub_glGetMapParameterivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMapParameterivNV);
	CALL_FUNCTION(glGetMapParameterivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMapdv,(GLenum, GLenum, GLdouble*),void);
value glstub_glGetMapdv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMapdv);
	CALL_FUNCTION(glGetMapdv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMapfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetMapfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMapfv);
	CALL_FUNCTION(glGetMapfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMapiv,(GLenum, GLenum, GLint*),void);
value glstub_glGetMapiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMapiv);
	CALL_FUNCTION(glGetMapiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMaterialfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetMaterialfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMaterialfv);
	CALL_FUNCTION(glGetMaterialfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMaterialiv,(GLenum, GLenum, GLint*),void);
value glstub_glGetMaterialiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMaterialiv);
	CALL_FUNCTION(glGetMaterialiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMinmax,(GLenum, GLboolean, GLenum, GLenum, GLvoid*),void);
value glstub_glGetMinmax(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glGetMinmax);
	CALL_FUNCTION(glGetMinmax)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMinmaxEXT,(GLenum, GLboolean, GLenum, GLenum, GLvoid*),void);
value glstub_glGetMinmaxEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glGetMinmaxEXT);
	CALL_FUNCTION(glGetMinmaxEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMinmaxParameterfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetMinmaxParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMinmaxParameterfv);
	CALL_FUNCTION(glGetMinmaxParameterfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMinmaxParameterfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetMinmaxParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMinmaxParameterfvEXT);
	CALL_FUNCTION(glGetMinmaxParameterfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMinmaxParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glGetMinmaxParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMinmaxParameteriv);
	CALL_FUNCTION(glGetMinmaxParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetMinmaxParameterivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetMinmaxParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetMinmaxParameterivEXT);
	CALL_FUNCTION(glGetMinmaxParameterivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetObjectBufferfvATI,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetObjectBufferfvATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetObjectBufferfvATI);
	CALL_FUNCTION(glGetObjectBufferfvATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetObjectBufferivATI,(GLuint, GLenum, GLint*),void);
value glstub_glGetObjectBufferivATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetObjectBufferivATI);
	CALL_FUNCTION(glGetObjectBufferivATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetObjectParameterfvARB,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetObjectParameterfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetObjectParameterfvARB);
	CALL_FUNCTION(glGetObjectParameterfvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetObjectParameterivARB,(GLuint, GLenum, GLint*),void);
value glstub_glGetObjectParameterivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetObjectParameterivARB);
	CALL_FUNCTION(glGetObjectParameterivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetOcclusionQueryivNV,(GLuint, GLenum, GLint*),void);
value glstub_glGetOcclusionQueryivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetOcclusionQueryivNV);
	CALL_FUNCTION(glGetOcclusionQueryivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetOcclusionQueryuivNV,(GLuint, GLenum, GLuint*),void);
value glstub_glGetOcclusionQueryuivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetOcclusionQueryuivNV);
	CALL_FUNCTION(glGetOcclusionQueryuivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetPixelMapfv,(GLenum, GLfloat*),void);
value glstub_glGetPixelMapfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetPixelMapfv);
	CALL_FUNCTION(glGetPixelMapfv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetPixelMapuiv,(GLenum, GLuint*),void);
value glstub_glGetPixelMapuiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetPixelMapuiv);
	CALL_FUNCTION(glGetPixelMapuiv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetPixelMapusv,(GLenum, GLushort*),void);
value glstub_glGetPixelMapusv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetPixelMapusv);
	CALL_FUNCTION(glGetPixelMapusv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetPixelTransformParameterfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetPixelTransformParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetPixelTransformParameterfvEXT);
	CALL_FUNCTION(glGetPixelTransformParameterfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetPixelTransformParameterivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetPixelTransformParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetPixelTransformParameterivEXT);
	CALL_FUNCTION(glGetPixelTransformParameterivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetPointerv,(GLenum, GLvoid**),void);
value glstub_glGetPointerv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid** lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetPointerv);
	CALL_FUNCTION(glGetPointerv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetPolygonStipple,(GLubyte*),void);
value glstub_glGetPolygonStipple(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glGetPolygonStipple);
	CALL_FUNCTION(glGetPolygonStipple)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramEnvParameterdvARB,(GLenum, GLuint, GLdouble*),void);
value glstub_glGetProgramEnvParameterdvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetProgramEnvParameterdvARB);
	CALL_FUNCTION(glGetProgramEnvParameterdvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramEnvParameterfvARB,(GLenum, GLuint, GLfloat*),void);
value glstub_glGetProgramEnvParameterfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetProgramEnvParameterfvARB);
	CALL_FUNCTION(glGetProgramEnvParameterfvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramInfoLog,(GLuint, GLsizei, GLsizei*, GLchar*),void);
value glstub_glGetProgramInfoLog(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	LOAD_FUNCTION(glGetProgramInfoLog);
	CALL_FUNCTION(glGetProgramInfoLog)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramLocalParameterdvARB,(GLenum, GLuint, GLdouble*),void);
value glstub_glGetProgramLocalParameterdvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetProgramLocalParameterdvARB);
	CALL_FUNCTION(glGetProgramLocalParameterdvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramLocalParameterfvARB,(GLenum, GLuint, GLfloat*),void);
value glstub_glGetProgramLocalParameterfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetProgramLocalParameterfvARB);
	CALL_FUNCTION(glGetProgramLocalParameterfvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramNamedParameterdvNV,(GLuint, GLsizei, GLubyte*, GLdouble*),void);
value glstub_glGetProgramNamedParameterdvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLdouble* lv3 = (Tag_val(v3) == Double_array_tag)? (double *)v3: Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetProgramNamedParameterdvNV);
	CALL_FUNCTION(glGetProgramNamedParameterdvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramNamedParameterfvNV,(GLuint, GLsizei, GLubyte*, GLfloat*),void);
value glstub_glGetProgramNamedParameterfvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetProgramNamedParameterfvNV);
	CALL_FUNCTION(glGetProgramNamedParameterfvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramParameterdvNV,(GLenum, GLuint, GLenum, GLdouble*),void);
value glstub_glGetProgramParameterdvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLdouble* lv3 = (Tag_val(v3) == Double_array_tag)? (double *)v3: Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetProgramParameterdvNV);
	CALL_FUNCTION(glGetProgramParameterdvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramParameterfvNV,(GLenum, GLuint, GLenum, GLfloat*),void);
value glstub_glGetProgramParameterfvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetProgramParameterfvNV);
	CALL_FUNCTION(glGetProgramParameterfvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramStringARB,(GLenum, GLenum, GLvoid*),void);
value glstub_glGetProgramStringARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glGetProgramStringARB);
	CALL_FUNCTION(glGetProgramStringARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramStringNV,(GLuint, GLenum, GLubyte*),void);
value glstub_glGetProgramStringNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetProgramStringNV);
	CALL_FUNCTION(glGetProgramStringNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramiv,(GLuint, GLenum, GLint*),void);
value glstub_glGetProgramiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetProgramiv);
	CALL_FUNCTION(glGetProgramiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramivARB,(GLenum, GLenum, GLint*),void);
value glstub_glGetProgramivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetProgramivARB);
	CALL_FUNCTION(glGetProgramivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetProgramivNV,(GLuint, GLenum, GLint*),void);
value glstub_glGetProgramivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetProgramivNV);
	CALL_FUNCTION(glGetProgramivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetQueryObjectiv,(GLuint, GLenum, GLint*),void);
value glstub_glGetQueryObjectiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetQueryObjectiv);
	CALL_FUNCTION(glGetQueryObjectiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetQueryObjectivARB,(GLuint, GLenum, GLint*),void);
value glstub_glGetQueryObjectivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetQueryObjectivARB);
	CALL_FUNCTION(glGetQueryObjectivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetQueryObjectuiv,(GLuint, GLenum, GLuint*),void);
value glstub_glGetQueryObjectuiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetQueryObjectuiv);
	CALL_FUNCTION(glGetQueryObjectuiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetQueryObjectuivARB,(GLuint, GLenum, GLuint*),void);
value glstub_glGetQueryObjectuivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetQueryObjectuivARB);
	CALL_FUNCTION(glGetQueryObjectuivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetQueryiv,(GLenum, GLenum, GLint*),void);
value glstub_glGetQueryiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetQueryiv);
	CALL_FUNCTION(glGetQueryiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetQueryivARB,(GLenum, GLenum, GLint*),void);
value glstub_glGetQueryivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetQueryivARB);
	CALL_FUNCTION(glGetQueryivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetRenderbufferParameterivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetRenderbufferParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetRenderbufferParameterivEXT);
	CALL_FUNCTION(glGetRenderbufferParameterivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetSeparableFilter,(GLenum, GLenum, GLenum, GLvoid*, GLvoid*, GLvoid*),void);
value glstub_glGetSeparableFilter(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glGetSeparableFilter);
	CALL_FUNCTION(glGetSeparableFilter)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glGetSeparableFilter_byte(value * argv, int n)
{
	return glstub_glGetSeparableFilter(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glGetSeparableFilterEXT,(GLenum, GLenum, GLenum, GLvoid*, GLvoid*, GLvoid*),void);
value glstub_glGetSeparableFilterEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glGetSeparableFilterEXT);
	CALL_FUNCTION(glGetSeparableFilterEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glGetSeparableFilterEXT_byte(value * argv, int n)
{
	return glstub_glGetSeparableFilterEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glGetShaderInfoLog,(GLuint, GLsizei, GLsizei*, GLchar*),void);
value glstub_glGetShaderInfoLog(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	LOAD_FUNCTION(glGetShaderInfoLog);
	CALL_FUNCTION(glGetShaderInfoLog)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetShaderSource,(GLint, GLsizei, GLsizei*, GLchar*),void);
value glstub_glGetShaderSource(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	LOAD_FUNCTION(glGetShaderSource);
	CALL_FUNCTION(glGetShaderSource)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetShaderSourceARB,(GLuint, GLsizei, GLsizei*, GLchar*),void);
value glstub_glGetShaderSourceARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	LOAD_FUNCTION(glGetShaderSourceARB);
	CALL_FUNCTION(glGetShaderSourceARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetShaderiv,(GLuint, GLenum, GLint*),void);
value glstub_glGetShaderiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetShaderiv);
	CALL_FUNCTION(glGetShaderiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetSharpenTexFuncSGIS,(GLenum, GLfloat*),void);
value glstub_glGetSharpenTexFuncSGIS(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetSharpenTexFuncSGIS);
	CALL_FUNCTION(glGetSharpenTexFuncSGIS)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetString,(GLenum),GLstring);
value glstub_glGetString(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLstring ret;
	LOAD_FUNCTION(glGetString);
	ret = CALL_FUNCTION(glGetString)(lv0);
	result = caml_copy_string(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetTexBumpParameterfvATI,(GLenum, GLfloat*),void);
value glstub_glGetTexBumpParameterfvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetTexBumpParameterfvATI);
	CALL_FUNCTION(glGetTexBumpParameterfvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexBumpParameterivATI,(GLenum, GLint*),void);
value glstub_glGetTexBumpParameterivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glGetTexBumpParameterivATI);
	CALL_FUNCTION(glGetTexBumpParameterivATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexEnvfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetTexEnvfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexEnvfv);
	CALL_FUNCTION(glGetTexEnvfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexEnviv,(GLenum, GLenum, GLint*),void);
value glstub_glGetTexEnviv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexEnviv);
	CALL_FUNCTION(glGetTexEnviv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexFilterFuncSGIS,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetTexFilterFuncSGIS(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexFilterFuncSGIS);
	CALL_FUNCTION(glGetTexFilterFuncSGIS)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexGendv,(GLenum, GLenum, GLdouble*),void);
value glstub_glGetTexGendv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexGendv);
	CALL_FUNCTION(glGetTexGendv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexGenfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetTexGenfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexGenfv);
	CALL_FUNCTION(glGetTexGenfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexGeniv,(GLenum, GLenum, GLint*),void);
value glstub_glGetTexGeniv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexGeniv);
	CALL_FUNCTION(glGetTexGeniv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexImage,(GLenum, GLint, GLenum, GLenum, GLvoid*),void);
value glstub_glGetTexImage(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glGetTexImage);
	CALL_FUNCTION(glGetTexImage)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexLevelParameterfv,(GLenum, GLint, GLenum, GLfloat*),void);
value glstub_glGetTexLevelParameterfv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetTexLevelParameterfv);
	CALL_FUNCTION(glGetTexLevelParameterfv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexLevelParameteriv,(GLenum, GLint, GLenum, GLint*),void);
value glstub_glGetTexLevelParameteriv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetTexLevelParameteriv);
	CALL_FUNCTION(glGetTexLevelParameteriv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexParameterIivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glGetTexParameterIivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexParameterIivEXT);
	CALL_FUNCTION(glGetTexParameterIivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexParameterIuivEXT,(GLenum, GLenum, GLuint*),void);
value glstub_glGetTexParameterIuivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexParameterIuivEXT);
	CALL_FUNCTION(glGetTexParameterIuivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexParameterPointervAPPLE,(GLenum, GLenum, GLvoid**),void);
value glstub_glGetTexParameterPointervAPPLE(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexParameterPointervAPPLE);
	CALL_FUNCTION(glGetTexParameterPointervAPPLE)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexParameterfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glGetTexParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexParameterfv);
	CALL_FUNCTION(glGetTexParameterfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTexParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glGetTexParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTexParameteriv);
	CALL_FUNCTION(glGetTexParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTrackMatrixivNV,(GLenum, GLuint, GLenum, GLint*),void);
value glstub_glGetTrackMatrixivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glGetTrackMatrixivNV);
	CALL_FUNCTION(glGetTrackMatrixivNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetTransformFeedbackVaryingNV,(GLuint, GLuint, GLint*),void);
value glstub_glGetTransformFeedbackVaryingNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetTransformFeedbackVaryingNV);
	CALL_FUNCTION(glGetTransformFeedbackVaryingNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetUniformBufferSizeEXT,(GLuint, GLint),GLint);
value glstub_glGetUniformBufferSizeEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint ret;
	LOAD_FUNCTION(glGetUniformBufferSizeEXT);
	ret = CALL_FUNCTION(glGetUniformBufferSizeEXT)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetUniformLocation,(GLint, GLchar*),GLint);
value glstub_glGetUniformLocation(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	LOAD_FUNCTION(glGetUniformLocation);
	ret = CALL_FUNCTION(glGetUniformLocation)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetUniformLocationARB,(GLuint, GLchar*),GLint);
value glstub_glGetUniformLocationARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	LOAD_FUNCTION(glGetUniformLocationARB);
	ret = CALL_FUNCTION(glGetUniformLocationARB)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetUniformOffsetEXT,(GLuint, GLint),GLintptr);
value glstub_glGetUniformOffsetEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLintptr ret;
	LOAD_FUNCTION(glGetUniformOffsetEXT);
	ret = CALL_FUNCTION(glGetUniformOffsetEXT)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetUniformfv,(GLuint, GLint, GLfloat*),void);
value glstub_glGetUniformfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetUniformfv);
	CALL_FUNCTION(glGetUniformfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetUniformfvARB,(GLuint, GLint, GLfloat*),void);
value glstub_glGetUniformfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetUniformfvARB);
	CALL_FUNCTION(glGetUniformfvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetUniformiv,(GLuint, GLint, GLint*),void);
value glstub_glGetUniformiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetUniformiv);
	CALL_FUNCTION(glGetUniformiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetUniformivARB,(GLuint, GLint, GLint*),void);
value glstub_glGetUniformivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetUniformivARB);
	CALL_FUNCTION(glGetUniformivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetUniformuivEXT,(GLuint, GLint, GLuint*),void);
value glstub_glGetUniformuivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetUniformuivEXT);
	CALL_FUNCTION(glGetUniformuivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVariantArrayObjectfvATI,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetVariantArrayObjectfvATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVariantArrayObjectfvATI);
	CALL_FUNCTION(glGetVariantArrayObjectfvATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVariantArrayObjectivATI,(GLuint, GLenum, GLint*),void);
value glstub_glGetVariantArrayObjectivATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVariantArrayObjectivATI);
	CALL_FUNCTION(glGetVariantArrayObjectivATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVariantBooleanvEXT,(GLuint, GLenum, GLboolean*),void);
value glstub_glGetVariantBooleanvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVariantBooleanvEXT);
	CALL_FUNCTION(glGetVariantBooleanvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVariantFloatvEXT,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetVariantFloatvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVariantFloatvEXT);
	CALL_FUNCTION(glGetVariantFloatvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVariantIntegervEXT,(GLuint, GLenum, GLint*),void);
value glstub_glGetVariantIntegervEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVariantIntegervEXT);
	CALL_FUNCTION(glGetVariantIntegervEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVariantPointervEXT,(GLuint, GLenum, GLvoid**),void);
value glstub_glGetVariantPointervEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVariantPointervEXT);
	CALL_FUNCTION(glGetVariantPointervEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVaryingLocationNV,(GLuint, GLchar*),GLint);
value glstub_glGetVaryingLocationNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	LOAD_FUNCTION(glGetVaryingLocationNV);
	ret = CALL_FUNCTION(glGetVaryingLocationNV)(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glGetVertexAttribArrayObjectfvATI,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetVertexAttribArrayObjectfvATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribArrayObjectfvATI);
	CALL_FUNCTION(glGetVertexAttribArrayObjectfvATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribArrayObjectivATI,(GLuint, GLenum, GLint*),void);
value glstub_glGetVertexAttribArrayObjectivATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribArrayObjectivATI);
	CALL_FUNCTION(glGetVertexAttribArrayObjectivATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribIivEXT,(GLuint, GLenum, GLint*),void);
value glstub_glGetVertexAttribIivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribIivEXT);
	CALL_FUNCTION(glGetVertexAttribIivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribIuivEXT,(GLuint, GLenum, GLuint*),void);
value glstub_glGetVertexAttribIuivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribIuivEXT);
	CALL_FUNCTION(glGetVertexAttribIuivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribPointerv,(GLuint, GLenum, GLvoid*),void);
value glstub_glGetVertexAttribPointerv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glGetVertexAttribPointerv);
	CALL_FUNCTION(glGetVertexAttribPointerv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribPointervARB,(GLuint, GLenum, GLvoid**),void);
value glstub_glGetVertexAttribPointervARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribPointervARB);
	CALL_FUNCTION(glGetVertexAttribPointervARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribPointervNV,(GLuint, GLenum, GLvoid**),void);
value glstub_glGetVertexAttribPointervNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribPointervNV);
	CALL_FUNCTION(glGetVertexAttribPointervNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribdv,(GLuint, GLenum, GLdouble*),void);
value glstub_glGetVertexAttribdv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribdv);
	CALL_FUNCTION(glGetVertexAttribdv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribdvARB,(GLuint, GLenum, GLdouble*),void);
value glstub_glGetVertexAttribdvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribdvARB);
	CALL_FUNCTION(glGetVertexAttribdvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribdvNV,(GLuint, GLenum, GLdouble*),void);
value glstub_glGetVertexAttribdvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribdvNV);
	CALL_FUNCTION(glGetVertexAttribdvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribfv,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetVertexAttribfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribfv);
	CALL_FUNCTION(glGetVertexAttribfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribfvARB,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetVertexAttribfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribfvARB);
	CALL_FUNCTION(glGetVertexAttribfvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribfvNV,(GLuint, GLenum, GLfloat*),void);
value glstub_glGetVertexAttribfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribfvNV);
	CALL_FUNCTION(glGetVertexAttribfvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribiv,(GLuint, GLenum, GLint*),void);
value glstub_glGetVertexAttribiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribiv);
	CALL_FUNCTION(glGetVertexAttribiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribivARB,(GLuint, GLenum, GLint*),void);
value glstub_glGetVertexAttribivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribivARB);
	CALL_FUNCTION(glGetVertexAttribivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGetVertexAttribivNV,(GLuint, GLenum, GLint*),void);
value glstub_glGetVertexAttribivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glGetVertexAttribivNV);
	CALL_FUNCTION(glGetVertexAttribivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGlobalAlphaFactorbSUN,(GLbyte),void);
value glstub_glGlobalAlphaFactorbSUN(value v0)
{
	CAMLparam1(v0);
	GLbyte lv0 = Int_val(v0);
	LOAD_FUNCTION(glGlobalAlphaFactorbSUN);
	CALL_FUNCTION(glGlobalAlphaFactorbSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGlobalAlphaFactordSUN,(GLdouble),void);
value glstub_glGlobalAlphaFactordSUN(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	LOAD_FUNCTION(glGlobalAlphaFactordSUN);
	CALL_FUNCTION(glGlobalAlphaFactordSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGlobalAlphaFactorfSUN,(GLfloat),void);
value glstub_glGlobalAlphaFactorfSUN(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glGlobalAlphaFactorfSUN);
	CALL_FUNCTION(glGlobalAlphaFactorfSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGlobalAlphaFactoriSUN,(GLint),void);
value glstub_glGlobalAlphaFactoriSUN(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glGlobalAlphaFactoriSUN);
	CALL_FUNCTION(glGlobalAlphaFactoriSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGlobalAlphaFactorsSUN,(GLshort),void);
value glstub_glGlobalAlphaFactorsSUN(value v0)
{
	CAMLparam1(v0);
	GLshort lv0 = Int_val(v0);
	LOAD_FUNCTION(glGlobalAlphaFactorsSUN);
	CALL_FUNCTION(glGlobalAlphaFactorsSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGlobalAlphaFactorubSUN,(GLubyte),void);
value glstub_glGlobalAlphaFactorubSUN(value v0)
{
	CAMLparam1(v0);
	GLubyte lv0 = Int_val(v0);
	LOAD_FUNCTION(glGlobalAlphaFactorubSUN);
	CALL_FUNCTION(glGlobalAlphaFactorubSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGlobalAlphaFactoruiSUN,(GLuint),void);
value glstub_glGlobalAlphaFactoruiSUN(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glGlobalAlphaFactoruiSUN);
	CALL_FUNCTION(glGlobalAlphaFactoruiSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glGlobalAlphaFactorusSUN,(GLushort),void);
value glstub_glGlobalAlphaFactorusSUN(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	LOAD_FUNCTION(glGlobalAlphaFactorusSUN);
	CALL_FUNCTION(glGlobalAlphaFactorusSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glHint,(GLenum, GLenum),void);
value glstub_glHint(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glHint);
	CALL_FUNCTION(glHint)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glHistogram,(GLenum, GLsizei, GLenum, GLboolean),void);
value glstub_glHistogram(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLboolean lv3 = Bool_val(v3);
	LOAD_FUNCTION(glHistogram);
	CALL_FUNCTION(glHistogram)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glHistogramEXT,(GLenum, GLsizei, GLenum, GLboolean),void);
value glstub_glHistogramEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLboolean lv3 = Bool_val(v3);
	LOAD_FUNCTION(glHistogramEXT);
	CALL_FUNCTION(glHistogramEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glImageTransformParameterfHP,(GLenum, GLenum, GLfloat),void);
value glstub_glImageTransformParameterfHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glImageTransformParameterfHP);
	CALL_FUNCTION(glImageTransformParameterfHP)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glImageTransformParameterfvHP,(GLenum, GLenum, GLfloat*),void);
value glstub_glImageTransformParameterfvHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glImageTransformParameterfvHP);
	CALL_FUNCTION(glImageTransformParameterfvHP)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glImageTransformParameteriHP,(GLenum, GLenum, GLint),void);
value glstub_glImageTransformParameteriHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glImageTransformParameteriHP);
	CALL_FUNCTION(glImageTransformParameteriHP)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glImageTransformParameterivHP,(GLenum, GLenum, GLint*),void);
value glstub_glImageTransformParameterivHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glImageTransformParameterivHP);
	CALL_FUNCTION(glImageTransformParameterivHP)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexFuncEXT,(GLenum, GLfloat),void);
value glstub_glIndexFuncEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glIndexFuncEXT);
	CALL_FUNCTION(glIndexFuncEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexMask,(GLuint),void);
value glstub_glIndexMask(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glIndexMask);
	CALL_FUNCTION(glIndexMask)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexMaterialEXT,(GLenum, GLenum),void);
value glstub_glIndexMaterialEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glIndexMaterialEXT);
	CALL_FUNCTION(glIndexMaterialEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexPointer,(GLenum, GLsizei, GLvoid*),void);
value glstub_glIndexPointer(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glIndexPointer);
	CALL_FUNCTION(glIndexPointer)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexPointerEXT,(GLenum, GLsizei, GLsizei, GLvoid*),void);
value glstub_glIndexPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glIndexPointerEXT);
	CALL_FUNCTION(glIndexPointerEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexPointerListIBM,(GLenum, GLint, GLvoid**, GLint),void);
value glstub_glIndexPointerListIBM(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glIndexPointerListIBM);
	CALL_FUNCTION(glIndexPointerListIBM)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexd,(GLdouble),void);
value glstub_glIndexd(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	LOAD_FUNCTION(glIndexd);
	CALL_FUNCTION(glIndexd)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexdv,(GLdouble*),void);
value glstub_glIndexdv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glIndexdv);
	CALL_FUNCTION(glIndexdv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexf,(GLfloat),void);
value glstub_glIndexf(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glIndexf);
	CALL_FUNCTION(glIndexf)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexfv,(GLfloat*),void);
value glstub_glIndexfv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glIndexfv);
	CALL_FUNCTION(glIndexfv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexi,(GLint),void);
value glstub_glIndexi(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glIndexi);
	CALL_FUNCTION(glIndexi)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexiv,(GLint*),void);
value glstub_glIndexiv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glIndexiv);
	CALL_FUNCTION(glIndexiv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexs,(GLshort),void);
value glstub_glIndexs(value v0)
{
	CAMLparam1(v0);
	GLshort lv0 = Int_val(v0);
	LOAD_FUNCTION(glIndexs);
	CALL_FUNCTION(glIndexs)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexsv,(GLshort*),void);
value glstub_glIndexsv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glIndexsv);
	CALL_FUNCTION(glIndexsv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexub,(GLubyte),void);
value glstub_glIndexub(value v0)
{
	CAMLparam1(v0);
	GLubyte lv0 = Int_val(v0);
	LOAD_FUNCTION(glIndexub);
	CALL_FUNCTION(glIndexub)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIndexubv,(GLubyte*),void);
value glstub_glIndexubv(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glIndexubv);
	CALL_FUNCTION(glIndexubv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glInitNames,(void),void);
value glstub_glInitNames(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glInitNames);
	CALL_FUNCTION(glInitNames)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glInsertComponentEXT,(GLuint, GLuint, GLuint),void);
value glstub_glInsertComponentEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glInsertComponentEXT);
	CALL_FUNCTION(glInsertComponentEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glInterleavedArrays,(GLenum, GLsizei, GLvoid*),void);
value glstub_glInterleavedArrays(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glInterleavedArrays);
	CALL_FUNCTION(glInterleavedArrays)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glIsAsyncMarkerSGIX,(GLuint),GLboolean);
value glstub_glIsAsyncMarkerSGIX(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsAsyncMarkerSGIX);
	ret = CALL_FUNCTION(glIsAsyncMarkerSGIX)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsBuffer,(GLuint),GLboolean);
value glstub_glIsBuffer(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsBuffer);
	ret = CALL_FUNCTION(glIsBuffer)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsBufferARB,(GLuint),GLboolean);
value glstub_glIsBufferARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsBufferARB);
	ret = CALL_FUNCTION(glIsBufferARB)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsEnabled,(GLenum),GLboolean);
value glstub_glIsEnabled(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsEnabled);
	ret = CALL_FUNCTION(glIsEnabled)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsEnabledIndexedEXT,(GLenum, GLuint),GLboolean);
value glstub_glIsEnabledIndexedEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLboolean ret;
	LOAD_FUNCTION(glIsEnabledIndexedEXT);
	ret = CALL_FUNCTION(glIsEnabledIndexedEXT)(lv0, lv1);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsFenceAPPLE,(GLuint),GLboolean);
value glstub_glIsFenceAPPLE(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsFenceAPPLE);
	ret = CALL_FUNCTION(glIsFenceAPPLE)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsFenceNV,(GLuint),GLboolean);
value glstub_glIsFenceNV(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsFenceNV);
	ret = CALL_FUNCTION(glIsFenceNV)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsFramebufferEXT,(GLuint),GLboolean);
value glstub_glIsFramebufferEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsFramebufferEXT);
	ret = CALL_FUNCTION(glIsFramebufferEXT)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsList,(GLuint),GLboolean);
value glstub_glIsList(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsList);
	ret = CALL_FUNCTION(glIsList)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsObjectBufferATI,(GLuint),GLboolean);
value glstub_glIsObjectBufferATI(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsObjectBufferATI);
	ret = CALL_FUNCTION(glIsObjectBufferATI)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsOcclusionQueryNV,(GLuint),GLboolean);
value glstub_glIsOcclusionQueryNV(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsOcclusionQueryNV);
	ret = CALL_FUNCTION(glIsOcclusionQueryNV)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsProgram,(GLuint),GLboolean);
value glstub_glIsProgram(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsProgram);
	ret = CALL_FUNCTION(glIsProgram)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsProgramARB,(GLuint),GLboolean);
value glstub_glIsProgramARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsProgramARB);
	ret = CALL_FUNCTION(glIsProgramARB)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsProgramNV,(GLuint),GLboolean);
value glstub_glIsProgramNV(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsProgramNV);
	ret = CALL_FUNCTION(glIsProgramNV)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsQuery,(GLuint),GLboolean);
value glstub_glIsQuery(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsQuery);
	ret = CALL_FUNCTION(glIsQuery)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsQueryARB,(GLuint),GLboolean);
value glstub_glIsQueryARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsQueryARB);
	ret = CALL_FUNCTION(glIsQueryARB)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsRenderbufferEXT,(GLuint),GLboolean);
value glstub_glIsRenderbufferEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsRenderbufferEXT);
	ret = CALL_FUNCTION(glIsRenderbufferEXT)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsShader,(GLuint),GLboolean);
value glstub_glIsShader(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsShader);
	ret = CALL_FUNCTION(glIsShader)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsTexture,(GLuint),GLboolean);
value glstub_glIsTexture(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsTexture);
	ret = CALL_FUNCTION(glIsTexture)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsTextureEXT,(GLuint),GLboolean);
value glstub_glIsTextureEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsTextureEXT);
	ret = CALL_FUNCTION(glIsTextureEXT)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsVariantEnabledEXT,(GLuint, GLenum),GLboolean);
value glstub_glIsVariantEnabledEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean ret;
	LOAD_FUNCTION(glIsVariantEnabledEXT);
	ret = CALL_FUNCTION(glIsVariantEnabledEXT)(lv0, lv1);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsVertexArray,(GLuint),GLboolean);
value glstub_glIsVertexArray(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsVertexArray);
	ret = CALL_FUNCTION(glIsVertexArray)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glIsVertexArrayAPPLE,(GLuint),GLboolean);
value glstub_glIsVertexArrayAPPLE(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glIsVertexArrayAPPLE);
	ret = CALL_FUNCTION(glIsVertexArrayAPPLE)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glLightEnviEXT,(GLenum, GLint),void);
value glstub_glLightEnviEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glLightEnviEXT);
	CALL_FUNCTION(glLightEnviEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLightModelf,(GLenum, GLfloat),void);
value glstub_glLightModelf(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glLightModelf);
	CALL_FUNCTION(glLightModelf)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLightModelfv,(GLenum, GLfloat*),void);
value glstub_glLightModelfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glLightModelfv);
	CALL_FUNCTION(glLightModelfv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLightModeli,(GLenum, GLint),void);
value glstub_glLightModeli(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glLightModeli);
	CALL_FUNCTION(glLightModeli)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLightModeliv,(GLenum, GLint*),void);
value glstub_glLightModeliv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glLightModeliv);
	CALL_FUNCTION(glLightModeliv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLightf,(GLenum, GLenum, GLfloat),void);
value glstub_glLightf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glLightf);
	CALL_FUNCTION(glLightf)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLightfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glLightfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glLightfv);
	CALL_FUNCTION(glLightfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLighti,(GLenum, GLenum, GLint),void);
value glstub_glLighti(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glLighti);
	CALL_FUNCTION(glLighti)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLightiv,(GLenum, GLenum, GLint*),void);
value glstub_glLightiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glLightiv);
	CALL_FUNCTION(glLightiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLineStipple,(GLint, GLushort),void);
value glstub_glLineStipple(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	LOAD_FUNCTION(glLineStipple);
	CALL_FUNCTION(glLineStipple)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLineWidth,(GLfloat),void);
value glstub_glLineWidth(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glLineWidth);
	CALL_FUNCTION(glLineWidth)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLinkProgram,(GLuint),void);
value glstub_glLinkProgram(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glLinkProgram);
	CALL_FUNCTION(glLinkProgram)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLinkProgramARB,(GLuint),void);
value glstub_glLinkProgramARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glLinkProgramARB);
	CALL_FUNCTION(glLinkProgramARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glListBase,(GLuint),void);
value glstub_glListBase(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glListBase);
	CALL_FUNCTION(glListBase)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadIdentity,(void),void);
value glstub_glLoadIdentity(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glLoadIdentity);
	CALL_FUNCTION(glLoadIdentity)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadMatrixd,(GLdouble*),void);
value glstub_glLoadMatrixd(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glLoadMatrixd);
	CALL_FUNCTION(glLoadMatrixd)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadMatrixf,(GLfloat*),void);
value glstub_glLoadMatrixf(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glLoadMatrixf);
	CALL_FUNCTION(glLoadMatrixf)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadName,(GLuint),void);
value glstub_glLoadName(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glLoadName);
	CALL_FUNCTION(glLoadName)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadProgramNV,(GLenum, GLuint, GLsizei, GLubyte*),void);
value glstub_glLoadProgramNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLubyte* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glLoadProgramNV);
	CALL_FUNCTION(glLoadProgramNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadTransposeMatrixd,(GLdouble*),void);
value glstub_glLoadTransposeMatrixd(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glLoadTransposeMatrixd);
	CALL_FUNCTION(glLoadTransposeMatrixd)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadTransposeMatrixdARB,(GLdouble*),void);
value glstub_glLoadTransposeMatrixdARB(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glLoadTransposeMatrixdARB);
	CALL_FUNCTION(glLoadTransposeMatrixdARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadTransposeMatrixf,(GLfloat*),void);
value glstub_glLoadTransposeMatrixf(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glLoadTransposeMatrixf);
	CALL_FUNCTION(glLoadTransposeMatrixf)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLoadTransposeMatrixfARB,(GLfloat*),void);
value glstub_glLoadTransposeMatrixfARB(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glLoadTransposeMatrixfARB);
	CALL_FUNCTION(glLoadTransposeMatrixfARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLockArraysEXT,(GLint, GLsizei),void);
value glstub_glLockArraysEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	LOAD_FUNCTION(glLockArraysEXT);
	CALL_FUNCTION(glLockArraysEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glLogicOp,(GLenum),void);
value glstub_glLogicOp(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glLogicOp);
	CALL_FUNCTION(glLogicOp)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMap1d,(GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble*),void);
value glstub_glMap1d(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLdouble* lv5 = (Tag_val(v5) == Double_array_tag)? (double *)v5: Data_bigarray_val(v5);
	LOAD_FUNCTION(glMap1d);
	CALL_FUNCTION(glMap1d)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMap1d_byte(value * argv, int n)
{
	return glstub_glMap1d(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glMap1f,(GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat*),void);
value glstub_glMap1f(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLfloat* lv5 = Data_bigarray_val(v5);
	LOAD_FUNCTION(glMap1f);
	CALL_FUNCTION(glMap1f)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMap1f_byte(value * argv, int n)
{
	return glstub_glMap1f(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glMap2d,(GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, GLdouble*),void);
value glstub_glMap2d(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLdouble lv5 = Double_val(v5);
	GLdouble lv6 = Double_val(v6);
	GLint lv7 = Int_val(v7);
	GLint lv8 = Int_val(v8);
	GLdouble* lv9 = (Tag_val(v9) == Double_array_tag)? (double *)v9: Data_bigarray_val(v9);
	LOAD_FUNCTION(glMap2d);
	CALL_FUNCTION(glMap2d)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glMap2d_byte(value * argv, int n)
{
	return glstub_glMap2d(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

DECLARE_FUNCTION(glMap2f,(GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, GLfloat*),void);
value glstub_glMap2f(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLint lv7 = Int_val(v7);
	GLint lv8 = Int_val(v8);
	GLfloat* lv9 = Data_bigarray_val(v9);
	LOAD_FUNCTION(glMap2f);
	CALL_FUNCTION(glMap2f)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glMap2f_byte(value * argv, int n)
{
	return glstub_glMap2f(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

DECLARE_FUNCTION(glMapBuffer,(GLenum, GLenum),GLvoid*);
value glstub_glMapBuffer(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* ret;
	LOAD_FUNCTION(glMapBuffer);
	ret = CALL_FUNCTION(glMapBuffer)(lv0, lv1);
	result = (value)(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glMapBufferARB,(GLenum, GLenum),GLvoid*);
value glstub_glMapBufferARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* ret;
	LOAD_FUNCTION(glMapBufferARB);
	ret = CALL_FUNCTION(glMapBufferARB)(lv0, lv1);
	result = (value)(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glMapControlPointsNV,(GLenum, GLuint, GLenum, GLsizei, GLsizei, GLint, GLint, GLboolean, GLvoid*),void);
value glstub_glMapControlPointsNV(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	GLboolean lv7 = Bool_val(v7);
	GLvoid* lv8 = (Is_long(v8) ? (GLvoid*)Long_val(v8) : ((Tag_val(v8) == String_tag)? (String_val(v8)) : (Data_bigarray_val(v8))));
	LOAD_FUNCTION(glMapControlPointsNV);
	CALL_FUNCTION(glMapControlPointsNV)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glMapControlPointsNV_byte(value * argv, int n)
{
	return glstub_glMapControlPointsNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glMapGrid1d,(GLint, GLdouble, GLdouble),void);
value glstub_glMapGrid1d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glMapGrid1d);
	CALL_FUNCTION(glMapGrid1d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMapGrid1f,(GLint, GLfloat, GLfloat),void);
value glstub_glMapGrid1f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glMapGrid1f);
	CALL_FUNCTION(glMapGrid1f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMapGrid2d,(GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble),void);
value glstub_glMapGrid2d(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLint lv3 = Int_val(v3);
	GLdouble lv4 = Double_val(v4);
	GLdouble lv5 = Double_val(v5);
	LOAD_FUNCTION(glMapGrid2d);
	CALL_FUNCTION(glMapGrid2d)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMapGrid2d_byte(value * argv, int n)
{
	return glstub_glMapGrid2d(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glMapGrid2f,(GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat),void);
value glstub_glMapGrid2f(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLint lv3 = Int_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glMapGrid2f);
	CALL_FUNCTION(glMapGrid2f)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMapGrid2f_byte(value * argv, int n)
{
	return glstub_glMapGrid2f(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glMapObjectBufferATI,(GLuint),void*);
value glstub_glMapObjectBufferATI(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	void* ret;
	LOAD_FUNCTION(glMapObjectBufferATI);
	ret = CALL_FUNCTION(glMapObjectBufferATI)(lv0);
	result = (value)(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glMapParameterfvNV,(GLenum, GLenum, GLfloat*),void);
value glstub_glMapParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glMapParameterfvNV);
	CALL_FUNCTION(glMapParameterfvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMapParameterivNV,(GLenum, GLenum, GLint*),void);
value glstub_glMapParameterivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glMapParameterivNV);
	CALL_FUNCTION(glMapParameterivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMaterialf,(GLenum, GLenum, GLfloat),void);
value glstub_glMaterialf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glMaterialf);
	CALL_FUNCTION(glMaterialf)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMaterialfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glMaterialfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glMaterialfv);
	CALL_FUNCTION(glMaterialfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMateriali,(GLenum, GLenum, GLint),void);
value glstub_glMateriali(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glMateriali);
	CALL_FUNCTION(glMateriali)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMaterialiv,(GLenum, GLenum, GLint*),void);
value glstub_glMaterialiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glMaterialiv);
	CALL_FUNCTION(glMaterialiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMatrixIndexPointerARB,(GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glMatrixIndexPointerARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glMatrixIndexPointerARB);
	CALL_FUNCTION(glMatrixIndexPointerARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMatrixIndexubvARB,(GLint, GLubyte*),void);
value glstub_glMatrixIndexubvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMatrixIndexubvARB);
	CALL_FUNCTION(glMatrixIndexubvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMatrixIndexuivARB,(GLint, GLuint*),void);
value glstub_glMatrixIndexuivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMatrixIndexuivARB);
	CALL_FUNCTION(glMatrixIndexuivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMatrixIndexusvARB,(GLint, GLushort*),void);
value glstub_glMatrixIndexusvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMatrixIndexusvARB);
	CALL_FUNCTION(glMatrixIndexusvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMatrixMode,(GLenum),void);
value glstub_glMatrixMode(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glMatrixMode);
	CALL_FUNCTION(glMatrixMode)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMinmax,(GLenum, GLenum, GLboolean),void);
value glstub_glMinmax(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	LOAD_FUNCTION(glMinmax);
	CALL_FUNCTION(glMinmax)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMinmaxEXT,(GLenum, GLenum, GLboolean),void);
value glstub_glMinmaxEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	LOAD_FUNCTION(glMinmaxEXT);
	CALL_FUNCTION(glMinmaxEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultMatrixd,(GLdouble*),void);
value glstub_glMultMatrixd(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glMultMatrixd);
	CALL_FUNCTION(glMultMatrixd)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultMatrixf,(GLfloat*),void);
value glstub_glMultMatrixf(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glMultMatrixf);
	CALL_FUNCTION(glMultMatrixf)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultTransposeMatrixd,(GLdouble*),void);
value glstub_glMultTransposeMatrixd(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glMultTransposeMatrixd);
	CALL_FUNCTION(glMultTransposeMatrixd)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultTransposeMatrixdARB,(GLdouble*),void);
value glstub_glMultTransposeMatrixdARB(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glMultTransposeMatrixdARB);
	CALL_FUNCTION(glMultTransposeMatrixdARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultTransposeMatrixf,(GLfloat*),void);
value glstub_glMultTransposeMatrixf(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glMultTransposeMatrixf);
	CALL_FUNCTION(glMultTransposeMatrixf)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultTransposeMatrixfARB,(GLfloat*),void);
value glstub_glMultTransposeMatrixfARB(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glMultTransposeMatrixfARB);
	CALL_FUNCTION(glMultTransposeMatrixfARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiDrawArrays,(GLenum, GLint*, GLsizei*, GLsizei),void);
value glstub_glMultiDrawArrays(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glMultiDrawArrays);
	CALL_FUNCTION(glMultiDrawArrays)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiDrawArraysEXT,(GLenum, GLint*, GLsizei*, GLsizei),void);
value glstub_glMultiDrawArraysEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glMultiDrawArraysEXT);
	CALL_FUNCTION(glMultiDrawArraysEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiDrawElementArrayAPPLE,(GLenum, GLint*, GLsizei*, GLsizei),void);
value glstub_glMultiDrawElementArrayAPPLE(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glMultiDrawElementArrayAPPLE);
	CALL_FUNCTION(glMultiDrawElementArrayAPPLE)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiDrawElements,(GLenum, GLsizei*, GLenum, GLvoid**, GLsizei),void);
value glstub_glMultiDrawElements(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei* lv1 = Data_bigarray_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glMultiDrawElements);
	CALL_FUNCTION(glMultiDrawElements)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiDrawElementsEXT,(GLenum, GLsizei*, GLenum, GLvoid**, GLsizei),void);
value glstub_glMultiDrawElementsEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei* lv1 = Data_bigarray_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glMultiDrawElementsEXT);
	CALL_FUNCTION(glMultiDrawElementsEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiDrawRangeElementArrayAPPLE,(GLenum, GLuint, GLuint, GLint*, GLsizei*, GLsizei),void);
value glstub_glMultiDrawRangeElementArrayAPPLE(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	GLsizei* lv4 = Data_bigarray_val(v4);
	GLsizei lv5 = Int_val(v5);
	LOAD_FUNCTION(glMultiDrawRangeElementArrayAPPLE);
	CALL_FUNCTION(glMultiDrawRangeElementArrayAPPLE)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMultiDrawRangeElementArrayAPPLE_byte(value * argv, int n)
{
	return glstub_glMultiDrawRangeElementArrayAPPLE(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glMultiModeDrawArraysIBM,(GLenum*, GLint*, GLsizei*, GLsizei, GLint),void);
value glstub_glMultiModeDrawArraysIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum* lv0 = Data_bigarray_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glMultiModeDrawArraysIBM);
	CALL_FUNCTION(glMultiModeDrawArraysIBM)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiModeDrawElementsIBM,(GLenum*, GLsizei*, GLenum, GLvoid**, GLsizei, GLint),void);
value glstub_glMultiModeDrawElementsIBM(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum* lv0 = Data_bigarray_val(v0);
	GLsizei* lv1 = Data_bigarray_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	LOAD_FUNCTION(glMultiModeDrawElementsIBM);
	CALL_FUNCTION(glMultiModeDrawElementsIBM)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMultiModeDrawElementsIBM_byte(value * argv, int n)
{
	return glstub_glMultiModeDrawElementsIBM(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glMultiTexCoord1d,(GLenum, GLdouble),void);
value glstub_glMultiTexCoord1d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1d);
	CALL_FUNCTION(glMultiTexCoord1d)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1dARB,(GLenum, GLdouble),void);
value glstub_glMultiTexCoord1dARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1dARB);
	CALL_FUNCTION(glMultiTexCoord1dARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1dv,(GLenum, GLdouble*),void);
value glstub_glMultiTexCoord1dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1dv);
	CALL_FUNCTION(glMultiTexCoord1dv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1dvARB,(GLenum, GLdouble*),void);
value glstub_glMultiTexCoord1dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1dvARB);
	CALL_FUNCTION(glMultiTexCoord1dvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1f,(GLenum, GLfloat),void);
value glstub_glMultiTexCoord1f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1f);
	CALL_FUNCTION(glMultiTexCoord1f)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1fARB,(GLenum, GLfloat),void);
value glstub_glMultiTexCoord1fARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1fARB);
	CALL_FUNCTION(glMultiTexCoord1fARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1fv,(GLenum, GLfloat*),void);
value glstub_glMultiTexCoord1fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1fv);
	CALL_FUNCTION(glMultiTexCoord1fv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1fvARB,(GLenum, GLfloat*),void);
value glstub_glMultiTexCoord1fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1fvARB);
	CALL_FUNCTION(glMultiTexCoord1fvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1hNV,(GLenum, GLushort),void);
value glstub_glMultiTexCoord1hNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1hNV);
	CALL_FUNCTION(glMultiTexCoord1hNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1hvNV,(GLenum, GLushort*),void);
value glstub_glMultiTexCoord1hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1hvNV);
	CALL_FUNCTION(glMultiTexCoord1hvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1i,(GLenum, GLint),void);
value glstub_glMultiTexCoord1i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1i);
	CALL_FUNCTION(glMultiTexCoord1i)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1iARB,(GLenum, GLint),void);
value glstub_glMultiTexCoord1iARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1iARB);
	CALL_FUNCTION(glMultiTexCoord1iARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1iv,(GLenum, GLint*),void);
value glstub_glMultiTexCoord1iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1iv);
	CALL_FUNCTION(glMultiTexCoord1iv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1ivARB,(GLenum, GLint*),void);
value glstub_glMultiTexCoord1ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1ivARB);
	CALL_FUNCTION(glMultiTexCoord1ivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1s,(GLenum, GLshort),void);
value glstub_glMultiTexCoord1s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1s);
	CALL_FUNCTION(glMultiTexCoord1s)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1sARB,(GLenum, GLshort),void);
value glstub_glMultiTexCoord1sARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1sARB);
	CALL_FUNCTION(glMultiTexCoord1sARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1sv,(GLenum, GLshort*),void);
value glstub_glMultiTexCoord1sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1sv);
	CALL_FUNCTION(glMultiTexCoord1sv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord1svARB,(GLenum, GLshort*),void);
value glstub_glMultiTexCoord1svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord1svARB);
	CALL_FUNCTION(glMultiTexCoord1svARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2d,(GLenum, GLdouble, GLdouble),void);
value glstub_glMultiTexCoord2d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2d);
	CALL_FUNCTION(glMultiTexCoord2d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2dARB,(GLenum, GLdouble, GLdouble),void);
value glstub_glMultiTexCoord2dARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2dARB);
	CALL_FUNCTION(glMultiTexCoord2dARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2dv,(GLenum, GLdouble*),void);
value glstub_glMultiTexCoord2dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2dv);
	CALL_FUNCTION(glMultiTexCoord2dv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2dvARB,(GLenum, GLdouble*),void);
value glstub_glMultiTexCoord2dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2dvARB);
	CALL_FUNCTION(glMultiTexCoord2dvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2f,(GLenum, GLfloat, GLfloat),void);
value glstub_glMultiTexCoord2f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2f);
	CALL_FUNCTION(glMultiTexCoord2f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2fARB,(GLenum, GLfloat, GLfloat),void);
value glstub_glMultiTexCoord2fARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2fARB);
	CALL_FUNCTION(glMultiTexCoord2fARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2fv,(GLenum, GLfloat*),void);
value glstub_glMultiTexCoord2fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2fv);
	CALL_FUNCTION(glMultiTexCoord2fv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2fvARB,(GLenum, GLfloat*),void);
value glstub_glMultiTexCoord2fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2fvARB);
	CALL_FUNCTION(glMultiTexCoord2fvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2hNV,(GLenum, GLushort, GLushort),void);
value glstub_glMultiTexCoord2hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2hNV);
	CALL_FUNCTION(glMultiTexCoord2hNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2hvNV,(GLenum, GLushort*),void);
value glstub_glMultiTexCoord2hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2hvNV);
	CALL_FUNCTION(glMultiTexCoord2hvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2i,(GLenum, GLint, GLint),void);
value glstub_glMultiTexCoord2i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2i);
	CALL_FUNCTION(glMultiTexCoord2i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2iARB,(GLenum, GLint, GLint),void);
value glstub_glMultiTexCoord2iARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2iARB);
	CALL_FUNCTION(glMultiTexCoord2iARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2iv,(GLenum, GLint*),void);
value glstub_glMultiTexCoord2iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2iv);
	CALL_FUNCTION(glMultiTexCoord2iv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2ivARB,(GLenum, GLint*),void);
value glstub_glMultiTexCoord2ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2ivARB);
	CALL_FUNCTION(glMultiTexCoord2ivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2s,(GLenum, GLshort, GLshort),void);
value glstub_glMultiTexCoord2s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2s);
	CALL_FUNCTION(glMultiTexCoord2s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2sARB,(GLenum, GLshort, GLshort),void);
value glstub_glMultiTexCoord2sARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glMultiTexCoord2sARB);
	CALL_FUNCTION(glMultiTexCoord2sARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2sv,(GLenum, GLshort*),void);
value glstub_glMultiTexCoord2sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2sv);
	CALL_FUNCTION(glMultiTexCoord2sv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord2svARB,(GLenum, GLshort*),void);
value glstub_glMultiTexCoord2svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord2svARB);
	CALL_FUNCTION(glMultiTexCoord2svARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3d,(GLenum, GLdouble, GLdouble, GLdouble),void);
value glstub_glMultiTexCoord3d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3d);
	CALL_FUNCTION(glMultiTexCoord3d)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3dARB,(GLenum, GLdouble, GLdouble, GLdouble),void);
value glstub_glMultiTexCoord3dARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3dARB);
	CALL_FUNCTION(glMultiTexCoord3dARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3dv,(GLenum, GLdouble*),void);
value glstub_glMultiTexCoord3dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3dv);
	CALL_FUNCTION(glMultiTexCoord3dv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3dvARB,(GLenum, GLdouble*),void);
value glstub_glMultiTexCoord3dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3dvARB);
	CALL_FUNCTION(glMultiTexCoord3dvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3f,(GLenum, GLfloat, GLfloat, GLfloat),void);
value glstub_glMultiTexCoord3f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3f);
	CALL_FUNCTION(glMultiTexCoord3f)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3fARB,(GLenum, GLfloat, GLfloat, GLfloat),void);
value glstub_glMultiTexCoord3fARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3fARB);
	CALL_FUNCTION(glMultiTexCoord3fARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3fv,(GLenum, GLfloat*),void);
value glstub_glMultiTexCoord3fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3fv);
	CALL_FUNCTION(glMultiTexCoord3fv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3fvARB,(GLenum, GLfloat*),void);
value glstub_glMultiTexCoord3fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3fvARB);
	CALL_FUNCTION(glMultiTexCoord3fvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3hNV,(GLenum, GLushort, GLushort, GLushort),void);
value glstub_glMultiTexCoord3hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3hNV);
	CALL_FUNCTION(glMultiTexCoord3hNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3hvNV,(GLenum, GLushort*),void);
value glstub_glMultiTexCoord3hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3hvNV);
	CALL_FUNCTION(glMultiTexCoord3hvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3i,(GLenum, GLint, GLint, GLint),void);
value glstub_glMultiTexCoord3i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3i);
	CALL_FUNCTION(glMultiTexCoord3i)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3iARB,(GLenum, GLint, GLint, GLint),void);
value glstub_glMultiTexCoord3iARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3iARB);
	CALL_FUNCTION(glMultiTexCoord3iARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3iv,(GLenum, GLint*),void);
value glstub_glMultiTexCoord3iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3iv);
	CALL_FUNCTION(glMultiTexCoord3iv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3ivARB,(GLenum, GLint*),void);
value glstub_glMultiTexCoord3ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3ivARB);
	CALL_FUNCTION(glMultiTexCoord3ivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3s,(GLenum, GLshort, GLshort, GLshort),void);
value glstub_glMultiTexCoord3s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3s);
	CALL_FUNCTION(glMultiTexCoord3s)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3sARB,(GLenum, GLshort, GLshort, GLshort),void);
value glstub_glMultiTexCoord3sARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glMultiTexCoord3sARB);
	CALL_FUNCTION(glMultiTexCoord3sARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3sv,(GLenum, GLshort*),void);
value glstub_glMultiTexCoord3sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3sv);
	CALL_FUNCTION(glMultiTexCoord3sv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord3svARB,(GLenum, GLshort*),void);
value glstub_glMultiTexCoord3svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord3svARB);
	CALL_FUNCTION(glMultiTexCoord3svARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4d,(GLenum, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glMultiTexCoord4d(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4d);
	CALL_FUNCTION(glMultiTexCoord4d)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4dARB,(GLenum, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glMultiTexCoord4dARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4dARB);
	CALL_FUNCTION(glMultiTexCoord4dARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4dv,(GLenum, GLdouble*),void);
value glstub_glMultiTexCoord4dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4dv);
	CALL_FUNCTION(glMultiTexCoord4dv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4dvARB,(GLenum, GLdouble*),void);
value glstub_glMultiTexCoord4dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4dvARB);
	CALL_FUNCTION(glMultiTexCoord4dvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4f,(GLenum, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glMultiTexCoord4f(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4f);
	CALL_FUNCTION(glMultiTexCoord4f)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4fARB,(GLenum, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glMultiTexCoord4fARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4fARB);
	CALL_FUNCTION(glMultiTexCoord4fARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4fv,(GLenum, GLfloat*),void);
value glstub_glMultiTexCoord4fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4fv);
	CALL_FUNCTION(glMultiTexCoord4fv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4fvARB,(GLenum, GLfloat*),void);
value glstub_glMultiTexCoord4fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4fvARB);
	CALL_FUNCTION(glMultiTexCoord4fvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4hNV,(GLenum, GLushort, GLushort, GLushort, GLushort),void);
value glstub_glMultiTexCoord4hNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	GLushort lv4 = Int_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4hNV);
	CALL_FUNCTION(glMultiTexCoord4hNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4hvNV,(GLenum, GLushort*),void);
value glstub_glMultiTexCoord4hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4hvNV);
	CALL_FUNCTION(glMultiTexCoord4hvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4i,(GLenum, GLint, GLint, GLint, GLint),void);
value glstub_glMultiTexCoord4i(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4i);
	CALL_FUNCTION(glMultiTexCoord4i)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4iARB,(GLenum, GLint, GLint, GLint, GLint),void);
value glstub_glMultiTexCoord4iARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4iARB);
	CALL_FUNCTION(glMultiTexCoord4iARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4iv,(GLenum, GLint*),void);
value glstub_glMultiTexCoord4iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4iv);
	CALL_FUNCTION(glMultiTexCoord4iv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4ivARB,(GLenum, GLint*),void);
value glstub_glMultiTexCoord4ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4ivARB);
	CALL_FUNCTION(glMultiTexCoord4ivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4s,(GLenum, GLshort, GLshort, GLshort, GLshort),void);
value glstub_glMultiTexCoord4s(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4s);
	CALL_FUNCTION(glMultiTexCoord4s)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4sARB,(GLenum, GLshort, GLshort, GLshort, GLshort),void);
value glstub_glMultiTexCoord4sARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	LOAD_FUNCTION(glMultiTexCoord4sARB);
	CALL_FUNCTION(glMultiTexCoord4sARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4sv,(GLenum, GLshort*),void);
value glstub_glMultiTexCoord4sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4sv);
	CALL_FUNCTION(glMultiTexCoord4sv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glMultiTexCoord4svARB,(GLenum, GLshort*),void);
value glstub_glMultiTexCoord4svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glMultiTexCoord4svARB);
	CALL_FUNCTION(glMultiTexCoord4svARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNewList,(GLuint, GLenum),void);
value glstub_glNewList(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glNewList);
	CALL_FUNCTION(glNewList)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNewObjectBufferATI,(GLsizei, GLvoid*, GLenum),GLuint);
value glstub_glNewObjectBufferATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	GLenum lv2 = Int_val(v2);
	GLuint ret;
	LOAD_FUNCTION(glNewObjectBufferATI);
	ret = CALL_FUNCTION(glNewObjectBufferATI)(lv0, lv1, lv2);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glNormal3b,(GLbyte, GLbyte, GLbyte),void);
value glstub_glNormal3b(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	LOAD_FUNCTION(glNormal3b);
	CALL_FUNCTION(glNormal3b)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3bv,(GLbyte*),void);
value glstub_glNormal3bv(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glNormal3bv);
	CALL_FUNCTION(glNormal3bv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3d,(GLdouble, GLdouble, GLdouble),void);
value glstub_glNormal3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glNormal3d);
	CALL_FUNCTION(glNormal3d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3dv,(GLdouble*),void);
value glstub_glNormal3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glNormal3dv);
	CALL_FUNCTION(glNormal3dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3f,(GLfloat, GLfloat, GLfloat),void);
value glstub_glNormal3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glNormal3f);
	CALL_FUNCTION(glNormal3f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3fVertex3fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glNormal3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glNormal3fVertex3fSUN);
	CALL_FUNCTION(glNormal3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glNormal3fVertex3fvSUN,(GLfloat*, GLfloat*),void);
value glstub_glNormal3fVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glNormal3fVertex3fvSUN);
	CALL_FUNCTION(glNormal3fVertex3fvSUN)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3fv,(GLfloat*),void);
value glstub_glNormal3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glNormal3fv);
	CALL_FUNCTION(glNormal3fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3hNV,(GLushort, GLushort, GLushort),void);
value glstub_glNormal3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glNormal3hNV);
	CALL_FUNCTION(glNormal3hNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3hvNV,(GLushort*),void);
value glstub_glNormal3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glNormal3hvNV);
	CALL_FUNCTION(glNormal3hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3i,(GLint, GLint, GLint),void);
value glstub_glNormal3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glNormal3i);
	CALL_FUNCTION(glNormal3i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3iv,(GLint*),void);
value glstub_glNormal3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glNormal3iv);
	CALL_FUNCTION(glNormal3iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3s,(GLshort, GLshort, GLshort),void);
value glstub_glNormal3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glNormal3s);
	CALL_FUNCTION(glNormal3s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormal3sv,(GLshort*),void);
value glstub_glNormal3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glNormal3sv);
	CALL_FUNCTION(glNormal3sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalPointer,(GLenum, GLsizei, GLvoid*),void);
value glstub_glNormalPointer(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glNormalPointer);
	CALL_FUNCTION(glNormalPointer)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalPointerEXT,(GLenum, GLsizei, GLsizei, GLvoid*),void);
value glstub_glNormalPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glNormalPointerEXT);
	CALL_FUNCTION(glNormalPointerEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalPointerListIBM,(GLenum, GLint, GLvoid**, GLint),void);
value glstub_glNormalPointerListIBM(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glNormalPointerListIBM);
	CALL_FUNCTION(glNormalPointerListIBM)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalPointervINTEL,(GLenum, GLvoid**),void);
value glstub_glNormalPointervINTEL(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid** lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glNormalPointervINTEL);
	CALL_FUNCTION(glNormalPointervINTEL)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3bATI,(GLenum, GLbyte, GLbyte, GLbyte),void);
value glstub_glNormalStream3bATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	GLbyte lv3 = Int_val(v3);
	LOAD_FUNCTION(glNormalStream3bATI);
	CALL_FUNCTION(glNormalStream3bATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3bvATI,(GLenum, GLbyte*),void);
value glstub_glNormalStream3bvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glNormalStream3bvATI);
	CALL_FUNCTION(glNormalStream3bvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3dATI,(GLenum, GLdouble, GLdouble, GLdouble),void);
value glstub_glNormalStream3dATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glNormalStream3dATI);
	CALL_FUNCTION(glNormalStream3dATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3dvATI,(GLenum, GLdouble*),void);
value glstub_glNormalStream3dvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glNormalStream3dvATI);
	CALL_FUNCTION(glNormalStream3dvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3fATI,(GLenum, GLfloat, GLfloat, GLfloat),void);
value glstub_glNormalStream3fATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glNormalStream3fATI);
	CALL_FUNCTION(glNormalStream3fATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3fvATI,(GLenum, GLfloat*),void);
value glstub_glNormalStream3fvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glNormalStream3fvATI);
	CALL_FUNCTION(glNormalStream3fvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3iATI,(GLenum, GLint, GLint, GLint),void);
value glstub_glNormalStream3iATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glNormalStream3iATI);
	CALL_FUNCTION(glNormalStream3iATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3ivATI,(GLenum, GLint*),void);
value glstub_glNormalStream3ivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glNormalStream3ivATI);
	CALL_FUNCTION(glNormalStream3ivATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3sATI,(GLenum, GLshort, GLshort, GLshort),void);
value glstub_glNormalStream3sATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glNormalStream3sATI);
	CALL_FUNCTION(glNormalStream3sATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glNormalStream3svATI,(GLenum, GLshort*),void);
value glstub_glNormalStream3svATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glNormalStream3svATI);
	CALL_FUNCTION(glNormalStream3svATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glOrtho,(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glOrtho(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	GLdouble lv5 = Double_val(v5);
	LOAD_FUNCTION(glOrtho);
	CALL_FUNCTION(glOrtho)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glOrtho_byte(value * argv, int n)
{
	return glstub_glOrtho(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glOrthofOES,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glOrthofOES(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glOrthofOES);
	CALL_FUNCTION(glOrthofOES)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glOrthofOES_byte(value * argv, int n)
{
	return glstub_glOrthofOES(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glPNTrianglesfATI,(GLenum, GLfloat),void);
value glstub_glPNTrianglesfATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPNTrianglesfATI);
	CALL_FUNCTION(glPNTrianglesfATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPNTrianglesiATI,(GLenum, GLint),void);
value glstub_glPNTrianglesiATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glPNTrianglesiATI);
	CALL_FUNCTION(glPNTrianglesiATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPassTexCoordATI,(GLuint, GLuint, GLenum),void);
value glstub_glPassTexCoordATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	LOAD_FUNCTION(glPassTexCoordATI);
	CALL_FUNCTION(glPassTexCoordATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPassThrough,(GLfloat),void);
value glstub_glPassThrough(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glPassThrough);
	CALL_FUNCTION(glPassThrough)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelDataRangeNV,(GLenum, GLsizei, GLvoid*),void);
value glstub_glPixelDataRangeNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glPixelDataRangeNV);
	CALL_FUNCTION(glPixelDataRangeNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelMapfv,(GLenum, GLsizei, GLfloat*),void);
value glstub_glPixelMapfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glPixelMapfv);
	CALL_FUNCTION(glPixelMapfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelMapuiv,(GLenum, GLsizei, GLuint*),void);
value glstub_glPixelMapuiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glPixelMapuiv);
	CALL_FUNCTION(glPixelMapuiv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelMapusv,(GLenum, GLsizei, GLushort*),void);
value glstub_glPixelMapusv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glPixelMapusv);
	CALL_FUNCTION(glPixelMapusv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelStoref,(GLenum, GLfloat),void);
value glstub_glPixelStoref(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPixelStoref);
	CALL_FUNCTION(glPixelStoref)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelStorei,(GLenum, GLint),void);
value glstub_glPixelStorei(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glPixelStorei);
	CALL_FUNCTION(glPixelStorei)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelTexGenSGIX,(GLenum),void);
value glstub_glPixelTexGenSGIX(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glPixelTexGenSGIX);
	CALL_FUNCTION(glPixelTexGenSGIX)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelTransferf,(GLenum, GLfloat),void);
value glstub_glPixelTransferf(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPixelTransferf);
	CALL_FUNCTION(glPixelTransferf)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelTransferi,(GLenum, GLint),void);
value glstub_glPixelTransferi(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glPixelTransferi);
	CALL_FUNCTION(glPixelTransferi)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelTransformParameterfEXT,(GLenum, GLenum, GLfloat),void);
value glstub_glPixelTransformParameterfEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glPixelTransformParameterfEXT);
	CALL_FUNCTION(glPixelTransformParameterfEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelTransformParameterfvEXT,(GLenum, GLenum, GLfloat*),void);
value glstub_glPixelTransformParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glPixelTransformParameterfvEXT);
	CALL_FUNCTION(glPixelTransformParameterfvEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelTransformParameteriEXT,(GLenum, GLenum, GLint),void);
value glstub_glPixelTransformParameteriEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glPixelTransformParameteriEXT);
	CALL_FUNCTION(glPixelTransformParameteriEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelTransformParameterivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glPixelTransformParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glPixelTransformParameterivEXT);
	CALL_FUNCTION(glPixelTransformParameterivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPixelZoom,(GLfloat, GLfloat),void);
value glstub_glPixelZoom(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPixelZoom);
	CALL_FUNCTION(glPixelZoom)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointParameterf,(GLenum, GLfloat),void);
value glstub_glPointParameterf(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPointParameterf);
	CALL_FUNCTION(glPointParameterf)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointParameterfARB,(GLenum, GLfloat),void);
value glstub_glPointParameterfARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPointParameterfARB);
	CALL_FUNCTION(glPointParameterfARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointParameterfEXT,(GLenum, GLfloat),void);
value glstub_glPointParameterfEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPointParameterfEXT);
	CALL_FUNCTION(glPointParameterfEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointParameterfv,(GLenum, GLfloat*),void);
value glstub_glPointParameterfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glPointParameterfv);
	CALL_FUNCTION(glPointParameterfv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointParameterfvARB,(GLenum, GLfloat*),void);
value glstub_glPointParameterfvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glPointParameterfvARB);
	CALL_FUNCTION(glPointParameterfvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointParameterfvEXT,(GLenum, GLfloat*),void);
value glstub_glPointParameterfvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glPointParameterfvEXT);
	CALL_FUNCTION(glPointParameterfvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointParameteriNV,(GLenum, GLint),void);
value glstub_glPointParameteriNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glPointParameteriNV);
	CALL_FUNCTION(glPointParameteriNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointParameterivNV,(GLenum, GLint*),void);
value glstub_glPointParameterivNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glPointParameterivNV);
	CALL_FUNCTION(glPointParameterivNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPointSize,(GLfloat),void);
value glstub_glPointSize(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glPointSize);
	CALL_FUNCTION(glPointSize)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPollAsyncSGIX,(GLuint*),GLint);
value glstub_glPollAsyncSGIX(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLint ret;
	LOAD_FUNCTION(glPollAsyncSGIX);
	ret = CALL_FUNCTION(glPollAsyncSGIX)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glPolygonMode,(GLenum, GLenum),void);
value glstub_glPolygonMode(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glPolygonMode);
	CALL_FUNCTION(glPolygonMode)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPolygonOffset,(GLfloat, GLfloat),void);
value glstub_glPolygonOffset(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPolygonOffset);
	CALL_FUNCTION(glPolygonOffset)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPolygonOffsetEXT,(GLfloat, GLfloat),void);
value glstub_glPolygonOffsetEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glPolygonOffsetEXT);
	CALL_FUNCTION(glPolygonOffsetEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPolygonStipple,(GLubyte*),void);
value glstub_glPolygonStipple(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glPolygonStipple);
	CALL_FUNCTION(glPolygonStipple)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPopAttrib,(void),void);
value glstub_glPopAttrib(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glPopAttrib);
	CALL_FUNCTION(glPopAttrib)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPopClientAttrib,(void),void);
value glstub_glPopClientAttrib(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glPopClientAttrib);
	CALL_FUNCTION(glPopClientAttrib)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPopMatrix,(void),void);
value glstub_glPopMatrix(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glPopMatrix);
	CALL_FUNCTION(glPopMatrix)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPopName,(void),void);
value glstub_glPopName(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glPopName);
	CALL_FUNCTION(glPopName)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPrimitiveRestartIndexNV,(GLuint),void);
value glstub_glPrimitiveRestartIndexNV(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glPrimitiveRestartIndexNV);
	CALL_FUNCTION(glPrimitiveRestartIndexNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPrimitiveRestartNV,(void),void);
value glstub_glPrimitiveRestartNV(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glPrimitiveRestartNV);
	CALL_FUNCTION(glPrimitiveRestartNV)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPrioritizeTextures,(GLsizei, GLuint*, GLclampf*),void);
value glstub_glPrioritizeTextures(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLclampf* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glPrioritizeTextures);
	CALL_FUNCTION(glPrioritizeTextures)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPrioritizeTexturesEXT,(GLsizei, GLuint*, GLclampf*),void);
value glstub_glPrioritizeTexturesEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLclampf* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glPrioritizeTexturesEXT);
	CALL_FUNCTION(glPrioritizeTexturesEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramBufferParametersIivNV,(GLenum, GLuint, GLuint, GLsizei, GLint*),void);
value glstub_glProgramBufferParametersIivNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLint* lv4 = Data_bigarray_val(v4);
	LOAD_FUNCTION(glProgramBufferParametersIivNV);
	CALL_FUNCTION(glProgramBufferParametersIivNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramBufferParametersIuivNV,(GLenum, GLuint, GLuint, GLsizei, GLuint*),void);
value glstub_glProgramBufferParametersIuivNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLuint* lv4 = Data_bigarray_val(v4);
	LOAD_FUNCTION(glProgramBufferParametersIuivNV);
	CALL_FUNCTION(glProgramBufferParametersIuivNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramBufferParametersfvNV,(GLenum, GLuint, GLuint, GLsizei, GLfloat*),void);
value glstub_glProgramBufferParametersfvNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLfloat* lv4 = Data_bigarray_val(v4);
	LOAD_FUNCTION(glProgramBufferParametersfvNV);
	CALL_FUNCTION(glProgramBufferParametersfvNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramEnvParameter4dARB,(GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glProgramEnvParameter4dARB(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	GLdouble lv5 = Double_val(v5);
	LOAD_FUNCTION(glProgramEnvParameter4dARB);
	CALL_FUNCTION(glProgramEnvParameter4dARB)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameter4dARB_byte(value * argv, int n)
{
	return glstub_glProgramEnvParameter4dARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramEnvParameter4dvARB,(GLenum, GLuint, GLdouble*),void);
value glstub_glProgramEnvParameter4dvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramEnvParameter4dvARB);
	CALL_FUNCTION(glProgramEnvParameter4dvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramEnvParameter4fARB,(GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glProgramEnvParameter4fARB(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glProgramEnvParameter4fARB);
	CALL_FUNCTION(glProgramEnvParameter4fARB)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameter4fARB_byte(value * argv, int n)
{
	return glstub_glProgramEnvParameter4fARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramEnvParameter4fvARB,(GLenum, GLuint, GLfloat*),void);
value glstub_glProgramEnvParameter4fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramEnvParameter4fvARB);
	CALL_FUNCTION(glProgramEnvParameter4fvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramEnvParameterI4iNV,(GLenum, GLuint, GLint, GLint, GLint, GLint),void);
value glstub_glProgramEnvParameterI4iNV(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	LOAD_FUNCTION(glProgramEnvParameterI4iNV);
	CALL_FUNCTION(glProgramEnvParameterI4iNV)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameterI4iNV_byte(value * argv, int n)
{
	return glstub_glProgramEnvParameterI4iNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramEnvParameterI4ivNV,(GLenum, GLuint, GLint*),void);
value glstub_glProgramEnvParameterI4ivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramEnvParameterI4ivNV);
	CALL_FUNCTION(glProgramEnvParameterI4ivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramEnvParameterI4uiNV,(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glProgramEnvParameterI4uiNV(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	LOAD_FUNCTION(glProgramEnvParameterI4uiNV);
	CALL_FUNCTION(glProgramEnvParameterI4uiNV)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameterI4uiNV_byte(value * argv, int n)
{
	return glstub_glProgramEnvParameterI4uiNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramEnvParameterI4uivNV,(GLenum, GLuint, GLuint*),void);
value glstub_glProgramEnvParameterI4uivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramEnvParameterI4uivNV);
	CALL_FUNCTION(glProgramEnvParameterI4uivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramEnvParameters4fvEXT,(GLenum, GLuint, GLsizei, GLfloat*),void);
value glstub_glProgramEnvParameters4fvEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramEnvParameters4fvEXT);
	CALL_FUNCTION(glProgramEnvParameters4fvEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramEnvParametersI4ivNV,(GLenum, GLuint, GLsizei, GLint*),void);
value glstub_glProgramEnvParametersI4ivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramEnvParametersI4ivNV);
	CALL_FUNCTION(glProgramEnvParametersI4ivNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramEnvParametersI4uivNV,(GLenum, GLuint, GLsizei, GLuint*),void);
value glstub_glProgramEnvParametersI4uivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLuint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramEnvParametersI4uivNV);
	CALL_FUNCTION(glProgramEnvParametersI4uivNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramLocalParameter4dARB,(GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glProgramLocalParameter4dARB(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	GLdouble lv5 = Double_val(v5);
	LOAD_FUNCTION(glProgramLocalParameter4dARB);
	CALL_FUNCTION(glProgramLocalParameter4dARB)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameter4dARB_byte(value * argv, int n)
{
	return glstub_glProgramLocalParameter4dARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramLocalParameter4dvARB,(GLenum, GLuint, GLdouble*),void);
value glstub_glProgramLocalParameter4dvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramLocalParameter4dvARB);
	CALL_FUNCTION(glProgramLocalParameter4dvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramLocalParameter4fARB,(GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glProgramLocalParameter4fARB(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glProgramLocalParameter4fARB);
	CALL_FUNCTION(glProgramLocalParameter4fARB)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameter4fARB_byte(value * argv, int n)
{
	return glstub_glProgramLocalParameter4fARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramLocalParameter4fvARB,(GLenum, GLuint, GLfloat*),void);
value glstub_glProgramLocalParameter4fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramLocalParameter4fvARB);
	CALL_FUNCTION(glProgramLocalParameter4fvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramLocalParameterI4iNV,(GLenum, GLuint, GLint, GLint, GLint, GLint),void);
value glstub_glProgramLocalParameterI4iNV(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	LOAD_FUNCTION(glProgramLocalParameterI4iNV);
	CALL_FUNCTION(glProgramLocalParameterI4iNV)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameterI4iNV_byte(value * argv, int n)
{
	return glstub_glProgramLocalParameterI4iNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramLocalParameterI4ivNV,(GLenum, GLuint, GLint*),void);
value glstub_glProgramLocalParameterI4ivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramLocalParameterI4ivNV);
	CALL_FUNCTION(glProgramLocalParameterI4ivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramLocalParameterI4uiNV,(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glProgramLocalParameterI4uiNV(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	LOAD_FUNCTION(glProgramLocalParameterI4uiNV);
	CALL_FUNCTION(glProgramLocalParameterI4uiNV)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameterI4uiNV_byte(value * argv, int n)
{
	return glstub_glProgramLocalParameterI4uiNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramLocalParameterI4uivNV,(GLenum, GLuint, GLuint*),void);
value glstub_glProgramLocalParameterI4uivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramLocalParameterI4uivNV);
	CALL_FUNCTION(glProgramLocalParameterI4uivNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramLocalParameters4fvEXT,(GLenum, GLuint, GLsizei, GLfloat*),void);
value glstub_glProgramLocalParameters4fvEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramLocalParameters4fvEXT);
	CALL_FUNCTION(glProgramLocalParameters4fvEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramLocalParametersI4ivNV,(GLenum, GLuint, GLsizei, GLint*),void);
value glstub_glProgramLocalParametersI4ivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramLocalParametersI4ivNV);
	CALL_FUNCTION(glProgramLocalParametersI4ivNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramLocalParametersI4uivNV,(GLenum, GLuint, GLsizei, GLuint*),void);
value glstub_glProgramLocalParametersI4uivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLuint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramLocalParametersI4uivNV);
	CALL_FUNCTION(glProgramLocalParametersI4uivNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramNamedParameter4dNV,(GLuint, GLsizei, GLubyte*, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glProgramNamedParameter4dNV(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	GLdouble lv5 = Double_val(v5);
	GLdouble lv6 = Double_val(v6);
	LOAD_FUNCTION(glProgramNamedParameter4dNV);
	CALL_FUNCTION(glProgramNamedParameter4dNV)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glProgramNamedParameter4dNV_byte(value * argv, int n)
{
	return glstub_glProgramNamedParameter4dNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glProgramNamedParameter4dvNV,(GLuint, GLsizei, GLubyte*, GLdouble*),void);
value glstub_glProgramNamedParameter4dvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLdouble* lv3 = (Tag_val(v3) == Double_array_tag)? (double *)v3: Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramNamedParameter4dvNV);
	CALL_FUNCTION(glProgramNamedParameter4dvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramNamedParameter4fNV,(GLuint, GLsizei, GLubyte*, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glProgramNamedParameter4fNV(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	LOAD_FUNCTION(glProgramNamedParameter4fNV);
	CALL_FUNCTION(glProgramNamedParameter4fNV)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glProgramNamedParameter4fNV_byte(value * argv, int n)
{
	return glstub_glProgramNamedParameter4fNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glProgramNamedParameter4fvNV,(GLuint, GLsizei, GLubyte*, GLfloat*),void);
value glstub_glProgramNamedParameter4fvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramNamedParameter4fvNV);
	CALL_FUNCTION(glProgramNamedParameter4fvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramParameter4dNV,(GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glProgramParameter4dNV(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	GLdouble lv5 = Double_val(v5);
	LOAD_FUNCTION(glProgramParameter4dNV);
	CALL_FUNCTION(glProgramParameter4dNV)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramParameter4dNV_byte(value * argv, int n)
{
	return glstub_glProgramParameter4dNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramParameter4dvNV,(GLenum, GLuint, GLdouble*),void);
value glstub_glProgramParameter4dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramParameter4dvNV);
	CALL_FUNCTION(glProgramParameter4dvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramParameter4fNV,(GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glProgramParameter4fNV(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glProgramParameter4fNV);
	CALL_FUNCTION(glProgramParameter4fNV)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramParameter4fNV_byte(value * argv, int n)
{
	return glstub_glProgramParameter4fNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glProgramParameter4fvNV,(GLenum, GLuint, GLfloat*),void);
value glstub_glProgramParameter4fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glProgramParameter4fvNV);
	CALL_FUNCTION(glProgramParameter4fvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramParameteriEXT,(GLuint, GLenum, GLint),void);
value glstub_glProgramParameteriEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glProgramParameteriEXT);
	CALL_FUNCTION(glProgramParameteriEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramParameters4dvNV,(GLenum, GLuint, GLuint, GLdouble*),void);
value glstub_glProgramParameters4dvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLdouble* lv3 = (Tag_val(v3) == Double_array_tag)? (double *)v3: Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramParameters4dvNV);
	CALL_FUNCTION(glProgramParameters4dvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramParameters4fvNV,(GLenum, GLuint, GLuint, GLfloat*),void);
value glstub_glProgramParameters4fvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glProgramParameters4fvNV);
	CALL_FUNCTION(glProgramParameters4fvNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramStringARB,(GLenum, GLenum, GLsizei, GLvoid*),void);
value glstub_glProgramStringARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glProgramStringARB);
	CALL_FUNCTION(glProgramStringARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glProgramVertexLimitNV,(GLenum, GLint),void);
value glstub_glProgramVertexLimitNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glProgramVertexLimitNV);
	CALL_FUNCTION(glProgramVertexLimitNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPushAttrib,(GLbitfield),void);
value glstub_glPushAttrib(value v0)
{
	CAMLparam1(v0);
	GLbitfield lv0 = Int_val(v0);
	LOAD_FUNCTION(glPushAttrib);
	CALL_FUNCTION(glPushAttrib)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPushClientAttrib,(GLbitfield),void);
value glstub_glPushClientAttrib(value v0)
{
	CAMLparam1(v0);
	GLbitfield lv0 = Int_val(v0);
	LOAD_FUNCTION(glPushClientAttrib);
	CALL_FUNCTION(glPushClientAttrib)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPushMatrix,(void),void);
value glstub_glPushMatrix(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glPushMatrix);
	CALL_FUNCTION(glPushMatrix)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glPushName,(GLuint),void);
value glstub_glPushName(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glPushName);
	CALL_FUNCTION(glPushName)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos2d,(GLdouble, GLdouble),void);
value glstub_glRasterPos2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glRasterPos2d);
	CALL_FUNCTION(glRasterPos2d)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos2dv,(GLdouble*),void);
value glstub_glRasterPos2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos2dv);
	CALL_FUNCTION(glRasterPos2dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos2f,(GLfloat, GLfloat),void);
value glstub_glRasterPos2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glRasterPos2f);
	CALL_FUNCTION(glRasterPos2f)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos2fv,(GLfloat*),void);
value glstub_glRasterPos2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos2fv);
	CALL_FUNCTION(glRasterPos2fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos2i,(GLint, GLint),void);
value glstub_glRasterPos2i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glRasterPos2i);
	CALL_FUNCTION(glRasterPos2i)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos2iv,(GLint*),void);
value glstub_glRasterPos2iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos2iv);
	CALL_FUNCTION(glRasterPos2iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos2s,(GLshort, GLshort),void);
value glstub_glRasterPos2s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glRasterPos2s);
	CALL_FUNCTION(glRasterPos2s)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos2sv,(GLshort*),void);
value glstub_glRasterPos2sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos2sv);
	CALL_FUNCTION(glRasterPos2sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos3d,(GLdouble, GLdouble, GLdouble),void);
value glstub_glRasterPos3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glRasterPos3d);
	CALL_FUNCTION(glRasterPos3d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos3dv,(GLdouble*),void);
value glstub_glRasterPos3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos3dv);
	CALL_FUNCTION(glRasterPos3dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos3f,(GLfloat, GLfloat, GLfloat),void);
value glstub_glRasterPos3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glRasterPos3f);
	CALL_FUNCTION(glRasterPos3f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos3fv,(GLfloat*),void);
value glstub_glRasterPos3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos3fv);
	CALL_FUNCTION(glRasterPos3fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos3i,(GLint, GLint, GLint),void);
value glstub_glRasterPos3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glRasterPos3i);
	CALL_FUNCTION(glRasterPos3i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos3iv,(GLint*),void);
value glstub_glRasterPos3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos3iv);
	CALL_FUNCTION(glRasterPos3iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos3s,(GLshort, GLshort, GLshort),void);
value glstub_glRasterPos3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glRasterPos3s);
	CALL_FUNCTION(glRasterPos3s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos3sv,(GLshort*),void);
value glstub_glRasterPos3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos3sv);
	CALL_FUNCTION(glRasterPos3sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos4d,(GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glRasterPos4d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glRasterPos4d);
	CALL_FUNCTION(glRasterPos4d)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos4dv,(GLdouble*),void);
value glstub_glRasterPos4dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos4dv);
	CALL_FUNCTION(glRasterPos4dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos4f,(GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glRasterPos4f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glRasterPos4f);
	CALL_FUNCTION(glRasterPos4f)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos4fv,(GLfloat*),void);
value glstub_glRasterPos4fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos4fv);
	CALL_FUNCTION(glRasterPos4fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos4i,(GLint, GLint, GLint, GLint),void);
value glstub_glRasterPos4i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glRasterPos4i);
	CALL_FUNCTION(glRasterPos4i)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos4iv,(GLint*),void);
value glstub_glRasterPos4iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos4iv);
	CALL_FUNCTION(glRasterPos4iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos4s,(GLshort, GLshort, GLshort, GLshort),void);
value glstub_glRasterPos4s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glRasterPos4s);
	CALL_FUNCTION(glRasterPos4s)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRasterPos4sv,(GLshort*),void);
value glstub_glRasterPos4sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glRasterPos4sv);
	CALL_FUNCTION(glRasterPos4sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReadBuffer,(GLenum),void);
value glstub_glReadBuffer(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glReadBuffer);
	CALL_FUNCTION(glReadBuffer)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReadPixels,(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glReadPixels(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glReadPixels);
	CALL_FUNCTION(glReadPixels)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glReadPixels_byte(value * argv, int n)
{
	return glstub_glReadPixels(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glReadVideoPixelsSUN,(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glReadVideoPixelsSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glReadVideoPixelsSUN);
	CALL_FUNCTION(glReadVideoPixelsSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glReadVideoPixelsSUN_byte(value * argv, int n)
{
	return glstub_glReadVideoPixelsSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glRectd,(GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glRectd(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glRectd);
	CALL_FUNCTION(glRectd)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRectdv,(GLdouble*, GLdouble*),void);
value glstub_glRectdv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glRectdv);
	CALL_FUNCTION(glRectdv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRectf,(GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glRectf(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glRectf);
	CALL_FUNCTION(glRectf)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRectfv,(GLfloat*, GLfloat*),void);
value glstub_glRectfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glRectfv);
	CALL_FUNCTION(glRectfv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRecti,(GLint, GLint, GLint, GLint),void);
value glstub_glRecti(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glRecti);
	CALL_FUNCTION(glRecti)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRectiv,(GLint*, GLint*),void);
value glstub_glRectiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint* lv0 = Data_bigarray_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glRectiv);
	CALL_FUNCTION(glRectiv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRects,(GLshort, GLshort, GLshort, GLshort),void);
value glstub_glRects(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glRects);
	CALL_FUNCTION(glRects)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRectsv,(GLshort*, GLshort*),void);
value glstub_glRectsv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort* lv0 = Data_bigarray_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glRectsv);
	CALL_FUNCTION(glRectsv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReferencePlaneSGIX,(GLdouble*),void);
value glstub_glReferencePlaneSGIX(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glReferencePlaneSGIX);
	CALL_FUNCTION(glReferencePlaneSGIX)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRenderMode,(GLenum),GLint);
value glstub_glRenderMode(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLint ret;
	LOAD_FUNCTION(glRenderMode);
	ret = CALL_FUNCTION(glRenderMode)(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glRenderbufferStorageEXT,(GLenum, GLenum, GLsizei, GLsizei),void);
value glstub_glRenderbufferStorageEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glRenderbufferStorageEXT);
	CALL_FUNCTION(glRenderbufferStorageEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRenderbufferStorageMultisampleCoverageNV,(GLenum, GLsizei, GLsizei, GLenum, GLsizei, GLsizei),void);
value glstub_glRenderbufferStorageMultisampleCoverageNV(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	LOAD_FUNCTION(glRenderbufferStorageMultisampleCoverageNV);
	CALL_FUNCTION(glRenderbufferStorageMultisampleCoverageNV)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glRenderbufferStorageMultisampleCoverageNV_byte(value * argv, int n)
{
	return glstub_glRenderbufferStorageMultisampleCoverageNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glRenderbufferStorageMultisampleEXT,(GLenum, GLsizei, GLenum, GLsizei, GLsizei),void);
value glstub_glRenderbufferStorageMultisampleEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	LOAD_FUNCTION(glRenderbufferStorageMultisampleEXT);
	CALL_FUNCTION(glRenderbufferStorageMultisampleEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodePointerSUN,(GLenum, GLsizei, GLvoid*),void);
value glstub_glReplacementCodePointerSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glReplacementCodePointerSUN);
	CALL_FUNCTION(glReplacementCodePointerSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeubSUN,(GLubyte),void);
value glstub_glReplacementCodeubSUN(value v0)
{
	CAMLparam1(v0);
	GLubyte lv0 = Int_val(v0);
	LOAD_FUNCTION(glReplacementCodeubSUN);
	CALL_FUNCTION(glReplacementCodeubSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeubvSUN,(GLubyte*),void);
value glstub_glReplacementCodeubvSUN(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glReplacementCodeubvSUN);
	CALL_FUNCTION(glReplacementCodeubvSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiColor3fVertex3fSUN,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glReplacementCodeuiColor3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	LOAD_FUNCTION(glReplacementCodeuiColor3fVertex3fSUN);
	CALL_FUNCTION(glReplacementCodeuiColor3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiColor3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiColor3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glReplacementCodeuiColor3fVertex3fvSUN,(GLuint*, GLfloat*, GLfloat*),void);
value glstub_glReplacementCodeuiColor3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glReplacementCodeuiColor3fVertex3fvSUN);
	CALL_FUNCTION(glReplacementCodeuiColor3fVertex3fvSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiColor4fNormal3fVertex3fSUN,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glReplacementCodeuiColor4fNormal3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam1(v10);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	GLfloat lv8 = Double_val(v8);
	GLfloat lv9 = Double_val(v9);
	GLfloat lv10 = Double_val(v10);
	LOAD_FUNCTION(glReplacementCodeuiColor4fNormal3fVertex3fSUN);
	CALL_FUNCTION(glReplacementCodeuiColor4fNormal3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiColor4fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiColor4fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

DECLARE_FUNCTION(glReplacementCodeuiColor4fNormal3fVertex3fvSUN,(GLuint*, GLfloat*, GLfloat*, GLfloat*),void);
value glstub_glReplacementCodeuiColor4fNormal3fVertex3fvSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glReplacementCodeuiColor4fNormal3fVertex3fvSUN);
	CALL_FUNCTION(glReplacementCodeuiColor4fNormal3fVertex3fvSUN)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiColor4ubVertex3fSUN,(GLuint, GLubyte, GLubyte, GLubyte, GLubyte, GLfloat, GLfloat, GLfloat),void);
value glstub_glReplacementCodeuiColor4ubVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLuint lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLubyte lv4 = Int_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	LOAD_FUNCTION(glReplacementCodeuiColor4ubVertex3fSUN);
	CALL_FUNCTION(glReplacementCodeuiColor4ubVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiColor4ubVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiColor4ubVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glReplacementCodeuiColor4ubVertex3fvSUN,(GLuint*, GLubyte*, GLfloat*),void);
value glstub_glReplacementCodeuiColor4ubVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glReplacementCodeuiColor4ubVertex3fvSUN);
	CALL_FUNCTION(glReplacementCodeuiColor4ubVertex3fvSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiNormal3fVertex3fSUN,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glReplacementCodeuiNormal3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	LOAD_FUNCTION(glReplacementCodeuiNormal3fVertex3fSUN);
	CALL_FUNCTION(glReplacementCodeuiNormal3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glReplacementCodeuiNormal3fVertex3fvSUN,(GLuint*, GLfloat*, GLfloat*),void);
value glstub_glReplacementCodeuiNormal3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glReplacementCodeuiNormal3fVertex3fvSUN);
	CALL_FUNCTION(glReplacementCodeuiNormal3fVertex3fvSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiSUN,(GLuint),void);
value glstub_glReplacementCodeuiSUN(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glReplacementCodeuiSUN);
	CALL_FUNCTION(glReplacementCodeuiSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10, value v11, value v12)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam3(v10, v11, v12);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	GLfloat lv8 = Double_val(v8);
	GLfloat lv9 = Double_val(v9);
	GLfloat lv10 = Double_val(v10);
	GLfloat lv11 = Double_val(v11);
	GLfloat lv12 = Double_val(v12);
	LOAD_FUNCTION(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN);
	CALL_FUNCTION(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11, lv12);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12]);
}

DECLARE_FUNCTION(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN,(GLuint*, GLfloat*, GLfloat*, GLfloat*, GLfloat*),void);
value glstub_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	GLfloat* lv4 = Data_bigarray_val(v4);
	LOAD_FUNCTION(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN);
	CALL_FUNCTION(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	GLfloat lv8 = Double_val(v8);
	LOAD_FUNCTION(glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN);
	CALL_FUNCTION(glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN,(GLuint*, GLfloat*, GLfloat*, GLfloat*),void);
value glstub_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN);
	CALL_FUNCTION(glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiTexCoord2fVertex3fSUN,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glReplacementCodeuiTexCoord2fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	LOAD_FUNCTION(glReplacementCodeuiTexCoord2fVertex3fSUN);
	CALL_FUNCTION(glReplacementCodeuiTexCoord2fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiTexCoord2fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiTexCoord2fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glReplacementCodeuiTexCoord2fVertex3fvSUN,(GLuint*, GLfloat*, GLfloat*),void);
value glstub_glReplacementCodeuiTexCoord2fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glReplacementCodeuiTexCoord2fVertex3fvSUN);
	CALL_FUNCTION(glReplacementCodeuiTexCoord2fVertex3fvSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiVertex3fSUN,(GLuint, GLfloat, GLfloat, GLfloat),void);
value glstub_glReplacementCodeuiVertex3fSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glReplacementCodeuiVertex3fSUN);
	CALL_FUNCTION(glReplacementCodeuiVertex3fSUN)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuiVertex3fvSUN,(GLuint*, GLfloat*),void);
value glstub_glReplacementCodeuiVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glReplacementCodeuiVertex3fvSUN);
	CALL_FUNCTION(glReplacementCodeuiVertex3fvSUN)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeuivSUN,(GLuint*),void);
value glstub_glReplacementCodeuivSUN(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glReplacementCodeuivSUN);
	CALL_FUNCTION(glReplacementCodeuivSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeusSUN,(GLushort),void);
value glstub_glReplacementCodeusSUN(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	LOAD_FUNCTION(glReplacementCodeusSUN);
	CALL_FUNCTION(glReplacementCodeusSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glReplacementCodeusvSUN,(GLushort*),void);
value glstub_glReplacementCodeusvSUN(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glReplacementCodeusvSUN);
	CALL_FUNCTION(glReplacementCodeusvSUN)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRequestResidentProgramsNV,(GLsizei, GLuint*),void);
value glstub_glRequestResidentProgramsNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glRequestResidentProgramsNV);
	CALL_FUNCTION(glRequestResidentProgramsNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glResetHistogram,(GLenum),void);
value glstub_glResetHistogram(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glResetHistogram);
	CALL_FUNCTION(glResetHistogram)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glResetHistogramEXT,(GLenum),void);
value glstub_glResetHistogramEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glResetHistogramEXT);
	CALL_FUNCTION(glResetHistogramEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glResetMinmax,(GLenum),void);
value glstub_glResetMinmax(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glResetMinmax);
	CALL_FUNCTION(glResetMinmax)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glResetMinmaxEXT,(GLenum),void);
value glstub_glResetMinmaxEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glResetMinmaxEXT);
	CALL_FUNCTION(glResetMinmaxEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glResizeBuffersMESA,(void),void);
value glstub_glResizeBuffersMESA(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glResizeBuffersMESA);
	CALL_FUNCTION(glResizeBuffersMESA)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRotated,(GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glRotated(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glRotated);
	CALL_FUNCTION(glRotated)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glRotatef,(GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glRotatef(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glRotatef);
	CALL_FUNCTION(glRotatef)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSampleCoverage,(GLclampf, GLboolean),void);
value glstub_glSampleCoverage(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLboolean lv1 = Bool_val(v1);
	LOAD_FUNCTION(glSampleCoverage);
	CALL_FUNCTION(glSampleCoverage)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSampleCoverageARB,(GLclampf, GLboolean),void);
value glstub_glSampleCoverageARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLboolean lv1 = Bool_val(v1);
	LOAD_FUNCTION(glSampleCoverageARB);
	CALL_FUNCTION(glSampleCoverageARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSampleMapATI,(GLuint, GLuint, GLenum),void);
value glstub_glSampleMapATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	LOAD_FUNCTION(glSampleMapATI);
	CALL_FUNCTION(glSampleMapATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSampleMaskEXT,(GLclampf, GLboolean),void);
value glstub_glSampleMaskEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLboolean lv1 = Bool_val(v1);
	LOAD_FUNCTION(glSampleMaskEXT);
	CALL_FUNCTION(glSampleMaskEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSampleMaskSGIS,(GLclampf, GLboolean),void);
value glstub_glSampleMaskSGIS(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLboolean lv1 = Bool_val(v1);
	LOAD_FUNCTION(glSampleMaskSGIS);
	CALL_FUNCTION(glSampleMaskSGIS)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSamplePatternEXT,(GLenum),void);
value glstub_glSamplePatternEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glSamplePatternEXT);
	CALL_FUNCTION(glSamplePatternEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSamplePatternSGIS,(GLenum),void);
value glstub_glSamplePatternSGIS(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glSamplePatternSGIS);
	CALL_FUNCTION(glSamplePatternSGIS)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glScaled,(GLdouble, GLdouble, GLdouble),void);
value glstub_glScaled(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glScaled);
	CALL_FUNCTION(glScaled)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glScalef,(GLfloat, GLfloat, GLfloat),void);
value glstub_glScalef(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glScalef);
	CALL_FUNCTION(glScalef)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glScissor,(GLint, GLint, GLsizei, GLsizei),void);
value glstub_glScissor(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glScissor);
	CALL_FUNCTION(glScissor)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3b,(GLbyte, GLbyte, GLbyte),void);
value glstub_glSecondaryColor3b(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3b);
	CALL_FUNCTION(glSecondaryColor3b)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3bEXT,(GLbyte, GLbyte, GLbyte),void);
value glstub_glSecondaryColor3bEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3bEXT);
	CALL_FUNCTION(glSecondaryColor3bEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3bv,(GLbyte*),void);
value glstub_glSecondaryColor3bv(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3bv);
	CALL_FUNCTION(glSecondaryColor3bv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3bvEXT,(GLbyte*),void);
value glstub_glSecondaryColor3bvEXT(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3bvEXT);
	CALL_FUNCTION(glSecondaryColor3bvEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3d,(GLdouble, GLdouble, GLdouble),void);
value glstub_glSecondaryColor3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glSecondaryColor3d);
	CALL_FUNCTION(glSecondaryColor3d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3dEXT,(GLdouble, GLdouble, GLdouble),void);
value glstub_glSecondaryColor3dEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glSecondaryColor3dEXT);
	CALL_FUNCTION(glSecondaryColor3dEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3dv,(GLdouble*),void);
value glstub_glSecondaryColor3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3dv);
	CALL_FUNCTION(glSecondaryColor3dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3dvEXT,(GLdouble*),void);
value glstub_glSecondaryColor3dvEXT(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3dvEXT);
	CALL_FUNCTION(glSecondaryColor3dvEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3f,(GLfloat, GLfloat, GLfloat),void);
value glstub_glSecondaryColor3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glSecondaryColor3f);
	CALL_FUNCTION(glSecondaryColor3f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3fEXT,(GLfloat, GLfloat, GLfloat),void);
value glstub_glSecondaryColor3fEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glSecondaryColor3fEXT);
	CALL_FUNCTION(glSecondaryColor3fEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3fv,(GLfloat*),void);
value glstub_glSecondaryColor3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3fv);
	CALL_FUNCTION(glSecondaryColor3fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3fvEXT,(GLfloat*),void);
value glstub_glSecondaryColor3fvEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3fvEXT);
	CALL_FUNCTION(glSecondaryColor3fvEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3hNV,(GLushort, GLushort, GLushort),void);
value glstub_glSecondaryColor3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3hNV);
	CALL_FUNCTION(glSecondaryColor3hNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3hvNV,(GLushort*),void);
value glstub_glSecondaryColor3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3hvNV);
	CALL_FUNCTION(glSecondaryColor3hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3i,(GLint, GLint, GLint),void);
value glstub_glSecondaryColor3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3i);
	CALL_FUNCTION(glSecondaryColor3i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3iEXT,(GLint, GLint, GLint),void);
value glstub_glSecondaryColor3iEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3iEXT);
	CALL_FUNCTION(glSecondaryColor3iEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3iv,(GLint*),void);
value glstub_glSecondaryColor3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3iv);
	CALL_FUNCTION(glSecondaryColor3iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3ivEXT,(GLint*),void);
value glstub_glSecondaryColor3ivEXT(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3ivEXT);
	CALL_FUNCTION(glSecondaryColor3ivEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3s,(GLshort, GLshort, GLshort),void);
value glstub_glSecondaryColor3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3s);
	CALL_FUNCTION(glSecondaryColor3s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3sEXT,(GLshort, GLshort, GLshort),void);
value glstub_glSecondaryColor3sEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3sEXT);
	CALL_FUNCTION(glSecondaryColor3sEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3sv,(GLshort*),void);
value glstub_glSecondaryColor3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3sv);
	CALL_FUNCTION(glSecondaryColor3sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3svEXT,(GLshort*),void);
value glstub_glSecondaryColor3svEXT(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3svEXT);
	CALL_FUNCTION(glSecondaryColor3svEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3ub,(GLubyte, GLubyte, GLubyte),void);
value glstub_glSecondaryColor3ub(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3ub);
	CALL_FUNCTION(glSecondaryColor3ub)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3ubEXT,(GLubyte, GLubyte, GLubyte),void);
value glstub_glSecondaryColor3ubEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3ubEXT);
	CALL_FUNCTION(glSecondaryColor3ubEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3ubv,(GLubyte*),void);
value glstub_glSecondaryColor3ubv(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3ubv);
	CALL_FUNCTION(glSecondaryColor3ubv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3ubvEXT,(GLubyte*),void);
value glstub_glSecondaryColor3ubvEXT(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3ubvEXT);
	CALL_FUNCTION(glSecondaryColor3ubvEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3ui,(GLuint, GLuint, GLuint),void);
value glstub_glSecondaryColor3ui(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3ui);
	CALL_FUNCTION(glSecondaryColor3ui)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3uiEXT,(GLuint, GLuint, GLuint),void);
value glstub_glSecondaryColor3uiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3uiEXT);
	CALL_FUNCTION(glSecondaryColor3uiEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3uiv,(GLuint*),void);
value glstub_glSecondaryColor3uiv(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3uiv);
	CALL_FUNCTION(glSecondaryColor3uiv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3uivEXT,(GLuint*),void);
value glstub_glSecondaryColor3uivEXT(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3uivEXT);
	CALL_FUNCTION(glSecondaryColor3uivEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3us,(GLushort, GLushort, GLushort),void);
value glstub_glSecondaryColor3us(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3us);
	CALL_FUNCTION(glSecondaryColor3us)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3usEXT,(GLushort, GLushort, GLushort),void);
value glstub_glSecondaryColor3usEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glSecondaryColor3usEXT);
	CALL_FUNCTION(glSecondaryColor3usEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3usv,(GLushort*),void);
value glstub_glSecondaryColor3usv(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3usv);
	CALL_FUNCTION(glSecondaryColor3usv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColor3usvEXT,(GLushort*),void);
value glstub_glSecondaryColor3usvEXT(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glSecondaryColor3usvEXT);
	CALL_FUNCTION(glSecondaryColor3usvEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColorPointer,(GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glSecondaryColorPointer(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glSecondaryColorPointer);
	CALL_FUNCTION(glSecondaryColorPointer)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColorPointerEXT,(GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glSecondaryColorPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glSecondaryColorPointerEXT);
	CALL_FUNCTION(glSecondaryColorPointerEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSecondaryColorPointerListIBM,(GLint, GLenum, GLint, GLvoid**, GLint),void);
value glstub_glSecondaryColorPointerListIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glSecondaryColorPointerListIBM);
	CALL_FUNCTION(glSecondaryColorPointerListIBM)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSelectBuffer,(GLsizei, GLuint*),void);
value glstub_glSelectBuffer(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glSelectBuffer);
	CALL_FUNCTION(glSelectBuffer)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSeparableFilter2D,(GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, GLvoid*, GLvoid*),void);
value glstub_glSeparableFilter2D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	GLvoid* lv7 = (Is_long(v7) ? (GLvoid*)Long_val(v7) : ((Tag_val(v7) == String_tag)? (String_val(v7)) : (Data_bigarray_val(v7))));
	LOAD_FUNCTION(glSeparableFilter2D);
	CALL_FUNCTION(glSeparableFilter2D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glSeparableFilter2D_byte(value * argv, int n)
{
	return glstub_glSeparableFilter2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glSeparableFilter2DEXT,(GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, GLvoid*, GLvoid*),void);
value glstub_glSeparableFilter2DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	GLvoid* lv7 = (Is_long(v7) ? (GLvoid*)Long_val(v7) : ((Tag_val(v7) == String_tag)? (String_val(v7)) : (Data_bigarray_val(v7))));
	LOAD_FUNCTION(glSeparableFilter2DEXT);
	CALL_FUNCTION(glSeparableFilter2DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glSeparableFilter2DEXT_byte(value * argv, int n)
{
	return glstub_glSeparableFilter2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glSetFenceAPPLE,(GLuint),void);
value glstub_glSetFenceAPPLE(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glSetFenceAPPLE);
	CALL_FUNCTION(glSetFenceAPPLE)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSetFenceNV,(GLuint, GLenum),void);
value glstub_glSetFenceNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glSetFenceNV);
	CALL_FUNCTION(glSetFenceNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSetFragmentShaderConstantATI,(GLuint, GLfloat*),void);
value glstub_glSetFragmentShaderConstantATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glSetFragmentShaderConstantATI);
	CALL_FUNCTION(glSetFragmentShaderConstantATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSetInvariantEXT,(GLuint, GLenum, GLvoid*),void);
value glstub_glSetInvariantEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glSetInvariantEXT);
	CALL_FUNCTION(glSetInvariantEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSetLocalConstantEXT,(GLuint, GLenum, GLvoid*),void);
value glstub_glSetLocalConstantEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glSetLocalConstantEXT);
	CALL_FUNCTION(glSetLocalConstantEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glShadeModel,(GLenum),void);
value glstub_glShadeModel(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glShadeModel);
	CALL_FUNCTION(glShadeModel)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glShaderOp1EXT,(GLenum, GLuint, GLuint),void);
value glstub_glShaderOp1EXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glShaderOp1EXT);
	CALL_FUNCTION(glShaderOp1EXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glShaderOp2EXT,(GLenum, GLuint, GLuint, GLuint),void);
value glstub_glShaderOp2EXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	LOAD_FUNCTION(glShaderOp2EXT);
	CALL_FUNCTION(glShaderOp2EXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glShaderOp3EXT,(GLenum, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glShaderOp3EXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	LOAD_FUNCTION(glShaderOp3EXT);
	CALL_FUNCTION(glShaderOp3EXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glShaderSource,(GLuint, GLsizei, GLchar**, GLint*),void);
value glstub_glShaderSource(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLchar** lv2 = (GLchar** )(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glShaderSource);
	CALL_FUNCTION(glShaderSource)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glShaderSourceARB,(GLuint, GLsizei, GLchar**, GLint*),void);
value glstub_glShaderSourceARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLchar** lv2 = (GLchar** )(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glShaderSourceARB);
	CALL_FUNCTION(glShaderSourceARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSharpenTexFuncSGIS,(GLenum, GLsizei, GLfloat*),void);
value glstub_glSharpenTexFuncSGIS(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glSharpenTexFuncSGIS);
	CALL_FUNCTION(glSharpenTexFuncSGIS)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSpriteParameterfSGIX,(GLenum, GLfloat),void);
value glstub_glSpriteParameterfSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glSpriteParameterfSGIX);
	CALL_FUNCTION(glSpriteParameterfSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSpriteParameterfvSGIX,(GLenum, GLfloat*),void);
value glstub_glSpriteParameterfvSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glSpriteParameterfvSGIX);
	CALL_FUNCTION(glSpriteParameterfvSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSpriteParameteriSGIX,(GLenum, GLint),void);
value glstub_glSpriteParameteriSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glSpriteParameteriSGIX);
	CALL_FUNCTION(glSpriteParameteriSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSpriteParameterivSGIX,(GLenum, GLint*),void);
value glstub_glSpriteParameterivSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glSpriteParameterivSGIX);
	CALL_FUNCTION(glSpriteParameterivSGIX)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStencilFunc,(GLenum, GLint, GLuint),void);
value glstub_glStencilFunc(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glStencilFunc);
	CALL_FUNCTION(glStencilFunc)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStencilFuncSeparate,(GLenum, GLenum, GLint, GLuint),void);
value glstub_glStencilFuncSeparate(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	LOAD_FUNCTION(glStencilFuncSeparate);
	CALL_FUNCTION(glStencilFuncSeparate)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStencilFuncSeparateATI,(GLenum, GLenum, GLint, GLuint),void);
value glstub_glStencilFuncSeparateATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	LOAD_FUNCTION(glStencilFuncSeparateATI);
	CALL_FUNCTION(glStencilFuncSeparateATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStencilMask,(GLuint),void);
value glstub_glStencilMask(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glStencilMask);
	CALL_FUNCTION(glStencilMask)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStencilMaskSeparate,(GLenum, GLuint),void);
value glstub_glStencilMaskSeparate(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glStencilMaskSeparate);
	CALL_FUNCTION(glStencilMaskSeparate)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStencilOp,(GLenum, GLenum, GLenum),void);
value glstub_glStencilOp(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	LOAD_FUNCTION(glStencilOp);
	CALL_FUNCTION(glStencilOp)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStencilOpSeparate,(GLenum, GLenum, GLenum, GLenum),void);
value glstub_glStencilOpSeparate(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glStencilOpSeparate);
	CALL_FUNCTION(glStencilOpSeparate)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStencilOpSeparateATI,(GLenum, GLenum, GLenum, GLenum),void);
value glstub_glStencilOpSeparateATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glStencilOpSeparateATI);
	CALL_FUNCTION(glStencilOpSeparateATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glStringMarkerGREMEDY,(GLsizei, GLvoid*),void);
value glstub_glStringMarkerGREMEDY(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	LOAD_FUNCTION(glStringMarkerGREMEDY);
	CALL_FUNCTION(glStringMarkerGREMEDY)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glSwizzleEXT,(GLuint, GLuint, GLenum, GLenum, GLenum, GLenum),void);
value glstub_glSwizzleEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	LOAD_FUNCTION(glSwizzleEXT);
	CALL_FUNCTION(glSwizzleEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glSwizzleEXT_byte(value * argv, int n)
{
	return glstub_glSwizzleEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glTagSampleBufferSGIX,(void),void);
value glstub_glTagSampleBufferSGIX(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glTagSampleBufferSGIX);
	CALL_FUNCTION(glTagSampleBufferSGIX)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTangentPointerEXT,(GLenum, GLsizei, GLvoid*),void);
value glstub_glTangentPointerEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glTangentPointerEXT);
	CALL_FUNCTION(glTangentPointerEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTbufferMask3DFX,(GLuint),void);
value glstub_glTbufferMask3DFX(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glTbufferMask3DFX);
	CALL_FUNCTION(glTbufferMask3DFX)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTestFenceAPPLE,(GLuint),GLboolean);
value glstub_glTestFenceAPPLE(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glTestFenceAPPLE);
	ret = CALL_FUNCTION(glTestFenceAPPLE)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glTestFenceNV,(GLuint),GLboolean);
value glstub_glTestFenceNV(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glTestFenceNV);
	ret = CALL_FUNCTION(glTestFenceNV)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glTestObjectAPPLE,(GLenum, GLuint),GLboolean);
value glstub_glTestObjectAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLboolean ret;
	LOAD_FUNCTION(glTestObjectAPPLE);
	ret = CALL_FUNCTION(glTestObjectAPPLE)(lv0, lv1);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glTexBufferEXT,(GLenum, GLenum, GLuint),void);
value glstub_glTexBufferEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glTexBufferEXT);
	CALL_FUNCTION(glTexBufferEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexBumpParameterfvATI,(GLenum, GLfloat*),void);
value glstub_glTexBumpParameterfvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glTexBumpParameterfvATI);
	CALL_FUNCTION(glTexBumpParameterfvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexBumpParameterivATI,(GLenum, GLint*),void);
value glstub_glTexBumpParameterivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glTexBumpParameterivATI);
	CALL_FUNCTION(glTexBumpParameterivATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1d,(GLdouble),void);
value glstub_glTexCoord1d(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	LOAD_FUNCTION(glTexCoord1d);
	CALL_FUNCTION(glTexCoord1d)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1dv,(GLdouble*),void);
value glstub_glTexCoord1dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord1dv);
	CALL_FUNCTION(glTexCoord1dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1f,(GLfloat),void);
value glstub_glTexCoord1f(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glTexCoord1f);
	CALL_FUNCTION(glTexCoord1f)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1fv,(GLfloat*),void);
value glstub_glTexCoord1fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord1fv);
	CALL_FUNCTION(glTexCoord1fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1hNV,(GLushort),void);
value glstub_glTexCoord1hNV(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	LOAD_FUNCTION(glTexCoord1hNV);
	CALL_FUNCTION(glTexCoord1hNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1hvNV,(GLushort*),void);
value glstub_glTexCoord1hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord1hvNV);
	CALL_FUNCTION(glTexCoord1hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1i,(GLint),void);
value glstub_glTexCoord1i(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glTexCoord1i);
	CALL_FUNCTION(glTexCoord1i)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1iv,(GLint*),void);
value glstub_glTexCoord1iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord1iv);
	CALL_FUNCTION(glTexCoord1iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1s,(GLshort),void);
value glstub_glTexCoord1s(value v0)
{
	CAMLparam1(v0);
	GLshort lv0 = Int_val(v0);
	LOAD_FUNCTION(glTexCoord1s);
	CALL_FUNCTION(glTexCoord1s)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord1sv,(GLshort*),void);
value glstub_glTexCoord1sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord1sv);
	CALL_FUNCTION(glTexCoord1sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2d,(GLdouble, GLdouble),void);
value glstub_glTexCoord2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glTexCoord2d);
	CALL_FUNCTION(glTexCoord2d)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2dv,(GLdouble*),void);
value glstub_glTexCoord2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord2dv);
	CALL_FUNCTION(glTexCoord2dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2f,(GLfloat, GLfloat),void);
value glstub_glTexCoord2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glTexCoord2f);
	CALL_FUNCTION(glTexCoord2f)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2fColor3fVertex3fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord2fColor3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	LOAD_FUNCTION(glTexCoord2fColor3fVertex3fSUN);
	CALL_FUNCTION(glTexCoord2fColor3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fColor3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord2fColor3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glTexCoord2fColor3fVertex3fvSUN,(GLfloat*, GLfloat*, GLfloat*),void);
value glstub_glTexCoord2fColor3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexCoord2fColor3fVertex3fvSUN);
	CALL_FUNCTION(glTexCoord2fColor3fVertex3fvSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2fColor4fNormal3fVertex3fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord2fColor4fNormal3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10, value v11)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam2(v10, v11);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	GLfloat lv8 = Double_val(v8);
	GLfloat lv9 = Double_val(v9);
	GLfloat lv10 = Double_val(v10);
	GLfloat lv11 = Double_val(v11);
	LOAD_FUNCTION(glTexCoord2fColor4fNormal3fVertex3fSUN);
	CALL_FUNCTION(glTexCoord2fColor4fNormal3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fColor4fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord2fColor4fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11]);
}

DECLARE_FUNCTION(glTexCoord2fColor4fNormal3fVertex3fvSUN,(GLfloat*, GLfloat*, GLfloat*, GLfloat*),void);
value glstub_glTexCoord2fColor4fNormal3fVertex3fvSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glTexCoord2fColor4fNormal3fVertex3fvSUN);
	CALL_FUNCTION(glTexCoord2fColor4fNormal3fVertex3fvSUN)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2fColor4ubVertex3fSUN,(GLfloat, GLfloat, GLubyte, GLubyte, GLubyte, GLubyte, GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord2fColor4ubVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLubyte lv4 = Int_val(v4);
	GLubyte lv5 = Int_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	GLfloat lv8 = Double_val(v8);
	LOAD_FUNCTION(glTexCoord2fColor4ubVertex3fSUN);
	CALL_FUNCTION(glTexCoord2fColor4ubVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fColor4ubVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord2fColor4ubVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glTexCoord2fColor4ubVertex3fvSUN,(GLfloat*, GLubyte*, GLfloat*),void);
value glstub_glTexCoord2fColor4ubVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexCoord2fColor4ubVertex3fvSUN);
	CALL_FUNCTION(glTexCoord2fColor4ubVertex3fvSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2fNormal3fVertex3fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord2fNormal3fVertex3fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	LOAD_FUNCTION(glTexCoord2fNormal3fVertex3fSUN);
	CALL_FUNCTION(glTexCoord2fNormal3fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord2fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glTexCoord2fNormal3fVertex3fvSUN,(GLfloat*, GLfloat*, GLfloat*),void);
value glstub_glTexCoord2fNormal3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexCoord2fNormal3fVertex3fvSUN);
	CALL_FUNCTION(glTexCoord2fNormal3fVertex3fvSUN)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2fVertex3fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord2fVertex3fSUN(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glTexCoord2fVertex3fSUN);
	CALL_FUNCTION(glTexCoord2fVertex3fSUN)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2fVertex3fvSUN,(GLfloat*, GLfloat*),void);
value glstub_glTexCoord2fVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glTexCoord2fVertex3fvSUN);
	CALL_FUNCTION(glTexCoord2fVertex3fvSUN)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2fv,(GLfloat*),void);
value glstub_glTexCoord2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord2fv);
	CALL_FUNCTION(glTexCoord2fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2hNV,(GLushort, GLushort),void);
value glstub_glTexCoord2hNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	LOAD_FUNCTION(glTexCoord2hNV);
	CALL_FUNCTION(glTexCoord2hNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2hvNV,(GLushort*),void);
value glstub_glTexCoord2hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord2hvNV);
	CALL_FUNCTION(glTexCoord2hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2i,(GLint, GLint),void);
value glstub_glTexCoord2i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glTexCoord2i);
	CALL_FUNCTION(glTexCoord2i)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2iv,(GLint*),void);
value glstub_glTexCoord2iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord2iv);
	CALL_FUNCTION(glTexCoord2iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2s,(GLshort, GLshort),void);
value glstub_glTexCoord2s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glTexCoord2s);
	CALL_FUNCTION(glTexCoord2s)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord2sv,(GLshort*),void);
value glstub_glTexCoord2sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord2sv);
	CALL_FUNCTION(glTexCoord2sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3d,(GLdouble, GLdouble, GLdouble),void);
value glstub_glTexCoord3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glTexCoord3d);
	CALL_FUNCTION(glTexCoord3d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3dv,(GLdouble*),void);
value glstub_glTexCoord3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord3dv);
	CALL_FUNCTION(glTexCoord3dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3f,(GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glTexCoord3f);
	CALL_FUNCTION(glTexCoord3f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3fv,(GLfloat*),void);
value glstub_glTexCoord3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord3fv);
	CALL_FUNCTION(glTexCoord3fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3hNV,(GLushort, GLushort, GLushort),void);
value glstub_glTexCoord3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glTexCoord3hNV);
	CALL_FUNCTION(glTexCoord3hNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3hvNV,(GLushort*),void);
value glstub_glTexCoord3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord3hvNV);
	CALL_FUNCTION(glTexCoord3hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3i,(GLint, GLint, GLint),void);
value glstub_glTexCoord3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glTexCoord3i);
	CALL_FUNCTION(glTexCoord3i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3iv,(GLint*),void);
value glstub_glTexCoord3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord3iv);
	CALL_FUNCTION(glTexCoord3iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3s,(GLshort, GLshort, GLshort),void);
value glstub_glTexCoord3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glTexCoord3s);
	CALL_FUNCTION(glTexCoord3s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord3sv,(GLshort*),void);
value glstub_glTexCoord3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord3sv);
	CALL_FUNCTION(glTexCoord3sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4d,(GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glTexCoord4d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glTexCoord4d);
	CALL_FUNCTION(glTexCoord4d)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4dv,(GLdouble*),void);
value glstub_glTexCoord4dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord4dv);
	CALL_FUNCTION(glTexCoord4dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4f,(GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord4f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glTexCoord4f);
	CALL_FUNCTION(glTexCoord4f)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4fColor4fNormal3fVertex4fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord4fColor4fNormal3fVertex4fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10, value v11, value v12, value v13, value v14)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam5(v10, v11, v12, v13, v14);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	GLfloat lv8 = Double_val(v8);
	GLfloat lv9 = Double_val(v9);
	GLfloat lv10 = Double_val(v10);
	GLfloat lv11 = Double_val(v11);
	GLfloat lv12 = Double_val(v12);
	GLfloat lv13 = Double_val(v13);
	GLfloat lv14 = Double_val(v14);
	LOAD_FUNCTION(glTexCoord4fColor4fNormal3fVertex4fSUN);
	CALL_FUNCTION(glTexCoord4fColor4fNormal3fVertex4fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11, lv12, lv13, lv14);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4fColor4fNormal3fVertex4fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord4fColor4fNormal3fVertex4fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14]);
}

DECLARE_FUNCTION(glTexCoord4fColor4fNormal3fVertex4fvSUN,(GLfloat*, GLfloat*, GLfloat*, GLfloat*),void);
value glstub_glTexCoord4fColor4fNormal3fVertex4fvSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glTexCoord4fColor4fNormal3fVertex4fvSUN);
	CALL_FUNCTION(glTexCoord4fColor4fNormal3fVertex4fvSUN)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4fVertex4fSUN,(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glTexCoord4fVertex4fSUN(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	GLfloat lv5 = Double_val(v5);
	GLfloat lv6 = Double_val(v6);
	GLfloat lv7 = Double_val(v7);
	LOAD_FUNCTION(glTexCoord4fVertex4fSUN);
	CALL_FUNCTION(glTexCoord4fVertex4fSUN)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4fVertex4fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord4fVertex4fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glTexCoord4fVertex4fvSUN,(GLfloat*, GLfloat*),void);
value glstub_glTexCoord4fVertex4fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glTexCoord4fVertex4fvSUN);
	CALL_FUNCTION(glTexCoord4fVertex4fvSUN)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4fv,(GLfloat*),void);
value glstub_glTexCoord4fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord4fv);
	CALL_FUNCTION(glTexCoord4fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4hNV,(GLushort, GLushort, GLushort, GLushort),void);
value glstub_glTexCoord4hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	LOAD_FUNCTION(glTexCoord4hNV);
	CALL_FUNCTION(glTexCoord4hNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4hvNV,(GLushort*),void);
value glstub_glTexCoord4hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord4hvNV);
	CALL_FUNCTION(glTexCoord4hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4i,(GLint, GLint, GLint, GLint),void);
value glstub_glTexCoord4i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glTexCoord4i);
	CALL_FUNCTION(glTexCoord4i)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4iv,(GLint*),void);
value glstub_glTexCoord4iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord4iv);
	CALL_FUNCTION(glTexCoord4iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4s,(GLshort, GLshort, GLshort, GLshort),void);
value glstub_glTexCoord4s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glTexCoord4s);
	CALL_FUNCTION(glTexCoord4s)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoord4sv,(GLshort*),void);
value glstub_glTexCoord4sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glTexCoord4sv);
	CALL_FUNCTION(glTexCoord4sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoordPointer,(GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glTexCoordPointer(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glTexCoordPointer);
	CALL_FUNCTION(glTexCoordPointer)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoordPointerEXT,(GLint, GLenum, GLsizei, GLsizei, GLvoid*),void);
value glstub_glTexCoordPointerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glTexCoordPointerEXT);
	CALL_FUNCTION(glTexCoordPointerEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoordPointerListIBM,(GLint, GLenum, GLint, GLvoid**, GLint),void);
value glstub_glTexCoordPointerListIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glTexCoordPointerListIBM);
	CALL_FUNCTION(glTexCoordPointerListIBM)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexCoordPointervINTEL,(GLint, GLenum, GLvoid**),void);
value glstub_glTexCoordPointervINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexCoordPointervINTEL);
	CALL_FUNCTION(glTexCoordPointervINTEL)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexEnvf,(GLenum, GLenum, GLfloat),void);
value glstub_glTexEnvf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glTexEnvf);
	CALL_FUNCTION(glTexEnvf)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexEnvfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glTexEnvfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexEnvfv);
	CALL_FUNCTION(glTexEnvfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexEnvi,(GLenum, GLenum, GLint),void);
value glstub_glTexEnvi(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glTexEnvi);
	CALL_FUNCTION(glTexEnvi)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexEnviv,(GLenum, GLenum, GLint*),void);
value glstub_glTexEnviv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexEnviv);
	CALL_FUNCTION(glTexEnviv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexFilterFuncSGIS,(GLenum, GLenum, GLsizei, GLfloat*),void);
value glstub_glTexFilterFuncSGIS(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glTexFilterFuncSGIS);
	CALL_FUNCTION(glTexFilterFuncSGIS)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexGend,(GLenum, GLenum, GLdouble),void);
value glstub_glTexGend(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glTexGend);
	CALL_FUNCTION(glTexGend)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexGendv,(GLenum, GLenum, GLdouble*),void);
value glstub_glTexGendv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexGendv);
	CALL_FUNCTION(glTexGendv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexGenf,(GLenum, GLenum, GLfloat),void);
value glstub_glTexGenf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glTexGenf);
	CALL_FUNCTION(glTexGenf)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexGenfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glTexGenfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexGenfv);
	CALL_FUNCTION(glTexGenfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexGeni,(GLenum, GLenum, GLint),void);
value glstub_glTexGeni(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glTexGeni);
	CALL_FUNCTION(glTexGeni)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexGeniv,(GLenum, GLenum, GLint*),void);
value glstub_glTexGeniv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexGeniv);
	CALL_FUNCTION(glTexGeniv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexImage1D,(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, GLvoid*),void);
value glstub_glTexImage1D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam3(v5, v6, v7);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLenum lv6 = Int_val(v6);
	GLvoid* lv7 = (Is_long(v7) ? (GLvoid*)Long_val(v7) : ((Tag_val(v7) == String_tag)? (String_val(v7)) : (Data_bigarray_val(v7))));
	LOAD_FUNCTION(glTexImage1D);
	CALL_FUNCTION(glTexImage1D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage1D_byte(value * argv, int n)
{
	return glstub_glTexImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

DECLARE_FUNCTION(glTexImage2D,(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, GLvoid*),void);
value glstub_glTexImage2D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLenum lv6 = Int_val(v6);
	GLenum lv7 = Int_val(v7);
	GLvoid* lv8 = (Is_long(v8) ? (GLvoid*)Long_val(v8) : ((Tag_val(v8) == String_tag)? (String_val(v8)) : (Data_bigarray_val(v8))));
	LOAD_FUNCTION(glTexImage2D);
	CALL_FUNCTION(glTexImage2D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage2D_byte(value * argv, int n)
{
	return glstub_glTexImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glTexImage3D,(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, GLvoid*),void);
value glstub_glTexImage3D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	GLenum lv7 = Int_val(v7);
	GLenum lv8 = Int_val(v8);
	GLvoid* lv9 = (Is_long(v9) ? (GLvoid*)Long_val(v9) : ((Tag_val(v9) == String_tag)? (String_val(v9)) : (Data_bigarray_val(v9))));
	LOAD_FUNCTION(glTexImage3D);
	CALL_FUNCTION(glTexImage3D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage3D_byte(value * argv, int n)
{
	return glstub_glTexImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

DECLARE_FUNCTION(glTexImage3DEXT,(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, GLvoid*),void);
value glstub_glTexImage3DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLint lv6 = Int_val(v6);
	GLenum lv7 = Int_val(v7);
	GLenum lv8 = Int_val(v8);
	GLvoid* lv9 = (Is_long(v9) ? (GLvoid*)Long_val(v9) : ((Tag_val(v9) == String_tag)? (String_val(v9)) : (Data_bigarray_val(v9))));
	LOAD_FUNCTION(glTexImage3DEXT);
	CALL_FUNCTION(glTexImage3DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage3DEXT_byte(value * argv, int n)
{
	return glstub_glTexImage3DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

DECLARE_FUNCTION(glTexImage4DSGIS,(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, GLvoid*),void);
value glstub_glTexImage4DSGIS(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam1(v10);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLint lv7 = Int_val(v7);
	GLenum lv8 = Int_val(v8);
	GLenum lv9 = Int_val(v9);
	GLvoid* lv10 = (Is_long(v10) ? (GLvoid*)Long_val(v10) : ((Tag_val(v10) == String_tag)? (String_val(v10)) : (Data_bigarray_val(v10))));
	LOAD_FUNCTION(glTexImage4DSGIS);
	CALL_FUNCTION(glTexImage4DSGIS)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage4DSGIS_byte(value * argv, int n)
{
	return glstub_glTexImage4DSGIS(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

DECLARE_FUNCTION(glTexParameterIivEXT,(GLenum, GLenum, GLint*),void);
value glstub_glTexParameterIivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexParameterIivEXT);
	CALL_FUNCTION(glTexParameterIivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexParameterIuivEXT,(GLenum, GLenum, GLuint*),void);
value glstub_glTexParameterIuivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexParameterIuivEXT);
	CALL_FUNCTION(glTexParameterIuivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexParameterf,(GLenum, GLenum, GLfloat),void);
value glstub_glTexParameterf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glTexParameterf);
	CALL_FUNCTION(glTexParameterf)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexParameterfv,(GLenum, GLenum, GLfloat*),void);
value glstub_glTexParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexParameterfv);
	CALL_FUNCTION(glTexParameterfv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexParameteri,(GLenum, GLenum, GLint),void);
value glstub_glTexParameteri(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glTexParameteri);
	CALL_FUNCTION(glTexParameteri)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexParameteriv,(GLenum, GLenum, GLint*),void);
value glstub_glTexParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glTexParameteriv);
	CALL_FUNCTION(glTexParameteriv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexScissorFuncINTEL,(GLenum, GLenum, GLenum),void);
value glstub_glTexScissorFuncINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	LOAD_FUNCTION(glTexScissorFuncINTEL);
	CALL_FUNCTION(glTexScissorFuncINTEL)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexScissorINTEL,(GLenum, GLclampf, GLclampf),void);
value glstub_glTexScissorINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLclampf lv1 = Double_val(v1);
	GLclampf lv2 = Double_val(v2);
	LOAD_FUNCTION(glTexScissorINTEL);
	CALL_FUNCTION(glTexScissorINTEL)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTexSubImage1D,(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glTexSubImage1D(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glTexSubImage1D);
	CALL_FUNCTION(glTexSubImage1D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage1D_byte(value * argv, int n)
{
	return glstub_glTexSubImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glTexSubImage1DEXT,(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glTexSubImage1DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	GLvoid* lv6 = (Is_long(v6) ? (GLvoid*)Long_val(v6) : ((Tag_val(v6) == String_tag)? (String_val(v6)) : (Data_bigarray_val(v6))));
	LOAD_FUNCTION(glTexSubImage1DEXT);
	CALL_FUNCTION(glTexSubImage1DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage1DEXT_byte(value * argv, int n)
{
	return glstub_glTexSubImage1DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glTexSubImage2D,(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glTexSubImage2D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLenum lv6 = Int_val(v6);
	GLenum lv7 = Int_val(v7);
	GLvoid* lv8 = (Is_long(v8) ? (GLvoid*)Long_val(v8) : ((Tag_val(v8) == String_tag)? (String_val(v8)) : (Data_bigarray_val(v8))));
	LOAD_FUNCTION(glTexSubImage2D);
	CALL_FUNCTION(glTexSubImage2D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage2D_byte(value * argv, int n)
{
	return glstub_glTexSubImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glTexSubImage2DEXT,(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glTexSubImage2DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam4(v5, v6, v7, v8);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLenum lv6 = Int_val(v6);
	GLenum lv7 = Int_val(v7);
	GLvoid* lv8 = (Is_long(v8) ? (GLvoid*)Long_val(v8) : ((Tag_val(v8) == String_tag)? (String_val(v8)) : (Data_bigarray_val(v8))));
	LOAD_FUNCTION(glTexSubImage2DEXT);
	CALL_FUNCTION(glTexSubImage2DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage2DEXT_byte(value * argv, int n)
{
	return glstub_glTexSubImage2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

DECLARE_FUNCTION(glTexSubImage3D,(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glTexSubImage3D(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam1(v10);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLenum lv8 = Int_val(v8);
	GLenum lv9 = Int_val(v9);
	GLvoid* lv10 = (Is_long(v10) ? (GLvoid*)Long_val(v10) : ((Tag_val(v10) == String_tag)? (String_val(v10)) : (Data_bigarray_val(v10))));
	LOAD_FUNCTION(glTexSubImage3D);
	CALL_FUNCTION(glTexSubImage3D)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage3D_byte(value * argv, int n)
{
	return glstub_glTexSubImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

DECLARE_FUNCTION(glTexSubImage3DEXT,(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glTexSubImage3DEXT(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam1(v10);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLsizei lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLenum lv8 = Int_val(v8);
	GLenum lv9 = Int_val(v9);
	GLvoid* lv10 = (Is_long(v10) ? (GLvoid*)Long_val(v10) : ((Tag_val(v10) == String_tag)? (String_val(v10)) : (Data_bigarray_val(v10))));
	LOAD_FUNCTION(glTexSubImage3DEXT);
	CALL_FUNCTION(glTexSubImage3DEXT)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage3DEXT_byte(value * argv, int n)
{
	return glstub_glTexSubImage3DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

DECLARE_FUNCTION(glTexSubImage4DSGIS,(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLvoid*),void);
value glstub_glTexSubImage4DSGIS(value v0, value v1, value v2, value v3, value v4, value v5, value v6, value v7, value v8, value v9, value v10, value v11, value v12)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam5(v5, v6, v7, v8, v9);
	CAMLxparam3(v10, v11, v12);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	GLint lv5 = Int_val(v5);
	GLsizei lv6 = Int_val(v6);
	GLsizei lv7 = Int_val(v7);
	GLsizei lv8 = Int_val(v8);
	GLsizei lv9 = Int_val(v9);
	GLenum lv10 = Int_val(v10);
	GLenum lv11 = Int_val(v11);
	GLvoid* lv12 = (Is_long(v12) ? (GLvoid*)Long_val(v12) : ((Tag_val(v12) == String_tag)? (String_val(v12)) : (Data_bigarray_val(v12))));
	LOAD_FUNCTION(glTexSubImage4DSGIS);
	CALL_FUNCTION(glTexSubImage4DSGIS)(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11, lv12);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage4DSGIS_byte(value * argv, int n)
{
	return glstub_glTexSubImage4DSGIS(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12]);
}

DECLARE_FUNCTION(glTextureFogSGIX,(GLenum),void);
value glstub_glTextureFogSGIX(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glTextureFogSGIX);
	CALL_FUNCTION(glTextureFogSGIX)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTextureLightEXT,(GLenum),void);
value glstub_glTextureLightEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glTextureLightEXT);
	CALL_FUNCTION(glTextureLightEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTextureMaterialEXT,(GLenum, GLenum),void);
value glstub_glTextureMaterialEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	LOAD_FUNCTION(glTextureMaterialEXT);
	CALL_FUNCTION(glTextureMaterialEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTextureNormalEXT,(GLenum),void);
value glstub_glTextureNormalEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	LOAD_FUNCTION(glTextureNormalEXT);
	CALL_FUNCTION(glTextureNormalEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTextureRangeAPPLE,(GLenum, GLsizei, GLvoid*),void);
value glstub_glTextureRangeAPPLE(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	LOAD_FUNCTION(glTextureRangeAPPLE);
	CALL_FUNCTION(glTextureRangeAPPLE)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTrackMatrixNV,(GLenum, GLuint, GLenum, GLenum),void);
value glstub_glTrackMatrixNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glTrackMatrixNV);
	CALL_FUNCTION(glTrackMatrixNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTransformFeedbackAttribsNV,(GLuint, GLint*, GLenum),void);
value glstub_glTransformFeedbackAttribsNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLenum lv2 = Int_val(v2);
	LOAD_FUNCTION(glTransformFeedbackAttribsNV);
	CALL_FUNCTION(glTransformFeedbackAttribsNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTransformFeedbackVaryingsNV,(GLuint, GLsizei, GLint*, GLenum),void);
value glstub_glTransformFeedbackVaryingsNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	GLenum lv3 = Int_val(v3);
	LOAD_FUNCTION(glTransformFeedbackVaryingsNV);
	CALL_FUNCTION(glTransformFeedbackVaryingsNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTranslated,(GLdouble, GLdouble, GLdouble),void);
value glstub_glTranslated(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glTranslated);
	CALL_FUNCTION(glTranslated)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glTranslatef,(GLfloat, GLfloat, GLfloat),void);
value glstub_glTranslatef(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glTranslatef);
	CALL_FUNCTION(glTranslatef)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1f,(GLint, GLfloat),void);
value glstub_glUniform1f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glUniform1f);
	CALL_FUNCTION(glUniform1f)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1fARB,(GLint, GLfloat),void);
value glstub_glUniform1fARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glUniform1fARB);
	CALL_FUNCTION(glUniform1fARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1fv,(GLint, GLsizei, GLfloat*),void);
value glstub_glUniform1fv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform1fv);
	CALL_FUNCTION(glUniform1fv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1fvARB,(GLint, GLsizei, GLfloat*),void);
value glstub_glUniform1fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform1fvARB);
	CALL_FUNCTION(glUniform1fvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1i,(GLint, GLint),void);
value glstub_glUniform1i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glUniform1i);
	CALL_FUNCTION(glUniform1i)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1iARB,(GLint, GLint),void);
value glstub_glUniform1iARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glUniform1iARB);
	CALL_FUNCTION(glUniform1iARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1iv,(GLint, GLsizei, GLint*),void);
value glstub_glUniform1iv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform1iv);
	CALL_FUNCTION(glUniform1iv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1ivARB,(GLint, GLsizei, GLint*),void);
value glstub_glUniform1ivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform1ivARB);
	CALL_FUNCTION(glUniform1ivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1uiEXT,(GLint, GLuint),void);
value glstub_glUniform1uiEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glUniform1uiEXT);
	CALL_FUNCTION(glUniform1uiEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform1uivEXT,(GLint, GLsizei, GLuint*),void);
value glstub_glUniform1uivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform1uivEXT);
	CALL_FUNCTION(glUniform1uivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2f,(GLint, GLfloat, GLfloat),void);
value glstub_glUniform2f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glUniform2f);
	CALL_FUNCTION(glUniform2f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2fARB,(GLint, GLfloat, GLfloat),void);
value glstub_glUniform2fARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glUniform2fARB);
	CALL_FUNCTION(glUniform2fARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2fv,(GLint, GLsizei, GLfloat*),void);
value glstub_glUniform2fv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform2fv);
	CALL_FUNCTION(glUniform2fv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2fvARB,(GLint, GLsizei, GLfloat*),void);
value glstub_glUniform2fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform2fvARB);
	CALL_FUNCTION(glUniform2fvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2i,(GLint, GLint, GLint),void);
value glstub_glUniform2i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glUniform2i);
	CALL_FUNCTION(glUniform2i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2iARB,(GLint, GLint, GLint),void);
value glstub_glUniform2iARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glUniform2iARB);
	CALL_FUNCTION(glUniform2iARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2iv,(GLint, GLsizei, GLint*),void);
value glstub_glUniform2iv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform2iv);
	CALL_FUNCTION(glUniform2iv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2ivARB,(GLint, GLsizei, GLint*),void);
value glstub_glUniform2ivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform2ivARB);
	CALL_FUNCTION(glUniform2ivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2uiEXT,(GLint, GLuint, GLuint),void);
value glstub_glUniform2uiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glUniform2uiEXT);
	CALL_FUNCTION(glUniform2uiEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform2uivEXT,(GLint, GLsizei, GLuint*),void);
value glstub_glUniform2uivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform2uivEXT);
	CALL_FUNCTION(glUniform2uivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3f,(GLint, GLfloat, GLfloat, GLfloat),void);
value glstub_glUniform3f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glUniform3f);
	CALL_FUNCTION(glUniform3f)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3fARB,(GLint, GLfloat, GLfloat, GLfloat),void);
value glstub_glUniform3fARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glUniform3fARB);
	CALL_FUNCTION(glUniform3fARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3fv,(GLint, GLsizei, GLfloat*),void);
value glstub_glUniform3fv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform3fv);
	CALL_FUNCTION(glUniform3fv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3fvARB,(GLint, GLsizei, GLfloat*),void);
value glstub_glUniform3fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform3fvARB);
	CALL_FUNCTION(glUniform3fvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3i,(GLint, GLint, GLint, GLint),void);
value glstub_glUniform3i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glUniform3i);
	CALL_FUNCTION(glUniform3i)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3iARB,(GLint, GLint, GLint, GLint),void);
value glstub_glUniform3iARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glUniform3iARB);
	CALL_FUNCTION(glUniform3iARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3iv,(GLint, GLsizei, GLint*),void);
value glstub_glUniform3iv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform3iv);
	CALL_FUNCTION(glUniform3iv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3ivARB,(GLint, GLsizei, GLint*),void);
value glstub_glUniform3ivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform3ivARB);
	CALL_FUNCTION(glUniform3ivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3uiEXT,(GLint, GLuint, GLuint, GLuint),void);
value glstub_glUniform3uiEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	LOAD_FUNCTION(glUniform3uiEXT);
	CALL_FUNCTION(glUniform3uiEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform3uivEXT,(GLint, GLsizei, GLuint*),void);
value glstub_glUniform3uivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform3uivEXT);
	CALL_FUNCTION(glUniform3uivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4f,(GLint, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glUniform4f(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glUniform4f);
	CALL_FUNCTION(glUniform4f)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4fARB,(GLint, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glUniform4fARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glUniform4fARB);
	CALL_FUNCTION(glUniform4fARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4fv,(GLint, GLsizei, GLfloat*),void);
value glstub_glUniform4fv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform4fv);
	CALL_FUNCTION(glUniform4fv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4fvARB,(GLint, GLsizei, GLfloat*),void);
value glstub_glUniform4fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform4fvARB);
	CALL_FUNCTION(glUniform4fvARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4i,(GLint, GLint, GLint, GLint, GLint),void);
value glstub_glUniform4i(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glUniform4i);
	CALL_FUNCTION(glUniform4i)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4iARB,(GLint, GLint, GLint, GLint, GLint),void);
value glstub_glUniform4iARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glUniform4iARB);
	CALL_FUNCTION(glUniform4iARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4iv,(GLint, GLsizei, GLint*),void);
value glstub_glUniform4iv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform4iv);
	CALL_FUNCTION(glUniform4iv)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4ivARB,(GLint, GLsizei, GLint*),void);
value glstub_glUniform4ivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform4ivARB);
	CALL_FUNCTION(glUniform4ivARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4uiEXT,(GLint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glUniform4uiEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	LOAD_FUNCTION(glUniform4uiEXT);
	CALL_FUNCTION(glUniform4uiEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniform4uivEXT,(GLint, GLsizei, GLuint*),void);
value glstub_glUniform4uivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glUniform4uivEXT);
	CALL_FUNCTION(glUniform4uivEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformBufferEXT,(GLuint, GLint, GLuint),void);
value glstub_glUniformBufferEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glUniformBufferEXT);
	CALL_FUNCTION(glUniformBufferEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix2fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix2fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix2fv);
	CALL_FUNCTION(glUniformMatrix2fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix2fvARB,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix2fvARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix2fvARB);
	CALL_FUNCTION(glUniformMatrix2fvARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix2x3fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix2x3fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix2x3fv);
	CALL_FUNCTION(glUniformMatrix2x3fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix2x4fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix2x4fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix2x4fv);
	CALL_FUNCTION(glUniformMatrix2x4fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix3fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix3fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix3fv);
	CALL_FUNCTION(glUniformMatrix3fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix3fvARB,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix3fvARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix3fvARB);
	CALL_FUNCTION(glUniformMatrix3fvARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix3x2fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix3x2fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix3x2fv);
	CALL_FUNCTION(glUniformMatrix3x2fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix3x4fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix3x4fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix3x4fv);
	CALL_FUNCTION(glUniformMatrix3x4fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix4fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix4fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix4fv);
	CALL_FUNCTION(glUniformMatrix4fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix4fvARB,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix4fvARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix4fvARB);
	CALL_FUNCTION(glUniformMatrix4fvARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix4x2fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix4x2fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix4x2fv);
	CALL_FUNCTION(glUniformMatrix4x2fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUniformMatrix4x3fv,(GLint, GLsizei, GLboolean, GLfloat*),void);
value glstub_glUniformMatrix4x3fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	LOAD_FUNCTION(glUniformMatrix4x3fv);
	CALL_FUNCTION(glUniformMatrix4x3fv)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUnlockArraysEXT,(void),void);
value glstub_glUnlockArraysEXT(value v0)
{
	CAMLparam1(v0);
	LOAD_FUNCTION(glUnlockArraysEXT);
	CALL_FUNCTION(glUnlockArraysEXT)();
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUnmapBuffer,(GLenum),GLboolean);
value glstub_glUnmapBuffer(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glUnmapBuffer);
	ret = CALL_FUNCTION(glUnmapBuffer)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glUnmapBufferARB,(GLenum),GLboolean);
value glstub_glUnmapBufferARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLboolean ret;
	LOAD_FUNCTION(glUnmapBufferARB);
	ret = CALL_FUNCTION(glUnmapBufferARB)(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

DECLARE_FUNCTION(glUnmapObjectBufferATI,(GLuint),void);
value glstub_glUnmapObjectBufferATI(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glUnmapObjectBufferATI);
	CALL_FUNCTION(glUnmapObjectBufferATI)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUpdateObjectBufferATI,(GLuint, GLuint, GLsizei, GLvoid*, GLenum),void);
value glstub_glUpdateObjectBufferATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	GLenum lv4 = Int_val(v4);
	LOAD_FUNCTION(glUpdateObjectBufferATI);
	CALL_FUNCTION(glUpdateObjectBufferATI)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUseProgram,(GLuint),void);
value glstub_glUseProgram(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glUseProgram);
	CALL_FUNCTION(glUseProgram)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glUseProgramObjectARB,(GLuint),void);
value glstub_glUseProgramObjectARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glUseProgramObjectARB);
	CALL_FUNCTION(glUseProgramObjectARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glValidateProgram,(GLuint),void);
value glstub_glValidateProgram(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glValidateProgram);
	CALL_FUNCTION(glValidateProgram)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glValidateProgramARB,(GLuint),void);
value glstub_glValidateProgramARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	LOAD_FUNCTION(glValidateProgramARB);
	CALL_FUNCTION(glValidateProgramARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantArrayObjectATI,(GLuint, GLenum, GLsizei, GLuint, GLuint),void);
value glstub_glVariantArrayObjectATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	LOAD_FUNCTION(glVariantArrayObjectATI);
	CALL_FUNCTION(glVariantArrayObjectATI)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantPointerEXT,(GLuint, GLenum, GLuint, GLvoid*),void);
value glstub_glVariantPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glVariantPointerEXT);
	CALL_FUNCTION(glVariantPointerEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantbvEXT,(GLuint, GLbyte*),void);
value glstub_glVariantbvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVariantbvEXT);
	CALL_FUNCTION(glVariantbvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantdvEXT,(GLuint, GLdouble*),void);
value glstub_glVariantdvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVariantdvEXT);
	CALL_FUNCTION(glVariantdvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantfvEXT,(GLuint, GLfloat*),void);
value glstub_glVariantfvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVariantfvEXT);
	CALL_FUNCTION(glVariantfvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantivEXT,(GLuint, GLint*),void);
value glstub_glVariantivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVariantivEXT);
	CALL_FUNCTION(glVariantivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantsvEXT,(GLuint, GLshort*),void);
value glstub_glVariantsvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVariantsvEXT);
	CALL_FUNCTION(glVariantsvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantubvEXT,(GLuint, GLubyte*),void);
value glstub_glVariantubvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVariantubvEXT);
	CALL_FUNCTION(glVariantubvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantuivEXT,(GLuint, GLuint*),void);
value glstub_glVariantuivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVariantuivEXT);
	CALL_FUNCTION(glVariantuivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVariantusvEXT,(GLuint, GLushort*),void);
value glstub_glVariantusvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVariantusvEXT);
	CALL_FUNCTION(glVariantusvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2d,(GLdouble, GLdouble),void);
value glstub_glVertex2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertex2d);
	CALL_FUNCTION(glVertex2d)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2dv,(GLdouble*),void);
value glstub_glVertex2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex2dv);
	CALL_FUNCTION(glVertex2dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2f,(GLfloat, GLfloat),void);
value glstub_glVertex2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertex2f);
	CALL_FUNCTION(glVertex2f)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2fv,(GLfloat*),void);
value glstub_glVertex2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex2fv);
	CALL_FUNCTION(glVertex2fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2hNV,(GLushort, GLushort),void);
value glstub_glVertex2hNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertex2hNV);
	CALL_FUNCTION(glVertex2hNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2hvNV,(GLushort*),void);
value glstub_glVertex2hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex2hvNV);
	CALL_FUNCTION(glVertex2hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2i,(GLint, GLint),void);
value glstub_glVertex2i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertex2i);
	CALL_FUNCTION(glVertex2i)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2iv,(GLint*),void);
value glstub_glVertex2iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex2iv);
	CALL_FUNCTION(glVertex2iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2s,(GLshort, GLshort),void);
value glstub_glVertex2s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertex2s);
	CALL_FUNCTION(glVertex2s)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex2sv,(GLshort*),void);
value glstub_glVertex2sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex2sv);
	CALL_FUNCTION(glVertex2sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3d,(GLdouble, GLdouble, GLdouble),void);
value glstub_glVertex3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertex3d);
	CALL_FUNCTION(glVertex3d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3dv,(GLdouble*),void);
value glstub_glVertex3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex3dv);
	CALL_FUNCTION(glVertex3dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3f,(GLfloat, GLfloat, GLfloat),void);
value glstub_glVertex3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertex3f);
	CALL_FUNCTION(glVertex3f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3fv,(GLfloat*),void);
value glstub_glVertex3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex3fv);
	CALL_FUNCTION(glVertex3fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3hNV,(GLushort, GLushort, GLushort),void);
value glstub_glVertex3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertex3hNV);
	CALL_FUNCTION(glVertex3hNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3hvNV,(GLushort*),void);
value glstub_glVertex3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex3hvNV);
	CALL_FUNCTION(glVertex3hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3i,(GLint, GLint, GLint),void);
value glstub_glVertex3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertex3i);
	CALL_FUNCTION(glVertex3i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3iv,(GLint*),void);
value glstub_glVertex3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex3iv);
	CALL_FUNCTION(glVertex3iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3s,(GLshort, GLshort, GLshort),void);
value glstub_glVertex3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertex3s);
	CALL_FUNCTION(glVertex3s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex3sv,(GLshort*),void);
value glstub_glVertex3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex3sv);
	CALL_FUNCTION(glVertex3sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4d,(GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertex4d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertex4d);
	CALL_FUNCTION(glVertex4d)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4dv,(GLdouble*),void);
value glstub_glVertex4dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex4dv);
	CALL_FUNCTION(glVertex4dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4f,(GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertex4f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertex4f);
	CALL_FUNCTION(glVertex4f)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4fv,(GLfloat*),void);
value glstub_glVertex4fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex4fv);
	CALL_FUNCTION(glVertex4fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4hNV,(GLushort, GLushort, GLushort, GLushort),void);
value glstub_glVertex4hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertex4hNV);
	CALL_FUNCTION(glVertex4hNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4hvNV,(GLushort*),void);
value glstub_glVertex4hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex4hvNV);
	CALL_FUNCTION(glVertex4hvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4i,(GLint, GLint, GLint, GLint),void);
value glstub_glVertex4i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertex4i);
	CALL_FUNCTION(glVertex4i)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4iv,(GLint*),void);
value glstub_glVertex4iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex4iv);
	CALL_FUNCTION(glVertex4iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4s,(GLshort, GLshort, GLshort, GLshort),void);
value glstub_glVertex4s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertex4s);
	CALL_FUNCTION(glVertex4s)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertex4sv,(GLshort*),void);
value glstub_glVertex4sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertex4sv);
	CALL_FUNCTION(glVertex4sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexArrayParameteriAPPLE,(GLenum, GLint),void);
value glstub_glVertexArrayParameteriAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertexArrayParameteriAPPLE);
	CALL_FUNCTION(glVertexArrayParameteriAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexArrayRangeAPPLE,(GLsizei, GLvoid*),void);
value glstub_glVertexArrayRangeAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	LOAD_FUNCTION(glVertexArrayRangeAPPLE);
	CALL_FUNCTION(glVertexArrayRangeAPPLE)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexArrayRangeNV,(GLsizei, GLvoid*),void);
value glstub_glVertexArrayRangeNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	LOAD_FUNCTION(glVertexArrayRangeNV);
	CALL_FUNCTION(glVertexArrayRangeNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1d,(GLuint, GLdouble),void);
value glstub_glVertexAttrib1d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertexAttrib1d);
	CALL_FUNCTION(glVertexAttrib1d)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1dARB,(GLuint, GLdouble),void);
value glstub_glVertexAttrib1dARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertexAttrib1dARB);
	CALL_FUNCTION(glVertexAttrib1dARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1dNV,(GLuint, GLdouble),void);
value glstub_glVertexAttrib1dNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertexAttrib1dNV);
	CALL_FUNCTION(glVertexAttrib1dNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1dv,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib1dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1dv);
	CALL_FUNCTION(glVertexAttrib1dv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1dvARB,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib1dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1dvARB);
	CALL_FUNCTION(glVertexAttrib1dvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1dvNV,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib1dvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1dvNV);
	CALL_FUNCTION(glVertexAttrib1dvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1f,(GLuint, GLfloat),void);
value glstub_glVertexAttrib1f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertexAttrib1f);
	CALL_FUNCTION(glVertexAttrib1f)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1fARB,(GLuint, GLfloat),void);
value glstub_glVertexAttrib1fARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertexAttrib1fARB);
	CALL_FUNCTION(glVertexAttrib1fARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1fNV,(GLuint, GLfloat),void);
value glstub_glVertexAttrib1fNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertexAttrib1fNV);
	CALL_FUNCTION(glVertexAttrib1fNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1fv,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib1fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1fv);
	CALL_FUNCTION(glVertexAttrib1fv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1fvARB,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib1fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1fvARB);
	CALL_FUNCTION(glVertexAttrib1fvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1fvNV,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib1fvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1fvNV);
	CALL_FUNCTION(glVertexAttrib1fvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1hNV,(GLuint, GLushort),void);
value glstub_glVertexAttrib1hNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertexAttrib1hNV);
	CALL_FUNCTION(glVertexAttrib1hNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1hvNV,(GLuint, GLushort*),void);
value glstub_glVertexAttrib1hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1hvNV);
	CALL_FUNCTION(glVertexAttrib1hvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1s,(GLuint, GLshort),void);
value glstub_glVertexAttrib1s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertexAttrib1s);
	CALL_FUNCTION(glVertexAttrib1s)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1sARB,(GLuint, GLshort),void);
value glstub_glVertexAttrib1sARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertexAttrib1sARB);
	CALL_FUNCTION(glVertexAttrib1sARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1sNV,(GLuint, GLshort),void);
value glstub_glVertexAttrib1sNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertexAttrib1sNV);
	CALL_FUNCTION(glVertexAttrib1sNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1sv,(GLuint, GLshort*),void);
value glstub_glVertexAttrib1sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1sv);
	CALL_FUNCTION(glVertexAttrib1sv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1svARB,(GLuint, GLshort*),void);
value glstub_glVertexAttrib1svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1svARB);
	CALL_FUNCTION(glVertexAttrib1svARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib1svNV,(GLuint, GLshort*),void);
value glstub_glVertexAttrib1svNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib1svNV);
	CALL_FUNCTION(glVertexAttrib1svNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2d,(GLuint, GLdouble, GLdouble),void);
value glstub_glVertexAttrib2d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertexAttrib2d);
	CALL_FUNCTION(glVertexAttrib2d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2dARB,(GLuint, GLdouble, GLdouble),void);
value glstub_glVertexAttrib2dARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertexAttrib2dARB);
	CALL_FUNCTION(glVertexAttrib2dARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2dNV,(GLuint, GLdouble, GLdouble),void);
value glstub_glVertexAttrib2dNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertexAttrib2dNV);
	CALL_FUNCTION(glVertexAttrib2dNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2dv,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib2dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2dv);
	CALL_FUNCTION(glVertexAttrib2dv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2dvARB,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib2dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2dvARB);
	CALL_FUNCTION(glVertexAttrib2dvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2dvNV,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib2dvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2dvNV);
	CALL_FUNCTION(glVertexAttrib2dvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2f,(GLuint, GLfloat, GLfloat),void);
value glstub_glVertexAttrib2f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertexAttrib2f);
	CALL_FUNCTION(glVertexAttrib2f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2fARB,(GLuint, GLfloat, GLfloat),void);
value glstub_glVertexAttrib2fARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertexAttrib2fARB);
	CALL_FUNCTION(glVertexAttrib2fARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2fNV,(GLuint, GLfloat, GLfloat),void);
value glstub_glVertexAttrib2fNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertexAttrib2fNV);
	CALL_FUNCTION(glVertexAttrib2fNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2fv,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib2fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2fv);
	CALL_FUNCTION(glVertexAttrib2fv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2fvARB,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib2fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2fvARB);
	CALL_FUNCTION(glVertexAttrib2fvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2fvNV,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib2fvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2fvNV);
	CALL_FUNCTION(glVertexAttrib2fvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2hNV,(GLuint, GLushort, GLushort),void);
value glstub_glVertexAttrib2hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertexAttrib2hNV);
	CALL_FUNCTION(glVertexAttrib2hNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2hvNV,(GLuint, GLushort*),void);
value glstub_glVertexAttrib2hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2hvNV);
	CALL_FUNCTION(glVertexAttrib2hvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2s,(GLuint, GLshort, GLshort),void);
value glstub_glVertexAttrib2s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertexAttrib2s);
	CALL_FUNCTION(glVertexAttrib2s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2sARB,(GLuint, GLshort, GLshort),void);
value glstub_glVertexAttrib2sARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertexAttrib2sARB);
	CALL_FUNCTION(glVertexAttrib2sARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2sNV,(GLuint, GLshort, GLshort),void);
value glstub_glVertexAttrib2sNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertexAttrib2sNV);
	CALL_FUNCTION(glVertexAttrib2sNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2sv,(GLuint, GLshort*),void);
value glstub_glVertexAttrib2sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2sv);
	CALL_FUNCTION(glVertexAttrib2sv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2svARB,(GLuint, GLshort*),void);
value glstub_glVertexAttrib2svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2svARB);
	CALL_FUNCTION(glVertexAttrib2svARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib2svNV,(GLuint, GLshort*),void);
value glstub_glVertexAttrib2svNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib2svNV);
	CALL_FUNCTION(glVertexAttrib2svNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3d,(GLuint, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertexAttrib3d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertexAttrib3d);
	CALL_FUNCTION(glVertexAttrib3d)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3dARB,(GLuint, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertexAttrib3dARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertexAttrib3dARB);
	CALL_FUNCTION(glVertexAttrib3dARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3dNV,(GLuint, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertexAttrib3dNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertexAttrib3dNV);
	CALL_FUNCTION(glVertexAttrib3dNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3dv,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib3dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3dv);
	CALL_FUNCTION(glVertexAttrib3dv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3dvARB,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib3dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3dvARB);
	CALL_FUNCTION(glVertexAttrib3dvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3dvNV,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib3dvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3dvNV);
	CALL_FUNCTION(glVertexAttrib3dvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3f,(GLuint, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertexAttrib3f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertexAttrib3f);
	CALL_FUNCTION(glVertexAttrib3f)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3fARB,(GLuint, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertexAttrib3fARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertexAttrib3fARB);
	CALL_FUNCTION(glVertexAttrib3fARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3fNV,(GLuint, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertexAttrib3fNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertexAttrib3fNV);
	CALL_FUNCTION(glVertexAttrib3fNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3fv,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib3fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3fv);
	CALL_FUNCTION(glVertexAttrib3fv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3fvARB,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib3fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3fvARB);
	CALL_FUNCTION(glVertexAttrib3fvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3fvNV,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib3fvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3fvNV);
	CALL_FUNCTION(glVertexAttrib3fvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3hNV,(GLuint, GLushort, GLushort, GLushort),void);
value glstub_glVertexAttrib3hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertexAttrib3hNV);
	CALL_FUNCTION(glVertexAttrib3hNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3hvNV,(GLuint, GLushort*),void);
value glstub_glVertexAttrib3hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3hvNV);
	CALL_FUNCTION(glVertexAttrib3hvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3s,(GLuint, GLshort, GLshort, GLshort),void);
value glstub_glVertexAttrib3s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertexAttrib3s);
	CALL_FUNCTION(glVertexAttrib3s)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3sARB,(GLuint, GLshort, GLshort, GLshort),void);
value glstub_glVertexAttrib3sARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertexAttrib3sARB);
	CALL_FUNCTION(glVertexAttrib3sARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3sNV,(GLuint, GLshort, GLshort, GLshort),void);
value glstub_glVertexAttrib3sNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertexAttrib3sNV);
	CALL_FUNCTION(glVertexAttrib3sNV)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3sv,(GLuint, GLshort*),void);
value glstub_glVertexAttrib3sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3sv);
	CALL_FUNCTION(glVertexAttrib3sv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3svARB,(GLuint, GLshort*),void);
value glstub_glVertexAttrib3svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3svARB);
	CALL_FUNCTION(glVertexAttrib3svARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib3svNV,(GLuint, GLshort*),void);
value glstub_glVertexAttrib3svNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib3svNV);
	CALL_FUNCTION(glVertexAttrib3svNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4Nbv,(GLuint, GLbyte*),void);
value glstub_glVertexAttrib4Nbv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4Nbv);
	CALL_FUNCTION(glVertexAttrib4Nbv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4NbvARB,(GLuint, GLbyte*),void);
value glstub_glVertexAttrib4NbvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4NbvARB);
	CALL_FUNCTION(glVertexAttrib4NbvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4Niv,(GLuint, GLint*),void);
value glstub_glVertexAttrib4Niv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4Niv);
	CALL_FUNCTION(glVertexAttrib4Niv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4NivARB,(GLuint, GLint*),void);
value glstub_glVertexAttrib4NivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4NivARB);
	CALL_FUNCTION(glVertexAttrib4NivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4Nsv,(GLuint, GLshort*),void);
value glstub_glVertexAttrib4Nsv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4Nsv);
	CALL_FUNCTION(glVertexAttrib4Nsv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4NsvARB,(GLuint, GLshort*),void);
value glstub_glVertexAttrib4NsvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4NsvARB);
	CALL_FUNCTION(glVertexAttrib4NsvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4Nub,(GLuint, GLubyte, GLubyte, GLubyte, GLubyte),void);
value glstub_glVertexAttrib4Nub(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLubyte lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttrib4Nub);
	CALL_FUNCTION(glVertexAttrib4Nub)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4NubARB,(GLuint, GLubyte, GLubyte, GLubyte, GLubyte),void);
value glstub_glVertexAttrib4NubARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLubyte lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttrib4NubARB);
	CALL_FUNCTION(glVertexAttrib4NubARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4Nubv,(GLuint, GLubyte*),void);
value glstub_glVertexAttrib4Nubv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4Nubv);
	CALL_FUNCTION(glVertexAttrib4Nubv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4NubvARB,(GLuint, GLubyte*),void);
value glstub_glVertexAttrib4NubvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4NubvARB);
	CALL_FUNCTION(glVertexAttrib4NubvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4Nuiv,(GLuint, GLuint*),void);
value glstub_glVertexAttrib4Nuiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4Nuiv);
	CALL_FUNCTION(glVertexAttrib4Nuiv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4NuivARB,(GLuint, GLuint*),void);
value glstub_glVertexAttrib4NuivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4NuivARB);
	CALL_FUNCTION(glVertexAttrib4NuivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4Nusv,(GLuint, GLushort*),void);
value glstub_glVertexAttrib4Nusv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4Nusv);
	CALL_FUNCTION(glVertexAttrib4Nusv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4NusvARB,(GLuint, GLushort*),void);
value glstub_glVertexAttrib4NusvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4NusvARB);
	CALL_FUNCTION(glVertexAttrib4NusvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4bv,(GLuint, GLbyte*),void);
value glstub_glVertexAttrib4bv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4bv);
	CALL_FUNCTION(glVertexAttrib4bv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4bvARB,(GLuint, GLbyte*),void);
value glstub_glVertexAttrib4bvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4bvARB);
	CALL_FUNCTION(glVertexAttrib4bvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4d,(GLuint, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertexAttrib4d(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	LOAD_FUNCTION(glVertexAttrib4d);
	CALL_FUNCTION(glVertexAttrib4d)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4dARB,(GLuint, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertexAttrib4dARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	LOAD_FUNCTION(glVertexAttrib4dARB);
	CALL_FUNCTION(glVertexAttrib4dARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4dNV,(GLuint, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertexAttrib4dNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	LOAD_FUNCTION(glVertexAttrib4dNV);
	CALL_FUNCTION(glVertexAttrib4dNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4dv,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib4dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4dv);
	CALL_FUNCTION(glVertexAttrib4dv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4dvARB,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib4dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4dvARB);
	CALL_FUNCTION(glVertexAttrib4dvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4dvNV,(GLuint, GLdouble*),void);
value glstub_glVertexAttrib4dvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4dvNV);
	CALL_FUNCTION(glVertexAttrib4dvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4f,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertexAttrib4f(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glVertexAttrib4f);
	CALL_FUNCTION(glVertexAttrib4f)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4fARB,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertexAttrib4fARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glVertexAttrib4fARB);
	CALL_FUNCTION(glVertexAttrib4fARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4fNV,(GLuint, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertexAttrib4fNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glVertexAttrib4fNV);
	CALL_FUNCTION(glVertexAttrib4fNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4fv,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib4fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4fv);
	CALL_FUNCTION(glVertexAttrib4fv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4fvARB,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib4fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4fvARB);
	CALL_FUNCTION(glVertexAttrib4fvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4fvNV,(GLuint, GLfloat*),void);
value glstub_glVertexAttrib4fvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4fvNV);
	CALL_FUNCTION(glVertexAttrib4fvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4hNV,(GLuint, GLushort, GLushort, GLushort, GLushort),void);
value glstub_glVertexAttrib4hNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	GLushort lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttrib4hNV);
	CALL_FUNCTION(glVertexAttrib4hNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4hvNV,(GLuint, GLushort*),void);
value glstub_glVertexAttrib4hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4hvNV);
	CALL_FUNCTION(glVertexAttrib4hvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4iv,(GLuint, GLint*),void);
value glstub_glVertexAttrib4iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4iv);
	CALL_FUNCTION(glVertexAttrib4iv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4ivARB,(GLuint, GLint*),void);
value glstub_glVertexAttrib4ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4ivARB);
	CALL_FUNCTION(glVertexAttrib4ivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4s,(GLuint, GLshort, GLshort, GLshort, GLshort),void);
value glstub_glVertexAttrib4s(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttrib4s);
	CALL_FUNCTION(glVertexAttrib4s)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4sARB,(GLuint, GLshort, GLshort, GLshort, GLshort),void);
value glstub_glVertexAttrib4sARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttrib4sARB);
	CALL_FUNCTION(glVertexAttrib4sARB)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4sNV,(GLuint, GLshort, GLshort, GLshort, GLshort),void);
value glstub_glVertexAttrib4sNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttrib4sNV);
	CALL_FUNCTION(glVertexAttrib4sNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4sv,(GLuint, GLshort*),void);
value glstub_glVertexAttrib4sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4sv);
	CALL_FUNCTION(glVertexAttrib4sv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4svARB,(GLuint, GLshort*),void);
value glstub_glVertexAttrib4svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4svARB);
	CALL_FUNCTION(glVertexAttrib4svARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4svNV,(GLuint, GLshort*),void);
value glstub_glVertexAttrib4svNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4svNV);
	CALL_FUNCTION(glVertexAttrib4svNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4ubNV,(GLuint, GLubyte, GLubyte, GLubyte, GLubyte),void);
value glstub_glVertexAttrib4ubNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLubyte lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttrib4ubNV);
	CALL_FUNCTION(glVertexAttrib4ubNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4ubv,(GLuint, GLubyte*),void);
value glstub_glVertexAttrib4ubv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4ubv);
	CALL_FUNCTION(glVertexAttrib4ubv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4ubvARB,(GLuint, GLubyte*),void);
value glstub_glVertexAttrib4ubvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4ubvARB);
	CALL_FUNCTION(glVertexAttrib4ubvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4ubvNV,(GLuint, GLubyte*),void);
value glstub_glVertexAttrib4ubvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4ubvNV);
	CALL_FUNCTION(glVertexAttrib4ubvNV)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4uiv,(GLuint, GLuint*),void);
value glstub_glVertexAttrib4uiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4uiv);
	CALL_FUNCTION(glVertexAttrib4uiv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4uivARB,(GLuint, GLuint*),void);
value glstub_glVertexAttrib4uivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4uivARB);
	CALL_FUNCTION(glVertexAttrib4uivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4usv,(GLuint, GLushort*),void);
value glstub_glVertexAttrib4usv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4usv);
	CALL_FUNCTION(glVertexAttrib4usv)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttrib4usvARB,(GLuint, GLushort*),void);
value glstub_glVertexAttrib4usvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttrib4usvARB);
	CALL_FUNCTION(glVertexAttrib4usvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribArrayObjectATI,(GLuint, GLint, GLenum, GLboolean, GLsizei, GLuint, GLuint),void);
value glstub_glVertexAttribArrayObjectATI(value v0, value v1, value v2, value v3, value v4, value v5, value v6)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam2(v5, v6);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLboolean lv3 = Bool_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLuint lv5 = Int_val(v5);
	GLuint lv6 = Int_val(v6);
	LOAD_FUNCTION(glVertexAttribArrayObjectATI);
	CALL_FUNCTION(glVertexAttribArrayObjectATI)(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribArrayObjectATI_byte(value * argv, int n)
{
	return glstub_glVertexAttribArrayObjectATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

DECLARE_FUNCTION(glVertexAttribI1iEXT,(GLuint, GLint),void);
value glstub_glVertexAttribI1iEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertexAttribI1iEXT);
	CALL_FUNCTION(glVertexAttribI1iEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI1ivEXT,(GLuint, GLint*),void);
value glstub_glVertexAttribI1ivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI1ivEXT);
	CALL_FUNCTION(glVertexAttribI1ivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI1uiEXT,(GLuint, GLuint),void);
value glstub_glVertexAttribI1uiEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertexAttribI1uiEXT);
	CALL_FUNCTION(glVertexAttribI1uiEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI1uivEXT,(GLuint, GLuint*),void);
value glstub_glVertexAttribI1uivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI1uivEXT);
	CALL_FUNCTION(glVertexAttribI1uivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI2iEXT,(GLuint, GLint, GLint),void);
value glstub_glVertexAttribI2iEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertexAttribI2iEXT);
	CALL_FUNCTION(glVertexAttribI2iEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI2ivEXT,(GLuint, GLint*),void);
value glstub_glVertexAttribI2ivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI2ivEXT);
	CALL_FUNCTION(glVertexAttribI2ivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI2uiEXT,(GLuint, GLuint, GLuint),void);
value glstub_glVertexAttribI2uiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertexAttribI2uiEXT);
	CALL_FUNCTION(glVertexAttribI2uiEXT)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI2uivEXT,(GLuint, GLuint*),void);
value glstub_glVertexAttribI2uivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI2uivEXT);
	CALL_FUNCTION(glVertexAttribI2uivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI3iEXT,(GLuint, GLint, GLint, GLint),void);
value glstub_glVertexAttribI3iEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertexAttribI3iEXT);
	CALL_FUNCTION(glVertexAttribI3iEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI3ivEXT,(GLuint, GLint*),void);
value glstub_glVertexAttribI3ivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI3ivEXT);
	CALL_FUNCTION(glVertexAttribI3ivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI3uiEXT,(GLuint, GLuint, GLuint, GLuint),void);
value glstub_glVertexAttribI3uiEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertexAttribI3uiEXT);
	CALL_FUNCTION(glVertexAttribI3uiEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI3uivEXT,(GLuint, GLuint*),void);
value glstub_glVertexAttribI3uivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI3uivEXT);
	CALL_FUNCTION(glVertexAttribI3uivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI4bvEXT,(GLuint, GLbyte*),void);
value glstub_glVertexAttribI4bvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI4bvEXT);
	CALL_FUNCTION(glVertexAttribI4bvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI4iEXT,(GLuint, GLint, GLint, GLint, GLint),void);
value glstub_glVertexAttribI4iEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttribI4iEXT);
	CALL_FUNCTION(glVertexAttribI4iEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI4ivEXT,(GLuint, GLint*),void);
value glstub_glVertexAttribI4ivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI4ivEXT);
	CALL_FUNCTION(glVertexAttribI4ivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI4svEXT,(GLuint, GLshort*),void);
value glstub_glVertexAttribI4svEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI4svEXT);
	CALL_FUNCTION(glVertexAttribI4svEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI4ubvEXT,(GLuint, GLubyte*),void);
value glstub_glVertexAttribI4ubvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI4ubvEXT);
	CALL_FUNCTION(glVertexAttribI4ubvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI4uiEXT,(GLuint, GLuint, GLuint, GLuint, GLuint),void);
value glstub_glVertexAttribI4uiEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexAttribI4uiEXT);
	CALL_FUNCTION(glVertexAttribI4uiEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI4uivEXT,(GLuint, GLuint*),void);
value glstub_glVertexAttribI4uivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI4uivEXT);
	CALL_FUNCTION(glVertexAttribI4uivEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribI4usvEXT,(GLuint, GLushort*),void);
value glstub_glVertexAttribI4usvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexAttribI4usvEXT);
	CALL_FUNCTION(glVertexAttribI4usvEXT)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribIPointerEXT,(GLuint, GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glVertexAttribIPointerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glVertexAttribIPointerEXT);
	CALL_FUNCTION(glVertexAttribIPointerEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribPointer,(GLuint, GLint, GLenum, GLboolean, GLsizei, GLvoid*),void);
value glstub_glVertexAttribPointer(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLboolean lv3 = Bool_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glVertexAttribPointer);
	CALL_FUNCTION(glVertexAttribPointer)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribPointer_byte(value * argv, int n)
{
	return glstub_glVertexAttribPointer(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glVertexAttribPointerARB,(GLuint, GLint, GLenum, GLboolean, GLsizei, GLvoid*),void);
value glstub_glVertexAttribPointerARB(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLboolean lv3 = Bool_val(v3);
	GLsizei lv4 = Int_val(v4);
	GLvoid* lv5 = (Is_long(v5) ? (GLvoid*)Long_val(v5) : ((Tag_val(v5) == String_tag)? (String_val(v5)) : (Data_bigarray_val(v5))));
	LOAD_FUNCTION(glVertexAttribPointerARB);
	CALL_FUNCTION(glVertexAttribPointerARB)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribPointerARB_byte(value * argv, int n)
{
	return glstub_glVertexAttribPointerARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glVertexAttribPointerNV,(GLuint, GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glVertexAttribPointerNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glVertexAttribPointerNV);
	CALL_FUNCTION(glVertexAttribPointerNV)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs1dvNV,(GLuint, GLsizei, GLdouble*),void);
value glstub_glVertexAttribs1dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs1dvNV);
	CALL_FUNCTION(glVertexAttribs1dvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs1fvNV,(GLuint, GLsizei, GLfloat*),void);
value glstub_glVertexAttribs1fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs1fvNV);
	CALL_FUNCTION(glVertexAttribs1fvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs1hvNV,(GLuint, GLsizei, GLushort*),void);
value glstub_glVertexAttribs1hvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs1hvNV);
	CALL_FUNCTION(glVertexAttribs1hvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs1svNV,(GLuint, GLsizei, GLshort*),void);
value glstub_glVertexAttribs1svNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLshort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs1svNV);
	CALL_FUNCTION(glVertexAttribs1svNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs2dvNV,(GLuint, GLsizei, GLdouble*),void);
value glstub_glVertexAttribs2dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs2dvNV);
	CALL_FUNCTION(glVertexAttribs2dvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs2fvNV,(GLuint, GLsizei, GLfloat*),void);
value glstub_glVertexAttribs2fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs2fvNV);
	CALL_FUNCTION(glVertexAttribs2fvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs2hvNV,(GLuint, GLsizei, GLushort*),void);
value glstub_glVertexAttribs2hvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs2hvNV);
	CALL_FUNCTION(glVertexAttribs2hvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs2svNV,(GLuint, GLsizei, GLshort*),void);
value glstub_glVertexAttribs2svNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLshort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs2svNV);
	CALL_FUNCTION(glVertexAttribs2svNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs3dvNV,(GLuint, GLsizei, GLdouble*),void);
value glstub_glVertexAttribs3dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs3dvNV);
	CALL_FUNCTION(glVertexAttribs3dvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs3fvNV,(GLuint, GLsizei, GLfloat*),void);
value glstub_glVertexAttribs3fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs3fvNV);
	CALL_FUNCTION(glVertexAttribs3fvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs3hvNV,(GLuint, GLsizei, GLushort*),void);
value glstub_glVertexAttribs3hvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs3hvNV);
	CALL_FUNCTION(glVertexAttribs3hvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs3svNV,(GLuint, GLsizei, GLshort*),void);
value glstub_glVertexAttribs3svNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLshort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs3svNV);
	CALL_FUNCTION(glVertexAttribs3svNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs4dvNV,(GLuint, GLsizei, GLdouble*),void);
value glstub_glVertexAttribs4dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs4dvNV);
	CALL_FUNCTION(glVertexAttribs4dvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs4fvNV,(GLuint, GLsizei, GLfloat*),void);
value glstub_glVertexAttribs4fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs4fvNV);
	CALL_FUNCTION(glVertexAttribs4fvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs4hvNV,(GLuint, GLsizei, GLushort*),void);
value glstub_glVertexAttribs4hvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs4hvNV);
	CALL_FUNCTION(glVertexAttribs4hvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs4svNV,(GLuint, GLsizei, GLshort*),void);
value glstub_glVertexAttribs4svNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLshort* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs4svNV);
	CALL_FUNCTION(glVertexAttribs4svNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexAttribs4ubvNV,(GLuint, GLsizei, GLubyte*),void);
value glstub_glVertexAttribs4ubvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexAttribs4ubvNV);
	CALL_FUNCTION(glVertexAttribs4ubvNV)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexBlendARB,(GLint),void);
value glstub_glVertexBlendARB(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	LOAD_FUNCTION(glVertexBlendARB);
	CALL_FUNCTION(glVertexBlendARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexBlendEnvfATI,(GLenum, GLfloat),void);
value glstub_glVertexBlendEnvfATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glVertexBlendEnvfATI);
	CALL_FUNCTION(glVertexBlendEnvfATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexBlendEnviATI,(GLenum, GLint),void);
value glstub_glVertexBlendEnviATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glVertexBlendEnviATI);
	CALL_FUNCTION(glVertexBlendEnviATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexPointer,(GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glVertexPointer(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glVertexPointer);
	CALL_FUNCTION(glVertexPointer)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexPointerEXT,(GLint, GLenum, GLsizei, GLsizei, GLvoid*),void);
value glstub_glVertexPointerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	LOAD_FUNCTION(glVertexPointerEXT);
	CALL_FUNCTION(glVertexPointerEXT)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexPointerListIBM,(GLint, GLenum, GLint, GLvoid**, GLint),void);
value glstub_glVertexPointerListIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexPointerListIBM);
	CALL_FUNCTION(glVertexPointerListIBM)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexPointervINTEL,(GLint, GLenum, GLvoid**),void);
value glstub_glVertexPointervINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	LOAD_FUNCTION(glVertexPointervINTEL);
	CALL_FUNCTION(glVertexPointervINTEL)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream2dATI,(GLenum, GLdouble, GLdouble),void);
value glstub_glVertexStream2dATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertexStream2dATI);
	CALL_FUNCTION(glVertexStream2dATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream2dvATI,(GLenum, GLdouble*),void);
value glstub_glVertexStream2dvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream2dvATI);
	CALL_FUNCTION(glVertexStream2dvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream2fATI,(GLenum, GLfloat, GLfloat),void);
value glstub_glVertexStream2fATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glVertexStream2fATI);
	CALL_FUNCTION(glVertexStream2fATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream2fvATI,(GLenum, GLfloat*),void);
value glstub_glVertexStream2fvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream2fvATI);
	CALL_FUNCTION(glVertexStream2fvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream2iATI,(GLenum, GLint, GLint),void);
value glstub_glVertexStream2iATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertexStream2iATI);
	CALL_FUNCTION(glVertexStream2iATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream2ivATI,(GLenum, GLint*),void);
value glstub_glVertexStream2ivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream2ivATI);
	CALL_FUNCTION(glVertexStream2ivATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream2sATI,(GLenum, GLshort, GLshort),void);
value glstub_glVertexStream2sATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glVertexStream2sATI);
	CALL_FUNCTION(glVertexStream2sATI)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream2svATI,(GLenum, GLshort*),void);
value glstub_glVertexStream2svATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream2svATI);
	CALL_FUNCTION(glVertexStream2svATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream3dATI,(GLenum, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertexStream3dATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertexStream3dATI);
	CALL_FUNCTION(glVertexStream3dATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream3dvATI,(GLenum, GLdouble*),void);
value glstub_glVertexStream3dvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream3dvATI);
	CALL_FUNCTION(glVertexStream3dvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream3fATI,(GLenum, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertexStream3fATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glVertexStream3fATI);
	CALL_FUNCTION(glVertexStream3fATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream3fvATI,(GLenum, GLfloat*),void);
value glstub_glVertexStream3fvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream3fvATI);
	CALL_FUNCTION(glVertexStream3fvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream3iATI,(GLenum, GLint, GLint, GLint),void);
value glstub_glVertexStream3iATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertexStream3iATI);
	CALL_FUNCTION(glVertexStream3iATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream3ivATI,(GLenum, GLint*),void);
value glstub_glVertexStream3ivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream3ivATI);
	CALL_FUNCTION(glVertexStream3ivATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream3sATI,(GLenum, GLshort, GLshort, GLshort),void);
value glstub_glVertexStream3sATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glVertexStream3sATI);
	CALL_FUNCTION(glVertexStream3sATI)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream3svATI,(GLenum, GLshort*),void);
value glstub_glVertexStream3svATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream3svATI);
	CALL_FUNCTION(glVertexStream3svATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream4dATI,(GLenum, GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glVertexStream4dATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	LOAD_FUNCTION(glVertexStream4dATI);
	CALL_FUNCTION(glVertexStream4dATI)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream4dvATI,(GLenum, GLdouble*),void);
value glstub_glVertexStream4dvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream4dvATI);
	CALL_FUNCTION(glVertexStream4dvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream4fATI,(GLenum, GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glVertexStream4fATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	LOAD_FUNCTION(glVertexStream4fATI);
	CALL_FUNCTION(glVertexStream4fATI)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream4fvATI,(GLenum, GLfloat*),void);
value glstub_glVertexStream4fvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream4fvATI);
	CALL_FUNCTION(glVertexStream4fvATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream4iATI,(GLenum, GLint, GLint, GLint, GLint),void);
value glstub_glVertexStream4iATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexStream4iATI);
	CALL_FUNCTION(glVertexStream4iATI)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream4ivATI,(GLenum, GLint*),void);
value glstub_glVertexStream4ivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream4ivATI);
	CALL_FUNCTION(glVertexStream4ivATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream4sATI,(GLenum, GLshort, GLshort, GLshort, GLshort),void);
value glstub_glVertexStream4sATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	LOAD_FUNCTION(glVertexStream4sATI);
	CALL_FUNCTION(glVertexStream4sATI)(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexStream4svATI,(GLenum, GLshort*),void);
value glstub_glVertexStream4svATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glVertexStream4svATI);
	CALL_FUNCTION(glVertexStream4svATI)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexWeightPointerEXT,(GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glVertexWeightPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glVertexWeightPointerEXT);
	CALL_FUNCTION(glVertexWeightPointerEXT)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexWeightfEXT,(GLfloat),void);
value glstub_glVertexWeightfEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	LOAD_FUNCTION(glVertexWeightfEXT);
	CALL_FUNCTION(glVertexWeightfEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexWeightfvEXT,(GLfloat*),void);
value glstub_glVertexWeightfvEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertexWeightfvEXT);
	CALL_FUNCTION(glVertexWeightfvEXT)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexWeighthNV,(GLushort),void);
value glstub_glVertexWeighthNV(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	LOAD_FUNCTION(glVertexWeighthNV);
	CALL_FUNCTION(glVertexWeighthNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glVertexWeighthvNV,(GLushort*),void);
value glstub_glVertexWeighthvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glVertexWeighthvNV);
	CALL_FUNCTION(glVertexWeighthvNV)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glViewport,(GLint, GLint, GLsizei, GLsizei),void);
value glstub_glViewport(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	LOAD_FUNCTION(glViewport);
	CALL_FUNCTION(glViewport)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightPointerARB,(GLint, GLenum, GLsizei, GLvoid*),void);
value glstub_glWeightPointerARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	LOAD_FUNCTION(glWeightPointerARB);
	CALL_FUNCTION(glWeightPointerARB)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightbvARB,(GLint, GLbyte*),void);
value glstub_glWeightbvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glWeightbvARB);
	CALL_FUNCTION(glWeightbvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightdvARB,(GLint, GLdouble*),void);
value glstub_glWeightdvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	LOAD_FUNCTION(glWeightdvARB);
	CALL_FUNCTION(glWeightdvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightfvARB,(GLint, GLfloat*),void);
value glstub_glWeightfvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glWeightfvARB);
	CALL_FUNCTION(glWeightfvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightivARB,(GLint, GLint*),void);
value glstub_glWeightivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glWeightivARB);
	CALL_FUNCTION(glWeightivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightsvARB,(GLint, GLshort*),void);
value glstub_glWeightsvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glWeightsvARB);
	CALL_FUNCTION(glWeightsvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightubvARB,(GLint, GLubyte*),void);
value glstub_glWeightubvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glWeightubvARB);
	CALL_FUNCTION(glWeightubvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightuivARB,(GLint, GLuint*),void);
value glstub_glWeightuivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glWeightuivARB);
	CALL_FUNCTION(glWeightuivARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWeightusvARB,(GLint, GLushort*),void);
value glstub_glWeightusvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	LOAD_FUNCTION(glWeightusvARB);
	CALL_FUNCTION(glWeightusvARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2d,(GLdouble, GLdouble),void);
value glstub_glWindowPos2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glWindowPos2d);
	CALL_FUNCTION(glWindowPos2d)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2dARB,(GLdouble, GLdouble),void);
value glstub_glWindowPos2dARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glWindowPos2dARB);
	CALL_FUNCTION(glWindowPos2dARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2dMESA,(GLdouble, GLdouble),void);
value glstub_glWindowPos2dMESA(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	LOAD_FUNCTION(glWindowPos2dMESA);
	CALL_FUNCTION(glWindowPos2dMESA)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2dv,(GLdouble*),void);
value glstub_glWindowPos2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2dv);
	CALL_FUNCTION(glWindowPos2dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2dvARB,(GLdouble*),void);
value glstub_glWindowPos2dvARB(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2dvARB);
	CALL_FUNCTION(glWindowPos2dvARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2dvMESA,(GLdouble*),void);
value glstub_glWindowPos2dvMESA(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2dvMESA);
	CALL_FUNCTION(glWindowPos2dvMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2f,(GLfloat, GLfloat),void);
value glstub_glWindowPos2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glWindowPos2f);
	CALL_FUNCTION(glWindowPos2f)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2fARB,(GLfloat, GLfloat),void);
value glstub_glWindowPos2fARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glWindowPos2fARB);
	CALL_FUNCTION(glWindowPos2fARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2fMESA,(GLfloat, GLfloat),void);
value glstub_glWindowPos2fMESA(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	LOAD_FUNCTION(glWindowPos2fMESA);
	CALL_FUNCTION(glWindowPos2fMESA)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2fv,(GLfloat*),void);
value glstub_glWindowPos2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2fv);
	CALL_FUNCTION(glWindowPos2fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2fvARB,(GLfloat*),void);
value glstub_glWindowPos2fvARB(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2fvARB);
	CALL_FUNCTION(glWindowPos2fvARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2fvMESA,(GLfloat*),void);
value glstub_glWindowPos2fvMESA(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2fvMESA);
	CALL_FUNCTION(glWindowPos2fvMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2i,(GLint, GLint),void);
value glstub_glWindowPos2i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glWindowPos2i);
	CALL_FUNCTION(glWindowPos2i)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2iARB,(GLint, GLint),void);
value glstub_glWindowPos2iARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glWindowPos2iARB);
	CALL_FUNCTION(glWindowPos2iARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2iMESA,(GLint, GLint),void);
value glstub_glWindowPos2iMESA(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	LOAD_FUNCTION(glWindowPos2iMESA);
	CALL_FUNCTION(glWindowPos2iMESA)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2iv,(GLint*),void);
value glstub_glWindowPos2iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2iv);
	CALL_FUNCTION(glWindowPos2iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2ivARB,(GLint*),void);
value glstub_glWindowPos2ivARB(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2ivARB);
	CALL_FUNCTION(glWindowPos2ivARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2ivMESA,(GLint*),void);
value glstub_glWindowPos2ivMESA(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2ivMESA);
	CALL_FUNCTION(glWindowPos2ivMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2s,(GLshort, GLshort),void);
value glstub_glWindowPos2s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glWindowPos2s);
	CALL_FUNCTION(glWindowPos2s)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2sARB,(GLshort, GLshort),void);
value glstub_glWindowPos2sARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glWindowPos2sARB);
	CALL_FUNCTION(glWindowPos2sARB)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2sMESA,(GLshort, GLshort),void);
value glstub_glWindowPos2sMESA(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	LOAD_FUNCTION(glWindowPos2sMESA);
	CALL_FUNCTION(glWindowPos2sMESA)(lv0, lv1);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2sv,(GLshort*),void);
value glstub_glWindowPos2sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2sv);
	CALL_FUNCTION(glWindowPos2sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2svARB,(GLshort*),void);
value glstub_glWindowPos2svARB(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2svARB);
	CALL_FUNCTION(glWindowPos2svARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos2svMESA,(GLshort*),void);
value glstub_glWindowPos2svMESA(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos2svMESA);
	CALL_FUNCTION(glWindowPos2svMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3d,(GLdouble, GLdouble, GLdouble),void);
value glstub_glWindowPos3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glWindowPos3d);
	CALL_FUNCTION(glWindowPos3d)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3dARB,(GLdouble, GLdouble, GLdouble),void);
value glstub_glWindowPos3dARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glWindowPos3dARB);
	CALL_FUNCTION(glWindowPos3dARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3dMESA,(GLdouble, GLdouble, GLdouble),void);
value glstub_glWindowPos3dMESA(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	LOAD_FUNCTION(glWindowPos3dMESA);
	CALL_FUNCTION(glWindowPos3dMESA)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3dv,(GLdouble*),void);
value glstub_glWindowPos3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3dv);
	CALL_FUNCTION(glWindowPos3dv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3dvARB,(GLdouble*),void);
value glstub_glWindowPos3dvARB(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3dvARB);
	CALL_FUNCTION(glWindowPos3dvARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3dvMESA,(GLdouble*),void);
value glstub_glWindowPos3dvMESA(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3dvMESA);
	CALL_FUNCTION(glWindowPos3dvMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3f,(GLfloat, GLfloat, GLfloat),void);
value glstub_glWindowPos3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glWindowPos3f);
	CALL_FUNCTION(glWindowPos3f)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3fARB,(GLfloat, GLfloat, GLfloat),void);
value glstub_glWindowPos3fARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glWindowPos3fARB);
	CALL_FUNCTION(glWindowPos3fARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3fMESA,(GLfloat, GLfloat, GLfloat),void);
value glstub_glWindowPos3fMESA(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	LOAD_FUNCTION(glWindowPos3fMESA);
	CALL_FUNCTION(glWindowPos3fMESA)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3fv,(GLfloat*),void);
value glstub_glWindowPos3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3fv);
	CALL_FUNCTION(glWindowPos3fv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3fvARB,(GLfloat*),void);
value glstub_glWindowPos3fvARB(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3fvARB);
	CALL_FUNCTION(glWindowPos3fvARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3fvMESA,(GLfloat*),void);
value glstub_glWindowPos3fvMESA(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3fvMESA);
	CALL_FUNCTION(glWindowPos3fvMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3i,(GLint, GLint, GLint),void);
value glstub_glWindowPos3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glWindowPos3i);
	CALL_FUNCTION(glWindowPos3i)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3iARB,(GLint, GLint, GLint),void);
value glstub_glWindowPos3iARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glWindowPos3iARB);
	CALL_FUNCTION(glWindowPos3iARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3iMESA,(GLint, GLint, GLint),void);
value glstub_glWindowPos3iMESA(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	LOAD_FUNCTION(glWindowPos3iMESA);
	CALL_FUNCTION(glWindowPos3iMESA)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3iv,(GLint*),void);
value glstub_glWindowPos3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3iv);
	CALL_FUNCTION(glWindowPos3iv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3ivARB,(GLint*),void);
value glstub_glWindowPos3ivARB(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3ivARB);
	CALL_FUNCTION(glWindowPos3ivARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3ivMESA,(GLint*),void);
value glstub_glWindowPos3ivMESA(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3ivMESA);
	CALL_FUNCTION(glWindowPos3ivMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3s,(GLshort, GLshort, GLshort),void);
value glstub_glWindowPos3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glWindowPos3s);
	CALL_FUNCTION(glWindowPos3s)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3sARB,(GLshort, GLshort, GLshort),void);
value glstub_glWindowPos3sARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glWindowPos3sARB);
	CALL_FUNCTION(glWindowPos3sARB)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3sMESA,(GLshort, GLshort, GLshort),void);
value glstub_glWindowPos3sMESA(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	LOAD_FUNCTION(glWindowPos3sMESA);
	CALL_FUNCTION(glWindowPos3sMESA)(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3sv,(GLshort*),void);
value glstub_glWindowPos3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3sv);
	CALL_FUNCTION(glWindowPos3sv)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3svARB,(GLshort*),void);
value glstub_glWindowPos3svARB(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3svARB);
	CALL_FUNCTION(glWindowPos3svARB)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos3svMESA,(GLshort*),void);
value glstub_glWindowPos3svMESA(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos3svMESA);
	CALL_FUNCTION(glWindowPos3svMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos4dMESA,(GLdouble, GLdouble, GLdouble, GLdouble),void);
value glstub_glWindowPos4dMESA(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	LOAD_FUNCTION(glWindowPos4dMESA);
	CALL_FUNCTION(glWindowPos4dMESA)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos4dvMESA,(GLdouble*),void);
value glstub_glWindowPos4dvMESA(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos4dvMESA);
	CALL_FUNCTION(glWindowPos4dvMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos4fMESA,(GLfloat, GLfloat, GLfloat, GLfloat),void);
value glstub_glWindowPos4fMESA(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	LOAD_FUNCTION(glWindowPos4fMESA);
	CALL_FUNCTION(glWindowPos4fMESA)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos4fvMESA,(GLfloat*),void);
value glstub_glWindowPos4fvMESA(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos4fvMESA);
	CALL_FUNCTION(glWindowPos4fvMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos4iMESA,(GLint, GLint, GLint, GLint),void);
value glstub_glWindowPos4iMESA(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	LOAD_FUNCTION(glWindowPos4iMESA);
	CALL_FUNCTION(glWindowPos4iMESA)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos4ivMESA,(GLint*),void);
value glstub_glWindowPos4ivMESA(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos4ivMESA);
	CALL_FUNCTION(glWindowPos4ivMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos4sMESA,(GLshort, GLshort, GLshort, GLshort),void);
value glstub_glWindowPos4sMESA(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	LOAD_FUNCTION(glWindowPos4sMESA);
	CALL_FUNCTION(glWindowPos4sMESA)(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWindowPos4svMESA,(GLshort*),void);
value glstub_glWindowPos4svMESA(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	LOAD_FUNCTION(glWindowPos4svMESA);
	CALL_FUNCTION(glWindowPos4svMESA)(lv0);
	CAMLreturn(Val_unit);
}

DECLARE_FUNCTION(glWriteMaskEXT,(GLuint, GLuint, GLenum, GLenum, GLenum, GLenum),void);
value glstub_glWriteMaskEXT(value v0, value v1, value v2, value v3, value v4, value v5)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	CAMLxparam1(v5);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	GLenum lv5 = Int_val(v5);
	LOAD_FUNCTION(glWriteMaskEXT);
	CALL_FUNCTION(glWriteMaskEXT)(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glWriteMaskEXT_byte(value * argv, int n)
{
	return glstub_glWriteMaskEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

DECLARE_FUNCTION(glewInit,(void),GLint);
value glstub_glewInit(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLint ret;
	LOAD_FUNCTION(glewInit);
	ret = CALL_FUNCTION(glewInit)();
	result = Val_int(ret);
	CAMLreturn(result);
}

