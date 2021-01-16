/*
 * P_Audio.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Audio.h"

void Audio_Init()
{
	//Init the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);
	//Load module
	mmLoad(MOD_RETROGAMES_INGAME3);
	//Load effects - Jump and enemy effects
	mmLoadEffect(SFX_JUMP);
	mmLoadEffect(SFX_ENEMY);

}
void Audio_PlaySoundEX( int i )
{
	//Declare a sound effect
	mm_sound_effect sound;
	//Set the id of the sound effect with the input parameter
	sound.id = i;
	//Set the rate to the default one (1024)
	sound.rate = 1024;
	//Set the volume to the maximum - 255 (range 0...255)
	sound.volume = 255;
	//Set the panning at the center - 127 (0-left....255-right)
	sound.panning = 127;
	//Play the effect using the sound structure
	mmEffectEx(&sound);
}


void Audio_PlayMusic()
{
	//Start playing music in a loop
	mmStart(MOD_RETROGAMES_INGAME3, MM_PLAY_LOOP);
	//Set module volume to 512 (range 0...1024) using the function mmSetModuleVolume(...)
	mmSetModuleVolume(512);
}
