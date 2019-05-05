/*
 * CHMovesHistory.h
 *
 *  Created on: Feb 16, 2018
 *      Author: Dubi
 */

#ifndef CHMOVESHISTORY_H_
#define CHMOVESHISTORY_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//bool value indicating if we are in the UI mode (true) or in console mode (false)
bool UIMode;

//Struct representing one move record
typedef struct chess_game_move_t {
	char oldPiece;
	int oldRow;
	int oldCol;
	int newRow;
	int newCol;
} ChessMoveRecord;

//Struct representing chess history
typedef struct chess_game_moves_history_t {
	ChessMoveRecord* movesHistory;
	int maxSize;
	int movesInHistory;
} ChessHistory;

//History message enum
typedef enum chess_list_message_t {
	CHESS_HISTORY_LIST_SUCCESS,
	CHESS_HISTORY_LIST_FAIL,
	CHESS_HISTORY_LIST_INVALID_ARGUMENT,
	CHESS_HISTORY_LIST_FULL,
	CHESS_HISTORY_LIST_EMPTY
} CHESS_HISTORY_LIST_MESSAGE;

/*
 * Create a chess move record
 * @params oldPiece - piece at the source location before move
 * @params oldRow - source row coord
 * @params oldCol - source col coord
 * @params newRow - destination row coord
 * @params newCol - destination col coord
 * @return move record representing a move
 */
ChessMoveRecord createChessMoveRecord(char oldPiece, int oldRow,
		int oldCol, int newRow, int newCol);

/*
 * Create a chess history of the given size
 * @params maxSize - history maximum size
 * @return pointer to chess history
 */
ChessHistory* createChessHistory(int maxSize);

/*
 * Check if chess history contains moves
 * @params chessHistory - current history
 * @return message indicating history state
 */
CHESS_HISTORY_LIST_MESSAGE chessHasHistory(ChessHistory* chessHistory);

/*
 * Add move to chess history, if possible
 * @params chessHistory - current history
 * @params oldPiece - piece at the source location before move
 * @params oldRow - source row coord
 * @params oldCol - source col coord
 * @params newRow - destination row coord
 * @params newCol - destination col coord
 * @return message indicating whether add action was successful
 */
CHESS_HISTORY_LIST_MESSAGE addMoveToChessHistory(ChessHistory* chessHistory, char oldPiece, int oldRow,
		int oldCol, int newRow, int newCol);

/*
 * Add move to chess history at the last place
 * @params chessHistory - current history
 * @params oldPiece - piece at the source location before move
 * @params oldRow - source row coord
 * @params oldCol - source col coord
 * @params newRow - destination row coord
 * @params newCol - destination col coord
 * @return message indicating whether add action was successful
 */
CHESS_HISTORY_LIST_MESSAGE addLastMoveToChessHistory(ChessHistory* chessHistory, char oldPiece, int oldRow,
		int oldCol, int newRow, int newCol);

/*
 * Remove first move record from chess history
 * @params chessHistory - current history
 * @return message indicating whether remove action was successful
 */
CHESS_HISTORY_LIST_MESSAGE removeFirstMoveFromChessHistory(ChessHistory* chessHistory);

/*
 * Remove last move record from chess history
 * @params chessHistory - current history
 * @params loc - move location in history
 * @return move record of the last move
 */
ChessMoveRecord removeLastMoveFromChessHistory(ChessHistory* chessHistory);

/*
 * Get a history move record from chess history at the specified location
 * @params chessHistory - current history
 * @params loc - move location in history
 * @return move record
 */
ChessMoveRecord getMoveFromChessHistory(ChessHistory* chessHistory, int loc);

/*
 * Free chess history memory
 * @params chessHistory - current history
 * @return message indicating whether free action was successful
 */
CHESS_HISTORY_LIST_MESSAGE freeChessHistory(ChessHistory* chessHistory);

/*
 * Make undo chess move in history
 * @params chessHistory - current history
 * @return message indicating whether undo action was successful
 */
CHESS_HISTORY_LIST_MESSAGE undoChessMove(ChessHistory* chessHistory);

/*
 * Add move record to first place in history
 * @params chessHistory - current history
 * @params firstRec - first record to be inserted
 * @return message indicating whether add action was successful
 */
CHESS_HISTORY_LIST_MESSAGE addFirstRecordChessHistory(ChessHistory* chessHistory, ChessMoveRecord firstRec);

#endif /* CHMOVESHISTORY_H_ */
