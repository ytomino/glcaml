(* Objective Caml interface for SDL_ttf with SDLCaml *)
(* based on SDL_ttf.h 2.0.11 *)

open Sdl;;

type uint16_array = (int, Bigarray.int16_unsigned_elt, Bigarray.c_layout) Bigarray.Array1.t

(* This function gets the version of the dynamically linked SDL_ttf library.
   it should NOT be used to fill a version structure, instead you should
   use the SDL_TTF_VERSION() macro. *)
val linked_version: unit -> int * int * int;;

(* ZERO WIDTH NO-BREAKSPACE (Unicode byte order mark) *)
val unicode_bom_native: int;;
val unicode_bom_swapped: int;;

(* This function tells the library whether UNICODE text is generally
   byteswapped.  A UNICODE BOM character in a string will override
   this setting for the remainder of that string. *)
val byte_swapped_unicode: swapped: bool -> unit;;

(* The internal structure containing font information *)
type font;;

(* Initialize the TTF engine - returns 0 if successful, -1 on error *)
val init: unit -> unit;;

(* Open a font file and create a font of the specified point size.
 * Some .fon fonts will have several sizes embedded in the file, so the
 * point size becomes the index of choosing which size.  If the value
 * is too high, the last indexed size will be the default. *)
val open_font: file: string -> ptsize: int -> font;;
val open_font_index: file: string -> ptsize: int -> index: int -> font;;
(* val open_font_rw: src: rwops -> int: freesrc -> ptsize: int -> font;; *)
(* val open_font_index_rw: src: rwops -> int: freesrc -> ptsize: int -> index: int -> font;; *)
 
(* Set and retrieve the font style
   This font style is implemented by modifying the font glyphs, and
   doesn't reflect any inherent properties of the truetype font file. *)
type font_style = STYLE_BOLD | STYLE_ITALIC | STYLE_UNDERLINE;;

val get_font_style: font: font -> font_style list;;
val set_font_style: font: font -> (* style: *) font_style list -> unit;;

(* Set and retrieve FreeType hinter settings *)
type hinting = HINTING_NORMAL | HINTING_LIGHT | HINTING_MONO | HINTING_NONE;;

val get_font_hinting: font: font -> hinting;;
val set_font_hinting: font: font -> (* hinting: *) hinting -> unit;;

(* Get the total height of the font - usually equal to point size *)
val font_height: font: font -> int;;

(* Get the offset from the baseline to the top of the font
   This is a positive value, relative to the baseline. *)
val font_ascent: font: font -> int;;

(* Get the offset from the baseline to the bottom of the font
   This is a negative value, relative to the baseline. *)
val font_descent: font: font -> int;;

(* Get the recommended spacing between lines of text for this font *)
val font_line_skip: font: font -> int;;

(* Get/Set whether or not kerning is allowed for this font *)
val get_font_kerning: font: font -> bool;;
val set_font_kerning: font: font -> (* allowed: *) bool -> unit;;

(* Get the number of faces of the font *)
val font_faces: font: font -> int;;

(* Get the font face attributes, if any *)
val font_face_is_fixed_width: font: font -> bool;;
val font_face_family_name: font: font -> string;;
val font_face_style_name: font: font -> string;;

(* Check wether a glyph is provided by the font or not *)
val glyph_is_provided: font: font -> ch: int -> bool;;

(* Get the metrics (dimensions) of a glyph
   To understand what these metrics mean, here is a useful link:
    http://freetype.sourceforge.net/freetype2/docs/tutorial/step2.html *)
val glyph_metrics: font: font -> ch: int -> int * int * int * int * int;;

(* Get the dimensions of a rendered string of text *)
val size_text: font: font -> text: string -> int * int;;
val size_utf8: font: font -> text: string -> int * int;;
val size_unicode: font: font -> text: uint16_array -> int * int;;

(* Create an 8-bit palettized surface and render the given text at
   fast quality with the given font and color.  The 0 pixel is the
   colorkey, giving a transparent background, and the 1 pixel is set
   to the text color.
   This function returns the new surface, or NULL if there was an error. *)
val render_text_solid: font: font -> text: string -> fg: Video.color -> Video.surface;;
val render_utf8_solid: font: font -> text: string -> fg: Video.color -> Video.surface;;
val render_unicode_solid: font: font -> text: uint16_array -> fg: Video.color -> Video.surface;;

(* Create an 8-bit palettized surface and render the given glyph at
   fast quality with the given font and color.  The 0 pixel is the
   colorkey, giving a transparent background, and the 1 pixel is set
   to the text color.  The glyph is rendered without any padding or
   centering in the X direction, and aligned normally in the Y direction.
   This function returns the new surface, or NULL if there was an error. *)
val render_glyph_solid: font: font -> ch: int -> fg: Video.color -> Video.surface;;

(* Create an 8-bit palettized surface and render the given text at
   high quality with the given font and colors.  The 0 pixel is background,
   while other pixels have varying degrees of the foreground color.
   This function returns the new surface, or NULL if there was an error. *)
val render_text_shaded: font: font -> text: string -> fg: Video.color -> bg: Video.color -> Video.surface;;
val render_utf8_shaded: font: font -> text: string -> fg: Video.color -> bg: Video.color -> Video.surface;;
val render_unicode_shaded: font: font -> text: uint16_array -> fg: Video.color -> bg: Video.color -> Video.surface;;

(* Create an 8-bit palettized surface and render the given glyph at
   high quality with the given font and colors.  The 0 pixel is background,
   while other pixels have varying degrees of the foreground color.
   The glyph is rendered without any padding or centering in the X
   direction, and aligned normally in the Y direction.
   This function returns the new surface, or NULL if there was an error. *)
val render_glyph_shaded: font: font -> ch: int -> fg: Video.color -> bg: Video.color -> Video.surface;;

(* Create a 32-bit ARGB surface and render the given text at high quality,
   using alpha blending to dither the font with the given color.
   This function returns the new surface, or NULL if there was an error. *)
val render_text_blended: font: font -> text: string -> fg: Video.color -> Video.surface;;
val render_utf8_blended: font: font -> text: string -> fg: Video.color -> Video.surface;;
val render_unicode_blended: font: font -> text: uint16_array -> fg: Video.color -> Video.surface;;

(* Create a 32-bit ARGB surface and render the given glyph at high quality,
   using alpha blending to dither the font with the given color.
   The glyph is rendered without any padding or centering in the X
   direction, and aligned normally in the Y direction.
   This function returns the new surface, or NULL if there was an error. *)
val render_glyph_blended: font: font -> ch: int -> fg: Video.color -> Video.surface;;

(* Close an opened font file *)
val close_font: font: font -> unit;;

(* De-initialize the TTF engine *)
val quit: unit -> unit;;

(* Check if the TTF engine is initialized *)
val was_init: unit -> bool;;

(* Get the kerning size of two glyphs *)
val get_font_kerning_size: font: font -> prev_index: int -> index: int -> int;;
