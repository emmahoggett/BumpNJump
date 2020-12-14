/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "P_Initializer.h"
#include "P_Controls.h"
#include "P_GamePlay.h"


int main(void) {
	P_InitNDS();

	while(1){
		handleKeys();
		handleTouch();
		Gameplay_Update();
	}
}
