/*
 * CHParser.h
 *
 *  Created on: Feb 15, 2018
 *      Author: Dubi
 */

#ifndef CHPARSER_H_
#define CHPARSER_H_

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
	CH_GAME_MODE,
	CH_DIFFICULTY,
	CH_USER_COLOR,
	CH_LOAD,
	CH_DEFAULT,
	CH_PRINT_SETTINGS,
	CH_QUIT,
	CH_START,
	CH_PIECE_MOVE,
	CH_GET_MOVES,
	CH_SAVE,
	CH_UNDO_MOVE,
	CH_RESET,
	CH_INVALID_LINE,
	CH_INVALID_POSITION
} CH_COMMAND;

/*
 * Checks whether the given string represents an integer
 * @params str - given string
 * @return true - if str represents an integer, otherwise false
 */
bool CHParserIsInt(const char* str);

//Struct representing a game command. Consists of the command CH_COMMAND and values
typedef struct command_t {
	CH_COMMAND cmd;
	int validFirstArg; //is set to true if the line contains a valid argument
	int validSecondArg;
	int validThirdArg;
	int validFourthArg;
	int validFifthArg;
	int firstArg;
	char secondArg;
	int thirdArg;
	char fourthArg;
	char* fifthArg;
} CHCommand;

/*
 * Parse a given user input and convert it to a game command.
 * @params str - user input string
 * @return CHCommand representing the user command. Invalid command if the string does not contains a valid command
 */
CHCommand CHParserPraseLine(const char* str);

/*
 * Check if the given string is a single char and return it
 * @params str - given string
 * @return char that is the string, otherwise '@'
 */
char CHParserChar(const char* str);

/*
 * Extract string value from user input and place it as the fifth argument in the given command.
 * Used to extract the file path for save/load functions
 * @params currCommand - command struct to place the string at
 */
void CHParserOneStringArg(CHCommand* currCommand);

/*
 * Extract value from user input and place it as the specified argument in the given command.
 * @params currCommand - command struct to place the argument at
 * @params argNum - argument number of the command to be placed at
 */
void CHParserOneArgLine(CHCommand* currCommand, int argNum);

/*
 * Parse first part of the coord input <X,Y> and place X in the specified argument
 * @params currCommand - command struct to place the argument at
 * @params argNum - argument number of the command to be placed at
 */
void CHParserLocPart1(CHCommand* currCommand, int argNum);

/*
 * Parse second part of the coord input <X,Y> and place Y in the specified argument
 * @params currCommand - command struct to place the argument at
 * @params argNum - argument number of the command to be placed at
 */
void CHParserLocPart2(CHCommand* currCommand, int argNum);

#endif /* CHPARSER_H_ */
