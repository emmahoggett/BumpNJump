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
#include "P_Score.h"
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
u16* gfx_pink_up;
u16* gfx_pink_down;

/*
 * \brief Configure the main background 1
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
 * \brief Configure the main background 0
 * The "warning.png" is stored and appear every time a jump action is required
 * from the user. This function is thus link with a timer that make the sign
 * blink.
 *
 * The following configuration is performed:
 * 		- 32x32 tile map
 * 		- 16 color palette - - BG_PALETTE 10
 * 		- BG_MAP 9 - BG_TILE 2
 */
void P_Map16x16_configureBG0();

/*
 * \brief Configure the main background 2
 * The "numbers.png" is stored and is used to show the score to the player and
 * the highest score. Both scores are showed on the left upper section of the
 * main screen. When the start menu is activated the player score is erased and
 * the highest score is moved to the center of the screen.
 *
 * The following configuration is performed:
 * 		- 32x32 tile map
 * 		- 16 color palette - BG_PALETTE 8 & 9
 * 		- BG_MAP 10 - BG_TILE 3
 *
 * Two color palettes are used, one for the highest score that is orange and one
 * for the players score that is white.
 */
void P_Map16x16_configureBG2();

/*
 * \brief Configure the main background 3
 * The "road.png" is stored and correspond to the road background.
 *
 * The following configuration is performed:
 * 		- 32x64 tile map
 * 		- 16 color palette - BG_PALETTE 0
 * 		- BG_MAP 7 - BG_TILE 0
 *
 * As the map of the road is larger then the previous images, a second memory
 * slot is used, BG_MAP 8.
 */
void P_Map16x16_configureBG3();

void P_Map16x16_configureBG2_Sub();

/*
 * \brief Make the scrolling accordingly to the speed of the car on the main
 * background 3, that correspond to the road.
 *
 * The car speed is controlled by players. If the position is close to the jump,
 * the Timer0 is triggered and it triggers the warning sign blinking.
 */
void P_Map16x16_scrolling_BG3(int _speed);
void P_Map16x16_scrolling_BG2_Sub(int _speed);
void P_Map16x16_scrolling_Init();

/*
 * \brief The position of the road is returned
 */
int scroll_pos(int bg_num);


void P_Map16x16_Init();

void P_Graphics_configureSprites();
void P_Graphics_setCarRed(int sprite_x, bool hide);
void P_Graphics_setCarPink(OamState* oam, int sprite_x, int sprite_y, bool hide, int palette);
void P_Graphics_setCarJump(int sprite_x, bool hide);




