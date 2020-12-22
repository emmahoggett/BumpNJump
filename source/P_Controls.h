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
 * 		- KEY_A : to jump
 * 		- KEY_UP : to increase the speed of the background
 * 		- KEY_DOWN : to decrease the speed of the background
 * 		- KEY_LEFT : to move the car left
 * 		- KEY_RIGHT : to move the car right
 * 		- KEY_START : bring back to the start menu and reset the score to zero
 */
void handleKeys();

/*
 * \brief Handle the touch screen pressed by the player
 * The car don't move along the y-axis. The start button must be pressed before
 * handling the touch screen.
 * The keys are defined as following :
 * 		- double touch : to jump
 * 		- y >= 96 : to increase the speed of the background
 * 		- y < 96 : to decrease the speed of the background
 * 		- x < 128 : to move the car left
 * 		- x >= 128 : to move the car right
 */
void handleTouch();



