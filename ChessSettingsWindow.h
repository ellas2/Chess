#ifndef SETTINGSWINDOW_H_
#define SETTINGSWINDOW_H_
#include "ChessWindow.h"

//game mode buttons variables
#define ONE_PLAYER "./images/onePlayer.bmp"
#define ONE_PLAYER_A "./images/onePlayerA.bmp"
#define TWO_PLAYERS "./images/twoPlayers.bmp"
#define TWO_PLAYERS_A "./images/twoPlayersA.bmp"
#define PLAYERS_BTN_HEIGHT 99
#define PLAYERS_BTN_WIDTH 169
#define ONE_PLAYER_X WIN_WIDTH/2 - 200 + HEIGHT_OFFSET
#define TWO_PLAYERS_X WIN_WIDTH/2 + 12
#define PLAYER_Y WIN_HEIGHT/4 - PLAYER_OFFSET_Y
#define PLAYER_OFFSET_Y 102
#define PLAYER_OFFSET_X BACK_START_BTN_WIDTH/2

//difficulty level buttons variables
#define AMAT "./images/amat.bmp"
#define AMAT_A "./images/amatA.bmp"
#define EASY "./images/easy.bmp"
#define EASY_A "./images/easyA.bmp"
#define MODER "./images/moder.bmp"
#define MODER_A "./images/moderA.bmp"
#define HARD "./images/hard.bmp"
#define HARD_A "./images/hardA.bmp"
#define HARD "./images/hard.bmp"
#define HARD_A "./images/hardA.bmp"
#define EXP "./images/exp.bmp"
#define EXP_A "./images/expA.bmp"
#define DIFF_Y 222
#define SETTINGS_BTN_WIDTH 140
#define SETTINGS_BTN_HEIGHT 68
#define AMAT_X 20
#define EASY_X 180
#define MODER_X 340
#define HARD_X 500
#define EXP_X 660

//color buttons variables
#define WHITE "./images/white.bmp"
#define WHITE_A "./images/whiteA.bmp"
#define BLACK "./images/black.bmp"
#define BLACK_A "./images/blackA.bmp"
#define COLOR_Y WIN_HEIGHT/2 + 10
#define WHITE_X WIN_WIDTH/2 - 150
#define BLACK_X WIN_WIDTH/2 + 60
#define COLOR_BTN_WIDTH SETTINGS_BTN_WIDTH
#define COLOR_BTN_HEIGHT SETTINGS_BTN_HEIGHT

//back button variables
#define BACK "./images/back.bmp"
#define BACK_BTN_HEIGHT 53
#define BACK_BTN_WIDTH 150
#define BACK_X 650
#define BACK_Y 30
//start button related
#define START "./images/start.bmp"
#define START_BTN_WIDTH 211
#define START_BTN_HEIGHT 84
#define START_X 295
#define START_Y 444

#define BACK_START_BTN_WIDTH 200
#define BACK_START_BTN_HEIGHT (WIN_HEIGHT/4)*3

#define HEIGHT_OFFSET 20

//Type used in order to know which button was clicked and handle it properly
typedef enum {
	//Game mode events
	SETTINGS_1_PLAYER,
	SETTINGS_2_PLAYERS,
	//Difficulty events
	SETTINGS_AMAT,
	SETTINGS_EASY,
	SETTINGS_MODER,
	SETTINGS_HARD,
	SETTINGS_EXP,
	//Color events
	SETTINGS_WHITE,
	SETTINGS_BLACK,
	//General buttons' events
	SETTINGS_BACK,
	SETTINGS_START,

	SETTINGS_INVALID,
	SETTINGS_NONE,
	SETTINGS_QUIT
} SETTINGS_EVENT;

/* Settings window Struct.
 * Contains an active and an inactive texture for each button
 * a pointer to the window, a pointer to the renderer
 * and a boolean for each button - indicating whether the button is active or not
 */
typedef struct chess_settingswindow_t {
	SDL_Window* win;
	SDL_Renderer* winRenderer;
	//Texture for each button
	SDL_Texture* onePlayerTextureA;
	SDL_Texture* onePlayerTexture;
	bool isOnePlayerActive;
	SDL_Texture* twoPlayersTextureA;
	SDL_Texture* twoPlayersTexture;
	bool isTwoPlayersActive;
	SDL_Texture* amatTextureA;
	SDL_Texture* amatTexture;
	bool isAmatActive;
	SDL_Texture* easyTextureA;
	SDL_Texture* easyTexture;
	bool isEasyActive;
	SDL_Texture* moderTextureA;
	SDL_Texture* moderTexture;
	bool isModerActive;
	SDL_Texture* hardTextureA;
	SDL_Texture* hardTexture;
	bool isHardActive;
	SDL_Texture* expTextureA;
	SDL_Texture* expTexture;
	bool isExpActive;
	SDL_Texture* whiteTextureA;
	SDL_Texture* whiteTexture;
	bool isWhiteActive;
	SDL_Texture* blackTextureA;
	SDL_Texture* blackTexture;
	bool isBlackActive;
	SDL_Texture* startTexture;
	SDL_Texture* backTexture;
} ChessSettingsWin;

/* creates the settings window  and all related resources
 * @return
 * on success - a pointer to the created settings window
 * on failure or error - NULL and a message is printed to the console
 */
ChessSettingsWin* createSettingsWindow();

/* destroys the settings window - frees all allocated memory
 * @params - a pointer to the settings window
 */
void destroySettingsWindow(ChessSettingsWin* src);

/* draws the settings window - uses the window's textures and renderer in order to draw the buttons properly
 * @params - a pointer to the settings window
 */
void drawSettingsWindow(ChessSettingsWin* src);

/* handles settings window events - categorizes the events
 * @params - a pointer to the settings window
 * @params - the SDL event
 * @return - the relevant SETTINGS_EVENT according to the clicked location
 */
SETTINGS_EVENT handleSettingsWindowEvent(ChessSettingsWin* src, SDL_Event* event);

/* hides the settings window
 * @params - a pointer to the settings window
 */
void hideSettingsWindow(ChessSettingsWin* src);

/* shows the settings window
 * @params - a pointer to the settings window
 */
void showSettingsWindow(ChessSettingsWin* src);

/*	a helper function that indicates whether the user has finished choosing all the 'one player' settings
 * @params - a pointer to the settings window
 * @return - 1 if the user has completed, 0 otherwise
 */
int isOnePlayerComplete(ChessSettingsWin* src);

#endif



