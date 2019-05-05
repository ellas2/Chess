#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include "ChessGUIManager.h"
int main(int argc, char** argv) {
	extern bool UIMode;
	if (argc > 2){
		printf("Invalid number of arguments");
		return 0;
	} else if	(argc == 1){
		UIMode = false;
	} else if (argc == 2){
		if (strcmp(argv[1],"-g") == 0){
			UIMode = true;
			if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
				printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
				return 1;
			}
			ChessGuiManager* manager = createManager();
			if (manager == NULL ) {
				SDL_Quit();
				return 0;
			}
			SDL_Event event;
			while (1) {
				SDL_WaitEvent(&event);
				if (handleManagerEvent(manager, &event) == MANAGER_QUIT) {
					break;
				}
				if (manager->activeWin != GAME_WINDOW){
					drawManager(manager);
				}
			}
			destroyManager(manager);
			SDL_Quit();
			return 0;
		} else if (strcmp(argv[1], "-c") == 0){
			UIMode = false;
		}
	}
	printf(" Chess\n-------\n");
	ChessGame* newGame = ChessGameCreate();
	UIMode = false;
	while (true)
	{
		gameSettings(newGame);
		CHESS_GAME_MESSAGE msg = gamePlayed(newGame);
		if (msg == CHESS_GAME_RESTARTING)
		{
			ChessGameDestroy(newGame);
			newGame = ChessGameCreate();
		}

	}
	return 0;
}

