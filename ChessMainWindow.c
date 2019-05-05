#include <stdlib.h>
#include <stdio.h>

#include "ChessMainWindow.h"



//Inner functions
int isClickOnNew(int x, int y) {
	int maxX = BUTTONS_X_VAL + BUTTONS_WIDTH;
	int maxY = NEW_BUTTON_Y_VAL + BUTTONS_HEIGHT;
	if ((x >= BUTTONS_X_VAL && x <= maxX) && (y >= NEW_BUTTON_Y_VAL && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnLoad(int x, int y) {
	int maxX = BUTTONS_X_VAL + BUTTONS_WIDTH;
	int maxY = LOAD_BUTTON_Y_VAL + BUTTONS_HEIGHT;
	if ((x >= BUTTONS_X_VAL && x <= maxX) && (y >= LOAD_BUTTON_Y_VAL && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnQuit(int x, int y) {
	int maxX = BUTTONS_X_VAL + BUTTONS_WIDTH;
	if ((x >= BUTTONS_X_VAL && x <= maxX) && (y >= QUIT_BUTTON_Y_VAL && y <= QUIT_BUTTON_Y_VAL+BUTTONS_HEIGHT)) {
		return 1;
	}
	return 0;
}

ChessMainWin* createMainWindow() {
	ChessMainWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (ChessMainWin*) calloc(sizeof(ChessMainWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	// Create an application window with the following settings:
	res->win = SDL_CreateWindow("Chess Main Window", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			WIN_WIDTH,                               // width, in pixels
			WIN_HEIGHT,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->win == NULL ) {
		destroyMainWindow(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->winRenderer = SDL_CreateRenderer(res->win, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->winRenderer == NULL ) {
		// In the case that the window could not be made...
		destroyMainWindow(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}



	loadingSurface = SDL_LoadBMP(NEW_IMAGE);
	if (loadingSurface == NULL ) {
		destroyMainWindow(res);
		printf("couldn't create new.bmp surface\n");
		return NULL ;
	}
	res->newTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->newTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyMainWindow(res);
		printf("couldn't create new.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);


	loadingSurface = SDL_LoadBMP(LOAD_IMAGE);
		if (loadingSurface == NULL ) {
			destroyMainWindow(res);
			printf("couldn't create load.bmp surface\n");
			return NULL ;
		}
		res->loadTexture = SDL_CreateTextureFromSurface(res->winRenderer,
				loadingSurface);
		if (res->loadTexture == NULL ) {
			SDL_FreeSurface(loadingSurface);
			destroyMainWindow(res);
			printf("couldn't create load.bmp texture\n");
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP(QUIT_IMAGE);
	if (loadingSurface == NULL ) {
		destroyMainWindow(res);
		printf("couldn't create exit.bmp surface\n");
		return NULL ;
	}
	res->quitTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->quitTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyMainWindow(res);
		printf("couldn't create quit.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void destroyMainWindow(ChessMainWin* src) {
	if (!src) {
		return;
	}
	if (src->newTexture != NULL ) {
		SDL_DestroyTexture(src->newTexture);
	}
	if (src->loadTexture != NULL ) {
		SDL_DestroyTexture(src->loadTexture);
	}
	if (src->quitTexture != NULL ) {
		SDL_DestroyTexture(src->quitTexture);
	}
	if (src->winRenderer != NULL ) {
		SDL_DestroyRenderer(src->winRenderer);
	}
	if (src->win != NULL ) {
		SDL_DestroyWindow(src->win);
	}
	free(src);
}

void drawMainWindow(ChessMainWin* src) {
	if(src==NULL){
		return;
	}
	//Creating the rectangles
	SDL_Rect newR = { .x = BUTTONS_X_VAL, .y = NEW_BUTTON_Y_VAL, .h = BUTTONS_HEIGHT, .w = BUTTONS_WIDTH };
	SDL_Rect loadR = { .x = BUTTONS_X_VAL, .y = LOAD_BUTTON_Y_VAL, .h = BUTTONS_HEIGHT, .w = BUTTONS_WIDTH};
	SDL_Rect quitR = { .x = BUTTONS_X_VAL, .y = QUIT_BUTTON_Y_VAL, .h = BUTTONS_HEIGHT, .w = BUTTONS_WIDTH };

	SDL_SetRenderDrawColor(src->winRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->winRenderer);
	SDL_RenderCopy(src->winRenderer, src->newTexture, NULL, &newR);
	SDL_RenderCopy(src->winRenderer, src->loadTexture, NULL, &loadR);
	SDL_RenderCopy(src->winRenderer, src->quitTexture, NULL, &quitR);
	SDL_RenderPresent(src->winRenderer);
}

MAIN_EVENT handleMainWindowEvent(ChessMainWin* src, SDL_Event* event) {
	if (!event || !src) {
		return MAIN_INVALID;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnNew(event->button.x, event->button.y)) {
			return MAIN_NEW;
		} else if (isClickOnLoad(event->button.x, event->button.y)) {
			return MAIN_LOAD;
		} else if (isClickOnQuit(event->button.x, event->button.y)) {
			return MAIN_QUIT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_QUIT;
		}
		break;
	default:
		return MAIN_NONE;
	}
	return MAIN_NONE;
}

void hideMainWindow(ChessMainWin* src) {
	SDL_HideWindow(src->win);
}

void showMainWindow(ChessMainWin* src) {
	SDL_ShowWindow(src->win);
}
