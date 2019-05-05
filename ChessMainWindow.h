#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include "ChessWindow.h"
//Buttons images
#define NEW_IMAGE "./images/new.bmp"
#define LOAD_IMAGE "./images/load.bmp"
#define QUIT_IMAGE "./images/quit.bmp"

//Buttons variables
#define NUM_BUTTONS_MAIN_WIN 3
#define BUTTONS_WIDTH 226
#define BUTTONS_HEIGHT 90
#define BUTTONS_X_VAL WIN_WIDTH/2 - BUTTONS_WIDTH/2
#define NEW_BUTTON_Y_VAL 160
#define LOAD_BUTTON_Y_VAL NEW_BUTTON_Y_VAL + BUTTONS_HEIGHT + 10
#define QUIT_BUTTON_Y_VAL LOAD_BUTTON_Y_VAL + BUTTONS_HEIGHT + 10

//Type used in order to know which button was clicked and handle it properly
typedef enum {
	MAIN_NEW, MAIN_LOAD, MAIN_QUIT, MAIN_INVALID, MAIN_NONE
} MAIN_EVENT;

/* Main window Struct.
 * Contains a texture for each button, a pointer to the window and a pointer to the renderer
 */
typedef struct chess_mainwindow_t {
	SDL_Window* win;
	SDL_Renderer* winRenderer;
	//Texture for each button
	SDL_Texture* newTexture;
	SDL_Texture* loadTexture;
	SDL_Texture* quitTexture;
} ChessMainWin;

/* creates the main window
 * @return
 * on success - a pointer to the created main window
 * on failure or error - NULL and a message is printed to the console
 */
ChessMainWin* createMainWindow();

/* destroys the main window - frees all allocated memory
 * @params - a pointer to the main window
 */
void destroyMainWindow(ChessMainWin* src);

/* draws the main window - uses the window's textures and renderer in order to draw the buttons properly
 * @params - a pointer to the main window
 */
void drawMainWindow(ChessMainWin* src);

/* handles main window events - categorizes the events
 * @params - a pointer to the main window
 * @params - the SDL event
 * @return - the relevant MAIN_EVENT according to the clicked location
 */
MAIN_EVENT handleMainWindowEvent(ChessMainWin* src, SDL_Event* event);

/* hides the main window
 * @params - a pointer to the main window
 */
void hideMainWindow(ChessMainWin* src);

/* shows the main window
 * @params - a pointer to the main window
 */
void showMainWindow(ChessMainWin* src);

#endif



