/*
 * CHMovesHistory.c
 *
 *  Created on: Feb 16, 2018
 *      Author: Dubi
 */

#include "CHMovesHistory.h"

ChessMoveRecord createChessMoveRecord(char oldPiece, int oldRow,
		int oldCol, int newRow, int newCol)
{
	ChessMoveRecord newRecord;
	newRecord.oldPiece = oldPiece;
	newRecord.oldRow = oldRow;
	newRecord.oldCol = oldCol;
	newRecord.newRow = newRow;
	newRecord.newCol = newCol;
	return newRecord;
}

ChessHistory* createChessHistory(int maxSize)
{
	extern bool UIMode;
	ChessHistory* newHistory = (ChessHistory*)malloc(sizeof(ChessHistory));
	if (newHistory == NULL)
	{
		if (!UIMode)
			printf("Failed to create move history");
		return NULL;
	}
	newHistory->maxSize = maxSize;
	newHistory->movesInHistory = 0;
	newHistory->movesHistory = (ChessMoveRecord*)malloc(sizeof(ChessMoveRecord) * maxSize);
	if (newHistory->movesHistory == NULL)
	{
		if (!UIMode)
			printf("Failed to create history moves");
		free(newHistory);
		return NULL;
	}
	return newHistory;
}

CHESS_HISTORY_LIST_MESSAGE chessHasHistory(ChessHistory* chessHistory)
{
	if (chessHistory == NULL)
	{
		return CHESS_HISTORY_LIST_INVALID_ARGUMENT;
	}
	if (chessHistory->movesInHistory == 0)
	{
		return CHESS_HISTORY_LIST_EMPTY;
	}
	else if (chessHistory->movesInHistory == chessHistory->maxSize)
	{
		return CHESS_HISTORY_LIST_FULL;
	}
	else
	{
		return CHESS_HISTORY_LIST_SUCCESS;
	}
}

CHESS_HISTORY_LIST_MESSAGE addMoveToChessHistory(ChessHistory* chessHistory, char oldPiece, int oldRow,
		int oldCol, int newRow, int newCol)
{
	if (chessHistory == NULL)
	{
		return CHESS_HISTORY_LIST_INVALID_ARGUMENT;
	}
	CHESS_HISTORY_LIST_MESSAGE msg = chessHasHistory(chessHistory);
	if (msg == CHESS_HISTORY_LIST_FULL )
	{
		CHESS_HISTORY_LIST_MESSAGE remMsg = removeFirstMoveFromChessHistory(chessHistory);
		if (remMsg != CHESS_HISTORY_LIST_SUCCESS)
		{
			if (!UIMode)
				printf("Error while removing first move from history");
			return CHESS_HISTORY_LIST_FAIL;
		}
	}
	return addLastMoveToChessHistory(chessHistory, oldPiece, oldRow, oldCol, newRow, newCol);
}

CHESS_HISTORY_LIST_MESSAGE addLastMoveToChessHistory(ChessHistory* chessHistory, char oldPiece, int oldRow,
		int oldCol, int newRow, int newCol)
{
	chessHistory->movesHistory[chessHistory->movesInHistory] =
			createChessMoveRecord(oldPiece, oldRow, oldCol, newRow, newCol);
	chessHistory->movesInHistory += 1;
	return CHESS_HISTORY_LIST_SUCCESS;
}

CHESS_HISTORY_LIST_MESSAGE removeFirstMoveFromChessHistory(ChessHistory* chessHistory)
{
	if (chessHistory == NULL)
	{
		return CHESS_HISTORY_LIST_INVALID_ARGUMENT;
	}
	chessHistory->movesInHistory = chessHistory->movesInHistory - 1;
	for (int i = 0; i < chessHistory->movesInHistory; i++)
	{
		chessHistory->movesHistory[i] = chessHistory->movesHistory[i+1];
	}
	return CHESS_HISTORY_LIST_SUCCESS;
}

ChessMoveRecord removeLastMoveFromChessHistory(ChessHistory* chessHistory)
{
	chessHistory->movesInHistory -= 1;
	return chessHistory->movesHistory[chessHistory->movesInHistory];
}

CHESS_HISTORY_LIST_MESSAGE addFirstRecordChessHistory(ChessHistory* chessHistory, ChessMoveRecord firstRec)
{
	if (chessHistory == NULL)
	{
		return CHESS_HISTORY_LIST_INVALID_ARGUMENT;
	}
	for (int i = chessHistory->movesInHistory; i > 0; i--)
	{
		chessHistory->movesHistory[i] = chessHistory->movesHistory[i-1];
	}
	chessHistory->movesHistory[0] = firstRec;
	chessHistory->movesInHistory = chessHistory->movesInHistory + 1;
	return CHESS_HISTORY_LIST_SUCCESS;
}

CHESS_HISTORY_LIST_MESSAGE freeChessHistory(ChessHistory* chessHistory)
{
	if (chessHistory == NULL)
	{
		return CHESS_HISTORY_LIST_INVALID_ARGUMENT;
	}
	free(chessHistory->movesHistory);
	free(chessHistory);
	return CHESS_HISTORY_LIST_SUCCESS;
}

ChessMoveRecord getMoveFromChessHistory(ChessHistory* chessHistory, int loc)
{
	ChessMoveRecord rec = chessHistory->movesHistory[loc];
	return rec;
}
