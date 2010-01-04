open Glcaml

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
		Graphics.set_window_title "";
        glViewport 0 0 (Graphics.size_x ()) (Graphics.size_y ());
        glClearColor 0.0 0.0 0.0 0.0;
		event_loop true
		
let () = main ()
