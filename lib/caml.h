#ifndef CAML_H

#define CAML_H

/*  CAML - C interface */
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/bigarray.h>


/*  Caml list manipulations */
#define NIL_tag 0
#define CONS_tag 1

#define is_nil Is_long
#define is_not_nil Is_block
#define hd(x) Field(x, 0)
#define tl(x) Field(x, 1)

#define Opt_arg(v, conv, def) (Is_block(v) ? conv(Field((v), 0)) : (def))

#endif
