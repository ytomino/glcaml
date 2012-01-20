#if defined(USE_FRAMEWORK)
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "caml/callback.h"
#include "caml/alloc.h"
#include "caml/memory.h"
#include "caml/fail.h"
#include "caml/bigarray.h"

/* utilities */

#define is_not_nil Is_block
#define hd(v) Field((v), 0)
#define tl(v) Field((v), 1)

static value cons(value x, value l)
{
	CAMLparam2(x, l);
	CAMLlocal1(m);
	m = alloc_small(2, Tag_cons);
	Field(m, 0) = x;
	Field(m, 1) = l;
	CAMLreturn(m);
}

/* color type */

static inline SDL_Color SDL_Color_val(value v)
{
	SDL_Color result;
	result.r = Int_val(Field(v,0));
	result.g = Int_val(Field(v,1));
	result.b = Int_val(Field(v,2));
	result.unused = 0;
	return result;
}

/* surface type (unmanaged) */

static inline value Val_SDL_Surface(SDL_Surface *surface)
{
	return (value)surface;
}

/* font type (unmanaged) */

static inline value Val_TTF_Font(TTF_Font *font)
{
	return (value)font;
}

static inline TTF_Font *TTF_Font_val(value v)
{
	return (TTF_Font *)v;
}

/* font style */

static int const font_style_table[] = {
	TTF_STYLE_BOLD,
	TTF_STYLE_ITALIC,
	TTF_STYLE_UNDERLINE
};

static value Val_style(int style)
{
	CAMLparam0();
	CAMLlocal1(result);
	int i;
	result = Val_emptylist;
	for(i = 0; i < 3; i++){
		if(font_style_table[i] & style){
			result = cons(Val_int(i), result);
		}
	}
	CAMLreturn(result);
}

static int Style_val(value style)
{
	int result = 0;
	while(is_not_nil(style)){
		result |= font_style_table[Int_val(hd(style))];
		style = tl(style);
	}
	return result;
}

/* hinting */

static value Val_hinting(int hinting)
{
	return Val_int(hinting);
}

static int Hinting_val(value hinting)
{
	return Int_val(hinting);
}

/* exception */

static void raise_failure(void)
{
	raise_with_string(*caml_named_value("SDL_failure"), TTF_GetError());
}

/* primitives */

