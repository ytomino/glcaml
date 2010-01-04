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
let rtri = ref 0.0
let rquad = ref 0.0 
let draw_gl_scene () =
	glClear (gl_color_buffer_bit lor gl_depth_buffer_bit);
	glLoadIdentity ();
	glTranslatef (-.1.5) 0.0 (-.6.0);
	glRotatef !rtri 0.0 1.0 0.0;
	
	(* draw a pyramid (in smooth coloring mode) *)
	glBegin gl_triangles;				(* start drawing a pyramid *)
	
	(* front face of pyramid *)
	glColor3f 1.0 0.0 0.0;			(* Set The Color To Red *)
	glVertex3f 0.0  1.0  0.0;		        (* Top of triangle (front) *)
	glColor3f 0.0 1.0 0.0;			(* Set The Color To Green *)
	glVertex3f (-.1.0) (-.1.0)  1.0;		(* left of triangle (front) *)
	glColor3f 0.0 0.0 1.0;			(* Set The Color To Blue *)
	glVertex3f 1.0 (-.1.0)  1.0;		        (* right of traingle (front) *)	
	
	(* right face of pyramid*)
	glColor3f 1.0 0.0 0.0;			(* Red *)
	glVertex3f  0.0  1.0  0.0;		(* Top Of Triangle (Right) *)
	glColor3f 0.0 0.0 1.0;			(* Blue *)
	glVertex3f  1.0 (-.1.0)  1.0;		(* Left Of Triangle (Right) *)
	glColor3f 0.0 1.0 0.0;			(* Green *)
	glVertex3f  1.0 (-.1.0)  (-.1.0);		(* Right Of Triangle (Right) *)
	
	(* back face of pyramid*)
	glColor3f 1.0 0.0 0.0;			(* Red *)
	glVertex3f  0.0  1.0  0.0;		(* Top Of Triangle (Back) *)
	glColor3f 0.0 1.0 0.0;			(* Green *)
	glVertex3f  1.0 (-.1.0)  (-.1.0);		(* Left Of Triangle (Back) *)
	glColor3f 0.0 0.0 1.0;			(* Blue *)
	glVertex3f (-.1.0) (-.1.0)  (-.1.0);		(* Right Of Triangle (Back) *)
	
	(* left face of pyramid.*)
	glColor3f 1.0 0.0 0.0;			(* Red *)
	glVertex3f  0.0  1.0  0.0;		(* Top Of Triangle (Left) *)
	glColor3f 0.0 0.0 1.0;			(* Blue *)
	glVertex3f (-.1.0) (-.1.0) (-.1.0);		(* Left Of Triangle (Left) *)
	glColor3f 0.0 1.0 0.0;			(* Green *)
	glVertex3f (-.1.0) (-.1.0)  1.0;		(* Right Of Triangle (Left) *)
	
	glEnd();					(* Done Drawing The Pyramid *)
	
	glLoadIdentity();				(* make sure we're no longer rotated. *)
	glTranslatef 1.5 0.0 (-.7.0);		(* Move Right 3 Units  and back into the screen 7 *)
	
	glRotatef !rquad 1.0 1.0 1.0;		(* Rotate The Cube On X  Y  and Z *)
	
	(* draw a cube (6 quadrilaterals) *)
	glBegin gl_quads;				(* start drawing the cube. *)
	
	(* top of cube *)
	glColor3f 0.0 1.0 0.0;			(* Set The Color To Blue *)
	glVertex3f  1.0  1.0 (-.1.0);		(* Top Right Of The Quad (Top) *)
	glVertex3f (-.1.0)  1.0 (-.1.0);		(* Top Left Of The Quad (Top) *)
	glVertex3f (-.1.0)  1.0  1.0;		(* Bottom Left Of The Quad (Top) *)
	glVertex3f  1.0  1.0  1.0;		(* Bottom Right Of The Quad (Top) *)
	
	(* bottom of cube *)
	glColor3f 1.0 0.5 0.0;			(* Set The Color To Orange *)
	glVertex3f  1.0 (-.1.0)  1.0;		(* Top Right Of The Quad (Bottom) *)
	glVertex3f (-.1.0) (-.1.0)  1.0;		(* Top Left Of The Quad (Bottom) *)
	glVertex3f (-.1.0) (-.1.0) (-.1.0);		(* Bottom Left Of The Quad (Bottom) *)
	glVertex3f  1.0 (-.1.0) (-.1.0);		(* Bottom Right Of The Quad (Bottom) *)
	
	(* front of cube *)
	glColor3f 1.0 0.0 0.0;			(* Set The Color To Red *)
	glVertex3f  1.0  1.0  1.0;		(* Top Right Of The Quad (Front) *)
	glVertex3f (-.1.0)  1.0  1.0;		(* Top Left Of The Quad (Front) *)
	glVertex3f (-.1.0) (-.1.0)  1.0;		(* Bottom Left Of The Quad (Front) *)
	glVertex3f  1.0 (-.1.0)  1.0;		(* Bottom Right Of The Quad (Front) *)
	
	(* back of cube. *)
	glColor3f 1.0 1.0 0.0;			(* Set The Color To Yellow *)
	glVertex3f  1.0 (-.1.0) (-.1.0);		(* Top Right Of The Quad (Back) *)
	glVertex3f (-.1.0) (-.1.0) (-.1.0);		(* Top Left Of The Quad (Back) *)
	glVertex3f (-.1.0)  1.0 (-.1.0);		(* Bottom Left Of The Quad (Back) *)
	glVertex3f  1.0  1.0 (-.1.0);		(* Bottom Right Of The Quad (Back) *)
	
	(* left of cube *)
	glColor3f 0.0 0.0 1.0;			(* Blue *)
	glVertex3f (-.1.0)  1.0  1.0;		(* Top Right Of The Quad (Left) *)
	glVertex3f (-.1.0)  1.0 (-.1.0);		(* Top Left Of The Quad (Left) *)
	glVertex3f (-.1.0) (-.1.0) (-.1.0);		(* Bottom Left Of The Quad (Left) *)
	glVertex3f (-.1.0) (-.1.0)  1.0;		(* Bottom Right Of The Quad (Left) *)
	
	(* Right of cube *)
	glColor3f 1.0 0.0 1.0;			(* Set The Color To Violet *)
	glVertex3f  1.0  1.0 (-.1.0);	        (* Top Right Of The Quad (Right) *)
	glVertex3f  1.0  1.0  1.0;		(* Top Left Of The Quad (Right) *)
	glVertex3f  1.0 (-.1.0)  1.0;		(* Bottom Left Of The Quad (Right) *)
	glVertex3f  1.0 (-.1.0) (-.1.0);		(* Bottom Right Of The Quad (Right) *)
	glEnd();					(* Done Drawing The Cube *)
	
	
	rtri  := !rtri +. 0.15;
	rquad := !rquad +. 0.15
						

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
	handle_events false;
	quit ()	


(* Program entry point *)
let _ = 
	try
		main ()
	with
		SDL_failure m -> failwith m
    
