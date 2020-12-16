#include "P_GamePlay.h"


int speed = 0, x_car = 128, game_state = 0;
int x_pink = 128, y_pink = SCREEN_HEIGHT-SPRITE_HEIGHT;
int touch = 0, enemy = 0;


void Gameplay_handleInput(enum ACTION a){
	if (game_state == 0 && a !=START) a = -1;
	switch(a){
	case JUMP :
		irqEnable(IRQ_TIMER1);
		Audio_PlaySoundEX(SFX_JUMP);break;
	case SPEED:
		if (speed < 5)speed++; break;
	case LEFT:
		if (x_car >= 70) x_car-=1; break;
	case RIGHT:
		if (x_car < 180) x_car++; break;
	case START:
		if (game_state == 0) game_state = 1;
		else game_state = 0;
	default:
		break;
	}
}

void Gameplay_Update(){
	P_Map16x16_scrolling_BG3(speed);
	P_Map16x16_scrolling_BG2_Sub(speed);

	Gameplay_Enemies();
	if ( Get_TimerTicks1() == 0) {
		EraseJump(x_car);
		carTouched(x_pink, y_pink);
	} else {
		carJump(x_pink, y_pink);
	}
	updateScore(speed, touch, enemy);
	enemy = 0; touch = 0;
}


void carTouched(int x_enemy, int y_enemy){
	if (abs(y_pink-POS_REDCAR) < SPRITE_HEIGHT/2){
		if (abs (x_car- x_enemy)< SPRITE_WIDTH/2){
			Audio_PlaySoundEX(SFX_ENEMY);
			enemy = 50;
		}
	}
}

void carJump(int x_enemy, int y_enemy){
	if (abs(y_pink-POS_REDCAR) < SPRITE_HEIGHT){
		if (abs (x_car- x_enemy)< SPRITE_WIDTH){
			Audio_PlaySoundEX(SFX_ENEMY);
			y_pink = SCREEN_HEIGHT-SPRITE_HEIGHT;
			x_pink = rand()%111 + 70;
			P_Graphics_setCarPink(x_pink, y_pink, true);
			touch = 100;
		}
	}
}

void Gameplay_Enemies(){
	int sgn_x= rand()%3 -1,sgn_y= rand()%3 -1;
	if (x_pink+sgn_x < 70 )
		x_pink =70;
	else if (x_pink+sgn_x > 180 )
		x_pink =180;
	else x_pink= x_pink+sgn_x;

	if (y_pink > 128-SPRITE_HEIGHT)
		y_pink--;
	else if (y_pink < 64-SPRITE_HEIGHT)
		y_pink++;
	else
		y_pink = y_pink+sgn_y;

	if ((y_pink <SPRITE_HEIGHT && y_pink > SCREEN_HEIGHT-SPRITE_HEIGHT )||( speed ==0)){
		y_pink =SCREEN_HEIGHT-SPRITE_HEIGHT;
		P_Graphics_setCarPink(x_pink, y_pink, true);
	}else{
		P_Graphics_setCarPink(x_pink, y_pink, false);
	}


}

int Get_Car_Pos(){return x_car;}
