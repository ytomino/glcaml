open Printf
open Sdl
open Sdl_mixer

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


let main () =

    Sdl.init [AUDIO];
    Mix.init [MP3; OGG];

    p "SDL_mixer version %s" (Mix.get_version ());

    Mix.open_audio 44100 Audio.S16 Audio.STEREO 512;

    let decoders_chunk = Mix.get_chunk_decoders () in
    let decoders_music = Mix.get_music_decoders () in
    p "Chunk decoders: %s" (flatten decoders_chunk ", ");
    p "Music decoders: %s" (flatten decoders_music ", ");

    (* optional: allocate a bunch of channels *)
    let alloc_channels = 11 in 
    p "Intially available %d channels" (Mix.get_available_channel_count ());
    p "Allocating %d channels" alloc_channels;
    p "Allocated: %d channels" (Mix.allocate_channels alloc_channels);
    p "Now available %d channels" (Mix.get_available_channel_count ());

    (* optional: reserve a bunch of channels for application *)

    let res_channels = 3 in
    p "Reserving %d channels" res_channels;
    p "Reserved: %d channels" (Mix.reserve_channels res_channels);

    (* load some music and sound *)

    let snd = Mix.load_wav "data/warning.wav" in
    let mus = Mix.load_music "data/sample.xm" in

    (* fade in the music, start looping the sound on channel #2 *)

    p "Music %s playing" (if Mix.fade_in_music mus Mix.loop_forever 5000 then "is" else "NOT");
    p "Audio on channel %d" (Mix.play_channel 2 snd Mix.loop_forever);

    (* optional: group the channels with tag (any number). In this case, tag = 2010 *)

    p "Grouping channels: %s" (if Mix.group_channel 1 2010 then "ok" else "failed");
    p "There is %d channel in group tagged 2010" (Mix.group_count 2010);



    p "Now playing: %s" (
        match Mix.get_music_type None with
        | MUS_NONE -> "None"
        | MUS_CMD -> "CMD"
        | MUS_WAV -> "WAV"
        | MUS_MOD -> "MOD"
        | MUS_MID -> "MID"
        | MUS_OGG -> "OGG"
        | MUS_MP3 -> "MP3"
        | MUS_MP3_MAD -> "MP3_MAD"
        | MUS_FLAC -> "MP3_MAD"
    );

    p "Music is %s" (
        match Mix.get_music_fading () with
        | NO_FADING -> "not fading"
        | FADING_IN -> "fading in"
        | FADING_OUT -> "fading out"
    );

    p "Sound is %s" (
        match Mix.get_channel_fading 2 with
        | NO_FADING -> "not fading"
        | FADING_IN -> "fading in"
        | FADING_OUT -> "fading out"
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
