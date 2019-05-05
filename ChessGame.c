/*
 * ChessGame.c
 *
 *  Created on: Feb 15, 2018
 *      Author: Dubi
 */
#include "ChessGame.h"
#include <stdlib.h>
#include <math.h>
#include "SPBufferset.h"

ChessGame* ChessGameCreate()
{
	ChessGame *newGame;
	newGame = (ChessGame*)malloc(sizeof(ChessGame));
	if (newGame == NULL)//If memory allocation failed
	{
		return NULL;
	}
	//set history
	newGame->history = createChessHistory(CHESS_GAME_MAX_HISTORY);

	//set game board - initialized to empty entries
	(newGame->gameBoard)[0][0] = 'r';
	(newGame->gameBoard)[0][1] = 'n';
	(newGame->gameBoard)[0][2] = 'b';
	(newGame->gameBoard)[0][3] = 'q';
	(newGame->gameBoard)[0][4] = 'k';
	(newGame->gameBoard)[0][5] = 'b';
	(newGame->gameBoard)[0][6] = 'n';
	(newGame->gameBoard)[0][7] = 'r';

	(newGame->gameBoard)[7][0] = 'R';
	(newGame->gameBoard)[7][1] = 'N';
	(newGame->gameBoard)[7][2] = 'B';
	(newGame->gameBoard)[7][3] = 'Q';
	(newGame->gameBoard)[7][4] = 'K';
	(newGame->gameBoard)[7][5] = 'B';
	(newGame->gameBoard)[7][6] = 'N';
	(newGame->gameBoard)[7][7] = 'R';
	for (int j=0; j<CHESS_GAME_N_ROWS; j++)
	{
		(newGame->gameBoard)[1][j] = 'm';
	}
	for(int i=2; i<CHESS_GAME_N_ROWS - 2; i++)
	{
		for (int j=0; j<CHESS_GAME_N_ROWS; j++)
		{
			(newGame->gameBoard)[i][j] = CHESS_GAME_EMPTY_ENTRY;
		}
	}
	for (int j=0; j<CHESS_GAME_N_ROWS; j++)
	{
		(newGame->gameBoard)[6][j] = 'M';
	}
	newGame->difficulty = 2;
	newGame->userColor = 1;
	newGame->currentPlayer = 1;
	newGame->numOfPlayers = 1;
	return newGame;
}

CHESS_GAME_MESSAGE checkBasicCoord(ChessGame* src, int row, int col)
{
	if (row < 0 || row > 7 || col < 0 || col > 7)
	{
		return CHESS_GAME_INVALID_ARGUMENT;
	}
	if (row < 0 || row > 7 || col < 0 || col > 7)
	{
		return CHESS_GAME_INVALID_ARGUMENT;
	}
	char curPiece = src->gameBoard[row][col];
	if (curPiece == '_')
	{
		return CHESS_GAME_INVALID_PIECE;
	}
	return CHESS_GAME_SUCCESS;
}

