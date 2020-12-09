#include "P_Graphics_Sub.h"


int i,j;
u8 grassTileSub[64] = {
		8,8,8,8,8,8,8,8,
		8,7,7,8,8,8,8,8,
		8,7,7,8,8,8,8,8,
		8,7,7,8,8,8,8,8,
		8,8,8,8,8,8,8,8,
		8,8,8,8,7,7,8,8,
		8,8,8,8,7,7,8,8,
		8,8,8,8,8,8,8,8
};

u8 waterTileSub[64] = {
		9,9,9,9,9,9,9,9,
		10,10,9,9,10,10,9,9,
		9,10,10,9,9,10,10,9,
		10,10,9,9,10,10,9,9,
		9,10,10,9,9,10,10,9,
		10,10,9,9,10,10,9,9,
		9,10,10,9,9,10,10,9,
		9,9,9,9,9,9,9,9
};

void P_Graphics_Sub(){
	VRAM_C_CR = VRAM_ENABLE|VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE;
}

void P_Graphics_Sub_config_BG0(){
	BGCTRL_SUB[0] =  BG_32x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	// Transfer of the image and the palette to the engine
	swiCopy(roadTiles,BG_TILE_RAM_SUB(1), roadTilesLen/2);
	swiCopy(roadPal,BG_PALETTE_SUB, roadPalLen/2);

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[i*32], &BG_MAP_RAM_SUB(0)[i*32],64);
	}

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[(i+32)*32], &BG_MAP_RAM_SUB(1)[i*32],64);
	}


}

void P_Graphics_Sub_config_BG1(){
	BGCTRL_SUB[1] =  BG_32x64 | BG_COLOR_256 | BG_MAP_BASE(29) | BG_TILE_BASE(5);

	swiCopy(grassTileSub,&BG_TILE_RAM_SUB(5)[0], 64);
	swiCopy(waterTileSub,&BG_TILE_RAM_SUB(5)[32], 64);

	BG_PALETTE_SUB [8] = ARGB16(1, 0, 20, 15);
	BG_PALETTE_SUB [7] = ARGB16(1,10, 25, 10);

	BG_PALETTE_SUB [9] = ARGB16(1, 0, 15, 31);
	BG_PALETTE_SUB [10] = ARGB16(1, 0, 25, 25);

	for (i = 0; i < 32; i++){
		for (j = 0; j < 32; j++){
			if (j < 16) BG_MAP_RAM_SUB(29)[i*32 +j] = 0;
			else BG_MAP_RAM_SUB(29)[i*32 +j] = 1;
		}
	}

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
	swiCopy(carredTiles, &gfx[0], carredTilesLen/2);
}


void P_Graphics_setSprites(OamState oam, int sprite, int sprite_x, int sprite_y, int palette){
	oamSet(&oam, 	// oam handler
		sprite,				// Number of sprite
		sprite_x, sprite_y,			// Coordinates
		0,				// Priority
		palette,				// Palette to use
		SpriteSize_16x16,			// Sprite size
		SpriteColorFormat_256Color,	// Color format
		gfx,			// Loaded graphic to display
		-1,				// Affine rotation to use (-1 none)
		false,			// Double size if rotating
		false,			// Hide this sprite
		false, false,	// Horizontal or vertical flip
		false			// Mosaic
		);
	swiWaitForVBlank();
	//Update the sprites
	oamUpdate(&oam);
}
