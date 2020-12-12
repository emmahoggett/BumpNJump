#include "P_Controls.h"

//Position
int x_car = 127, speed = 2;
int  jump = 0, comptBg=192;


void handleKeys(){
		scanKeys();
		unsigned keys = keysHeld();
    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT) && (x_car < (SCREEN_WIDTH - SPRITE_WIDTH))) x_car+=2;
    	if((keys & KEY_DOWN) && (speed < 3)) speed+=1;
    	if((keys & KEY_LEFT) && (x_car  > 66)) x_car-=2;
    	P_Graphics_Main_scrolling_BG0(speed);
    	P_Graphics_Sub_scrolling_BG0(speed);
    	spritePosition(oamSub, 1, x_car, 100);
}



int carTouched(int x_enemy, int y_enemy){
	int touch = 0;
	if (y_enemy+2*SPRITE_HEIGHT == 95 || y_enemy-2*SPRITE_HEIGHT == 95 ){
		if (x_car+2*SPRITE_WIDTH == x_enemy || x_car == x_enemy +2*SPRITE_WIDTH)
			touch = 1;
	}
	return touch;
}

void P_Game(){
	scanKeys();
	if (keysDown() & KEY_START){
		 P_InitNDS();
	}
	handleKeys();
	comptBg = (comptBg +speed)%512;
	if (comptBg >= 300 && comptBg<310){
		irqEnable(IRQ_TIMER0);
	}

}

void P_Lose(){

}

