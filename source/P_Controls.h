/*
 * P_Controls.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include <nds.h>

#include "P_Map16x16.h"


/*
 * \brief Handle the keys pressed by the player
 * The car don't move along the y-axis.
 * The keys are defined as following :
 * 	- KEY UP : 		The car speed up if the key is pressed once. To go faster,
 *					the player needs to press again the key to increase speed.
 *					The speed is limited to 5, which means that the speed can go above.
 * 	- KEY DOWN :	The car slow down if the key is held.
 * 	- KEY RIGHT :	The car turns right when the right key is held.
 * 	- KEY LEFT :	The car turns left when the left key is held.
 * 	- KEY A : 		The car jumps when the A key is held.
 * 	- KEY_START : 	Bring back to the start menu and reset the score to zero
 *
 */
void handleKeys();

/*
 * \brief Handle the touch screen pressed by the player
 * The car don't move along the y-axis. The start button must be pressed before
 * handling the touch screen.
 * The keys are defined as following :
 * 		- Double touch : The car jumps.
 * 		- y < 30 : The car speeds up.
 * 		- y > 162 : The car slows down.
 * The position of the touch is read and is compared with the current position
 * of the car :
 * 		- x_car < x : The car turns right.
 * 		- x_car > x : The  car turns left.
 * To jump, the player must do a simple touch.
 */
void handleTouch();



