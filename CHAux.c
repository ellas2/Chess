/*
 * CHAux.c
 *
 *  Created on: Feb 19, 2018
 *      Author: Dubi
 */
#include "CHAux.h"

void handleReturnedMessage(CHESS_GAME_MESSAGE msg, ChessGame* game){
	extern bool UIMode;
	char msgToPrint[200];
	if (msg == CHESS_GAME_CHECK)
	{
		sprintf(msgToPrint, "Check: %s king is threatened\n", getPlayerColor(game, true));
		printMSG(msgToPrint);
	}

	if (msg == CHESS_GAME_DRAW)
	{
		printMSG("The game ends in a draw\n");
		ChessGameDestroy(game);
		exit(0);
	}
	if (msg == CHESS_GAME_CHECKMATE)
	{
		sprintf(msgToPrint, "Checkmate! %s player wins the game\n", getPlayerColor(game, false));
		printMSG(msgToPrint);
		if (!UIMode)
		{
			ChessGameDestroy(game);
			exit(0);
		}
	}
	if (msg == CHESS_GAME_INVALID_POSITION)
		printMSG("Invalid position on the board\n");
	if (msg == CHESS_GAME_INVALID_PIECE)
		printMSG("The specified position does not contain your piece\n");
	if (msg == CHESS_GAME_NO_HISTORY)
		printMSG("Empty history, no moves to undo\n");
	if (msg == CHESS_GAME_INVALID_MOVE)
		printMSG("Illegal move\n");
	if (msg == CHESS_GAME_INVALID_ARGUMENT)
		printMSG("Invalid position on the board\n");
	if (msg == CHESS_GAME_STILL_CHECK)
		printMSG("Illegal move: king is still threatened\n");
	if (msg == CHESS_GAME_WILL_CAUSE_CHECK)
		printMSG("Illegal move: king will be threatened\n");
}

void settingsActions(ChessGame* game, CHCommand currCommand)
{
	char msg[200];
	if (currCommand.cmd == CH_GAME_MODE)
	{
		if (currCommand.validFirstArg)
		{
			game->numOfPlayers = currCommand.firstArg;
			sprintf(msg, "Game mode is set to %d-player\n", currCommand.firstArg);
			printMSG(msg);
		}
		else
		{
			printMSG("Wrong game mode\n");
		}
	}
	else if (currCommand.cmd == CH_DIFFICULTY)
	{
		if (game->numOfPlayers == 2)
		{
			printMSG("ERROR: Invalid Command\n");
		}
		game->difficulty = currCommand.firstArg;
		if (currCommand.validFirstArg)
		{
			sprintf(msg, "Difficulty is set to %s\n", getDifficultyLevel(game));
			printMSG(msg);
		}

		else
			printMSG("Wrong difficulty level. The value should be between 1 to 5\n");
	}
	else if (currCommand.cmd == CH_LOAD)
	{
		sprintf(msg, "Load %d\n", currCommand.firstArg);
		printMSG(msg);
	}
	else if (currCommand.cmd == CH_USER_COLOR)
	{
		if (game->numOfPlayers == 2)
		{
			printMSG("ERROR: Invalid Command\n");
		}

		if (currCommand.validFirstArg)
		{
			game->userColor = currCommand.firstArg;
			sprintf(msg, "User color is set to %s\n", getUserColor(game));
			printMSG(msg);
		}
		else
			printMSG("Wrong user color. The value should be 0 or 1\n");
	}
	else if (currCommand.cmd == CH_DEFAULT)
	{
		game->difficulty = 2;
		game->userColor = 1;
		game->numOfPlayers = 1;
		printMSG("All settings reset to default\n");
	}
	else if (currCommand.cmd == CH_PRINT_SETTINGS)
	{
		if (game->numOfPlayers == 2)
		{
			sprintf(msg, "SETTINGS:\nGAME_MODE: 2-player\n");
		}
		else
		{
			sprintf(msg, "SETTINGS:\nGAME_MODE: 1-player\nDIFFICULTY: %s\nUSER_COLOR: %s\n",
					getDifficultyLevel(game), getUserColor(game));
		}
		printMSG(msg);

	}
	/*else if (currCommand.cmd == CH_START)
	{
		printf("Start %d\n");
	}*/
	else
	{
		printMSG("ERROR: Invalid Command\n");
	}

}


