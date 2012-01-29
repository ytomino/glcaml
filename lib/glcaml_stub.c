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

#include <GL/glew.h>

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
//typedef char GLbyte;
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
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef char* GLstring;

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

value unsafe_coercion(value v)
{
        CAMLparam1(v);
        CAMLreturn(v);
}

value glstub_glAccum(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glAccum(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glActiveStencilFaceEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glActiveStencilFaceEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glActiveTexture(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glActiveTexture(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glActiveTextureARB(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glActiveTextureARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glActiveVaryingNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	 glActiveVaryingNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glAddSwapHintRectWIN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glAddSwapHintRectWIN(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glAlphaFragmentOp1ATI(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glAlphaFragmentOp1ATI_byte(value * argv, int n)
{
	return glstub_glAlphaFragmentOp1ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glAlphaFragmentOp2ATI(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glAlphaFragmentOp2ATI_byte(value * argv, int n)
{
	return glstub_glAlphaFragmentOp2ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glAlphaFragmentOp3ATI(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11);
	CAMLreturn(Val_unit);
}

value glstub_glAlphaFragmentOp3ATI_byte(value * argv, int n)
{
	return glstub_glAlphaFragmentOp3ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11]);
}

value glstub_glAlphaFunc(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLclampf lv1 = Double_val(v1);
	 glAlphaFunc(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glApplyTextureEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glApplyTextureEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glAreProgramsResidentNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	GLboolean ret;
	ret =  glAreProgramsResidentNV(lv0, lv1, lv2);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glAreTexturesResident(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	GLboolean ret;
	ret =  glAreTexturesResident(lv0, lv1, lv2);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glAreTexturesResidentEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	GLboolean ret;
	ret =  glAreTexturesResidentEXT(lv0, lv1, lv2);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glArrayElement(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glArrayElement(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glArrayElementEXT(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glArrayElementEXT(lv0);
	CAMLreturn(Val_unit);
}

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
	 glArrayObjectATI(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glArrayObjectATI_byte(value * argv, int n)
{
	return glstub_glArrayObjectATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glAsyncMarkerSGIX(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glAsyncMarkerSGIX(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glAttachObjectARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glAttachObjectARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glAttachShader(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glAttachShader(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBegin(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glBegin(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBeginFragmentShaderATI(value v0)
{
	CAMLparam1(v0);
	 glBeginFragmentShaderATI();
	CAMLreturn(Val_unit);
}

value glstub_glBeginOcclusionQueryNV(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glBeginOcclusionQueryNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBeginQuery(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBeginQuery(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBeginQueryARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBeginQueryARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBeginSceneEXT(value v0)
{
	CAMLparam1(v0);
	 glBeginSceneEXT();
	CAMLreturn(Val_unit);
}

value glstub_glBeginTransformFeedbackNV(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glBeginTransformFeedbackNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBeginVertexShaderEXT(value v0)
{
	CAMLparam1(v0);
	 glBeginVertexShaderEXT();
	CAMLreturn(Val_unit);
}

value glstub_glBindAttribLocation(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLchar* lv2 = String_val(v2);
	 glBindAttribLocation(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glBindAttribLocationARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLchar* lv2 = String_val(v2);
	 glBindAttribLocationARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glBindBuffer(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBindBuffer(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBindBufferARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBindBufferARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBindBufferBaseNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glBindBufferBaseNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glBindBufferOffsetNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLintptr lv3 = Int_val(v3);
	 glBindBufferOffsetNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glBindBufferRangeNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLintptr lv3 = Int_val(v3);
	GLsizeiptr lv4 = Int_val(v4);
	 glBindBufferRangeNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glBindFragDataLocationEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLchar* lv2 = String_val(v2);
	 glBindFragDataLocationEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glBindFragmentShaderATI(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glBindFragmentShaderATI(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBindFramebufferEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBindFramebufferEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBindLightParameterEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint ret;
	ret =  glBindLightParameterEXT(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glBindMaterialParameterEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint ret;
	ret =  glBindMaterialParameterEXT(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glBindParameterEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint ret;
	ret =  glBindParameterEXT(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glBindProgramARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBindProgramARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBindProgramNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBindProgramNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBindRenderbufferEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBindRenderbufferEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBindTexGenParameterEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint ret;
	ret =  glBindTexGenParameterEXT(lv0, lv1, lv2);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glBindTexture(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBindTexture(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBindTextureEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glBindTextureEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBindTextureUnitParameterEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint ret;
	ret =  glBindTextureUnitParameterEXT(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glBindVertexArray(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glBindVertexArray(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBindVertexArrayAPPLE(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glBindVertexArrayAPPLE(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBindVertexShaderEXT(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glBindVertexShaderEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBinormalPointerEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glBinormalPointerEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glBitmap(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glBitmap_byte(value * argv, int n)
{
	return glstub_glBitmap(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glBlendColor(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLclampf lv0 = Double_val(v0);
	GLclampf lv1 = Double_val(v1);
	GLclampf lv2 = Double_val(v2);
	GLclampf lv3 = Double_val(v3);
	 glBlendColor(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glBlendColorEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLclampf lv0 = Double_val(v0);
	GLclampf lv1 = Double_val(v1);
	GLclampf lv2 = Double_val(v2);
	GLclampf lv3 = Double_val(v3);
	 glBlendColorEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glBlendEquation(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glBlendEquation(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBlendEquationEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glBlendEquationEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glBlendEquationSeparate(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glBlendEquationSeparate(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBlendEquationSeparateEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glBlendEquationSeparateEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBlendFunc(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glBlendFunc(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glBlendFuncSeparate(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	 glBlendFuncSeparate(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glBlendFuncSeparateEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	 glBlendFuncSeparateEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glBlitFramebufferEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glBlitFramebufferEXT_byte(value * argv, int n)
{
	return glstub_glBlitFramebufferEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

value glstub_glBufferData(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizeiptr lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	GLenum lv3 = Int_val(v3);
	 glBufferData(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glBufferDataARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizeiptr lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	GLenum lv3 = Int_val(v3);
	 glBufferDataARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glBufferSubData(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLintptr lv1 = Int_val(v1);
	GLsizeiptr lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glBufferSubData(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glBufferSubDataARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLintptr lv1 = Int_val(v1);
	GLsizeiptr lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glBufferSubDataARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glCallList(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glCallList(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glCallLists(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glCallLists(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glCheckFramebufferStatusEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum ret;
	ret =  glCheckFramebufferStatusEXT(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glClampColorARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glClampColorARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glClear(value v0)
{
	CAMLparam1(v0);
	GLbitfield lv0 = Int_val(v0);
	 glClear(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClearAccum(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glClearAccum(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glClearColor(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLclampf lv0 = Double_val(v0);
	GLclampf lv1 = Double_val(v1);
	GLclampf lv2 = Double_val(v2);
	GLclampf lv3 = Double_val(v3);
	 glClearColor(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glClearColorIiEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glClearColorIiEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glClearColorIuiEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	 glClearColorIuiEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glClearDepth(value v0)
{
	CAMLparam1(v0);
	GLclampd lv0 = Double_val(v0);
	 glClearDepth(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClearDepthdNV(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	 glClearDepthdNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClearDepthfOES(value v0)
{
	CAMLparam1(v0);
	GLclampd lv0 = Double_val(v0);
	 glClearDepthfOES(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClearIndex(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glClearIndex(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClearStencil(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glClearStencil(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClientActiveTexture(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glClientActiveTexture(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClientActiveTextureARB(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glClientActiveTextureARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClientActiveVertexStreamATI(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glClientActiveVertexStreamATI(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glClipPlane(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glClipPlane(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glClipPlanefOES(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glClipPlanefOES(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glColor3b(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	 glColor3b(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor3bv(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	 glColor3bv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glColor3d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glColor3dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glColor3f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glColor3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColor3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glColor3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glColor3fVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glColor3fVertex3fvSUN(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glColor3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glColor3fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glColor3hNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glColor3hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glColor3i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glColor3iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glColor3s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glColor3sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor3ub(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	 glColor3ub(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor3ubv(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	 glColor3ubv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor3ui(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glColor3ui(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor3uiv(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	 glColor3uiv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor3us(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glColor3us(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor3usv(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glColor3usv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4b(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	GLbyte lv3 = Int_val(v3);
	 glColor4b(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColor4bv(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	 glColor4bv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glColor4d(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColor4dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glColor4dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glColor4f(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glColor4fNormal3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glColor4fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glColor4fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

value glstub_glColor4fNormal3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glColor4fNormal3fVertex3fvSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColor4fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glColor4fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	 glColor4hNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColor4hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glColor4hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glColor4i(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColor4iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glColor4iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glColor4s(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColor4sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glColor4sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4ub(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	 glColor4ub(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glColor4ubVertex2fSUN(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColor4ubVertex2fSUN_byte(value * argv, int n)
{
	return glstub_glColor4ubVertex2fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glColor4ubVertex2fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLubyte* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glColor4ubVertex2fvSUN(lv0, lv1);
	CAMLreturn(Val_unit);
}

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
	 glColor4ubVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glColor4ubVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glColor4ubVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glColor4ubVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLubyte* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glColor4ubVertex3fvSUN(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glColor4ubv(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	 glColor4ubv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4ui(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	 glColor4ui(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColor4uiv(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	 glColor4uiv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glColor4us(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	 glColor4us(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColor4usv(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glColor4usv(lv0);
	CAMLreturn(Val_unit);
}

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
	 glColorFragmentOp1ATI(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glColorFragmentOp1ATI_byte(value * argv, int n)
{
	return glstub_glColorFragmentOp1ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glColorFragmentOp2ATI(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glColorFragmentOp2ATI_byte(value * argv, int n)
{
	return glstub_glColorFragmentOp2ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

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
	 glColorFragmentOp3ATI(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11, lv12);
	CAMLreturn(Val_unit);
}

value glstub_glColorFragmentOp3ATI_byte(value * argv, int n)
{
	return glstub_glColorFragmentOp3ATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12]);
}

value glstub_glColorMask(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLboolean lv0 = Bool_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLboolean lv3 = Bool_val(v3);
	 glColorMask(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColorMaskIndexedEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLboolean lv3 = Bool_val(v3);
	GLboolean lv4 = Bool_val(v4);
	 glColorMaskIndexedEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glColorMaterial(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glColorMaterial(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glColorPointer(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glColorPointer(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glColorPointerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glColorPointerEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glColorPointerListIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLint lv4 = Int_val(v4);
	 glColorPointerListIBM(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glColorPointervINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glColorPointervINTEL(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glColorSubTable(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorSubTable_byte(value * argv, int n)
{
	return glstub_glColorSubTable(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glColorSubTableEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorSubTableEXT_byte(value * argv, int n)
{
	return glstub_glColorSubTableEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glColorTable(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorTable_byte(value * argv, int n)
{
	return glstub_glColorTable(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glColorTableEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorTableEXT_byte(value * argv, int n)
{
	return glstub_glColorTableEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glColorTableParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glColorTableParameterfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColorTableParameterfvSGI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glColorTableParameterfvSGI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColorTableParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glColorTableParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glColorTableParameterivSGI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glColorTableParameterivSGI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glColorTableSGI(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glColorTableSGI_byte(value * argv, int n)
{
	return glstub_glColorTableSGI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glCombinerInputNV(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCombinerInputNV_byte(value * argv, int n)
{
	return glstub_glCombinerInputNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glCombinerOutputNV(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glCombinerOutputNV_byte(value * argv, int n)
{
	return glstub_glCombinerOutputNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

value glstub_glCombinerParameterfNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glCombinerParameterfNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glCombinerParameterfvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glCombinerParameterfvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glCombinerParameteriNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glCombinerParameteriNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glCombinerParameterivNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glCombinerParameterivNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glCombinerStageParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glCombinerStageParameterfvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glCompileShader(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glCompileShader(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glCompileShaderARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glCompileShaderARB(lv0);
	CAMLreturn(Val_unit);
}

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
	 glCompressedTexImage1D(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage1D_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glCompressedTexImage1DARB(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage1DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage1DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glCompressedTexImage2D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage2D_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

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
	 glCompressedTexImage2DARB(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage2DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage2DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

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
	 glCompressedTexImage3D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage3D_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glCompressedTexImage3DARB(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexImage3DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexImage3DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glCompressedTexSubImage1D(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage1D_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glCompressedTexSubImage1DARB(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage1DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage1DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glCompressedTexSubImage2D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage2D_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glCompressedTexSubImage2DARB(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage2DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage2DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glCompressedTexSubImage3D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage3D_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

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
	 glCompressedTexSubImage3DARB(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glCompressedTexSubImage3DARB_byte(value * argv, int n)
{
	return glstub_glCompressedTexSubImage3DARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

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
	 glConvolutionFilter1D(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionFilter1D_byte(value * argv, int n)
{
	return glstub_glConvolutionFilter1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glConvolutionFilter1DEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionFilter1DEXT_byte(value * argv, int n)
{
	return glstub_glConvolutionFilter1DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glConvolutionFilter2D(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionFilter2D_byte(value * argv, int n)
{
	return glstub_glConvolutionFilter2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glConvolutionFilter2DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionFilter2DEXT_byte(value * argv, int n)
{
	return glstub_glConvolutionFilter2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glConvolutionParameterf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glConvolutionParameterf(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionParameterfEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glConvolutionParameterfEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glConvolutionParameterfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glConvolutionParameterfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionParameteri(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glConvolutionParameteri(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionParameteriEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glConvolutionParameteriEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glConvolutionParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glConvolutionParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glConvolutionParameterivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glCopyColorSubTable(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glCopyColorSubTable(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glCopyColorSubTableEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glCopyColorSubTableEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glCopyColorTable(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glCopyColorTable(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glCopyColorTableSGI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glCopyColorTableSGI(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glCopyConvolutionFilter1D(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glCopyConvolutionFilter1D(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glCopyConvolutionFilter1DEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glCopyConvolutionFilter1DEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

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
	 glCopyConvolutionFilter2D(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCopyConvolutionFilter2D_byte(value * argv, int n)
{
	return glstub_glCopyConvolutionFilter2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glCopyConvolutionFilter2DEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCopyConvolutionFilter2DEXT_byte(value * argv, int n)
{
	return glstub_glCopyConvolutionFilter2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glCopyPixels(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	 glCopyPixels(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

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
	 glCopyTexImage1D(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexImage1D_byte(value * argv, int n)
{
	return glstub_glCopyTexImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glCopyTexImage1DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexImage1DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexImage1DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glCopyTexImage2D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexImage2D_byte(value * argv, int n)
{
	return glstub_glCopyTexImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

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
	 glCopyTexImage2DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexImage2DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexImage2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

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
	 glCopyTexSubImage1D(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage1D_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glCopyTexSubImage1DEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage1DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage1DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glCopyTexSubImage2D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage2D_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

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
	 glCopyTexSubImage2DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage2DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

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
	 glCopyTexSubImage3D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage3D_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glCopyTexSubImage3DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glCopyTexSubImage3DEXT_byte(value * argv, int n)
{
	return glstub_glCopyTexSubImage3DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

value glstub_glCreateProgram(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint ret;
	ret =  glCreateProgram();
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glCreateProgramObjectARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint ret;
	ret =  glCreateProgramObjectARB();
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glCreateShader(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint ret;
	ret =  glCreateShader(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glCreateShaderObjectARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint ret;
	ret =  glCreateShaderObjectARB(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glCullFace(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glCullFace(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glCullParameterdvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glCullParameterdvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glCullParameterfvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glCullParameterfvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glCurrentPaletteMatrixARB(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glCurrentPaletteMatrixARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteAsyncMarkersSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	 glDeleteAsyncMarkersSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteBuffers(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteBuffers(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteBuffersARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteBuffersARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteFencesAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteFencesAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteFencesNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteFencesNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteFragmentShaderATI(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glDeleteFragmentShaderATI(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteFramebuffersEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteFramebuffersEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteLists(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	 glDeleteLists(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteObjectARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glDeleteObjectARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteOcclusionQueriesNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteOcclusionQueriesNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteProgram(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glDeleteProgram(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteProgramsARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteProgramsARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteProgramsNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteProgramsNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteQueries(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteQueries(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteQueriesARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteQueriesARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteRenderbuffersEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteRenderbuffersEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteShader(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glDeleteShader(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteTextures(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteTextures(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteTexturesEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteTexturesEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteVertexArrays(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteVertexArrays(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteVertexArraysAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glDeleteVertexArraysAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDeleteVertexShaderEXT(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glDeleteVertexShaderEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDepthBoundsEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampd lv0 = Double_val(v0);
	GLclampd lv1 = Double_val(v1);
	 glDepthBoundsEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDepthBoundsdNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glDepthBoundsdNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDepthFunc(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glDepthFunc(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDepthMask(value v0)
{
	CAMLparam1(v0);
	GLboolean lv0 = Bool_val(v0);
	 glDepthMask(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDepthRange(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampd lv0 = Double_val(v0);
	GLclampd lv1 = Double_val(v1);
	 glDepthRange(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDepthRangedNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glDepthRangedNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDepthRangefOES(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLclampf lv1 = Double_val(v1);
	 glDepthRangefOES(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDetachObjectARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glDetachObjectARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDetachShader(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glDetachShader(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDetailTexFuncSGIS(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glDetailTexFuncSGIS(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glDisable(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glDisable(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDisableClientState(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glDisableClientState(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDisableIndexedEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glDisableIndexedEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDisableVariantClientStateEXT(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glDisableVariantClientStateEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDisableVertexAttribArray(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glDisableVertexAttribArray(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDisableVertexAttribArrayARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glDisableVertexAttribArrayARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDrawArrays(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	 glDrawArrays(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glDrawArraysEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	 glDrawArraysEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glDrawArraysInstancedEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glDrawArraysInstancedEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glDrawBuffer(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glDrawBuffer(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glDrawBuffers(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLenum* lv1 = Data_bigarray_val(v1);
	 glDrawBuffers(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDrawBuffersARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLenum* lv1 = Data_bigarray_val(v1);
	 glDrawBuffersARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDrawBuffersATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLenum* lv1 = Data_bigarray_val(v1);
	 glDrawBuffersATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDrawElementArrayAPPLE(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	 glDrawElementArrayAPPLE(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glDrawElementArrayATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	 glDrawElementArrayATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glDrawElements(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glDrawElements(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glDrawElementsInstancedEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	GLsizei lv4 = Int_val(v4);
	 glDrawElementsInstancedEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glDrawPixels(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLsizei lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glDrawPixels(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glDrawRangeElementArrayAPPLE(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glDrawRangeElementArrayAPPLE(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glDrawRangeElementArrayATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glDrawRangeElementArrayATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glDrawRangeElements(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glDrawRangeElements_byte(value * argv, int n)
{
	return glstub_glDrawRangeElements(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glDrawRangeElementsEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glDrawRangeElementsEXT_byte(value * argv, int n)
{
	return glstub_glDrawRangeElementsEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glEdgeFlag(value v0)
{
	CAMLparam1(v0);
	GLboolean lv0 = Bool_val(v0);
	 glEdgeFlag(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEdgeFlagPointer(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	 glEdgeFlagPointer(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glEdgeFlagPointerEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	 glEdgeFlagPointerEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glEdgeFlagPointerListIBM(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLboolean** lv1 = Data_bigarray_val(v1);
	GLint lv2 = Int_val(v2);
	 glEdgeFlagPointerListIBM(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glEdgeFlagv(value v0)
{
	CAMLparam1(v0);
	GLboolean* lv0 = Data_bigarray_val(v0);
	 glEdgeFlagv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glElementPointerAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	 glElementPointerAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glElementPointerATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	 glElementPointerATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glEnable(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glEnable(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEnableClientState(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glEnableClientState(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEnableIndexedEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glEnableIndexedEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glEnableVariantClientStateEXT(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glEnableVariantClientStateEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEnableVertexAttribArray(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glEnableVertexAttribArray(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEnableVertexAttribArrayARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glEnableVertexAttribArrayARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEnd(value v0)
{
	CAMLparam1(v0);
	 glEnd();
	CAMLreturn(Val_unit);
}

value glstub_glEndFragmentShaderATI(value v0)
{
	CAMLparam1(v0);
	 glEndFragmentShaderATI();
	CAMLreturn(Val_unit);
}

value glstub_glEndList(value v0)
{
	CAMLparam1(v0);
	 glEndList();
	CAMLreturn(Val_unit);
}

value glstub_glEndOcclusionQueryNV(value v0)
{
	CAMLparam1(v0);
	 glEndOcclusionQueryNV();
	CAMLreturn(Val_unit);
}

value glstub_glEndQuery(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glEndQuery(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEndQueryARB(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glEndQueryARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEndSceneEXT(value v0)
{
	CAMLparam1(v0);
	 glEndSceneEXT();
	CAMLreturn(Val_unit);
}

value glstub_glEndTransformFeedbackNV(value v0)
{
	CAMLparam1(v0);
	 glEndTransformFeedbackNV();
	CAMLreturn(Val_unit);
}

value glstub_glEndVertexShaderEXT(value v0)
{
	CAMLparam1(v0);
	 glEndVertexShaderEXT();
	CAMLreturn(Val_unit);
}

value glstub_glEvalCoord1d(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	 glEvalCoord1d(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEvalCoord1dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glEvalCoord1dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEvalCoord1f(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glEvalCoord1f(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEvalCoord1fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glEvalCoord1fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEvalCoord2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glEvalCoord2d(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glEvalCoord2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glEvalCoord2dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEvalCoord2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glEvalCoord2f(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glEvalCoord2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glEvalCoord2fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEvalMapsNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glEvalMapsNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glEvalMesh1(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glEvalMesh1(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glEvalMesh2(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glEvalMesh2(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glEvalPoint1(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glEvalPoint1(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glEvalPoint2(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glEvalPoint2(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glExecuteProgramNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glExecuteProgramNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glExtractComponentEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glExtractComponentEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFeedbackBuffer(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glFeedbackBuffer(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFinalCombinerInputNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	 glFinalCombinerInputNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glFinish(value v0)
{
	CAMLparam1(v0);
	 glFinish();
	CAMLreturn(Val_unit);
}

value glstub_glFinishAsyncSGIX(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLint ret;
	ret =  glFinishAsyncSGIX(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glFinishFenceAPPLE(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glFinishFenceAPPLE(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFinishFenceNV(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glFinishFenceNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFinishObjectAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glFinishObjectAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFinishTextureSUNX(value v0)
{
	CAMLparam1(v0);
	 glFinishTextureSUNX();
	CAMLreturn(Val_unit);
}

value glstub_glFlush(value v0)
{
	CAMLparam1(v0);
	 glFlush();
	CAMLreturn(Val_unit);
}

value glstub_glFlushPixelDataRangeNV(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glFlushPixelDataRangeNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFlushRasterSGIX(value v0)
{
	CAMLparam1(v0);
	 glFlushRasterSGIX();
	CAMLreturn(Val_unit);
}

value glstub_glFlushVertexArrayRangeAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	 glFlushVertexArrayRangeAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFlushVertexArrayRangeNV(value v0)
{
	CAMLparam1(v0);
	 glFlushVertexArrayRangeNV();
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordPointer(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glFogCoordPointer(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordPointerEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glFogCoordPointerEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordPointerListIBM(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	GLint lv3 = Int_val(v3);
	 glFogCoordPointerListIBM(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordd(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	 glFogCoordd(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoorddEXT(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	 glFogCoorddEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoorddv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glFogCoorddv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoorddvEXT(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glFogCoorddvEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordf(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glFogCoordf(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordfEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glFogCoordfEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordfv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glFogCoordfv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordfvEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glFogCoordfvEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordhNV(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	 glFogCoordhNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogCoordhvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glFogCoordhvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFogFuncSGIS(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glFogFuncSGIS(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFogf(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glFogf(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFogfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glFogfv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFogi(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glFogi(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFogiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glFogiv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentColorMaterialEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glFragmentColorMaterialEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentColorMaterialSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glFragmentColorMaterialSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightModelfEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glFragmentLightModelfEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightModelfSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glFragmentLightModelfSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightModelfvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glFragmentLightModelfvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightModelfvSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glFragmentLightModelfvSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightModeliEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glFragmentLightModeliEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightModeliSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glFragmentLightModeliSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightModelivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glFragmentLightModelivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightModelivSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glFragmentLightModelivSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightfEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glFragmentLightfEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightfSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glFragmentLightfSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glFragmentLightfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightfvSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glFragmentLightfvSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glFragmentLightiEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightiSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glFragmentLightiSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glFragmentLightivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentLightivSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glFragmentLightivSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentMaterialfEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glFragmentMaterialfEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentMaterialfSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glFragmentMaterialfSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentMaterialfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glFragmentMaterialfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentMaterialfvSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glFragmentMaterialfvSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentMaterialiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glFragmentMaterialiEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentMaterialiSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glFragmentMaterialiSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentMaterialivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glFragmentMaterialivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFragmentMaterialivSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glFragmentMaterialivSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glFrameZoomSGIX(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glFrameZoomSGIX(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFramebufferRenderbufferEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	 glFramebufferRenderbufferEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glFramebufferTexture1DEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glFramebufferTexture1DEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glFramebufferTexture2DEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glFramebufferTexture2DEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

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
	 glFramebufferTexture3DEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glFramebufferTexture3DEXT_byte(value * argv, int n)
{
	return glstub_glFramebufferTexture3DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glFramebufferTextureEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glFramebufferTextureEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glFramebufferTextureFaceEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLenum lv4 = Int_val(v4);
	 glFramebufferTextureFaceEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glFramebufferTextureLayerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glFramebufferTextureLayerEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glFreeObjectBufferATI(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glFreeObjectBufferATI(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glFrontFace(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glFrontFace(lv0);
	CAMLreturn(Val_unit);
}

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
	 glFrustum(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glFrustum_byte(value * argv, int n)
{
	return glstub_glFrustum(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glFrustumfOES(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glFrustumfOES_byte(value * argv, int n)
{
	return glstub_glFrustumfOES(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glGenAsyncMarkersSGIX(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint ret;
	ret =  glGenAsyncMarkersSGIX(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGenBuffers(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenBuffers(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenBuffersARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenBuffersARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenFencesAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenFencesAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenFencesNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenFencesNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenFragmentShadersATI(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLuint ret;
	ret =  glGenFragmentShadersATI(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGenFramebuffersEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenFramebuffersEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenLists(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLuint ret;
	ret =  glGenLists(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGenOcclusionQueriesNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenOcclusionQueriesNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenProgramsARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenProgramsARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenProgramsNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenProgramsNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenQueries(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenQueries(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenQueriesARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenQueriesARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenRenderbuffersEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenRenderbuffersEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenSymbolsEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint ret;
	ret =  glGenSymbolsEXT(lv0, lv1, lv2, lv3);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGenTextures(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenTextures(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenTexturesEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenTexturesEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenVertexArrays(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenVertexArrays(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenVertexArraysAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGenVertexArraysAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGenVertexShadersEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLuint ret;
	ret =  glGenVertexShadersEXT(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGenerateMipmapEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glGenerateMipmapEXT(lv0);
	CAMLreturn(Val_unit);
}

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
	 glGetActiveAttrib(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveAttrib_byte(value * argv, int n)
{
	return glstub_glGetActiveAttrib(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glGetActiveAttribARB(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveAttribARB_byte(value * argv, int n)
{
	return glstub_glGetActiveAttribARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glGetActiveUniform(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveUniform_byte(value * argv, int n)
{
	return glstub_glGetActiveUniform(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glGetActiveUniformARB(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveUniformARB_byte(value * argv, int n)
{
	return glstub_glGetActiveUniformARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glGetActiveVaryingNV(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetActiveVaryingNV_byte(value * argv, int n)
{
	return glstub_glGetActiveVaryingNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glGetArrayObjectfvATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetArrayObjectfvATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetArrayObjectivATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetArrayObjectivATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetAttachedObjectsARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLuint* lv3 = Data_bigarray_val(v3);
	 glGetAttachedObjectsARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetAttachedShaders(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLuint* lv3 = Data_bigarray_val(v3);
	 glGetAttachedShaders(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetAttribLocation(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	ret =  glGetAttribLocation(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetAttribLocationARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	ret =  glGetAttribLocationARB(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetBooleanIndexedvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	 glGetBooleanIndexedvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetBooleanv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLboolean* lv1 = Data_bigarray_val(v1);
	 glGetBooleanv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetBufferParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetBufferParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetBufferParameterivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetBufferParameterivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetBufferPointerv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glGetBufferPointerv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetBufferPointervARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glGetBufferPointervARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetBufferSubData(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLintptr lv1 = Int_val(v1);
	GLsizeiptr lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glGetBufferSubData(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetBufferSubDataARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLintptr lv1 = Int_val(v1);
	GLsizeiptr lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glGetBufferSubDataARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetClipPlane(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glGetClipPlane(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetClipPlanefOES(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glGetClipPlanefOES(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTable(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glGetColorTable(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTableEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glGetColorTableEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTableParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetColorTableParameterfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTableParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetColorTableParameterfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTableParameterfvSGI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetColorTableParameterfvSGI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTableParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetColorTableParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTableParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetColorTableParameterivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTableParameterivSGI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetColorTableParameterivSGI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetColorTableSGI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glGetColorTableSGI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetCombinerInputParameterfvNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLfloat* lv4 = Data_bigarray_val(v4);
	 glGetCombinerInputParameterfvNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glGetCombinerInputParameterivNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLint* lv4 = Data_bigarray_val(v4);
	 glGetCombinerInputParameterivNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glGetCombinerOutputParameterfvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glGetCombinerOutputParameterfvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetCombinerOutputParameterivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glGetCombinerOutputParameterivNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetCombinerStageParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetCombinerStageParameterfvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetCompressedTexImage(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glGetCompressedTexImage(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetCompressedTexImageARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glGetCompressedTexImageARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetConvolutionFilter(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glGetConvolutionFilter(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetConvolutionFilterEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glGetConvolutionFilterEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetConvolutionParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetConvolutionParameterfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetConvolutionParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetConvolutionParameterfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetConvolutionParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetConvolutionParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetConvolutionParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetConvolutionParameterivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetDetailTexFuncSGIS(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glGetDetailTexFuncSGIS(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetDoublev(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glGetDoublev(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetError(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum ret;
	ret =  glGetError();
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetFenceivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetFenceivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFinalCombinerInputParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetFinalCombinerInputParameterfvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFinalCombinerInputParameterivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetFinalCombinerInputParameterivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFloatv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glGetFloatv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetFogFuncSGIS(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glGetFogFuncSGIS(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGetFragDataLocationEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	ret =  glGetFragDataLocationEXT(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetFragmentLightfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetFragmentLightfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFragmentLightfvSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetFragmentLightfvSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFragmentLightivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetFragmentLightivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFragmentLightivSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetFragmentLightivSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFragmentMaterialfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetFragmentMaterialfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFragmentMaterialfvSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetFragmentMaterialfvSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFragmentMaterialivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetFragmentMaterialivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFragmentMaterialivSGIX(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetFragmentMaterialivSGIX(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetFramebufferAttachmentParameterivEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glGetFramebufferAttachmentParameterivEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetHandleARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint ret;
	ret =  glGetHandleARB(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetHistogram(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glGetHistogram(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glGetHistogramEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glGetHistogramEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glGetHistogramParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetHistogramParameterfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetHistogramParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetHistogramParameterfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetHistogramParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetHistogramParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetHistogramParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetHistogramParameterivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetImageTransformParameterfvHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetImageTransformParameterfvHP(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetImageTransformParameterivHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetImageTransformParameterivHP(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetInfoLogARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	 glGetInfoLogARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetIntegerIndexedvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetIntegerIndexedvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetIntegerv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glGetIntegerv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetInvariantBooleanvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	 glGetInvariantBooleanvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetInvariantFloatvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetInvariantFloatvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetInvariantIntegervEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetInvariantIntegervEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetLightfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetLightfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetLightiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetLightiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetLocalConstantBooleanvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	 glGetLocalConstantBooleanvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetLocalConstantFloatvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetLocalConstantFloatvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetLocalConstantIntegervEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetLocalConstantIntegervEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMapAttribParameterfvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glGetMapAttribParameterfvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetMapAttribParameterivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glGetMapAttribParameterivNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glGetMapControlPointsNV(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glGetMapControlPointsNV_byte(value * argv, int n)
{
	return glstub_glGetMapControlPointsNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glGetMapParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetMapParameterfvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMapParameterivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetMapParameterivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMapdv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glGetMapdv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMapfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetMapfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMapiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetMapiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMaterialfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetMaterialfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMaterialiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetMaterialiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMinmax(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glGetMinmax(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glGetMinmaxEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLboolean lv1 = Bool_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glGetMinmaxEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glGetMinmaxParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetMinmaxParameterfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMinmaxParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetMinmaxParameterfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMinmaxParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetMinmaxParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetMinmaxParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetMinmaxParameterivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetObjectBufferfvATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetObjectBufferfvATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetObjectBufferivATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetObjectBufferivATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetObjectParameterfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetObjectParameterfvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetObjectParameterivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetObjectParameterivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetOcclusionQueryivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetOcclusionQueryivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetOcclusionQueryuivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glGetOcclusionQueryuivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetPixelMapfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glGetPixelMapfv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetPixelMapuiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glGetPixelMapuiv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetPixelMapusv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glGetPixelMapusv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetPixelTransformParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetPixelTransformParameterfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetPixelTransformParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetPixelTransformParameterivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetPointerv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid** lv1 = Data_bigarray_val(v1);
	 glGetPointerv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetPointervEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid** lv1 = Data_bigarray_val(v1);
	 glGetPointervEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetPolygonStipple(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	 glGetPolygonStipple(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramEnvParameterdvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glGetProgramEnvParameterdvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramEnvParameterfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetProgramEnvParameterfvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramInfoLog(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	 glGetProgramInfoLog(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramLocalParameterdvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glGetProgramLocalParameterdvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramLocalParameterfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetProgramLocalParameterfvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramNamedParameterdvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLdouble* lv3 = (Tag_val(v3) == Double_array_tag)? (double *)v3: Data_bigarray_val(v3);
	 glGetProgramNamedParameterdvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramNamedParameterfvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glGetProgramNamedParameterfvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramParameterdvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLdouble* lv3 = (Tag_val(v3) == Double_array_tag)? (double *)v3: Data_bigarray_val(v3);
	 glGetProgramParameterdvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramParameterfvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glGetProgramParameterfvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramStringARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glGetProgramStringARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramStringNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	 glGetProgramStringNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetProgramiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetProgramivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetProgramivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetProgramivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetQueryObjectiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetQueryObjectiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetQueryObjectivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetQueryObjectivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetQueryObjectuiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glGetQueryObjectuiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetQueryObjectuivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glGetQueryObjectuivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetQueryiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetQueryiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetQueryivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetQueryivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetRenderbufferParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetRenderbufferParameterivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glGetSeparableFilter(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glGetSeparableFilter_byte(value * argv, int n)
{
	return glstub_glGetSeparableFilter(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glGetSeparableFilterEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glGetSeparableFilterEXT_byte(value * argv, int n)
{
	return glstub_glGetSeparableFilterEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glGetShaderInfoLog(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	 glGetShaderInfoLog(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetShaderSource(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	 glGetShaderSource(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetShaderSourceARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLchar* lv3 = String_val(v3);
	 glGetShaderSourceARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetShaderiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetShaderiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetSharpenTexFuncSGIS(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glGetSharpenTexFuncSGIS(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetString(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLstring ret;
	ret =  glGetString(lv0);
	result = caml_copy_string(ret);
	CAMLreturn(result);
}

value glstub_glGetTexBumpParameterfvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glGetTexBumpParameterfvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexBumpParameterivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glGetTexBumpParameterivATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexEnvfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetTexEnvfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexEnviv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetTexEnviv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexFilterFuncSGIS(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetTexFilterFuncSGIS(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexGendv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glGetTexGendv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexGenfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetTexGenfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexGeniv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetTexGeniv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexImage(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glGetTexImage(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexLevelParameterfv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glGetTexLevelParameterfv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexLevelParameteriv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glGetTexLevelParameteriv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexParameterIivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetTexParameterIivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexParameterIuivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glGetTexParameterIuivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexParameterPointervAPPLE(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glGetTexParameterPointervAPPLE(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetTexParameterfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTexParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetTexParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetTrackMatrixivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glGetTrackMatrixivNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glGetTransformFeedbackVaryingNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetTransformFeedbackVaryingNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetUniformBufferSizeEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint ret;
	ret =  glGetUniformBufferSizeEXT(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetUniformLocation(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	ret =  glGetUniformLocation(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetUniformLocationARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	ret =  glGetUniformLocationARB(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetUniformOffsetEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLintptr ret;
	ret =  glGetUniformOffsetEXT(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetUniformfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetUniformfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetUniformfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetUniformfvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetUniformiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetUniformiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetUniformivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetUniformivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetUniformuivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glGetUniformuivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVariantArrayObjectfvATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetVariantArrayObjectfvATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVariantArrayObjectivATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetVariantArrayObjectivATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVariantBooleanvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean* lv2 = Data_bigarray_val(v2);
	 glGetVariantBooleanvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVariantFloatvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetVariantFloatvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVariantIntegervEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetVariantIntegervEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVariantPointervEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glGetVariantPointervEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVaryingLocationNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLchar* lv1 = String_val(v1);
	GLint ret;
	ret =  glGetVaryingLocationNV(lv0, lv1);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glGetVertexAttribArrayObjectfvATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribArrayObjectfvATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribArrayObjectivATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribArrayObjectivATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribIivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribIivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribIuivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribIuivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribPointerv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glGetVertexAttribPointerv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribPointervARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribPointervARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribPointervNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribPointervNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribdv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glGetVertexAttribdv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribdvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glGetVertexAttribdvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribdvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glGetVertexAttribdvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribfvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribfvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribfvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGetVertexAttribivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glGetVertexAttribivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glGlobalAlphaFactorbSUN(value v0)
{
	CAMLparam1(v0);
	GLbyte lv0 = Int_val(v0);
	 glGlobalAlphaFactorbSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGlobalAlphaFactordSUN(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	 glGlobalAlphaFactordSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGlobalAlphaFactorfSUN(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glGlobalAlphaFactorfSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGlobalAlphaFactoriSUN(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glGlobalAlphaFactoriSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGlobalAlphaFactorsSUN(value v0)
{
	CAMLparam1(v0);
	GLshort lv0 = Int_val(v0);
	 glGlobalAlphaFactorsSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGlobalAlphaFactorubSUN(value v0)
{
	CAMLparam1(v0);
	GLubyte lv0 = Int_val(v0);
	 glGlobalAlphaFactorubSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGlobalAlphaFactoruiSUN(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glGlobalAlphaFactoruiSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glGlobalAlphaFactorusSUN(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	 glGlobalAlphaFactorusSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glHint(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glHint(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glHistogram(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLboolean lv3 = Bool_val(v3);
	 glHistogram(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glHistogramEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLboolean lv3 = Bool_val(v3);
	 glHistogramEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glImageTransformParameterfHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glImageTransformParameterfHP(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glImageTransformParameterfvHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glImageTransformParameterfvHP(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glImageTransformParameteriHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glImageTransformParameteriHP(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glImageTransformParameterivHP(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glImageTransformParameterivHP(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glIndexFuncEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glIndexFuncEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glIndexMask(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glIndexMask(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexMaterialEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glIndexMaterialEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glIndexPointer(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glIndexPointer(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glIndexPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glIndexPointerEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glIndexPointerListIBM(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	GLint lv3 = Int_val(v3);
	 glIndexPointerListIBM(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glIndexd(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	 glIndexd(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexdv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glIndexdv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexf(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glIndexf(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexfv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glIndexfv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexi(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glIndexi(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexiv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glIndexiv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexs(value v0)
{
	CAMLparam1(v0);
	GLshort lv0 = Int_val(v0);
	 glIndexs(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexsv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glIndexsv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexub(value v0)
{
	CAMLparam1(v0);
	GLubyte lv0 = Int_val(v0);
	 glIndexub(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glIndexubv(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	 glIndexubv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glInitNames(value v0)
{
	CAMLparam1(v0);
	 glInitNames();
	CAMLreturn(Val_unit);
}

value glstub_glInsertComponentEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glInsertComponentEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glInterleavedArrays(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glInterleavedArrays(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glIsAsyncMarkerSGIX(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsAsyncMarkerSGIX(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsBuffer(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsBuffer(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsBufferARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsBufferARB(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsEnabled(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsEnabled(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsEnabledIndexedEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLboolean ret;
	ret =  glIsEnabledIndexedEXT(lv0, lv1);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsFenceAPPLE(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsFenceAPPLE(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsFenceNV(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsFenceNV(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsFramebufferEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsFramebufferEXT(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsList(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsList(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsObjectBufferATI(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsObjectBufferATI(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsOcclusionQueryNV(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsOcclusionQueryNV(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsProgram(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsProgram(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsProgramARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsProgramARB(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsProgramNV(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsProgramNV(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsQuery(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsQuery(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsQueryARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsQueryARB(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsRenderbufferEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsRenderbufferEXT(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsShader(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsShader(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsTexture(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsTexture(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsTextureEXT(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsTextureEXT(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsVariantEnabledEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean ret;
	ret =  glIsVariantEnabledEXT(lv0, lv1);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsVertexArray(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsVertexArray(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glIsVertexArrayAPPLE(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glIsVertexArrayAPPLE(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glLightEnviEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glLightEnviEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glLightModelf(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glLightModelf(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glLightModelfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glLightModelfv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glLightModeli(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glLightModeli(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glLightModeliv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glLightModeliv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glLightf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glLightf(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glLightfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glLightfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glLighti(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glLighti(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glLightiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glLightiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glLineStipple(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	 glLineStipple(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glLineWidth(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glLineWidth(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLinkProgram(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glLinkProgram(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLinkProgramARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glLinkProgramARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glListBase(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glListBase(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLoadIdentity(value v0)
{
	CAMLparam1(v0);
	 glLoadIdentity();
	CAMLreturn(Val_unit);
}

value glstub_glLoadMatrixd(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glLoadMatrixd(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLoadMatrixf(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glLoadMatrixf(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLoadName(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glLoadName(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLoadProgramNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLubyte* lv3 = Data_bigarray_val(v3);
	 glLoadProgramNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glLoadTransposeMatrixd(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glLoadTransposeMatrixd(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLoadTransposeMatrixdARB(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glLoadTransposeMatrixdARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLoadTransposeMatrixf(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glLoadTransposeMatrixf(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLoadTransposeMatrixfARB(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glLoadTransposeMatrixfARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glLockArraysEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	 glLockArraysEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glLogicOp(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glLogicOp(lv0);
	CAMLreturn(Val_unit);
}

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
	 glMap1d(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMap1d_byte(value * argv, int n)
{
	return glstub_glMap1d(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glMap1f(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMap1f_byte(value * argv, int n)
{
	return glstub_glMap1f(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glMap2d(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glMap2d_byte(value * argv, int n)
{
	return glstub_glMap2d(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

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
	 glMap2f(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glMap2f_byte(value * argv, int n)
{
	return glstub_glMap2f(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

value glstub_glMapBuffer(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* ret;
	ret =  glMapBuffer(lv0, lv1);
	result = (value)(ret);
	CAMLreturn(result);
}

value glstub_glMapBufferARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* ret;
	ret =  glMapBufferARB(lv0, lv1);
	result = (value)(ret);
	CAMLreturn(result);
}

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
	 glMapControlPointsNV(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glMapControlPointsNV_byte(value * argv, int n)
{
	return glstub_glMapControlPointsNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

value glstub_glMapGrid1d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glMapGrid1d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMapGrid1f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glMapGrid1f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glMapGrid2d(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMapGrid2d_byte(value * argv, int n)
{
	return glstub_glMapGrid2d(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glMapGrid2f(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMapGrid2f_byte(value * argv, int n)
{
	return glstub_glMapGrid2f(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glMapObjectBufferATI(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	void* ret;
	ret =  glMapObjectBufferATI(lv0);
	result = (value)(ret);
	CAMLreturn(result);
}

value glstub_glMapParameterfvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glMapParameterfvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMapParameterivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glMapParameterivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMaterialf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glMaterialf(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMaterialfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glMaterialfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMateriali(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glMateriali(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMaterialiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glMaterialiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMatrixIndexPointerARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glMatrixIndexPointerARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMatrixIndexubvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glMatrixIndexubvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMatrixIndexuivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glMatrixIndexuivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMatrixIndexusvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glMatrixIndexusvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMatrixMode(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glMatrixMode(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glMinmax(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	 glMinmax(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMinmaxEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	 glMinmaxEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultMatrixd(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glMultMatrixd(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glMultMatrixf(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glMultMatrixf(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glMultTransposeMatrixd(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glMultTransposeMatrixd(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glMultTransposeMatrixdARB(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glMultTransposeMatrixdARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glMultTransposeMatrixf(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glMultTransposeMatrixf(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glMultTransposeMatrixfARB(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glMultTransposeMatrixfARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glMultiDrawArrays(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glMultiDrawArrays(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiDrawArraysEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glMultiDrawArraysEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiDrawElementArrayAPPLE(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glMultiDrawElementArrayAPPLE(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiDrawElements(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei* lv1 = Data_bigarray_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glMultiDrawElements(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiDrawElementsEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei* lv1 = Data_bigarray_val(v1);
	GLenum lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glMultiDrawElementsEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

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
	 glMultiDrawRangeElementArrayAPPLE(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMultiDrawRangeElementArrayAPPLE_byte(value * argv, int n)
{
	return glstub_glMultiDrawRangeElementArrayAPPLE(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glMultiModeDrawArraysIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum* lv0 = Data_bigarray_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLsizei* lv2 = Data_bigarray_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glMultiModeDrawArraysIBM(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

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
	 glMultiModeDrawElementsIBM(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glMultiModeDrawElementsIBM_byte(value * argv, int n)
{
	return glstub_glMultiModeDrawElementsIBM(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glMultiTexCoord1d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glMultiTexCoord1d(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1dARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glMultiTexCoord1dARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glMultiTexCoord1dv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glMultiTexCoord1dvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glMultiTexCoord1f(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1fARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glMultiTexCoord1fARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord1fv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord1fvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1hNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	 glMultiTexCoord1hNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord1hvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glMultiTexCoord1i(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1iARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glMultiTexCoord1iARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord1iv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord1ivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glMultiTexCoord1s(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1sARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glMultiTexCoord1sARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord1sv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord1svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord1svARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glMultiTexCoord2d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2dARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glMultiTexCoord2dARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glMultiTexCoord2dv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glMultiTexCoord2dvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glMultiTexCoord2f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2fARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glMultiTexCoord2fARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord2fv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord2fvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glMultiTexCoord2hNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord2hvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glMultiTexCoord2i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2iARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glMultiTexCoord2iARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord2iv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord2ivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glMultiTexCoord2s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2sARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glMultiTexCoord2sARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord2sv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord2svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord2svARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glMultiTexCoord3d(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3dARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glMultiTexCoord3dARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glMultiTexCoord3dv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glMultiTexCoord3dvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glMultiTexCoord3f(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3fARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glMultiTexCoord3fARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord3fv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord3fvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	 glMultiTexCoord3hNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord3hvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glMultiTexCoord3i(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3iARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glMultiTexCoord3iARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord3iv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord3ivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glMultiTexCoord3s(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3sARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glMultiTexCoord3sARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord3sv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord3svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord3svARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4d(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	 glMultiTexCoord4d(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4dARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	 glMultiTexCoord4dARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glMultiTexCoord4dv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glMultiTexCoord4dvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4f(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glMultiTexCoord4f(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4fARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glMultiTexCoord4fARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord4fv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord4fvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4hNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	GLushort lv4 = Int_val(v4);
	 glMultiTexCoord4hNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord4hvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4i(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glMultiTexCoord4i(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4iARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glMultiTexCoord4iARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord4iv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord4ivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4s(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	 glMultiTexCoord4s(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4sARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	 glMultiTexCoord4sARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord4sv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glMultiTexCoord4svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glMultiTexCoord4svARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glNewList(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glNewList(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glNewObjectBufferATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	CAMLlocal1(result);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	GLenum lv2 = Int_val(v2);
	GLuint ret;
	ret =  glNewObjectBufferATI(lv0, lv1, lv2);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glNormal3b(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	 glNormal3b(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3bv(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	 glNormal3bv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glNormal3d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glNormal3dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glNormal3f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glNormal3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glNormal3fVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glNormal3fVertex3fvSUN(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glNormal3fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glNormal3hNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glNormal3hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glNormal3i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glNormal3iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glNormal3s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glNormal3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glNormal3sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glNormalPointer(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glNormalPointer(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glNormalPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glNormalPointerEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glNormalPointerListIBM(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	GLint lv3 = Int_val(v3);
	 glNormalPointerListIBM(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glNormalPointervINTEL(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLvoid** lv1 = Data_bigarray_val(v1);
	 glNormalPointervINTEL(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3bATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	GLbyte lv3 = Int_val(v3);
	 glNormalStream3bATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3bvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	 glNormalStream3bvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3dATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glNormalStream3dATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3dvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glNormalStream3dvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3fATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glNormalStream3fATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3fvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glNormalStream3fvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3iATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glNormalStream3iATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3ivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glNormalStream3ivATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3sATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glNormalStream3sATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glNormalStream3svATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glNormalStream3svATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

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
	 glOrtho(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glOrtho_byte(value * argv, int n)
{
	return glstub_glOrtho(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glOrthofOES(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glOrthofOES_byte(value * argv, int n)
{
	return glstub_glOrthofOES(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glPNTrianglesfATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPNTrianglesfATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPNTrianglesiATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glPNTrianglesiATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPassTexCoordATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	 glPassTexCoordATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPassThrough(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glPassThrough(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glPixelDataRangeNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glPixelDataRangeNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPixelMapfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glPixelMapfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPixelMapuiv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glPixelMapuiv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPixelMapusv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	 glPixelMapusv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPixelStoref(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPixelStoref(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPixelStorei(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glPixelStorei(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPixelTexGenSGIX(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glPixelTexGenSGIX(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glPixelTransferf(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPixelTransferf(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPixelTransferi(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glPixelTransferi(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPixelTransformParameterfEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glPixelTransformParameterfEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPixelTransformParameterfvEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glPixelTransformParameterfvEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPixelTransformParameteriEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glPixelTransformParameteriEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPixelTransformParameterivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glPixelTransformParameterivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPixelZoom(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPixelZoom(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointParameterf(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPointParameterf(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointParameterfARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPointParameterfARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointParameterfEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPointParameterfEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointParameterfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glPointParameterfv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointParameterfvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glPointParameterfvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointParameterfvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glPointParameterfvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointParameteriNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glPointParameteriNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointParameterivNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glPointParameterivNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPointSize(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glPointSize(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glPollAsyncSGIX(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLint ret;
	ret =  glPollAsyncSGIX(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glPolygonMode(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glPolygonMode(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPolygonOffset(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPolygonOffset(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPolygonOffsetEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glPolygonOffsetEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPolygonStipple(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	 glPolygonStipple(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glPopAttrib(value v0)
{
	CAMLparam1(v0);
	 glPopAttrib();
	CAMLreturn(Val_unit);
}

value glstub_glPopClientAttrib(value v0)
{
	CAMLparam1(v0);
	 glPopClientAttrib();
	CAMLreturn(Val_unit);
}

value glstub_glPopMatrix(value v0)
{
	CAMLparam1(v0);
	 glPopMatrix();
	CAMLreturn(Val_unit);
}

value glstub_glPopName(value v0)
{
	CAMLparam1(v0);
	 glPopName();
	CAMLreturn(Val_unit);
}

value glstub_glPrimitiveRestartIndexNV(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glPrimitiveRestartIndexNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glPrimitiveRestartNV(value v0)
{
	CAMLparam1(v0);
	 glPrimitiveRestartNV();
	CAMLreturn(Val_unit);
}

value glstub_glPrioritizeTextures(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLclampf* lv2 = Data_bigarray_val(v2);
	 glPrioritizeTextures(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glPrioritizeTexturesEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	GLclampf* lv2 = Data_bigarray_val(v2);
	 glPrioritizeTexturesEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glProgramBufferParametersIivNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLint* lv4 = Data_bigarray_val(v4);
	 glProgramBufferParametersIivNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glProgramBufferParametersIuivNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLuint* lv4 = Data_bigarray_val(v4);
	 glProgramBufferParametersIuivNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glProgramBufferParametersfvNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLfloat* lv4 = Data_bigarray_val(v4);
	 glProgramBufferParametersfvNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

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
	 glProgramEnvParameter4dARB(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameter4dARB_byte(value * argv, int n)
{
	return glstub_glProgramEnvParameter4dARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramEnvParameter4dvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glProgramEnvParameter4dvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glProgramEnvParameter4fARB(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameter4fARB_byte(value * argv, int n)
{
	return glstub_glProgramEnvParameter4fARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramEnvParameter4fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glProgramEnvParameter4fvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glProgramEnvParameterI4iNV(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameterI4iNV_byte(value * argv, int n)
{
	return glstub_glProgramEnvParameterI4iNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramEnvParameterI4ivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glProgramEnvParameterI4ivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glProgramEnvParameterI4uiNV(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameterI4uiNV_byte(value * argv, int n)
{
	return glstub_glProgramEnvParameterI4uiNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramEnvParameterI4uivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glProgramEnvParameterI4uivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParameters4fvEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glProgramEnvParameters4fvEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParametersI4ivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glProgramEnvParametersI4ivNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glProgramEnvParametersI4uivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLuint* lv3 = Data_bigarray_val(v3);
	 glProgramEnvParametersI4uivNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glProgramLocalParameter4dARB(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameter4dARB_byte(value * argv, int n)
{
	return glstub_glProgramLocalParameter4dARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramLocalParameter4dvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glProgramLocalParameter4dvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glProgramLocalParameter4fARB(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameter4fARB_byte(value * argv, int n)
{
	return glstub_glProgramLocalParameter4fARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramLocalParameter4fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glProgramLocalParameter4fvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glProgramLocalParameterI4iNV(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameterI4iNV_byte(value * argv, int n)
{
	return glstub_glProgramLocalParameterI4iNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramLocalParameterI4ivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glProgramLocalParameterI4ivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glProgramLocalParameterI4uiNV(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameterI4uiNV_byte(value * argv, int n)
{
	return glstub_glProgramLocalParameterI4uiNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramLocalParameterI4uivNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glProgramLocalParameterI4uivNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParameters4fvEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glProgramLocalParameters4fvEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParametersI4ivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glProgramLocalParametersI4ivNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glProgramLocalParametersI4uivNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLuint* lv3 = Data_bigarray_val(v3);
	 glProgramLocalParametersI4uivNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glProgramNamedParameter4dNV(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glProgramNamedParameter4dNV_byte(value * argv, int n)
{
	return glstub_glProgramNamedParameter4dNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glProgramNamedParameter4dvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLdouble* lv3 = (Tag_val(v3) == Double_array_tag)? (double *)v3: Data_bigarray_val(v3);
	 glProgramNamedParameter4dvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glProgramNamedParameter4fNV(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glProgramNamedParameter4fNV_byte(value * argv, int n)
{
	return glstub_glProgramNamedParameter4fNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glProgramNamedParameter4fvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glProgramNamedParameter4fvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glProgramParameter4dNV(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramParameter4dNV_byte(value * argv, int n)
{
	return glstub_glProgramParameter4dNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramParameter4dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glProgramParameter4dvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glProgramParameter4fNV(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glProgramParameter4fNV_byte(value * argv, int n)
{
	return glstub_glProgramParameter4fNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glProgramParameter4fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glProgramParameter4fvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glProgramParameteriEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glProgramParameteriEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glProgramParameters4dvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLdouble* lv3 = (Tag_val(v3) == Double_array_tag)? (double *)v3: Data_bigarray_val(v3);
	 glProgramParameters4dvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glProgramParameters4fvNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glProgramParameters4fvNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glProgramStringARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glProgramStringARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glProgramVertexLimitNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glProgramVertexLimitNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glPushAttrib(value v0)
{
	CAMLparam1(v0);
	GLbitfield lv0 = Int_val(v0);
	 glPushAttrib(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glPushClientAttrib(value v0)
{
	CAMLparam1(v0);
	GLbitfield lv0 = Int_val(v0);
	 glPushClientAttrib(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glPushMatrix(value v0)
{
	CAMLparam1(v0);
	 glPushMatrix();
	CAMLreturn(Val_unit);
}

value glstub_glPushName(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glPushName(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glRasterPos2d(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glRasterPos2dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glRasterPos2f(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glRasterPos2fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos2i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glRasterPos2i(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos2iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glRasterPos2iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos2s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glRasterPos2s(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos2sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glRasterPos2sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glRasterPos3d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glRasterPos3dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glRasterPos3f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glRasterPos3fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glRasterPos3i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glRasterPos3iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glRasterPos3s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glRasterPos3sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos4d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glRasterPos4d(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos4dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glRasterPos4dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos4f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glRasterPos4f(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos4fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glRasterPos4fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos4i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glRasterPos4i(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos4iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glRasterPos4iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos4s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glRasterPos4s(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRasterPos4sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glRasterPos4sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glReadBuffer(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glReadBuffer(lv0);
	CAMLreturn(Val_unit);
}

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
	 glReadPixels(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glReadPixels_byte(value * argv, int n)
{
	return glstub_glReadPixels(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glReadVideoPixelsSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glReadVideoPixelsSUN_byte(value * argv, int n)
{
	return glstub_glReadVideoPixelsSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glRectd(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glRectd(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRectdv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glRectdv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glRectf(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glRectf(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRectfv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glRectfv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glRecti(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glRecti(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRectiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint* lv0 = Data_bigarray_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glRectiv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glRects(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glRects(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRectsv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort* lv0 = Data_bigarray_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glRectsv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glReferencePlaneSGIX(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glReferencePlaneSGIX(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRenderMode(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLint ret;
	ret =  glRenderMode(lv0);
	result = Val_int(ret);
	CAMLreturn(result);
}

value glstub_glRenderbufferStorageEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glRenderbufferStorageEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glRenderbufferStorageMultisampleCoverageNV(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glRenderbufferStorageMultisampleCoverageNV_byte(value * argv, int n)
{
	return glstub_glRenderbufferStorageMultisampleCoverageNV(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glRenderbufferStorageMultisampleEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLsizei lv4 = Int_val(v4);
	 glRenderbufferStorageMultisampleEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodePointerSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glReplacementCodePointerSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeubSUN(value v0)
{
	CAMLparam1(v0);
	GLubyte lv0 = Int_val(v0);
	 glReplacementCodeubSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeubvSUN(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	 glReplacementCodeubvSUN(lv0);
	CAMLreturn(Val_unit);
}

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
	 glReplacementCodeuiColor3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiColor3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiColor3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glReplacementCodeuiColor3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glReplacementCodeuiColor3fVertex3fvSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glReplacementCodeuiColor4fNormal3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiColor4fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiColor4fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

value glstub_glReplacementCodeuiColor4fNormal3fVertex3fvSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glReplacementCodeuiColor4fNormal3fVertex3fvSUN(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glReplacementCodeuiColor4ubVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiColor4ubVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiColor4ubVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

value glstub_glReplacementCodeuiColor4ubVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glReplacementCodeuiColor4ubVertex3fvSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glReplacementCodeuiNormal3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glReplacementCodeuiNormal3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glReplacementCodeuiNormal3fVertex3fvSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiSUN(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glReplacementCodeuiSUN(lv0);
	CAMLreturn(Val_unit);
}

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
	 glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11, lv12);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12]);
}

value glstub_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	GLfloat* lv4 = Data_bigarray_val(v4);
	 glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

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
	 glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

value glstub_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glReplacementCodeuiTexCoord2fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiTexCoord2fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glReplacementCodeuiTexCoord2fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glReplacementCodeuiTexCoord2fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glReplacementCodeuiTexCoord2fVertex3fvSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiVertex3fSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glReplacementCodeuiVertex3fSUN(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuiVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glReplacementCodeuiVertex3fvSUN(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeuivSUN(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	 glReplacementCodeuivSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeusSUN(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	 glReplacementCodeusSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glReplacementCodeusvSUN(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glReplacementCodeusvSUN(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glRequestResidentProgramsNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glRequestResidentProgramsNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glResetHistogram(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glResetHistogram(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glResetHistogramEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glResetHistogramEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glResetMinmax(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glResetMinmax(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glResetMinmaxEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glResetMinmaxEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glResizeBuffersMESA(value v0)
{
	CAMLparam1(v0);
	 glResizeBuffersMESA();
	CAMLreturn(Val_unit);
}

value glstub_glRotated(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glRotated(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glRotatef(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glRotatef(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glSampleCoverage(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLboolean lv1 = Bool_val(v1);
	 glSampleCoverage(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSampleCoverageARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLboolean lv1 = Bool_val(v1);
	 glSampleCoverageARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSampleMapATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	 glSampleMapATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSampleMaskEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLboolean lv1 = Bool_val(v1);
	 glSampleMaskEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSampleMaskSGIS(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLclampf lv0 = Double_val(v0);
	GLboolean lv1 = Bool_val(v1);
	 glSampleMaskSGIS(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSamplePatternEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glSamplePatternEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSamplePatternSGIS(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glSamplePatternSGIS(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glScaled(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glScaled(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glScalef(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glScalef(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glScissor(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glScissor(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3b(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	 glSecondaryColor3b(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3bEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLbyte lv0 = Int_val(v0);
	GLbyte lv1 = Int_val(v1);
	GLbyte lv2 = Int_val(v2);
	 glSecondaryColor3bEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3bv(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3bv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3bvEXT(value v0)
{
	CAMLparam1(v0);
	GLbyte* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3bvEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glSecondaryColor3d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3dEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glSecondaryColor3dEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glSecondaryColor3dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3dvEXT(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glSecondaryColor3dvEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glSecondaryColor3f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3fEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glSecondaryColor3fEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3fvEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3fvEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glSecondaryColor3hNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glSecondaryColor3i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3iEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glSecondaryColor3iEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3ivEXT(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3ivEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glSecondaryColor3s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3sEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glSecondaryColor3sEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3svEXT(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3svEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3ub(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	 glSecondaryColor3ub(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3ubEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLubyte lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	 glSecondaryColor3ubEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3ubv(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3ubv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3ubvEXT(value v0)
{
	CAMLparam1(v0);
	GLubyte* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3ubvEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3ui(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glSecondaryColor3ui(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3uiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glSecondaryColor3uiEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3uiv(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3uiv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3uivEXT(value v0)
{
	CAMLparam1(v0);
	GLuint* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3uivEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3us(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glSecondaryColor3us(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3usEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glSecondaryColor3usEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3usv(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3usv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColor3usvEXT(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glSecondaryColor3usvEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColorPointer(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glSecondaryColorPointer(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColorPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glSecondaryColorPointerEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glSecondaryColorPointerListIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLint lv4 = Int_val(v4);
	 glSecondaryColorPointerListIBM(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glSelectBuffer(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glSelectBuffer(lv0, lv1);
	CAMLreturn(Val_unit);
}

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
	 glSeparableFilter2D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glSeparableFilter2D_byte(value * argv, int n)
{
	return glstub_glSeparableFilter2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

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
	 glSeparableFilter2DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glSeparableFilter2DEXT_byte(value * argv, int n)
{
	return glstub_glSeparableFilter2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

value glstub_glSetFenceAPPLE(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glSetFenceAPPLE(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glSetFenceNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glSetFenceNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSetFragmentShaderConstantATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glSetFragmentShaderConstantATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSetInvariantEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glSetInvariantEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSetLocalConstantEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glSetLocalConstantEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glShadeModel(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glShadeModel(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glShaderOp1EXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glShaderOp1EXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glShaderOp2EXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	 glShaderOp2EXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glShaderOp3EXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	 glShaderOp3EXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glShaderSource(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLchar** lv2 = (GLchar** )(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glShaderSource(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glShaderSourceARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLchar** lv2 = (GLchar** )(v2);
	GLint* lv3 = Data_bigarray_val(v3);
	 glShaderSourceARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glSharpenTexFuncSGIS(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glSharpenTexFuncSGIS(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glSpriteParameterfSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glSpriteParameterfSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSpriteParameterfvSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glSpriteParameterfvSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSpriteParameteriSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glSpriteParameteriSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glSpriteParameterivSGIX(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glSpriteParameterivSGIX(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glStencilFunc(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glStencilFunc(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glStencilFuncSeparate(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	 glStencilFuncSeparate(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glStencilFuncSeparateATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	 glStencilFuncSeparateATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glStencilMask(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glStencilMask(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glStencilMaskSeparate(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glStencilMaskSeparate(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glStencilOp(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	 glStencilOp(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glStencilOpSeparate(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	 glStencilOpSeparate(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glStencilOpSeparateATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	 glStencilOpSeparateATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glStringMarkerGREMEDY(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	 glStringMarkerGREMEDY(lv0, lv1);
	CAMLreturn(Val_unit);
}

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
	 glSwizzleEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glSwizzleEXT_byte(value * argv, int n)
{
	return glstub_glSwizzleEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glTagSampleBufferSGIX(value v0)
{
	CAMLparam1(v0);
	 glTagSampleBufferSGIX();
	CAMLreturn(Val_unit);
}

value glstub_glTangentPointerEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glTangentPointerEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTbufferMask3DFX(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glTbufferMask3DFX(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTestFenceAPPLE(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glTestFenceAPPLE(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glTestFenceNV(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLuint lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glTestFenceNV(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glTestObjectAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLboolean ret;
	ret =  glTestObjectAPPLE(lv0, lv1);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glTexBufferEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glTexBufferEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexBumpParameterfvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glTexBumpParameterfvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTexBumpParameterivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glTexBumpParameterivATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1d(value v0)
{
	CAMLparam1(v0);
	GLdouble lv0 = Double_val(v0);
	 glTexCoord1d(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glTexCoord1dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1f(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glTexCoord1f(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glTexCoord1fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1hNV(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	 glTexCoord1hNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glTexCoord1hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1i(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glTexCoord1i(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glTexCoord1iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1s(value v0)
{
	CAMLparam1(v0);
	GLshort lv0 = Int_val(v0);
	 glTexCoord1s(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord1sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glTexCoord1sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glTexCoord2d(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glTexCoord2dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glTexCoord2f(lv0, lv1);
	CAMLreturn(Val_unit);
}

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
	 glTexCoord2fColor3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fColor3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord2fColor3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

value glstub_glTexCoord2fColor3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glTexCoord2fColor3fVertex3fvSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glTexCoord2fColor4fNormal3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fColor4fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord2fColor4fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11]);
}

value glstub_glTexCoord2fColor4fNormal3fVertex3fvSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glTexCoord2fColor4fNormal3fVertex3fvSUN(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glTexCoord2fColor4ubVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fColor4ubVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord2fColor4ubVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

value glstub_glTexCoord2fColor4ubVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glTexCoord2fColor4ubVertex3fvSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glTexCoord2fNormal3fVertex3fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fNormal3fVertex3fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord2fNormal3fVertex3fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

value glstub_glTexCoord2fNormal3fVertex3fvSUN(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glTexCoord2fNormal3fVertex3fvSUN(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fVertex3fSUN(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glTexCoord2fVertex3fSUN(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fVertex3fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glTexCoord2fVertex3fvSUN(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glTexCoord2fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2hNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	 glTexCoord2hNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glTexCoord2hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glTexCoord2i(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glTexCoord2iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glTexCoord2s(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord2sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glTexCoord2sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glTexCoord3d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glTexCoord3dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glTexCoord3f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glTexCoord3fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glTexCoord3hNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glTexCoord3hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glTexCoord3i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glTexCoord3iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glTexCoord3s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glTexCoord3sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glTexCoord4d(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glTexCoord4dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glTexCoord4f(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glTexCoord4fColor4fNormal3fVertex4fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11, lv12, lv13, lv14);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4fColor4fNormal3fVertex4fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord4fColor4fNormal3fVertex4fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14]);
}

value glstub_glTexCoord4fColor4fNormal3fVertex4fvSUN(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glTexCoord4fColor4fNormal3fVertex4fvSUN(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

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
	 glTexCoord4fVertex4fSUN(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4fVertex4fSUN_byte(value * argv, int n)
{
	return glstub_glTexCoord4fVertex4fSUN(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

value glstub_glTexCoord4fVertex4fvSUN(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat* lv0 = Data_bigarray_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glTexCoord4fVertex4fvSUN(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glTexCoord4fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	 glTexCoord4hNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glTexCoord4hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glTexCoord4i(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glTexCoord4iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glTexCoord4s(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoord4sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glTexCoord4sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoordPointer(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glTexCoordPointer(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoordPointerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glTexCoordPointerEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoordPointerListIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLint lv4 = Int_val(v4);
	 glTexCoordPointerListIBM(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glTexCoordPointervINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glTexCoordPointervINTEL(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexEnvf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glTexEnvf(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexEnvfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glTexEnvfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexEnvi(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glTexEnvi(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexEnviv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glTexEnviv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexFilterFuncSGIS(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glTexFilterFuncSGIS(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glTexGend(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glTexGend(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexGendv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glTexGendv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexGenf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glTexGenf(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexGenfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glTexGenfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexGeni(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glTexGeni(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexGeniv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glTexGeniv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glTexImage1D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage1D_byte(value * argv, int n)
{
	return glstub_glTexImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

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
	 glTexImage2D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage2D_byte(value * argv, int n)
{
	return glstub_glTexImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glTexImage3D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage3D_byte(value * argv, int n)
{
	return glstub_glTexImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

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
	 glTexImage3DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage3DEXT_byte(value * argv, int n)
{
	return glstub_glTexImage3DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
}

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
	 glTexImage4DSGIS(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glTexImage4DSGIS_byte(value * argv, int n)
{
	return glstub_glTexImage4DSGIS(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

value glstub_glTexParameterIivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glTexParameterIivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexParameterIuivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glTexParameterIuivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexParameterf(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glTexParameterf(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexParameterfv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glTexParameterfv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexParameteri(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glTexParameteri(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexParameteriv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glTexParameteriv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexScissorFuncINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	 glTexScissorFuncINTEL(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTexScissorINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLclampf lv1 = Double_val(v1);
	GLclampf lv2 = Double_val(v2);
	 glTexScissorINTEL(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

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
	 glTexSubImage1D(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage1D_byte(value * argv, int n)
{
	return glstub_glTexSubImage1D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glTexSubImage1DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage1DEXT_byte(value * argv, int n)
{
	return glstub_glTexSubImage1DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

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
	 glTexSubImage2D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage2D_byte(value * argv, int n)
{
	return glstub_glTexSubImage2D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glTexSubImage2DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage2DEXT_byte(value * argv, int n)
{
	return glstub_glTexSubImage2DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

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
	 glTexSubImage3D(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage3D_byte(value * argv, int n)
{
	return glstub_glTexSubImage3D(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

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
	 glTexSubImage3DEXT(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage3DEXT_byte(value * argv, int n)
{
	return glstub_glTexSubImage3DEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);
}

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
	 glTexSubImage4DSGIS(lv0, lv1, lv2, lv3, lv4, lv5, lv6, lv7, lv8, lv9, lv10, lv11, lv12);
	CAMLreturn(Val_unit);
}

value glstub_glTexSubImage4DSGIS_byte(value * argv, int n)
{
	return glstub_glTexSubImage4DSGIS(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11], argv[12]);
}

value glstub_glTextureFogSGIX(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glTextureFogSGIX(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTextureLightEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glTextureLightEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTextureMaterialEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	 glTextureMaterialEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glTextureNormalEXT(value v0)
{
	CAMLparam1(v0);
	GLenum lv0 = Int_val(v0);
	 glTextureNormalEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glTextureRangeAPPLE(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLvoid* lv2 = (Is_long(v2) ? (GLvoid*)Long_val(v2) : ((Tag_val(v2) == String_tag)? (String_val(v2)) : (Data_bigarray_val(v2))));
	 glTextureRangeAPPLE(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTrackMatrixNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLenum lv3 = Int_val(v3);
	 glTrackMatrixNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glTransformFeedbackAttribsNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	GLenum lv2 = Int_val(v2);
	 glTransformFeedbackAttribsNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTransformFeedbackVaryingsNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	GLenum lv3 = Int_val(v3);
	 glTransformFeedbackVaryingsNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glTranslated(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glTranslated(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glTranslatef(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glTranslatef(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glUniform1f(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1fARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glUniform1fARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1fv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glUniform1fv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glUniform1fvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glUniform1i(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1iARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glUniform1iARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1iv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glUniform1iv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1ivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glUniform1ivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1uiEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glUniform1uiEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glUniform1uivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glUniform1uivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glUniform2f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2fARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glUniform2fARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2fv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glUniform2fv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glUniform2fvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glUniform2i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2iARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glUniform2iARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2iv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glUniform2iv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2ivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glUniform2ivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2uiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glUniform2uiEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform2uivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glUniform2uivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glUniform3f(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3fARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glUniform3fARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3fv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glUniform3fv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glUniform3fvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glUniform3i(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3iARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glUniform3iARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3iv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glUniform3iv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3ivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glUniform3ivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3uiEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	 glUniform3uiEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniform3uivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glUniform3uivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4f(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glUniform4f(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4fARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glUniform4fARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4fv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glUniform4fv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4fvARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glUniform4fvARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4i(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glUniform4i(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4iARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glUniform4iARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4iv(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glUniform4iv(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4ivARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLint* lv2 = Data_bigarray_val(v2);
	 glUniform4ivARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4uiEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	 glUniform4uiEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glUniform4uivEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLuint* lv2 = Data_bigarray_val(v2);
	 glUniform4uivEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniformBufferEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glUniformBufferEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix2fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix2fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix2fvARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix2fvARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix2x3fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix2x3fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix2x4fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix2x4fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix3fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix3fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix3fvARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix3fvARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix3x2fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix3x2fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix3x4fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix3x4fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix4fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix4fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix4fvARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix4fvARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix4x2fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix4x2fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUniformMatrix4x3fv(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLboolean lv2 = Bool_val(v2);
	GLfloat* lv3 = Data_bigarray_val(v3);
	 glUniformMatrix4x3fv(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glUnlockArraysEXT(value v0)
{
	CAMLparam1(v0);
	 glUnlockArraysEXT();
	CAMLreturn(Val_unit);
}

value glstub_glUnmapBuffer(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glUnmapBuffer(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glUnmapBufferARB(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLenum lv0 = Int_val(v0);
	GLboolean ret;
	ret =  glUnmapBufferARB(lv0);
	result = Val_bool(ret);
	CAMLreturn(result);
}

value glstub_glUnmapObjectBufferATI(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glUnmapObjectBufferATI(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glUpdateObjectBufferATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	GLenum lv4 = Int_val(v4);
	 glUpdateObjectBufferATI(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glUseProgram(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glUseProgram(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glUseProgramObjectARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glUseProgramObjectARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glValidateProgram(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glValidateProgram(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glValidateProgramARB(value v0)
{
	CAMLparam1(v0);
	GLuint lv0 = Int_val(v0);
	 glValidateProgramARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVariantArrayObjectATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	 glVariantArrayObjectATI(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVariantPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glVariantPointerEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVariantbvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	 glVariantbvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVariantdvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVariantdvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVariantfvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVariantfvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVariantivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVariantivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVariantsvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVariantsvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVariantubvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glVariantubvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVariantuivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVariantuivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVariantusvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVariantusvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glVertex2d(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glVertex2dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glVertex2f(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glVertex2fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2hNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	 glVertex2hNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glVertex2hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glVertex2i(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glVertex2iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glVertex2s(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertex2sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glVertex2sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glVertex3d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glVertex3dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glVertex3f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glVertex3fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glVertex3hNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glVertex3hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glVertex3i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glVertex3iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glVertex3s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertex3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glVertex3sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glVertex4d(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glVertex4dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glVertex4f(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glVertex4fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLushort lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	 glVertex4hNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4hvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glVertex4hvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4i(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glVertex4i(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glVertex4iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glVertex4s(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertex4sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glVertex4sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertexArrayParameteriAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glVertexArrayParameteriAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexArrayRangeAPPLE(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	 glVertexArrayRangeAPPLE(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexArrayRangeNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLsizei lv0 = Int_val(v0);
	GLvoid* lv1 = (Is_long(v1) ? (GLvoid*)Long_val(v1) : ((Tag_val(v1) == String_tag)? (String_val(v1)) : (Data_bigarray_val(v1))));
	 glVertexArrayRangeNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glVertexAttrib1d(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1dARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glVertexAttrib1dARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1dNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glVertexAttrib1dNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib1dv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib1dvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1dvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib1dvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glVertexAttrib1f(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1fARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glVertexAttrib1fARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1fNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glVertexAttrib1fNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib1fv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib1fvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1fvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib1fvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1hNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	 glVertexAttrib1hNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib1hvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glVertexAttrib1s(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1sARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glVertexAttrib1sARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1sNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glVertexAttrib1sNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib1sv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib1svARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib1svNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib1svNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glVertexAttrib2d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2dARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glVertexAttrib2dARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2dNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glVertexAttrib2dNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib2dv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib2dvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2dvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib2dvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glVertexAttrib2f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2fARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glVertexAttrib2fARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2fNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glVertexAttrib2fNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib2fv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib2fvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2fvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib2fvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2hNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	 glVertexAttrib2hNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib2hvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glVertexAttrib2s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2sARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glVertexAttrib2sARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2sNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glVertexAttrib2sNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib2sv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib2svARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib2svNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib2svNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3d(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glVertexAttrib3d(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3dARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glVertexAttrib3dARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3dNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glVertexAttrib3dNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib3dv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib3dvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3dvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib3dvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3f(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glVertexAttrib3f(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3fARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glVertexAttrib3fARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3fNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glVertexAttrib3fNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib3fv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib3fvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3fvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib3fvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3hNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	 glVertexAttrib3hNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib3hvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3s(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glVertexAttrib3s(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3sARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glVertexAttrib3sARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3sNV(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glVertexAttrib3sNV(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib3sv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib3svARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib3svNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib3svNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4Nbv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4Nbv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4NbvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4NbvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4Niv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4Niv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4NivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4NivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4Nsv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4Nsv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4NsvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4NsvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4Nub(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLubyte lv4 = Int_val(v4);
	 glVertexAttrib4Nub(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4NubARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLubyte lv4 = Int_val(v4);
	 glVertexAttrib4NubARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4Nubv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4Nubv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4NubvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4NubvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4Nuiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4Nuiv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4NuivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4NuivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4Nusv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4Nusv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4NusvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4NusvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4bv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4bv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4bvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4bvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4d(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	 glVertexAttrib4d(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4dARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	 glVertexAttrib4dARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4dNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	 glVertexAttrib4dNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4dv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib4dv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4dvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib4dvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4dvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexAttrib4dvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4f(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glVertexAttrib4f(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4fARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glVertexAttrib4fARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4fNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glVertexAttrib4fNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4fv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4fv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4fvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4fvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4fvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4fvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4hNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLushort lv1 = Int_val(v1);
	GLushort lv2 = Int_val(v2);
	GLushort lv3 = Int_val(v3);
	GLushort lv4 = Int_val(v4);
	 glVertexAttrib4hNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4hvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4hvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4iv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4iv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4ivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4ivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4s(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	 glVertexAttrib4s(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4sARB(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	 glVertexAttrib4sARB(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4sNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	 glVertexAttrib4sNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4sv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4sv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4svARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4svARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4svNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4svNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4ubNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLubyte lv1 = Int_val(v1);
	GLubyte lv2 = Int_val(v2);
	GLubyte lv3 = Int_val(v3);
	GLubyte lv4 = Int_val(v4);
	 glVertexAttrib4ubNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4ubv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4ubv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4ubvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4ubvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4ubvNV(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4ubvNV(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4uiv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4uiv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4uivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4uivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4usv(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4usv(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttrib4usvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttrib4usvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

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
	 glVertexAttribArrayObjectATI(lv0, lv1, lv2, lv3, lv4, lv5, lv6);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribArrayObjectATI_byte(value * argv, int n)
{
	return glstub_glVertexAttribArrayObjectATI(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value glstub_glVertexAttribI1iEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glVertexAttribI1iEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI1ivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI1ivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI1uiEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	 glVertexAttribI1uiEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI1uivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI1uivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI2iEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glVertexAttribI2iEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI2ivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI2ivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI2uiEXT(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	 glVertexAttribI2uiEXT(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI2uivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI2uivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI3iEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glVertexAttribI3iEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI3ivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI3ivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI3uiEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	 glVertexAttribI3uiEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI3uivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI3uivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI4bvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI4bvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI4iEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glVertexAttribI4iEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI4ivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI4ivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI4svEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI4svEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI4ubvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI4ubvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI4uiEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLuint lv1 = Int_val(v1);
	GLuint lv2 = Int_val(v2);
	GLuint lv3 = Int_val(v3);
	GLuint lv4 = Int_val(v4);
	 glVertexAttribI4uiEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI4uivEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI4uivEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribI4usvEXT(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLuint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glVertexAttribI4usvEXT(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribIPointerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glVertexAttribIPointerEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

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
	 glVertexAttribPointer(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribPointer_byte(value * argv, int n)
{
	return glstub_glVertexAttribPointer(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

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
	 glVertexAttribPointerARB(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribPointerARB_byte(value * argv, int n)
{
	return glstub_glVertexAttribPointerARB(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glVertexAttribPointerNV(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLuint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLenum lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glVertexAttribPointerNV(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs1dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glVertexAttribs1dvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs1fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs1fvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs1hvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs1hvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs1svNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLshort* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs1svNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs2dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glVertexAttribs2dvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs2fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs2fvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs2hvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs2hvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs2svNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLshort* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs2svNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs3dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glVertexAttribs3dvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs3fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs3fvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs3hvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs3hvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs3svNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLshort* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs3svNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs4dvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLdouble* lv2 = (Tag_val(v2) == Double_array_tag)? (double *)v2: Data_bigarray_val(v2);
	 glVertexAttribs4dvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs4fvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLfloat* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs4fvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs4hvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLushort* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs4hvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs4svNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLshort* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs4svNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexAttribs4ubvNV(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLuint lv0 = Int_val(v0);
	GLsizei lv1 = Int_val(v1);
	GLubyte* lv2 = Data_bigarray_val(v2);
	 glVertexAttribs4ubvNV(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexBlendARB(value v0)
{
	CAMLparam1(v0);
	GLint lv0 = Int_val(v0);
	 glVertexBlendARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertexBlendEnvfATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glVertexBlendEnvfATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexBlendEnviATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glVertexBlendEnviATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexPointer(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glVertexPointer(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexPointerEXT(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	GLvoid* lv4 = (Is_long(v4) ? (GLvoid*)Long_val(v4) : ((Tag_val(v4) == String_tag)? (String_val(v4)) : (Data_bigarray_val(v4))));
	 glVertexPointerEXT(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexPointerListIBM(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLvoid** lv3 = Data_bigarray_val(v3);
	GLint lv4 = Int_val(v4);
	 glVertexPointerListIBM(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexPointervINTEL(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLvoid** lv2 = Data_bigarray_val(v2);
	 glVertexPointervINTEL(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream2dATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glVertexStream2dATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream2dvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexStream2dvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream2fATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glVertexStream2fATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream2fvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexStream2fvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream2iATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glVertexStream2iATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream2ivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexStream2ivATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream2sATI(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glVertexStream2sATI(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream2svATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexStream2svATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream3dATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glVertexStream3dATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream3dvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexStream3dvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream3fATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glVertexStream3fATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream3fvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexStream3fvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream3iATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glVertexStream3iATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream3ivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexStream3ivATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream3sATI(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glVertexStream3sATI(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream3svATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexStream3svATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream4dATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	GLdouble lv4 = Double_val(v4);
	 glVertexStream4dATI(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream4dvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glVertexStream4dvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream4fATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	GLfloat lv4 = Double_val(v4);
	 glVertexStream4fATI(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream4fvATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glVertexStream4fvATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream4iATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	GLint lv4 = Int_val(v4);
	 glVertexStream4iATI(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream4ivATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glVertexStream4ivATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream4sATI(value v0, value v1, value v2, value v3, value v4)
{
	CAMLparam5(v0, v1, v2, v3, v4);
	GLenum lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	GLshort lv4 = Int_val(v4);
	 glVertexStream4sATI(lv0, lv1, lv2, lv3, lv4);
	CAMLreturn(Val_unit);
}

value glstub_glVertexStream4svATI(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLenum lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glVertexStream4svATI(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glVertexWeightPointerEXT(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glVertexWeightPointerEXT(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glVertexWeightfEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat lv0 = Double_val(v0);
	 glVertexWeightfEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertexWeightfvEXT(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glVertexWeightfvEXT(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertexWeighthNV(value v0)
{
	CAMLparam1(v0);
	GLushort lv0 = Int_val(v0);
	 glVertexWeighthNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glVertexWeighthvNV(value v0)
{
	CAMLparam1(v0);
	GLushort* lv0 = Data_bigarray_val(v0);
	 glVertexWeighthvNV(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glViewport(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLsizei lv3 = Int_val(v3);
	 glViewport(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glWeightPointerARB(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLenum lv1 = Int_val(v1);
	GLsizei lv2 = Int_val(v2);
	GLvoid* lv3 = (Is_long(v3) ? (GLvoid*)Long_val(v3) : ((Tag_val(v3) == String_tag)? (String_val(v3)) : (Data_bigarray_val(v3))));
	 glWeightPointerARB(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glWeightbvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLbyte* lv1 = Data_bigarray_val(v1);
	 glWeightbvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWeightdvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLdouble* lv1 = (Tag_val(v1) == Double_array_tag)? (double *)v1: Data_bigarray_val(v1);
	 glWeightdvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWeightfvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLfloat* lv1 = Data_bigarray_val(v1);
	 glWeightfvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWeightivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint* lv1 = Data_bigarray_val(v1);
	 glWeightivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWeightsvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLshort* lv1 = Data_bigarray_val(v1);
	 glWeightsvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWeightubvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLubyte* lv1 = Data_bigarray_val(v1);
	 glWeightubvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWeightuivARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLuint* lv1 = Data_bigarray_val(v1);
	 glWeightuivARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWeightusvARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLushort* lv1 = Data_bigarray_val(v1);
	 glWeightusvARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2d(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glWindowPos2d(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2dARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glWindowPos2dARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2dMESA(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	 glWindowPos2dMESA(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glWindowPos2dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2dvARB(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glWindowPos2dvARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2dvMESA(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glWindowPos2dvMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2f(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glWindowPos2f(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2fARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glWindowPos2fARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2fMESA(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	 glWindowPos2fMESA(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glWindowPos2fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2fvARB(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glWindowPos2fvARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2fvMESA(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glWindowPos2fvMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2i(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glWindowPos2i(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2iARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glWindowPos2iARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2iMESA(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	 glWindowPos2iMESA(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glWindowPos2iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2ivARB(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glWindowPos2ivARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2ivMESA(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glWindowPos2ivMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2s(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glWindowPos2s(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2sARB(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glWindowPos2sARB(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2sMESA(value v0, value v1)
{
	CAMLparam2(v0, v1);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	 glWindowPos2sMESA(lv0, lv1);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glWindowPos2sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2svARB(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glWindowPos2svARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos2svMESA(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glWindowPos2svMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3d(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glWindowPos3d(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3dARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glWindowPos3dARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3dMESA(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	 glWindowPos3dMESA(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3dv(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glWindowPos3dv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3dvARB(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glWindowPos3dvARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3dvMESA(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glWindowPos3dvMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3f(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glWindowPos3f(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3fARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glWindowPos3fARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3fMESA(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	 glWindowPos3fMESA(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3fv(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glWindowPos3fv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3fvARB(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glWindowPos3fvARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3fvMESA(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glWindowPos3fvMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3i(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glWindowPos3i(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3iARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glWindowPos3iARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3iMESA(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	 glWindowPos3iMESA(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3iv(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glWindowPos3iv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3ivARB(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glWindowPos3ivARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3ivMESA(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glWindowPos3ivMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3s(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glWindowPos3s(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3sARB(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glWindowPos3sARB(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3sMESA(value v0, value v1, value v2)
{
	CAMLparam3(v0, v1, v2);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	 glWindowPos3sMESA(lv0, lv1, lv2);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3sv(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glWindowPos3sv(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3svARB(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glWindowPos3svARB(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos3svMESA(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glWindowPos3svMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos4dMESA(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLdouble lv0 = Double_val(v0);
	GLdouble lv1 = Double_val(v1);
	GLdouble lv2 = Double_val(v2);
	GLdouble lv3 = Double_val(v3);
	 glWindowPos4dMESA(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos4dvMESA(value v0)
{
	CAMLparam1(v0);
	GLdouble* lv0 = (Tag_val(v0) == Double_array_tag)? (double *)v0: Data_bigarray_val(v0);
	 glWindowPos4dvMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos4fMESA(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLfloat lv0 = Double_val(v0);
	GLfloat lv1 = Double_val(v1);
	GLfloat lv2 = Double_val(v2);
	GLfloat lv3 = Double_val(v3);
	 glWindowPos4fMESA(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos4fvMESA(value v0)
{
	CAMLparam1(v0);
	GLfloat* lv0 = Data_bigarray_val(v0);
	 glWindowPos4fvMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos4iMESA(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLint lv0 = Int_val(v0);
	GLint lv1 = Int_val(v1);
	GLint lv2 = Int_val(v2);
	GLint lv3 = Int_val(v3);
	 glWindowPos4iMESA(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos4ivMESA(value v0)
{
	CAMLparam1(v0);
	GLint* lv0 = Data_bigarray_val(v0);
	 glWindowPos4ivMESA(lv0);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos4sMESA(value v0, value v1, value v2, value v3)
{
	CAMLparam4(v0, v1, v2, v3);
	GLshort lv0 = Int_val(v0);
	GLshort lv1 = Int_val(v1);
	GLshort lv2 = Int_val(v2);
	GLshort lv3 = Int_val(v3);
	 glWindowPos4sMESA(lv0, lv1, lv2, lv3);
	CAMLreturn(Val_unit);
}

value glstub_glWindowPos4svMESA(value v0)
{
	CAMLparam1(v0);
	GLshort* lv0 = Data_bigarray_val(v0);
	 glWindowPos4svMESA(lv0);
	CAMLreturn(Val_unit);
}

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
	 glWriteMaskEXT(lv0, lv1, lv2, lv3, lv4, lv5);
	CAMLreturn(Val_unit);
}

value glstub_glWriteMaskEXT_byte(value * argv, int n)
{
	return glstub_glWriteMaskEXT(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

value glstub_glewInit(value v0)
{
	CAMLparam1(v0);
	CAMLlocal1(result);
	GLint ret;
	ret =  glewInit();
	result = Val_int(ret);
	CAMLreturn(result);
}

