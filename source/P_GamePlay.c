/*
 * P_GamePlay.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_GamePlay.h"

int speed = 0, x_car = 128, game_state = 0;
int x_subpink = 128, y_subpink = SCREEN_HEIGHT-SPRITE_HEIGHT;
int x_mainpink = 128, y_mainpink = 0;
int touch = 0, enemy = 0;
int car_pal, car_palmain;
int left_bound = 81, right_bound = 207;


void Gameplay_handleInput(enum ACTION a){
	if (game_state == 0 && a !=START) a = -1;
	switch(a){
	case JUMP :
		irqEnable(IRQ_TIMER1);
		Audio_PlaySoundEX(SFX_JUMP);
		break;
	case DOWN:
		if (speed > 0)speed--; break;
	case UP:
		if (speed < 5)speed++; break;
	case LEFT:
		if (x_car >= left_bound) x_car-=1; break;
	case RIGHT:
		if (x_car < right_bound - SPRITE_WIDTH) x_car++; break;
	case START:
		if (game_state){
			game_state = 0;
		}
		else game_state = 1;
		Gameplay_GraphicsToggle();
	default:
		break;
	}
}

void Gameplay_Update(){
	// Update the road background on the main and the sub engine
	P_Map16x16_scrolling(speed);
	Gameplay_RoadBoundaries();
	Gameplay_Enemies();

	if (Get_TimerTicks1() == 0 && Get_TimerTicks2() == 0 ) {
		EraseJump(x_car);
		carTouched(x_subpink, y_subpink);
	} else if (Get_TimerTicks1() != 0){
		carJump();
	}

	if(Get_TimerTicks1() == 0 && (scroll_pos(2)<=400 && scroll_pos(2)>=390)){
		Gameplay_handleInput(START);
	}
	int pos_scroll_pink = (scroll_pos(2) + y_subpink)%512;
	if((pos_scroll_pink<=511 && pos_scroll_pink>=416)){
		y_subpink = SCREEN_HEIGHT +1;
	}

	pos_scroll_pink = (scroll_pos(3) + y_mainpink)%512;
	if((pos_scroll_pink<=511 && pos_scroll_pink>=416)){
		// Erase the enemies on the main
		y_mainpink = 0;
	}
	updateScore(speed, touch, enemy, game_state);
	enemy = 0; touch = 0;
}


void P_Game(){
	if (game_state)
		Gameplay_Update();
	handleKeys();
	handleTouch();
}

void Gameplay_GraphicsToggle(){
	int i;
	car_pal = rand()%3 +2;
	for (i = 0; i<32*32; i++){
		BG_MAP_RAM(10)[i] = 0;
	}
	if (game_state){
		readMaxScore();
		// Disable the start background and enable the game background
		REG_DISPCNT = ~(DISPLAY_BG1_ACTIVE) & ~(MODE_0_2D) & ~(DISPLAY_BG2_ACTIVE);
		REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG3_ACTIVE;
		displayMaxScore();
		oamInit(&oamMain, SpriteMapping_1D_32, false);
		y_mainpink = 0;
	}else {
		writeMaxScore();
		speed = 0;
		P_Map16x16_scrolling_Init();
		REG_DISPCNT = ~(DISPLAY_BG1_ACTIVE) & ~(DISPLAY_BG3_ACTIVE) & ~(DISPLAY_BG0_ACTIVE) & ~(MODE_0_2D);
		REG_DISPCNT = MODE_0_2D | DISPLAY_BG1_ACTIVE |DISPLAY_BG2_ACTIVE;
		displayMaxScore_Start(game_state);
		updateScore(speed, touch, enemy, game_state);
	}

}

void carTouched(int x_enemy, int y_enemy){
	if ((abs(y_enemy-POS_REDCAR) < SPRITE_HEIGHT/2) && (abs (x_car- x_enemy)< SPRITE_WIDTH/2)){
		if (Get_TimerTicks2() == 0){
			enemy = 50;
			irqEnable(IRQ_TIMER2);
			Audio_PlaySoundEX(SFX_ENEMY);
		}
	}
}



void carJump(){
	if (abs(y_subpink-POS_REDCAR) < SPRITE_HEIGHT){
		if (abs (x_car- x_subpink)< SPRITE_WIDTH){
			y_subpink = SCREEN_HEIGHT;
			touch = 100;
			car_pal = rand()%3 + 2;
			P_Graphics_setCarPink(&oamSub,x_subpink, y_subpink, true, car_pal);
		}
	}
}

void Gameplay_Enemies(){
	int sgn_x= rand()%3 -1;
	if (x_subpink+sgn_x < 70 )
		x_subpink =70;
	else if (x_subpink+sgn_x > 180 )
		x_subpink =180;
	else x_subpink= x_subpink+sgn_x;

	y_subpink = y_subpink - 1;

	if ((y_subpink <0 || y_subpink > SCREEN_HEIGHT )||( game_state ==0)){
		y_subpink = SCREEN_HEIGHT;
		x_subpink = rand()%111 + 70;
		car_pal = rand()%3 + 2;
		P_Graphics_setCarPink(&oamSub,x_subpink, y_subpink, true, car_pal);
	}else{
		P_Graphics_setCarPink(&oamSub,x_subpink, y_subpink, false, car_pal);
	}
	if (y_subpink <= 0) {
		y_mainpink = SCREEN_HEIGHT;
		x_mainpink = x_subpink;
		car_palmain = car_pal;
	}
	if (y_mainpink > 0){
		P_Graphics_setCarPink(&oamMain,x_mainpink, y_mainpink, false, car_palmain);
		y_mainpink -=1;
		int sgn_x= rand()%3 -1;
		if (x_mainpink+sgn_x < 70 )
			x_mainpink =70;
		else if (x_mainpink+sgn_x > 180 )
			x_mainpink =180;
		else x_mainpink= x_mainpink+sgn_x;
	} else {
		P_Graphics_setCarPink(&oamMain,x_mainpink, y_mainpink, true, car_palmain);
	}

}
void Gameplay_RoadBoundaries(){
	int pos_car = (scroll_pos(2) + POS_REDCAR)%512;
	if (pos_car >264 && pos_car < 296-SPRITE_HEIGHT){
		left_bound = 67;
		right_bound = 187;
	} else if (pos_car >184 && pos_car < 215-SPRITE_HEIGHT){
		left_bound = 67;
		right_bound = 219;
	} else {
		left_bound = 81;
		right_bound = 207;
	}
}

int Get_Car_Pos(){return x_car;}
