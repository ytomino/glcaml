open Sdl;;

external linked_version: unit -> int * int * int = "sdlmixerstub_linked_version";;

type init_flags = INIT_FLAC | INIT_MOD | INIT_MP3 | INIT_OGG;;

external init: init_flags list -> unit = "sdlmixerstub_init";;
external quit: unit -> unit = "sdlmixerstub_quit";;

external little_endian: unit -> bool = "sdlmixerutil_little_endian";;

let channels: int = 8;;
let default_frequency: int = 22050;;
let default_format: Audio.sample_type = if little_endian () then Audio.S16LSB else Audio.S16MSB;;
let default_channels: int = 2;;
let max_volume: int = 128;;

type chunk;;
type fading = NO_FADING | FADING_OUT | FADING_IN;;
type music_type = MUS_NONE | MUS_CMD | MUS_WAV | MUS_MOD | MUS_MID | MUS_OGG | MUS_MP3 | MUS_MP3_MAD | MUS_FLAC;;
type music;;

external open_audio: frequency: int -> format: Audio.sample_type -> channels: int -> chunksize: int -> unit = "sdlmixerstub_open_audio";;
external allocate_channels: numchans: int -> int = "sdlmixerstub_allocate_channels";;
external query_spec: unit -> int * Audio.sample_type * int = "sdlmixerstub_query_spec";;
external load_wav: file: string -> chunk = "sdlmixerstub_load_wav";;
external load_mus: file: string -> music = "sdlmixerstub_load_mus";;
external quick_load_wav: mem: byte_array -> chunk = "sdlmixerstub_quick_load_wav";;
external quick_load_raw: mem: byte_array -> chunk = "sdlmixerstub_quick_load_raw";;
external free_chunk: chunk: chunk -> unit = "sdlmixerstub_free_chunk";;
external free_music: music: music -> unit = "sdlmixerstub_free_music";;
external get_num_chunk_decoders: unit -> int = "sdlmixerstub_get_num_chunk_decoders";;
external get_chunk_decoder: int -> string = "sdlmixerstub_get_chunk_decoder";;
external get_num_music_decoders: unit -> int = "sdlmixerstub_get_num_music_decoders";;
external get_music_decoder: int -> string = "sdlmixerstub_get_music_decoder";;
external get_music_type: music: music -> music_type = "sdlmixerstub_get_music_type";;
external set_post_mix: mix_func: (byte_array -> unit) -> unit = "sdlmixerstub_set_post_mix";;

let channel_post: int = -2;;

type effect_func_t = int -> byte_array -> unit;;
type effect_done_t = int -> unit;;

external register_effect: chan: int -> f: effect_func_t -> d: effect_done_t -> unit = "sdlmixerstub_register_effect";;
external unregister_all_effects: channel: int -> unit = "sdlmixerstub_unregister_all_effects";;

let effects_max_speed: string = "MIX_EFFECTSMAXSPEED";;

external set_panning: channel: int -> left: int -> right: int -> unit = "sdlmixerstub_set_panning";;
external set_position: channel: int -> angle: int -> distance: int -> unit = "sdlmixerstub_set_position";;
external set_distance: channel: int -> distance: int -> unit = "sdlmixerstub_set_distance";;
external set_reverse_stereo: channel: int -> flip: bool -> unit = "sdlmixerstub_set_reverse_stereo";;
external reserve_channels: int -> int = "sdlmixerstub_reserve_channels";;
external group_channel: which: int -> tag: int -> unit = "sdlmixerstub_group_channel";;
external group_channels: from: int -> until: int -> tag: int -> unit = "sdlmixerstub_group_channels";;
external group_available: tag: int -> bool = "sdlmixerstub_group_available";;
external group_count: tag: int -> int = "sdlmixerstub_group_count";;
external group_oldest: tag: int -> int = "sdlmixerstub_group_oldest";;
external group_newer: tag: int -> int = "sdlmixerstub_group_newer";;
external play_channel_timed: channel: int -> chunk: chunk -> loops: int -> ticks: int -> int = "sdlmixerstub_play_channel_timed";;
external play_music: music: music -> loops: int -> int = "sdlmixerstub_play_music";;
external fade_in_music: music: music -> loops: int -> ms: int -> unit = "sdlmixerstub_fade_in_music";;
external fade_in_music_pos: music: music -> loops: int -> ms: int -> position: float -> unit = "sdlmixerstub_fade_in_music_pos";;
external fade_in_channel_timed: channel: int -> chunk: chunk -> loops: int -> ms: int -> ticks: int -> unit = "sdlmixerstub_fade_in_channel_timed";;
external volume: channel: int -> volume: int -> int = "sdlmixerstub_volume";;
external volume_chunk: chunk: chunk -> volume: int -> int = "sdlmixerstub_volume_chunk";;
external volume_music: volume: int -> int = "sdlmixerstub_volume_music";;
external halt_channel: channel: int -> unit = "sdlmixerstub_halt_channel";;
external halt_group: tag: int -> unit = "sdlmixerstub_halt_group";;
external halt_music: unit -> unit = "sdlmixerstub_halt_music";;
external expire_channel: channel: int -> ticks: int -> unit = "sdlmixerstub_expire_channel";;
external fade_out_channel: which: int -> ms: int -> unit = "sdlmixerstub_fade_out_channel";;
external fade_out_group: tag: int -> ms: int -> unit = "sdlmixerstub_fade_out_group";;
external fade_out_music: ms: int -> unit = "sdlmixerstub_fade_out_music";;
external fading_music: unit -> fading = "sdlmixerstub_fading_music";;
external fading_channel: which: int -> fading = "sdlmixerstub_fading_channel";;
external pause: channel: int -> unit = "sdlmixerstub_pause";;
external resume: channel: int -> unit = "sdlmixerstub_resume";;
external paused: channel: int -> bool = "sdlmixerstub_paused";;
external pause_music: unit -> unit = "sdlmixerstub_pause_music";;
external resume_music: unit -> unit = "sdlmixerstub_resume_music";;
external rewind_music: unit -> unit = "sdlmixerstub_rewind_music";;
external paused_music: unit -> bool = "sdlmixerstub_paused_music";;
external set_music_position: position: float -> unit = "sdlmixerstub_set_music_position";;
external playing: channel: int -> bool = "sdlmixerstub_playing";;
external playing_music: unit -> bool = "sdlmixerstub_playing_music";;
external set_music_cmd: command: string -> unit = "sdlmixerstub_set_music_cmd";;
external set_synchro_value: value: int -> unit = "sdlmixerstub_set_synchro_value";;
external get_synchro_value: unit -> int = "sdlmixerstub_get_synchro_value";;
external get_chunk: channel: int -> chunk = "sdlmixerstub_get_chunk";;
external close_audio: unit -> unit = "sdlmixerstub_close_audio";;

let play_channel ~(channel: int) ~(chunk: chunk) ~(loops: int): int = (
	play_channel_timed ~channel ~chunk ~loops ~ticks:(-1)
);;

let fade_in_channel ~(channel: int) ~(chunk: chunk) ~(loops: int) ~(ms: int): unit = (
	fade_in_channel_timed ~channel ~chunk ~loops ~ms ~ticks:(-1)
);;

