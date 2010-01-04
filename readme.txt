		GLCAML (http://glcaml.sourceforge.net)

About
--------
GLCaml is an Objective Caml interface for OpenGL versions 1.1, 1.2, 1.3, 1.4, 1.5, 
2.0 and 2.1, plus extensions. It consists of three files: glcaml.ml, glcaml.mli 
and glcaml_stub.c, and is intended as a compact drop-in binding rather than a big 
standalone library. 

Platforms
-----------
GLCaml has been tested on the following platforms
1. Windows XP, with the MinGW distribution of the Ocaml compiler
2. Windows 2000, with the MinGW distribution of the Ocaml compiler
3. Ubuntu Linux (6.06), with the AMD64 version of the Ocaml compiler
4. Mac OS X
5. Solaris 5.10

It should work, but has not been tested on
1. Windows 2000/XP/Vista with the MSVC distribution of the Ocaml compiler
2. Other Linux distributions
3. FreeBSD

Copyright and License
----------------------
GLCaml is copyright (c) 2008 Elliott Oti (http://www.elliottoti.com)
It is licensed under the BSD license (see licence.txt)

Disclaimer
-----------
ALL SOFTWARE AND INFORMATION PERTAINING TO GLCAML, SDLCAML AND WIN IS PROVIDED "AS IS" WITHOUT 
WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND FREEDOM 
FROM INFRINGEMENT.

Current Version
-------------------
The current version is 20080215, created on 15 february 2008

Installation
-------------
See the file install.txt, provided along with this distribution.

Changes
----------
This version of GLCaml has major API changes with respect to the previous versions.
The following changes have been made:

1. Bigarrays are no longer necessary for using OpenGL functions. Standard Ocaml
types (ints, floats, bools and strings) are now used.

2. Enumerated constants (glenums) have been replaced by ints. As a result, there
are no more GL_ALL_CAPS constants; these have been replaced by gl_no_caps ints

3. An exception is now always thrown if an OpenGL call is not available. This is
because silent fails can leave mutable parameters in an undefined state.

GLCaml
--------
The bindings are generated with the file convert.ml using cleaned up header files 
from the glext project on Sourceforge (http://glext.sourceforge.net). 
GLCaml is a direct, not particularly type-safe binding to OpenGL. 
It has the following features:

    * Inspired by camlgl.sourceforge.net, GLCaml loads the OpenGL library dynamically 
    ("OpenGL32.dll" on windows, "libGL.so.1" on Linux, "libGL.dylib" on OS-X)
    * OpenGL functions are loaded dynamically and memoized, once loaded, to 
    speed up future calls.
    * Function names are exactly the same as in the traditional 'C' OpenGL API.
    
This binding is wholly automatically generated and contains hundreds of function 
bindings, the vast majority of which have not been tested. Use at your own risk.

GLCaml can be used in combination with OcamlSDL, the canonical binding for SDL, 
or Jean-Christophe Filliatre's SDL bindings, or with lablgtk's GTKGlArea. Optional 
bindings for SDL are also provided along with the GLCaml package to enable instant 
usage, if so desired. GLCaml can also be used with the Win module, provided in this
package, which enables the use of Ocaml's Graphics module for OpenGL output.

The lablgl OpenGL bindings are typesafe, elegant and portable. However, it only 
covers OpenGL 1.2. In addition, it's statically linked to the OpenGL import library.

Another OpenGL binding for Ocaml is Nickolay Kolchin-Semyonov's camlgl. It extends 
OpenGL support to version 1.5 and loads all functions dynamically. It is however 
unmaintained at the moment.

GLCaml supports all ARB and vendor extensions.

SDLCaml
-----------
This package comes with SDLCaml, a compact drop-in binding for LibSDL.
SDLCaml is licensed under the LGPL (http://www.gnu.org/licenses/lgpl.html), 
as it contains substantial portions of source code derived from an LGPL-licensed library.
SDLCaml can be used as a small, fast replacement for OcamlSDL.	
It contains the following files
	sdlcaml.ml
	sdlcaml.mli
	sdlcaml_stub.c
located in the /lib subdirectory
Generated, comprehensive documentation is located in the /doc directory
The /src directory contains a number of SDL tutorials, translated into
Ocaml from the Lazy Foo' Productions tutorials
(http://lazyfooproductions.com/SDL_tutorials/index.php)
In addition to the SDL bindings, SDLCaml contains the following
convenience functions, all written in OCaml:
    * A TGA file reader, able to read 15,16,24 and 32 bit-per-pixel TGA files, both run-length encoded and uncompressed.
    * Texture-map scaling functions, with a number of different scaling filters.
    * A texture mipmap generator, using the scaling functions to generate mip-maps suitable for OpenGL
    * A bitmapped font library, based on the SFONT specifications

Win
-----
This package also comes with Win, a small library that enables OpenGL
calls to be used from the Ocaml Graphics module, without requiring the presence
of SDL or other third-party package. 
Win is licensed under the BSD licence (see licence.txt)
It contains the following files
	win.ml
	win.mli
	win_stub.c
located in the /lib subdirectory	

