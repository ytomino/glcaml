let font_filename = (
	if Sys.os_type = "Win32" then
		"C:\\WINDOWS\\Fonts\\times.ttf"
	else
		"/System/Library/Fonts/AppleGothic.ttf"
);;

open Glcaml;;
open Sdl;;
module TTF = Sdl_ttf;;

(* texture *)

let tex_indexes = [|0|];;

let gl_init (): unit = (
	glClearColor 0.5 0.0 0.0 0.0;
	let font = TTF.open_font font_filename 64 in
	let tex = TTF.render_utf8_shaded font "ABC" 
		{Video.red = 255; Video.green = 255; Video.blue = 255}
		{Video.red =  0; Video.green = 255; Video.blue = 255} in
	Printf.eprintf "loaded(%d).\n" (Video.surface_bpp tex); flush stderr;
	Printf.eprintf "r(%d).\n" (Video.surface_rmask tex); flush stderr;
	Printf.eprintf "g(%d).\n" (Video.surface_gmask tex); flush stderr;
	Printf.eprintf "b(%d).\n" (Video.surface_bmask tex); flush stderr;
	Printf.eprintf "a(%d).\n" (Video.surface_amask tex); flush stderr;
	Printf.eprintf "w(%d).\n" (Video.surface_width tex); flush stderr;
	Video.set_alpha tex [] 0;
	let tex2 = Video.create_rgb_surface [] 128 128 32 in
	Video.blit_surface tex None tex2 None;
	Printf.eprintf "converted(%d).\n" (Video.surface_bpp tex2); flush stderr;
	let ptr = Video.surface_pixels tex2 in
	prerr_string "get.\n"; flush stderr;
	glGenTextures 1 tex_indexes;
	Printf.eprintf "texture=%d\n" tex_indexes.(0);
	glBindTexture gl_texture_2d tex_indexes.(0);
	glPixelStorei gl_unpack_alignment 1;
	glTexImage2D gl_texture_2d 0 gl_rgba 128 128 0 gl_rgba gl_unsigned_byte ptr;
	TTF.close_font font
);;

let gl_draw (): unit = (
	glClear gl_color_buffer_bit;
	glLoadIdentity ();
	glTranslated (-1.0) (1.0) 0.0;
	glScaled (2.0 /. 640.0) (-2.0 /. 480.0) 1.0;
	glEnable gl_texture_2d;
	glShadeModel gl_flat;
	glBindTexture gl_texture_2d tex_indexes.(0);
	glTexParameteri gl_texture_2d gl_texture_min_filter gl_nearest;
	glTexParameteri gl_texture_2d gl_texture_mag_filter gl_nearest;
	glEnable gl_blend;
	glBlendFunc gl_src_alpha gl_one_minus_src_alpha;
	(* glColor3d 0.0 1.0 1.0; *)
	glBegin gl_polygon;
	glTexCoord2d 0.0 0.0; glVertex2d 50.0 50.0;
	glTexCoord2d 0.0 1.0; glVertex2d 50.0 100.0;
	glTexCoord2d 1.0 1.0; glVertex2d 100.0 100.0;
	glTexCoord2d 1.0 0.0; glVertex2d 100.0 50.0;
	glEnd ();
	glDisable gl_texture_2d;
	glDisable gl_blend;
	glColor3d 1.0 1.0 1.0;
	glBegin gl_polygon;
	glVertex2d 10.0 10.0;
	glVertex2d 10.0 20.0;
	glVertex2d 20.0 20.0;
	glVertex2d 20.0 10.0;
	glEnd ();
	glFlush ()
);;

let gl_done (): unit = (
	glDeleteTextures 1 tex_indexes
);;

let init (fullscreen: bool): Video.surface = (
	SDLGL.set_attribute SDLGL.DOUBLEBUFFER 1;
	let mode = if fullscreen then [Video.OPENGL; Video.FULLSCREEN] else [Video.OPENGL] in
	let (result: Video.surface) = Video.set_video_mode 640 480 32 mode in
	Video.show_cursor (not fullscreen);
	gl_init ();
	result
);;

Sdl.init [VIDEO];;
at_exit Sdl.quit;;
TTF.init ();;
at_exit TTF.quit;;
Window.set_caption "title" "icon-title";;
(* Window.set_icon (Video.load_bmp "icon.bmp");; *)
let fullscreen = ref false;;
let surface = ref (init !fullscreen);;
while (
	begin match Event.poll_event () with
	| Event.Key {Event.keystate = Event.PRESSED; Event.sym = Event.K_RETURN; Event.modifiers = modifiers} when List.mem Event.KMOD_LALT modifiers ->
		begin try Window.toggle_fullscreen !surface with
		| SDL_failure _ ->
			gl_done ();
			fullscreen := not !fullscreen;
			surface := init !fullscreen
		end;
		true
	| Event.Key {Event.keystate = Event.PRESSED; Event.sym = Event.K_ESCAPE} | Event.Quit ->
		prerr_string "quit.\n";
		flush stderr;
		false
	| _ ->
		true
	end
) do
	gl_draw ();
	SDLGL.swap_buffers ();
done;;
gl_done ();;
