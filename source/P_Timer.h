/*
 * P_Timer.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */


#include <nds.h>
#include "P_Map16x16.h"
#include "P_GamePlay.h"


void P_Timer_Init();

void DisplayWarning();
void EraseWarning();

void DisplayJump(int x);
void EraseJump(int x);

int Get_TimerTicks1();
