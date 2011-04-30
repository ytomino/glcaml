LIBDIR=lib
SRCDIR=examples
BINDIR=bin
BUILDDIR=build

ifdef NOSDL
# glcaml only
LIBS=graphics unix bigarray glcaml glwin
else
# glcaml + sdlcaml
LIBS=unix bigarray glcaml sdl sdl_mixer
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
	ocamlc -c -I $(BUILDDIR) -o $(CMO) $(EXAMPLE)
	ocamlc -I $(BUILDDIR) -o $@ $(addsuffix .cma,$(LIBS)) $(CMO)

$(OPTEXE): $(EXAMPLE)
	ocamlopt -c -I $(BUILDDIR) -o $(CMX) $(EXAMPLE)
	ocamlopt -I $(BUILDDIR) -o $@ $(addsuffix .cmxa,$(LIBS)) $(CMX)

clean:
	-rm $(BUILDDIR)/$(MLFILE).cmi
	-rm $(CMO) $(BYTEEXE)
	-rm $(CMX) $(BUILDDIR)/$(MLFILE).o $(OPTEXE)
