#include <SDL/SDL.h>


/* Ugly: SDL_AudioSpec has a field called "callback" which caml/callback.h redefines to caml_callback.
So this function has to come before the caml #includes*/
static void set_audiospec(SDL_AudioSpec *in, int freq, int format, int channels, int samples, void (*callback)(void *userdata, Uint8 *stream, int len))
{
    in->freq = freq;
    in->format = format;
    in->channels = channels;
    in->samples = samples;
    in->callback = callback;
    in->userdata = NULL;
}


/*  CAML - C interface */
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/bigarray.h>
#include <caml/threads.h>


/* audio */
static void __audio_callback(__attribute__((unused)) void *userdata, unsigned char *stream, int len)
{
    caml_c_thread_register();
    caml_leave_blocking_section();
    caml_callback(*caml_named_value("ml_setaudiocallback"), alloc_bigarray_dims(BIGARRAY_UINT8 | BIGARRAY_C_LAYOUT, 1, stream, len));
    caml_enter_blocking_section();
}



value sdlstub_open_audio(value freq, value format, value channels, value samples) {
    CAMLparam4 (freq, format, channels, samples);
    CAMLlocal1 (result);
    SDL_AudioSpec input, output;
    result = caml_alloc (6, 0);
    set_audiospec(&input, Int_val(freq),Int_val(format),Int_val(channels),Int_val(samples), __audio_callback);
    set_audiospec(&output, 0,0,0,0, NULL);
    SDL_OpenAudio(&input, &output);
    Store_field (result, 0, Val_int((int)output.freq));
    Store_field (result, 1, Val_int((int)output.format));
    Store_field (result, 2, Val_int((int)output.channels));
    Store_field (result, 3, Val_int((int)output.silence));
    Store_field (result, 4, Val_int((int)output.samples));
    Store_field (result, 5, Val_int((int)output.size));
    CAMLreturn (result);
}


value sdlstub_close_audio(value u) {
    CAMLparam1(u);
    SDL_CloseAudio();
    CAMLreturn (Val_unit);
}

value sdlstub_load_wav(value file) {
    CAMLparam1(file);
    CAMLlocal1 (result);
    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;
    char *filename = String_val(file);
    result = caml_alloc (7, 0);
    if( SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL ){
        caml_failwith(SDL_GetError());
    }
    Store_field (result, 0, Val_int((int)wav_spec.freq));
    Store_field (result, 1, Val_int((int)wav_spec.format));
    Store_field (result, 2, Val_int((int)wav_spec.channels));
    Store_field (result, 3, Val_int((int)wav_spec.silence));
    Store_field (result, 4, Val_int((int)wav_spec.samples));
    Store_field (result, 5, Val_int((int)wav_spec.size));
    Store_field (result, 6, alloc_bigarray_dims(BIGARRAY_UINT8 | BIGARRAY_C_LAYOUT, 1, wav_buffer, wav_length));
    CAMLreturn (result);
}


value sdlstub_free_wav(value wav) {
    CAMLparam1(wav);
    SDL_FreeWAV(Data_bigarray_val(wav));
    CAMLreturn (Val_unit);
}

value sdlstub_pause_audio(value on) {
    CAMLparam1(on);
    int p =  0;
    if (Bool_val(on)) p = 1;
    SDL_PauseAudio(p);
    CAMLreturn (Val_unit);
}

value sdlstub_lock_audio(value u) {
    CAMLparam1(u);
    SDL_LockAudio();
    CAMLreturn(Val_unit);
}

value sdlstub_unlock_audio(value u) {
    CAMLparam1(u);
    SDL_UnlockAudio();
    CAMLreturn(Val_unit);
}

value sdlstub_get_audio_status(value u) {
    CAMLparam1(u);
    CAMLreturn (Val_int(SDL_GetAudioStatus()));
}

