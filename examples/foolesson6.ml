open Sdl
open Video
open Window
open Timer
open Event

(* 	Load an image and convert it to the current display format 
	Set the color keying for the image to RGB(0 255 255) *)
let load_image bmp =
	let s1 = (load_bmp bmp) in
	let s2 = display_format s1 in
	let colorkey = map_rgb s2 0 255 255 in
	set_color_key s2 [RLEACCEL; SRCCOLORKEY] colorkey;
	free_surface s1;
	s2
	
(* 	Blit a source surface to a destination surface with offset (x,y) *)	
let apply_surface x y src dest clip =
	blit_surface src clip dest (Some {rect_x = x; rect_y = y; rect_w = (surface_width src); rect_h = (surface_height src)});;
	
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
   	Load dots.bmp and background bmp
   	Set the window caption to "Split the dots" and the icon (taskbar) title to "Lesson 6"
   	Blit the background bitmap to the screen
   	and blit clipped subrectangles of foo.bmp at various offsets over that.
   	Wait until a key is pressed, free bitmap surfaces and quit *)
let main () =
	init [VIDEO];
	let w = 640 and h = 480	and bpp = 32 in
	let screen = set_video_mode w h bpp [SWSURFACE] 
	and dots = load_image "data/dots.bmp"
	and background = load_image "data/background.bmp" in
	set_caption "Split the dots" "Lesson 6";
	apply_surface 0 0 background screen None;
	apply_surface 0 0 dots screen (Some {rect_x = 0; rect_y = 0; rect_w = 100; rect_h = 100});
	apply_surface 540 0 dots screen (Some {rect_x = 100; rect_y = 0; rect_w = 100; rect_h = 100});
	apply_surface 0 380 dots screen (Some {rect_x = 0; rect_y = 100; rect_w = 100; rect_h = 100});
	apply_surface 540 380 dots screen (Some {rect_x = 100; rect_y = 100; rect_w = 100; rect_h = 100});
	flip screen;
	handle_events false;
	free_surface background;
	free_surface dots;
	quit ()	


(* Program entry point *)
let _ = 
	try
		main ()
	with
		SDL_failure m -> failwith m
    
