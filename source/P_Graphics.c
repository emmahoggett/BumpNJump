#include "P_Graphics.h"


u8 roadTile[64] = {
	8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8
}; // emplacement 8 de la palette = gris - route

u8 centerLineTile[64] = {
		8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,
		8,8,7,7,7,7,8,8,
		8,8,7,7,7,7,8,8,
		8,8,7,7,7,7,8,8,
		8,8,7,7,7,7,8,8,
		8,8,7,7,7,7,8,8
}; // emplacement 7 de la palette = blanc - emplacement 0 de la palette = transparent - séparation route

u8 backgroundTile[64] = {
		0,0,5,5,5,5,5,5,
		0,0,5,5,5,5,5,5,
		5,5,0,0,5,5,5,5,
		5,5,0,0,5,5,5,5,
		5,5,5,5,5,5,5,5,
		5,5,5,5,5,5,0,0,
		5,5,5,5,5,5,0,0,
		5,5,5,5,5,5,5,5
}; //emplacement 5 de la palette = bleu - background

u8 roadBoarderTile [64] = {
		0,0,0,0,0,0,0,0,
		0,7,7,7,7,7,7,0,
		0,7,7,7,7,7,7,0,
		0,7,7,7,7,7,7,0,
		0,7,7,7,7,7,7,0,
		0,7,7,7,7,7,7,0,
		0,7,7,7,7,7,7,0,
		0,7,7,7,7,7,7,0
};


void P_Graphics_Main(){
	VRAM_A_CR = VRAM_ENABLE|VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;
}

void P_Graphics_Main_config_BG0(){
	BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	swiCopy (roadTile, &BG_TILE_RAM(1)[0], 64);
	swiCopy (centerLineTile, &BG_TILE_RAM(1)[32], 64);

	BG_PALETTE[8] = ARGB16(1,7,7,7);
	BG_PALETTE[7] = ARGB16(1,31,31,31);

	int x, y;
	for (x = 0; x < 32; x++){
		for (y = 0; y <32 ;y ++){
			BG_MAP_RAM(0)[y*32 + x] = 0;
		}
	}

	for (y = 0; y < 32; y+=2){
		BG_MAP_RAM(0)[y*32 + 15] = 1;
		BG_MAP_RAM(0)[(y +1)*32 + 15] = 1 | (1<<11);
	}
}
