#include "P_Graphics_Main.h"

int i, bg0_main = 344-192;

u8 emptyTile[64] = {
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0
};

u8 warningTile[64] = {
		254,254,254,255,255,254,254,254,
		254,254,254,255,255,254,254,254,
		254,254,254,255,255,254,254,254,
		254,254,254,255,255,254,254,254,
		254,254,254,255,255,254,254,254,
		254,254,254,254,254,254,254,254,
		254,254,254,255,255,254,254,254,
		254,254,254,255,255,254,254,254,
};
u8 redTile[64] = {
		254,254,254,254,254,254,254,254,
		254,254,254,254,254,254,254,254,
		254,254,254,254,254,254,254,254,
		254,254,254,254,254,254,254,254,
		254,254,254,254,254,254,254,254,
		254,254,254,254,254,254,254,254,
		254,254,254,254,254,254,254,254,
		254,254,254,254,254,254,254,254,
};


void P_Graphics_Main(){
	VRAM_A_CR = VRAM_ENABLE|VRAM_A_MAIN_BG;
}


void P_Graphics_Main_config_BG0(){
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE ;
	BGCTRL[2] =  BG_32x64 | BG_COLOR_256 | BG_MAP_BASE(8) | BG_TILE_BASE(2);

	// Transfer of the image and the palette to the engine
	swiCopy(roadTiles,BG_TILE_RAM(2), roadTilesLen/2);
	swiCopy(roadPal,BG_PALETTE, roadPalLen/2);

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[i*32], &BG_MAP_RAM(8)[i*32],64);
	}

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[(i+32)*32], &BG_MAP_RAM(9)[i*32],64);
	}

}

void P_Graphics_Main_config_BG2(){
	BGCTRL[0] =  BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(0);
	// Transfer of the image and the palette to the engine
	swiCopy(emptyTile,&BG_TILE_RAM(0)[0], 64);
	swiCopy(warningTile,&BG_TILE_RAM(0)[32], 64);
	swiCopy(redTile,&BG_TILE_RAM(0)[64], 64);
	BG_PALETTE[255] = ARGB16(1,25,25,25);
	BG_PALETTE[254] = ARGB16(1,31,0,0);

	for (i = 0; i<32*32; i++){
		BG_MAP_RAM(1)[i] = 0;
	}

}

void P_Graphics_Main_scrolling_BG0(int speed){
	REG_BG2VOFS = bg0_main;
	bg0_main=(bg0_main- speed)%512;
}

void P_Graphics_Main_config_Start(){
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG1_ACTIVE;
	BGCTRL[1] =  BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(17) | BG_TILE_BASE(4);

	// Transfer of the image and the palette to the engine
	swiCopy(startscreenmainMap,BG_MAP_RAM(17), startscreenmainMapLen/2);
	swiCopy(startscreenmainPal,BG_PALETTE, startscreenmainPalLen/2);
	swiCopy(startscreenmainTiles, BG_TILE_RAM(4), startscreenmainTilesLen/2);
}




