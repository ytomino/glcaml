MAKE=make
# Uncomment the following line on WIN32
# MAKE=make WIN32=true

all: sdl nosdl

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

nosdl:	
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=accum
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=prim
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=camera
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=checker
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=shader
	
clean:
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
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=accum clean
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=prim clean
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=camera clean
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=checker clean
	$(MAKE) -f makefile.inc NOSDL=true MLFILE=shader clean

htmldoc:
	ocamldoc -html lib/sdl.mli lib/glcaml.mli lib/win.mli -d doc
