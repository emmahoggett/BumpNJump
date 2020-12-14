#include "P_Initializer.h"



void P_InitNDS(){
	P_Graphics_setup_main();

	P_Map16x16_Init();
	P_Timer_Init();
	DisplayWarning();

	Audio_Init();
	Audio_PlayMusic();

}
