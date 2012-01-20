open Printf
open Sdl
module Mix = Sdl_mixer

(*
 * example of using SDL_mixer
 *
 * as this is also something like a live test, it attempts to use most of the features.
 * don't be scared, it's actually quite easy to use and follow.
 *
 *)


(* print something, finish it with newline and immediately flush output *)
(* I just hate to write \n%! too often. *)
let print_newlined s =
    printf "%s\n%!" s

(* printf-syntax blessed version of print_newlined *)
let p fmt = ksprintf print_newlined fmt

(* flatten list of strings using separator *)
let rec flatten l sep =
    match l with
    | [] -> ""
    | [x] -> x
    | h :: t -> h ^ sep ^ (flatten t sep)

let get_chunk_decoders () =
    let rec loop i rs =
        if i < 0 then rs else
        loop (i - 1) (Mix.get_chunk_decoder i :: rs)
    in
    loop (Mix.get_num_chunk_decoders () - 1) []

let get_music_decoders () =
    let rec loop i rs =
        if i < 0 then rs else
        loop (i - 1) (Mix.get_music_decoder i :: rs)
    in
    loop (Mix.get_num_music_decoders () - 1) []

let get_available_channel_count () = Mix.group_count ~tag:(-1)

let get_music_fading = Mix.fading_music

let get_channel_fading = Mix.fading_channel

let main () =

    Sdl.init [AUDIO];
    Mix.init [Mix.INIT_MP3; Mix.INIT_OGG];

    let major, minor, patch = Mix.linked_version () in
    p "SDL_mixer version %d.%d.%d" major minor patch;

    Mix.open_audio ~frequency:44100 ~format:Audio.S16 ~channels:2 ~chunksize:512;

    let decoders_chunk = get_chunk_decoders () in
    let decoders_music = get_music_decoders () in
    p "Chunk decoders: %s" (flatten decoders_chunk ", ");
    p "Music decoders: %s" (flatten decoders_music ", ");

    (* optional: allocate a bunch of channels *)
    let alloc_channels = 11 in
    p "Intially available %d channels" (get_available_channel_count ());
    p "Allocating %d channels" alloc_channels;
    p "Allocated: %d channels" (Mix.allocate_channels alloc_channels);
    p "Now available %d channels" (get_available_channel_count ());

    (* optional: reserve a bunch of channels for application *)

    let res_channels = 3 in
    p "Reserving %d channels" res_channels;
    p "Reserved: %d channels" (Mix.reserve_channels res_channels);

    (* load some music and sound *)

    let snd = Mix.load_wav "data/warning.wav" in
    let mus = Mix.load_mus "data/sample.xm" in

    (* fade in the music, start looping the sound on channel #2 *)

    p "Music %s playing" (
        try Mix.fade_in_music ~music:mus ~loops:(-1) ~ms:5000; "is" with
        | SDL_failure _ -> "NOT");
    p "Audio on channel %d" (Mix.play_channel ~channel:2 ~chunk:snd ~loops:(-1));

    (* optional: group the channels with tag (any number). In this case, tag = 2010 *)

    p "Grouping channels: %s" (
        try Mix.group_channel ~which:1 ~tag:2010; "ok" with
        | SDL_failure _ -> "failed");
    p "There is %d channel in group tagged 2010" (Mix.group_count 2010);



    p "Now playing: %s" (
        match Mix.get_music_type mus with
        | Mix.MUS_NONE -> "None"
        | Mix.MUS_CMD -> "CMD"
        | Mix.MUS_WAV -> "WAV"
        | Mix.MUS_MOD -> "MOD"
        | Mix.MUS_MID -> "MID"
        | Mix.MUS_OGG -> "OGG"
        | Mix.MUS_MP3 -> "MP3"
        | Mix.MUS_MP3_MAD -> "MP3_MAD"
        | Mix.MUS_FLAC -> "FLAC"
        | Mix.MUS_MODPLUG -> "MODPLUG"
    );

    p "Music is %s" (
        match get_music_fading () with
        | Mix.NO_FADING -> "not fading"
        | Mix.FADING_IN -> "fading in"
        | Mix.FADING_OUT -> "fading out"
    );

    p "Sound is %s" (
        match get_channel_fading 2 with
        | Mix.NO_FADING -> "not fading"
        | Mix.FADING_IN -> "fading in"
        | Mix.FADING_OUT -> "fading out"
    );
    p "Sound is %s" (
        if Mix.paused_music () then "paused" else "playing"
    );

    Mix.pause 2;
    p "Channel 2 is %s" (
        if Mix.paused 2 then "paused" else "playing"
    );

    Mix.resume 2;
    p "Channel 2 is %s" (
        if Mix.paused 2 then "paused" else "playing"
    );

    (* play around with panning / etc *)
    (* channel_post means that panning is a post-process effect and as a result will
     * be applied to all the sounds.
     *)

    ignore ( Mix.set_panning Mix.channel_post 255 0 );
    Unix.sleep 1;
    ignore ( Mix.set_panning Mix.channel_post 240 240 );
    Unix.sleep 1;
    ignore ( Mix.set_panning Mix.channel_post 0 255 );
    Unix.sleep 1;

    ignore ( Mix.set_panning Mix.channel_post 255 255 );
    Mix.halt_channel 1;

    Unix.sleep 2;

    Mix.halt_music ();

    Mix.free_chunk snd;
    Mix.free_music mus;

    Mix.quit ()

let _ = main ()
