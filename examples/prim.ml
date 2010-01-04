(*
	Tests all OpenGL primitives
	- press 'q' to quit
	- press '1' to enable fill mode
	- press '2' to enable line (wireframe) mode
	- press '3' for smooth interpolated shading
	- press '4' for flat shading
*)

open Glcaml

let pixel_center x  = ((float x) +. 0.5)

let gap = 10
let rows = 3
let cols = 4

let opengl_width = 48
let opengl_height = 13

let windW = 600
let windH = 300

let boxW = (windW - (cols + 1) * gap) / cols
let boxH = (windH - (rows + 1) * gap) / rows 

let opengl_bits =  [|
   0x00; 0x03; 0x00; 0x00; 0x00; 0x00; 
   0x7f; 0xfb; 0xff; 0xff; 0xff; 0x01;
   0x7f; 0xfb; 0xff; 0xff; 0xff; 0x01; 
   0x00; 0x03; 0x00; 0x00; 0x00; 0x00;
   0x3e; 0x8f; 0xb7; 0xf9; 0xfc; 0x01; 
   0x63; 0xdb; 0xb0; 0x8d; 0x0d; 0x00;
   0x63; 0xdb; 0xb7; 0x8d; 0x0d; 0x00; 
   0x63; 0xdb; 0xb6; 0x8d; 0x0d; 0x00;
   0x63; 0x8f; 0xf3; 0xcc; 0x0d; 0x00; 
   0x63; 0x00; 0x00; 0x0c; 0x4c; 0x0a;
   0x63; 0x00; 0x00; 0x0c; 0x4c; 0x0e; 
   0x63; 0x00; 0x00; 0x8c; 0xed; 0x0e;
   0x3e; 0x00; 0x00; 0xf8; 0x0c; 0x00 |]

let viewport row column =
    let x = gap + column * (boxW + gap)
    and y = gap + row * (boxH + gap) in
	glDisable gl_scissor_test;
	glViewport x y boxW boxH;
    glMatrixMode gl_projection;
    glLoadIdentity ();
    glOrtho (float (-boxW/2)) (float (boxW/2)) (float (-boxH/2)) (float (boxH/2)) 0.0 1.0;
    glMatrixMode gl_modelview;
    glEnable gl_scissor_test;
    glScissor x y boxW boxH

let set_color index =
	match index with
	| 0 ->  glColor3d 0.0 0.0 0.0
	| 1 ->  glColor3d 1.0 0.0 0.0
	| 2 ->  glColor3d 0.0 1.0 0.0
	| 3 ->  glColor3d 1.0 1.0 0.0
	| 4 ->  glColor3d 0.0 0.0 1.0
	| 5 ->  glColor3d 1.0 0.0 1.0
	| 6 ->  glColor3d 0.0 1.0 1.0
	| _ ->  glColor3d 1.0 1.0 1.0


let point () =
    glBegin gl_points;
	for i = 1 to 7 do
	    let j = i * 2 in
	    set_color i;
	    glVertex2i (-j) (-j);
	    glVertex2i (-j) 0;
	    glVertex2i (-j) j;
	    glVertex2i 0 j;
	    glVertex2i j j;
	    glVertex2i j 0;
	    glVertex2i j (-j);
	    glVertex2i 0 (-j);
	done;
    glEnd ()

let lines () =
	glPushMatrix();
	glTranslated (-12.0) 0.0 0.0;
	for i = 1 to 7 do
		set_color i;
		glBegin gl_lines;
	    glVertex2i (-boxW/4) (-boxH/4);
	    glVertex2i (boxW/4) (boxH/4);
		glEnd();
		glTranslated 4.0 0.0 0.0;
    done;
    glPopMatrix();
    glColor3d 1.0 1.0 1.0;
    glBegin gl_lines;
	glVertex2i 0 0;
    glEnd()

let linestrip () =
    glBegin gl_line_strip;
	set_color 1;
	glVertex2d (pixel_center (-boxW/4)) (pixel_center (-boxH/4));
	set_color 2;
	glVertex2d (pixel_center (-boxW/4)) (pixel_center (boxH/4));
	set_color 3;
	glVertex2d (pixel_center (boxW/4)) (pixel_center (boxH/4));
	set_color 4;
	glVertex2d (pixel_center (boxW/4)) (pixel_center (-boxH/4));
    glEnd ();
    glColor3d 1.0 1.0 1.0;
    glBegin gl_line_strip;
	glVertex2i 0 0;
    glEnd()

