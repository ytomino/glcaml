#include <memory.h>
#if defined(USE_FRAMEWORK)
#include <SDL_image/SDL_image.h>
#else
#include <SDL/SDL_image.h>
#endif
#include "caml/callback.h"
#include "caml/mlvalues.h"
#include "caml/memory.h"
#include "caml/fail.h"
#include "caml/alloc.h"

/* exception */

static void raise_failure(void)
{
	raise_with_string(*caml_named_value("SDL_failure"), IMG_GetError());
}

/* surface type (unmanaged) */

static inline value Val_SDL_Surface(SDL_Surface *surface)
{
	return (value)surface;
}

/* primitives */

CAMLprim value sdlimagestub_load(value file)
{
	CAMLparam1(file);
	SDL_Surface *new_surface = IMG_Load(String_val(file));
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}

CAMLprim value sdlimagestub_read_xpm_from_array(value xpm)
{
	CAMLparam1(xpm);
	size_t i;
	size_t length = Wosize_val(xpm);
	char **data = malloc((length + 1) * sizeof(char *));
	if(data == NULL){
		caml_raise_out_of_memory();
	}
	for(i = 0; i < length; ++i){
		data[i] = String_val(Field(xpm, i));
	}
	data[length] = NULL;
	SDL_Surface *new_surface = IMG_ReadXPMFromArray(data);
	free(data);
	if(new_surface == NULL){
		raise_failure();
	}
	value result = Val_SDL_Surface(new_surface);
	CAMLreturn(result);
}
