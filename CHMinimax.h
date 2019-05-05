/*
 * CHMinimax.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Dubi
 */

#ifndef CHMINIMAX_H_
#define CHMINIMAX_H_
#include "ChessGame.h"

/*
 * AI suggest move function, suggesting the move for the computer and placing coords in the given references
 * @params src - current game
 * @params fromRow - pointer to int representing the source row coord to be suggested
 * @params fromCol - pointer to int representing the source col coord to be suggested
 * @params toRow - pointer to int representing the destination row coord to be suggested
 * @params toCol - pointer to int representing the destination col coord to be suggested
 */
void suggestMove(ChessGame* src, int* fromRow, int* fromCol, int* toRow, int* toCol);

/*
 * Minimax function used to compute the best possible move. The function is recursive and uses pruning algorithm
 * Depth of the recursion is determined by the game's difficulty
 * @params src - current game
 * @params depth - current recursion depth
 * @params alpha - alpha parameter of the pruning algorithm
 * @params beta - beta parameter of the pruning algorithm
 */
int minimaxFunction(ChessGame* src, int depth, int alpha, int beta, bool maxPlayer);

#endif /* CHMINIMAX_H_ */