let lineloop () =
    glBegin gl_line_loop ;
	set_color 1;
	glVertex2f (pixel_center (-boxW/4)) (pixel_center (-boxH/4));
	set_color 2;
	glVertex2f (pixel_center(-boxW/4)) (pixel_center (boxH/4));
	set_color 3;
	glVertex2f (pixel_center (boxW/4)) (pixel_center (boxH/4));
	set_color 4;
	glVertex2f (pixel_center (boxW/4)) (pixel_center (-boxH/4));
    glEnd();
    glEnable gl_logic_op;
    glLogicOp gl_xor;
    glEnable gl_blend;
    glBlendFunc gl_one gl_one;
    set_color 5;
    glBegin gl_line_loop;
	glVertex2f (pixel_center (-boxW/8)) (pixel_center (-boxH/8));
	glVertex2f (pixel_center (-boxW/8)) (pixel_center (boxH/8));
    glEnd();
    glBegin gl_line_loop;
	glVertex2f (pixel_center (-boxW/8)) (pixel_center (boxH/8+5));
	glVertex2f (pixel_center (boxW/8)) (pixel_center (boxH/8+5));
    glEnd();
    glDisable gl_logic_op;
    glDisable gl_blend;
    set_color 6;
    glBegin gl_points;
	glVertex2i 0 0;
    glEnd ();
    glColor3f 1.0 1.0 1.0;
    glBegin gl_line_loop;
	glVertex2i 0 0;
    glEnd()


let bitmap () =
    glBegin gl_lines;
	set_color 1;
	glVertex2i (-boxW/2) 0;
	glVertex2i (boxW/2) 0;
	glVertex2i 0 (-boxH/2);
	glVertex2i 0 (boxH/2);
	set_color 2;
	glVertex2i 0 (-3);
	glVertex2i 0 (-3+opengl_height);
	set_color 3;
	glVertex2i 0 (-3);
	glVertex2i opengl_width (-3);
    glEnd();
    set_color 4;
    glPixelStorei gl_unpack_lsb_first gl_true;
    glPixelStorei gl_unpack_alignment 1;
    glRasterPos2i 0 0;
    glBitmap opengl_width opengl_height 0.0 3.0 0.0 0.0 opengl_bits

let triangles () =
    glBegin gl_triangles;
	set_color 1;
	glVertex2i (-boxW/4) (-boxH/4);
	set_color 2;
	glVertex2i (-boxW/8) (-boxH/16);
	set_color 3;
	glVertex2i (boxW/8) (-boxH/16);
	set_color 4;
	glVertex2i (-boxW/4) (boxH/4);
	set_color 5;
	glVertex2i (-boxW/8) (boxH/16);
	set_color 6;
	glVertex2i (boxW/8) (boxH/16);
    glEnd();
    glColor3f 1.0 1.0 1.0;
    glBegin gl_triangles;
	glVertex2i 0 0;
	glVertex2i (-100) 100;
    glEnd()

let triangle_strip () =
    glBegin gl_triangle_strip;
	set_color 1;
	glVertex2i (-boxW/4) (-boxH/4);
	set_color 2;
	glVertex2i (-boxW/4) (boxH/4);
	set_color 3;
	glVertex2i 0 (-boxH/4);
	set_color 4;
	glVertex2i 0 (boxH/4);
	set_color 5;
	glVertex2i (boxW/4) (-boxH/4);
	set_color 6;
	glVertex2i (boxW/4) (boxH/4);
    glEnd();
    glColor3f 1.0 1.0 1.0;
    glBegin gl_triangle_strip;
	glVertex2i 0 0;
	glVertex2i (-100) 100;
    glEnd()

let triangle_fan () =
    let y0 = -boxH/4 in
    let y1 = y0 + boxH/2/3 in
    let y2 = y1 + boxH/2/3 in
    let y3 = boxH/4 in
    let x0 = -boxW/4 in
    let x1 = x0 + boxW/2/3 in
    let x2 = x1 + boxW/2/3 in
    let x3 = boxW/4 in
	let vx = 
	[| 
		[| x0; y1 |];
		[| x0; y2 |];
		[| x1; y3 |];
		[| x2; y3 |];
		[| x3; y2 |];
		[| x3; y1 |];
		[| x2; y0 |];
		[| x1; y0 |];
	|] 
	in
    glBegin gl_triangle_fan;
    set_color 7;
	glVertex2i 0 0;
	for i = 0 to 7 do
	    set_color (7-i);
	    glVertex2iv vx.(i);
	done;
    glEnd();
	glColor3f 1.0 1.0 1.0;
    glBegin gl_triangle_fan;
	glVertex2i 0 0;
	glVertex2i (-100) 100;
    glEnd()

