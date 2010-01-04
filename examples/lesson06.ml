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
 

let int_array_make num =
	Bigarray.Array1.create Bigarray.int Bigarray.c_layout num

let texture = Array.make 1 0

let load_gl_textures () =
	let s = load_bmp "data/NeHe.bmp" in
	glGenTextures 1 texture;
	glBindTexture gl_texture_2d texture.(0);
	glTexParameteri gl_texture_2d gl_texture_mag_filter gl_linear; (* scale linearly when image bigger than texture *)
	glTexParameteri gl_texture_2d gl_texture_min_filter gl_linear; (* scale linearly when image smalled than texture *)
    (* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
     border 0 (normal), rgb color data, unsigned byte data, and finally the data itself. *)
	glTexImage2D gl_texture_2d 0 3 (surface_width s) (surface_height s) 0 gl_rgb gl_unsigned_byte (surface_pixels s)


(* A general OpenGL initialization function.  Sets all of the initial parameters. *)
let init_gl width height =
	glViewport 0 0 width height;
	glClearColor 0.0 0.0 0.0 0.0;
	glClearDepth 1.0;
	glDepthFunc gl_less;
	glEnable gl_depth_test;
	glEnable gl_texture_2d;
	load_gl_textures ();
	glShadeModel gl_smooth;
	glMatrixMode gl_projection;
	glLoadIdentity ();
	let aspect = (float_of_int width) /. (float_of_int height) in
	perspective 45.0 aspect 1.0 100.0;
	glMatrixMode gl_modelview
	
	
(* The main drawing function. *)
let xrot = ref 0.0
let yrot = ref 0.0 
let zrot = ref 0.0 
let draw_gl_scene () =
	
	glClear (gl_color_buffer_bit lor gl_depth_buffer_bit);
	glLoadIdentity ();

	glTranslatef 0.0 0.0 (-.5.0);              (* move 5 units into the screen. *) 

	glRotatef !xrot 1.0 0.0 0.0 ;		(* Rotate On The X Axis *)
	glRotatef !yrot 0.0 1.0 0.0 ;		(* Rotate On The Y Axis *)
	glRotatef !zrot 0.0 0.0 1.0 ;		(* Rotate On The Z Axis *)

	glBindTexture gl_texture_2d texture.(0);   (* choose the texture to use. *)

	glBegin gl_quads;		                (* begin drawing a cube *)

	(* Front Face (note that the texture's corners have to match the quad's corners) *)
	glTexCoord2f 0.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)   1.0 ;	(* Bottom Left Of The Texture and Quad *)
	glTexCoord2f 1.0  0.0 ; glVertex3f  1.0  (-.1.0)   1.0 ;	(* Bottom Right Of The Texture and Quad *)
	glTexCoord2f 1.0  1.0 ; glVertex3f  1.0   1.0   1.0 ;	(* Top Right Of The Texture and Quad *)
	glTexCoord2f 0.0  1.0 ; glVertex3f (-.1.0)   1.0   1.0 ;	(* Top Left Of The Texture and Quad *)

	(* Back Face *)
	glTexCoord2f 1.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)  (-.1.0) ;	(* Bottom Right Of The Texture and Quad *)
	glTexCoord2f 1.0  1.0 ; glVertex3f (-.1.0)   1.0  (-.1.0) ;	(* Top Right Of The Texture and Quad *)
	glTexCoord2f 0.0  1.0 ; glVertex3f  1.0   1.0  (-.1.0) ;	(* Top Left Of The Texture and Quad *)
	glTexCoord2f 0.0  0.0 ; glVertex3f  1.0  (-.1.0)  (-.1.0) ;	(* Bottom Left Of The Texture and Quad *)

	(* Top Face *)
	glTexCoord2f 0.0  1.0 ; glVertex3f (-.1.0)   1.0  (-.1.0) ;	(* Top Left Of The Texture and Quad *)
	glTexCoord2f 0.0  0.0 ; glVertex3f (-.1.0)   1.0   1.0 ;	(* Bottom Left Of The Texture and Quad *)
	glTexCoord2f 1.0  0.0 ; glVertex3f  1.0   1.0   1.0 ;	(* Bottom Right Of The Texture and Quad *)
	glTexCoord2f 1.0  1.0 ; glVertex3f  1.0   1.0  (-.1.0) ;	(* Top Right Of The Texture and Quad *)

	(* Bottom Face    *)    
	glTexCoord2f 1.0  1.0 ; glVertex3f (-.1.0)  (-.1.0)  (-.1.0) ;	(* Top Right Of The Texture and Quad *)
	glTexCoord2f 0.0  1.0 ; glVertex3f  1.0  (-.1.0)  (-.1.0) ;	(* Top Left Of The Texture and Quad *)
	glTexCoord2f 0.0  0.0 ; glVertex3f  1.0  (-.1.0)   1.0 ;	(* Bottom Left Of The Texture and Quad *)
	glTexCoord2f 1.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)   1.0 ;	(* Bottom Right Of The Texture and Quad *)

	(* Right face *)
	glTexCoord2f 1.0  0.0 ; glVertex3f  1.0  (-.1.0)  (-.1.0) ;	(* Bottom Right Of The Texture and Quad *)
	glTexCoord2f 1.0  1.0 ; glVertex3f  1.0   1.0  (-.1.0) ;	(* Top Right Of The Texture and Quad *)
	glTexCoord2f 0.0  1.0 ; glVertex3f  1.0   1.0   1.0 ;	(* Top Left Of The Texture and Quad *)
	glTexCoord2f 0.0  0.0 ; glVertex3f  1.0  (-.1.0)   1.0 ;	(* Bottom Left Of The Texture and Quad *)

	(* Left Face *)
	glTexCoord2f 0.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)  (-.1.0) ;	(* Bottom Left Of The Texture and Quad *)
	glTexCoord2f 1.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)   1.0 ;	(* Bottom Right Of The Texture and Quad *)
	glTexCoord2f 1.0  1.0 ; glVertex3f (-.1.0)   1.0   1.0 ;	(* Top Right Of The Texture and Quad *)
	glTexCoord2f 0.0  1.0 ; glVertex3f (-.1.0)   1.0  (-.1.0) ;	(* Top Left Of The Texture and Quad *)

	glEnd();                                    (* done with the polygon. *)

	xrot := !xrot +. 0.15;		                (* X Axis Rotation	 *)
	yrot := !yrot +. 0.15;		                (* Y Axis Rotation *)
	zrot := !zrot +. 0.15		                (* Z Axis Rotation *)

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
	set_caption "Jeff Molofee's GL Code Tutorial ... NeHe '99" "NeHe 06";
	init_gl w h;
	handle_events false;
	quit ()	


(* Program entry point *)
let _ = 
	try
		main ()
	with
		SDL_failure m -> failwith m
    
