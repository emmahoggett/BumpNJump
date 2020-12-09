
#include "P_Controls.h"

//Position
int x = 127, y = 175, keys;
int  image;


void handleInput(){
	for (image = 512-192; image >=0; image-=1){
		swiWaitForVBlank();
		REG_BG0VOFS = (image+192)%(513-192);
		REG_BG0VOFS_SUB = (image+72)%(513-192);
		scanKeys();
		keys = keysHeld();

    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT) && (x < (SCREEN_WIDTH - SPRITE_WIDTH))) x+=2;
    	if((keys & KEY_DOWN) && (y < (SCREEN_HEIGHT - SPRITE_HEIGHT)))
    		y+=2;
    	if((keys & KEY_LEFT) && (x  > 66)) x-=2;
    	if((keys & KEY_UP) && (y  > 0))
    		y-=2;
    	spritePosition(oamSub, 1, x, y);
	}
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


