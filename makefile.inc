LIBDIR=lib
SRCDIR=examples
BINDIR=bin
LIBS=graphics unix bigarray
GL_SOURCE=$(LIBDIR)/glcaml_stub.c $(LIBDIR)/glcaml.mli $(LIBDIR)/glcaml.ml

CLIBS=SDL GLEW
SDL_SOURCE=$(LIBDIR)/sdl_stub.c $(LIBDIR)/sdl.mli $(LIBDIR)/sdl.ml

ifneq ($(findstring darwin,$(shell gcc -dumpmachine)),)
OCAMLLDFLAGS=-ccopt -framework -ccopt Cocoa -ccopt -framework -ccopt OpenGL
CLIBS+=SDLmain
else
CLIBS+=GL
endif

ifdef NOSDLMIXER
CLIBS=SDL GLEW
SDL_SOURCE=$(LIBDIR)/sdl_stub.c $(LIBDIR)/sdl.mli $(LIBDIR)/sdl.ml
endif

ifndef NOSDLMIXER
CLIBS+=SDL_mixer
SDL_SOURCE+=$(LIBDIR)/sdl_mixer_stub.c $(LIBDIR)/sdl_mixer.mli $(LIBDIR)/sdl_mixer.ml
endif

EXAMPLE=$(SRCDIR)/$(MLFILE).ml
CC=gcc
SOURCES=$(WIN_SOURCE) $(SDL_SOURCE) $(GL_SOURCE) $(EXAMPLE)
RESULT=$(BINDIR)/$(MLFILE)
-include OCamlMakefile

# vim: set syn=make :
