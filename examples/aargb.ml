open Printf
open Glcaml

let dbg_print_array a =
	Array.iter (fun i -> printf "%f " i) a

let init () =
	let values = glGetFloatv gl_line_width_granularity in 
	()



(******************************************************************************)
let rec event_loop = function
	| false -> ()
	| true ->	
		let k = Graphics.read_key () in
		let continue =
		match k with
		| 'q' -> false
		| _ -> true
		in event_loop continue


let main () =
	    Graphics.open_graph " 200x200";
        Win.init_opengl ();
		Graphics.set_window_title "Antialiased lines";
        glViewport 0 0 (Graphics.size_x ()) (Graphics.size_y ());
        glClearColor 0.0 0.0 0.0 0.0;
		init ();
		event_loop true
		
let () = main ()
