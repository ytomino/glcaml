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

#define SDL_IMAGE_VERSION_NUM \
	(SDL_IMAGE_MAJOR_VERSION * 0x10000 \
	+ SDL_IMAGE_MINOR_VERSION * 0x100 \
	+ SDL_IMAGE_PATCHLEVEL)

/* utilities */

#define is_not_nil Is_block
#define hd(v) Field((v), 0)
#define tl(v) Field((v), 1)

/* surface type (unmanaged) */

static inline value Val_SDL_Surface(SDL_Surface *surface)
{
	return (value)surface;
}

/* IMG_InitFlags */

static int const initflags_table[] = {
	IMG_INIT_JPG,
	IMG_INIT_PNG,
	IMG_INIT_TIF,
#if SDL_IMAGE_VERSION_NUM >= 0x1020c
	IMG_INIT_WEBP,
#else
	0,
#endif
};

static inline int Initflags_val(value initflags)
{
	int result = 0;
	while(is_not_nil(initflags)){
		result |= initflags_table[Int_val(hd(initflags))];
		initflags = tl(initflags);
	}
	return result;
}

/* exception */

static void raise_failure(void)
{
	raise_with_string(*caml_named_value("SDL_failure"), IMG_GetError());
}

/* primitives */

CAMLprim value sdlimagestub_linked_version(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	SDL_version const *version = IMG_Linked_Version();
	result = alloc(3, 0);
	Store_field(result, 0, Val_int(version->major));
	Store_field(result, 1, Val_int(version->minor));
	Store_field(result, 2, Val_int(version->patch));
	CAMLreturn(result);
}

CAMLprim value sdlimagestub_init(value flags)
{
	CAMLparam1(flags);
	IMG_Init(Initflags_val(flags));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlimagestub_quit(value unit)
{
	CAMLparam1(unit);
	IMG_Quit();
	CAMLreturn(Val_unit);
}

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
