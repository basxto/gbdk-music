#include "../sound.h"
#include "../music.h"

// Remix of The Journey Begins
// https://opengameart.org/content/the-journey-begins
// by Igor Gundarev released under cc0

const Pattern_frame the_journey_begins_pattern[][8] = {

    //  |-------PULSE-2-------|
    //  |------NOTE-----| |VI-|
    {
        {note(1,note_cis), 0x80},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F}
    },
    {
        {note(1,note_gis), 0x80},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F}
    },
    {
        {note(1,note_ais), 0x80},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F},
        {0xFF            , 0x8F}
    },
    //  |------- WAVE---------|
    {
        {note(2,note_cis), wF|0x3},
        {0xFF            , wF|0xF},
        {note(2,note_gis), wF|0x3},
        {0xFF            , wF|0xF},
        {note(3,note_cis), wF|0x3},
        {0xFF            , wF|0xF},
        {note(2,note_gis), wF|0x3},
        {0xFF            , wF|0xF}
    },
    {
        {note(1,note_gis), wF|0x3},
        {0x00           , wF|0xF},
        {note(2,note_dis), wF|0x3},
        {0x00           , wF|0xF},
        {note(2,note_gis), wF|0x3},
        {0xFF            , wF|0xF},
        {note(2,note_dis), wF|0x3},
        {0xFF            , wF|0xF}
    },
    {
        {note(1,note_ais), wF|0x3},
        {0x00           , wF|0xF},
        {note(2,note_gis), wF|0x3},
        {0x00           , wF|0xF},
        {note(3,note_cis), wF|0x3},
        {0xFF            , wF|0xF},
        {note(2,note_gis), wF|0x3},
        {0xFF            , wF|0xF}
    },
    //  |-------NOISE---------|
    {
        {0xFF            ,0x86},
        {0xFF            ,0xFF},
        {0xFF            ,0xFF},
        {0xFF            ,0xA4},
        {0xFF            ,0x86},
        {0xFF            ,0xFF},
        {0xFF            ,0x86},
        {0xFF            ,0xA4}
    },
    //  |-------PULSE-1-------|
    {
        {note(2,note_f)  , 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {note(2,note_gis), 0x60},
        {0xFF            , 0x6F}
    },
    {
        {note(3,note_cis), 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F}
    },
    {
        {note(3,note_dis), 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {note(3,note_cis), 0x60},
        {0xFF            , 0x6F}
    },
    {
        {note(3,note_c)  , 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {note(2,note_fis), 0x60},
        {note(2,note_ais), 0x60},
        {note(3,note_gis), 0x80}
    },
    {
        {note(3,note_f)  , 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00}
    },
    {
        {note(3,note_f)  , 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {note(3,note_cis), 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F}
    },
    {
        {note(2,note_ais), 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {note(2,note_gis), 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F}
    },
    {
        {note(3,note_cis), 0x60},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x6F},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00}
    },
    {
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00}
    },
    {
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {note(2,note_cis), 0x60},
        {0xFF            , 0x6F},
        {note(2,note_ais), 0x60},
        {0xFF            , 0x6F},
        {note(2,note_gis), 0x60},
        {0xFF            , 0x6F}
    },
    {
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {0xFF            , 0x00},
        {note(2,note_cis), 0x60},
        {note(2,note_ais), 0x60},
        {note(2,note_gis), 0x60}
    }
};

const Song_frame the_journey_begins_arrangement[] = {
//   P1  P2  W   N
    { 7,  0,  3,  6},
    { 8,  0,  3,  6},
    { 9,  1,  4,  6},
    {10,  1,  4,  6},
    { 7,  2,  3,  6},
    { 8,  2,  3,  6},
    {15,  2,  5,  6},
    {17,  2,  5,  6},
    { 7,  0,  3,  6},
    { 8,  0,  3,  6},
    { 9,  1,  4,  6},
    {11,  1,  4,  6},
    {12,  2,  3,  6},
    {13,  2,  3,  6},
    {14,  2,  5,  6},
    {15,  2,  5,  6},
    {15,  0,  3,  6},
    {15,  0,  3,  6},
    {15,  1,  4,  6},
    {15,  1,  4,  6},
    {15,  2,  3,  6},
    {15,  2,  3,  6},
    {15,  2,  5,  6},
    {16,  2,  5,  6}
};

const Instrument the_journey_begins_instruments[] = {
    //NR2     NR1   NR4   NR0/NR3
    // pulse
    {0x00   , 0x90, 0x80, 0x00},
    {0x02   , 0x50, 0xC0, 0x00},
    {0x07   , 0x90, 0xC0, 0x00},
    // wave
    {0x00   , 0xF0, 0xC0, 0x80},
    // noise
    {0x00 |2,   23, 0xC0, 0x10 | 0x04 | 0x03},
    {0x00 |3,   28, 0xC0, 0x60 | 0x04 | 0x03},
    {0x00 |5,   30, 0xC0, 0x20 | 0x04 | 0x03}
};

const Song the_journey_begins={
    (sizeof(the_journey_begins_pattern[0])/sizeof(Pattern_frame)),
    (sizeof(the_journey_begins_arrangement)/sizeof(Song_frame)),
    40,
    &(the_journey_begins_pattern[0][0]),
    &(the_journey_begins_arrangement[0]),
    &(the_journey_begins_instruments[0])
};