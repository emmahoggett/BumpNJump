/*
 * P_Map16x16.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Map16x16.h"

int i, bg3_main = 1,bg2_sub = 193;

void P_Map16x16_configureBG0(){
	//Initialize Background
	BGCTRL[0] =  BG_32x32 | BG_COLOR_16 | BG_MAP_BASE(9) | BG_TILE_BASE(2);

	// Transfer of the image and the palette to the engine
	dmaCopy(warningTiles,(u8*)BG_TILE_RAM(2),warningTilesLen);
	dmaCopy(warningPal,&BG_PALETTE[160],warningPalLen);
	int i = 32*32;
	while(i--)
		BG_MAP_RAM(9)[i] = 0;

}

void P_Map16x16_configureBG3(){
	//Initialize Background
	BGCTRL[3] =  BG_32x64 | BG_COLOR_16 | BG_MAP_BASE(7) | BG_TILE_BASE(0);

	// Transfer of the image and the palette to the engine
	dmaCopy(roadTiles,BG_TILE_RAM(0), roadTilesLen);
	dmaCopy(roadPal,&BG_PALETTE[0], roadPalLen);

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[i*32], &BG_MAP_RAM(7)[i*32],64);
	}

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[(i+32)*32], &BG_MAP_RAM(8)[i*32],64);
	}
	REG_BG3VOFS = bg3_main;
}

void P_Map16x16_configureBG2(){
	//Initialize Background
	BGCTRL[1] = BG_32x32 | BG_COLOR_16 | BG_MAP_BASE(10) | BG_TILE_BASE(3);

	dmaCopy(numbersTiles,(u8*)BG_TILE_RAM(3),numbersTilesLen);
	dmaCopy(numbersPal,&BG_PALETTE[128],numbersPalLen);
	dmaCopy(numbersPal,&BG_PALETTE[144],numbersPalLen);
	BG_PALETTE[129] = ARGB16(1,31,15,0);
	BG_PALETTE[145] = ARGB16(1,31,31,31);

	int i = 32*32;
	while(i--)
		BG_MAP_RAM(10)[i] = 0;
}


void P_Map16x16_scrolling_BG3(int _speed){
	REG_BG3VOFS = bg3_main;
	bg3_main =( bg3_main - _speed)%512;
	if (bg3_main>=-_speed-1 && bg3_main<=0)irqEnable(IRQ_TIMER0);
}

int scroll_pos(int bg_num){
	if (bg_num ==2)return bg2_sub;
	else return bg3_main;
}

void P_Map16x16_scrolling_Init(){
	bg3_main = 1; bg2_sub = 193;
}

void P_Map16x16_configureStart(){
	//Initialize Background
	BGCTRL[2] = BG_32x32 | BG_COLOR_16 | BG_MAP_BASE(12) | BG_TILE_BASE(4);
	dmaCopy(startscreenmainTiles,BG_TILE_RAM(4),startscreenmainTilesLen);
	dmaCopy(startscreenmainPal,&BG_PALETTE[0xD0],startscreenmainPalLen);
	dmaCopy(startscreenmainMap,BG_MAP_RAM(12),startscreenmainMapLen);

	for (i = 0; i<32*32;i++){
		//Render the number
		BG_MAP_RAM(12)[i] = startscreenmainMap[(i)] | TILE_PALETTE(13);
	}
	displayMaxScore_Start(0);

}

void P_Map16x16_configureBG2_Sub(){
	//Initialize Background
	BGCTRL_SUB[2] =  BG_32x64 | BG_COLOR_16 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	// Transfer of the image and the palette to the engine
	dmaCopy(roadTiles,BG_TILE_RAM_SUB(1), roadTilesLen);
	dmaCopy(roadPal,BG_PALETTE_SUB, roadPalLen);

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[i*32], &BG_MAP_RAM_SUB(0)[i*32],64);
	}

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[(i+32)*32], &BG_MAP_RAM_SUB(1)[i*32],64);
	}

	REG_BG2VOFS_SUB = bg2_sub;
}

void P_Map16x16_scrolling_BG2_Sub(int _speed){
	REG_BG2VOFS_SUB = bg2_sub;
	bg2_sub = bg2_sub- _speed;
}

void P_Map16x16_Init(){
	// Configure the main engine backgrounds
	P_Map16x16_configureBG3();
	P_Map16x16_configureBG2();
	P_Map16x16_configureStart();
	P_Map16x16_configureBG0();

	// Configure the sub engine backgrounds
	P_Map16x16_configureBG2_Sub();

	// Configure the sub engine sprites
	P_Graphics_configureSprites();
}

void P_Graphics_configureSprites(){
	//Allocate space for the graphic to show in the sprites (enemies, red car, jump animation)
	gfx_red = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_16Color);
	gfx_jump = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_16Color);
	gfx_pink_down = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_16Color);
	gfx_pink_up = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_16Color);

	//Copy data for the graphic (palette)
	dmaCopy(carredPal, SPRITE_PALETTE_SUB, carredPalLen);
	dmaCopy(carjumpPal, &SPRITE_PALETTE_SUB[16], carjumpPalLen);
	dmaCopy(carpinkPal, &SPRITE_PALETTE_SUB[32], carpinkPalLen);

	dmaCopy(carpinkPal, SPRITE_PALETTE, carpinkPalLen);

	//Copy data for the graphic (tiles)
	dmaCopy(carredTiles, gfx_red, carredTilesLen);
	dmaCopy(carjumpTiles, gfx_jump, carjumpTilesLen);
	dmaCopy(carpinkTiles, gfx_pink_down, carpinkTilesLen);
	dmaCopy(carpinkTiles, gfx_pink_up, carpinkTilesLen);

	//Show the red car and hide the jump animation and the enemies
	P_Graphics_setCarRed(128, false);
	P_GraphicsSub_setCarPink(0, 0, true, 2);
	P_Graphics_setCarJump(100, true);
	P_GraphicsMain_setCarPink(0, 0, true);
}



void P_Graphics_setCarRed(int sprite_x, bool hide){
	oamSet(&oamSub, 				// oam handler
		2,							// Number of sprite
		sprite_x, POS_REDCAR,		// Coordinates
		0,							// Priority
		0,							// Palette to use
		SpriteSize_16x16,			// Sprite size
		SpriteColorFormat_16Color,	// Color format
		gfx_red,			// Loaded graphic to display
		-1,				// Affine rotation to use (-1 none)
		false,			// Double size if rotating
		hide,			// Hide this sprite
		false, false,	// Horizontal or vertical flip
		false			// Mosaic
		);
	//Update the sprites
	oamUpdate(&oamSub);
}


void P_GraphicsSub_setCarPink(int sprite_x, int sprite_y, bool hide, int palette){
	oamSet(&oamSub, 				// oam handler
		1,							// Number of sprite
		sprite_x, sprite_y,			// Coordinates
		0,							// Priority
		palette,							// Palette to use
		SpriteSize_16x16,			// Sprite size
		SpriteColorFormat_16Color,	// Color format
		gfx_pink_down,			// Loaded graphic to display
		-1,				// Affine rotation to use (-1 none)
		false,			// Double size if rotating
		hide,			// Hide this sprite
		false, false,	// Horizontal or vertical flip
		false			// Mosaic
		);
	//Update the sprites
	oamUpdate(&oamSub);
}

void P_GraphicsMain_setCarPink(int sprite_x, int sprite_y, bool hide){
	oamSet(&oamMain, 				// oam handler
		3,							// Number of sprite
		sprite_x, sprite_y,			// Coordinates
		0,							// Priority
		1,							// Palette to use
		SpriteSize_16x16,			// Sprite size
		SpriteColorFormat_16Color,	// Color format
		gfx_pink_up,			// Loaded graphic to display
		-1,				// Affine rotation to use (-1 none)
		false,			// Double size if rotating
		hide,			// Hide this sprite
		false, false,	// Horizontal or vertical flip
		false			// Mosaic
		);
	//Update the sprites
	oamUpdate(&oamMain);
}

void P_Graphics_setCarJump(int sprite_x, bool hide){
	oamSet(&oamSub, 				// oam handler
		0,							// Number of sprite
		sprite_x-8, 95,				// Coordinates
		0,							// Priority
		1,							// Palette to use
		SpriteSize_32x32,			// Sprite size
		SpriteColorFormat_16Color,	// Color format
		gfx_jump,			// Loaded graphic to display
		-1,				// Affine rotation to use (-1 none)
		false,			// Double size if rotating
		hide,			// Hide this sprite
		false, false,	// Horizontal or vertical flip
		false			// Mosaic
		);
	//Update the sprites
	oamUpdate(&oamSub);
}
