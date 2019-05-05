/*
 * CHAux.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Dubi
 */

#ifndef CHAUX_H_
#define CHAUX_H_
#include "CHMinimax.h"
#include "CHParser.h"
#include "SPBufferset.h"

/*
 * Handles returned message after game event, print to user if needed
 * @params msg - the returned message
 * @params game - pointer to current chess game
 */
void handleReturnedMessage(CHESS_GAME_MESSAGE msg, ChessGame* game);

/*
 * Set the specified setting of the game
 * @params game - current game
 * @params currCommand - contains the setting needed to be set with the desired value(s)
 */
void settingsActions(ChessGame* game, CHCommand currCommand);

/*
 * Execute the specified action in the game
 * @params game - current game
 * @params currCommand - contains the action needed to be executed with the desired value(s)
 * @return message indicating whether the action was successful, and in case of failure - the reason for it
 */
CHESS_GAME_MESSAGE gameActions(ChessGame* game, CHCommand currCommand);

/*
 * Console mode settings flow - remain in this function to set all the settings until start/quit/load is invoked
 * @params game - current game
 * @return message when one of the start/quit/load options is invoked
 */
CHESS_GAME_MESSAGE gameSettings(ChessGame* game);

/*
 * Console mode game flow - remain in this function until the game is over, or reset/quit is invoked
 * @params game - current game
 * @return message when the game is over or reset/quit is invoked
 */
CHESS_GAME_MESSAGE gamePlayed(ChessGame* game);

/*
 * Save the current game to file
 * @params game - current game
 * @params outFile - full path of file to save the game into
 */
void saveGameToFile(ChessGame* game, char* outFile);

/*
 * Load game from file
 * @params game - current game
 * @params outFile - full path of file to load the game from
 */
void loadGameFromFile(ChessGame* game, char* inFile);

#endif /* CHAUX_H_ */
