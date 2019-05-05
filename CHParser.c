/*
 * CHParser.c
 *
 *  Created on: Feb 15, 2018
 *      Author: Dubi
 */
#include "CHParser.h"
#include <stdio.h>

bool CHParserIsInt(const char* str)
{
	const char *p;
	p = str;
	if (*p == '-')
	{
		p++;
	}
	while (*p != '\0')
	{
		if (!isdigit(*p))
		{
			return false;
		}
		p++;
		//i++;
	}
	return true;
}

char CHParserChar(const char* str)
{
	const char *p = str;
	if (strlen(p) != 1)
		return '@';
	else if (p[0] < 'A' || p[0] > 'Z')
		return '@';
	return p[0];
}

void CHParserOneStringArg(CHCommand* currCommand)
{
	char s[] = ", \t\r\n";
	char *token, *file;
	//get the col number
	//walk through other tokens
	token = strtok(NULL, s);
	if (!token)
	{
		currCommand->cmd = CH_INVALID_LINE;
	}
	file = (char *) malloc(sizeof(char)*(strlen(token) + 1));
	strcpy(file, token);
	file[strlen(token)] = '\0';
	currCommand->validFifthArg = 1;
	currCommand->fifthArg = file;
}

void CHParserOneArgLine(CHCommand* currCommand, int argNum)
{
	char s[] = ", \t\r\n";
	char *token;
	//get the col number
	//walk through other tokens
	token = strtok(NULL, s);
	if (!token)
	{
		currCommand->cmd = CH_INVALID_LINE;
	}
	else if (CHParserIsInt(token))
	{
		switch (argNum)
		{
			case 1:
				currCommand->validFirstArg = 1;
				currCommand->firstArg = atoi(token);
				break;
			case 3:
				currCommand->validThirdArg = 1;
				currCommand->thirdArg = atoi(token);
				break;
			default:
				break;
		}
	}
	else if (CHParserChar(token) != '@')
	{
		switch (argNum)
		{
			case 2:
				currCommand->validSecondArg = 1;
				currCommand->secondArg = CHParserChar(token);
				break;
			case 4:
				currCommand->validFourthArg = 1;
				currCommand->fourthArg = CHParserChar(token);
				break;
			default:
				break;
		}
	}
	else
	{
		currCommand->cmd = CH_INVALID_LINE;
	}
}

void CHParserLocPart1(CHCommand* currCommand, int argNum)
{
	char t[] = ",";
	char *token;
	//get the col number
	//walk through other tokens
	token = strtok(NULL, t);
	if (!token)
	{
		currCommand->cmd = CH_INVALID_LINE;
	}
	else if (strlen(token) > 0 && token[0] == '<')
	{
		char* subToken = token + 1;
		if (CHParserIsInt(subToken))
		{
			switch (argNum)
			{
				case 1:
					currCommand->validFirstArg = 1;
					currCommand->firstArg = atoi(subToken);
					break;
				case 2:
					currCommand->validThirdArg = 1;
					currCommand->thirdArg = atoi(subToken);
					break;
				default:
					break;
			}
		}
		else
		{
			currCommand->cmd = CH_INVALID_LINE;
		}

	}
	else
	{
		currCommand->cmd = CH_INVALID_LINE;
	}
}
void CHParserLocPart2(CHCommand* currCommand, int argNum)
{
	char s[] = " \t\r\n";
	char *token;
	//get the col number
	//walk through other tokens
	token = strtok(NULL, s);
	if (!token)
	{
		currCommand->cmd = CH_INVALID_LINE;
	}
	else if (strlen(token) > 0 && token[strlen(token) - 1] == '>')
	{
		token[strlen(token) - 1] = '\0';
		if (CHParserChar(token) != '@')
		{
			switch (argNum)
			{
				case 1:
					currCommand->validSecondArg = 1;
					currCommand->secondArg = CHParserChar(token);
					break;
				case 2:
					currCommand->validFourthArg = 1;
					currCommand->fourthArg = CHParserChar(token);
					break;
				default:
					break;
			}
		}
		else
		{
			currCommand->cmd = CH_INVALID_LINE;
		}

	}
	else
	{
		currCommand->cmd = CH_INVALID_LINE;
	}
}