let rect () =
    glColor3f 1.0 0.0 1.0;
    glRecti (-boxW/4) (-boxH/4) (boxW/4) (boxH/4)

let polygons () =
    let y0 = -boxH/4 in
    let y1 = y0 + boxH/2/3 in
    let y2 = y1 + boxH/2/3 in
    let y3 = boxH/4 in
    let x0 = -boxW/4 in
    let x1 = x0 + boxW/2/3 in
    let x2 = x1 + boxW/2/3 in
    let x3 = boxW/4 in
	let vx = 
	[| 
		[| x0; y1 |];
		[| x0; y2 |];
		[| x1; y3 |];
		[| x2; y3 |];
		[| x3; y2 |];
		[| x3; y1 |];
		[| x2; y0 |];
		[| x1; y0 |];
	|] 
	in
    glBegin gl_polygon;
	for i = 0 to 7 do
	    set_color (7-i);
	    glVertex2iv vx.(i);
	done;
    glEnd();
	glColor3f 1.0 1.0 1.0;
    glBegin gl_polygon;
	glVertex2i 0 0;
	glVertex2i (-100) 100;
    glEnd()

let quads () =
    glBegin gl_quads ;
	set_color 1;
	glVertex2i (-boxW/4) (-boxH/4);
	set_color 2;
	glVertex2i (-boxW/8) (-boxH/16);
	set_color 3;
	glVertex2i (boxW/8) (-boxH/16);
	set_color 4;
	glVertex2i (boxW/4) (-boxH/4);
	set_color 5;
	glVertex2i (-boxW/4) (boxH/4);
	set_color 6;
	glVertex2i (-boxW/8) (boxH/16);
	set_color 7;
	glVertex2i (boxW/8) (boxH/16);
	set_color 0;
	glVertex2i (boxW/4) (boxH/4);
    glEnd();
	glColor3f 1.0  1.0  1.0;
    glBegin gl_quads;
	glVertex2i 0 0;
	glVertex2i 100 100;
	glVertex2i (-100) 100;
    glEnd()

let quad_strip () =
    glBegin gl_quad_strip;
	set_color 1;
	glVertex2i (-boxW/4) (-boxH/4);
	set_color 2;
	glVertex2i (-boxW/4) (boxH/4);
	set_color 3;
	glVertex2i 0 (-boxH/4);
	set_color 4;
	glVertex2i 0 (boxH/4);
	set_color 5;
	glVertex2i (boxW/4) (-boxH/4);
	set_color 6;
	glVertex2i (boxW/4) (boxH/4);
    glEnd();
    glColor3f 1.0 1.0 1.0;
    glBegin gl_quad_strip;
	glVertex2i 0 0;
	glVertex2i 100 100;
	glVertex2i (-100) 100;
    glEnd()


let draw () =
    glViewport 0 0 windW windH;
    glDisable gl_scissor_test;
    glPushAttrib gl_color_buffer_bit;
    glColorMask true true true true;
    glClearColor 0.0  0.0  0.0  0.0;
    glClear gl_color_buffer_bit;
    glPopAttrib();
	let run r c f =
		viewport r c;
		f () 
	in
	run 0 0 point;	 
    run 0 1 lines;
	run 0 2 linestrip;
	run 0 3 lineloop;
	run 1 0 bitmap;
	run 1 1 triangles;
	run 1 2 triangle_strip;
	run 1 3 triangle_fan;
	run 2 0 rect;
	run 2 1 polygons;
	run 2 2 quads;
	run 2 3 quad_strip



(******************************************************************************)
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
		| '3' -> glShadeModel gl_smooth
		| '4' -> glShadeModel gl_flat
		| _ -> ()
		in event_loop f continue


let main () =
	    open_graph (Printf.sprintf " %dx%d" windW windH);
        Win.init_opengl ();
		Graphics.set_window_title "GL Primitives Test";
        glViewport 0 0 (size_x ()) (size_y ());
        glClearColor 0.0 0.0 0.0 0.0;
		event_loop (fun () -> draw (); Win.swap_buffers ()) true
		
let () = main ()