CAMLprim value sdlttfstub_linked_version(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	SDL_version const *version = TTF_Linked_Version();
	result = alloc(3, 0);
	Store_field(result, 0, Val_int(version->major));
	Store_field(result, 1, Val_int(version->minor));
	Store_field(result, 2, Val_int(version->patch));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_byte_swapped_unicode(value swapped)
{
	CAMLparam1(swapped);
	TTF_ByteSwappedUNICODE(Bool_val(swapped));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlttfstub_init(value unit)
{
	CAMLparam1(unit);
	TTF_Init();
	CAMLreturn(Val_unit);
}

CAMLprim value sdlttfstub_open_font(value file, value ptsize)
{
	CAMLparam2(file, ptsize);
	TTF_Font *font = TTF_OpenFont(String_val(file), Int_val(ptsize));
	if(font == NULL){
		caml_raise_sys_error(caml_copy_string(TTF_GetError()));
	}
	value result = Val_TTF_Font(font);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_open_font_index(value file, value ptsize, value index)
{
	CAMLparam3(file, ptsize, index);
	TTF_Font *font = TTF_OpenFontIndex(String_val(file), Int_val(ptsize), Int_val(index));
	if(font == NULL){
		caml_raise_sys_error(caml_copy_string(TTF_GetError()));
	}
	value result = Val_TTF_Font(font);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_get_font_style(value font)
{
	CAMLparam1(font);
	int style = TTF_GetFontStyle(TTF_Font_val(font));
	value result = Val_style(style);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_set_font_style(value font, value style)
{
	CAMLparam2(font, style);
	TTF_SetFontStyle(TTF_Font_val(font), Style_val(style));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlttfstub_get_font_hinting(value font)
{
	CAMLparam1(font);
	int hinting = TTF_GetFontHinting(TTF_Font_val(font));
	value result = Val_hinting(hinting);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_set_font_hinting(value font, value hinting)
{
	CAMLparam2(font, hinting);
	TTF_SetFontHinting(TTF_Font_val(font), Hinting_val(hinting));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlttfstub_font_height(value font)
{
	CAMLparam1(font);
	value result = Val_int(TTF_FontHeight(TTF_Font_val(font)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_font_ascent(value font)
{
	CAMLparam1(font);
	value result = Val_int(TTF_FontAscent(TTF_Font_val(font)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_font_descent(value font)
{
	CAMLparam1(font);
	value result = Val_int(TTF_FontDescent(TTF_Font_val(font)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_font_line_skip(value font)
{
	CAMLparam1(font);
	value result = Val_int(TTF_FontLineSkip(TTF_Font_val(font)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_get_font_kerning(value font)
{
	CAMLparam1(font);
	int allowed = TTF_GetFontKerning(TTF_Font_val(font));
	value result = Val_bool(allowed);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_set_font_kerning(value font, value allowed)
{
	CAMLparam2(font, allowed);
	TTF_SetFontKerning(TTF_Font_val(font), Bool_val(allowed));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlttfstub_font_faces(value font)
{
	CAMLparam1(font);
	value result = Val_int(TTF_FontFaces(TTF_Font_val(font)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_font_face_is_fixed_width(value font)
{
	CAMLparam1(font);
	value result = Val_bool(TTF_FontFaceIsFixedWidth(TTF_Font_val(font)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_font_face_family_name(value font)
{
	CAMLparam1(font);
	value result = caml_copy_string(TTF_FontFaceFamilyName(TTF_Font_val(font)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_font_face_style_name(value font)
{
	CAMLparam1(font);
	value result = caml_copy_string(TTF_FontFaceStyleName(TTF_Font_val(font)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_glyph_is_provided(value font, value ch)
{
	CAMLparam2(font, ch);
	value result = Val_bool(TTF_GlyphIsProvided(TTF_Font_val(font), Int_val(ch)));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_glyph_metrics(value font, value ch)
{
	CAMLparam2(font, ch);
	CAMLlocal1(result);
	int minx, miny, maxx, maxy, advance;
	TTF_GlyphMetrics(TTF_Font_val(font), Int_val(ch),
		&minx, &maxx, &miny, &maxy, &advance);
	result = alloc(5, 0);
	Store_field(result, 0, Val_int(minx));
	Store_field(result, 1, Val_int(maxx));
	Store_field(result, 2, Val_int(miny));
	Store_field(result, 3, Val_int(maxy));
	Store_field(result, 4, Val_int(advance));
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_size_text(value font, value text)
{
	CAMLparam2(font, text);
	CAMLlocal1(result);
	int w, h;
	if(TTF_SizeText(TTF_Font_val(font), String_val(text), &w, &h)){
		raise_failure();
	}
	result = alloc_small(2, 0);
	Field(result, 0) = Val_int(w);
	Field(result, 1) = Val_int(h);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_size_utf8(value font, value text)
{
	CAMLparam2(font, text);
	CAMLlocal1(result);
	int w, h;
	if(TTF_SizeUTF8(TTF_Font_val(font), String_val(text), &w, &h)){
		raise_failure();
	}
	result = alloc_small(2, 0);
	Field(result, 0) = Val_int(w);
	Field(result, 1) = Val_int(h);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_size_unicode(value font, value text)
{
	CAMLparam2(font, text);
	CAMLlocal1(result);
	int w, h;
	if(TTF_SizeUNICODE(TTF_Font_val(font), Caml_ba_data_val(text), &w, &h)){
		raise_failure();
	}
	result = alloc_small(2, 0);
	Field(result, 0) = Val_int(w);
	Field(result, 1) = Val_int(h);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_text_solid(value font, value text, value fg)
{
	CAMLparam3(font, text, fg);
	SDL_Surface *new_surface = TTF_RenderText_Solid(
		TTF_Font_val(font),
		String_val(text),
		SDL_Color_val(fg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_utf8_solid(value font, value text, value fg)
{
	CAMLparam3(font, text, fg);
	SDL_Surface *new_surface = TTF_RenderUTF8_Solid(
		TTF_Font_val(font),
		String_val(text),
		SDL_Color_val(fg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_unicode_solid(value font, value text, value fg)
{
	CAMLparam3(font, text, fg);
	SDL_Surface *new_surface = TTF_RenderUNICODE_Solid(
		TTF_Font_val(font),
		Caml_ba_data_val(text),
		SDL_Color_val(fg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_glyph_solid(value font, value ch, value fg)
{
	CAMLparam3(font, ch, fg);
	SDL_Surface *new_surface = TTF_RenderGlyph_Solid(
		TTF_Font_val(font),
		Int_val(ch),
		SDL_Color_val(fg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_text_shaded(value font, value text, value fg, value bg)
{
	CAMLparam4(font, text, fg, bg);
	SDL_Surface *new_surface = TTF_RenderText_Shaded(
		TTF_Font_val(font),
		String_val(text),
		SDL_Color_val(fg),
		SDL_Color_val(bg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_utf8_shaded(value font, value text, value fg, value bg)
{
	CAMLparam4(font, text, fg, bg);
	SDL_Surface *new_surface = TTF_RenderUTF8_Shaded(
		TTF_Font_val(font),
		String_val(text),
		SDL_Color_val(fg),
		SDL_Color_val(bg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_unicode_shaded(value font, value text, value fg, value bg)
{
	CAMLparam4(font, text, fg, bg);
	SDL_Surface *new_surface = TTF_RenderUNICODE_Shaded(
		TTF_Font_val(font),
		Caml_ba_data_val(text),
		SDL_Color_val(fg),
		SDL_Color_val(bg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_glyph_shaded(value font, value ch, value fg, value bg)
{
	CAMLparam3(font, ch, fg);
	SDL_Surface *new_surface = TTF_RenderGlyph_Shaded(
		TTF_Font_val(font),
		Int_val(ch),
		SDL_Color_val(fg),
		SDL_Color_val(bg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_text_blended(value font, value text, value fg)
{
	CAMLparam3(font, text, fg);
	SDL_Surface *new_surface = TTF_RenderText_Blended(
		TTF_Font_val(font),
		String_val(text),
		SDL_Color_val(fg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_utf8_blended(value font, value text, value fg)
{
	CAMLparam3(font, text, fg);
	SDL_Surface *new_surface = TTF_RenderUTF8_Blended(
		TTF_Font_val(font),
		String_val(text),
		SDL_Color_val(fg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_unicode_blended(value font, value text, value fg)
{
	CAMLparam3(font, text, fg);
	SDL_Surface *new_surface = TTF_RenderUNICODE_Blended(
		TTF_Font_val(font),
		Caml_ba_data_val(text),
		SDL_Color_val(fg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_render_glyph_blended(value font, value ch, value fg)
{
	CAMLparam3(font, ch, fg);
	SDL_Surface *new_surface = TTF_RenderGlyph_Blended(
		TTF_Font_val(font),
		Int_val(ch),
		SDL_Color_val(fg));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_close_font(value font)
{
	CAMLparam1(font);
	TTF_CloseFont(TTF_Font_val(font));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlttfstub_quit(value unit)
{
	CAMLparam1(unit);
	TTF_Quit();
	CAMLreturn(Val_unit);
}

CAMLprim value sdlttfstub_was_init(value unit)
{
	CAMLparam1(unit);
	value result = Val_bool(TTF_WasInit());
	CAMLreturn(result);
}

CAMLprim value sdlttfstub_get_font_kerning_size(value font, value prev_index, value index)
{
	CAMLparam3(font, prev_index, index);
	value result = Val_int(TTF_GetFontKerningSize(
		TTF_Font_val(font),
		Int_val(prev_index),
		Int_val(index)));
	CAMLreturn(result);
}
