(*
	Draw a sphere, a cube and a grid and circle them with
	the camera.
	Press ESC to quit
*)

open Glcaml

let pi = 4.0 *. (atan 1.0)

let vdot a b =
	a.(0) *. b.(0) +. a.(1) *. b.(1) +.a.(2) *. b.(2)
       
let vadd a b =
	[| a.(0) +. b.(0); a.(1) +. b.(1); a.(2) +. b.(2) |]

let vsub a b =
	[| a.(0) -. b.(0); a.(1) -. b.(1); a.(2) -. b.(2) |]

let vscale k a =
	[| k *. a.(0); k *. a.(1); k *. a.(2) |]

let vmul a b = 
	[| a.(0) *. b.(0); a.(1) *. b.(1); a.(2) *. b.(2) |]	

let vlength a = sqrt (vdot a a)          
       
let vnorm a = vscale (1.0 /.(vlength a)) a

let vcross v1 v2 =
	[| v1.(1)*.v2.(2) -. v2.(1)*.v1.(2);  v1.(2)*.v2.(0) -. v2.(2)*.v1.(0);  v1.(0)*.v2.(1) -. v2.(0)*.v1.(1) |]

(* Replacement for gluPerspective() *)
let perspective fov aspect near far =
	let h = (tan (fov /. 360.0 *. pi )) *. near in
	let w = h *. aspect in
	glFrustum (-.w) w (-.h) h near far

(* A replacement for gluLookAt *)
let lookat ex ey ez cx cy cz ux uy uz =
	let f = (vnorm (vsub [| cx; cy; cz |] [| ex; ey; ez |])) in
	let s = vcross f [| ux; uy ; uz |] in
	let u = vcross s f in
	glMultMatrixd [| s.(0); u.(0); -.f.(0); 0.0; 
					 s.(1); u.(1); -.f.(1); 0.0; 
					 s.(2); u.(2); -.f.(2); 0.0; 
					 0.0;   0.0;     0.0;   1.0  |]; 
	glTranslated (-.ex) (-.ey) (-.ez)

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
	let aspect = (float width) /. (float height) in
	perspective 45.0 aspect 1.0 100.0;
	glMatrixMode gl_modelview

(* geometry *)
	
type polygon = { pv : float array array; pc : float array array }

type sphere  = { scenter: float array; sradius: float}

(* Generate a unit sphere centered on the origin. The parameter lod determines the level of tesselation *)
let generate_unit_sphere lod =
	let bisect p1 p2 p3 =
		let pa =  vnorm (vscale 0.5 (vadd p1 p2))
		and pb =  vnorm (vscale 0.5 (vadd p2 p3))
		and pc =  vnorm (vscale 0.5 (vadd p3 p1))
		in
		[|
		[|p1; pa; pc|];
		[|pa; p2; pb|];
		[|pc; pb; p3|];
		[|pa; pb; pc|];
		|]
	in
	let rec iterate n l =
		if n <= 0 then l else 
		iterate (n - 1) (Array.concat (Array.to_list (Array.map (fun c -> bisect c.(0) c.(1) c.(2)) l))) 
	in	
	let p = [| [| 0.;  0.; 1. |];  [| 0.; 0.; -1. |];  [| -1.; -1.; 0. |]; 
		       [| 1.; -1.; 0. |];  [| 1.; 1.;  0. |];  [| -1.;  1.; 0. |] |] 
	and a = 1.0 /. (sqrt 2.) in
	let p = Array.map (fun c -> vmul c [| a; a; 1.; 1.|]) p in
	iterate lod
	[|
	[| p.(0); p.(3); p.(4); |]; 
	[| p.(0); p.(4); p.(5); |]; 
	[| p.(0); p.(5); p.(2); |]; 
	[| p.(0); p.(2); p.(3); |]; 
	[| p.(1); p.(4); p.(3); |]; 
	[| p.(1); p.(5); p.(4); |]; 
	[| p.(1); p.(2); p.(5); |]; 
	[| p.(1); p.(3); p.(2); |]; 
	|]	   	   
	
