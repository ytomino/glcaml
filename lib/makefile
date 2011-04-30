.PHONY: all clean install uninstall

all clean install uninstall:
	echo "**** glcaml ****"
	make -f makefile-glcaml $@
ifneq ($(OCAMLC),gcamlc)
	echo "**** glwin ****"
	make -f makefile-glwin $@
endif
	echo "**** SDL ****"
	make -f makefile-sdl $@
	echo "**** SDL_mixer ****"
	make -f makefile-sdl_mixer $@
