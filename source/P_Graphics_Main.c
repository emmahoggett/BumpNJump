#include "P_Graphics_Main.h"

int i,j;
u8 grassTile[64] = {
		8,8,8,8,8,8,8,8,
		8,7,7,8,8,8,8,8,
		8,7,7,8,8,8,8,8,
		8,7,7,8,8,8,8,8,
		8,8,8,8,8,8,8,8,
		8,8,8,8,7,7,8,8,
		8,8,8,8,7,7,8,8,
		8,8,8,8,8,8,8,8
};

u8 waterTile[64] = {
		9,9,9,9,9,9,9,9,
		10,10,9,9,10,10,9,9,
		9,10,10,9,9,10,10,9,
		10,10,9,9,10,10,9,9,
		9,10,10,9,9,10,10,9,
		10,10,9,9,10,10,9,9,
		9,10,10,9,9,10,10,9,
		9,9,9,9,9,9,9,9
};


void P_Graphics_Main(){
	VRAM_A_CR = VRAM_ENABLE|VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE;
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


void P_Graphics_Main_config_BG1(){
	BGCTRL[1] =  BG_32x64 | BG_COLOR_256 | BG_MAP_BASE(28) | BG_TILE_BASE(4);

	swiCopy(grassTile,&BG_TILE_RAM(4)[0], 64);
	swiCopy(waterTile,&BG_TILE_RAM(4)[32], 64);

	BG_PALETTE [8] = ARGB16(1, 0, 20, 15);
	BG_PALETTE [7] = ARGB16(1,10, 25, 10);

	BG_PALETTE [9] = ARGB16(1, 0, 15, 31);
	BG_PALETTE [10] = ARGB16(1, 0, 25, 25);

	for (i = 0; i < 32; i++){
		for (j = 0; j < 32; j++){
			if (j < 16) BG_MAP_RAM(28)[i*32 +j] = 0;
			else BG_MAP_RAM(28)[i*32 +j] = 1;
		}
	}

}


