
#ifndef SOUND_H
#define SOUND_H

#define note_c (0x00)
#define note_cis (0x01)
#define note_des (0x01)
#define note_d (0x02)
#define note_dis (0x03)
#define note_es (0x03)
#define note_e (0x04)
#define note_f (0x05)
#define note_fis (0x06)
#define note_ges (0x06)
#define note_g (0x07)
#define note_gis (0x08)
#define note_as (0x08)
#define note_a (0x09)
#define note_ais (0x0A)
#define note_b (0x0A)
#define note_h (0x0B)

#define note2int_hi(x) ((notes[x] >> 8) & 0xFF)
#define note2int_lo(x) (notes[x] & 0xFF)

// octave < 7 && n <= note_h
#define note(octave,n) (octave*12 + (n))

#endif
