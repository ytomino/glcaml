#include <memory.h>
#if defined(USE_FRAMEWORK)
#include <SDL_image/SDL_image.h>
#else
#include <SDL/SDL_image.h>
#endif
#include "IMG_savepng.h"
#include "caml/alloc.h"
#include "caml/callback.h"
#include "caml/fail.h"
#include "caml/memory.h"
#include "caml/mlvalues.h"

/* exception */

static void raise_failure(void)
{
	raise_with_string(*caml_named_value("SDL_failure"), IMG_GetError());
}

/* surface type (unmanaged) */

static inline SDL_Surface *SDL_Surface_val(value surface)
{
	return (SDL_Surface *)surface;
}

/* stub */

CAMLprim value sdlimagestub_savepng(value surf, value file)
{
	CAMLparam2(surf, file);
	int ret = IMG_SavePNG(
		String_val(file),
		SDL_Surface_val(surf),
		IMG_COMPRESS_MAX);
	if(ret != 0) raise_failure();
	CAMLreturn(Val_unit);
}