CHESS_GAME_MESSAGE ChessGameSetMove(ChessGame* src,
		int fromRow, char fromChar, int toRow, char toChar)
{
	CHESS_GAME_MESSAGE msg = moveChecksAndExec(src, fromRow, fromChar, toRow, toChar);
	if (msg != CHESS_GAME_SUCCESS)
		return msg;
	else
		return afterMoveChecks(src);
}
CHESS_GAME_MESSAGE moveChecksAndExec(ChessGame* src,
		int fromRow, char fromChar, int toRow, char toChar)
{
	int toCol = toChar - 'A';
	int fromCol = fromChar - 'A';
	fromRow = fromRow -1;
	toRow = toRow - 1;
	bool check = false;
	CHESS_GAME_MESSAGE basicCheck = checkBasicCoord(src, fromRow, fromCol);
	if (basicCheck != CHESS_GAME_SUCCESS)
	{
		return basicCheck;
	}
	char curPiece = src->gameBoard[fromRow][fromCol];
	if (src->currentPlayer == 1 && (curPiece < 'a' || curPiece > 'z'))
	{
		return CHESS_GAME_INVALID_PIECE;
	}
	if (src->currentPlayer == 0 && (curPiece < 'A' || curPiece > 'Z'))
	{
		return CHESS_GAME_INVALID_PIECE;
	}
	if (!ChessCheckPieceMove(src, fromRow, fromCol, toRow, toCol)){
		return CHESS_GAME_INVALID_MOVE;
	}
	check = isCheckChess(src);
	char backUpPiece = src->gameBoard[toRow][toCol];
	src->gameBoard[fromRow][fromCol] = '_';
	src->gameBoard[toRow][toCol] = curPiece;
	if (isCheckChess(src))
	{
		src->gameBoard[fromRow][fromCol] = src->gameBoard[toRow][toCol];
		src->gameBoard[toRow][toCol] = backUpPiece;
		if (check)
			return CHESS_GAME_STILL_CHECK;
		else
			return CHESS_GAME_WILL_CAUSE_CHECK;
	}
	addMoveToChessHistory(src->history, backUpPiece, fromRow, fromCol, toRow, toCol);
	changePlayerChess(src);
	return CHESS_GAME_SUCCESS;
}
CHESS_GAME_MESSAGE afterMoveChecks(ChessGame* src)
{
	if (isCheckChess(src)){
		if (!hasSafeMoveChess(src)){
			return CHESS_GAME_CHECKMATE;
		}
		else{
			return CHESS_GAME_CHECK;
		}
	}
	if (!hasSafeMoveChess(src))
	{
		return CHESS_GAME_DRAW;
	}
	return CHESS_GAME_SUCCESS;
}
bool ChessCheckPieceMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol)
{

	char curPiece = src->gameBoard[fromRow][fromCol];
	if (abs(toRow - fromRow) == 0 && abs(toCol - fromCol) == 0)
	{
		return false;
	}
	if (src->gameBoard[toRow][toCol] != '_')
	{
		if (sameTeam(src->gameBoard[toRow][toCol], curPiece))
		{
			return false;
		}
	}
	switch (curPiece){
		case 'm':
		case 'M':
			return ChessCheckPawnMove(src, fromRow, fromCol, toRow, toCol);
			break;
		case 'r':
		case 'R':
			return ChessCheckRookMove(src, fromRow, fromCol, toRow, toCol);
			break;
		case 'n':
		case 'N':
			return ChessCheckKnightMove(src, fromRow, fromCol, toRow, toCol);
			break;
		case 'b':
		case 'B':
			return ChessCheckBishopMove(src, fromRow, fromCol, toRow, toCol);
			break;
		case 'q':
		case 'Q':
			return ChessCheckQueenMove(src, fromRow, fromCol, toRow, toCol);
			break;
		case 'k':
		case 'K':
			return ChessCheckKingMove(src, fromRow, fromCol, toRow, toCol);
			break;
		default:
			return false;
	}

}


