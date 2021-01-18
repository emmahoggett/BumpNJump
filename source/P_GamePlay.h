/*
 * P_GamePlay.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#pragma once

#include <nds.h>
#include "BumpNJumpDefines.h"
#include "P_Audio.h"
#include "P_Map16x16.h"
#include <nds/arm9/sound.h>		// sound functions
#include "soundbank.h"
#include "P_Score.h"
#include "P_Timer.h"
#include "P_Controls.h"

/*
 * \brief Initialize Gameplay (game state, score).
 * ELLE NEST PAS DANS LE .c ?
 * This function does not receive any input parameter.
 */
void Gameplay_Init();

/*
 * \brief Handle the action enabled by pressing the corresponding keys
 *
 * @param Action a : enumeration a defined as ACTION, possible action are JUMP, RIGHT, LEFT, DOWN, UP, START.
 */
void Gameplay_handleInput(enum ACTION a);

/*
 * \brief Update road background, road boundaries, car position, enemy position, jump and the score
 * This function does not receive any input parameter.
 */
void Gameplay_Update();

/*
 * \brief Disable the main background and display the start screen with updated score.
 * This function does not receive any input parameter.
 */
void Gameplay_GraphicsToggle();

/*
 * \brief Handle keys, touch and update the game, if the game is on.
 * This function does not receive any input parameter.
 */
void P_Game();

/*
 * \brief Configure the sprite enemy
 *
 * Position configuration for the subscreen and the main screen.
 * This function does not receive any input parameter.
 */
void Gameplay_Enemies();

/*
 * \brief Configure the road boundaries for a given scrolling position.
 * @param pos	:	Integer that correspond to the scrolling position or the position along y of the car
 * 				    on the map.
 * @param left	: 	Integer, pointer modified accordingly to pos.
 * @param right	: 	Integer, pointer modified accordingly to pos.
 */
void Gameplay_RoadBoundaries(int pos, int* left, int* right);

/*
 * \brief Define if the car enemy has been touched.
 *
 * @param x_enemy	:	Integer that correspond to the position along x of the enemy
 * 					 	on the screen.
 * @param y_enemy	:	Integer that correspond to the position along y of the enemy
 * 					 	on the screen.
 * Enable Timer2.
 * The car blinks for 1[s] with the Timer2.
 * Play the enemy effect.
*/
void carTouched(int x_enemy, int y_enemy);

/*
 * \brief Define if the enemy vehicles that have been jumped upon is detroyed
 *
 * Set if the enemy sprite needs to be hidden.
 * Set the touch score to 100.
 * Set the enemy sprite palette randomly.
 */
void carJump();

/*
 * \brief Return the position of the car along x.
 *
 * This function does not receive any input parameter.
 */
int Get_Car_Pos();