CHCommand CHParserPraseLine(const char* str)
{
	CHCommand currCommand;
	currCommand.validFirstArg = 0;
	char s[] = ", \t\r\n";
	char *token;
	char *strcopy = (char *)malloc(sizeof(char)*(strlen(str)+1));
	strcpy(strcopy, str);
	//get the first token
	token = strtok(strcopy, s);
	if (!token)
	{
		currCommand.cmd = CH_INVALID_LINE;
		free(strcopy);
		return currCommand;
	}
	else if (strcmp(token, "game_mode") == 0)
	{
		currCommand.cmd = CH_GAME_MODE;
		CHParserOneArgLine(&currCommand, 1);
		if (currCommand.validFirstArg && currCommand.firstArg != 1 && currCommand.firstArg != 2)
			currCommand.validFirstArg = 0;
	}
	else if (strcmp(token, "difficulty") == 0)
	{
		currCommand.cmd = CH_DIFFICULTY;
		CHParserOneArgLine(&currCommand, 1);
		if (currCommand.validFirstArg && !(currCommand.firstArg >= 1 && currCommand.firstArg <= 5))
			currCommand.validFirstArg = 0;
	}
	else if (strcmp(token, "user_color") == 0)
	{
		currCommand.cmd = CH_USER_COLOR;
		CHParserOneArgLine(&currCommand, 1);
		if (currCommand.validFirstArg && currCommand.firstArg != 1 && currCommand.firstArg != 0)
			currCommand.validFirstArg = 0;
	}
	else if (strcmp(token, "load") == 0)
	{
		currCommand.cmd = CH_LOAD;
		CHParserOneStringArg(&currCommand);
	}
	else if (strcmp(token, "default") == 0)
	{
		currCommand.cmd = CH_DEFAULT;
	}
	else if (strcmp(token, "print_settings") == 0)
	{
		currCommand.cmd = CH_PRINT_SETTINGS;
	}
	else if (strcmp(token, "quit") == 0)
	{
		currCommand.cmd = CH_QUIT;
	}
	else if (strcmp(token, "start") == 0)
	{
		currCommand.cmd = CH_START;
	}
	else if (strcmp(token, "move") == 0)
	{
		currCommand.cmd = CH_PIECE_MOVE;
		CHParserLocPart1(&currCommand, 1);
		if (currCommand.cmd != CH_INVALID_LINE)
			CHParserLocPart2(&currCommand, 1);
		//CHParserOneArgLine(&currCommand, 1);
		//CHParserOneArgLine(&currCommand, 2);
		token = strtok(NULL, s);
		if (!token)
		{
			currCommand.cmd = CH_INVALID_LINE;
		}
		else if (strcmp(token, "to") == 0)
		{
			CHParserLocPart1(&currCommand, 2);
			if (currCommand.cmd != CH_INVALID_LINE)
				CHParserLocPart2(&currCommand, 2);
			//CHParserOneArgLine(&currCommand, 3);
			//CHParserOneArgLine(&currCommand, 4);
		}
		else
		{
			currCommand.cmd = CH_INVALID_LINE;
		}

		if (currCommand.validFirstArg && !(currCommand.firstArg >= 1 && currCommand.firstArg <= 8)){
			currCommand.validFirstArg = 0;
		}

		if (currCommand.validSecondArg && !(currCommand.secondArg >= 'A' && currCommand.secondArg <= 'H'))
			currCommand.validSecondArg = 0;
		if (currCommand.validThirdArg && !(currCommand.thirdArg >= 1 && currCommand.thirdArg <= 8))
			currCommand.validThirdArg = 0;
		if (currCommand.validFourthArg && !(currCommand.fourthArg >= 'A' && currCommand.fourthArg <= 'H'))
			currCommand.validFourthArg = 0;
	}
	else if (strcmp(token, "get_moves") == 0)
	{
		currCommand.cmd = CH_GET_MOVES;
		CHParserLocPart1(&currCommand, 1);
		if (currCommand.cmd != CH_INVALID_LINE)
			CHParserLocPart2(&currCommand, 1);
		//CHParserOneArgLine(&currCommand, 1);
		//CHParserOneArgLine(&currCommand, 2);
		if (currCommand.validFirstArg && !(currCommand.firstArg >= 1 && currCommand.firstArg <= 8))
			currCommand.validFirstArg = 0;
		if (currCommand.validSecondArg && !(currCommand.secondArg >= 'A' && currCommand.secondArg <= 'H'))
			currCommand.validSecondArg = 0;
	}
	else if (strcmp(token, "save") == 0)
	{
		currCommand.cmd = CH_SAVE;
		CHParserOneStringArg(&currCommand);
	}
	else if (strcmp(token, "undo") == 0)
	{
		currCommand.cmd = CH_UNDO_MOVE;
	}
	else if (strcmp(token, "reset") == 0)
	{
		currCommand.cmd = CH_RESET;
	}
	else
	{
		currCommand.cmd = CH_INVALID_LINE;
	}
	free(strcopy);
	return currCommand;
}
