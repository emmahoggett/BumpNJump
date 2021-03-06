/*
 * P_Graphics.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Graphics.h"


void P_Graphics_setup_main(){
	//Enable RAM memory bank A for the main engine.
	VRAM_A_CR = VRAM_ENABLE|VRAM_A_MAIN_BG;

	//Configure the main engine in mode 0 (2D) and activate Backgrounds 2 and 1.
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE;

	//Enable RAM memory bank C for the main engine.
	VRAM_C_CR = VRAM_ENABLE|VRAM_C_SUB_BG;

	//Configure the sub engine in mode 0 (2D) and activate Backgrounds 2.
	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG2_ACTIVE;

	//Set up memory bank to work in sprite mode for the main and sub engine
	//(offset since we are using VRAM A for backgrounds).
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;
	VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;

	//Initialize sprite manager and the engine for the main and sub engines.
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);


}

