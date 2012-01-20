#if defined(USE_FRAMEWORK)
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif
#include "caml/callback.h"
#include "caml/mlvalues.h"
#include "caml/memory.h"
#include "caml/fail.h"
#include "caml/alloc.h"
#include "caml/bigarray.h"

/* utilities */

#define is_not_nil Is_block
#define hd(v) Field((v), 0)
#define tl(v) Field((v), 1)

static value cons(value x, value l)
{
	CAMLparam2(x, l);
	CAMLlocal1(m);
	m = alloc_small(2, Tag_cons);
	Field(m, 0) = x;
	Field(m, 1) = l;
	CAMLreturn(m);
}

/* MIX_InitFlags */

static int const initflags_table[] = {
    MIX_INIT_FLAC,
    MIX_INIT_MOD,
    MIX_INIT_MP3,
    MIX_INIT_OGG,
    MIX_INIT_FLUIDSYNTH,
};

static inline int Initflags_val(value initflags)
{
	int result = 0;
	while(is_not_nil(initflags)){
		result |= initflags_table[Int_val(hd(initflags))];
		initflags = tl(initflags);
	}
	return result;
}

/* Audio.sample_type */

static int const sample_table[] = {
	AUDIO_U8,
	AUDIO_S8,
	AUDIO_U16,
	AUDIO_S16,
	AUDIO_U16LSB,
	AUDIO_S16LSB,
	AUDIO_U16MSB,
	AUDIO_S16MSB
};

static value Val_sample_type(Uint16 format)
{
	int i;
	for(i = 0; i < 8; ++i){
		if(sample_table[i] == format){
			return Val_int(i);
		}
	}
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	return Val_int(5); /* AUDIO_S16LSB */
#else
	return Val_int(7); /* AUDIO_S16MSB */
#endif
}

static inline Uint16 Sample_type_val(value v)
{
	return sample_table[Int_val(v)];
}

/* fading type */

static inline value Val_Mix_Fading(Mix_Fading fading)
{
	return Val_int(fading);
}

/* music_type type */

static inline value Val_Mix_MusicType(Mix_MusicType music_type)
{
	return Val_int(music_type);
}

/* chunk type (unmanaged) */

static inline value Val_Mix_Chunk(Mix_Chunk *chunk)
{
	return (value)chunk;
}

static inline Mix_Chunk *Mix_Chunk_val(value v)
{
	return (Mix_Chunk *)v;
}

/* music type (unmanaged) */

static inline value Val_Mix_Music(Mix_Music *music)
{
	return (value)music;
}

static inline Mix_Music *Mix_Music_val(value v)
{
	return (Mix_Music *)v;
}

/* exception */

static void raise_failure(void)
{
	raise_with_string(*caml_named_value("SDL_failure"), Mix_GetError());
}

/* utilitiy primitive */

CAMLprim value sdlmixerutil_little_endian(value unit)
{
	CAMLparam1(unit);
	value result;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	result = Val_true;
#else
	result = Val_false;
#endif
	CAMLreturn(result);
}

/* primitives */

