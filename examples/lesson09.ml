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


let star_num = 50
type stars =  {r : int; g : int; b : int; dist : float; angle : float}
let star = Array.init star_num (fun i -> {r = Random.int 255; g = Random.int 255; b = Random.int 255; dist = 5.0 *. (float_of_int i)/.(float_of_int star_num); angle = 0.0  })
	
let zoom = ref (-.15.0)
let tilt = ref 90.0
let spin = ref 0.0
let twinkle = ref false

let texture = Array.make 1 0

let load_gl_textures () =
	let s = load_bmp "data/Star.bmp" in
	let p = (surface_pixels s) in
	
	glGenTextures 1 texture;
	
	(* Texture 2: Linear scaling *)
	glBindTexture gl_texture_2d texture.(0);
	glTexParameteri gl_texture_2d gl_texture_mag_filter gl_linear; (* linear scaling when image bigger than texture *)
	glTexParameteri gl_texture_2d gl_texture_min_filter gl_linear; (* linear scaling when image smalled than texture *)
    (* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
     border 0 (normal), rgb color data, unsigned byte data, and finally the data itself. *)
	glTexImage2D gl_texture_2d 0 3 (surface_width s) (surface_height s) 0 gl_rgb gl_unsigned_byte p
	
	
(* A general OpenGL initialization function.  Sets all of the initial parameters. *)
let init_gl width height =
	load_gl_textures ();
	glViewport 0 0 width height;
	glClearColor 0.0 0.0 0.0 0.0;
	glClearDepth 1.0;
	glEnable gl_texture_2d;
	glShadeModel gl_smooth;
	glMatrixMode gl_projection;
	glLoadIdentity ();
	let aspect = (float_of_int width) /. (float_of_int height) in
	perspective 45.0 aspect 1.0 100.0;
	glMatrixMode gl_modelview;
    (* setup blending *)
    glBlendFunc gl_src_alpha gl_one;			(* Set The Blending Function For Translucency *)
    glEnable gl_blend
	
let draw_gl_scene () =
    glClear (gl_color_buffer_bit lor gl_depth_buffer_bit);		(* Clear The Screen And The Depth Buffer *)
    
    glBindTexture gl_texture_2d texture.(0);    (* pick the texture. *)

	for i = 0 to (star_num - 1) do  
		let c = star.(i) in
 	 	glLoadIdentity ();                        (* reset the view before we draw each star. *)
		glTranslatef 0.0 0.0 !zoom;          (* zoom into the screen. *)
		glRotatef !tilt 1.0 0.0 0.0;       (* tilt the view. *)
		
		glRotatef c.angle 0.0 1.0 0.0; (* rotate to the current star's angle. *)
		glTranslatef c.dist 0.0 0.0; (* move forward on the X plane (the star's x plane).*)
	
		glRotatef (-.(c.angle)) 0.0 1.0 0.0; (* cancel the current star's angle.*)
		glRotatef (-.(!tilt)) 1.0 0.0 0.0;      (* cancel the screen tilt. *)

		
		if (!twinkle = true) then begin                          (* twinkling stars enabled ... draw an additional star. *)
		    (* assign a color using bytes *)
		    glColor4ub star.(star_num - i - 1).r star.(star_num - i - 1).g star.(star_num - i - 1).b  255;  
		    glBegin gl_quads;                   (* begin drawing the textured quad. *)
		    glTexCoord2f 0.0 0.0; glVertex3f (-.1.0) (-.1.0) 0.0;
		    glTexCoord2f 1.0 0.0; glVertex3f  1.0 (-.1.0) 0.0;
		    glTexCoord2f 1.0 1.0; glVertex3f  1.0  1.0 0.0;
		    glTexCoord2f 0.0 1.0; glVertex3f (-.1.0) 1.0 0.0;
		    glEnd ();                             (* done drawing the textured quad. *)
		end;
	
		(* main star *)
		glRotatef !spin 0.0 0.0 1.0;       (* rotate the star on the z axis. *)
	
	        (* Assign A Color Using Bytes *)
		glColor4ub c.r c.g c.b 255;
		glBegin gl_quads;			(* Begin Drawing The Textured Quad *)
		glTexCoord2f 0.0 0.0; glVertex3f (-.1.0) (-.1.0) 0.0;
		glTexCoord2f 1.0 0.0; glVertex3f  1.0 (-.1.0) 0.0;
		glTexCoord2f 1.0 1.0; glVertex3f  1.0 1.0 0.0;
		glTexCoord2f 0.0 1.0; glVertex3f (-.1.0) 1.0 0.0;
		glEnd ();				(* Done Drawing The Textured Quad *)
		
		spin := !spin +. 0.01;                           (* used to spin the stars. *)
		
		let newc_angle = c.angle +. (float_of_int i) /. (float_of_int star_num)    (* change star angle. *)
		and newc_dist  = c.dist -. 0.01              (* bring back to center. *)
		in
		let newc =
		if c.dist >= 0.0 then
		{
			r = c.r; g = c.g; b = c.b; dist = newc_dist; angle = newc_angle
		}
		else
		{
			r = Random.int 255; g = Random.int 255; b = Random.int 255; dist = newc_dist +. 5.0; angle = newc_angle
		}
		in
		star.(i) <- newc;
	done;	

    (* swap buffers to display, since we're double buffered. *)
    swap_buffers ();
;;
    

let callback k =
	match (k.sym) with
       | K_T -> twinkle := not !twinkle;
       | _ -> ()
    
(* Wait until a key is pressed or the window is closed *)	
let rec handle_events quit =
	draw_gl_scene ();
	if not quit then begin
		match poll_event () with
			| Key k -> callback k; handle_events false;
			| Quit ->  handle_events true;
      		| _ -> handle_events false;
	end
;;	

let main () =
	init [VIDEO];
	let w = 640 and h = 480	and bpp = 32 in
	let _ = set_video_mode w h bpp [OPENGL] in
	set_caption "Jeff Molofee's GL Code Tutorial ... NeHe '99" "NeHe 07";
	init_gl w h;
	handle_events false;
	quit ()	
;;

(* Program entry point *)
let _ = 
	try
		main ()
	with
		SDL_failure m -> failwith m    
