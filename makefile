MAKE=make

.PHONY: all nosdl sdl sdlmixer sdlttf clean htmldoc

# Uncomment the following line if use glew
# export GLEW=true

ALLTARGETS=sdl sdlmixer sdlttf
ifeq ($(GLEW),)
ALLTARGETS+=nosdl
endif

all: build/glcaml.cma $(ALLTARGETS)

build/glcaml.cma:
	make -C lib -f makefile install DESTDIR=$(abspath build)

ifeq ($(GLEW),)
nosdl:
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=accum
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=prim
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=camera
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=checker
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=shader
endif

sdl:
	$(MAKE) -f makefile.inc MLFILE=audiopan
	$(MAKE) -f makefile.inc MLFILE=audiopitch
	$(MAKE) -f makefile.inc MLFILE=audiopitchpan
	$(MAKE) -f makefile.inc MLFILE=audiosample
	$(MAKE) -f makefile.inc MLFILE=events
	$(MAKE) -f makefile.inc MLFILE=foolesson2
	$(MAKE) -f makefile.inc MLFILE=foolesson4
	$(MAKE) -f makefile.inc MLFILE=foolesson5
	$(MAKE) -f makefile.inc MLFILE=foolesson6
	$(MAKE) -f makefile.inc MLFILE=foolesson8
	$(MAKE) -f makefile.inc MLFILE=lesson02
	$(MAKE) -f makefile.inc MLFILE=lesson03
	$(MAKE) -f makefile.inc MLFILE=lesson04
	$(MAKE) -f makefile.inc MLFILE=lesson05
	$(MAKE) -f makefile.inc MLFILE=lesson06
	$(MAKE) -f makefile.inc MLFILE=lesson07
	$(MAKE) -f makefile.inc MLFILE=lesson08
	$(MAKE) -f makefile.inc MLFILE=lesson09

sdlmixer: 
	$(MAKE) -f makefile.inc MLFILE=mixer

sdlttf:
	$(MAKE) -f makefile.inc MLFILE=test_ttf

clean:
	# nosdl
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=accum clean
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=prim clean
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=camera clean
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=checker clean
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=shader clean
	# sdl
	$(MAKE) -f makefile.inc MLFILE=audiopan clean
	$(MAKE) -f makefile.inc MLFILE=audiopitch clean
	$(MAKE) -f makefile.inc MLFILE=audiopitchpan clean
	$(MAKE) -f makefile.inc MLFILE=audiosample clean
	$(MAKE) -f makefile.inc MLFILE=events clean
	$(MAKE) -f makefile.inc MLFILE=foolesson2 clean
	$(MAKE) -f makefile.inc MLFILE=foolesson4 clean
	$(MAKE) -f makefile.inc MLFILE=foolesson5 clean
	$(MAKE) -f makefile.inc MLFILE=foolesson6  clean
	$(MAKE) -f makefile.inc MLFILE=foolesson8 clean
	$(MAKE) -f makefile.inc MLFILE=lesson02 clean
	$(MAKE) -f makefile.inc MLFILE=lesson03 clean
	$(MAKE) -f makefile.inc MLFILE=lesson04 clean
	$(MAKE) -f makefile.inc MLFILE=lesson05 clean
	$(MAKE) -f makefile.inc MLFILE=lesson06 clean
	$(MAKE) -f makefile.inc MLFILE=lesson07 clean
	$(MAKE) -f makefile.inc MLFILE=lesson08 clean
	$(MAKE) -f makefile.inc MLFILE=lesson09 clean
	# mixer
	$(MAKE) -f makefile.inc MLFILE=mixer clean
	# ttf
	$(MAKE) -f makefile.inc MLFILE=test_ttf clean
	# libs
	make -C lib -f makefile clean uninstall DESTDIR=$(abspath build)
	-rmdir build/stublibs
	-rmdir build

htmldoc:
	ocamldoc -v -I lib -html lib/sdl.mli lib/glcaml.mli lib/win.mli lib/sdl_mixer.mli -d doc