value sdlstub_mix_audio(value b1, value b2, value volume){
    CAMLparam3(b1, b2, volume);
    SDL_MixAudio(Data_bigarray_val(b1), Data_bigarray_val(b2), Bigarray_val(b1)->dim[0], Int_val(volume));
    CAMLreturn (Val_unit);
}

value sdlstub_convert_audio(value from_format, value from_channels, value from_freq,
                            value to_format, value to_channels, value to_freq, value buffer){
    CAMLparam5(from_format, from_channels, from_freq, to_format, to_channels);
    CAMLxparam2(to_freq, buffer);
    SDL_AudioCVT  wav_cvt;
    int wav_len = Bigarray_val(buffer)->dim[0];
    unsigned char *wav_buf = Data_bigarray_val(buffer);
    if(!SDL_BuildAudioCVT(&wav_cvt, Int_val(from_format), Int_val(from_channels), Int_val(from_freq),
                        Int_val(to_format), Int_val(to_channels), Int_val(to_freq)) ){
        caml_failwith("Unable to carry out conversion");
    }
    wav_cvt.buf = malloc(wav_len * wav_cvt.len_mult);
    wav_cvt.len = wav_len;
    memcpy(wav_cvt.buf, wav_buf, wav_len);
    SDL_ConvertAudio(&wav_cvt);
    CAMLreturn (alloc_bigarray_dims(BIGARRAY_UINT8 | BIGARRAY_C_LAYOUT, 1, wav_cvt.buf, wav_len * wav_cvt.len_mult));
}

value sdlstub_convert_audio_byte(value * argv, __attribute__((unused)) int n){
    return sdlstub_convert_audio (argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

/* Audio effects */

// Author: A. Umbach sdl@lokigames.com
static int fxShift(double pitch, Uint8 *source, Uint8 *target, int len) {
    int i, j, k;
    double l;
    double pa = 0;
    double shift = pitch > 0 ? pitch : 0;
    len /= 4;
    for(i = 0; i < len; i++) { // LR pairs
        for(j = 0; j < 2; j++) { // channels
            pa = i * shift;
            k = (int) pa;
            l = pa - k;
            *(Sint16*) (target + 2 * j + 4 * i) +=
            ( *(Sint16*) (source + 2 * j + 4 * (k + 0) ) * ( 1 - l ) +
            *(Sint16*) (source + 2 * j + 4 * (k + 2) ) * ( l ) );
        }
    }
    return ( (int)(len * shift + 0.49999) ) * 4;
}

value fxstub_shift(value shift, value source, value target)
{
    CAMLparam3(shift, source, target);
    int consumed = 0;
    consumed = fxShift(Double_val(shift), Data_bigarray_val(source), Data_bigarray_val(target), Bigarray_val(target)->dim[0] );
    CAMLreturn (Val_int(consumed));
}

// Author: A. Umbach sdl@lokigames.com
static void fxPan(double pan, double vol, Uint8 *buf, Uint8 *out, int len) {
    int i;
    double left_vol =  - vol * ( -1.0 + pan ) / 2.0;
    double right_vol = vol * ( 1.0 + pan ) / 2.0;

    // Guards
    if(left_vol < 0)left_vol = 0;
    if(left_vol > 1)left_vol = 1;
    if(right_vol < 0)right_vol = 0;
    if(right_vol > 1)right_vol = 1;

    for(i = 0; i < len; i += 4) {
        *(Sint16*) (out + i) = *(Sint16*) (buf + i) * left_vol;
        *(Sint16*) (out + i + 2) = *(Sint16*) (buf + i + 2) * right_vol;
    }
}

value fxstub_pan(value pan, value vol, value buf, value out)
{
    CAMLparam4(pan, vol, buf, out);
    fxPan(Double_val(pan), Double_val(vol), Data_bigarray_val(buf), Data_bigarray_val(out), Bigarray_val(buf)->dim[0]);
    CAMLreturn (Val_unit);
}
