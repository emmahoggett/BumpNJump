/*
 * P_Timer.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Timer.h"

int i, j, timer_ticks0, timer_ticks1;

void timer0_IRQ(){

	swiWaitForVBlank();

	if (timer_ticks0%2)EraseWarning();
	else DisplayWarning();
	timer_ticks0++;
	if (timer_ticks0>=10){
		irqDisable(IRQ_TIMER0);
		timer_ticks0 = 0;
	}


}
void timer1_IRQ(){
	int x_pos = Get_Car_Pos();
	DisplayJump(x_pos);
	timer_ticks1++;
	if (timer_ticks1>=5){
		EraseJump(x_pos);
		irqDisable(IRQ_TIMER1);
		timer_ticks1 = 0;
	}
}


void P_Timer_Init(){
	timer_ticks0 = 0;
	TIMER_CR(0) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER_DATA(0) = TIMER_FREQ_1024(10);
	irqSet(IRQ_TIMER0, &timer0_IRQ);

	timer_ticks1 = 0;
	TIMER_CR(1) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER_DATA(1) = TIMER_FREQ_1024(10);
	irqSet(IRQ_TIMER1, &timer1_IRQ);

}


void DisplayWarning(){
	j= 0;
	for (i = 0; i <2; i++){
		BG_MAP_RAM(9)[(i+21)*32 + 16] = warningMap[j] | TILE_PALETTE(10);
		j++;
		BG_MAP_RAM(9)[(i+21)*32 + 17] = warningMap[j] | TILE_PALETTE(10);
		j++;
	}
}
void EraseWarning(){
	for (i = 0; i <2; i++){
		BG_MAP_RAM(9)[(i+21)*32 + 16] = 0;
		BG_MAP_RAM(9)[(i+21)*32 + 17] = 0;
	}
}

void DisplayJump(int x){
	P_Graphics_setCarRed(x, true);
	P_Graphics_setCarJump(x, false);
}


void EraseJump(int x){
	P_Graphics_setCarRed(x, false);
	P_Graphics_setCarJump(x, true);
}

int Get_TimerTicks1(){return timer_ticks1;}
