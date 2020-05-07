#include "music.h"
#include "sound.c"
//#include "music/the_journey_begins.c"

// see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
// see https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware

// enable/disable channels
#define NOISE

UINT8 music_counter;
UINT8 tick_counter;
UINT8 sound_counter;

Song *current_song;
Song *current_sound;

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

void play_sound(Song *song){
    current_sound = song;
    sound_counter = song->pattern_size;// * song->song_size;
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
#define current_pf(pttrn, pttrn_frame) (current_song->pattern + ((pttrn) * current_song->pattern_size) + (pttrn_frame))

// no instrument
const Instrument instnoment = {0x00, 0x00, 0x00, 0x00};

inline void subtick_music(){
    UINT8 *current_sf = &((current_song->arrangement[music_counter / current_song->pattern_size]).noise_pattern);
    UINT8 pttrn_frame = music_counter % current_song->pattern_size;
    const Pattern_frame *pat;
    const Instrument *instr;
    const Instrument *instruments = current_song->instruments;
    __REG base = (&NR10_REG)+10;//(__REG)0xFF10;

#ifdef NOISE
    pat = current_pf(*current_sf, pttrn_frame);
    if((pat->note & 0x0F) != 0x0F){
        instr = &(instruments[pat->note & 0x0F]);
        NR44_REG = 0x80;
        NR41_REG = instr->NR1;
        NR43_REG = instr->other;
        NR42_REG = (pat->note & 0xF0) | instr->NR2;
    }
#endif
    --current_sf;


    // loop first three channels (reverse)
    for(UINT8 i = 0; i < 3; ++i){
        pat = current_pf(*current_sf, pttrn_frame);
        instr = &(instruments[pat->vi & 0x0F]);
        if((pat->vi & 0x0F) != 0x0F){
            *(base) = instr->other;
            *(base+2) = instr->NR2 | (pat->vi & 0xF0);
            *(base+1) = instr->NR1;
        }else
            instr = &instnoment;

        if (pat->note != 0xFF) {
            *(base+4) = instr->NR4 | note2int_hi(pat->note); // msb
            *(base+3) = note2int_lo(pat->note);
        }
        --current_sf;
        base-=5;
    }
    UINT8 tmp = current_song->pattern_size * current_song->song_size;
    if(++music_counter >= tmp)
        music_counter = 0;
    if(sound_counter != 0)
        --sound_counter;
}

UINT8 tick_music() {
    if(++tick_counter >= current_song->speed_divider){
        tick_counter = 0;
    }
    if(tick_counter != 0){
        return 0;
    }
    subtick_music();
    return 1;
}