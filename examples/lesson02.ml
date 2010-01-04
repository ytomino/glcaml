open Sdl
open Video
open Window
open Timer
open Event
open SDLGL
open Glcaml

let perspective fov aspect zNear zFar =
	let pi = 4.0 *. (atan 1.0) in
	let fH = (tan (fov /. 360.0 *. pi )) *. zNear in
	let fW = fH *. aspect in 
	glFrustum (-.fW) fW (-.fH) fH zNear zFar 
	
	
(* A general OpenGL initialization function.  Sets all of the initial parameters. *)
let init_gl width height =
	glViewport 0 0 width height;
	glClearColor 0.0 0.0 0.0 0.0;
	glClearDepth 1.0;
	glDepthFunc gl_less;
	glEnable gl_depth_test;
	glShadeModel gl_smooth;
	glMatrixMode gl_projection;
	glLoadIdentity ();
	let aspect = (float_of_int width) /. (float_of_int height) in
	perspective 45.0 aspect 1.0 100.0;
	glMatrixMode gl_modelview
	
(* The main drawing function. *)
let draw_gl_scene () =
	glClear (gl_color_buffer_bit lor gl_depth_buffer_bit); 
	glLoadIdentity ();

	glTranslatef (-.1.5) 0.0 (-.6.0);
	(* draw a triangle *)
	glBegin gl_triangles;				
	glVertex3f  0.0 1.0 0.0;		
	glVertex3f 1.0 (-.1.0) 0.0;		
	glVertex3f (-.1.0) (-.1.0) 0.0;			
	glEnd ();	
					
	glTranslatef 3.0 0.0 0.0;		        (* Move Right 3 Units *)
	(* draw a square (quadrilateral) *)
	glBegin gl_quads;				
	glVertex3f (-.1.0) 1.0 0.0;		
	glVertex3f 1.0 1.0 0.0;		
	glVertex3f 1.0 (-.1.0) 0.0;		
	glVertex3f (-.1.0)(-.1.0) 0.0;		
	glEnd ()

(* Wait until a key is pressed or the window is closed *)	
let rec handle_events quit =
	draw_gl_scene (); 
	swap_buffers ();
	if not quit then begin
		match poll_event () with
			| Key k -> handle_events false;
			| Quit ->  handle_events true;
      		| _ -> handle_events false;
	end
	



let main () =
	init [VIDEO];
	let w = 640 and h = 480	and bpp = 32 in
	let _ = set_video_mode w h bpp [OPENGL] in
	set_caption "Jeff Molofee's GL Code Tutorial ... NeHe '99" "NeHe 02";
	init_gl w h;
	swap_buffers () ;
	handle_events false;
	quit ()	


(* Program entry point *)
let _ = 
	try
		main ()
	with
		SDL_failure m -> failwith m
    
