
#include "P_GamePlay.h"
#include "P_Score.h"

int speed = 0, x_car = 128;

void Gameplay_handleInput(enum ACTION a){
	switch(a){
	case JUMP :
		break;
	case SPEED:
		if (speed < 3)speed++; break;
	case LEFT:
		if (x_car >= 70) x_car-=1; break;
	case RIGHT:
		if (x_car < 180)x_car++; break;
	default:
		break;
	}
}

void Gameplay_Update(){
	P_Map16x16_scrolling_BG3(speed);
	P_Map16x16_scrolling_BG2_Sub(speed);
	P_Graphics_setSprites(oamSub, 1, x_car, 100, 0);
	updateScore(speed);
}


int carTouched(int x_enemy, int y_enemy){
	int touch = 0;
	if (y_enemy+2*SPRITE_HEIGHT == 95 || y_enemy-2*SPRITE_HEIGHT == 95 ){
		if (x_car+2*SPRITE_WIDTH == x_enemy || x_car == x_enemy +2*SPRITE_WIDTH)
			touch = 1;
	}
	return touch;
}
