open Sdl
open Video
open Window
open Timer
open Event
open Draw
open Int32


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
let apply_surface x y src dest =
	blit_surface src None dest (Some {rect_x = x; rect_y = y; rect_w = (surface_width src); rect_h = (surface_height src)})
	

let main () =
	init [VIDEO];
	let w = 640 and h = 480	and bpp = 32 in
	let screen = set_video_mode w h bpp [SWSURFACE]  
	and background = load_bmp "data/background.bmp" 
	and foo = load_tga "data/parafont.tga" 
	in
	set_caption "Test TGA" "Test TGA";
	let fnt = make_sfont foo in 
	let display s =
		apply_surface 0 0 background screen;  
		sfont_print s 2 2 fnt screen; 
		flip screen 
	in
	display "Press any key"; 
(* Wait until a key is pressed or the window is closed *)
	let rec handle_events quit=
		if not quit then begin
			let keyst k = if k = PRESSED then "Pressed" else "Released" in
			let prkeybd k = 
				let s = Printf.sprintf "%s\nscan=%d\nkey=%s\nunicode=%d" (keyst k.keystate) k.scancode (get_key_name k.sym) k.unicode in
				display s 
			in
			match poll_event () with
			| Key k -> prkeybd k; handle_events false;
			| Quit ->  handle_events true;
	      		| _ -> handle_events false;
		end
		in
		handle_events false;
	free_surface foo;
	quit ()	



(* Program entry point *)
let _ = 
	try
		main ()
	with
		SDL_failure m -> failwith m
    
