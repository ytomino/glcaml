/*
 * sdlcaml - Objective Caml interface for the SDL library
 * SDL Mixer interface
 * Copyright (C) 2010 Einar Lielmanis, einars@gmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2, as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Library General Public License version 2 for more details
 * (enclosed in the file LGPL).
 */


#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "caml.h"

// thanks to OCamlSDL for the insight.
// Mix_Chunk and Mix_Music get stuffed into Abstract_tag values
// and treated as simple blobs in ocaml.
value abstract_ptr(void *p)
{
    value v = alloc_small(1, Abstract_tag);
    Field(v, 0) = Val_bp(p);
    return v;
}

void nullify_abstract(value v)
{
    Field(v, 0) = Val_bp(NULL);
}

#define SDL_CHUNK(chunk) ((Mix_Chunk *)Field((chunk), 0))
#define ML_CHUNK(chunk) abstract_ptr(chunk)
#define SDL_MUSIC(chunk) ((Mix_Music *)Field((chunk), 0))
#define ML_MUSIC(chunk) abstract_ptr(chunk)



value sdlmixer_get_version (value u)
{
    CAMLparam1(u);

    char tmp[250];
    const SDL_version* version;
    version = Mix_Linked_Version();
    snprintf(tmp, 250, "%d.%d.%d", version->major, version->minor, version->patch);

    CAMLreturn (copy_string(tmp));
}

#define FLAC_tag 0
#define MOD_tag  1
#define MP3_tag  2
#define OGG_tag  3

int _sdlmixer_init_flag_val (value flag_list)
{
    CAMLparam1(flag_list);

    int flag = 0;
    value l = flag_list;
    while (is_not_nil(l))
    {
        switch (Int_val(hd(l)))
        {
        case FLAC_tag: flag |= MIX_INIT_FLAC; break;
        case MOD_tag : flag |= MIX_INIT_MOD; break;
        case MP3_tag : flag |= MIX_INIT_MP3; break;
        case OGG_tag : flag |= MIX_INIT_OGG; break;
        }
        l = tl(l);
    }

    CAMLreturn (flag);
}


int _sdlmixer_fading_to_caml (Mix_Fading f)
{
    switch (f) {
        case MIX_NO_FADING: return 0;
        case MIX_FADING_OUT: return 1;
        case MIX_FADING_IN: return 2;
    }
    return 0;
}

value sdlmixer_get_last_error (value u)
{
    CAMLparam1(u);
    CAMLreturn (copy_string(Mix_GetError()));
}


value sdlmixer_init (value vf)
{
    CAMLparam1(vf);
    int flags = _sdlmixer_init_flag_val(vf);
    int res = Mix_Init(flags);

    if (res == 0) {
        caml_failwith (SDL_GetError());
    }

    CAMLreturn (Val_unit);
}


value sdlmixer_open_audio (value freq, value format, value channels, value chunksize)
{
    CAMLparam4 (freq, format, channels, chunksize);
    int res = Mix_OpenAudio(Int_val(freq), Int_val(format), Int_val(channels), Int_val(chunksize));

    if (res != 0) {
        caml_failwith (SDL_GetError());
    }
    CAMLreturn (Val_unit);
}


value sdlmixer_quit (value u)
{
    Mix_Quit();
    return Val_unit;
}


value sdlmixer_allocate_channels (value c)
{
    int new_channels = Mix_AllocateChannels(Int_val(c));
    return Val_int(new_channels);
}


value sdlmixer_load_wav (value file_name)
{
    CAMLparam1 (file_name);

    Mix_Chunk *chunk = Mix_LoadWAV(String_val(file_name));
    if (chunk == NULL) {
        caml_failwith(SDL_GetError());
    }

    CAMLreturn (abstract_ptr(chunk));
}

value sdlmixer_load_mus (value file_name)
{
    CAMLparam1 (file_name);
    Mix_Music *music = Mix_LoadMUS(String_val(file_name));
    if (music == NULL) {
        caml_failwith(SDL_GetError());
    }
    CAMLreturn (ML_CHUNK(music));

}

value sdlmixer_free_chunk (value chunk)
{
    CAMLparam1 (chunk);
    Mix_FreeChunk (SDL_CHUNK(chunk));
    nullify_abstract(chunk);
    CAMLreturn (Val_unit);
}


value sdlmixer_free_music (value music_chunk)
{
    CAMLparam1 (music_chunk);
    Mix_FreeMusic(SDL_MUSIC(music_chunk));
    nullify_abstract(music_chunk);
    CAMLreturn (Val_unit);
}


value sdlmixer_play_channel (value channel, value chunk, value loops)
{
    CAMLparam3 (channel, chunk, loops);
    int ch = Mix_PlayChannel(Int_val(channel), SDL_CHUNK(chunk), Int_val(loops));
    CAMLreturn(Val_int(ch));

}

