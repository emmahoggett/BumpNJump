/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "P_Initializer.h"
#include "P_Controls.h"

int image = 0;

int main(void) {

	P_InitNDS();

	while(1){
		for (image = 0; image <=512-192; image++){
			REG_BG0VOFS = image;
			REG_BG0VOFS_SUB = image;
			handleInput();
			swiWaitForVBlank();
		}

	}
}