bool ChessCheckPawnMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol)
{
	int moveVert = abs(toRow - fromRow);
	int moveDiag = abs(toCol - fromCol);
	if (src->gameBoard[fromRow][fromCol] == 'm')
	{
		if (toRow <= fromRow || moveDiag > 1)
			{
				return false;
			}
	}
	else
	{
		if (toRow >= fromRow || moveDiag > 1)
		{
			return false;
		}
	}
	if (moveVert == 1 && moveDiag == 0)
	{
		if (src->gameBoard[toRow][toCol] != '_')
		{
			return false;
		}
	}
	else if (moveVert == 1 && moveDiag == 1)
	{
		if (src->gameBoard[toRow][toCol] == '_')
		{
			return false;
		}
	}
	else if (moveVert == 2)
	{
		if ((fromRow!= 1 && src->gameBoard[fromRow][fromCol] == 'm') ||
				(fromRow!= 6 && src->gameBoard[fromRow][fromCol] == 'M')){
			return false;
		}
		if (moveDiag != 0){
			return false;
		}
		if (src->gameBoard[toRow][toCol] != '_'){
			return false;
		}
		if (src->gameBoard[fromRow][fromCol] == 'm')
		{
			if (src->gameBoard[fromRow + 1][fromCol] != '_')
			{
				return false;
			}
		}
		else
		{
			if (src->gameBoard[fromRow - 1][fromCol] != '_')
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool ChessCheckBishopMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol)
{
	int moveVert = abs(toRow - fromRow);
	int moveDiag = abs(toCol - fromCol);
	if (moveVert != moveDiag)
	{
		return false;
	}
	if (moveVert == 0)
	{
		return false;
	}
	if (toRow > fromRow && toCol > fromCol)
	{
		for (int i = 1; i < moveVert; i++)
			{
				if (src->gameBoard[fromRow + i][fromCol + i] != '_'){
					return false;
				}
			}
	}
	else if (toRow > fromRow && toCol < fromCol)
	{
		for (int i = 1; i < moveVert; i++)
		{
			if (src->gameBoard[fromRow + i][fromCol - i] != '_')
			{
				return false;
			}
		}
	}
	else if (toRow < fromRow && toCol > fromCol)
	{
		for (int i = 1; i < moveVert; i++)
		{
			if (src->gameBoard[fromRow - i][fromCol + i] != '_')
			{
				return false;
			}
		}
	}
	else if (toRow < fromRow && toCol < fromCol)
	{
		for (int i = 1; i < moveVert; i++)
		{
			if (src->gameBoard[fromRow - i][fromCol - i] != '_')
			{
				return false;
			}
		}
	}
	return true;
}

bool ChessCheckRookMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol)
{
	int moveVert = abs(toRow - fromRow);
	int moveDiag = abs(toCol - fromCol);
	if (moveVert != 0 && moveDiag != 0){
		return false;
	}
	if (toRow > fromRow)
	{
		for (int i = 1; i < moveVert; i++)
			{
				if (src->gameBoard[fromRow + i][fromCol] != '_'){
					return false;
				}
			}
	}
	else if (toRow < fromRow)
	{
		for (int i = 1; i < moveVert; i++)
		{
			if (src->gameBoard[fromRow - i][fromCol] != '_')
			{
				return false;
			}
		}
	}
	else if (toCol > fromCol)
	{
		for (int i = 1; i < moveDiag; i++)
		{
			if (src->gameBoard[fromRow][fromCol + i] != '_')
			{
				return false;
			}
		}
	}
	else if (toCol < fromCol)
	{

		for (int i = 1; i < moveDiag; i++)
		{
			if (src->gameBoard[fromRow][fromCol - i] != '_')
			{
				return false;
			}
		}
	}
	return true;
}

bool ChessCheckKnightMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol)
{
	src->userColor = (src->userColor + 2) % 2;
	if ((abs(toRow - fromRow) == 2 && abs(toCol - fromCol) == 1)
			|| (abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 2) )
	{
		return true;
	}
	return false;
}

bool ChessCheckQueenMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol)
{
	if (ChessCheckRookMove(src, fromRow, fromCol, toRow, toCol) ||
			ChessCheckBishopMove(src, fromRow, fromCol, toRow, toCol)){
		return true;
	}
	return false;
}

bool ChessCheckKingMove(ChessGame* src,
		int fromRow, int fromCol, int toRow, int toCol)
{
	src->userColor = (src->userColor + 2) % 2;
	if (abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 1){
		return true;
	}
	if (abs(toRow - fromRow) == 0 && abs(toCol - fromCol) == 1){
		return true;
	}
	if (abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 0){
		return true;
	}
	return false;
}

