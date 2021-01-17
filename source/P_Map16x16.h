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
 * \brief Initialize engines' background and sprites.
 */
void P_Map16x16_Init();

/*
 * \brief Configure the main background 1
 * The "startscreen.png" is stored and appears when the start button is pushed
 * or before starting the game.
 *
 * The following configuration is performed:
 * 		- 32x32 tile map
 * 		- 16 color palette - BG_PALETTE 13
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
 * 		- 16 color palette - BG_PALETTE 10
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
 * 		- BG_MAP 7 & 8 - BG_TILE 0
 *
 * As the map of the road is larger then the previous images, a second memory
 * slot is used, BG_MAP 8.
 */
void P_Map16x16_configureBG3();

/*
 * \brief Configure the sub engine's background 2
 * The "road.png" is stored and correspond to the road background.
 *
 * The following configuration is performed:
 * 		- 32x64 tile map
 * 		- 16 color palette - BG_PALETTE_SUB 0
 * 		- BG_MAP_SUB 0 & 1 - BG_TILE_SUB 1
 *
 * As the map of the road is larger then the previous images, a second memory
 * slot is used, BG_MAP_SUB 1.
 */
void P_Map16x16_configureBG2_Sub();


/*
 * \brief Initialize the road's background scroll position.
 *
 * The road's position for the sub engine is the pixel 193 and for the main engine,
 * the pixel 1.
 */
void P_Map16x16_scrolling_Init();

/*
 * \brief Make the scrolling accordingly to the speed of the car on the main
 * background 3, that correspond to the road.
 *
 * The car speed is controlled by players. If the position is close to the jump,
 * the Timer0 is triggered and it triggers the warning sign blinking.
 */
void P_Map16x16_scrolling(int _speed);


/*
 * \brief Return the position of the road's scrolling
 *
 * @param bg_num : Choose which background scrolling is returned. For the sub
 * engine, bg_num = 2 and the main engine, bg_num = 3.
 *
 * @return A positive integer that is between 0 and 512. The value correspond to
 * the position in the road picture.
 *
 */
int scroll_pos(int bg_num);


/*
 * \brief Configure the car, jump and enemies sprites
 *
 * This function takes into account the memory allocation, the palette
 * configuration
 *
 * The following configuration is performed:
 *  a. For the red car
 * 		- 16x16 sprite size
 * 		- 16 color palette - SPRITE_PALETTE_SUB 0
 * 		- Pointer to the graphic buffer : gfx_red
 * 		- Sub engine
 *
 *  b. For the jump animation
 * 		- 32x32 sprite size
 * 		- 16 color palette - SPRITE_PALETTE_SUB 1
 * 		- Pointer to the graphic buffer : gfx_jump
 * 		- Sub engine
 *
 *  c. For the enemies in the sub engine
 * 		- 16x16 sprite size
 * 		- 16 color palette - SPRITE_PALETTE_SUB 2, 3 & 4
 * 		- Pointer to the graphic buffer : gfx_pink_down
 * 		- Sub engine
 *
 *  d. For the enemies in the main engine
 * 		- 16x16 sprite size
 * 		- 16 color palette - SPRITE_PALETTE 2, 3 & 4
 * 		- Pointer to the graphic buffer : gfx_pink_up
 * 		- Main engine
 */
void P_Graphics_configureSprites();

/*
 * \brief Set the red car position along x and if the sprites needs to be hiden.
 *
 * @param sprite_x	:	Integer that correspond to the position along x of the car
 * 					 	on the screen.
 * @param hide		: 	Boolean, if true the car is hiden otherwise the car is shown.
 */
void P_Graphics_setCarRed(int sprite_x, bool hide);
/*
 * \brief Set the enemies position (x & y), color (2,3 & 4), OamState (oamSub & oamMain),
 * and finally if the sprite is hiden or not.
 *
 * @param oam		:	OamState pointer that correspond tto which engine is used
 * 						(oamSub or oamMain)
 * @param sprite_x	:	Integer that correspond to the position along x of the enemy
 * 					 	on the screen.
 * @param sprite_y	:	Integer that correspond to the position along y of the enemy
 * 					 	on the screen.
 * @param hide		: 	Boolean, if true the enemy is hiden otherwise the enemy is shown.
 * @param palette	: 	Integer that correspond to the palette (2,3 & 4) used.
 * 						The palette definition is the same for the main and sub
 * 						engine for practical reasons.
 */
void P_Graphics_setCarPink(OamState* oam, int sprite_x, int sprite_y, bool hide, int palette);

/*
 * \brief Set the jump position along x and if the sprite needs to be hiden.
 *
 * @param sprite_x	:	Integer that correspond to the position along x of the jump
 * 					 	on the screen.
 * @param hide		: 	Boolean, if true the jump is hiden otherwise the jump is shown.
 */
void P_Graphics_setCarJump(int sprite_x, bool hide);




