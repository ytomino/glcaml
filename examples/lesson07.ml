open Sdl
open Video
open Window
open Timer
open Event
open SDLGL
open Draw
open Glcaml

let perspective fov aspect zNear zFar =
	let pi = 4.0 *. (atan 1.0) in
	let fH = (tan (fov /. 360.0 *. pi )) *. zNear in
	let fW = fH *. aspect in
	glFrustum (-.fW) fW (-.fH) fH zNear zFar;;

let opengl_mipmaps s filter =
	let mipmaps = make_mipmaps s filter in
	let len = Array.length mipmaps in
	let bpp = (surface_bpp mipmaps.(0)) in
	let c, rgba = if ((bpp = 15) || (bpp = 32)) then 4, gl_rgba else 3, gl_rgb in
	glPixelStorei gl_pack_alignment 1; 
	for i = 0 to (len - 1) do
		let w = (surface_width (mipmaps.(i))) and h = (surface_height (mipmaps.(i))) and pixels = (surface_pixels (mipmaps.(i))) in
		glTexImage2D gl_texture_2d i 3 w h 0 rgba gl_unsigned_byte pixels;  
	done 

let light_ambient =  [| 0.5; 0.5; 0.5; 1.0 |]
let light_diffuse =  [| 1.0; 1.0; 1.0; 1.0 |]
let light_position =  [|0.0; 0.0; 2.0; 1.0 |]

let xrot = ref 0.1
let yrot = ref 0.1
let xspeed = ref 0.1
let yspeed = ref 0.1	

let z = ref (-5.0)

let light = ref true

let filter = ref 2

let texture = Array.make 3 0

let load_gl_textures () =
	let s = load_bmp "data/crate.bmp" in
	let p = surface_pixels s in

 	glGenTextures 3 texture;
	
	(* Texture 1: poor quality scaling *)
	glBindTexture gl_texture_2d texture.(0);
	glTexParameteri gl_texture_2d gl_texture_mag_filter gl_nearest; (* cheap scaling when image bigger than texture *)
	glTexParameteri gl_texture_2d gl_texture_min_filter gl_nearest; (* cheap scaling when image smalled than texture *)
    (* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
     border 0 (normal), rgb color data, unsigned byte data, and finally the data itself. *)
	glTexImage2D gl_texture_2d 0 3 (surface_width s) (surface_height s) 0 gl_rgb gl_unsigned_byte p;

	(* Texture 2: Linear scaling *)
	glBindTexture gl_texture_2d texture.(1);
	glTexParameteri gl_texture_2d gl_texture_mag_filter gl_linear; (* linear scaling when image bigger than texture *)
	glTexParameteri gl_texture_2d gl_texture_min_filter gl_linear; (* linear scaling when image smalled than texture *)
    (* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
     border 0 (normal), rgb color data, unsigned byte data, and finally the data itself. *)
	glTexImage2D gl_texture_2d 0 3 (surface_width s) (surface_height s) 0 gl_rgb gl_unsigned_byte p;

	(* Texture 3: Mipmapped scaling *)
	glBindTexture gl_texture_2d texture.(2);
	glTexParameteri gl_texture_2d gl_texture_mag_filter gl_linear; (* linear scaling when image bigger than texture *)
	glTexParameteri gl_texture_2d gl_texture_min_filter gl_linear_mipmap_linear; (* scale linearly + mipmap when image smalled than texture *)
    (* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
     border 0 (normal), rgb color data, unsigned byte data, and finally the data itself. *)
	
	glTexImage2D gl_texture_2d 0 3 (surface_width s) (surface_height s) 0 gl_rgb gl_unsigned_byte p;
	opengl_mipmaps s triangle 
	
	
(* A general OpenGL initialization function.  Sets all of the initial parameters. *)
let init_gl width height =
	load_gl_textures ();
	glViewport 0 0 width height;
	glClearColor 0.0 0.0 0.0 0.0;
	glClearDepth 1.0;
	glDepthFunc gl_less;
	glEnable gl_depth_test;
	glEnable gl_texture_2d;
	glShadeModel gl_smooth;
	glMatrixMode gl_projection;
	glLoadIdentity ();
	let aspect = (float_of_int width) /. (float_of_int height) in
	perspective 45.0 aspect 1.0 100.0;
	glMatrixMode gl_modelview;
	(* Set up lights *)
	glEnable gl_lighting;
	glLightfv gl_light1 gl_ambient light_ambient;
	glLightfv gl_light1 gl_diffuse light_diffuse;
	glLightfv gl_light1 gl_position light_position;
	glEnable gl_light1	
	
