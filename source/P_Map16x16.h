/*
 * P_Map16x16.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include <nds.h>
#include <stdio.h>
#include "BumpNJumpDefines.h"
#include "P_Graphics.h"
#include "road.h"
#include "numbers.h"
#include "warning.h"
#include "carred.h"
#include "carjump.h"
#include "carpink.h"
#include "startscreenmain.h"

//Pointer to the graphic buffer where to store the sprites
u16* gfx_red;
u16* gfx_jump;
u16* gfx_pink;

/*
 * \brief Configure the background 1
 * The "startscreen.png" is stored and appears when the start button is pushed
 * or before starting the game.
 *
 * The following configuration is performed:
 * 		- 32x32 tile map
 * 		- 16 color palette
 * 		- BG_MAP 12 - BG_TILE 4
 */
void P_Map16x16_configureStart();

/*
 * \brief Configure the background 0
 * The "warning.png" is stored and appear every time a jump action is required
 * from the user. This function is thus link with a timer that make the sign
 * blink.
 *
 * The following configuration is performed:
 * 		- 32x32 tile map
 * 		- 16 color palette
 * 		- BG_MAP 9 - BG_TILE 2
 */
void P_Map16x16_configureBG0();


void P_Map16x16_configureBG2();
void P_Map16x16_configureBG3();

void P_Map16x16_configureBG2_Sub();

void P_Map16x16_scrolling_BG3(int _speed);
void P_Map16x16_scrolling_BG2_Sub(int _speed);
void P_Map16x16_scrolling_Init();
int scroll_pos(int bg_num);


void P_Map16x16_Init();

void P_Graphics_configureSprites();
void P_Graphics_setCarRed(int sprite_x, bool hide);
void P_Graphics_setCarPink(int sprite_x, int sprite_y, bool hide);
void P_Graphics_setCarJump(int sprite_x, bool hide);




