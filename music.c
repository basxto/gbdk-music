#include "music.h"
#include "sound.c"
//#include "music/the_journey_begins.c"

// see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
// see https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware

// enable/disable channels
#define WAVE
#define PULSE
#define NOISE

UINT8 music_counter;
UINT8 tick_counter;

Song *current_song;

void blinger(const UINT8 note, const UINT8 wait, const UINT8 note2, const UINT8 wait2, const UINT8 note3) {
    NR10_REG = 0x00; // no sweep
    NR11_REG = 0x50; // 50% duty

    NR12_REG = 0xF0; // constant volume envelope
    NR14_REG = 0xC0 | note2int_hi(note); // msb
    NR13_REG = note2int_lo(note);        // lsb

    // could pack that on a sound buffer and let tick hanlde it
    for(int i = 0; i < wait; ++i)
        wait_vbl_done();
    NR12_REG = 0xF0;
    NR14_REG = 0xC0 | note2int_hi(note2);
    NR13_REG = note2int_lo(note2);
    for(int i = 0; i < wait2; ++i)
        wait_vbl_done();
    NR12_REG = 0xF1; // falling volume envelope
    NR14_REG = 0xC0 | note2int_hi(note3);
    NR13_REG = note2int_lo(note3);
}

void plonger(const UINT8 note, const UINT8 duty, const INT8 arp) {
    NR12_REG = 0xF7; // volume envelope
    if(arp >= 0)
        NR10_REG = 0x10 | arp; // arpeggio
    else
        NR10_REG = 0x10 | 0x08 | -arp;
    
    NR11_REG = duty;

    NR14_REG = 0xC0 | note2int_hi(note);
    NR13_REG = note2int_lo(note);
}

void init_music(Song *song) {
    NR52_REG = 0x80; // enable sound
    NR50_REG = 0x77; // full volume
    NR51_REG = 0xFF; // all channels
    current_song = song;
    music_counter = 0;
    tick_counter = 0;
}

// access arrays via pointer
#define current_sf() (current_song->arrangement[music_counter / current_song->pattern_size])
#define current_pf(pttrn, pttrn_frame) (current_song->pattern + ((pttrn) * current_song->pattern_size) + (pttrn_frame))

inline void subtick_music(){
    UINT8 pttrn_frame = music_counter % current_song->pattern_size;
    UINT8 pttrn = current_sf().pulse_pattern;
    const Pattern_frame *pat = current_pf(pttrn, pttrn_frame);
    UINT8 tl;// trigger and length enable

#ifdef PULSE
    tl = 0xC0;
    // instrument
    switch ((pat->pulse_vi & 0x0F)) {
    case 8:
        NR22_REG = 0x00 | (pat->pulse_vi & 0xF0); // continuous tone
        NR21_REG = 0x90;
        tl = 0x80; // don't disable after time
        break;
    case 7:
        NR22_REG = 0x02 | (pat->pulse_vi & 0xF0); // volume envelope
        NR21_REG = 0x50;                          // 50% duty
        break;
    case 6:
        NR22_REG = 0x07 | (pat->pulse_vi & 0xF0); // volume envelope
        NR21_REG = 0x90;                          // 75% duty
        break;
    }

    if (pat->pulse_note != 0xFF) {
        NR24_REG = tl | note2int_hi(pat->pulse_note); // msb
        NR23_REG = note2int_lo(pat->pulse_note);
    }
#endif

#ifdef WAVE
    tl = 0xC0;
    pttrn = current_sf().wave_pattern;
    pat = current_pf(pttrn, pttrn_frame);

    if ((pat->wave_vi & 0x0F) == 2) {
        NR32_REG = 0x20; // max volume
        NR30_REG = 0x0;  // off
        NR30_REG = 0x80; // on
        NR31_REG = 0xF0; // sound length
    } else {
        NR30_REG = 0x0; // off
    }

    if (pat->wave_note != 0xFF) {
        NR34_REG = tl | note2int_hi(pat->wave_note); // msb
        NR33_REG = note2int_lo(pat->wave_note);
    }
#endif

#ifdef NOISE
    pttrn = current_sf().noise_pattern;
    pat = current_pf(pttrn, pttrn_frame);
    // NR41 sound length
    if((pat->noise_vi & 0x0F) != 0x0F){
        NR44_REG = 0x80;
    }
    switch (pat->noise_vi & 0x0F) {
    case 0x03: // hihat
        // Env. Start: 10
        // Env. Down/Up: 0
        // Nev. Length: 2
        // Sound Size: 23
        // start | down/up | length
        NR42_REG = (pat->noise_vi & 0xF0) | 0x00 | 2;
        NR41_REG = 23;
        NR43_REG = 0x10 | 0x04 | 0x03;
        break;
    case 0x04: // bass
        NR42_REG = (pat->noise_vi & 0xF0) | 0x00 | 3;
        NR41_REG = 28;
        NR43_REG = 0x60 | 0x04 | 0x03;
        break;
    case 0x05: // snare
        NR42_REG = (pat->noise_vi & 0xF0) | 0x00 | 5;
        NR41_REG = 30;
        NR43_REG = 0x20 | 0x04 | 0x03;
        break;
    }
#endif

    music_counter++;
    music_counter %= (current_song->pattern_size * current_song->song_size);
}

UINT8 tick_music() {
    tick_counter = (tick_counter + 1) % current_song->speed_divider;
    if (tick_counter == 0) {
        subtick_music();
        return 1;
    }
    return 0;
}