void ChessGameDestroy(ChessGame* src)
{
	if (!src)
	{
		return;
	}
	freeChessHistory(src->history);
	free(src);
}

CHESS_GAME_MESSAGE ChessGamePrintBoard(ChessGame* src)
{
	extern bool UIMode;
	if (!src)
	{
		return CHESS_GAME_INVALID_ARGUMENT;
	}
	if (!UIMode)
	{
	//Print the game board itself
		for (int i = CHESS_GAME_N_ROWS -1; i >= 0 ; i--)
		{
			printf("%d| ", i+1);
			for (int j=0; j<CHESS_GAME_N_ROWS; j++)
			{
				printf("%c ", src->gameBoard[i][j]);
			}
			printf("|\n");
		}

		printf ("  ");
		//Print the ---
		for (int i=0; i<17; i++)
		{
			printf ("-");
		}
		printf ("\n");
		//Print the nums
		printf("   ");
		printf("%c", 'A');
		for (int i=1; i<CHESS_GAME_N_COLUMNS; i++)
		{
			printf(" %c", 'A' + i);
		}
		printf("\n");
	}
	return CHESS_GAME_SUCCESS;
}

CHESS_GAME_MESSAGE changePlayerChess(ChessGame* src)
{
	if (src == NULL)
	{
		return CHESS_GAME_INVALID_ARGUMENT;
	}
	src->currentPlayer = (src->currentPlayer + 1) % 2;
	return CHESS_GAME_SUCCESS;
}

CHESS_GAME_MESSAGE undoChessMoves(ChessGame* src)
{
	if (src == NULL)
	{
		return CHESS_GAME_INVALID_ARGUMENT;
	}
	if (chessHasHistory(src->history) == CHESS_HISTORY_LIST_EMPTY)
	{
		return CHESS_GAME_NO_HISTORY;
	}
	undoSingleChessMove(src, true);
	if (src->history->movesInHistory >= 1)
	{
		undoSingleChessMove(src, true);
	}
	else if (src->numOfPlayers == 1)
	{
		makeComputerMove(src);
	}
	ChessGamePrintBoard(src);
	return CHESS_GAME_SUCCESS;
}

CHESS_GAME_MESSAGE undoSingleChessMove(ChessGame* src, bool print)
{
	extern bool UIMode;
	if (src == NULL)
	{
		return CHESS_GAME_INVALID_ARGUMENT;
	}
	if (chessHasHistory(src->history) == CHESS_HISTORY_LIST_EMPTY)
	{
		return CHESS_GAME_NO_HISTORY;
	}
	ChessMoveRecord lastRecord = removeLastMoveFromChessHistory(src->history);
	src->gameBoard[lastRecord.oldRow][lastRecord.oldCol] = src->gameBoard[lastRecord.newRow][lastRecord.newCol];
	src->gameBoard[lastRecord.newRow][lastRecord.newCol] = lastRecord.oldPiece;
	changePlayerChess(src);

	if (print)
	{
		char msg[100];
		sprintf(msg, "Undo move for %s player: <%d,%c> -> <%d,%c>\n", getPlayerColor(src, true), lastRecord.oldRow + 1, lastRecord.oldCol + 'A',
						lastRecord.newRow + 1, lastRecord.newCol + 'A');
		printMSG(msg);
	}
	return CHESS_GAME_SUCCESS;
}