let draw_gl_scene () =
    glClear  (gl_color_buffer_bit lor gl_depth_buffer_bit) ;		 (* Clear The Screen And The Depth Buffer *)
    glLoadIdentity  () ;				 (* Reset The View*)

    glTranslatef 0.0 0.0 !z ;                   (* move z units out from the screen. *)
    
    glRotatef !xrot 1.0 0.0 0.0 ;		 (* Rotate On The X Axis *)
    glRotatef !yrot 0.0 1.0 0.0 ;		 (* Rotate On The Y Axis *)

    glBindTexture gl_texture_2d  texture.(!filter) ;    (* choose the texture to use. *)

    glBegin gl_quads ;		                 (* begin drawing a cube *)
    
     (* Front Face  note that the texture's corners have to match the quad's corners  *)
    glNormal3f  0.0  0.0  1.0 ;                               (* front face points out of the screen on z. *)
    glTexCoord2f 0.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)   1.0 ;	 (* Bottom Left Of The Texture and Quad *)
    glTexCoord2f 1.0  0.0 ; glVertex3f  1.0  (-.1.0)   1.0 ;	 (* Bottom Right Of The Texture and Quad *)
    glTexCoord2f 1.0  1.0 ; glVertex3f  1.0   1.0   1.0 ;	 (* Top Right Of The Texture and Quad *)
    glTexCoord2f 0.0  1.0 ; glVertex3f (-.1.0)   1.0   1.0 ;	 (* Top Left Of The Texture and Quad *)
    
     (* Back Face *)
    glNormal3f  0.0  0.0 (-.1.0) ;                               (* back face points into the screen on z. *)
    glTexCoord2f 1.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)  (-.1.0) ;	 (* Bottom Right Of The Texture and Quad *)
    glTexCoord2f 1.0  1.0 ; glVertex3f (-.1.0)   1.0  (-.1.0) ;	 (* Top Right Of The Texture and Quad *)
    glTexCoord2f 0.0  1.0 ; glVertex3f  1.0   1.0  (-.1.0) ;	 (* Top Left Of The Texture and Quad *)
    glTexCoord2f 0.0  0.0 ; glVertex3f  1.0  (-.1.0)  (-.1.0) ;	 (* Bottom Left Of The Texture and Quad *)
	
     (* Top Face *)
    glNormal3f  0.0  1.0  0.0 ;                               (* top face points up on y. *)
    glTexCoord2f 0.0  1.0 ; glVertex3f (-.1.0)   1.0  (-.1.0) ;	 (* Top Left Of The Texture and Quad *)
    glTexCoord2f 0.0  0.0 ; glVertex3f (-.1.0)   1.0   1.0 ;	 (* Bottom Left Of The Texture and Quad *)
    glTexCoord2f 1.0  0.0 ; glVertex3f  1.0   1.0   1.0 ;	 (* Bottom Right Of The Texture and Quad *)
    glTexCoord2f 1.0  1.0 ; glVertex3f  1.0   1.0  (-.1.0) ;	 (* Top Right Of The Texture and Quad *)
    
     (* Bottom Face   *)     
    glNormal3f  0.0  (-.1.0)  0.0 ;                              (* bottom face points down on y.  *)
    glTexCoord2f 1.0  1.0 ; glVertex3f (-.1.0)  (-.1.0)  (-.1.0) ;	 (* Top Right Of The Texture and Quad *)
    glTexCoord2f 0.0  1.0 ; glVertex3f  1.0  (-.1.0)  (-.1.0) ;	 (* Top Left Of The Texture and Quad *)
    glTexCoord2f 0.0  0.0 ; glVertex3f  1.0  (-.1.0)   1.0 ;	 (* Bottom Left Of The Texture and Quad *)
    glTexCoord2f 1.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)   1.0 ;	 (* Bottom Right Of The Texture and Quad *)
    
     (* Right face *)
    glNormal3f  1.0  0.0  0.0 ;                               (* right face points right on x. *)
    glTexCoord2f 1.0  0.0 ; glVertex3f  1.0  (-.1.0)  (-.1.0) ;	 (* Bottom Right Of The Texture and Quad *)
    glTexCoord2f 1.0  1.0 ; glVertex3f  1.0   1.0  (-.1.0) ;	 (* Top Right Of The Texture and Quad *)
    glTexCoord2f 0.0  1.0 ; glVertex3f  1.0   1.0   1.0 ;	 (* Top Left Of The Texture and Quad *)
    glTexCoord2f 0.0  0.0 ; glVertex3f  1.0  (-.1.0)   1.0 ;	 (* Bottom Left Of The Texture and Quad *)
    
     (* Left Face *)
    glNormal3f (-.1.0)  0.0  0.0 ;                               (* left face points left on x. *)
    glTexCoord2f 0.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)  (-.1.0) ;	 (* Bottom Left Of The Texture and Quad *)
    glTexCoord2f 1.0  0.0 ; glVertex3f (-.1.0)  (-.1.0)   1.0 ;	 (* Bottom Right Of The Texture and Quad *)
    glTexCoord2f 1.0  1.0 ; glVertex3f (-.1.0)   1.0   1.0 ;	 (* Top Right Of The Texture and Quad *)
    glTexCoord2f 0.0  1.0 ; glVertex3f (-.1.0)   1.0  (-.1.0) ;	 (* Top Left Of The Texture and Quad *)
    
    glEnd  ();                                     (* done with the polygon. *)

    xrot := !xrot +. !xspeed;		                 (* X Axis Rotation	 *)
    yrot := !yrot +. !yspeed		                 (* Y Axis Rotation *)
    

let callback k =
	if k.keystate = PRESSED then
	match (k.sym) with
       | K_F -> filter := (!filter + 1) mod 3;
       | K_L -> if !light = false then glEnable gl_lighting else glDisable gl_lighting; light := not !light;
       | _ -> ()
    
(* Wait until a key is pressed or the window is closed *)	
let rec handle_events quit =
	draw_gl_scene ();
	swap_buffers ();
	if not quit then begin
		match poll_event () with
			| Key k -> callback k; handle_events false;
			| Quit ->  handle_events true;
      		| _ -> handle_events false;
	end
	


let main () =
	init [VIDEO];
	let w = 640 and h = 480	and bpp = 32 in
	let _ = set_video_mode w h bpp [OPENGL] in
	set_caption "Jeff Molofee's GL Code Tutorial ... NeHe '99" "NeHe 07";
	init_gl w h;
	handle_events false;
	quit ()	


(* Program entry point *)
let _ = 
	try
		main ()
	with
		SDL_failure m -> failwith m    
