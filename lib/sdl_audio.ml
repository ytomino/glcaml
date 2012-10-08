(****************************** Audio ****************************)
(* low-level audio. *)

open Sdl

include Audio

type audio_status =
  | STOPPED
  | PAUSED
  | PLAYING
  | UNKNOWN

type audio_spec = {
  frequency: int;
  format: sample_type;
  channels: channel_type;
  silence: int;
  samples: int;
  size: int;
}

let rec int_of_sampletype t =
  match t with
    | U8        -> 0x0008  (* Unsigned 8-bit samples *)
    | S8        -> 0x8008  (* Signed 8-bit samples *)
    | U16LSB    -> 0x0010  (* Unsigned 16-bit samples *)
    | S16LSB    -> 0x8010  (* Signed 16-bit samples *)
    | U16MSB    -> 0x1010  (* As above, but big-endian byte order *)
    | S16MSB    -> 0x9010  (* As above, but big-endian byte order *)
    | U16       -> int_of_sampletype U16LSB
    | S16       -> int_of_sampletype S16LSB

let sampletype_of_int i =
  match i with
    | 0x0008 -> U8
    | 0x8008 -> S8
    | 0x0010 -> U16LSB
    | 0x8010 -> S16LSB
    | 0x1010 -> U16MSB
    | 0x9010 -> S16MSB
    | _ ->  raise (SDL_failure "Unknown sample format")


let int_of_channel t =
  match t with
    | MONO -> 1
    | STEREO -> 2

let channel_of_int i =
  match i with
    | 1 -> MONO
    | 2 -> STEREO
    | _ -> raise (SDL_failure "Unknown channel format")

let mix_maxvolume  = 128

external proto_open_audio : int -> int -> int -> int -> int * int * int * int * int * int
= "sdlstub_open_audio"

let open_audio a callback =
  Callback.register "ml_setaudiocallback" callback;
  let (fr, fo, ch, si, sa, sz) = proto_open_audio a.frequency (int_of_sampletype a.format) (int_of_channel a.channels) a.samples in
  {frequency = fr; format = (sampletype_of_int fo); channels = (channel_of_int ch); silence = si; samples = sa; size = sz}

external close_audio : unit -> unit
= "sdlstub_close_audio"

external lock_audio : unit -> unit
= "sdlstub_lock_audio"

external unlock_audio : unit -> unit
= "sdlstub_unlock_audio"

external pause_audio : bool -> unit
= "sdlstub_pause_audio"

external proto_get_audio_status : unit -> int
= "sdlstub_get_audio_status"


external proto_load_wav : string -> int * int * int * int * int * int * byte_array
= "sdlstub_load_wav"

let get_audio_status () =
  let r = proto_get_audio_status () in
  if r = 0 then STOPPED else
  if r = 1 then PAUSED else
  if r = 2 then PLAYING else
  UNKNOWN

let load_wav file =
  let (fr, fo, ch, si, sa, sz, buf) = proto_load_wav file in
  {frequency = fr; format = (sampletype_of_int fo); channels = (channel_of_int ch); silence = si; samples = sa; size = sz}, buf

external free_wav : byte_array -> unit
= "sdlstub_free_wav"

external mix_audio : byte_array  -> byte_array  -> int -> unit
= "sdlstub_mix_audio"

external proto_convert_audio : int -> int -> int -> int -> int -> int -> byte_array -> byte_array
= "sdlstub_convert_audio_byte" "sdlstub_convert_audio"

let convert_audio f_fmt f_ch f_fr fmt ch fr ain  =
  proto_convert_audio (int_of_sampletype f_fmt) (int_of_channel f_ch) f_fr (int_of_sampletype fmt) (int_of_channel ch) fr ain

external proto_fx_pan : float -> float -> byte_array -> byte_array -> unit
= "fxstub_pan"

let fx_pan pan volume sample =
  lock_audio ();
  let len = Bigarray.Array1.dim sample in
  let newsample = Bigarray.Array1.create Bigarray.int8_unsigned Bigarray.c_layout len in
  proto_fx_pan pan volume sample newsample;
  unlock_audio ();
  newsample

external proto_fx_shift : float -> byte_array -> byte_array -> int
= "fxstub_shift"

let fx_shift pitch sample =
  lock_audio ();
  let p = if pitch < 0.1 then 0.1 else if pitch > 10.0 then 10.0 else pitch in
  let len = float_of_int (Bigarray.Array1.dim sample) in
  let newsample = Bigarray.Array1.create Bigarray.int8_unsigned Bigarray.c_layout (int_of_float (len /. p)) in
  let _ = proto_fx_shift p sample newsample in
  unlock_audio () ;
  newsample

(****************************** End Audio ****************************)

let (_: Thread.t) = Thread.self ();; (* use threads.cma/cmxa *)