bool isCheckChess(ChessGame* src)
{
	bool kingFound = false;
	int kingRow;
	int kingCol;
	for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
	{
		if (kingFound){
			break;
		}
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			if ((src->currentPlayer == 1 && src->gameBoard[i][j] == 'k') ||
					(src->currentPlayer == 0 && src->gameBoard[i][j] == 'K')){
				kingRow = i;
				kingCol = j;
				kingFound = true;
				break;
			}
		}
	}

	bool threatKing = isLocationThreatened(src, kingRow, kingCol);
	return threatKing;
}
bool isLocationThreatened(ChessGame* src, int targetRow, int targetCol)
{
	bool threat = false;
	char targetPiece = src->gameBoard[targetRow][targetCol];

	for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
	{
		if (threat){
			break;
		}
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			if (src->gameBoard[i][j] == CHESS_GAME_EMPTY_ENTRY)
			{
				continue;
			}
			else if (sameTeam(src->gameBoard[i][j], targetPiece))
			{
				continue;
			}
			if (ChessCheckPieceMove(src, i, j, targetRow, targetCol))
			{
				if ((src->gameBoard[i][j] == 'm' || src->gameBoard[i][j] == 'M') && targetCol == j)
				{
					continue;
				}
				threat = true;
				break;
			}
		}
	}
	return threat;
}

bool hasSafeMoveChess(ChessGame* src)
{
	bool hasSafeMove = false;
	for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
	{
		if (hasSafeMove){
			break;
		}
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			if (src->gameBoard[i][j] == CHESS_GAME_EMPTY_ENTRY)
			{
				continue;
			}
			else if (src->gameBoard[i][j] > 'A' && src->gameBoard[i][j] < 'Z' && src->currentPlayer == 1)
			{
				continue;
			}
			else if (src->gameBoard[i][j] > 'a' && src->gameBoard[i][j] < 'z' && src->currentPlayer == 0)
			{
				continue;
			}
			if (hasSafeMoveFromLocChess(src, i, j))
			{
				hasSafeMove = true;
				break;
			}
		}
	}
	return hasSafeMove;
}

ChessMoveRecord backUpfirstRecord(ChessGame* src)
{
	ChessMoveRecord backUprec;
	if (chessHasHistory(src->history) == CHESS_HISTORY_LIST_FULL){
		backUprec = src->history->movesHistory[0];
	}
	return backUprec;
}

bool hasSafeMoveFromLocChess(ChessGame* src, int fromRow, int fromCol)
{
	bool safeMove = false;
	for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
	{
		if (safeMove){
			break;
		}
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			if (isSafeMoveChess(src, fromRow, fromCol, i, j))
			{
				safeMove = true;
				break;
			}
		}
	}
	return safeMove;
}

bool isSafeMoveChess(ChessGame* src, int fromRow, int fromCol, int toRow, int toCol)
{
	bool fullHist = false;
	if (chessHasHistory(src->history) == CHESS_HISTORY_LIST_FULL){
		fullHist = true;
	}
	ChessMoveRecord backUpRec = backUpfirstRecord(src);
	CHESS_GAME_MESSAGE msg = moveChecksAndExec(src, fromRow + 1, fromCol + 'A', toRow + 1, toCol + 'A');
	if (msg == CHESS_GAME_SUCCESS)
	{
		undoSingleChessMove(src, false);
		if (fullHist){
			addFirstRecordChessHistory(src->history, backUpRec);
		}
		return true;
	}
	return false;
}

bool sameTeam(char first, char second)
{
	if ((first < 'z' && first > 'a' && second < 'z' && second > 'a') ||
			(first < 'Z' && first > 'A' && second < 'Z' && second > 'A'))
	{
		return true;
	}
	return false;
}

