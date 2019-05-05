/*
 * ChessGame.h
 *
 *  Created on: Feb 15, 2018
 *      Author: Dubi
 */

#ifndef CHESSGAME_H_
#define CHESSGAME_H_
#include "CHMovesHistory.h"
#include <stdbool.h>
#include <stdio.h>
//Definitions
#define CHESS_GAME_MAX_HISTORY 3
#define CHESS_GAME_N_ROWS 8
#define CHESS_GAME_N_COLUMNS 8
#define CHESS_GAME_EMPTY_ENTRY '_'

//Struct representing a chess game
typedef struct chess_game_t {
	char gameBoard[CHESS_GAME_N_ROWS][CHESS_GAME_N_COLUMNS];
	ChessHistory* history;
	int userColor;
	int difficulty;
	int currentPlayer;
	int numOfPlayers;
} ChessGame;

/**
 * Type used for returning error codes from game functions
 */
typedef enum chess_game_message_t {
	CHESS_GAME_INVALID_MOVE,
	CHESS_GAME_INVALID_ARGUMENT,
	CHESS_GAME_INVALID_PIECE,
	CHESS_GAME_INVALID_POSITION,
	CHESS_GAME_WILL_CAUSE_CHECK,
	CHESS_GAME_CHECK,
	CHESS_GAME_DRAW,
	CHESS_GAME_CHECKMATE,
	CHESS_GAME_STILL_CHECK,
	CHESS_GAME_NO_HISTORY,
	CHESS_GAME_SUCCESS,
	CHESS_GAME_RESTARTING,
	CHESS_GAME_STARTING,
	CHESS_GAME_OTHER
//You may add any message you like
} CHESS_GAME_MESSAGE;

/*
 * Creates a new ChessGame instance
 * @return - pointer to a new chess game instance
 */
ChessGame* ChessGameCreate();

/*
 * Destroy the given ChessGame instance and release all memory
 * @params src - game instance to destroy
 */
void ChessGameDestroy(ChessGame* src);

/*
 * Check if the given coordinate has a valid piece
 * @params src - current game
 * @params row - row value
 * @params col - col value
 * @return CHESS_GAME_INVALID_ARGUMENT - if wrong coords, CHESS_GAME_INVALID_PIECE - if coords don't contain a piece
 * 			CHESS_GAME_SUCCESS - valid coords
 */
CHESS_GAME_MESSAGE checkBasicCoord(ChessGame* src, int row, int col);

/*
 * Check if a given location is threatened by opponent piece
 * @params src - current game
 * @params targetRow - row coord
 * @params targetCol - col coord
 * @return true - if location is threatened, otherwise false
 */
bool isLocationThreatened(ChessGame* src, int targetRow, int targetCol);

/*
 * Print current game's board
 * @params src - current game
 * @return CHESS_GAME_SUCCESS if src is not null and printing executed
 */
CHESS_GAME_MESSAGE ChessGamePrintBoard(ChessGame* src);

/*
 * Execute a move command for the current player according to the given coords
 * @params src - current game
 * @params fromRow - source row coord
 * @params fromChar - source col coord
 * @params toRow - destination row coord
 * @params toChar - destination col coord
 * @return - message whether the move was successful or if not, the cause of failure
 */
CHESS_GAME_MESSAGE ChessGameSetMove(ChessGame* src,
		int fromRow, char fromChar, int toRow, char toChar);

/*
 * Check if coords for move are valid, and a move according to the given coords.
 * @params src - current game
 * @params fromRow - source row coord
 * @params fromChar - source col coord
 * @params toRow - destination row coord
 * @params toChar - destination col coord
 * @return - message whether the move was successful or if not, the cause of failure
 */
CHESS_GAME_MESSAGE moveChecksAndExec(ChessGame* src,
		int fromRow, char fromChar, int toRow, char toChar);

/*
 * Check if there is a Check or Checkmate state for the current player
 * @params src - current game
 * @return -message indicating wether there is a CheckqCheckmate state
 */
CHESS_GAME_MESSAGE afterMoveChecks(ChessGame* src);

/*
 * Check if a move is a valid chess move
 * @params src - current game
 * @params fromRow - row of source location
 * @params fromCol - col of source location
 * @params fromRow - row of target location
 * @params fromCol - col of target location
 * @return true - if the given move is a valid chess move, otherwise false
 */
bool ChessCheckPieceMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol);

/*
 * Check if a pawn move is a valid chess move
 * @params src - current game
 * @params fromRow - row of source location
 * @params fromCol - col of source location
 * @params fromRow - row of target location
 * @params fromCol - col of target location
 * @return true - if the given pawn move is a valid chess move, otherwise false
 */
bool ChessCheckPawnMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol);

/*
 * Check if a bishop move is a valid chess move
 * @params src - current game
 * @params fromRow - row of source location
 * @params fromCol - col of source location
 * @params fromRow - row of target location
 * @params fromCol - col of target location
 * @return true - if the given bishop move is a valid chess move, otherwise false
 */
bool ChessCheckBishopMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol);

/*
 * Check if a rook move is a valid chess move
 * @params src - current game
 * @params fromRow - row of source location
 * @params fromCol - col of source location
 * @params fromRow - row of target location
 * @params fromCol - col of target location
 * @return true - if the given rook move is a valid chess move, otherwise false
 */
