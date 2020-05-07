
#ifndef MUSIC_H
#define MUSIC_H

#include <gb/gb.h>

// per channel
typedef struct {
    // 0x14 is notes[1][0x04]
    // note_e is 0x04
    // 0x10 & note_e is also possible
    // 0xFF is keep note
    // noise instruments have fixed notes
    const UINT8 note;
    // 0x78 is volume 7 and 7th instrument
    // instrument F is NOP
    // for noise this FX channel (unused)
    const UINT8 vi;
} Pattern_frame;

typedef struct {
    const UINT8 pulse_pattern;
    const UINT8 pulse2_pattern;
    const UINT8 wave_pattern;
    const UINT8 noise_pattern;
} Song_frame;

typedef struct{
    const UINT8 NR2;// volume envelope
    const UINT8 NR1;// duty
    const UINT8 NR4;// trigger and length enable
    // NR0 for pulse1 and wave; NR3 for noise
    const UINT8 other;
} Instrument;

// 5 elements is again not suitable for arrays
// but this is not used often
typedef struct{
    const UINT8 pattern_size;
    const UINT8 song_size;
    const UINT8 speed_divider;
    const Pattern_frame *pattern;
    const Song_frame *arrangement;
    const Instrument *instruments;
} Song;

void blinger(const UINT8 note, const UINT8 wait, const UINT8 note2, const UINT8 wait2, const UINT8 note3);
void plonger(const UINT8 note, const UINT8 duty, const INT8 arp);

void init_music(Song *song);
UINT8 tick_music();

#endif