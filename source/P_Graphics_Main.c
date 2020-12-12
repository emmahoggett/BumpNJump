#include "P_Graphics_Main.h"

int i, bg0_main = 344-192;

void P_Graphics_Main(){
	VRAM_A_CR = VRAM_ENABLE|VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;
}


void P_Graphics_Main_config_BG0(){
	BGCTRL[0] =  BG_32x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	// Transfer of the image and the palette to the engine
	swiCopy(roadTiles,BG_TILE_RAM(1), roadTilesLen/2);
	swiCopy(roadPal,BG_PALETTE, roadPalLen/2);

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[i*32], &BG_MAP_RAM(0)[i*32],64);
	}

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[(i+32)*32], &BG_MAP_RAM(1)[i*32],64);
	}

}

void P_Graphics_Main_scrolling_BG0(int speed){
	if (speed < 0) speed = 0;
	else if(speed > 8) speed = 8;

	REG_BG0VOFS = bg0_main;
	bg0_main-=speed;
}




