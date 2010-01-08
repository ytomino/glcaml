(* SDLCaml, an Objective Caml interface for the SDL library *)
(* SDL_Mixer support module *)

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

open Sdl
open Audio

(** Initialization flags *)
type init_flag =
    | FLAC (** Initialize FLAC decoder *)
    | MOD  (** Initialize MOD  decoder (via mikmod library) *)
    | MP3  (** Initialize MP3 decoder *)
    | OGG  (** Initialize OGG decoder *)

(** Fading status query return codes *)
type fading_type =
    | NO_FADING
    | FADING_OUT
    | FADING_IN

(** Music type query return codes *)
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

(** Pointer-wrapped representation of audio chunk *)
type chunk_t

(** Pointer-wrapped representation of music file *)
type music_t

(** Channel number type. -1 usually corresponds to "all channels" or "any
    channel", depending on context. *)
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


(** Loads dynamic libraries and prepares them for use. *)
val init : init_flag list -> unit

(** Unloads libraries loaded by with Mix.init *)
val quit : unit -> unit


(** Retrieves a text representation of the used SDL_Mixer library, e.g 1.2.11 *)
val get_version : unit -> string 

(** Retrieves a string containing a description of most recent Mix error.
    Essentially the same as Sdl.get_error () *)
val get_last_error : unit -> string

(** [open_audio frequency format channels chunksize -> unit]
    Opens the mixer with certain audio format. *)
val open_audio : int -> Sdl.Audio.sample_type -> Sdl.Audio.channel_type -> int -> unit
val allocate_channels : int -> int

(** [load_wav file -> chunk_t]
    Load a wave file *)
val load_wav : string -> chunk_t

(** [load_mus file -> music_t]
    Load a music (.mod .s3m .it .xm) file *)
val load_mus : string -> music_t

(** [load_mus file -> music_t]
    Load a music (.mod .s3m .it .xm) file *)
val load_music : string -> music_t

(** Releases allocated sound chunk *)
val free_chunk : chunk_t -> unit 

(** Releases allocated music file *)
val free_music : music_t -> unit

(** [play_channel channel chunk loops -> channel]
   Plays an audio chunk on a specific channel.
   If specified channel is [Mix.first_available_channel] (-1), play on first free
   channel.
   If [loops] is greater than zero, loop the sound that many times.
   If [loops] is Mix.loop_forever (-1), loop infinitely (~65000 times?)
*)
val play_channel : channel -> chunk_t -> int -> channel

(** [play_channel_timed channel chunk loops ticks -> channel]
   Play an audio chunk on a specific channel for at most [ticks] seconds.
   If specified channel is [Mix.first_available_channel] (-1), play on first free
   channel.
   If [loops] is greater than zero, loop the sound that many times.
   If [loops] is Mix.loop_forever (-1), loop infinitely (~65000 times?)
*)

val play_channel_timed : channel -> chunk_t -> int -> int -> channel

(** [play_music music loops -> true/false]
   Play a music file (opened with [load_mus]) on a specific channel.
   If [loops] is greater than zero, loop the sound that many times.
   If [loops] is Mix.loop_forever (-1), loop infinitely (~65000 times?)
*)
val play_music : music_t -> int -> bool


(** Retrieves a list of formats supported for audio chunks. *)
val get_chunk_decoders : unit -> string list

(** Retrieves a list of formats supported for music files. *)
val get_music_decoders : unit -> string list

(** Retrieves currently playing music type if music = None.
    Retrieves a music type for the Some music_t *)
val get_music_type : music_t option -> music_type

(** [set_panning channel pan_left pan_right -> trye/false]
    Set the panning of a channel. The [pan_left] and [pan_right] channels are specified
    as integers between 0 and 255, quietest to loudest, respectively.
  
    Technically, this is just individual volume control for a sample with
    two (stereo) channels, so it can be used for more than just panning.
    If you want real panning, call it like this:
  
    Mix_SetPanning(channel, left, 255 - left);
  
    Setting [channel] to Mix.channel_post (-2) registers this as a posteffect, and
    the panning will be done to the final mixed stream before passing it on
    to the audio device.
  
    This uses the Mix_RegisterEffect() API internally, and returns without
    registering the effect function if the audio device is not configured
    for stereo output. Setting both (left) and (right) to 255 causes this
    effect to be unregistered, since that is the data's normal state.
  
    Note that an audio device in mono mode is a no-op, but this call will return
    success in that case.
    *)
val set_panning : channel -> int -> int -> bool

(** [set_position channel angle distance -> true/false]
    Set the position of a channel. [angle] is an integer from 0 to 360, that
    specifies the location of the sound in relation to the listener. [angle]
    will be reduced as neccesary (540 becomes 180 degrees, -100 becomes 260).
    Angle 0 is due north, and rotates clockwise as the value increases.
    For efficiency, the precision of this effect may be limited (angles 1
    through 7 might all produce the same effect, 8 through 15 are equal, etc).
    [distance] is an integer between 0 and 255 that specifies the space
    between the sound and the listener. The larger the number, the further
    away the sound is. Using 255 does not guarantee that the channel will be
    culled from the mixing process or be completely silent. For efficiency,
    the precision of this effect may be limited (distance 0 through 5 might
    all produce the same effect, 6 through 10 are equal, etc). Setting (angle)
    and [distance] to 0 unregisters this effect, since the data would be
    unchanged.
 
    If you need more precise positional audio, consider using OpenAL for
    spatialized effects instead of SDL_mixer. This is only meant to be a
    basic effect for simple "3D" games.
 
    If the audio device is configured for mono output, then you won't get
    any effectiveness from the angle; however, distance attenuation on the
    channel will still occur. While this effect will function with stereo
    voices, it makes more sense to use voices with only one channel of sound,
    so when they are mixed through this effect, the positioning will sound
    correct. You can convert them to mono through SDL before giving them to
    the mixer in the first place if you like.
 
    Setting [channel] to Mix.channel_post (-2) registers this as a posteffect, and
    the positioning will be done to the final mixed stream before passing it
    on to the audio device.
 
    This is a convenience wrapper over Mix_SetDistance() and Mix_SetPanning().
*)
val set_position : channel -> int -> int -> bool

(** [set_distance channel distance -> true/false]
    Set the "distance" of a channel. [distance] is an integer from 0 to 255
    that specifies the location of the sound in relation to the listener.
    Distance 0 is overlapping the listener, and 255 is as far away as possible
    A distance of 255 does not guarantee silence; in such a case, you might
    want to try changing the chunk's volume, or just cull the sample from the
    mixing process with Mix_HaltChannel().

    For efficiency, the precision of this effect may be limited (distances 1
    through 7 might all produce the same effect, 8 through 15 are equal, etc).
    [distance] is an integer between 0 and 255 that specifies the space
    between the sound and the listener. The larger the number, the further
    away the sound is.

    Setting [distance] to 0 unregisters this effect, since the data would be
    unchanged.

    If you need more precise positional audio, consider using OpenAL for
    spatialized effects instead of SDL_mixer. This is only meant to be a
    basic effect for simple "3D" games.

    Setting [channel] to Mix.channel_post (-2) registers this as a posteffect, and
    the distance attenuation will be done to the final mixed stream before
    passing it on to the audio device.

 *)
val set_distance : channel -> int -> bool


(** [set_reverse_stereo channel flip -> true/false]
    Causes a channel to reverse its stereo. This is handy if the user has his
    speakers hooked up backwards, or you would like to have a minor bit of
    psychedelia in your sound code.  :)  Calling this function with [flip]
    set to non-zero reverses the chunks's usual channels. If [flip] is zero,
    the effect is unregistered.

    This uses the Mix_RegisterEffect() API internally, and thus is probably
    more CPU intensive than having the user just plug in his speakers
    correctly. Mix_SetReverseStereo() returns without registering the effect
    function if the audio device is not configured for stereo output.

    If you specify Mix.channel_post (-2) for [channel], then this the effect is used
    on the final mixed stream before sending it on to the audio device (a
    posteffect).

     Note that an audio device in mono mode is a no-op, but this call will
     return successful in that case. 
*)
val set_reverse_stereo : channel -> bool -> bool

