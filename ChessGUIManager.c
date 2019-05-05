#include "ChessGUIManager.h"
#include <stdio.h>
#include <stdlib.h>

ChessGuiManager* createManager() {
	ChessGuiManager* res = (ChessGuiManager*) malloc(sizeof(ChessGuiManager));
	if (res == NULL ) {
		return NULL ;
	}
	res->mainWin = createMainWindow();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL ;
	}
	//initialize other windows to null
	res->loadWin = NULL;
	res->gameWin = NULL;
	res->settingsWin = NULL;
	//set active and previous window to main window
	res->activeWin = MAIN_WINDOW;
	res->prevWin = MAIN_WINDOW;
	res->isSaveOnWayToMain = false;
	return res;
}

void destroyManager(ChessGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->settingsWin != NULL) {
		destroySettingsWindow(src->settingsWin);
		src->settingsWin = NULL;
	}
	if (src->loadWin != NULL) {
		destroyLoadWindow(src->loadWin);
		src->loadWin = NULL;
	}
	if (src->gameWin != NULL){
		destroyGameWindow(src->gameWin);
		src->gameWin = NULL;
	}
	destroyMainWindow(src->mainWin);
	src->mainWin = NULL;
	free(src);
}

void drawManager(ChessGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == MAIN_WINDOW) {
		drawMainWindow(src->mainWin);
	}
	if (src->activeWin == SETTINGS_WINDOW) {
		drawSettingsWindow(src->settingsWin);
	}
	if (src->activeWin == LOAD_WINDOW) {
		drawLoadWindow(src->loadWin);
	}
	if (src->activeWin == GAME_WINDOW) {
		drawGameWindow(src->gameWin);
	}
}

MANAGER_EVENT handleManagerDueToMainEvent(ChessGuiManager* src, MAIN_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == MAIN_NEW) {
		hideMainWindow(src->mainWin);
		//Maybe we've already created a settings window		
		if (src->settingsWin != NULL){
			destroySettingsWindow(src->settingsWin);
			src->settingsWin = NULL;
		}
		src->settingsWin = createSettingsWindow();
		if (src->settingsWin == NULL ) {
			printf("Couldn't create settings window\n");
			return MANAGER_QUIT;
		}
		//Maybe we've already created a game window		
		if (src->gameWin != NULL){
			destroyGameWindow(src->gameWin);
			src->gameWin = NULL;
		}
		src->gameWin = createGameWindow();
		if (src->gameWin == NULL){
			free(src);
			return MANAGER_QUIT;
		}
		hideGameWindow(src->gameWin);
		src->activeWin = SETTINGS_WINDOW;
		src->prevWin = MAIN_WINDOW;
	} else if (event == MAIN_LOAD) {

		hideMainWindow(src->mainWin);
		//Maybe we've already created a load window		
		if (src->loadWin != NULL){
			destroyLoadWindow(src->loadWin);
			src->loadWin = NULL;
		}
		src->loadWin = createLoadWindow();
		if (src->loadWin == NULL){
			free(src);
			return MANAGER_QUIT;
		}
		//Maybe we've already created a game window		
		if (src->gameWin != NULL){
			destroyGameWindow(src->gameWin);
			src->gameWin = NULL;
		}
		src->gameWin = createGameWindow();
		if (src->gameWin == NULL){
			free(src);
			return MANAGER_QUIT;
		}
		hideGameWindow(src->gameWin);
		src->loadWin->isLoadWindow = true;
		src->activeWin = LOAD_WINDOW;
		src->prevWin = MAIN_WINDOW;
		showLoadWindow(src->loadWin);
	}
	if (event == MAIN_QUIT){
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}


