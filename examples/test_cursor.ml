open Sdl;;

let data = Bigarray.Array1.create Bigarray.int8_unsigned Bigarray.c_layout 128;;
let mask = Bigarray.Array1.create Bigarray.int8_unsigned Bigarray.c_layout 128;;

let image = [|
	"                ..              ";
	"  .             X.              ";
	" . .            X.              ";
	" ...            X.              ";
	" . .            X.              ";
	" . .            X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	"................X...............";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              ";
	"                X.              " |];;

for y = 0 to 31 do
	for x = 0 to 31 do
		let df, mf = (
			let f = image.(y).[x] in
			match f with
			| ' ' -> 0, 0
			| '.' -> 0, 1
			| 'X' -> 1, 1
			| _ -> failwith "data error"
		) in
		let i = y * 4 + x / 8 in
		let b = 1 lsl (7 - x mod 8) in
		let d = Bigarray.Array1.get data i in
		let m = Bigarray.Array1.get mask i in
		Bigarray.Array1.set data i ((d land lnot b) lor (b * df));
		Bigarray.Array1.set mask i ((m land lnot b) lor (b * mf))
	done
done;;

let init (fullscreen: bool): Video.surface = (
	let mode = if fullscreen then [Video.FULLSCREEN] else [] in
	let (result: Video.surface) = Video.set_video_mode 640 480 32 mode in
	Video.warp_mouse 320 240;
	result
);;

Sdl.init [VIDEO];;
at_exit Sdl.quit;;
Window.set_caption "title" "icon-title";;
let fullscreen = ref false;;
let surface = ref (init !fullscreen);;
Video.show_cursor true;;
let my_cursor = Video.create_cursor data mask 32 32 16 16;;
Video.set_cursor my_cursor;;
while (
	begin match Event.poll_event () with
	| Event.Key {Event.keystate = Event.PRESSED; Event.sym = Event.K_RETURN; Event.modifiers = modifiers} when List.mem Event.KMOD_LALT modifiers ->
		fullscreen := not !fullscreen;
		surface := init !fullscreen;
		true
	| Event.Key {Event.keystate = Event.PRESSED; Event.sym = Event.K_ESCAPE} | Event.Quit ->
		prerr_string "quit.\n";
		flush stderr;
		false
	| _ ->
		true
	end
) do
	Video.fill_surface !surface (Video.map_rgb !surface 128 128 128);
	Video.update_surface !surface
done;;
Video.free_cursor my_cursor;;
