open Glcaml


let perspective fov aspect near far =
	let h = (tan (fov /. 360.0 *. (4.0 *. (atan 1.0)) )) *. near in
	let w = h *. aspect in
	glFrustum (-.w) w (-.h) h near far

let print_log o =
    let infoLog = String.create 1024 in
	let infologLength = [| String.length infoLog |] in
	let _ = 
	if (glIsShader o) then
		glGetShaderInfoLog o 1024 infologLength infoLog
	else
		glGetProgramInfoLog o 1024 infologLength infoLog
	in
	print_string infoLog

let fsSource = 
	"/* Fragment shader */\n" ^  
	"void main()\n" ^
	"{\n" ^
	"	gl_FragColor[0] = gl_FragCoord[0] / 400.0;\n" ^
	"	gl_FragColor[1] = gl_FragCoord[1] / 400.0;\n" ^
	"	gl_FragColor[2] = 1.0;\n" ^
	"}\n" 

let vsSource =
	"/* Vertex shader */\n" ^ 
	"uniform float waveTime;\n" ^
	"uniform float waveWidth;\n" ^
	"uniform float waveHeight;\n" ^
	"\n" ^
	"void main(void)\n" ^
	"{\n" ^
	"	vec4 v = vec4(gl_Vertex);\n" ^
	"\n"	^
	"	v.z = sin(waveWidth * v.x + waveTime) * cos(waveWidth * v.y + waveTime) * waveHeight;\n" ^
	"\n"	^
	"	gl_Position = gl_ModelViewProjectionMatrix * v;\n" ^
	"}\n"


let waveTime = ref 0.0
let	waveWidth = ref 0.1
let	waveHeight = ref 3.0
let	waveFreq = ref 0.1 
let waveTimeLoc = ref 0
let waveWidthLoc = ref 0
let waveHeightLoc = ref 0
let fill = ref true


let init () =
	glShadeModel gl_smooth;
	glViewport 0 0 (Graphics.size_x()) (Graphics.size_y());
	glMatrixMode gl_projection;
	glLoadIdentity ();
	perspective 40.0 1.0 0.0001 1000.0;
	glMatrixMode gl_modelview;
	let vs = glCreateShader gl_vertex_shader in
	glShaderSource vs 1 [| vsSource |] [| String.length vsSource |];
	glCompileShader vs;
	print_log vs;
	let fs = glCreateShader gl_fragment_shader in
	glShaderSource fs 1 [| fsSource |]  [|  String.length fsSource |];
	glCompileShader fs;
	print_log fs;
	let sp = glCreateProgram () in
	glAttachShader sp vs;
	glAttachShader sp fs;
	glLinkProgram sp;
	print_log sp;
	glUseProgram sp;
	waveTime := 0.0;
	waveWidth := 0.1;
	waveHeight := 3.0;
	waveFreq := 0.1;
	waveTimeLoc := glGetUniformLocation sp "waveTime";
	waveWidthLoc := glGetUniformLocation sp "waveWidth";
	waveHeightLoc := glGetUniformLocation sp "waveHeight";
	print_log sp;
	Printf.printf "wave parameters location: %d %d %d\n" !waveTimeLoc !waveWidthLoc !waveHeightLoc;
	glPolygonMode gl_front_and_back gl_line;
	()
  
let draw k =
	match k with
	| '0' -> fill := not !fill; glPolygonMode gl_front_and_back (if !fill then gl_fill else gl_line)
	| '1' -> waveFreq := !waveFreq +. 0.1
	| '2' -> waveFreq := !waveFreq -. 0.1
	| '3' -> waveWidth := !waveWidth +. 0.1
	| '4' -> waveWidth := !waveWidth -. 0.1
	| '5' -> waveHeight := !waveHeight +. 0.1
	| '6' -> waveHeight := !waveHeight -. 0.1
	| _ -> ();
	glClear gl_color_buffer_bit;
	glLoadIdentity ();
	glTranslatef 0.0 0.0 (-150.0);
	glRotatef (-45.0) 1.0 0.0 0.0;
	(* Change time *)
	glUniform1f !waveTimeLoc !waveTime;
	glUniform1f !waveWidthLoc !waveWidth;
	glUniform1f !waveHeightLoc !waveHeight;
	(* Draw here a plain surface *)
	glBegin gl_quads;
	for i = -50 to 50 do
		for j = -50 to 50 do
		(
			glVertex2i i j;
			glVertex2i (i + 1) j;
			glVertex2i (i + 1) (j + 1);
			glVertex2i i (j + 1);
		)
		done
	done;	
	glEnd();
	waveTime := !waveTime +. !waveFreq;
	()



(******************************************************************************)
let rec event_loop f = function
	| false -> ()
	| true ->	
		let k = if Graphics.key_pressed () then Graphics.read_key () else ' ' in
		let _ = f k in
		let continue =
		match k with
		| 'q' -> false
		| _ -> true in
		Win.swap_buffers ();
		Win.usleep 300;
		event_loop f continue

let main () =
	    Graphics.open_graph " 800x600";
        Win.init_opengl ();
		Graphics.set_window_title "";
        glViewport 0 0 (Graphics.size_x ()) (Graphics.size_y ());
        glClearColor 0.0 0.0 0.0 0.0;
		init ();
		event_loop draw true
		
let () = main ()
