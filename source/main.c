#include <nds.h>
#include <stdio.h>

#include "P_Initializer.h"
#include "P_Controls.h"
#include "P_GamePlay.h"


int main(void) {
	P_InitNDS();

	while(1){
		P_Game();
		oamUpdate(&oamSub);
		oamUpdate(&oamMain);
		swiWaitForVBlank();
	}
}