(** [reserve_channels n -> n_reserved]
    Reserve the first channels (0..n-1) for the application: Don't allocate them
    dynamically for the next sample if requested with a
    [Mix.first_available_channel] (-1).
    *)
val reserve_channels : int -> int

(** [group_channel channel tag -> true/false]
    Attach a tag to a channel. A tag can e assigned to several mixer channels to
    for groups of channels.

    If [tag] = -1, the tag is removed, but better use [ungroup_channel] instead.
    *)
val group_channel : channel -> int -> bool

(** [group_channels first_channel last_channel tag -> true/false]
    Attach a tag to a range of consecutive channels.

    If [tag] = -1, the tag is removed, but better use [ungroup_channels] instead.
    *)
val group_channels : channel -> channel -> int -> bool

(** [ungroup_channel channel -> true/false]
    Remove a tag from the channel. *)
val ungroup_channel : channel -> bool

(** [ungroup_channels first_channel last_channel -> true/false]
    Remove a tag from the range of channels. *)
val ungroup_channels : channel -> channel -> bool

(** [group_available tag -> channel]
    Finds the first available channel in a group of channels.
    Returns -1 if none are available. *)
val group_available : int -> channel

(** [group_count tag -> n ]
    Returns the number of channels in a group. *)
val group_count : int -> int