value sdlmixer_play_channel_timed (value channel, value chunk, value loops, value ms)
{
    CAMLparam4 (channel, chunk, loops, ms);
    int res = Mix_PlayChannelTimed(Int_val(channel), SDL_CHUNK(chunk), Int_val(loops), Int_val(ms));
    CAMLreturn(Val_bool(res == 0));

}

value sdlmixer_volume (value channel, value volume)
{
    int vol = Mix_Volume (Int_val(channel), Int_val(volume));
    return Val_int(vol);
}


value sdlmixer_volume_chunk (value chunk, value volume)
{
    CAMLparam2 (chunk, volume);
    int vol = Mix_VolumeChunk (SDL_CHUNK(chunk), Int_val(volume));
    CAMLreturn (Val_int(vol));
}


value sdlmixer_volume_music (value volume)
{
    int vol = Mix_VolumeMusic (Int_val(volume));
    return Val_int(vol);
}


value sdlmixer_play_music (value music_chunk, value loops)
{
    CAMLparam2 (music_chunk, loops);
    int res = Mix_PlayMusic(SDL_MUSIC(music_chunk), Int_val(loops));
    CAMLreturn(Val_bool(res == 0));
}


value sdlmixer_get_chunk_decoders (value u)
{
    CAMLparam1 (u);
    CAMLlocal2 (r, t);
    int i;
    const char* decoder_name;

    int decoder_count = Mix_GetNumChunkDecoders();
    if (decoder_count == 0) {
        r = Val_int(0);
    } else {
        r = alloc(2, 0);
        decoder_name = Mix_GetChunkDecoder(0);
        Store_field(r, 0, copy_string(decoder_name));
        t = r;
        for (i = 1; i < decoder_count; i++) {
            Field(t, 1) = alloc(2, 0);
            t = Field(t, 1);
            decoder_name = Mix_GetChunkDecoder(i);
            Store_field(t, 0, copy_string(decoder_name));
        }
        Store_field(t, 1, Val_int(0));
    }

    CAMLreturn (r);
}


value sdlmixer_get_music_decoders (value u)
{
    CAMLparam1 (u);
    CAMLlocal2 (r, t);
    int i;
    const char* decoder_name;

    int decoder_count = Mix_GetNumMusicDecoders();
    if (decoder_count == 0) {
        r = Val_int(0);
    } else {
        r = alloc(2, 0);
        decoder_name = Mix_GetMusicDecoder(0);
        Store_field(r, 0, copy_string(decoder_name));
        t = r;
        for (i = 1; i < decoder_count; i++) {
            Field(t, 1) = alloc(2, 0);
            t = Field(t, 1);
            decoder_name = Mix_GetMusicDecoder(i);
            Store_field(t, 0, copy_string(decoder_name));
        }
        Store_field(t, 1, Val_int(0));
    }

    CAMLreturn (r);
}


value sdlmixer_get_music_type (value opt_music)
{
    Mix_Music *music = Opt_arg(opt_music, SDL_MUSIC, NULL);
    int music_type = 0;
    switch (Mix_GetMusicType(music)) {
    case MUS_CMD     : music_type = 1; break;
    case MUS_WAV     : music_type = 2; break;
    case MUS_MOD     : music_type = 3; break;
    case MUS_MID     : music_type = 4; break;
    case MUS_OGG     : music_type = 5; break;
    case MUS_MP3     : music_type = 6; break;
    case MUS_MP3_MAD : music_type = 7; break;
    case MUS_FLAC    : music_type = 8; break;
    }
    return Val_int(music_type);
}


value sdlmixer_set_panning (value channel, value left, value right)
{
    int res = Mix_SetPanning(Int_val(channel), Int_val(left), Int_val(right));
    return Val_bool(res);

}


value sdlmixer_set_position (value channel, value angle, value distance)
{
    int res = Mix_SetPosition(Int_val(channel), Int_val(angle), Int_val(distance));
    return Val_bool(res);
}


value sdlmixer_set_distance (value channel, value distance)
{
    int res = Mix_SetDistance(Int_val(channel), Int_val(distance));
    return Val_bool(res);
}

value sdlmixer_set_reverse_stereo (value channel, value flip)
{
    int res = Mix_SetReverseStereo(Int_val(channel), Bool_val(flip));
    return Val_bool(res);
}

value sdlmixer_reserve_channels (value channel_count)
{
    int reserved_channels = Mix_ReserveChannels(Int_val(channel_count));
    return Val_int(reserved_channels);

}


value sdlmixer_group_channel (value channel, value tag)
{
    int res = Mix_GroupChannel(Int_val(channel), Int_val(tag));
    return Val_bool(res);
}


value sdlmixer_group_channels (value channel_start, value channel_end, value tag)
{
    int res = Mix_GroupChannels(Int_val(channel_start), Int_val(channel_end), Int_val(tag));
    return Val_bool(res);
}

value sdlmixer_group_available (value tag)
{
    int channel = Mix_GroupAvailable(Int_val(tag));
    return Val_int(channel);
}

value sdlmixer_group_count (value tag)
{
    int channel_count = Mix_GroupCount(Int_val(tag));
    return Val_int(channel_count);
}