LOAD_EVENT handleManagerDueToLoadEvent(ChessGuiManager* src, LOAD_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == LOAD_SLOT1) {
		if (src->loadWin->isLoadWindow == true){
			if (src->loadWin->isSlot1Enabled == true){
				loadGameFromFile(src->gameWin->game, FILE_PATH_1);
				if (src->gameWin->game->numOfPlayers == 1 && src->gameWin->game->currentPlayer != src->gameWin->game->userColor)
					makeComputerMove(src->gameWin->game);
				hideLoadWindow(src->loadWin);
				showGameWindow(src->gameWin);
				drawGameWindow(src->gameWin);
				src->activeWin = GAME_WINDOW;
				src->prevWin = LOAD_WINDOW;
				src->gameWin->isGameSaved = true;
			}
			else{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Unable to load!",
									"There is no saved game in slot 1", NULL );
			}
		}
		else{
			saveGameToFile(src->gameWin->game, FILE_PATH_1);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Horray!",
																"Game is saved to slot 1", NULL );
			src->loadWin->isSlot1Enabled = true;
			if (src->isSaveOnWayToMain == true){

				hideLoadWindow(src->loadWin);
				if (src->gameWin != NULL){
					hideGameWindow(src->gameWin);
					printf("we still have a game window");
				}
				if (src->settingsWin != NULL){
					hideSettingsWindow(src->settingsWin);
					printf("we still have a settings window");
				}

				showMainWindow(src->mainWin);
				drawMainWindow(src->mainWin);
				src->activeWin = MAIN_WINDOW;
				src->prevWin= LOAD_WINDOW;

			}
		}
	} else if (event == LOAD_SLOT2) {
		if (src->loadWin->isLoadWindow == true){
			if (src->loadWin->isSlot2Enabled == true){
				loadGameFromFile(src->gameWin->game, FILE_PATH_2);
				hideLoadWindow(src->loadWin);
				showGameWindow(src->gameWin);
				drawGameWindow(src->gameWin);
				src->activeWin = GAME_WINDOW;
				src->prevWin = LOAD_WINDOW;
				src->gameWin->isGameSaved = true;
			}
			else{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Unable to load!",
									"There is no saved game in slot 2", NULL );
			}
		}
		else{
			saveGameToFile(src->gameWin->game, FILE_PATH_2);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Horray!",
																"Game is saved to slot 2", NULL );
			src->loadWin->isSlot2Enabled = true;
			if (src->isSaveOnWayToMain == true){
				hideLoadWindow(src->loadWin);
				showMainWindow(src->mainWin);
				drawMainWindow(src->mainWin);
				src->activeWin = MAIN_WINDOW;
				src->prevWin= LOAD_WINDOW;
			}


		}
	} else if (event == LOAD_SLOT3) {
		if (src->loadWin->isLoadWindow == true){
			if (src->loadWin->isSlot3Enabled == true){
				loadGameFromFile(src->gameWin->game, FILE_PATH_3);
				hideLoadWindow(src->loadWin);
				showGameWindow(src->gameWin);
				drawGameWindow(src->gameWin);
				src->activeWin = GAME_WINDOW;
				src->prevWin = LOAD_WINDOW;
				src->gameWin->isGameSaved = true;
			}
			else{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Unable to load!",
									"There is no saved game in slot 3", NULL );
			}
		}
		else{
			saveGameToFile(src->gameWin->game, FILE_PATH_3);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Horray!",
																"Game is saved to slot 3", NULL );
			src->loadWin->isSlot3Enabled = true;
			if (src->isSaveOnWayToMain == true){
				hideLoadWindow(src->loadWin);
				showMainWindow(src->mainWin);
				drawMainWindow(src->mainWin);
				src->activeWin = MAIN_WINDOW;
				src->prevWin= LOAD_WINDOW;
			}

		}
	} else if (event == LOAD_SLOT4) {
		if (src->loadWin->isLoadWindow == true){
			if (src->loadWin->isSlot4Enabled == true){
				loadGameFromFile(src->gameWin->game, FILE_PATH_4);
				hideLoadWindow(src->loadWin);
				showGameWindow(src->gameWin);
				drawGameWindow(src->gameWin);
				src->activeWin = GAME_WINDOW;
				src->prevWin = LOAD_WINDOW;
				src->gameWin->isGameSaved = true;
			}
			else{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Unable to load!",
									"There is no saved game in slot 4", NULL );
			}
		}
		else{
				saveGameToFile(src->gameWin->game, FILE_PATH_4);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Horray!",
																	"Game is saved to slot 4", NULL );
				src->loadWin->isSlot4Enabled = true;
				if (src->isSaveOnWayToMain == true){
					hideLoadWindow(src->loadWin);
					showMainWindow(src->mainWin);
					drawMainWindow(src->mainWin);
					src->activeWin = MAIN_WINDOW;
					src->prevWin= LOAD_WINDOW;
				}
		}
	} else if (event == LOAD_SLOT5) {
		if (src->loadWin->isLoadWindow == true){
			if (src->loadWin->isSlot5Enabled == true){
				loadGameFromFile(src->gameWin->game, FILE_PATH_5);
				hideLoadWindow(src->loadWin);
				showGameWindow(src->gameWin);
				drawGameWindow(src->gameWin);
				src->activeWin = GAME_WINDOW;
				src->prevWin = LOAD_WINDOW;
				src->gameWin->isGameSaved = true;
			}
			else{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Unable to load!",
									"There is no saved game in slot 5", NULL );
			}
		}
		else{
				saveGameToFile(src->gameWin->game, FILE_PATH_5);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Horray!",
																	"Game is saved to slot 5", NULL );
				src->loadWin->isSlot5Enabled = true;
				if (src->isSaveOnWayToMain == true){
					hideLoadWindow(src->loadWin);
					showMainWindow(src->mainWin);
					drawMainWindow(src->mainWin);
					src->activeWin = MAIN_WINDOW;
					src->prevWin= LOAD_WINDOW;
				}
		}
	} else if (event == LOAD_BACK) {
		hideLoadWindow(src->loadWin);
		if (src->prevWin == MAIN_WINDOW){
			if (src->mainWin != NULL){
				showMainWindow(src->mainWin);
				src->prevWin = LOAD_WINDOW;
				src->activeWin = MAIN_WINDOW;
			}
			else{
				printf("Couldn't find main window\n");
				return MANAGER_QUIT;
			}
		}

		else if (src->prevWin == GAME_WINDOW){
			if (src->gameWin != NULL){
				showGameWindow(src->gameWin);
				drawGameWindow(src->gameWin);
				src->prevWin = LOAD_WINDOW;
				src->activeWin = GAME_WINDOW;
				}
			else{
				printf("Couldn't find game window\n");
				return MANAGER_QUIT;
			}
		}
	} else if (event == LOAD_QUIT){
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}


