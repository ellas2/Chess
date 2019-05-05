/*
 * CHMinimax.c
 *
 *  Created on: Feb 18, 2018
 *      Author: Dubi
 */
#include "CHMinimax.h"

void suggestMove(ChessGame* src, int* fromRow, int* fromCol, int* toRow, int* toCol)
{

	int curValue;
	int alpha = -1000;
	int beta = 1000;
	bool fullHist = false;
	if (chessHasHistory(src->history) == CHESS_HISTORY_LIST_FULL)
	{
		fullHist = true;
	}
	ChessMoveRecord backUpRec = backUpfirstRecord(src);
	bool firstOption = true;
	if (src->difficulty%2 == 0){
		int maxValue = -1000;
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
			{
				for (int n = 0; n < CHESS_GAME_N_COLUMNS; n++)
				{
					for (int m = 0; m < CHESS_GAME_N_ROWS; m++)
					{
						CHESS_GAME_MESSAGE msg = ChessGameSetMove(src, i + 1, j + 'A', m + 1, n + 'A');
						if (msg == CHESS_GAME_DRAW)
							curValue = 0;
						else if (msg == CHESS_GAME_CHECKMATE)
							curValue = 1000;
						else if (msg == CHESS_GAME_CHECK || msg == CHESS_GAME_SUCCESS){
							curValue = minimaxFunction(src, src->difficulty - 1, alpha, beta, false);
						}
						else
						{
							continue;
						}
						undoSingleChessMove(src, false);
						if (curValue > maxValue || firstOption)
						{
							*fromRow = i;
							*fromCol = j;
							*toRow = m;
							*toCol = n;
							maxValue = curValue;
							firstOption = false;
						}
						if (maxValue > alpha)
							alpha = maxValue;
						if (beta <= alpha){
							if (fullHist)
								addFirstRecordChessHistory(src->history, backUpRec);
							return;
						}

					}
				}
			}
		}
	}
	else
	{
		int maxValue = 1000;
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
			{
				for (int n = 0; n < CHESS_GAME_N_COLUMNS; n++)
				{
					for (int m = 0; m < CHESS_GAME_N_ROWS; m++)
					{
						CHESS_GAME_MESSAGE msg = ChessGameSetMove(src, i + 1, j + 'A', m + 1, n + 'A');
						if (msg == CHESS_GAME_DRAW)
							curValue = 0;
						else if (msg == CHESS_GAME_CHECKMATE)
							curValue = -1000;
						else if (msg == CHESS_GAME_CHECK || msg == CHESS_GAME_SUCCESS){
							curValue = minimaxFunction(src, src->difficulty - 1, alpha, beta, true);
						}
						else
						{
							continue;
						}
						undoSingleChessMove(src, false);
						if (curValue < maxValue || firstOption)
						{
							*fromRow = i;
							*fromCol = j;
							*toRow = m;
							*toCol = n;
							maxValue = curValue;
							firstOption = false;
						}
						if (maxValue < beta)
							beta = maxValue;
						if (beta <= alpha){
							if (fullHist)
								addFirstRecordChessHistory(src->history, backUpRec);
							return;
						}

					}
				}
			}
		}
	}
	if (fullHist)
		addFirstRecordChessHistory(src->history, backUpRec);
}

int minimaxFunction(ChessGame* src, int depth, int alpha, int beta, bool maxPlayer)
{
	if (depth == 0)
		return boardScore(src);
	bool fullHist = false;
	if (chessHasHistory(src->history) == CHESS_HISTORY_LIST_FULL){
		fullHist = true;
	}
	ChessMoveRecord backUpRec = backUpfirstRecord(src);
	if (maxPlayer)
	{
		int value = -1000;
		int curValue;
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
			{
				for (int n = 0; n < CHESS_GAME_N_COLUMNS; n++)
				{
					for (int m = 0; m < CHESS_GAME_N_ROWS; m++)
					{
						CHESS_GAME_MESSAGE msg = ChessGameSetMove(src, i + 1, j + 'A', m + 1, n + 'A');
						if (msg == CHESS_GAME_DRAW)
							curValue = 0;
						else if (msg == CHESS_GAME_CHECKMATE)
							curValue = 1000;
						else if (msg == CHESS_GAME_CHECK || msg == CHESS_GAME_SUCCESS)
							curValue = minimaxFunction(src, depth - 1, alpha, beta, false);
						else
						{
							continue;
						}
						undoSingleChessMove(src, false);
						if (curValue > value)
							value = curValue;
						if (value > alpha)
							alpha = value;
						if (beta <= alpha)
						{
							if (fullHist)
								addFirstRecordChessHistory(src->history, backUpRec);
							return value;
						}
					}
				}
			}
		}
		if (fullHist)
			addFirstRecordChessHistory(src->history, backUpRec);
		return value;
	}
	else
	{
		int value = 1000;
		int curValue;
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
			{
				for (int n = 0; n < CHESS_GAME_N_COLUMNS; n++)
				{
					for (int m = 0; m < CHESS_GAME_N_ROWS; m++)
					{
						CHESS_GAME_MESSAGE msg = ChessGameSetMove(src, i + 1, j + 'A', m + 1, n + 'A');
						if (msg == CHESS_GAME_DRAW)
							curValue = 0;
						else if (msg == CHESS_GAME_CHECKMATE)
							curValue = -1000;
						else if (msg == CHESS_GAME_CHECK || msg == CHESS_GAME_SUCCESS)
							curValue = minimaxFunction(src, depth - 1, alpha, beta, true);
						else
						{
							//undoSingleChessMove(src, false);
							continue;
						}

						undoSingleChessMove(src, false);
						if (curValue < value)
							value = curValue;
						if (value < beta)
							beta = value;
						if (beta <= alpha)
						{
							if (fullHist)
								addFirstRecordChessHistory(src->history, backUpRec);
							return value;
						}

					}
				}
			}
		}
		if (fullHist)
			addFirstRecordChessHistory(src->history, backUpRec);
		return value;
	}
}
