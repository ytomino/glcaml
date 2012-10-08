(* ------------------------------------------- Audio.------------------------------------------------- *)
(** Low-level audio *)

open Sdl

(** Type of sample *)
type sample_type = Audio.sample_type =
  | U8    (** 8 bits unsigned *)
  | S8    (** 8 bits signed *)
  | U16   (** 16 bits unsigned *)
  | S16   (** 16 bits signed *)
  | U16LSB  (** 16 bits unsigned least-significant-bit first*)
  | S16LSB  (** 16 bits signed least-significant-bit first*)
  | U16MSB  (** 16 bits unsigned most-significant-bit first *)
  | S16MSB  (** 16 bits signed most-significant-bit first *)

type channel_type = Audio.channel_type =
  | MONO      (** Mono channel *)
  | STEREO  (** Stereo channel *)

(** Status of the audio device *)
type audio_status =
  | STOPPED (** Device has been stopped *)
  | PAUSED  (** Device has been paused *)
  | PLAYING   (** Device is currently playing *)
  | UNKNOWN (** Device state is unknown *)

(** The [audio_spec] structure is used to describe the format of some audio data.
  This structure is used by [open_audio] and [load-wav].
  While all fields are used by [open_audio] only freq, format, samples and channels are used by [load_wav]. *)
type audio_spec = {
  frequency: int;     (** The number of samples sent to the sound device every second. Common values are 11025, 22050 and 44100. The higher the better. *)
  format: sample_type;  (** Specifies the size and type of each sample element *)
  channels: channel_type; (** The number of seperate sound channels *)
  silence: int;
  samples: int;       (** When used with [open_audio] this refers to the size of the audio buffer in samples. A sample a chunk of audio data of the size specified in format mulitplied by the number of channels. When the [audio_spec] is used with [load-wav] samples is set to 4096.  *)
  size: int;
}

  val int_of_sampletype : sample_type -> int (* internal-ish *)
  val int_of_channel : channel_type -> int  (* internal-ish *)

(** The maximum sample mixer volume. Volume ranges from 0 (silence) to mix_maxvolume *)
val mix_maxvolume   : int

(** [open_audio desired_audio_spec mixer_callback -> obtained audio_spec ]
  This function opens the audio device with the [desired] parameters, and returns the [obtained] parameters,
  placing the actual hardware parameters in the structure pointed to by [obtained]. *)
val open_audio : audio_spec -> (byte_array -> unit) -> audio_spec

(** [close_audio] closes the audio device *)
val close_audio : unit -> unit

(** [load_wav filename -> obtained audio_spec * wav_buffer]
  This function loads a WAVE file into memory.
  If this function succeeds, it returns the given [audio-spec], filled with the audio data format of
  the wave data, and sets wav_buffer to a C-malloc'd buffer containing the audio data,
  You need to free the audio buffer with [free-wav] when you are done with it.
  This function sets the SDL error message if the wave file cannot be opened,
  uses an unknown data format, or is corrupt. Currently raw, MS-ADPCM and IMA-ADPCM WAVE files are supported. *)
val load_wav : string -> audio_spec * byte_array

(** [free_wav wav_buffer]
  Frees a WAV buffer allocated by load-wav *)
val free_wav : byte_array -> unit

(** [pause_audio on\off]
  Toggle audio playback on and off *)
val pause_audio : bool -> unit

(** The lock manipulated by these functions protects the callback function.
  During a [lock_audio] period, you can be guaranteed that the callback function is not running.
  Do not call these from the callback function or you will cause deadlock. *)
val lock_audio : unit -> unit

(** Unlocks a previous [lock_audio] call.*)
val unlock_audio : unit -> unit

(** [mix_audio buffer1 buffer2  volume]
  This function takes two audio buffers of len bytes each of the playing audio format and mixes them,
  performing addition, volume adjustment, and overflow clipping.
  The volume ranges from 0 to [mix_maxvolume] and should be set to the maximum value for full audio volume.
  Note this does not change hardware volume. This is provided for convenience -- you can mix your own audio data.
  Note: Do not use this function for mixing together more than two streams of sample data.
  The output from repeated application of this function may be distorted by clipping, because there is no
  accumulator with greater range than the input (not to mention this being an inefficient way of doing it).
  Use mixing functions from SDL_mixer, OpenAL, or write your own mixer instead. *)
val mix_audio :  byte_array -> byte_array  -> int -> unit

(** [get_audio_status -> audio_status]
  Returns either [STOPPED], [PAUSED] or [PLAYING] depending on the current audio status *)
val get_audio_status : unit -> audio_status

(** [convert_audio from_format from_channels from_frequency to_format to_channels to_frequency input_buffer -> output_buffer]
  Converts an audio sample in [input_buffer] of sample type [from_format], number of channels [from_channels], and sample frequency [from_frequency]
  to sample type [to_format], number of channels [to_channels], and sample frequency [to_frequency]
  The converted samples are returned in [output_buffer] *)
val convert_audio : sample_type -> channel_type -> int -> sample_type -> channel_type -> int -> byte_array -> byte_array

(** [fx_pan  pan volume input_buffer  -> output_buffer]
  This is an auxiliary, non core SDL mixing function.  It takes an input sample in [input_buffer]
  and pans it (or more accurately, adjusts the balance) according to the value of [pan] which lies in the range \[-1.0 - 1.0 \].
  A value of -1.0 means that the sound will be coming exclusively from the left speaker, a value of 0.0
  means that the sound will come equally from both speakers, and 1.0 means that the sound will come exclusively from
  the right speaker. The panned sample will be placed in the [output_buffer].
  [volume] sets the volume for the output buffer *)
val fx_pan : float -> float -> byte_array -> byte_array

(** [fx_shift : frequency_shift input_buffer -> output_buffer]
  This is an auxiliary, non core SDL mixing function.  It takes an input sample in [input_buffer] and shifts its frequency.
  [frequency_shift] determines the frequency shift. A value of 1.0 leaves the frequency unchanged, a value between 0.1 and 1.0
  lowers the frequency and a value between 1.0 and 10.0 raises the frequency. Shifts are capped in the range \[0.1 - 10.0\].
  The frequency shifted sound is placed in [output_buffer] *)
val fx_shift : float -> byte_array -> byte_array
