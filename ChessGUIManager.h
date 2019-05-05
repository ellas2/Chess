#ifndef SPTICTACTOEGUIMANAGER_H_
#define SPTICTACTOEGUIMANAGER_H_
#include <SDL.h>
#include "ChessMainWindow.h"
#include "ChessSettingsWindow.h"
#include "ChessLoadWindow.h"
#include "ChessGameWindow.h"


//Type used to indicate the active window
typedef enum{
	MAIN_WINDOW,
	SETTINGS_WINDOW,
	LOAD_WINDOW,
	GAME_WINDOW
}ACTIVE_WINDOW;

//Type used to indicate the type of event - in order to handle properly in main
typedef enum{
	MANAGER_QUIT,
	MANAGER_NONE,
}MANAGER_EVENT;

/* Gui manager struce
 * Contains pointers to all of the windows,
 * active window and previous window,
 * and a boolean indicating whether we are in the save window on the way to the main window
 */
typedef struct {
	ChessMainWin* mainWin;
	ChessSettingsWin* settingsWin;
	ChessLoadWin* loadWin;
	ChessGameWin* gameWin;
	ACTIVE_WINDOW activeWin;
	ACTIVE_WINDOW prevWin;
	bool isSaveOnWayToMain;
} ChessGuiManager;


/* creates the gui manager and all related resources
 * @return
 * on success - a pointer to the created gui manager
 * on failure or error - NULL and a message is printed to the console
 */
ChessGuiManager* createManager();

/* destroys the gui manager - frees all allocated memory
 * @params - a pointer to the gui manager
 */
void destroyManager(ChessGuiManager* src);

/* draws the gui manager - calls the draw function of the current active window
 * @params - a pointer to the gui manager
 */
void drawManager(ChessGuiManager* src);

/* handles load window events - categorizes the events
 * @params - a pointer to the load window
 * @params - the SDL event
 * @return - the relevant LOAD_EVENT according to the clicked location
 */
MANAGER_EVENT handleManagerEvent(ChessGuiManager* src, SDL_Event* event);


#endif
