/*
 * BumpNJumpDefines.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 *
 * Define major variables.
 */

#pragma once

#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

#define	SPRITE_WIDTH	16
#define	SPRITE_HEIGHT	16

#define POS_REDCAR 95

enum ACTION{
	NONE,
	EXIT,
	JUMP,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	START,
};