value sdlmixer_group_oldest (value tag)
{
    int channel = Mix_GroupOldest(Int_val(tag));
    return Val_int(channel);
}

value sdlmixer_group_newer (value tag)
{
    int channel = Mix_GroupNewer(Int_val(tag));
    return Val_int(channel);
}



value sdlmixer_fade_in_music (value music, value loops, value ms)
{
    CAMLparam3 (music, loops, ms);
    int res = Mix_FadeInMusic (SDL_MUSIC(music), Int_val(loops), Int_val(ms));
    CAMLreturn (Val_bool(res == 0));
}

value sdlmixer_fade_in_music_pos (value music, value loops, value ms, value pos)
{
    CAMLparam4 (music, loops, ms, pos);
    int res = Mix_FadeInMusicPos (SDL_MUSIC(music), Int_val(loops), Int_val(ms), Double_val(pos));
    CAMLreturn (Val_bool(res == 0));
}

value sdlmixer_fade_in_channel (value channel, value chunk, value loops, value ms)
{
    CAMLparam4 (channel, chunk, loops, ms);
    int ch = Mix_FadeInChannel (Int_val(ch), SDL_CHUNK(chunk), Int_val(loops), Int_val(ms));
    CAMLreturn (Val_int(ch));
}

value sdlmixer_fade_in_channel_timed (value channel, value chunk, value loops, value ms, value ticks)
{
    CAMLparam5 (channel, chunk, loops, ms, ticks);
    int ch = Mix_FadeInChannelTimed (Int_val(ch), SDL_CHUNK(chunk), Int_val(loops), Int_val(ms), Int_val(ticks));
    CAMLreturn (Val_int(ch));
}

value sdlmixer_halt_channel (value channel)
{
    Mix_HaltChannel(Int_val(channel));
    return Val_unit;
}

value sdlmixer_halt_group (value tag)
{
    Mix_HaltChannel(Int_val(tag));
    return Val_unit;
}

value sdlmixer_halt_music (value u)
{
    Mix_HaltMusic();
    return Val_unit;
}


value sdlmixer_expire_channel (value channel, value ticks)
{
    int res = Mix_ExpireChannel(Int_val(channel), Int_val(ticks));
    return Val_bool(res != 0);

}

value sdlmixer_fade_out_channel (value channel, value ms)
{
    int res = Mix_FadeOutChannel(Int_val(channel), Int_val(ms));
    return Val_bool(res);
}

value sdlmixer_fade_out_group (value group, value ms)
{
    int res = Mix_FadeOutGroup(Int_val(group), Int_val(ms));
    return Val_bool(res);
}

value sdlmixer_fade_out_music (value ms)
{
    CAMLparam1 (ms);
    int res = Mix_FadeOutMusic(Int_val(ms));
    return Val_bool(res);
}

value sdlmixer_fading_music (value u)
{
    Mix_Fading f = Mix_FadingMusic();
    return Val_int(_sdlmixer_fading_to_caml(f));
}

value sdlmixer_fading_channel (value channel)
{
    Mix_Fading f = Mix_FadingChannel(Int_val(channel));
    return Val_int(_sdlmixer_fading_to_caml(f));
}


value sdlmixer_pause (value channel)
{
    Mix_Pause(Int_val(channel));
    return Val_unit;
}

value sdlmixer_resume (value channel)
{
    Mix_Resume(Int_val(channel));
    return Val_unit;
}

value sdlmixer_paused (value channel)
{
    int res = Mix_Paused(Int_val(channel));
    return Val_bool(res);
}

value sdlmixer_pause_music (value u)
{
    Mix_PauseMusic();
    return Val_unit;
}

value sdlmixer_resume_music (value u)
{
    Mix_ResumeMusic();
    return Val_unit;
}

value sdlmixer_rewind_music (value u)
{
    Mix_RewindMusic();
    return Val_unit;
}

value sdlmixer_paused_music (value u)
{
    int res = Mix_PausedMusic();
    return Val_bool(res);
}

value sdlmixer_set_music_position (value position)
{
    int res = Mix_SetMusicPosition(Double_val(position));
    return Val_bool(res == 0);
}

value sdlmixer_playing (value channel)
{
    int res = Mix_Playing(Int_val(channel));
    return Val_bool(res);
}

value sdlmixer_playing_music (value u)
{
    int res = Mix_PlayingMusic();
    return Val_bool(res);
}

value sdlmixer_set_music_cmd (value command)
{
    int res = Mix_SetMusicCMD(String_val(command));
    return Val_bool(res == 0);
}

value sdlmixer_get_chunk (value channel)
{
    CAMLparam1(channel);
    Mix_Chunk* chunk = Mix_GetChunk(Int_val(channel));
    CAMLreturn (ML_CHUNK(chunk));
}

value sdlmixer_close_audio (value u)
{
    Mix_CloseAudio();
    return Val_unit;
}

#ifdef __APPLE__
int main(int argc, char **argv)
{
   caml_main(argv);
   return 0;
}
#endif
