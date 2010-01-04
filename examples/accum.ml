(*
	Tests the accumulation buffer
	- press 'q' to quit
	- press '1' to enable fill mode
	- press '2' to enable line (wireframe) mode
	
*)
open Glcaml

(* Clear the render and accumulation buffer*)
let clear () =
    glClearColor 0.0 0.0 0.0 0.0;
    glClearAccum 0.0 0.0 0.0 0.0

(* Create first, red rectangle *)
let make_rect1 () = 
	let id = glGenLists 1 in
    glNewList id gl_compile;
    glColor3d 1.0 0.0 0.0;
    glRectd (-1.0) (-1.0) 1.0 0.0;
    glEndList();
	id

(* Create second, green rectangle *)
let make_rect2 () = 
	let id = glGenLists 1 in
    glNewList id gl_compile;
    glColor3d 0.0 1.0 0.0;
    glRectd 0.0 (-1.0) 1.0 1.0;
    glEndList();
	id

(* Draw both rectangles *)
let draw id1 id2 = 
    glPushMatrix ();
    glScaled 0.8 0.8 1.0;
    glClear gl_color_buffer_bit;
    glCallList id1;
    glAccum gl_load 0.5;
    glClear gl_color_buffer_bit;
    glCallList id2;
    glAccum gl_accum 0.5;
    glAccum gl_return 1.0;
    glPopMatrix ()

(* Function to be called whenever the window is resized *)
let on_resize w h  =
	let x = Graphics.size_x ()
	and y = Graphics.size_y () in
	if (x != w) && (y != h) then
		(glViewport 0 0 x y;
    	glMatrixMode gl_projection;
    	glLoadIdentity ();
    	glMatrixMode gl_modelview;
    	glLoadIdentity ())
	else	
		()

(******************************** test  ********************************)
open Graphics

let rec event_loop f = function
	| false -> ()
	| true ->
		let _ = f () in	
		let k = if key_pressed () then read_key () else ' ' in
		let continue =
		match k with
		| 'q' -> false
		| _ -> true
		and _ =
		match k with
		| '1' -> glPolygonMode gl_front_and_back gl_fill
		| '2' -> glPolygonMode gl_front_and_back gl_line
		| _ -> ()
		in
		event_loop f continue

let main () =
	try
		open_graph " 300x300";
		Win.init_opengl ();
		set_window_title "GL accum test";
		let w = size_x ()
		and h = size_y () in
		glViewport 0 0  w h ;
		clear ();
		let resize () = on_resize w h in
		let id1 = make_rect1 ()
		and id2 = make_rect2 () in
		event_loop (fun () -> resize(); draw id1 id2; Win.swap_buffers () ) true
	with
	| _ -> ()
		
let () = main ()