CHESS_GAME_MESSAGE getMoves(ChessGame* src, int fromRow, char fromChar)
{
	//SP_BUFF_SET();
	extern bool UIMode;
	if (src == NULL)
		return CHESS_GAME_INVALID_MOVE;
	int fromCol = fromChar - 'A';
	fromRow = fromRow -1;
	CHESS_GAME_MESSAGE basicCheck = checkBasicCoord(src, fromRow, fromCol);
	if (basicCheck == CHESS_GAME_INVALID_ARGUMENT)
	{
		return CHESS_GAME_INVALID_ARGUMENT;
	}
	else if (basicCheck == CHESS_GAME_INVALID_PIECE)
	{
		return CHESS_GAME_INVALID_PIECE;
	}
	for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
	{
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			if (ChessCheckPieceMove(src, fromRow, fromCol, i, j))
			{
				if (!isSafeMoveChess(src, fromRow, fromCol, i, j))
					continue;
				char backUpPiece = src->gameBoard[i][j];
				src->gameBoard[i][j] = src->gameBoard[fromRow][fromCol];
				src->gameBoard[fromRow][fromCol] = '_';
				if (isLocationThreatened(src, i, j))
				{
					if (backUpPiece != '_')
					{
						if (!UIMode)
							printf("%d,%c*^\n", i + 1, j + 'A');
					}
					else
					{
						if (!UIMode)
							printf("%d,%c*\n", i + 1, j + 'A');
					}
				}
				else
				{
					if (backUpPiece != '_')
					{
						if (!UIMode)
							printf("%d,%c^\n", i + 1, j + 'A');
					}
					else
					{
						if (!UIMode)
							printf("%d,%c\n", i + 1, j + 'A');
					}
				}
				src->gameBoard[fromRow][fromCol] = src->gameBoard[i][j];
				src->gameBoard[i][j] = backUpPiece;
			}
		}
	}
	return CHESS_GAME_SUCCESS;
}

int boardScore(ChessGame* src)
{
	int totalScore = 0;
	for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
	{
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			if (src->gameBoard[i][j] == CHESS_GAME_EMPTY_ENTRY)
			{
				continue;
			}
			else if ((src->gameBoard[i][j] > 'a' && src->gameBoard[i][j] < 'z' && src->currentPlayer == 1) ||
					(src->gameBoard[i][j] > 'A' && src->gameBoard[i][j] < 'Z' && src->currentPlayer == 0))
			{
				totalScore += pieceValue(src->gameBoard[i][j]);
			}
			else
			{
				totalScore -= pieceValue(src->gameBoard[i][j]);
			}
		}
	}
	return totalScore;
}

int pieceValue(char piece)
{
	switch (piece){
		case 'm':
		case 'M':
			return 1;
			break;
		case 'r':
		case 'R':
			return 5;
			break;
		case 'n':
		case 'N':
			return 3;
			break;
		case 'b':
		case 'B':
			return 3;
			break;
		case 'q':
		case 'Q':
			return 9;
			break;
		case 'k':
		case 'K':
			return 100;
			break;
		default:
			return 0;
	}
}

char* getUserColor(ChessGame* src)
{
	if (src->userColor == 1)
	{
		return "white";
	}
	else
		return "black";
}
char* getPlayerColor(ChessGame* src, bool currentPlayer)
{
	if (src->currentPlayer == 1)
	{
		if (currentPlayer)
			return "white";
		else
			return "black";
	}
	else
	{
		if (!currentPlayer)
			return "white";
		else
			return "black";
	}
}

char* getDifficultyLevel(ChessGame* src)
{
	if (src->difficulty == 1)
	{
		return "amateur";
	}
	else if (src->difficulty == 2)
	{
		return "easy";
	}
	else if (src->difficulty == 3)
	{
		return "moderate";
	}
	else if (src->difficulty == 4)
	{
		return "hard";
	}
	else
		return "expert";
}

char* getPieceName(ChessGame* src, int row, int col)
{
	char piece = src->gameBoard[row][col];
	switch (piece){
		case 'm':
		case 'M':
			return "pawn";
			break;
		case 'r':
		case 'R':
			return "rook";
			break;
		case 'n':
		case 'N':
			return "knight";
			break;
		case 'b':
		case 'B':
			return "bishop";
			break;
		case 'q':
		case 'Q':
			return "queen";
			break;
		case 'k':
		case 'K':
			return "king";
			break;
		default:
			return 0;
	}
}


void printMSG(const char* currSTR)
{
	if (!UIMode)
		printf("%s", currSTR);
}

