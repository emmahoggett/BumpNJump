/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "P_Graphics.h"

int main(void) {
	
	 P_Graphics_Main();
	 P_Graphics_Main_config_BG0();

    while(1)
        swiWaitForVBlank();	
}
