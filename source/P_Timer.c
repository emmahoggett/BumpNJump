/*
 * P_Timer.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Timer.h"

int i, j, timer_ticks0, timer_ticks1, timer_ticks2;

void timer0_IRQ(){
	/*
	 * The warning tile blinks for 1[s] with the Timer0. After 1 [s], the timer is enabled,
	 * the counter timer_ticks0 is initialized to zero, and the warning tile is hiden.
	 */
	if (timer_ticks0%2)EraseWarning(); // Remove the warning sign
	else DisplayWarning(); // Display the warning sign
	timer_ticks0++;
	if (timer_ticks0>=10){
		/* Blinking warning sign last 1[s]
		 * The warning sign is already removed */
		irqDisable(IRQ_TIMER0);
		timer_ticks0 = 0;
	}


}
void timer1_IRQ(){
	/*
	 * The car jump for 1[s] with the Timer1. After 1 [s], the timer is enabled,
	 * the counter timer_ticks1 is initialized to zero, and the jump sprite is hiden.
	 */
	DisplayJump(Get_Car_Pos());
	timer_ticks1++;
	if (timer_ticks1>=10){
		/* Jump animation last 1[s]
		 * Remove the jump animation */
		EraseJump(Get_Car_Pos());
		timer_ticks1 = 0;
		irqDisable(IRQ_TIMER1);
	}
}
void timer2_IRQ(){
	/*
	 * The car blinks for 1[s] with the Timer2. After 1 [s], the timer is enabled,
	 * and the counter timer_ticks2 is initialized to zero.
	 */
	if (timer_ticks2%2)P_Graphics_setCarRed(Get_Car_Pos(), false); // Show the red car
	else P_Graphics_setCarRed(Get_Car_Pos(), true); // Hide the red car
	timer_ticks2++;
	if (timer_ticks2>=10){
		irqDisable(IRQ_TIMER2);
		timer_ticks2 = 0;
	}
}

void P_Timer_Init(){
	// Setting the interrupt for the warning sign
	timer_ticks0 = 0;
	TIMER_CR(0) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER_DATA(0) = TIMER_FREQ_1024(10); // Every 100 ms
	irqSet(IRQ_TIMER0, &timer0_IRQ);

	// Setting the interrupt for the jump animation
	timer_ticks1 = 0;
	TIMER_CR(1) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER_DATA(1) = TIMER_FREQ_1024(10);  // Every 100 ms
	irqSet(IRQ_TIMER1, &timer1_IRQ);

	// Setting the interrupt for the car when it is touched by enemies
	timer_ticks2 = 0;
	TIMER_CR(2) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER_DATA(2) = TIMER_FREQ_1024(10);  // Every 100 ms
	irqSet(IRQ_TIMER2, &timer2_IRQ);

}


void DisplayWarning(){
	j= 0;
	// Copy the map and the corresponding palette
	for (i = 0; i <2; i++){
		BG_MAP_RAM(9)[(i+21)*32 + 16] = warningMap[j] | TILE_PALETTE(10);
		j++;
		BG_MAP_RAM(9)[(i+21)*32 + 17] = warningMap[j] | TILE_PALETTE(10);
		j++;
	}
}
void EraseWarning(){
	// Fill with the transparent tile
	for (i = 0; i <2; i++){
		BG_MAP_RAM(9)[(i+21)*32 + 16] = 0;
		BG_MAP_RAM(9)[(i+21)*32 + 17] = 0;
	}
}

void DisplayJump(int x){
	P_Graphics_setCarRed(x, true);  // Hide the sprites of the red car
	P_Graphics_setCarJump(x, false); // Show the sprites of the jump
}


void EraseJump(int x){
	P_Graphics_setCarRed(x, false); // Show the sprites of the red car
	P_Graphics_setCarJump(x, true); // Hide the sprites of the jump
}

int Get_TimerTicks1(){return timer_ticks1;}
int Get_TimerTicks2(){return timer_ticks2;}


