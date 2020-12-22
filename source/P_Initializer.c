/*
 * P_Initializer.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Initializer.h"



void P_InitNDS(){

	//Initialize the main, sub and sprite engines
	P_Graphics_setup_main();

	//Initialize the backgrounds
	P_Map16x16_Init();

	// Initialize the timer for the warning and jump animation
	P_Timer_Init();

	// Initialize the audio and play the music in repeat
	Audio_Init();
	Audio_PlayMusic();
}
