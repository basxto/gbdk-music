// original gameboy
#include <gb/gb.h>

#include "music.h"
#include "music/the_journey_begins.c"

void timer_isr(){
	tick_music();
}

void main() {
	init_music(&the_journey_begins);
	// configure interrupt
	TIMA_REG = TMA_REG = 0x1A;
	TAC_REG = 0x4 | 0x0;//4096 Hz
	// enable timer interrupt
	disable_interrupts();
	add_TIM(timer_isr);
	enable_interrupts();
	set_interrupts(TIM_IFLAG);
}
