#pragma once

/*
 * P_Audio.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"


/*
 * \brief Initialize and load the sound library.
 *	Here is the list of the effects and music that are loaded
 *	 	MOD_RETROGAMES_INGAME3 : Game music
 *	 	SFX_JUMP : Jump effect
 *	 	SFX_ENEMY : Enemy effect
 */
void Audio_Init();

/*
 * \brief Play the effects in the sound library.
 *
 * @param i : Name of the effect - (SFX_JUMP - SFX_ENEMY)
 */
void Audio_PlaySoundEX(int i);

/*
 * \brief Play the music in the sound library, in loop.
 */
void Audio_PlayMusic();

