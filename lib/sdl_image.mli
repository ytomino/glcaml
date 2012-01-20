(* Objective Caml interface for SDL_image with SDLCaml *)
(* based on SDL_image.h 1.2.11 *)

open Sdl;;

(* This function gets the version of the dynamically linked SDL_image library.
   it should NOT be used to fill a version structure, instead you should
   use the SDL_IMAGE_VERSION() macro. *)
val linked_version: unit -> int * int * int;;

type init_flags = INIT_JPG | INIT_PNG | INIT_TIF | INIT_WEBP;;

(* Loads dynamic libraries and prepares them for use.  Flags should be
   one or more flags from IMG_InitFlags OR'd together.
   It returns the flags successfully initialized, or 0 on failure. *)
val init: init_flags list -> unit;;

(* Unloads libraries loaded with IMG_Init *)
val quit: unit -> unit;;

(* Load an image from an SDL data source.
   The 'type' may be one of: "BMP", "GIF", "PNG", etc.

   If the image format supports a transparent pixel, SDL will set the
   colorkey for the surface.  You can enable RLE acceleration on the
   surface afterwards by calling:
        SDL_SetColorKey(image, SDL_RLEACCEL, image->format->colorkey); *)
(* val load_typed_rw: src: rwops -> freesrc: int -> image_type: string -> Video.surface;; *)
(* Convenience functions *)
val load: file: string -> Video.surface;;
(* val load_rw: src: rwops -> freesrc: int -> Video.surface;; *)

(* Invert the alpha of a surface for use with OpenGL
   This function is now a no-op, and only provided for backwards compatibility. *)
(* val invert_alpha: bool -> unit;; *)

(* Functions to detect a file type, given a seekable source *)
(* val is_ico: src: rwops -> bool;;
   val is_cur: src: rwops -> bool;;
   val is_bmp: src: rwops -> bool;;
   val is_gif: src: rwops -> bool;;
   val is_jpg: src: rwops -> bool;;
   val is_lbm: src: rwops -> bool;;
   val is_pcx: src: rwops -> bool;;
   val is_png: src: rwops -> bool;;
   val is_pnm: src: rwops -> bool;;
   val is_tif: src: rwops -> bool;;
   val is_xcf: src: rwops -> bool;;
   val is_xpm: src: rwops -> bool;;
   val is_xv: src: rwops -> bool;;
   val is_webp: src: rwops -> bool;; *)

(* Individual loading functions *)
(* val load_ico_rw: src: rwops -> Video.surface;;
   val load_cur_rw: src: rwops -> Video.surface;;
   val load_bmp_rw: src: rwops -> Video.surface;;
   val load_gif_rw: src: rwops -> Video.surface;;
   val load_jpg_rw: src: rwops -> Video.surface;;
   val load_lbm_rw: src: rwops -> Video.surface;;
   val load_pcx_rw: src: rwops -> Video.surface;;
   val load_png_rw: src: rwops -> Video.surface;;
   val load_pnm_rw: src: rwops -> Video.surface;;
   val load_tga_rw: src: rwops -> Video.surface;;
   val load_tif_rw: src: rwops -> Video.surface;;
   val load_xcf_rw: src: rwops -> Video.surface;;
   val load_xpm_rw: src: rwops -> Video.surface;;
   val load_xv_rw: src: rwops -> Video.surface;;
   val load_webp_rw: src: rwops -> Video.surface;; *)

val read_xpm_from_array: xpm: string array -> Video.surface;;
