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
 * \brief Initialize the TIMER0 and TIMER1.
 *
 * The TIMER0 is for the warning blinking before every jump. The frequency of
 * the interrupt is 100[ms]. This last for 1 [s].
 * The TIMER1 is for the jump animation of the car.  The frequency of
 * the interrupt is 100[ms]. This animation last for 500[ms].
 *
 * The two timers aren't enabled.
 */
void P_Timer_Init();

/*
 *\brief Function that display the warning sign
 */
void DisplayWarning();
/*
 *\brief Function that remove the warning sign
 */
void EraseWarning();
/*
 *\brief Function that display the jump animation at position x
 * The jump animation correspond to a sprite that is shown when the jump action
 * is performed.
 */
void DisplayJump(int x);
/*
 *\brief Function that remove the jump animation at position x
 * The jump animation correspond to a sprite that is erased when the jump action
 * is performed.
 */
void EraseJump(int x);

/*
 * \brief Returns the tick of the timer 1. This timer is linked with the car's
 * jump.
 * This function is used for the P_Gameplay to know if a jump is performed or
 * not.
 */
int Get_TimerTicks1();

/*
 * \brief Returns the tick of the timer 2. This timer is linked with the car's
 * blinking when it is touched by an enemy.
 * This function is used for the P_Gameplay to know if the car is touched by an
 * enemy
 */
int Get_TimerTicks2();
