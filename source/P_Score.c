/*
 * P_Score.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Score.h"
#include "numbers.h"
#include <stdio.h>
#include <fat.h>

int score = 0, max_score = 0;

void updateScore(int speed, int touch, int enemy, int _game_state)
{
	/*
	 * Depending on the speed increase the score
	 *  1 point - 1 speed
	 *  2 points - 2 speed
	 *  3 points - 3 speed
	 *  4 points - 4 speed
	 *  5 points - 5 speed
	 *
	 *	If the enemy is touched without jumping, the enemy score is removed
	 *	If the enemy is touched while jumping, the touch score is added
	 */
	switch(speed)
	{
	case 1: score+=1; break;
	case 2: score+=2; break;
	case 3: score+=3; break;
	case 4: score+=4; break;
	case 5: score+=5; break;
	}
	if (touch > 0) score = score + touch;
	if (enemy > 0) score = score - enemy;
	if (score < 0) score = 0; // Avoid negative score
	//Display the score
	displayScore(_game_state);

	//Update highest score
	if(score > max_score)
	{
		max_score = score;
		displayMaxScore();
	}
}


/*
 * This function displays the score counter on the left of the
 * screen using the palette 9 (white color preloaded)
 *
 * The map (10) is modified accordingly to the points stored in the
 * variable store
 */

void displayScore(int _game_state)
{

	int j,i, number;
	//i, digit to display
	for(i = 5; i>0; i--)
	{
		//calculate the power of i-1 in j
		j = i-1; number = 1;
		while(j--)number = number*10;
		//Obtain the number to render
		number = score / number;
		number = number % 10;
		//Render the number
		if (_game_state){
			BG_MAP_RAM(10)[32 +6-i] = numbersMap[(number)] | TILE_PALETTE(9);
		}else {
			BG_MAP_RAM(10)[32 +6-i] = 0;
		}
	}
}
/*
 * This function displays the highest score obtained in previous games
 * on the center part of the screen at the start menu. It uses the palette 8
 * (with orange color preloaded)
 */
void displayMaxScore_Start(int _game_state)
{
	readMaxScore();
	int i, j, number;
	for(i = 5; i>0; i--)
	{
		j = i-1; number = 1;
		while(j--)number = number*10;
		number = max_score / number;
		number = number % 10;
		if (_game_state){
			BG_MAP_RAM(10)[(16)*32 +21-i] = 0;
		} else {
			BG_MAP_RAM(10)[(16)*32 +21-i] = numbersMap[(number)] | TILE_PALETTE(8);
		}
	}
}


/*
 * This function reads the highest score obtained in previous games and
 * stored in a text file called /BumpNJumprecord.txt. The read value is assigned
 * to the variable max_score
 */
void readMaxScore()
{
	//Open the file in read mode
	FILE* file = fopen("/BumpNJumprecord.txt","r");
	if(file != NULL)
	{
		//Read the value and put it into the variable max_score
		fscanf(file,"%i\n",&max_score);
		// close the file
		fclose(file);
	}
}

/*
 * This function writes the value of the variable max_score
 * into the text file /BumpNJumprecord
 */
void writeMaxScore()
{
	//Open the file in write mode to overwrite
	FILE* file = fopen("/BumpNJumprecord.txt","w+");
	if(file != NULL)
	{
		//Print the value in the file
		fprintf(file,"%i\n",max_score);
		//Close the file
		fclose(file);
	}
	score = 0;
}

/*
 * This function displays the highest score obtained in previous games
 * on the left part of top the screen. It uses the palette 8 (with orange color
 * preloaded)
 */
void displayMaxScore()
{

	int i, j, number;
	for(i = 5; i>0; i--)
	{
		j = i-1; number = 1;
		while(j--)number = number*10;
		number = max_score / number;
		number = number % 10;
		BG_MAP_RAM(10)[3*32 +6-i] = numbersMap[(number)] | TILE_PALETTE(8);
	}
}
