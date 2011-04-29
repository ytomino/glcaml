open Sdl;;

external load: file: string -> Video.surface = "sdlimagestub_load";;
external read_xpm_from_array: xpm: string array -> Video.surface = "sdlimagestub_read_xpm_from_array";;
