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
        NR21_REG = 0x90;
        NR22_REG = 0x00 | (pat->pulse_vi & 0xF0); // continuous tone
        tl = 0x80; // don't disable after time
        break;
    case 7:
        NR21_REG = 0x50;                          // 50% duty
        NR22_REG = 0x02 | (pat->pulse_vi & 0xF0); // volume envelope
        break;
    case 6:
        NR21_REG = 0x90;                          // 75% duty
        NR22_REG = 0x07 | (pat->pulse_vi & 0xF0); // volume envelope
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
        NR30_REG = 0x0;  // off
        NR30_REG = 0x80; // on
        NR32_REG = 0x20; // max volume
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
    NR44_REG = 0x80;
    NR42_REG = 0x07 | (pat->noise_vi & 0xF0);
    switch (pat->noise_vi & 0x0F) {
    case 0x03: // hihat
        // Env. Start: 10
        // Env. Down/Up: 0
        // Nev. Length: 2
        // Sound Size: 23
        NR41_REG = 23;
        // start | down/up | length
        NR42_REG = 0xA0 | 0x00 | 2;
        NR43_REG = 0x10 | 0x04 | 0x03;
        break;
    case 0x04: // bass
        NR41_REG = 28;
        NR42_REG = 0xF0 | 0x00 | 3;
        NR43_REG = 0x60 | 0x04 | 0x03;
        break;
    case 0x05: // snare
        NR41_REG = 30;
        NR42_REG = 0x80 | 0x00 | 5;
        NR43_REG = 0x20 | 0x04 | 0x03;
        break;
    }
#endif

    music_counter++;
    music_counter %= (current_song->pattern_size * current_song->song_size);
}

void tick_music() {
    tick_counter = (tick_counter + 1) % current_song->speed_divider;
    if (tick_counter == 0) {
        subtick_music();
    }
}