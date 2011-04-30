About
-----

This is my fork of glcaml / sdlcaml interfaces, with the intent to
provide a more complete sdl experience as well as bring some github
collaboration and transparency to the development process. I don't like
sourceforge too much.

Currently it improves SDLCaml by providing Sdl_mixer, interface to
audio mixing and playing features of SDL.

I don't plan on doing any "official" releases and won't sweat at providing
backwards compatibility, OCaml is enough of a minority and novelty to
worry about some legacy application breakage.

Still, it is currently fully compatible with the mainline glcaml/sdlcaml.


Contacts
--------

Einar Lielmanis, einars@gmail.com


ytomino version
---------------

I agree Einar's opinion.

- adding simple makefile instead of OCamlMakefile (for Windows and OSX)
- adding cursor and joystick support
- adding SDL_image support
  (including Sdl_image_savepng module to take a screen capture as .png file)
- adding SDL_ttf support
- adding another version SDL_mixer support instead of Einar's
