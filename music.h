
#ifndef MUSIC_H
#define MUSIC_H

#include <gb/gb.h>

// has 5 elements, but 2^n might be better
// +3 = 8 ... 2bytes for channel 1 and maybe effect channel
typedef struct {
    // 0x14 is notes[1][0x04]
    // note_e is 0x04
    // 0x10 & note_e is also possible
    // 0xFF is keep note
    const UINT8 pulse_note;
    // 0x78 is volume 7 and 7th instrument
    // instrument F is NOP
    const UINT8 pulse_vi;
    const UINT8 pulse2_note;
    const UINT8 pulse2_vi;
    const UINT8 wave_note;
    const UINT8 wave_vi;
    // noise instruments have fixed notes
    const UINT8 noise_vi;
    // unused so far
    const UINT8 fx;
} Pattern_frame;

// 3 patterns, 4 would be better (+other pulse)
// or + effects and pulse patterns always go together
typedef struct {
    const UINT8 pulse_pattern;
    const UINT8 pulse2_pattern;
    const UINT8 wave_pattern;
    const UINT8 noise_pattern;
} Song_frame;

// 5 elements is again not suitable for arrays
typedef struct{
    const UINT8 pattern_size;
    const UINT8 song_size;
    const UINT8 speed_divider;
    const Pattern_frame *pattern;
    const Song_frame *arrangement;
} Song;

void blinger(const UINT8 note, const UINT8 wait, const UINT8 note2, const UINT8 wait2, const UINT8 note3);
void plonger(const UINT8 note, const UINT8 duty, const INT8 arp);

void init_music(Song *song);
UINT8 tick_music();

#endif