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
int left_bound_enmain = 81, right_bound_enmain = 207;
int left_bound_ensub = 81, right_bound_ensub = 207;


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
		if (speed < 5)speed++;break;
	case LEFT:
		if (x_car >= left_bound) x_car-=1;
		else Gameplay_handleInput(START);
		break;
	case RIGHT:
		if (x_car < right_bound) x_car++;
		else Gameplay_handleInput(START);
		break;
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

	int pos_car = (scroll_pos(2) + POS_REDCAR)%512;
	int pos_enemy_sub = (scroll_pos(2) + y_subpink)%512;
	int pos_enemy_main = (scroll_pos(3) + y_mainpink)%512;

	Gameplay_RoadBoundaries(pos_car, &left_bound, &right_bound);
	Gameplay_RoadBoundaries(pos_enemy_sub, &left_bound_ensub, &right_bound_ensub);
	Gameplay_RoadBoundaries(pos_enemy_main, &left_bound_enmain, &right_bound_enmain);

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
		// Read the max score from previous
		readMaxScore();

		// Disable the main engine in mode 0 (2D) and activate Backgrounds 2 and 1.
		REG_DISPCNT = ~(DISPLAY_BG1_ACTIVE) & ~(MODE_0_2D) & ~(DISPLAY_BG2_ACTIVE);
		// Disable the main engine in mode 0 (2D) and activate Backgrounds 0, 1 and 3.
		REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG3_ACTIVE;
		displayMaxScore();
		oamInit(&oamMain, SpriteMapping_1D_32, false);
		y_mainpink = 0;
		x_car = 128;
		y_subpink = SCREEN_HEIGHT-SPRITE_HEIGHT;
	}else {
		writeMaxScore();
		speed = 0;
		P_Map16x16_scrolling_Init();
		// Disable the main engine in mode 0 (2D) and activate Backgrounds 0, 1 and 3.
		REG_DISPCNT = ~(DISPLAY_BG1_ACTIVE) & ~(DISPLAY_BG3_ACTIVE) & ~(DISPLAY_BG0_ACTIVE) & ~(MODE_0_2D);
		// Disable the main engine in mode 0 (2D) and activate Backgrounds 2 and 1.
		REG_DISPCNT = MODE_0_2D | DISPLAY_BG1_ACTIVE |DISPLAY_BG2_ACTIVE;
		displayMaxScore_Start(game_state);
		updateScore(speed, touch, enemy, game_state);
	}

}

void carTouched(int x_enemy, int y_enemy){
	/*
	* Launch the enemy car blinking animation.
	* The enemy is considered touch if the difference between its position along x and y with the player car position is closer than half of the sprite dimensions
	* Enemy is updated
	*/
	if ((abs(y_enemy-POS_REDCAR) < SPRITE_HEIGHT/2) && (abs (x_car- x_enemy)< SPRITE_WIDTH/2)){
		if (Get_TimerTicks2() == 0){
			enemy = 50;
			//launch sprite enemy blinking animation
			irqEnable(IRQ_TIMER2);
			//audio effect
			Audio_PlaySoundEX(SFX_ENEMY);
		}
	}
}



void carJump(){
	/*
	* When the position of the car and the sprite enemy along y and along x are both closer than respectively the sprite's height and width
	* The enemy sprite is destroyed and therefore hidden
	* touch is updated
	* a new color is generated for the enemy sprite
	*/
	if (abs(y_subpink-POS_REDCAR) < SPRITE_HEIGHT){
		if (abs (x_car- x_subpink)< SPRITE_WIDTH){
			//position in y is reinitialized in the sub screen
			y_subpink = SCREEN_HEIGHT;
			touch = 100;
			//new palette for the next sprite enemy
			car_pal = rand()%3 + 2;
			//sprite enemy is hidden when touched
			P_Graphics_setCarPink(&oamSub,x_subpink, y_subpink, true, car_pal);
		}
	}
}

void Gameplay_Enemies(){
	/*
		 * Position along x of the enemy defined randomly and adjust with the boundary of the subscreen map
		 * When the enemy sprite arrive at the top of the sub screen it is hidden and the main screen is updated with the given sprite.
		 * It will also be hidden when it will reach the top of the main screen and a new enemy sprite will be generated on the sub screen.
		 */
	//Position of the sprite enemy on the sub screen
	//x randomly generated

	int sgn_x= rand()%3 -1;
	//x adapted to the road width
	if (x_subpink+sgn_x < left_bound_ensub)
		x_subpink++;
	else if (x_subpink+sgn_x > right_bound_ensub )
		x_subpink -=1;
	//sprite enemy displacement across map along x
	else x_subpink= x_subpink+sgn_x;
	//sprite enemy displacement across the map along y
	y_subpink = y_subpink - 1;

	if ((y_subpink <0 || y_subpink > SCREEN_HEIGHT )||( game_state ==0)){
		//position for next sprite enemy (bottom screen after a start)
		//sprite is cut in half for a smoother entrance on the bottom screen
		y_subpink = SCREEN_HEIGHT;
		x_subpink = rand()%(right_bound_ensub-left_bound_ensub) + left_bound_ensub;
		//palette for next sprite enemy
		car_pal = rand()%3 + 2;
		//sprite enemy is hidden from the bottom screen if its position in y is out of the screen dimensions
		P_Graphics_setCarPink(&oamSub,x_subpink, y_subpink, true, car_pal);
	}else{
		//new sprite enemy
		P_Graphics_setCarPink(&oamSub,x_subpink, y_subpink, false, car_pal);
	}
	if (y_subpink <= 0) {
		//initialization of the sprite enemy position and color on the main screen
		y_mainpink = SCREEN_HEIGHT;
		//keep the x position from the sub screen for continuity
		x_mainpink = x_subpink;
		//keep the color from the sub screen
		car_palmain = car_pal;
	}
	if (y_mainpink > 0){
		//sprite enemy appears on main screen
		P_Graphics_setCarPink(&oamMain,x_mainpink, y_mainpink, false, car_palmain);
		y_mainpink -=1;
		//x is generated randomly
		int sgn_x= rand()%3 -1;
		//x position is adapted to the main screen boundary
		if (x_mainpink+sgn_x < left_bound_enmain )
			x_mainpink ++;
		else if (x_mainpink+sgn_x > right_bound_enmain )
			x_mainpink-=1;
		else x_mainpink= x_mainpink+sgn_x;
	} else {
		//sprite enemy is hidden
		P_Graphics_setCarPink(&oamMain,x_mainpink, y_mainpink, true, car_palmain);
	}

}
void Gameplay_RoadBoundaries(int pos, int* left, int* right){
	/*
		 * Different road width conditions
		 * Sprite width taken into account for the right side
		 *
		 */
	if (pos >255 && pos < 304){
		*left = 67;
		*right = 187;
	} else if (pos >176 && pos < 207){
		*left = 67;
		*right = 219;
	} else {
		*left = 81;
		*right = 207;
	}
	*right = *right - SPRITE_WIDTH;
}

int Get_Car_Pos(){return x_car;}
