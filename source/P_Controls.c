/*
 * P_Controls.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Controls.h"
#include "P_GamePlay.h"


int  comptBg=192, jump = 0, iter = 100;
int x_prev = 128, y_prev = 96;



void handleKeys(){
		scanKeys();
		unsigned keys = keysHeld();
    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT)) Gameplay_handleInput(RIGHT);
    	if((keys & KEY_DOWN)) Gameplay_handleInput(DOWN);
    	if((keys & KEY_UP)) Gameplay_handleInput(UP);
    	if((keys & KEY_LEFT)) Gameplay_handleInput(LEFT);
    	if ((keys & KEY_A)) Gameplay_handleInput(JUMP);
    	if ((keysDown() & KEY_START))Gameplay_handleInput(START);
}

void handleTouch(){
	scanKeys();
	touchPosition touch;
	int x, y;
	touchRead(&touch);
	x = touch.px; y = touch.py;
	if (x || y){

		if (x < x_prev)  Gameplay_handleInput(LEFT);
		else if (x >= x_prev) Gameplay_handleInput(RIGHT);

		if (y < y_prev)  Gameplay_handleInput(UP);
		else if (y >= y_prev) Gameplay_handleInput(DOWN);

		if (jump == 0) jump = 1;
		else if (jump == 2) {
			jump = 0;
			Gameplay_handleInput(JUMP);
		}
		iter--;
		if (iter == 0){
			iter = 100; jump = 0;
		}
	} else if (x == 0 && y == 0 && jump == 1){
		jump = 2;
	}

}


