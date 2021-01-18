/*
 * P_Timer.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */


#include <nds.h>
#include "P_Map16x16.h"
#include "P_GamePlay.h"

/*
 * \brief Initialize the TIMER0, TIMER1 and TIMER2.
 *
 * The TIMER0 is for the warning blinking before every jump. The frequency of
 * the interrupt is 100[ms]. This last for 1 [s].
 * The TIMER1 is for the jump animation of the car.  The frequency of
 * the interrupt is 100[ms]. This animation last for 1[s].
 * The TIMER2 is when the car is touched by an enemy.  The frequency of
 * the interrupt is 100[ms]. This animation last for 1[s].
 *
 * The two timers aren't enabled.
 * This function does not receive any input parameter.
 */
void P_Timer_Init();

/*
 *\brief Function that display the warning sign.
 *
 * Fill the main engine with the warning tile. The TILE_PALETTE(10)
 * correspond to the palette of the warning tile.
 * The warning tile is shown at the bottom center of the main engine.
 * This function does not receive any input parameter.
 */
void DisplayWarning();
/*
 *\brief Function that remove the warning sign.
 * Fill the main engine with the transparent tile where the warning sign is
 * shown. This has effect to erase the warning sign.
 * This function does not receive any input parameter.
 */
void EraseWarning();
/*
 *\brief Function that display the jump animation at position x.
 * The jump animation correspond to a sprite that is shown when the jump action
 * is performed.
 * @param x	:	Position where the jump animation will be displayed along x.
 */
void DisplayJump(int x);
/*
 *\brief Function that remove the jump animation at position x.
 * The jump animation correspond to a sprite that is erased when the jump action
 * is performed.
 * @param x	:	Position where the car will be displayed along x.
 */
void EraseJump(int x);

/*
 * \brief Returns the tick of the TIMER1.
 * This timer is linked with the car's jump.
 * This function is used for the P_Gameplay to know if a jump is performed or
 * not.
 * @return A positive integer that correspond to the 1st timer counter.
 */
int Get_TimerTicks1();

/*
 * \brief Returns the tick of the TIMER2.
 * This timer is linked with the car's blinking when it is touched by an enemy.
 * This function is used for the P_Gameplay to know if the car is touched by an
 * enemy
 * @return A positive integer that correspond to the 2nd timer counter.
 */
int Get_TimerTicks2();
