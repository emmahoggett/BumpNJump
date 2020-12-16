#include "P_Graphics.h"


void P_Graphics_setup_main(){
	VRAM_A_CR = VRAM_ENABLE|VRAM_A_MAIN_BG;
	VRAM_E_CR = VRAM_ENABLE|POWER_LCD;

	dmaCopy(startscreenmainPal,VRAM_E,startscreenmainPalLen);
	VRAM_E_CR = VRAM_ENABLE|VRAM_E_BG_EXT_PALETTE;

	REG_DISPCNT = MODE_0_2D | DISPLAY_BG1_ACTIVE | DISPLAY_BG_EXT_PALETTE;

	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG2_ACTIVE;
	VRAM_C_CR = VRAM_ENABLE|VRAM_C_SUB_BG;

	//Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;
	//Initialize sprite manager and the engine
	oamInit(&oamSub, SpriteMapping_1D_32, false);


}


