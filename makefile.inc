LIBDIR=lib
SRCDIR=examples
BINDIR=bin
LIBS=unix bigarray
GL_SOURCE=$(LIBDIR)/glcaml_stub.c $(LIBDIR)/glcaml.mli $(LIBDIR)/glcaml.ml

ifdef WIN32
TARGET=i686-pc-mingw32 # msvc?
else
TARGET=$(shell gcc -dumpmachine)
endif

CFLAGS=-Wall -W -Wno-unused-parameter

ifeq ($(LOADER),glew)
CFLAGS+=-DUSE_GLEW
CLIBS=GLEW
else
ifeq ($(LOADER),dynamic)
CFLAGS+=-DUSE_DYNAMIC -DUSE_DYNAMIC_EXT # all dynamic
else
ifeq ($(LOADER),static)
# all static
else
CFLAGS+=-DUSE_DYNAMIC_EXT # mixed mode
endif
endif
endif

ifdef NOSDL
LIBS+=graphics
WIN_SOURCE=$(LIBDIR)/win_stub.c $(LIBDIR)/win.mli $(LIBDIR)/win.ml
ifneq ($(findstring mingw32,$(TARGET)),)
CLIBS+=opengl32 gdi32
else
CLIBS+=GL
ifneq ($(findstring darwin,$(TARGET)),)
CFLAGS+=-D__unix__ -isystem /usr/X11/include
endif
endif
else
CLIBS+=SDL
ifneq ($(findstring darwin,$(TARGET)),)
CLIBS+=SDLmain
OCAMLLDFLAGS+=-ccopt -framework -ccopt Cocoa -ccopt -framework -ccopt OpenGL
endif
SDL_SOURCE=$(LIBDIR)/sdl_stub.c $(LIBDIR)/sdl.mli $(LIBDIR)/sdl.ml
ifndef NOSDLMIXER
CLIBS+=SDL_mixer
SDL_SOURCE+=$(LIBDIR)/sdl_mixer_stub.c $(LIBDIR)/sdl_mixer.mli $(LIBDIR)/sdl_mixer.ml
endif
endif

EXAMPLE=$(SRCDIR)/$(MLFILE).ml
CC=gcc
SOURCES=$(WIN_SOURCE) $(SDL_SOURCE) $(GL_SOURCE) $(EXAMPLE)
RESULT=$(BINDIR)/$(MLFILE)
-include OCamlMakefile

# vim: set syn=make :
