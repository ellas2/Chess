#ifndef LOADWINDOW_H_
#define LOADWINDOW_H_
#include "ChessWindow.h"

//slot buttons variables
#define NUM_SLOTS 5
#define BUTTON_WIDTH 1000/NUM_SLOTS
#define BUTTON_HEIGHT 400/NUM_SLOTS
#define BUTTONS_X WIN_WIDTH/2 - BUTTON_WIDTH/2

#define SLOT_1_IMAGE "./images/slot1.bmp"
#define SLOT_1_IMAGE_E "./images/slot1E.bmp"
#define FILE_PATH_1 "./files/slot1.txt"
#define SLOT_1_Y 50

#define SLOT_2_IMAGE "./images/slot2.bmp"
#define SLOT_2_IMAGE_E "./images/slot2E.bmp"
#define FILE_PATH_2 "./files/slot2.txt"
#define SLOT_2_Y SLOT_1_Y + BUTTON_HEIGHT + 10

#define SLOT_3_IMAGE "./images/slot3.bmp"
#define SLOT_3_IMAGE_E "./images/slot3E.bmp"
#define FILE_PATH_3 "./files/slot3.txt"
#define SLOT_3_Y SLOT_2_Y + BUTTON_HEIGHT + 10

#define SLOT_4_IMAGE "./images/slot4.bmp"
#define SLOT_4_IMAGE_E "./images/slot4E.bmp"
#define FILE_PATH_4 "./files/slot4.txt"
#define SLOT_4_Y SLOT_3_Y + BUTTON_HEIGHT + 10

#define SLOT_5_IMAGE "./images/slot5.bmp"
#define SLOT_5_IMAGE_E "./images/slot5E.bmp"
#define FILE_PATH_5 "./files/slot5.txt"
#define SLOT_5_Y SLOT_4_Y + BUTTON_HEIGHT + 10


//back button configurations
#define BACK "./images/back.bmp"
#define BACK_BTN_HEIGHT 53
#define BACK_BTN_WIDTH 150
#define BACK_X 650
#define BACK_Y 30


//Type used in order to know which button was clicked and handle it properly
typedef enum {
	LOAD_SLOT1, LOAD_SLOT2, LOAD_SLOT3, LOAD_SLOT4, LOAD_SLOT5,
	LOAD_BACK,
	LOAD_INVALID,
	LOAD_NONE,
	LOAD_QUIT
} LOAD_EVENT;

/* Load window Struct.
 * Contains an active and inactive texture for each button,
 * a pointer to the window, a pointer to the renderer
 * and a boolean that indicates if we're using the window as a load or save window
 */
typedef struct chess_loadwindow_t {
	SDL_Window* win;
	SDL_Renderer* winRenderer;
	//Texture for each button
	SDL_Texture* slot1Texture;
	SDL_Texture* slot1TextureE;
	bool isSlot1Enabled;
	SDL_Texture* slot2Texture;
	SDL_Texture* slot2TextureE;
	bool isSlot2Enabled;
	SDL_Texture* slot3Texture;
	SDL_Texture* slot3TextureE;
	bool isSlot3Enabled;
	SDL_Texture* slot4Texture;
	SDL_Texture* slot4TextureE;
	bool isSlot4Enabled;
	SDL_Texture* slot5Texture;
	SDL_Texture* slot5TextureE;
	bool isSlot5Enabled;
	SDL_Texture* backTexture;
	bool isLoadWindow;
} ChessLoadWin;


/* creates the load window and all related resources
 * @return
 * on success - a pointer to the created load window
 * on failure or error - NULL and a message is printed to the console
 */
ChessLoadWin* createLoadWindow();

/* destroys the load window - frees all allocated memory
 * @params - a pointer to the load window
 */
void destroyLoadWindow(ChessLoadWin* src);

/* draws the load window - uses the window's textures and renderer in order to draw the buttons properly
 * @params - a pointer to the load window
 */
void drawLoadWindow(ChessLoadWin* src);

/* handles load window events - categorizes the events
 * @params - a pointer to the load window
 * @params - the SDL event
 * @return - the relevant LOAD_EVENT according to the clicked location
 */
LOAD_EVENT handleLoadWindowEvent(ChessLoadWin* src, SDL_Event* event);

/* hides the load window
 * @params - a pointer to the load window
 */
void hideLoadWindow(ChessLoadWin* src);

/* shows the load window
 * @params - a pointer to the load window
 */
void showLoadWindow(ChessLoadWin* src);

#endif



