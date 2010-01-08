(*
 * sdlcaml - Objective Caml interface for the SDL library
 * SDL Mixer interface
 * Copyright (C) 2010 Einar Lielmanis, einars@gmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2, as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Library General Public License version 2 for more details
 * (enclosed in the file LGPL).
 *)

open Sdl
open Audio

type byte_array = (int, Bigarray.int8_unsigned_elt, Bigarray.c_layout) Bigarray.Array1.t 

type init_flag =
    | FLAC
    | MOD
    | MP3
    | OGG

type fading_type =
    | NO_FADING
    | FADING_OUT
    | FADING_IN

type music_type =
    | MUS_NONE
    | MUS_CMD
    | MUS_WAV
    | MUS_MOD
    | MUS_MID
    | MUS_OGG
    | MUS_MP3
    | MUS_MP3_MAD
    | MUS_FLAC

type channel = int

type chunk_t
type music_t

module Mix = struct

let any_channel = (-1)
let first_available_channel = (-1)
let channel_post = (-2)
let all_channels = (-2)
let loop_forever = (-1)
let play_once    = 0

external get_last_error : unit -> string = "sdlmixer_get_last_error"

external get_version : unit -> string = "sdlmixer_get_version"

external init : init_flag list -> unit = "sdlmixer_init"
external quit : unit -> unit = "sdlmixer_quit"
external proto_open_audio : int -> int -> int -> int -> unit = "sdlmixer_open_audio"
let open_audio frequency format channels samples =
    proto_open_audio frequency (int_of_sampletype format) (int_of_channel channels) samples

external allocate_channels : int -> int = "sdlmixer_allocate_channels"

external load_wav : string -> chunk_t = "sdlmixer_load_wav"
external load_mus : string -> music_t = "sdlmixer_load_mus"

let load_music = load_mus

external play_channel : channel -> chunk_t -> int -> channel = "sdlmixer_play_channel"
external play_channel_timed : channel -> chunk_t -> int -> int -> channel = "sdlmixer_play_channel_timed"
external play_music : music_t -> int -> bool = "sdlmixer_play_music"
external free_chunk : chunk_t -> unit = "sdlmixer_free_chunk"
external free_music : music_t -> unit = "sdlmixer_free_music"

external get_chunk_decoders : unit -> string list = "sdlmixer_get_chunk_decoders"
external get_music_decoders : unit -> string list = "sdlmixer_get_music_decoders"

external get_music_type : music_t option -> music_type = "sdlmixer_get_music_type"

external set_panning : channel -> int -> int -> bool = "sdlmixer_set_panning"
external set_position : channel -> int -> int -> bool = "sdlmixer_set_position"
external set_distance : channel -> int -> bool = "sdlmixer_set_distance"
external set_reverse_stereo : channel -> bool -> bool = "sdlmixer_set_reverse_stereo"

external reserve_channels : int -> int = "sdlmixer_reserve_channels"

external group_channel : channel -> int -> bool = "sdlmixer_group_channel"
external group_channels : channel -> channel -> int -> bool = "sdlmixer_group_channels"
let      ungroup_channel ch 
         = group_channel ch (-1)
let      ungroup_channels ch_start ch_end 
         = group_channels ch_start ch_end (-1)

external group_available : int -> channel = "sdlmixer_group_available"

external group_count : int -> int = "sdlmixer_group_count"
let get_available_channel_count () = group_count (-1)

external group_oldest : int -> channel = "sdlmixer_group_oldest"
external group_newer : int -> channel = "sdlmixer_group_newer"


external fade_in_music : music_t -> int -> int -> bool = "sdlmixer_fade_in_music"
external fade_in_music_pos : music_t -> int -> int -> float -> bool = "sdlmixer_fade_in_music_pos"

external fade_in_channel : channel -> chunk_t -> int -> int -> channel = "sdlmixer_fade_in_channel"
external fade_in_channel_timed : channel -> chunk_t -> int -> int -> int -> channel = "sdlmixer_fade_in_channel_timed"

external proto_volume : channel -> int -> int = "sdlmixer_volume"
let volume = proto_volume
let set_volume ch vol = proto_volume ch vol
let get_volume ch = set_volume ch (-1)

external proto_volume_chunk : chunk_t -> int -> int = "sdlmixer_volume_chunk"
let volume_chunk = proto_volume_chunk
let set_chunk_volume = volume_chunk
let get_chunk_volume ch = volume_chunk ch (-1)

external volume_music : int -> int = "sdlmixer_volume_music"
let get_music_volume () = volume_music (-1)
let set_music_volume vol = volume_music vol

external halt_channel : channel -> unit = "sdlmixer_halt_channel"
external halt_group : int -> unit = "sdlmixer_halt_group"
external halt_music : unit -> unit = "sdlmixer_halt_music"

external expire_channel : channel -> int -> bool = "sdlmixer_expire_channel"
let      remove_channel_expiration ch
         = expire_channel ch (-1)

external fade_out_channel : channel -> int -> bool = "sdlmixer_fade_out_channel"
external fade_out_group : int -> int -> bool = "sdlmixer_fade_out_group"
external fade_out_music : int -> bool = "sdlmixer_fade_out_music"

external fading_music : unit -> fading_type = "sdlmixer_fading_music"
external fading_channel : channel -> fading_type = "sdlmixer_fading_channel"

let get_music_fading = fading_music
let get_channel_fading = fading_channel

external pause : channel -> unit = "sdlmixer_pause"
external resume : channel -> unit = "sdlmixer_resume"
external paused : channel -> bool = "sdlmixer_paused"

external pause_music : unit -> unit = "sdlmixer_pause_music"
external resume_music : unit -> unit = "sdlmixer_resume_music"
external rewind_music : unit -> unit = "sdlmixer_rewind_music"
external paused_music : unit -> bool = "sdlmixer_paused_music"

external set_music_position : float -> bool = "sdlmixer_set_music_position"
external playing : channel -> bool = "sdlmixer_playing"
external playing_music : unit -> bool = "sdlmixer_playing_music"
external set_music_cmd : string -> bool = "sdlmixer_set_music_cmd"
external get_chunk : channel -> chunk_t = "sdlmixer_get_chunk"
external close_audio : unit -> unit = "sdlmixer_close_audio"


end
