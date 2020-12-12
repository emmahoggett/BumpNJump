#include "P_Initializer.h"

int game_state = 0, timer_ticks, tile1=0, tile2 = 0, i;

void timer0_ISR(){
	timer_ticks++;
	if (timer_ticks%2){
		tile1 = 1, tile2 = 2;
	} else {
		tile1 = 0, tile2 = 0;
	}
	if (timer_ticks == 15){
		irqDisable(IRQ_TIMER0);
		timer_ticks = 0;
		tile1 = 0, tile2 = 0;
	}
	for (i = 0; i<32*32; i++){
		if ((i > 14 && i <19) ||(i > 78 && i <83) ||  (i > 142 && i <147)
				|| i == 47 || i == 50 || i == 111 || i == 114) BG_MAP_RAM(1)[i] = tile2;
		else if (i == 48 || i == 49 || i == 112 || i == 113 ) BG_MAP_RAM(1)[i] = tile1;
		else BG_MAP_RAM(1)[i] = 0;
	}
}

void P_InitNDS(){

	 P_Graphics_Sub();
	 P_Graphics_Main();

	 P_Graphics_Main_config_Start();
	 P_Graphics_Sub_config_Start();

	while (game_state == 0){
		scanKeys();
		unsigned keys = keysDown();
		if (keys & KEY_START ||keys & KEY_TOUCH){
			game_state = 1;
		}
	}
	InitTimer();
	P_Graphics_Main_config_BG0();
	P_Graphics_Main_config_BG2();
	P_Graphics_Sub_config_BG0();
	//Configure sprites and fill graphics
	P_Graphics_configureSprites();

}

void InitTimer(){
	timer_ticks = 0;
	TIMER_CR(0) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER_DATA(0) = TIMER_FREQ_1024(10);
	irqSet(IRQ_TIMER0, &timer0_ISR);

}


