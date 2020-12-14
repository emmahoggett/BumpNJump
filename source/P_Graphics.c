#include "P_Graphics.h"


void P_Graphics_setup_main(){
	VRAM_A_CR = VRAM_ENABLE|VRAM_A_MAIN_BG;

	REG_DISPCNT = MODE_0_2D | DISPLAY_BG2_ACTIVE| DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE;

	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG2_ACTIVE;
	VRAM_C_CR = VRAM_ENABLE|VRAM_C_SUB_BG;

	//Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;
}