MANAGER_EVENT handleManagerDueToSettingsEvent(ChessGuiManager* src, SETTINGS_EVENT event){
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == SETTINGS_NONE){
		return MANAGER_NONE;
	}
	CHCommand currCommand;
	if (event == SETTINGS_1_PLAYER){
		currCommand.cmd = CH_GAME_MODE;
    currCommand.validFirstArg = 1;
		currCommand.firstArg = 1;
	} else if (event == SETTINGS_2_PLAYERS){
		currCommand.cmd = CH_GAME_MODE;
    currCommand.validFirstArg = 1;
		currCommand.firstArg = 2;
	} else if (event == SETTINGS_AMAT){
		currCommand.cmd = CH_DIFFICULTY;
    currCommand.validFirstArg = 1;
		currCommand.firstArg = 1;
	} else if (event == SETTINGS_EASY){
		currCommand.cmd = CH_DIFFICULTY;
    currCommand.validFirstArg = 1;
		currCommand.firstArg = 2;
	} else if (event == SETTINGS_MODER){
		currCommand.cmd = CH_DIFFICULTY;
    currCommand.validFirstArg = 1;
		currCommand.firstArg = 3;
	} else if (event == SETTINGS_HARD){
		currCommand.cmd = CH_DIFFICULTY;
    currCommand.validFirstArg = 1;
		currCommand.firstArg = 4;
	} else if (event == SETTINGS_EXP){
		currCommand.cmd = CH_DIFFICULTY;
    currCommand.validFirstArg = 1;
		currCommand.firstArg = 5;
	} else if (event == SETTINGS_BLACK){
		currCommand.cmd = CH_USER_COLOR;
		currCommand.validFirstArg = 1;
		currCommand.firstArg = 0;
	} else if (event == SETTINGS_WHITE){
		currCommand.cmd = CH_USER_COLOR;
		currCommand.validFirstArg = 1;
		currCommand.firstArg = 1;
	} else if (event == SETTINGS_BACK){
		hideSettingsWindow(src->settingsWin);
		showMainWindow(src->mainWin);
		src->activeWin = MAIN_WINDOW;
		src->prevWin = SETTINGS_WINDOW;
    return MANAGER_NONE;
	} else if (event == SETTINGS_START){
		if (src->gameWin != NULL){
			src->activeWin = GAME_WINDOW;
			src->prevWin = SETTINGS_WINDOW;
			hideSettingsWindow(src->settingsWin);
			showGameWindow(src->gameWin);
			if (src->gameWin->game->numOfPlayers == 1 && src->gameWin->game->userColor == 0){
				makeComputerMove(src->gameWin->game);
			}
			drawGameWindow(src->gameWin);
		}
    return MANAGER_NONE;
	}
	else if (event == SETTINGS_QUIT){
		return MANAGER_QUIT;
	}
	settingsActions(src->gameWin->game, currCommand);
	return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToGameEvent(ChessGuiManager* src, GAME_EVENT event){
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == GAME_NONE){
		return MANAGER_NONE;
	} else if (event == GAME_MAIN){
		if (src->gameWin->isGameSaved == false){
			const SDL_MessageBoxButtonData buttons[] = {
				        { /* .flags, .buttonid, .text */        0, 0, "Cancel" },
				        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" },
				        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "No" },
				    };
		const SDL_MessageBoxColorScheme colorScheme = {
			{ /* .colors (.r, .g, .b) */
				/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
				{ 255,   255,   255 },
				/* [SDL_MESSAGEBOX_COLOR_TEXT] */
				{ 0,   0,   100 },
				/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
				{ 0,   0,   100 },
				/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
				{   255,  255,  255 },
				/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
				{ 0,   0,  0 }
			}
		};
		const SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			"Your game is in danger!", /* .title */
			"Would you like to save your game?", /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
		};
		int buttonid;
		if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
			SDL_Log("error displaying message box");
			return 1;
		}
		if (buttonid == -1) {
			SDL_Log("no selection");
		}
		else{
			//"Cancel"
			if (buttonid == 0){
				drawGameWindow(src->gameWin);
				return MANAGER_NONE;
			//"Yes"
			} else if (buttonid == 1){
				src->isSaveOnWayToMain = true;
				hideGameWindow(src->gameWin);
				if (src->loadWin == NULL){
					src->loadWin = createLoadWindow();
					if (src->loadWin == NULL){
						free(src);
						return MANAGER_QUIT;
					}
				}
				src->loadWin->isLoadWindow = false;
				src->activeWin = LOAD_WINDOW;
				src->prevWin = GAME_WINDOW;
				showLoadWindow(src->loadWin);
				src->gameWin->isGameSaved = true;
				return MANAGER_NONE;
			} else if (buttonid == 2){
				//"No"
				hideGameWindow(src->gameWin);
				if (src->loadWin != NULL){
					hideLoadWindow(src->loadWin);
				}
				if (src->settingsWin != NULL){
					hideSettingsWindow(src->settingsWin);
				}
				showMainWindow(src->mainWin);
				src->activeWin = MAIN_WINDOW;
				src->prevWin = GAME_WINDOW;
				return MANAGER_NONE;
			}

		}
		}
			//Game is already saved
			hideGameWindow(src->gameWin);

			if (src->loadWin != NULL){
				hideLoadWindow(src->loadWin);
			}		
			if (src->settingsWin != NULL){
				hideSettingsWindow(src->settingsWin);
			}	
			showMainWindow(src->mainWin);
			src->activeWin = MAIN_WINDOW;
			src->prevWin = GAME_WINDOW;
	} else if (event == GAME_SAVE){
		hideGameWindow(src->gameWin);
		if (src->loadWin == NULL){
			src->loadWin = createLoadWindow();
			if (src->loadWin == NULL){
				free(src);
				return MANAGER_QUIT;
			}
		}
		src->loadWin->isLoadWindow = false;
		src->activeWin = LOAD_WINDOW;
		src->prevWin = GAME_WINDOW;
		showLoadWindow(src->loadWin);
		src->gameWin->isGameSaved = true;

	} else if (event == GAME_LOAD){
		hideGameWindow(src->gameWin);
		if (src->loadWin == NULL){
			src->loadWin = createLoadWindow();
			if (src->loadWin == NULL){
				free(src);
				return MANAGER_QUIT;
			}
		}
		src->loadWin->isLoadWindow = true;
		src->activeWin = LOAD_WINDOW;
		src->prevWin = GAME_WINDOW;
		showLoadWindow(src->loadWin);
	} else if (event == GAME_UNDO){
		CHCommand currCommand;
		currCommand.cmd = CH_UNDO_MOVE;
		gameActions(src->gameWin->game, currCommand);
		drawManager(src);
	} else if (event == GAME_RESTART){
		int userColor = src->gameWin->game->userColor;
		int difficulty = src->gameWin->game->difficulty;
		int currentPlayer = src->gameWin->game->currentPlayer;
		int numOfPlayers = src->gameWin->game->numOfPlayers;
		ChessGameDestroy(src->gameWin->game);
		src->gameWin->isGameSaved = true;
		src->gameWin->game = ChessGameCreate();
		src->gameWin->game->userColor = userColor;
		src->gameWin->game->difficulty = difficulty;
		src->gameWin->game->numOfPlayers = numOfPlayers;
		src->gameWin->game->currentPlayer = currentPlayer;
		drawManager(src);
	} else if (event == GAME_WHITE_CHECKED){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!",
															"White King is threatened", NULL );
	} else if (event == GAME_BLACK_CHECKED){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!",
															"Black King is threatened", NULL );
	} else if (event == GAME_TIE){
		const SDL_MessageBoxButtonData buttons[] = {
						        { /* .flags, .buttonid, .text */        0, 0, "Restart Game" },
						        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Quit Game" },
						        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Main Menu" },
						    };
				const SDL_MessageBoxColorScheme colorScheme = {
				{ /* .colors (.r, .g, .b) */
								/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
								{ 255,   255,   255 },
								/* [SDL_MESSAGEBOX_COLOR_TEXT] */
								{ 0,   0,   100 },
								/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
								{ 0,   0,   100 },
								/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
								{   255,  255,  255 },
								/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
								{ 0,   0,  0 }
							}
				};
				const SDL_MessageBoxData messageboxdata = {
					SDL_MESSAGEBOX_INFORMATION, /* .flags */
					NULL, /* .window */
					"It's a tie!", /* .title */
					"What would you like to do next?", /* .message */
					SDL_arraysize(buttons), /* .numbuttons */
					buttons, /* .buttons */
					&colorScheme /* .colorScheme */
				};
				int buttonid;
				if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
					SDL_Log("error displaying message box");
					return 1;
				}
				if (buttonid == -1) {
					SDL_Log("no selection");
				}
				else{
					//Restart Game
					if (buttonid == 0){
						return handleManagerDueToGameEvent(src, GAME_RESTART);
					//Quit Game
					} else if (buttonid == 1){
						return handleManagerDueToGameEvent(src, GAME_QUIT);
					//Main Menu
					} else if (buttonid == 2){
						src->gameWin->isGameSaved = true;
						return handleManagerDueToGameEvent(src, GAME_MAIN);
					}
				}
	} else if (event == GAME_WHITE_WON){
		const SDL_MessageBoxButtonData buttons[] = {
								        { /* .flags, .buttonid, .text */        0, 0, "Restart Game" },
								        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Quit Game" },
								        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Main Menu" },
								    };
						const SDL_MessageBoxColorScheme colorScheme = {
						{ /* .colors (.r, .g, .b) */
										/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
										{ 255,   255,   255 },
										/* [SDL_MESSAGEBOX_COLOR_TEXT] */
										{ 0,   0,   100 },
										/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
										{ 0,   0,   100 },
										/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
										{   255,  255,  255 },
										/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
										{ 0,   0,  0 }
									}
						};
						const SDL_MessageBoxData messageboxdata = {
							SDL_MESSAGEBOX_INFORMATION, /* .flags */
							NULL, /* .window */
							"White player won!", /* .title */
							"What would you like to do next?", /* .message */
							SDL_arraysize(buttons), /* .numbuttons */
							buttons, /* .buttons */
							&colorScheme /* .colorScheme */
						};
						int buttonid;
						if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
							SDL_Log("error displaying message box");
							return 1;
						}
						if (buttonid == -1) {
							SDL_Log("no selection");
						}
						else{
							//Restart Game
							if (buttonid == 0){
								return handleManagerDueToGameEvent(src, GAME_RESTART);
							//Quit Game
							} else if (buttonid == 1){
								return handleManagerDueToGameEvent(src, GAME_QUIT);
							//Main Menu
							} else if (buttonid == 2){
								src->gameWin->isGameSaved = true;
								return handleManagerDueToGameEvent(src, GAME_MAIN);
							}
						}
	} else if (event == GAME_BLACK_WON){
		const SDL_MessageBoxButtonData buttons[] = {
								        { /* .flags, .buttonid, .text */        0, 0, "Restart Game" },
								        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Quit Game" },
								        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Main Menu" },
								    };
						const SDL_MessageBoxColorScheme colorScheme = {
						{ /* .colors (.r, .g, .b) */
										/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
										{ 255,   255,   255 },
										/* [SDL_MESSAGEBOX_COLOR_TEXT] */
										{ 0,   0,   100 },
										/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
										{ 0,   0,   100 },
										/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
										{   255,  255,  255 },
										/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
										{ 0,   0,  0 }
									}
						};
						const SDL_MessageBoxData messageboxdata = {
							SDL_MESSAGEBOX_INFORMATION, /* .flags */
							NULL, /* .window */
							"Black player won!", /* .title */
							"What would you like to do next?", /* .message */
							SDL_arraysize(buttons), /* .numbuttons */
							buttons, /* .buttons */
							&colorScheme /* .colorScheme */
						};
						int buttonid;
						if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
							SDL_Log("error displaying message box");
							return 1;
						}
						if (buttonid == -1) {
							SDL_Log("no selection");
						}
						else{
							//Restart Game
							if (buttonid == 0){
								return handleManagerDueToGameEvent(src, GAME_RESTART);
							//Quit Game
							} else if (buttonid == 1){
								return handleManagerDueToGameEvent(src, GAME_QUIT);
							//Main Menu
							} else if (buttonid == 2){
								src->gameWin->isGameSaved = true;
								return handleManagerDueToGameEvent(src, GAME_MAIN);
							}
						}
	} else if (event == GAME_QUIT){
		return MANAGER_QUIT;
	}

	return MANAGER_NONE;
}


MANAGER_EVENT handleManagerEvent(ChessGuiManager* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return MANAGER_NONE;
	}
	if (src->activeWin == MAIN_WINDOW) {
		MAIN_EVENT mainEvent = handleMainWindowEvent(src->mainWin, event);
		return handleManagerDueToMainEvent(src, mainEvent);
	}

	if (src->activeWin == SETTINGS_WINDOW) {
		SETTINGS_EVENT settingsEvent = handleSettingsWindowEvent(src->settingsWin, event);
		return handleManagerDueToSettingsEvent(src, settingsEvent);
	}
	if (src->activeWin == LOAD_WINDOW) {
		LOAD_EVENT loadEvent = handleLoadWindowEvent(src->loadWin, event);
		return handleManagerDueToLoadEvent(src, loadEvent);
	}

	if (src->activeWin == GAME_WINDOW) {
		GAME_EVENT gameEvent = handleGameWindowEvent(src->gameWin, event);
		return handleManagerDueToGameEvent(src, gameEvent);
	}

	return MANAGER_NONE;
}
