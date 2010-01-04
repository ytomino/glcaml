open Sdl
open Video
open Window
open Timer
open Event

(* 	Load an image and convert it to the current display format *)
let load_image bmp =
	let s1 = (load_bmp bmp) in
	let s2 = display_format s1 in
	free_surface s1;
	s2
	
(* 	Blit a source surface to a destination surface with offset (x,y) *)	
let apply_surface x y src dest =
	blit_surface src None dest (Some {rect_x = x; rect_y = y; rect_w = (surface_width src); rect_h = (surface_height src)})
	
(* Wait until a key is pressed or the window is closed *)	
let rec handle_events quit =
	if not quit then begin
		match poll_event () with
			| Key k -> handle_events true;
			| Quit ->  handle_events true;
      		| _ -> handle_events false
	end
	
	
(* 	Initialize SDL video
   	Create a 640x480x32 bpp window
   	Load the hello_world.bmp and background bmp
   	Set the window caption to "Hello World" and the icon (taskbar) title to "Goodbye world"
   	Blit the background bitmap to the screen
   	and blit the hello world bitmap at an offset over that.
   	Wait until a key is pressed, free bitmap surfaces and quit *)
let main () =
	init [VIDEO];
	let w = 640 and h = 480	and bpp = 32 in
	let screen = set_video_mode w h bpp [SWSURFACE] 
	and message = load_image "data/hello_world.bmp"
	and background = load_image "data/background.bmp" in
	set_caption "Hello world" "Goodbye world";
	apply_surface 0 0 background screen;
	apply_surface 180 140 message screen;
	flip screen;
	handle_events false;
	free_surface background;
	free_surface message;
	quit ()	


(* Program entry point *)
let _ = 
	try
		main ()
	with
		SDL_failure m -> failwith m
    
