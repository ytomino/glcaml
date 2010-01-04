(*
 * currently not implemented:
 *
 *  - Mix_QuickLoad_(WAV,RAW) to load audio from the memory
 *  - Mix_Load(WAV,MUS)_RW for loading from SDL_RWops
 *  - Mix_SetPostMix callback
 *  - Mix_HookMusic
 *  - Mix_HookMusicFinished
 *  - Mix_GetMusicHookData
 *  - Mix_ChannelFinished
 *
 *  - Mix_*Effect*
 *
 *)

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

type chunk_t
type music_t

type channel = int

module Mix : sig

(* 
 * minor semantic helper variables 
 *)

val any_channel : int             (* -1, for play_channel, etc *)
val first_available_channel : int (* -1, ditto *)
val all_channels : int            (* -1, expire_channel, etc *)

val channel_post : int            (* -2, MIX_CHANNEL_POST, for panning/effects *)

val loop_forever : int            (* -1, fade_in_music, etc *)
val play_once    : int            (*  0, fade_in_music, etc *)



val get_version : unit -> string 
val get_last_error : unit -> string

val init : init_flag list -> unit
val quit : unit -> unit
val open_audio : int -> Sdl.Audio.sample_type -> Sdl.Audio.channel_type -> int -> unit
val allocate_channels : int -> int

val load_wav : string -> chunk_t
val free_chunk : chunk_t -> unit 
val free_music : music_t -> unit

val play_channel : channel -> chunk_t -> int -> channel
val play_channel_timed : channel -> chunk_t -> int -> int -> channel
val play_music : music_t -> int -> bool

val load_mus : string -> music_t
val load_music : string -> music_t

val get_chunk_decoders : unit -> string list
val get_music_decoders : unit -> string list

val get_music_type : music_t option -> music_type

val set_panning : channel -> int -> int -> bool
val set_position : channel -> int -> int -> bool
val set_distance : channel -> int -> bool
val set_reverse_stereo : channel -> bool -> bool

val reserve_channels : int -> int
val group_channel : channel -> int -> bool
val group_channels : channel -> channel -> int -> bool
val ungroup_channel : channel -> bool
val ungroup_channels : channel -> channel -> bool

val group_available : int -> channel
val group_count : int -> int
val get_available_channel_count : unit -> int

val group_oldest : int -> channel
val group_newer : int -> channel

val fade_in_music : music_t -> int -> int -> bool
val fade_in_music_pos : music_t -> int -> int -> float -> bool

val fade_in_channel : channel -> chunk_t -> int -> int -> channel
val fade_in_channel_timed : channel -> chunk_t -> int -> int -> int -> channel

val volume : channel -> int -> int
val set_volume : channel -> int -> int
val get_volume : channel -> int

val volume_chunk : chunk_t -> int -> int
val set_chunk_volume : chunk_t -> int -> int
val get_chunk_volume : chunk_t -> int

val volume_music : int -> int
val get_music_volume : unit -> int
val set_music_volume : int -> int


val halt_channel : channel -> unit
val halt_group : int -> unit
val halt_music : unit -> unit

val expire_channel : channel -> int -> bool
val remove_channel_expiration : channel -> bool

val fade_out_channel : channel -> int -> bool
val fade_out_group : int -> int -> bool
val fade_out_music : int -> bool

val fading_music : unit -> fading_type
val fading_channel : channel -> fading_type
val get_music_fading : unit -> fading_type
val get_channel_fading : channel -> fading_type

val pause : channel -> unit
val resume : channel -> unit
val paused : channel -> bool

val pause_music : unit -> unit
val resume_music : unit -> unit
val rewind_music : unit -> unit
val paused_music : unit -> bool


val set_music_position : float -> bool
val playing : channel -> bool
val playing_music : unit -> bool
val set_music_cmd : string -> bool
val set_synchro_value : int -> unit
val get_synchro_value : unit -> int
val get_chunk : channel -> chunk_t
val close_audio : unit -> unit

end
