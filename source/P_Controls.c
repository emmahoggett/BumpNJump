#include "P_Controls.h"

//Position
int x_car = 127, speed = 0, keys;
int  image;


void handleKeys(){
		scanKeys();
		keys = keysHeld();
    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT) && (x_car < (SCREEN_WIDTH - SPRITE_WIDTH))) x_car+=2;
    	if((keys & KEY_DOWN) && (speed < 3)) speed+=1;
    	if((keys & KEY_LEFT) && (x_car  > 66)) x_car-=2;
    	if((keys & KEY_UP) && (speed  > 0)) speed-=1;
    	P_Graphics_Main_scrolling_BG0(speed);
    	P_Graphics_Sub_scrolling_BG0(speed);
    	spritePosition(oamSub, 1, x_car, 100);
}

void spritePosition(OamState oam, int sprite, int sprite_x, int sprite_y){
	oamSet(&oam, 	// oam handler
		sprite,				// Number of sprite
		sprite_x, sprite_y,			// Coordinates
		0,				// Priority
		1,				// Palette to use
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


int carTouched(int x_enemy, int y_enemy){
	int touch = 0;
	if (y_enemy+2*SPRITE_HEIGHT == 95 || y_enemy-2*SPRITE_HEIGHT == 95 ){
		if (x_car+2*SPRITE_WIDTH == x_enemy || x_car == x_enemy +2*SPRITE_WIDTH)
			touch = 1;
	}
	return touch;
}

