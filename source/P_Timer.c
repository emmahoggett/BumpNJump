#include "P_Timer.h"

int i, j, timer_ticks0;

void timer0_IRQ(){

	//It is necessary to wait until the screen is refreshed...
	swiWaitForVBlank();

	if (timer_ticks0%2)BG_PALETTE_SUB[161] ^= 0x0B;
	else BG_PALETTE_SUB[161] = ARGB16(1,20,0,0);
	timer_ticks0++;
	if (timer_ticks0>=20){
		irqDisable(IRQ_TIMER0);
	}


}

void P_Timer_Init(){
	timer_ticks0 = 0;
	TIMER_CR(0) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER_DATA(0) = TIMER_FREQ_1024(100);
	irqSet(IRQ_TIMER0, &timer0_IRQ);
}


void DisplayWarning(){
	j= 0;
	for (i = 0; i <2; i++){
		BG_MAP_RAM(20)[(i+1)*32 + 16] = warningMap[j] | TILE_PALETTE(10);
		j++;
		BG_MAP_RAM(20)[(i+1)*32 + 17] = warningMap[j] | TILE_PALETTE(10);
		j++;
	}
}
