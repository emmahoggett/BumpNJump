#include "P_Map16x16.h"

int i, j, bg3_main = 0,bg2_sub = 192, timer_ticks0;

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

void timer0_IRQ(){
	i = 32*32;
	while(i--)
		BG_MAP_RAM(25)[i] = 10;
	for (i = 14; i<17;i+=2){
		for (j = 1; j<6; j++){
			if (j%2){
				BG_MAP_RAM(20)[i + j*32] = 2; BG_MAP_RAM(20)[i + 1 + j*32] = 2;
			}
			else
				BG_MAP_RAM(20)[i + j*32] = 2; BG_MAP_RAM(20)[i + 1 + j*32] = 1;
		}
	}
	timer_ticks0++;
	if (timer_ticks0>=20){
		irqDisable(IRQ_TIMER0);
	}

}


void P_Map16x16_configureBG3(){
	BGCTRL[3] =  BG_32x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	// Transfer of the image and the palette to the engine
	dmaCopy(roadTiles,BG_TILE_RAM(1), roadTilesLen);
	dmaCopy(roadPal,BG_PALETTE, roadPalLen);

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[i*32], &BG_MAP_RAM(0)[i*32],64);
	}

	for (i = 0; i <32; i++){
		dmaCopy(&roadMap[(i+32)*32], &BG_MAP_RAM(1)[i*32],64);
	}
	REG_BG3VOFS = bg3_main;
}

void P_Map16x16_configureBG2(){
	BGCTRL[2] = BG_32x32 | BG_COLOR_16 | BG_MAP_BASE(25) | BG_TILE_BASE(4);

	dmaCopy(numbersTiles,(u8*)BG_TILE_RAM(4),numbersTilesLen);
	dmaCopy(numbersPal,&BG_PALETTE[128],numbersPalLen);
	dmaCopy(numbersPal,&BG_PALETTE[144],numbersPalLen);
	BG_PALETTE[129] = ARGB16(1,31,15,0);
	BG_PALETTE[145] = ARGB16(1,31,31,31);

	int i = 32*32;
	while(i--)
		BG_MAP_RAM(25)[i] = 0;
}

void P_Map16x16_configureBG0(){
	BGCTRL[0] =  BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(20) | BG_TILE_BASE(2);
	// Transfer of the image and the palette to the engine
	dmaCopy(emptyTile,(u8*)BG_TILE_RAM(2), 64);
	dmaCopy(warningTile,(u8*)BG_TILE_RAM(2) + 64, 64);
	dmaCopy(redTile,(u8*)BG_TILE_RAM(2) + 128 , 64);
	BG_PALETTE[255] = ARGB16(1,25,25,25);
	BG_PALETTE[254] = ARGB16(1,31,0,0);

	int i = 32*32;
	while(i--)
		BG_MAP_RAM(20)[i] = 0;

}

void P_Map16x16_scrolling_BG3(int _speed){
	REG_BG3VOFS = bg3_main;
	bg3_main =( bg3_main- _speed)%512;
	if (bg3_main >= 417 && bg3_main <= 417+_speed)
		irqEnable(IRQ_TIMER0);
}

void P_Map16x16_configureBG2_Sub(){
	BGCTRL_SUB[2] =  BG_32x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

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

	P_Map16x16_configureBG3();
	P_Map16x16_configureBG2();
	P_Map16x16_configureBG0();

	P_Map16x16_configureBG2_Sub();
	P_Map16x16_TimerInit();
	P_Graphics_configureSprites();
}

void P_Graphics_configureSprites(){

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

void P_Map16x16_TimerInit(){
	timer_ticks0 = 0;
	TIMER_CR(0) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER_DATA(0) = TIMER_FREQ_1024(10);
	irqSet(IRQ_TIMER0, &timer0_IRQ);
}