(** Returns the total number of available channels. *)
val get_available_channel_count : unit -> int

(** [group_oldest tag -> channel]
    Returns the "oldest" sample playng in a group of channels. *)
val group_oldest : int -> channel

(** [group_newer tag -> channel]
    Returns the "newer" (last) sample playng in a group of channels. *)
val group_newer : int -> channel

(** [fade_in_music music_t loops ms -> true/false]
    Fades in music over [ms] milliseconds. See [play_music].
    *)
val fade_in_music : music_t -> int -> int -> bool

(** [fade_in_music_pos music_t loops ms position -> true/false]
    Fades in music over [ms] milliseconds, starting with exact position. See [play_music].
    *)
val fade_in_music_pos : music_t -> int -> int -> float -> bool

(** [fade_in_channel channel chunk loops ms -> true/false]
    Fades in channel / audio chunk over [ms] milliseconds. See [play_channel].
    *)
val fade_in_channel : channel -> chunk_t -> int -> int -> channel

(** [fade_in_channel_timed channel chunk loops ms ticks -> true/false]
    Fades in channel / audio chunk over [ms] milliseconds, for at most [ticks]
    milliseconds.. See [play_channel_timed]
    *)
val fade_in_channel_timed : channel -> chunk_t -> int -> int -> int -> channel

(** [volume channel volume -> previous_volume]
    Sets a volume (0..128) for the specified channel. *)
val volume : channel -> int -> int

(** [set_volume channel volume -> previous_volume]
    Sets a volume (0..128) for the specified channel. *)
val set_volume : channel -> int -> int

(** Retrieves current volume of the channel. *)
val get_volume : channel -> int

(** [volume_chunk chunk volume -> previous_volume]
    Sets a volume (0..128) for the specified audio chunk. *)
val volume_chunk : chunk_t -> int -> int

(** [set_chunk_volume chunk volume -> previous_volume]
    Sets a volume (0..128) for the specified audio chunk. *)
val set_chunk_volume : chunk_t -> int -> int

(** Retrieves current volume of the audio chunk. *)
val get_chunk_volume : chunk_t -> int

(** [volume_music volume -> previous_volume]
    Sets a volume (0..128) for the playing music. *)
val volume_music : int -> int

(** [set_music_volume volume -> previous_volume]
    Sets a volume (0..128) for the playing music. *)
val set_music_volume : int -> int

(** Retrieves the volume of currently playing music. *)
val get_music_volume : unit -> int


(** Halts playing of the specified channel. *)
val halt_channel : channel -> unit

(** [halt_group tag]
    Halts playing of the specified channel group. *)