CAMLprim value sdlmixerstub_linked_version(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	SDL_version const *version = Mix_Linked_Version();
	result = alloc(3, 0);
	Store_field(result, 0, Val_int(version->major));
	Store_field(result, 1, Val_int(version->minor));
	Store_field(result, 2, Val_int(version->patch));
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_init(value flags)
{
	CAMLparam1(flags);
	Mix_Init(Initflags_val(flags));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_quit(value unit)
{
	CAMLparam1(unit);
	Mix_Quit();
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_open_audio(value frequency, value format, value channels, value chunksize)
{
	CAMLparam4(frequency, format, channels, chunksize);
	if(Mix_OpenAudio(Int_val(frequency), Sample_type_val(format), Int_val(channels), Int_val(chunksize)) == -1){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_allocate_channels(value numchans)
{
	CAMLparam1(numchans);
	int channel = Mix_AllocateChannels(Int_val(numchans));
	value result = Val_int(channel);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_query_spec(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	int frequency;
	Uint16 format;
	int channels;
	if(! Mix_QuerySpec(&frequency, &format, &channels)){
		raise_failure();
	}
	result = caml_alloc_tuple(3);
	Field(result, 0) = Val_int(frequency);
	Field(result, 1) = Val_sample_type(format);
	Field(result, 2) = Val_int(channels);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_load_wav(value file)
{
	CAMLparam1(file);
	Mix_Chunk *chunk = Mix_LoadWAV(String_val(file));
	if(chunk == NULL){
		raise_failure();
	}
	value result = Val_Mix_Chunk(chunk);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_load_mus(value file)
{
	CAMLparam1(file);
	Mix_Music *music = Mix_LoadMUS(String_val(file));
	if(music == NULL){
		raise_failure();
	}
	value result = Val_Mix_Music(music);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_quick_load_wav(value mem)
{
	CAMLparam1(mem);
	Mix_Chunk *chunk = Mix_QuickLoad_WAV(Caml_ba_data_val(mem));
	value result = Val_Mix_Chunk(chunk);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_quick_load_raw(value mem)
{
	CAMLparam1(mem);
	Mix_Chunk *chunk = Mix_QuickLoad_RAW(Caml_ba_data_val(mem), Caml_ba_array_val(mem)->dim[0]);
	value result = Val_Mix_Chunk(chunk);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_free_chunk(value chunk)
{
	CAMLparam1(chunk);
	Mix_FreeChunk(Mix_Chunk_val(chunk));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_free_music(value music)
{
	CAMLparam1(music);
	Mix_FreeMusic(Mix_Music_val(music));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_get_num_chunk_decoders(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = Val_int(Mix_GetNumChunkDecoders());
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_get_chunk_decoder(value index)
{
	CAMLparam1(index);
	CAMLlocal1(result);
	result = caml_copy_string(Mix_GetChunkDecoder(Int_val(index)));
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_get_num_music_decoders(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = Val_int(Mix_GetNumMusicDecoders());
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_get_music_decoder(value index)
{
	CAMLparam1(index);
	CAMLlocal1(result);
	result = caml_copy_string(Mix_GetMusicDecoder(Int_val(index)));
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_get_music_type(value music)
{
	CAMLparam1(music);
	Mix_MusicType music_type = Mix_GetMusicType(Mix_Music_val(music));
	value result = Val_Mix_MusicType(music_type);
	CAMLreturn(result);
}

static void MixFunc(void *udata, Uint8 *stream, int len)
{
	CAMLparam0();
	CAMLlocal2(mix_func, byte_array);
	mix_func = (value)udata;
	byte_array = alloc_bigarray_dims(BIGARRAY_UINT8 | BIGARRAY_C_LAYOUT, 1, stream, len);
	caml_callback(mix_func, byte_array);
	CAMLreturn0;
}

static value mix_func = Val_unit;
static int mix_func_registered = 0;

CAMLprim value sdlmixerstub_set_post_mix(value the_mix_func)
{
	CAMLparam1(mix_func);
	if(! mix_func_registered){
		mix_func_registered = 1;
		caml_register_global_root(&mix_func);
	}
	mix_func = the_mix_func;
	if(the_mix_func != Val_unit){
		Mix_SetPostMix(MixFunc, (void *)the_mix_func);
	}else{
		Mix_SetPostMix(NULL, NULL);
	}
	CAMLreturn(Val_unit);
}

static void EffectFunc(int chan, void *stream, int len, void *udata)
{
	CAMLparam0();
	CAMLlocal3(list, f, byte_array);
	list = (value)udata;
	f = hd(list);
	byte_array = alloc_bigarray_dims(BIGARRAY_UINT8 | BIGARRAY_C_LAYOUT, 1, stream, len);
	caml_callback2(f, Val_int(chan), byte_array);
	CAMLreturn0;
}

static void EffectDone(int chan, void *udata)
{
	CAMLparam0();
	CAMLlocal2(list, d);
	list = (value)udata;
	d = hd(tl(list));
	caml_callback(d, Val_int(chan));
	CAMLreturn0;
}

static value effect_list = Val_emptylist;
static int effect_list_registered = 0;

CAMLprim value sdlmixerstub_register_effect(value chan, value f, value d)
{
	CAMLparam3(chan, f, d);
	Mix_EffectFunc_t c_f;
	Mix_EffectDone_t c_d;
	if(! effect_list_registered){
		effect_list_registered = 1;
		caml_register_global_root(&effect_list);
	}
	effect_list = cons(d, effect_list);
	effect_list = cons(f, effect_list);
	c_f = Is_block(f) ? EffectFunc : NULL;
	c_d = Is_block(d) ? EffectDone : NULL;
	Mix_RegisterEffect(Int_val(chan), c_f, c_d, (void *)effect_list);
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_unregister_all_effects(value channel)
{
	CAMLparam1(channel);
	Mix_UnregisterAllEffects(Int_val(channel));
	effect_list = Val_emptylist;
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_set_panning(value channel, value left, value right)
{
	CAMLparam3(channel, left, right);
	if(! Mix_SetPanning(Int_val(channel), Int_val(left), Int_val(right))){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_set_position(value channel, value angle, value distance)
{
	CAMLparam3(channel, angle, distance);
	if(! Mix_SetPosition(Int_val(channel), Int_val(angle), Int_val(distance))){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_set_distance(value channel, value distance)
{
	CAMLparam2(channel, distance);
	if(! Mix_SetDistance(Int_val(channel), Int_val(distance))){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_set_reverse_stereo(value channel, value flip)
{
	CAMLparam2(channel, flip);
	if(! Mix_SetReverseStereo(Int_val(channel), Bool_val(flip))){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_reserve_channels(value num)
{
	CAMLparam1(num);
	value result = Val_int(Mix_ReserveChannels(Int_val(num)));
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_group_channel(value which, value tag)
{
	CAMLparam2(which, tag);
	if(! Mix_GroupChannel(Int_val(which), Int_val(tag))){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_group_channels(value from, value to, value tag)
{
	CAMLparam3(from, to, tag);
	if(Mix_GroupChannels(Int_val(from), Int_val(to), Int_val(tag)) != to - from + 1){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_group_available(value tag)
{
	CAMLparam1(tag);
	int available = Mix_GroupAvailable(Int_val(tag));
	value result = Val_bool(available);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_group_count(value tag)
{
	CAMLparam1(tag);
	int count = Mix_GroupCount(Int_val(tag));
	value result = Val_int(count);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_group_oldest(value tag)
{
	CAMLparam1(tag);
	int found_channel = Mix_GroupOldest(Int_val(tag));
	value result = Val_int(found_channel);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_group_newer(value tag)
{
	CAMLparam1(tag);
	int found_channel = Mix_GroupNewer(Int_val(tag));
	value result = Val_int(found_channel);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_play_channel_timed(value channel, value chunk, value loops, value ticks)
{
	CAMLparam4(channel, chunk, loops, ticks);
	int playing_channel = Mix_PlayChannelTimed(Int_val(channel), Mix_Chunk_val(chunk), Int_val(loops), Int_val(ticks));
	value result = Val_int(playing_channel);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_play_music(value music, value loops)
{
	CAMLparam2(music, loops);
	int playing_channel = Mix_PlayMusic(Mix_Music_val(music), Int_val(loops));
	value result = Val_int(playing_channel);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_fade_in_music(value music, value loops, value ms)
{
	CAMLparam3(music, loops, ms);
	if(Mix_FadeInMusic(Mix_Music_val(music), Int_val(loops), Int_val(ms)) == -1){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_fade_in_music_pos(value music, value loops, value ms, value position)
{
	CAMLparam4(music, loops, ms, position);
	if(Mix_FadeInMusicPos(Mix_Music_val(music), Int_val(loops), Int_val(ms), Double_val(position)) == -1){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_fade_in_channel_timed(value channel, value chunk, value loops, value ms, value ticks)
{
	CAMLparam5(channel, chunk, loops, ms, ticks);
	if(Mix_FadeInChannelTimed(Int_val(channel), Mix_Chunk_val(chunk), Int_val(loops), Int_val(ms), Int_val(ticks)) == -1){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_volume(value channel, value volume)
{
	CAMLparam2(channel, volume);
	int old = Mix_Volume(Int_val(channel), Int_val(volume));
	value result = Val_int(old);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_volume_chunk(value chunk, value volume)
{
	CAMLparam2(chunk, volume);
	int old = Mix_VolumeChunk(Mix_Chunk_val(chunk), Int_val(volume));
	value result = Val_int(old);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_volume_music(value volume)
{
	CAMLparam1(volume);
	int old = Mix_VolumeMusic(Int_val(volume));
	value result = Val_int(old);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_halt_channel(value channel)
{
	CAMLparam1(channel);
	Mix_HaltChannel(Int_val(channel));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_halt_group(value tag)
{
	CAMLparam1(tag);
	Mix_HaltGroup(Int_val(tag));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_halt_music(value unit)
{
	CAMLparam1(unit);
	Mix_HaltMusic();
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_expire_channel(value channel, value ticks)
{
	CAMLparam2(channel, ticks);
	Mix_ExpireChannel(Int_val(channel), Int_val(ticks));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_fade_out_channel(value which, value ms)
{
	CAMLparam2(which, ms);
	Mix_FadeOutChannel(Int_val(which), Int_val(ms));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_fade_out_group(value tag, value ms)
{
	CAMLparam2(tag, ms);
	Mix_FadeOutGroup(Int_val(tag), Int_val(ms));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_fade_out_music(value ms)
{
	CAMLparam1(ms);
	Mix_FadeOutMusic(Int_val(ms));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_fading_music(value unit)
{
	CAMLparam1(unit);
	Mix_Fading fading = Mix_FadingMusic();
	value result = Val_Mix_Fading(fading);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_fading_channel(value which)
{
	CAMLparam1(which);
	Mix_Fading fading = Mix_FadingChannel(Int_val(which));
	value result = Val_Mix_Fading(fading);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_pause(value channel)
{
	CAMLparam1(channel);
	Mix_Pause(channel);
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_resume(value channel)
{
	CAMLparam1(channel);
	Mix_Resume(channel);
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_paused(value channel)
{
	CAMLparam1(channel);
	CAMLlocal1(result);
	int playing = Mix_Paused(Int_val(channel));
	result = Val_bool(playing);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_pause_music(value unit)
{
	CAMLparam1(unit);
	Mix_PauseMusic();
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_resume_music(value unit)
{
	CAMLparam1(unit);
	Mix_ResumeMusic();
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_rewind_music(value unit)
{
	CAMLparam1(unit);
	Mix_RewindMusic();
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_paused_music(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	int playing = Mix_PausedMusic();
	result = Val_bool(playing);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_set_music_position(value position)
{
	CAMLparam1(position);
	if(Mix_SetMusicPosition(Double_val(position)) == -1){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_playing(value channel)
{
	CAMLparam1(channel);
	CAMLlocal1(result);
	int playing = Mix_Playing(channel);
	result = Val_bool(playing);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_playing_music(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	int playing = Mix_PlayingMusic();
	result = Val_bool(playing);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_set_music_cmd(value command)
{
	CAMLparam1(command);
	if(Mix_SetMusicCMD(String_val(command)) == -1){
		raise_failure();
	}
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_set_synchro_value(value the_value)
{
	CAMLparam1(the_value);
	Mix_SetSynchroValue(Int_val(the_value));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_get_synchro_value(value unit)
{
	CAMLparam1(unit);
	int the_value = Mix_GetSynchroValue();
	value result = Val_int(the_value);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_set_sound_fonts(value paths)
{
	CAMLparam1(paths);
	Mix_SetSoundFonts(String_val(paths));
	CAMLreturn(Val_unit);
}

CAMLprim value sdlmixerstub_get_sound_fonts(value unit)
{
	CAMLparam1(unit);
	value result = caml_copy_string(Mix_GetSoundFonts());
	CAMLreturn(result);
}

static int EachSoundFont(char const *paths, void *data)
{
	CAMLparam0();
	CAMLlocal1(function);
	function = (value)data;
	value result = Val_int(caml_callback(function, caml_copy_string(paths)));
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_each_sound_font(value function)
{
	CAMLparam1(function);
	value result = Val_int(Mix_EachSoundFont(EachSoundFont, (void *)function));
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_get_chunk(value channel)
{
	CAMLparam1(channel);
	Mix_Chunk *chunk = Mix_GetChunk(Int_val(channel));
	if(chunk == NULL){
		raise_failure();
	}
	value result = Val_Mix_Chunk(chunk);
	CAMLreturn(result);
}

CAMLprim value sdlmixerstub_close_audio(value unit)
{
	CAMLparam1(unit);
	Mix_CloseAudio();
	CAMLreturn(Val_unit);
}

