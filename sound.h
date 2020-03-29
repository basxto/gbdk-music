
#ifndef SOUND_H
#define SOUND_H

#define note_c 0x00
#define note_cis 0x01
#define note_des 0x01
#define note_d 0x02
#define note_dis 0x03
#define note_es 0x03
#define note_e 0x04
#define note_f 0x05
#define note_fis 0x06
#define note_ges 0x06
#define note_g 0x07
#define note_gis 0x08
#define note_as 0x08
#define note_a 0x09
#define note_ais 0x0A
#define note_b 0x0A
#define note_h 0x0B

// 0x10 & note_b to notes[1][note_b]
#define note2int(x) (notes[((x) >> 4) & 0x0F][(x)&0x0F])

#define note2int_hi(x) (((notes[((x) >> 4) & 0x0F][(x)&0x0F] >> 8) & 0x00FF))
#define note2int_lo(x) ((notes[((x) >> 4) & 0x0F][(x)&0x0F] & 0x00FF))

#endif
