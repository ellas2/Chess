#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "ChessGame.h"
#include "CHAux.h"
#include "ChessWindow.h"

//buttons variables
#define BUTTONS_WIDTH_G 200
#define BUTTONS_HEIGHT_G 90
#define BUTTONS_X_G 600
#define RESTART_IMG "./images/restart.bmp"
#define RESTART_Y 10
#define SAVE_IMG "./images/save.bmp"
#define SAVE_Y RESTART_Y + BUTTONS_HEIGHT_G + 5
#define LOAD_IMG "./images/load.bmp"
#define LOAD_Y SAVE_Y + BUTTONS_HEIGHT_G + 5
#define UNDO_IMG "./images/undo.bmp"
#define UNDO_Y LOAD_Y + BUTTONS_HEIGHT_G + 5
#define MAIN_IMG "./images/main.bmp"
#define MAIN_Y UNDO_Y + BUTTONS_HEIGHT_G + 5
#define QUIT_IMG "./images/quit.bmp"
#define QUIT_Y MAIN_Y + BUTTONS_HEIGHT_G + 5
#define UNDO_UNAVAIL_IMG "./images/undoUnavailable.bmp"
#define MSG_Y QUIT_Y + BUTTONS_HEIGHT_G + 5


//Type used in order to know which button was clicked and handle it properly
//Also, there's an event for every game state - one player won, check, etc.
typedef enum {
	GAME_WHITE_WON,
	GAME_BLACK_WON,
	GAME_WHITE_CHECKED,
	GAME_BLACK_CHECKED,
	GAME_TIE,
	GAME_RESTART,
	GAME_SAVE,
	GAME_LOAD,
	GAME_UNDO,
	GAME_MAIN,
	GAME_QUIT,
	GAME_INVALID_ARGUMENT,
	GAME_NONE
} GAME_EVENT;


/* Game window Struct.
 * Contains an active and inactive texture for each button and each piece,
 * a pointer to the window, a pointer to the renderer,
 * a pointer to the game itself and a boolean that indicates if the game is saved
 */
typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;

	//pieces textures
	SDL_Texture* black_knight_Texture;
	SDL_Texture* white_knight_Texture;
	SDL_Texture* black_pawn_Texture;
	SDL_Texture* white_pawn_Texture;
	SDL_Texture* black_rook_Texture;
	SDL_Texture* white_rook_Texture;
	SDL_Texture* black_bishop_Texture;
	SDL_Texture* white_bishop_Texture;
	SDL_Texture* black_king_Texture;
	SDL_Texture* white_king_Texture;
	SDL_Texture* black_queen_Texture;
	SDL_Texture* white_queen_Texture;
	//other buttons textures
	SDL_Texture* restartTexture;
	SDL_Texture* saveTexture;
	SDL_Texture* loadTexture;
	SDL_Texture* undoTexture;
	SDL_Texture* mainTexture;
	SDL_Texture* quitTexture;
	//textures for highlight move
	SDL_Texture* yellow_square_Texture;
	SDL_Texture* red_square_Texture;
	SDL_Texture* purple_square_Texture;
	SDL_Texture* green_square_Texture;

	ChessGame* game;
	bool isGameSaved;
}ChessGameWin;

int fromRow;
int fromCol;
char remember;
SDL_Rect currRect;
int xDif;
int yDif;
int move;

/* creates the load window and all related resources
 * @return
 * on success - a pointer to the created load window
 * on failure or error - NULL and a message is printed to the console
 */
ChessGameWin* createGameWindow();

/* destroys the game window - frees all allocated memory
 * @params - a pointer to the game window
 */
void destroyGameWindow(ChessGameWin* src);

/* draws the game window - uses the window's textures and renderer in order to draw the buttons properly
 * @params - a pointer to the game window
 */
void drawGameWindow(ChessGameWin*);

/* handles game window events - categorizes the events
 * @params - a pointer to the game window
 * @params - the SDL event
 * @return - the relevant GAME_EVENT according to the clicked location
 */
GAME_EVENT handleGameWindowEvent(ChessGameWin* src, SDL_Event* event);

/* hides the game window
 * @params - a pointer to the game window
 */
void hideGameWindow(ChessGameWin* src);

/* shows the game window
 * @params - a pointer to the game window
 */
void showGameWindow(ChessGameWin* src);

/*
 * Get all possible moves of a piece from a given location
 * a standard square will be colored in yellow
 * a threatened square will be colored in red
 * a capture square will be colored in green
 * a capture and threatened square will be colored in purple
 * @params src - current game
 * @params fromRow - row coordinate of the piece
 * @params fromChar - col coordinate of the piece, represented by character
 * @return - The relevant CHESS_GAME_MESSAGE
 */

CHESS_GAME_MESSAGE getMovesGUI(ChessGameWin* src, int fromRow, int fromCol);

#endif /* GAMEWINDOW_H_ */
