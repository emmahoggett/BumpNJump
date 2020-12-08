
#include "P_Controls.h"

//Position
int x = 127, y = 175, keys;


void handleInput(){
    	//Read held keys
    	scanKeys();
    	keys = keysHeld();

    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT) && (x < (SCREEN_WIDTH - SPRITE_WIDTH))) x+=2;
    	if((keys & KEY_DOWN) && (y < (SCREEN_HEIGHT - SPRITE_HEIGHT))) y+=2;
    	if((keys & KEY_LEFT) && (x  > 0)) x-=2;
    	if((keys & KEY_UP) && (y  > 0)) y-=2;

    	oamSet(&oamSub, 	// oam handler
    		0,				// Number of sprite
    		x, y,			// Coordinates
    		0,				// Priority
    		0,				// Palette to use
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
		oamUpdate(&oamSub);
}
