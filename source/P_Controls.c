/*
 * P_Controls.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Controls.h"
#include "P_GamePlay.h"


int jump = 0, iter = 30;
touchPosition touch; int x, y;


void handleKeys(){
		// Obtain the current keypad state - Obtain the current keypad held state.
		scanKeys();
		unsigned keys = keysHeld();

    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT)) Gameplay_handleInput(RIGHT);
    	if((keys & KEY_DOWN)) Gameplay_handleInput(DOWN);
    	if((keys & KEY_UP)) Gameplay_handleInput(UP);
    	if((keys & KEY_LEFT)) Gameplay_handleInput(LEFT);

    	//Make the car jump
    	if ((keys & KEY_A)) Gameplay_handleInput(JUMP);
    	//Bring back to the start menu if the start button is pressed once
    	if ((keysDown() & KEY_START))Gameplay_handleInput(START);
}

void handleTouch(){
	/*
	 * Condition to make the car jump - the simple touch
	 * 		- Screen not touched : jump = 1
	 * 		- Screen touched & jump == 1 : jump = 2
	 * 		- Screen not touched & jump == 2 : Make the jump action
	 * There is a counter for the 3rd condition, such that the jump is not
	 * performed automatically.
	 *
	 */
	// Obtain the current keypad state
	scanKeys();
	//Read the touched position
	touchRead(&touch);
	x = touch.px; y = touch.py;
	if (keysHeld() & KEY_TOUCH){ //The screen is touched
		//Modify position of the sprite accordingly
		if (x < Get_Car_Pos())  Gameplay_handleInput(LEFT);
		else if (x > Get_Car_Pos()) Gameplay_handleInput(RIGHT);
		if (y < 30)  Gameplay_handleInput(UP);
		else if (y > 162) Gameplay_handleInput(DOWN);
	}
	// Handling the jump action
	if (x==0 && y==0){
		// The touch screen is untouched
		if (jump == 0) jump = 1;
		else if (jump == 2) {
			Gameplay_handleInput(JUMP);
			jump = 0;
		}
	} else  if ((keysHeld() & KEY_TOUCH) && (jump == 1)) jump = 2;  // The touch screen is touched
	// Counter - initialize jump if the scanKeys is called 30 times.
	iter--;
	if (iter == 0) {
		jump = 0; iter = 30;
	}

}


