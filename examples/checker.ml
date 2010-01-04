open Glcaml

let texName = Array.make 1 0
let checkImageWidth = 64
let checkImageHeight = 64

let checkImage = make_ubyte_array (checkImageWidth*checkImageHeight*4)

let perspective fov aspect near far =
	let h = (tan (fov /. 360.0 *. (4.0 *. (atan 1.0)) )) *. near in
	let w = h *. aspect in
	glFrustum (-.w) w (-.h) h near far

let clear () =
	glClearColor 0.0 0.0 0.0 0.0;
    glClear (gl_color_buffer_bit lor gl_depth_buffer_bit)
	

let makeCheckImage () = 
	let k = ref 0 in   
   for i = 0 to (checkImageHeight - 1) do
   	for j = 0 to (checkImageWidth - 1) do
         let a = if (i land 8 = 0) then 0 else 1  
         and b = if (j land 8 = 0) then 0 else 1  in
		 let c = (a lxor b) * 255 in
         checkImage.{!k} <- c;
         checkImage.{!k + 1} <- 0;
         checkImage.{!k + 2} <- 0;
         checkImage.{!k + 3} <- 255;
		 k := !k + 4;
	 done
   done	 	 

	
let init () =    
	makeCheckImage ();
   glShadeModel gl_flat;
   glEnable gl_depth_test;
   glPixelStorei gl_unpack_alignment 1;
   glGenTextures 1 texName;
   glBindTexture gl_texture_2d texName.(0);
   glTexParameteri gl_texture_2d gl_texture_wrap_s gl_repeat;
   glTexParameteri gl_texture_2d gl_texture_wrap_t gl_repeat;
   glTexParameteri gl_texture_2d gl_texture_mag_filter gl_nearest;
   glTexParameteri gl_texture_2d gl_texture_min_filter gl_nearest;
   glTexImage2D gl_texture_2d 0 gl_rgba checkImageWidth checkImageHeight 
                0 gl_rgba gl_unsigned_byte checkImage
	
	
let draw () =
   glEnable gl_texture_2d;
   glTexEnvi gl_texture_env gl_texture_env_mode gl_decal;
   glBindTexture gl_texture_2d texName.(0);
   glBegin gl_quads;
   glTexCoord2f 0.0 0.0; glVertex3f (-2.0) (-1.0) 0.0;
   glTexCoord2f 0.0 1.0; glVertex3f (-2.0) 1.0 0.0;
   glTexCoord2f 1.0 1.0; glVertex3f 0.0 1.0 0.0;
   glTexCoord2f 1.0 0.0; glVertex3f 0.0 (-1.0) 0.0;
   glTexCoord2f 0.0 0.0; glVertex3f 1.0 (-1.0) 0.0;
   glTexCoord2f 0.0 1.0; glVertex3f 1.0 1.0 0.0;
   glTexCoord2f 1.0 1.0; glVertex3f 2.41421 1.0 (-1.41421);
   glTexCoord2f 1.0 0.0; glVertex3f 2.41421 (-1.0) (-1.41421);
   glEnd ();
   glFlush ();
   glDisable gl_texture_2d

let resize () =
   let w = Graphics.size_x () 
   and h = Graphics.size_y () in
   glViewport 0 0  w  h;
   glMatrixMode gl_projection;
   glLoadIdentity ();
   perspective 60.0 ((float w)/.(float h)) 1.0 30.0;
   glMatrixMode gl_modelview;
   glLoadIdentity ();
   glTranslatef 0.0 0.0 (-3.6)



(******************************************************************************)
let rec event_loop f = function
	| false -> ()
	| true ->	
		let _ = f () in
		let k = Graphics.read_key () in
		let continue =
		match k with
		| 'q' -> false
		| _ -> true
		in event_loop f continue


let main () =
	    Graphics.open_graph " 300x300";
        Win.init_opengl ();
		Graphics.set_window_title "";
        init ();
		event_loop (clear (); resize (); fun () -> draw (); Win.swap_buffers ()) true
		
let () = main ()
