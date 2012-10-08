LIBDIR=lib
SRCDIR=examples
BINDIR=bin
BUILDDIR=build

ifdef NOSDL
# glcaml only
LIBS=graphics unix bigarray glcaml glwin
else
# glcaml + sdlcalm
LIBS=unix bigarray glcaml sdl sdl_mixer sdl_ttf
endif

ifdef THREADS
OCAMLCFLAGS=-thread
LIBS:=unix threads $(filter-out unix,$(LIBS))
endif

ifdef NOSDL
OCAMLCFLAGS_BYTE=$(OCAMLCFLAGS)
LIBS_BYTE=$(LIBS)
else # always use threads mode if byte-code and with SDL
OCAMLCFLAGS_BYTE=$(filter-out -thread,$(OCAMLCFLAGS)) -thread
LIBS_BYTE=unix threads $(filter-out unix,$(LIBS))
endif

EXAMPLE=$(SRCDIR)/$(MLFILE).ml

CMO=$(BUILDDIR)/$(MLFILE).cmo
BYTEEXE=$(BINDIR)/$(MLFILE).byte.exe

CMX=$(BUILDDIR)/$(MLFILE).cmx
OPTEXE=$(BINDIR)/$(MLFILE).opt.exe

export CAML_LD_LIBRARY_PATH=$(BUILDDIR)/stublibs

.PHONY: build clean

build: $(BYTEEXE) $(OPTEXE)

$(BYTEEXE): $(EXAMPLE)
	ocamlc -c -I $(BUILDDIR) $(OCAMLCFLAGS_BYTE) -o $(CMO) $(EXAMPLE)
	ocamlc -I $(BUILDDIR) $(OCAMLCFLAGS_BYTE) -o $@ $(addsuffix .cma,$(LIBS_BYTE)) $(CMO)

$(OPTEXE): $(EXAMPLE)
	ocamlopt -c -I $(BUILDDIR) $(OCAMLCFLAGS) -o $(CMX) $(EXAMPLE)
	ocamlopt -I $(BUILDDIR) $(OCAMLCFLAGS) -o $@ $(addsuffix .cmxa,$(LIBS)) $(CMX)

clean:
	-rm $(BUILDDIR)/$(MLFILE).cmi
	-rm $(CMO) $(BYTEEXE)
	-rm $(CMX) $(BUILDDIR)/$(MLFILE).o $(OPTEXE)