CHESS_GAME_MESSAGE gameActions(ChessGame* game, CHCommand currCommand)
{
	if (currCommand.cmd == CH_PIECE_MOVE)
	{

		if (!currCommand.validFirstArg || !currCommand.validSecondArg || !currCommand.validThirdArg || !currCommand.validFourthArg)
		{
			handleReturnedMessage(CHESS_GAME_INVALID_POSITION, game);
			return CHESS_GAME_INVALID_POSITION;
		}
		CHESS_GAME_MESSAGE msg = ChessGameSetMove(game, currCommand.firstArg,currCommand.secondArg, currCommand.thirdArg, currCommand.fourthArg);
		handleReturnedMessage(msg, game);
		if (msg == CHESS_GAME_CHECK || msg == CHESS_GAME_SUCCESS)
		{
			if (game->numOfPlayers == 1)
			{
				msg = makeComputerMove(game);
			}
			ChessGamePrintBoard(game);
		}
		return msg;

	}
	else if (currCommand.cmd == CH_GET_MOVES)
	{
		handleReturnedMessage(getMoves(game, currCommand.firstArg, currCommand.secondArg), game);
	}
	else if (currCommand.cmd == CH_SAVE)
	{
		saveGameToFile(game, currCommand.fifthArg);
	}
	else if (currCommand.cmd == CH_UNDO_MOVE)
	{
		handleReturnedMessage(undoChessMoves(game), game);
	}
	else
	{
		printMSG("ERROR: Invalid Command\n");
	}
	return CHESS_GAME_OTHER;
}
CHESS_GAME_MESSAGE makeComputerMove(ChessGame* game)
{
	int fR = 0, fC = 0, tR = 0, tC = 0;
	suggestMove(game, &fR, &fC, &tR, &tC);
	char msg[100];
	sprintf(msg,"Computer: move %s at <%d,%c> to <%d,%c>\n", getPieceName(game, fR, fC), fR + 1, fC + 'A', tR + 1, tC + 'A');
	printMSG(msg);
	CHESS_GAME_MESSAGE message = ChessGameSetMove(game, fR + 1, fC + 'A', tR + 1, tC + 'A');
	handleReturnedMessage(message, game);
	return message;
}
CHESS_GAME_MESSAGE gameSettings(ChessGame* game)
{
	SP_BUFF_SET();
	bool invalidCommand = true;
	char c[1024];
	CHCommand currCommand;
	//Initializing
	//The game itself
	printMSG("Specify game settings or type 'start' to begin a game with the current settings:\n");
	while (true)
	{
		while (invalidCommand)
		{
			if (fgets(c,1024,stdin) != NULL)
			{
				currCommand = CHParserPraseLine(c);
				if (currCommand.cmd == CH_INVALID_LINE)
				{
					printMSG("Error: invalid command\n");
					//printf("Please make the next move:\n");
				}
				else
					invalidCommand = false;
			}
		}
		if (currCommand.cmd == CH_QUIT)
		{
			ChessGameDestroy(game);
			printMSG("Exiting...");
			exit(0);
		}
		else if (currCommand.cmd == CH_LOAD)
		{
			loadGameFromFile(game, currCommand.fifthArg);
			return CHESS_GAME_STARTING;
		}
		else if (currCommand.cmd == CH_START)
		{
			printMSG("Starting game...\n");
			return CHESS_GAME_STARTING;
		}
		else
		{
			settingsActions(game, currCommand);
		}
		invalidCommand = true;
	}
	return CHESS_GAME_SUCCESS;
}
CHESS_GAME_MESSAGE gamePlayed(ChessGame* game)
{
	SP_BUFF_SET();
	char c[1024];
	CHCommand currCommand;
	if ((game->currentPlayer != game->userColor)&& game->numOfPlayers == 1)
	{
		makeComputerMove(game);
	}
	ChessGamePrintBoard(game);
	char msg[100];
	while (true)
	{
		sprintf(msg, "Enter your move (%s player):\n", getPlayerColor(game, true));
		printMSG(msg);
		fgets(c,1024,stdin);
		currCommand = CHParserPraseLine(c);
		if (currCommand.cmd == CH_QUIT)
		{
			ChessGameDestroy(game);
			printMSG("Exiting...\n");
			exit(0);
		}
		if (currCommand.cmd == CH_RESET)
		{
			printMSG("Restarting...\n");
			return CHESS_GAME_RESTARTING;
		}
		else
			gameActions(game, currCommand);
	}
	return CHESS_GAME_SUCCESS;
}

