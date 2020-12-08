#include "P_Graphics_Sub.h"


void P_Graphics_Sub(){
	VRAM_C_CR = VRAM_ENABLE|VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE;
}

void P_Graphics_Sub_config_BG0(){
	BGCTRL_SUB[0] =  BG_32x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	// Transfer of the image and the palette to the engine
	swiCopy(roadTiles,BG_TILE_RAM_SUB(1), roadTilesLen/2);
	swiCopy(roadPal,BG_PALETTE_SUB, roadPalLen/2);
	int i;
	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[i*32], &BG_MAP_RAM_SUB(0)[i*32],64);
	}

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[(i+32)*32], &BG_MAP_RAM_SUB(1)[i*32],64);
	}

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[(i+64)*32], &BG_MAP_RAM_SUB(2)[i*32],64);
	}

}

void P_Graphics_Sub_config_BG2(){

}

void P_Graphics_configureSprites(){
//Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;

	//Initialize sprite manager and the engine
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	//Allocate space for the graphic to show in the sprite
	gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);

	//Copy data for the graphic (palette and bitmap)
	swiCopy(carredPal, SPRITE_PALETTE_SUB, carredPalLen/2);
	swiCopy(carredTiles, gfx, carredTilesLen/2);
}
