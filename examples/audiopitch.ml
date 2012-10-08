open Sdl
open Sdl_audio
open Event


let sample_list = ref []

let pitch =  0.5

let mixaudio buf =
    let f s =
        match s with (sample, pos) ->
        let sample_left = (Bigarray.Array1.dim sample) - pos  in
        let buf_len = (Bigarray.Array1.dim buf) in
        if sample_left > buf_len then
        begin
    let new_buf_len = (int_of_float ((float_of_int buf_len) *. pitch)) in
    let newsample = fx_shift pitch (Bigarray.Array1.sub sample pos new_buf_len) in
                mix_audio buf newsample mix_maxvolume;
                (sample, pos + new_buf_len);
        end
        else
             (sample,0)
    in
    sample_list := List.map f !sample_list



let play_sound file =
    let a, buf = load_wav file in
    let sample = convert_audio a.format a.channels a.frequency S16 STEREO 22050 buf in
        sample_list := !sample_list @ [(sample, 0)]


(* Wait until a key is pressed or the window is closed *)
let rec handle_events quit =
  if not quit then begin
    match poll_event () with
      | Key k -> handle_events true;
      | Quit ->  handle_events true;
          | _ -> handle_events false
  end


let main() =
    let leave () =
        print_string ("Usage: " ^ Sys.argv.(0) ^ " <file.wav>");
        Sdl.quit ();
        ()
    in
    if Array.length Sys.argv < 2 then leave () else begin
        Sdl.init [Sdl.AUDIO];
        let _ = open_audio {frequency=22050; format=S16; channels=STEREO; silence = 0; samples=512; size=0} mixaudio in
            pause_audio false;
            for i = 1 to ((Array.length Sys.argv) - 1) do
                play_sound Sys.argv.(i);
            done;
            handle_events false;
            close_audio ();
    end


let _ = main ()

