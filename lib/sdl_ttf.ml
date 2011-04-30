open Sdl;;

type uint16_array = (int, Bigarray.int16_unsigned_elt, Bigarray.c_layout) Bigarray.Array1.t

external linked_version: unit -> int * int * int = "sdlttfstub_linked_version";;

let unicode_bom_native: int = 0xFEFF;;
let unicode_bom_swapped: int = 0xFFFE;;

external byte_swapped_unicode: swapped: bool -> unit = "sdlttfstub_byte_swapped_unicode";;

type font;; (* outside the heap *)

external init: unit -> unit = "sdlttfstub_init";;
external open_font: file: string -> ptsize: int -> font = "sdlttfstub_open_font";;
external open_font_index: file: string -> ptsize: int -> index: int -> font = "sdlttfstub_open_font_index";;

type font_style = STYLE_BOLD | STYLE_ITALIC | STYLE_UNDERLINE;;

external get_font_style: font: font -> font_style list = "sdlttfstub_get_font_style";;
external set_font_style: font: font -> font_style list -> unit = "sdlttfstub_set_font_style";;

type hinting = HINTING_NORMAL | HINTING_LIGHT | HINTING_MONO | HINTING_NONE;;

external get_font_hinting: font: font -> hinting = "sdlttfstub_get_font_hinting";;
external set_font_hinting: font: font -> hinting -> unit = "sdlttfstub_set_font_hinting";;
external font_height: font: font -> int = "sdlttfstub_font_height";;
external font_ascent: font: font -> int = "sdlttfstub_font_ascent";;
external font_descent: font: font -> int = "sdlttfstub_font_descent";;
external font_line_skip: font: font -> int = "sdlttfstub_font_line_skip";;
external get_font_kerning: font: font -> bool = "sdlttfstub_get_font_kerning";;
external set_font_kerning: font: font -> bool -> unit = "sdlttfstub_set_font_kerning";;
external font_faces: font: font -> int = "sdlttfstub_font_faces";;
external font_face_is_fixed_width: font: font -> bool = "sdlttfstub_font_face_is_fixed_width";;
external font_face_family_name: font: font -> string = "sdlttfstub_font_face_family_name";;
external font_face_style_name: font: font -> string = "sdlttfstub_font_face_style_name";;
external glyph_is_provided: font: font -> ch: int -> bool = "sdlttfstub_glyph_is_provided";;
external glyph_metrics: font: font -> ch: int -> int * int * int * int * int = "sdlttfstub_glyph_metrics";;
external size_text: font: font -> text: string -> int * int = "sdlttfstub_size_text";;
external size_utf8: font: font -> text: string -> int * int = "sdlttfstub_size_utf8";;
external size_unicode: font: font -> text: uint16_array -> int * int = "sdlttfstub_size_unicode";;
external render_text_solid: font: font -> text: string -> fg: Video.color -> Video.surface = "sdlttfstub_render_text_solid";;
external render_utf8_solid: font: font -> text: string -> fg: Video.color -> Video.surface = "sdlttfstub_render_utf8_solid";;
external render_unicode_solid: font: font -> text: uint16_array -> fg: Video.color -> Video.surface = "sdlttfstub_render_unicode_solid";;
external render_glyph_solid: font: font -> ch: int -> fg: Video.color -> Video.surface = "sdlttfstub_render_glyph_solid";;
external render_text_shaded: font: font -> text: string -> fg: Video.color -> bg: Video.color -> Video.surface = "sdlttfstub_render_text_shaded";;
external render_utf8_shaded: font: font -> text: string -> fg: Video.color -> bg: Video.color -> Video.surface = "sdlttfstub_render_utf8_shaded";;
external render_unicode_shaded: font: font -> text: uint16_array -> fg: Video.color -> bg: Video.color -> Video.surface = "sdlttfstub_render_unicode_shaded";;
external render_glyph_shaded: font: font -> ch: int -> fg: Video.color -> bg: Video.color -> Video.surface = "sdlttfstub_render_glyph_shaded";;
external render_text_blended: font: font -> text: string -> fg: Video.color -> Video.surface = "sdlttfstub_render_text_blended";;
external render_utf8_blended: font: font -> text: string -> fg: Video.color -> Video.surface = "sdlttfstub_render_utf8_blended";;
external render_unicode_blended: font: font -> text: uint16_array -> fg: Video.color -> Video.surface = "sdlttfstub_render_unicode_blended";;
external render_glyph_blended: font: font -> ch: int -> fg: Video.color -> Video.surface = "sdlttfstub_render_glyph_blended";;
external close_font: font: font -> unit = "sdlttfstub_close_font";;
external quit: unit -> unit = "sdlttfstub_quit";;
external was_init: unit -> bool = "sdlttfstub_was_init";;
