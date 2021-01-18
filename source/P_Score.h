/*
 * P_Score.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */


#include <nds.h>

/*
 * \brief Update the score of the player.
 *
 * @param speed			:	speed increase the score of the player.
 * @param touch			:	points gained by the player if they touch an enemy.
 * @param enemy			:	point lost by the player if an enemy touch them.
 * @param _game_state	:	Integer that correspond to the game state. If it's
 * 							equal to one the game starts if it's equal to zero,
 * 							we are on the start menu
 */
void updateScore(int speed, int touch, int enemy, int _game_state);
/*
 * This function displays the score counter on the left of the
 * screen using the TILE_PALETTE 9 (white color preloaded)
 * The map (10) is modified accordingly to the points stored in the
 * variable store
 *
 * @param _game_state	:	Integer that correspond to the game state. If it's
 * 							equal to one the game starts if it's equal to zero,
 * 							we are on the start menu
 */
void displayScore(int _game_state);
/*
 * \brief Display the max score on the start menu on the main screen
 * The max score is erased from the center of the main screen when the game starts.
 *
 * This function displays the highest score obtained in previous games
 * on the center part of the screen at the start menu. It uses the TILE_PALETTE
 * 8 (with orange color preloaded)
 *
 * @param _game_state	:	Integer that correspond to the game state. If it's
 * 							equal to one the game starts if it's equal to zero,
 * 							we are on the start menu
 */
void displayMaxScore_Start(int _game_state);

/*
 * \brief Read the max score from a secondary storage
 * This function reads the highest score obtained in previous games and
 * stored in a text file called /BumpNJumprecord.txt. The read value is assigned
 * to the variable max_score.
 *
 * This function does not receive any input parameter.
 */
void readMaxScore();

/*
 * \brief Write the max score in a secondary storage
 * This function writes the value of the variable max_score
 * into the text file /BumpNJumprecord.txt.
 *
 * This function does not receive any input parameter.
 */
void writeMaxScore();
/*
 * \brief Display the max score during the game.
 *
 * This function displays the highest score obtained in previous games
 * on the left part of top the screen. It uses the TILE_PALETTE 8 (with orange
 * color preloaded).
 *
 * This function does not receive any input parameter.
 */
void displayMaxScore();
