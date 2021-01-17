/*
 * P_Graphics.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#pragma once

#include <nds.h>
#include "startscreenmain.h"

/*
 * \brief It enables the corresponding VRAM bank to be used.
 *
 * The following parameters are set:
 * 	a.VRAM_A
 * 		- Main engine background
 * 		- MODE_0_2D
 * 		- Background 1 & 2
 *
 *  b.VRAM_C
 * 		- Sub engine background
 * 		- MODE_0_2D
 * 		- Background 2
 *
 * 	c.VRAM_B
 * 		- Main engine sprites
 *
 *  d.VRAM_D
 * 		- Sub engine sprites
 *
 * This function does not receive any input parameter.
 */
void P_Graphics_setup_main();