(* Generate the vertices of a unit cube centered on the origin *)
let generate_unit_cube () =
	[|
	[| [|-0.5; -0.5; -0.5 |];  [| 0.5; -0.5; -0.5 |];  [| 0.5; -0.5;  0.5 |];  [|-0.5; -0.5;  0.5 |] |];
	[| [|-0.5; -0.5; -0.5 |];  [|-0.5; -0.5;  0.5 |];  [|-0.5;  0.5;  0.5 |];  [|-0.5;  0.5; -0.5 |] |];
	[| [|-0.5; -0.5;  0.5 |];  [| 0.5; -0.5;  0.5 |];  [| 0.5;  0.5;  0.5 |];  [|-0.5;  0.5;  0.5 |] |];
	[| [|-0.5;  0.5; -0.5 |];  [|-0.5;  0.5;  0.5 |];  [| 0.5;  0.5;  0.5 |];  [| 0.5;  0.5; -0.5 |] |];
	[| [| 0.5; -0.5; -0.5 |];  [| 0.5;  0.5; -0.5 |];  [| 0.5;  0.5;  0.5 |];  [| 0.5; -0.5;  0.5 |] |];
	[| [|-0.5; -0.5; -0.5 |];  [|-0.5;  0.5; -0.5 |];  [| 0.5;  0.5; -0.5 |];  [| 0.5; -0.5; -0.5 |] |];
	|]

let generate_grid w' h' =
	let w = w'/2 and h = h'/2 in 
	let x = Array.init (2*w+1) (fun i -> [| [|(float (i - w)); 0.; (float (-w)) |]; [|(float (i - w)); 0.; (float w) |] |])
	and z = Array.init (2*h+1) (fun i -> [| [|(float (-h)); 0.; (float (i - h)) |]; [|(float h); 0.; (float (i - h)) |] |]) in
	Array.append x z
	
let sphere = 
	let col = [| [|0.5; 0.5; 1.|] |] in
	let l = generate_unit_sphere 1 in
	Array.map (fun c -> { pv = c; pc = col}) l
	
let cube =	
	let col = [| [| 1.; 0.0; 1.|] |] in
	let l = generate_unit_cube () in
	Array.map (fun c -> { pv = c; pc = col}) l 

let grid = 
	let x = 5 and z = 4 and col = [| [| 0.5; 0.; 0.5 |]|] in
	let l = generate_grid x z in
	Array.map (fun c -> {pv = c; pc = col}) l

let scene_data = [| grid; sphere; cube |]

(* Set wireframe mode *)
let wireframe () =
	glPolygonMode gl_front_and_back gl_line

(* Draw polygon (point, line, triangle. quad, general polygon) *)
let draw_polygon p = 
	let np = Array.length p.pv and nc = Array.length p.pc in
	let va = p.pv
	and ca = if np = nc then p.pc else Array.make np p.pc.(0) in
	let t =	match np with
	| 1 -> gl_points
	| 2 -> gl_lines
	| 3 -> gl_triangles
	| 4 -> gl_quads
	| _ -> gl_polygon in
	glBegin t;
	Array.iteri (fun i c -> glColor3f ca.(i).(0) ca.(i).(1) ca.(i).(2); glVertex3f c.(0) c.(1) c.(2)) va;
	glEnd ()

let draw_polytope p = 
	Array.iter draw_polygon p

(* Render openGL scene *)
let draw_gl_scene data =
	Array.iter (fun c -> draw_polytope c) data


(************ main ***********)
open Graphics

let width = 800
let height = 600

let tstart = Unix.gettimeofday ()

let init_graphics () =
	let init_string = (Printf.sprintf " %dx%d" width height) in
	open_graph init_string;
	Win.init_opengl ();
	init_gl width height;
	wireframe ();
	set_window_title "Camera"

let rec event_loop initial_data actions =
	let transformed_data = Array.fold_left (fun x a -> a x) initial_data actions in
	let k = if key_pressed () then read_key () else ' ' in
	if not (k = (char_of_int 27)) then event_loop transformed_data actions

let main () =
	let _ = init_graphics () in
	let cl () =
		glClear (gl_color_buffer_bit lor gl_depth_buffer_bit) 
	and l () =
		glLoadIdentity ();
		let period = 10.0 
		and t = Unix.gettimeofday () in
		let theta = (mod_float (t -. tstart) period) *. 2.0 *. pi /. period in
		let r = 10.0 in
		lookat (r *. (cos theta)) 5.0 (r *. (sin theta)) 0.0 0.0 0.0 0.0 1.0 0.0
	and swap () = Win.swap_buffers ()
	and pass func =	let f x = func (); x in f 	
	and no_change func = let f x = func x; x in f	
	in
       event_loop scene_data [| pass cl; pass l; no_change draw_gl_scene; pass swap |] ;;

main ()

