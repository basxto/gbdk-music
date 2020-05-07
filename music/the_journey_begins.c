#include "../sound.h"
#include "../music.h"

// Remix of The Journey Begins
// https://opengameart.org/content/the-journey-begins
// by Igor Gundarev released under cc0

const Pattern_frame the_journey_begins_pattern[][8] = {
    //  |-------PULSE-1-------|
    //  |------NOTE-----| |VI-|
    {
        {0x30 | note_f  , 0x60},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0x30 | note_gis, 0x60},
        {0xFF           , 0x6F}
    },
    {
        {0x30 | note_cis, 0x60},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F}
    },
    {
        {0x30 | note_dis, 0x60},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0xFF           , 0x6F},
        {0x30 | note_cis, 0x60},
        {0xFF           , 0x6F}
    },
    {
        {0x30 | note_c  , 0x60},
        {0xFF           , 0x6F},
        {0xFF           , 0x00},
        {0xFF           , 0x00},
        {0xFF           , 0x00},
        {0x30 | note_fis, 0x60},
        {0x30 | note_ais, 0x60},
        {0x30 | note_gis, 0x80}
    },
    //  |-------PULSE-2-------|
    {
        {0x10 | note_cis, 0x80},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F}
    },
    {
        {0x10 | note_gis, 0x80},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F}
    },
    {
        {0x10 | note_ais, 0x80},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F},
        {0xFF           , 0x8F}
    },
    //  |------- WAVE---------|
    {
        {0x20 | note_cis, 0xF3},
        {0xFF           , 0xFF},
        {0x20 | note_gis, 0xF3},
        {0xFF           , 0xFF},
        {0x30 | note_cis, 0xF3},
        {0xFF           , 0xFF},
        {0x20 | note_gis, 0xF3},
        {0xFF           , 0xFF}
    },
    {
        {0x10 | note_gis, 0xF3},
        {0x00           , 0xFF},
        {0x20 | note_dis, 0xF3},
        {0x00           , 0xFF},
        {0x20 | note_gis, 0xF3},
        {0xFF           , 0xFF},
        {0x20 | note_dis, 0xF3},
        {0xFF           , 0xFF}
    },
    {
        {0x10 | note_ais, 0xF3},
        {0x00           , 0xFF},
        {0x20 | note_gis, 0xF3},
        {0x00           , 0xFF},
        {0x30 | note_cis, 0xF3},
        {0xFF           , 0xFF},
        {0x20 | note_gis, 0xF3},
        {0xFF           , 0xFF}
    },
    //  |-------NOISE---------|
    {
        {0x86           , 0x00},
        {0xFF           , 0x00},
        {0xFF           , 0x00},
        {0xA4           , 0x00},
        {0x86           , 0x00},
        {0xFF           , 0x00},
        {0x86           , 0x00},
        {0xA4           , 0x00}
    },
};

const Song_frame the_journey_begins_arrangement[] = {
//   P1  P2  W   N
    { 0,  4,  7, 10},
    { 1,  4,  7, 10},
    { 2,  5,  8, 10},
    { 3,  5,  8, 10},
    { 0,  6,  7, 10},
    { 1,  6,  7, 10},
    { 2,  6,  9, 10},
    { 3,  6,  9, 10}
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

Song the_journey_begins={8,8,5,
    the_journey_begins_pattern[0],
    the_journey_begins_arrangement,
    the_journey_begins_instruments
};