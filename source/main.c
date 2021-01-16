#include <nds.h>
#include <stdio.h>

#include "P_Initializer.h"
#include "P_Controls.h"
#include "P_GamePlay.h"


int main(void) {
	// Initialize the engines, backgrounds, timers and audio.
	P_InitNDS();

	while(1){
		P_Game();

		// Update the sprites in the main and sub engine
		oamUpdate(&oamSub);
		oamUpdate(&oamMain);

		// Wait for VBlank interrupt
		swiWaitForVBlank();
	}
}
