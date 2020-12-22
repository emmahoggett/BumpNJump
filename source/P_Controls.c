/*
 * P_Controls.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Controls.h"
#include "P_GamePlay.h"


int jump = 0, iter = 100;


void handleKeys(){
		scanKeys();
		unsigned keys = keysHeld();

    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT)) Gameplay_handleInput(RIGHT);
    	if((keys & KEY_DOWN)) Gameplay_handleInput(DOWN);
    	if((keys & KEY_UP)) Gameplay_handleInput(UP);
    	if((keys & KEY_LEFT)) Gameplay_handleInput(LEFT);

    	//Make the car jump
    	if ((keys & KEY_A)) Gameplay_handleInput(JUMP);
    	//Bring back to the start menu
    	if ((keysDown() & KEY_START))Gameplay_handleInput(START);
}

void handleTouch(){
	/*
	 * Condition to make the car jump - the double touch
	 * 		- Screen not touched : jump = 1
	 * 		- Screen touched & jump == 1 : jump = 2
	 * 		- Screen not touched & jump == 2 : jump = 3
	 * 		- Screen touched & jump == 3 : Make the jump action
	 * There is a counter for the third condition, such that the jump is not
	 * performed automatically.
	 *
	 */
	scanKeys();
	touchPosition touch;
	int x, y;
	//Read the touched position
	touchRead(&touch);
	x = touch.px; y = touch.py;
	//The screen is touched
	if (x || y){
		//Modify position of the sprite accordingly
		if (x < 128)  Gameplay_handleInput(LEFT);
		else if (x >= 128) Gameplay_handleInput(RIGHT);
		if (y < 96)  Gameplay_handleInput(UP);
		else if (y >= 96) Gameplay_handleInput(DOWN);

		if (jump == 1) jump = 2;
		else if (jump == 3) {
			jump = 0;
			Gameplay_handleInput(JUMP);
		}
		iter--;
		if (iter == 0){
			iter = 100; jump = 0;
		}
	} else if (x == 0 && y == 0){ //The screen is not touched
		if (jump == 0)jump = 1;
		else if (jump == 2) jump = 3;
	}

}


