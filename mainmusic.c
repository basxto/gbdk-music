// original gameboy
#include <gb/gb.h>

#include "music.h"
#include "music/the_journey_begins.c"

#include "pix/win_gbc_data.c"
#include "pix/win_gbc_pal.c"
#include "pix/win_gbc_inv_data.c"

#define WIN_START 0
#define WIN_INV_START 96

typedef struct {
    const char name[21];
    const Song *song;
} Track;

Track tracks[] = {{"The Journey Begins ", &the_journey_begins}};

const char note2string[][3] = {"C ", "C#", "D ", "D#", "E ", "E#", "F ",
                               "F#", "G ", "G#", "A ", "A#", "H "};
const char hex2char[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

UINT16 counter;
UINT16 counter_max;

#define buffer_length (21)
// be cautious with this!
UINT8 buffer[buffer_length];

void write_bkg_line(UINT8 x, UINT8 y, UINT8 length, char *str, UINT8 inv) {
    UINT8 i;
	UINT8 start = WIN_START;
	if(inv != 0)
		start = WIN_INV_START;
    if (length == 0)
        return;
    for (i = 0; i != length; i++) {
        buffer[i] = start + ' ';
        // strings end with a nullbyte
        if (str[i] == '\0') {
            break;
        }
        if (str[i] > 0x60 && str[i] < 0x7B)
            // we don't have lower case in our font
            // shift to upper case
            buffer[i] = start + (str[i] - 0x20);
        else
            buffer[i] = start + (str[i]);
    }
    for (; i != buffer_length; i++) {
        buffer[i] = start + ' ';
    }
    set_bkg_tiles(x, y, length, 1, buffer);
}

// access arrays via pointer
#define get_sf(current_song, music_counter) (current_song->arrangement[(music_counter) / current_song->pattern_size])
#define get_pf(current_song, pttrn, pttrn_frame) (current_song->pattern + ((pttrn) * current_song->pattern_size) + (pttrn_frame))

void print_song(const Song *song){
	UINT8 line = 0;
	UINT16 music_counter = 0;
	UINT8 arrangement = 0;
	UINT8 pattern = 0;
	UINT8 pttrn;
	const Pattern_frame *pat;
	for(music_counter = 0; music_counter < (song->song_size * song->pattern_size); ++music_counter){
		// pulse channel
		pttrn = get_sf(song, music_counter).pulse_pattern;
		pat = get_pf(song, pttrn, ((music_counter) % song->pattern_size));
		if(pat->pulse_note == 0xFF){
			buffer[1] = '-';
			buffer[2] = '-';
			buffer[3] = ' ';
		}else{
			buffer[1] = hex2char[pat->pulse_note >> 4];
			buffer[2] = note2string[pat->pulse_note & 0xF][0];
			buffer[3] = note2string[pat->pulse_note & 0xF][1];
		}
		buffer[4] = ' ';
		buffer[5] = hex2char[pat->pulse_vi >> 4];
		if((pat->pulse_vi & 0xF) == 0xF){
			buffer[6] = '-';
		}else{
			buffer[6] = hex2char[pat->pulse_vi & 0xF];
		}
		buffer[7] = ' ';
		buffer[8] = '\\';
		buffer[9] = ' ';

		// wave channel
		pttrn = get_sf(song, music_counter).wave_pattern;
		pat = get_pf(song, pttrn, ((music_counter) % song->pattern_size));
		if(pat->wave_note == 0xFF){
			buffer[10] = '-';
			buffer[11] = '-';
			buffer[12] = ' ';
		}else{
			buffer[10] = hex2char[pat->wave_note >> 4];
			buffer[11] = note2string[pat->wave_note & 0xF][0];
			buffer[12] = note2string[pat->wave_note & 0xF][1];
		}
		buffer[13] = ' ';
		buffer[14] = hex2char[pat->wave_vi >> 4];
		if((pat->wave_vi & 0xF) == 0xF){
			buffer[15] = '-';
		}else{
			buffer[15] = hex2char[pat->wave_vi & 0xF];
		}
		buffer[16] = ' ';
		buffer[17] = '\\';
		buffer[18] = ' ';

		// noise channel
		pttrn = get_sf(song, music_counter).noise_pattern;
		pat = get_pf(song, pttrn, ((music_counter) % song->pattern_size));
		buffer[19] = hex2char[pat->noise_vi >> 4];
		if((pat->noise_vi & 0xF) == 0xF){
			buffer[20] = '-';
		}else{
			buffer[20] = hex2char[pat->noise_vi & 0xF];
		}

		write_bkg_line(0,music_counter,20,buffer + 1, music_counter%2);
	}
}

void write_win_line(UINT8 x, UINT8 y, UINT8 length, char *str) {
    UINT8 i;
    if (length == 0)
        return;
    for (i = 0; i != length; i++) {
        buffer[i] = WIN_START + ' ';
        // strings end with a nullbyte
        if (str[i] == '\0') {
            break;
        }
        if (str[i] > 0x60 && str[i] < 0x7B)
            // we don't have lower case in our font
            // shift to upper case
            buffer[i] = WIN_START + (str[i] - 0x20);
        else
            buffer[i] = WIN_START + (str[i]);
    }
    for (; i != buffer_length; i++) {
        buffer[i] = WIN_START + ' ';
    }
    set_win_tiles(x, y, length, 1, buffer);
}

void timer_isr() { 
	if(tick_music() == 1){
		move_bkg(0, counter * 8);
		counter = (counter + 1)%counter_max;
	}
}

void main() {
    init_music(tracks[0].song);
	counter_max = tracks[0].song->song_size * tracks[0].song->pattern_size;

    HIDE_BKG;
    HIDE_WIN;
    DISPLAY_OFF;
    cgb_compatibility();

    BGP_REG = 0xE1; // 11100001
    OBP0_REG = 0xE1;

    // configure interrupt
    TIMA_REG = TMA_REG = 0x1A;
    TAC_REG = 0x4 | 0x0; // 4096 Hz
    // enable timer interrupt
    disable_interrupts();
    add_TIM(timer_isr);
    enable_interrupts();
    set_interrupts(VBL_IFLAG | TIM_IFLAG);

    set_bkg_palette(0, 1, win_gbc_pal[0]);
    set_bkg_data(WIN_START, sizeof(win_gbc_data) / 16, win_gbc_data);
	set_bkg_data(WIN_INV_START, sizeof(win_gbc_inv_data) / 16, win_gbc_inv_data);

	print_song(tracks[0].song);
    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;
    // show two lines
    move_win(7, 16 * 8);
    write_win_line(0, 0, 20, tracks[0].name);
    write_win_line(0, 1, 20, "-No sound selected-");
}