val halt_group : int -> unit

(** Halts playing the music. *)
val halt_music : unit -> unit

(** [expire_channel channel ticks -> true/false]
    Changes the expiration delay for a particluar channel.

    The sample will stop playing after the [ticks] milliseconds have elapsed.
    *)
val expire_channel : channel -> int -> bool

(** [expire_channel channel -> true/false]
    Removes the expiration time for a particular channel.
    *)
val remove_channel_expiration : channel -> bool

(** [fade_out_channel channel ms -> true/false]
    Halts the channel, fading it out till it's silent. 
    The fading will take [ms] milliseconds.*)
val fade_out_channel : channel -> int -> bool

(** [fade_out_group tag ms -> true/false]
    Halts the channel group, fading it out till it's silent. 
    The fading will take [ms] milliseconds.*)
val fade_out_group : int -> int -> bool

(** [fade_out_music ms -> true/false]
    Halts the music, fading it out till it's silent. 
    The fading will take [ms] milliseconds.*)
val fade_out_music : int -> bool

(** Queries the fading status of the music. *)
val fading_music : unit -> fading_type

(** Queries the fading status of the specified channel. *)
val fading_channel : channel -> fading_type

(** Queries the fading status of the music. *)
val get_music_fading : unit -> fading_type

(** Queries the fading status of the specified channel. *)
val get_channel_fading : channel -> fading_type

(** Pauses the specified channel. *)
val pause : channel -> unit

(** Resumes a playback of the specified channel. *)
val resume : channel -> unit

(** Queries the pause state of the specified channel. *)
val paused : channel -> bool

(** Pauses the music. *)
val pause_music : unit -> unit

(** Resumes the music playback. *)
val resume_music : unit -> unit

(** Restarts the music playback from the beginning. *)
val rewind_music : unit -> unit

(** Queries whether the music is currently paused. *)
val paused_music : unit -> bool


(** [set_music_position pos -> true/false]
    Sets the current position in the music stream.
    This function is rumored to be implemented only for OGG and MOD music
    formats. *)
val set_music_position : float -> bool

(** Queries whether the channel is currently playing. *)
val playing : channel -> bool

(** Queries whether the music is currently playing. *)
val playing_music : unit -> bool

(** Stops music and sets external music playback command. *)
val set_music_cmd : string -> bool

(** Retrieves the chunk_t currently associated with the specified mixer channel.
    TODO: this probably messes up when the channel is invalid or there is no
    chunk associated (Mix_GetChunk returns NULL), and should return [chunk_t option] instead.
   *)
val get_chunk : channel -> chunk_t

(** Closes the mixer, halting all playing audio. *)
val close_audio : unit -> unit

end

(**
	{b Acknowledgements, license and copyright}
	
	SDLCaml
	
    Modifications 2010 Einar Lielmanis, einars@gmail.com

	Source code, additions and modifications 2006 - 2008  Elliott OTI 
	
	Copyright (C) 2006 - 2008 Elliott OTI
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License version 2, as published by the Free Software Foundation.
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU Library General Public License version 2 for more details
	(enclosed in the file LGPL). 
	
	{b Credits}
	
	Parts of the documentation reproduced verbatim or in altered form 
	from the libsdl documentation (http://www.libsdl.org)
	
	Portions of modules Sdl, Video, SDLGL, Timer and Draw are based on code by Jean-Christophe Filliatre.
	
	Copyright (C) 1999 Jean-Christophe FILLIATRE:
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License version 2, as published by the Free Software Foundation.
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU Library General Public License version 2 for more details
	(enclosed in the file LGPL). 
	
	The Event module contains code from the camlgl distribution (http://camlgl.sourceforge.net):
	
	(C) 2001-2002 Nickolay Kolchin-Semyonov
	
	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.
	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:
	
	1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgment in the product documentation would be
	 appreciated but is not required.
	
	2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.
	
	3. This notice may not be removed or altered from any source distribution.
	
	Nickolay Kolchin-Semyonov
	
	snob\@snob.spb.ru 
*)