void saveGameToFile(ChessGame* game, char* outFile)
{
	FILE *f;
	SP_BUFF_SET();
	char *file = outFile;
	f = fopen(file, "w");
	if (f == NULL)
	{
		printMSG("File cannot be created or modified\n");
		if (!UIMode){
			free(file);
		}
		return;
	}
	fprintf(f, "%s\n", getPlayerColor(game, true));
	if (game->numOfPlayers == 2)
	{
		fprintf(f, "SETTINGS:\nGAME_MODE: 2-player\n");
	}
	else
	{
		fprintf(f, "SETTINGS:\nGAME_MODE: 1-player\nDIFFICULTY: %s\nUSER_COLOR: %s\n",
				getDifficultyLevel(game), getUserColor(game));
	}
	for (int i = CHESS_GAME_N_ROWS -1; i >= 0 ; i--)
	{
		fprintf(f ,"%d| ", i+1);
		for (int j=0; j<CHESS_GAME_N_ROWS; j++)
		{
			fprintf(f, "%c ", game->gameBoard[i][j]);
		}
		fprintf(f, "|\n");
	}

	fprintf (f, "  ");
	//Print the ---
	for (int i=0; i<17; i++)
	{
		fprintf (f, "-");
	}
	fprintf (f, "\n");
	//Print the nums
	fprintf(f, "   ");
	fprintf(f, "%c", 'A');
	for (int i=1; i<CHESS_GAME_N_COLUMNS; i++)
	{
		fprintf(f, " %c", 'A' + i);
	}
	fprintf(f, "\n");
	char msg[sizeof(file) + 50];
	sprintf(msg, "Game saved to: %s\n", file);
	printMSG(msg);
	fclose(f);
	if (file != NULL && !UIMode){
			free(outFile);
		}
}

void loadGameFromFile(ChessGame* game, char* inFile)
{
	FILE *f;
	char *file = inFile;
	f = fopen(file, "r");
	if (f == NULL)
	{
		printMSG("ERROR: File doesn't exist or cannot be opened\n");
		if (!UIMode){
			free(file);
		}
		return;
	}
	char color[256];
	char difficulty[256];
	fscanf(f, "%s\n", color);
	if (strcmp(color,"black") == 0)
		game->currentPlayer = 0;
	else
		game->currentPlayer = 1;
	fscanf(f, "SETTINGS:\nGAME_MODE: %d-player\n", &game->numOfPlayers);
	if (game->numOfPlayers == 1)
	{
		fscanf(f, "DIFFICULTY: %s\nUSER_COLOR: %s\n",
						difficulty, color);
		if (strcmp(difficulty, "amateur") == 0)
		{
			game->difficulty = 1;
		}
		else if (strcmp(difficulty, "easy") == 0)
		{
			game->difficulty = 2;
		}
		else if (strcmp(difficulty, "moderate") == 0)
		{
			game->difficulty = 3;
		}
		else if (strcmp(difficulty, "hard") == 0)
		{
			game->difficulty = 4;
		}
		else
			game->difficulty = 5;
		if (strcmp(color,"black") == 0)
			game->userColor = 0;
		else
			game->userColor = 1;
	}
	int fake;
	for (int i = CHESS_GAME_N_ROWS -1; i >= 0 ; i--)
	{
		fscanf(f ,"%d| ", &fake);
		for (int j=0; j<CHESS_GAME_N_ROWS; j++)
		{
			fscanf(f, "%c ", &game->gameBoard[i][j]);
		}
		fscanf(f, "|\n");
	}
    game->history->movesInHistory = 0;
	char msg[sizeof(file) + 50];
	sprintf(msg, "Game loaded from: %s\n", file);
	printMSG(msg);
	if (!UIMode){
		free(file);
	}
	fclose(f);
}
