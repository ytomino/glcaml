open Sdl;;

external linked_version: unit -> int * int * int = "sdlimagestub_linked_version";;

type init_flags = INIT_JPG | INIT_PNG | INIT_TIF;;

external init: init_flags list -> unit = "sdlimagestub_init";;
external quit: unit -> unit = "sdlimagestub_quit";;
external load: file: string -> Video.surface = "sdlimagestub_load";;
external read_xpm_from_array: xpm: string array -> Video.surface = "sdlimagestub_read_xpm_from_array";;
