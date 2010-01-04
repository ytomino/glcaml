open Sdl
open Video
open Event
open Printf


let rec handle_events quit =
    if not quit then begin
        let e = poll_event () in
		let bquit = 
        match e with
            | NoEvent -> false
            | Active appstate -> printf "ActiveEvent\n" ; false
            | Key k -> printf "Key %d\n" k.scancode ; false
            | Motion m -> printf "MouseMotion x=%d y=%d\n" m.mx m.my; false
            | Button b -> printf "MouseButton \n";
                match b.mousebutton with
                  |LEFT -> printf "left\n"
                  |RIGHT -> printf "right\n"
                  |MIDDLE -> printf "middle\n"
                  |WHEELUP -> printf "wheelup\n"
                  |WHEELDOWN -> printf "wheeldown\n";
                ; false
            | Jaxis ja -> printf "JoyAxis\n" ; false
            | Jball jball -> printf "JoyBall\n" ; false
            | Jhat jh -> printf "JoyHat\n" ; false
            | Jbutton jbut -> printf "JoyButton\n" ; false
            | Resize r -> printf "Resize\n" ; false
            | Quit -> printf "Quit\n" ; true
            | _ -> printf "Unknown match\n" ; false
		in
		flush stdout;
		handle_events bquit
    end
;;    


let main () =
    init [VIDEO];
    let w = 100 and h = 100 and bpp = 32 in
    let _ = set_video_mode w h bpp [SWSURFACE]in
    handle_events false
        
let _ = main ()    
