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

void updateScore(int speed, int touch, int enemy)
{
	/*
	 * Depending on the lines increase the score
	 *  1 point - one single line
	 *  4 points - 2 lines
	 *  8 points - 3 lines
	 *  10 points - 4 lines
	 */
	switch(speed)
	{
	case 1: score+=1; break;
	case 2: score+=2; break;
	case 3: score+=3; break;
	case 4: score+=4; break;
	case 5: score+=5; break;
	}
	if (touch > 0) score = score+touch;
	if (enemy > 0) score = score -enemy;
	if (score < 0) score = 0;
	//Display the score
	displayScore();

	//Update highest score
	if(score > max_score)
	{
		max_score = score;
		displayMaxScore();
	}
}


/*
 * This function displays the score counter on the right of the
 * screen (looking sidewise) using the palette 9 (green color preloaded)
 *
 * The map (24) is modified accordingly to the points stored in the
 * variable store
 */

void displayScore()
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
		BG_MAP_RAM(10)[32 +6-i] = numbersMap[(number)] | TILE_PALETTE(9);
	}
}

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
 * stored in a text file called /Tetrisrecord.txt. The read value is assigned
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
 * into the text file /tetrisrecord
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
 * on the left part of bottom the screen (looking sideways). It uses the
 * palette 8 (with red color preloaded)
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