bool ChessCheckRookMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol);

/*
 * Check if a knight move is a valid chess move
 * @params src - current game
 * @params fromRow - row of source location
 * @params fromCol - col of source location
 * @params fromRow - row of target location
 * @params fromCol - col of target location
 * @return true - if the given pawn move is a valid chess move, otherwise false
 */
bool ChessCheckKnightMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol);

/*
 * Check if a queen move is a valid chess move
 * @params src - current game
 * @params fromRow - row of source location
 * @params fromCol - col of source location
 * @params fromRow - row of target location
 * @params fromCol - col of target location
 * @return true - if the given queen move is a valid chess move, otherwise false
 */
bool ChessCheckQueenMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol);
/*
 * Check if a king move is a valid chess move
 * @params src - current game
 * @params fromRow - row of source location
 * @params fromCol - col of source location
 * @params fromRow - row of target location
 * @params fromCol - col of target location
 * @return true - if the given king move is a valid chess move, otherwise false
 */
bool ChessCheckKingMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol);

/*
 * Execute undo move invoked by player. Undo two moves, except if the history contains no moves (or only
 * one) - in this case undo 0 (1) moves
 */
CHESS_GAME_MESSAGE undoChessMoves(ChessGame* src);

/*
 * Undo one chess move
 * @params src - current game
 * @params print - indicate whether to print the undo move message
 * @return proper message according to undo move result
 */
CHESS_GAME_MESSAGE undoSingleChessMove(ChessGame* src, bool print);

/*
 * Change the current player of the game
 * @params src - current game
 * @return CHESS_GAME_SUCCESS on successful player change
 */
CHESS_GAME_MESSAGE changePlayerChess(ChessGame* src);
/*
 * Check if both pieces are the same 'color'
 * @params first - char representing the first piece
 * @params second - char representing the second piece
 * @return true - if the two pieces are the same 'color', otherwise false
 */
bool sameTeam(char first, char second);

/*
 * Check whether there is a check state, i.e. the current player's king is threatened
 * @params src - current game
 * @return true - if the current player's king is threatened. Otherwise - false
 */
bool isCheckChess(ChessGame* src);

/*
 * Check whether there is a safe move, i.e. a move after which the king is not threatened
 * @params src - current game
 * @return true - if there is a safe move. Otherwise - false
 */
bool hasSafeMoveChess(ChessGame* src);

/*
 * Check whether there is a safe move from a given location, i.e. a move after which the king is not threatened
 * @params src - current game
 * @params fromRow - row coord of the source location
 * @params fromCol - col coord of the source location
 * @return true - if there is a safe move from the given location. Otherwise - false
 */
bool hasSafeMoveFromLocChess(ChessGame* src, int fromRow, int fromCol);

/*
 * Check whether the specified move is safe, i.e. king is not threatened after the move is made
 * @params src - current game
 * @params fromRow - row coord of the source location
 * @params fromCol - col coord of the source location
 * @params toRow - row coord of the destination location
 * @params toCol - col coord of the destination location
 * @return true - if the move is safe. Otherwise - false
 */
bool isSafeMoveChess(ChessGame* src, int fromRow, int fromCol, int toRow, int toCol);

/*
 * Get all possible moves of a piece from a given location
 * @params src - current game
 * @params fromRow - row coordinate of the piece
 * @params fromChar - col coordinate of the piece, represented by character
 */
CHESS_GAME_MESSAGE getMoves(ChessGame* src, int fromRow, char fromChar);

/*
 * Scoring Function - Calculate the score of the current board state
 * @params src - current game
 * @return - integer representing the current board score
 */
int boardScore(ChessGame* src);

/*
 * Calculate the score of the given piece for the Scoring Function
 * @params peice - char representing the piece
 * @return - integer representing the piece value
 */
int pieceValue(char piece);

/*
 * Back up first record in game history in order to restore it if undo move is needed
 * @params src - current game
 * @return - first record in game history, representing a piece move
 */
ChessMoveRecord backUpfirstRecord(ChessGame* src);

/*
 * Get user color setting
 * @params src - current game
 * @return - string representing the user color
 */
char* getUserColor(ChessGame* src);

/*
 * Get player color string
 * @params src - current game
 * @params currentPlayer - determine whether the color of the current player is needed, or the oppponent's color
 * @return - string representing the color of the specified player
 */
char* getPlayerColor(ChessGame* src, bool currentPlayer);

/*
 * Get difficulty setting
 * @params src - current game
 * @return - string representing the difficulty
 */
char* getDifficultyLevel(ChessGame* src);

/*
 * Get the string representation of a given piece
 * @params src - current game
 * @params row - row coord of the given piece
 * @params col - col coord of the given piece
 * @return - string representation of the piece
 */
char* getPieceName(ChessGame* src, int row, int col);

/*
 * Makes computer move (if the game is 1 player mode)
 * @params game - current game
 * @return proper message after making computer move
 */
CHESS_GAME_MESSAGE makeComputerMove(ChessGame* game);

/*
 * Print the given string if the game is in console mode
 * @params currSTR - string to print
 */
void printMSG(const char* currSTR);

#endif /* CHESSGAME_H_ */
