#include "P_Initializer.h"



void P_InitNDS(){

	 P_Graphics_Main();
	 P_Graphics_Sub();
	 P_Graphics_Main_config_BG0();
	 P_Graphics_Sub_config_BG0();


  	//Configure sprites and fill graphics
	 P_Graphics_configureSprites();
}

