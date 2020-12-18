/*
 * P_Initializer.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Initializer.h"



void P_InitNDS(){

	P_Graphics_setup_main();
	P_Map16x16_Init();
	P_Timer_Init();
	Audio_Init();
	Audio_PlayMusic();

}
