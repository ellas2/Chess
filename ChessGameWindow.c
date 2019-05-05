/*
 * CHgameWindow.c
 *
 *  Created on: Mar 12, 2018
 *      Author: Dubi
 */

#include "ChessGameWindow.h"
#include <assert.h>

#include <stdio.h>

int isClickOnRestart(int x, int y) {
	int maxX = BUTTONS_X_G + BUTTONS_WIDTH_G;
	int maxY = RESTART_Y + BUTTONS_HEIGHT_G;
	if ((x >= BUTTONS_X_G && x <= maxX) && (y >= RESTART_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnLoadGameWin(int x, int y) {
	int maxX = BUTTONS_X_G + BUTTONS_WIDTH_G;
	int maxY = LOAD_Y + BUTTONS_HEIGHT_G;
	if ((x >= BUTTONS_X_G && x <= maxX) && (y >= LOAD_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}
int isClickOnUndo(int x, int y) {
	int maxX = BUTTONS_X_G + BUTTONS_WIDTH_G;
	int maxY = UNDO_Y + BUTTONS_HEIGHT_G;
	if ((x >= BUTTONS_X_G && x <= maxX) && (y >= UNDO_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}


int isClickOnSave(int x, int y) {
	int maxX = BUTTONS_X_G + BUTTONS_WIDTH_G;
	int maxY = SAVE_Y + BUTTONS_HEIGHT_G;
	if ((x >= BUTTONS_X_G && x <= maxX) && (y >= SAVE_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnMain(int x, int y) {
	int maxX = BUTTONS_X_G + BUTTONS_WIDTH_G;
	int maxY = MAIN_Y + BUTTONS_HEIGHT_G;
	if ((x >= BUTTONS_X_G && x <= maxX) && (y >= MAIN_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnQuitGameWin(int x, int y) {
	int maxX = BUTTONS_X_G + BUTTONS_WIDTH_G;
	int maxY = QUIT_Y + BUTTONS_HEIGHT_G;
	if ((x >= BUTTONS_X_G && x <= maxX) && (y >= QUIT_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}


void destroyGameWindow(ChessGameWin* src) {
	if (!src) {
		return;
	}
	ChessGameDestroy(src->game);
	if (src->white_pawn_Texture != NULL ) {
		SDL_DestroyTexture(src->white_pawn_Texture);
	}
	if (src->black_pawn_Texture != NULL ) {
		SDL_DestroyTexture(src->black_pawn_Texture);
	}
	if (src->bgTexture != NULL ) {
		SDL_DestroyTexture(src->bgTexture);
	}
	if (src->black_knight_Texture != NULL){
		SDL_DestroyTexture(src->black_knight_Texture);
	}
	if (src->white_knight_Texture != NULL){
		SDL_DestroyTexture(src->white_knight_Texture);
	}
	if (src->black_rook_Texture != NULL){
			SDL_DestroyTexture(src->black_rook_Texture);
	}
	if (src->white_rook_Texture != NULL){
				SDL_DestroyTexture(src->white_rook_Texture);
	}
	if (src->black_bishop_Texture != NULL){
				SDL_DestroyTexture(src->black_bishop_Texture);
	}
	if (src->white_bishop_Texture != NULL){
				SDL_DestroyTexture(src->white_bishop_Texture);
	}
	if (src->black_king_Texture != NULL){
				SDL_DestroyTexture(src->black_king_Texture);
	}
	if (src->white_king_Texture != NULL){
				SDL_DestroyTexture(src->white_king_Texture);
	}
	if (src->black_queen_Texture != NULL){
				SDL_DestroyTexture(src->black_queen_Texture);
	}
	if (src->white_queen_Texture != NULL){
				SDL_DestroyTexture(src->white_queen_Texture);
	}
	if (src->restartTexture != NULL){
				SDL_DestroyTexture(src->restartTexture);
	}
	if (src->saveTexture != NULL){
				SDL_DestroyTexture(src->saveTexture);
	}
	if (src->loadTexture != NULL){
				SDL_DestroyTexture(src->loadTexture);
	}
	if (src->undoTexture != NULL){
				SDL_DestroyTexture(src->undoTexture);
	}
	if (src->mainTexture != NULL){
				SDL_DestroyTexture(src->mainTexture);
	}
	if (src->quitTexture != NULL){
				SDL_DestroyTexture(src->quitTexture);
	}
	if (src->yellow_square_Texture != NULL){
				SDL_DestroyTexture(src->yellow_square_Texture);
	}
	if (src->red_square_Texture != NULL){
				SDL_DestroyTexture(src->red_square_Texture);
	}
	if (src->purple_square_Texture != NULL){
				SDL_DestroyTexture(src->purple_square_Texture);
	}
	if (src->green_square_Texture != NULL){
				SDL_DestroyTexture(src->green_square_Texture);
	}
	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	free(src);
}

ChessGameWin* createGameWindow() {
	ChessGameWin* res = (ChessGameWin*) calloc(sizeof(ChessGameWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL ;
	}
	res->game = ChessGameCreate();
	if (res->game == NULL ) {
		printf("Couldn't create game\n");
		destroyGameWindow(res);
		return NULL ;
	}
	res->isGameSaved = true;
	// Create an application window with the following settings:
	res->window = SDL_CreateWindow("Chess", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			800,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->window == NULL ) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}

	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./images/grid.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//Create a texture for the black pawn symbol
	loadingSurface = SDL_LoadBMP("./images/black_pawn.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->black_pawn_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->black_pawn_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//Create a texture for the white knight symbol
	loadingSurface = SDL_LoadBMP("./images/white_knight.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->white_knight_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->white_knight_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the black knight symbol
	loadingSurface = SDL_LoadBMP("./images/black_knight.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->black_knight_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->black_knight_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for white pawn symbol
	loadingSurface = SDL_LoadBMP("./images/white_pawn.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->white_pawn_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->white_pawn_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white rook symbol
	loadingSurface = SDL_LoadBMP("./images/white_rook.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->white_rook_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->white_rook_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the black rook symbol
	loadingSurface = SDL_LoadBMP("./images/black_rook.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->black_rook_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->black_rook_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the black bishop symbol
	loadingSurface = SDL_LoadBMP("./images/black_bishop.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->black_bishop_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->black_bishop_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white bishop symbol
	loadingSurface = SDL_LoadBMP("./images/white_bishop.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->white_bishop_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->white_bishop_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white queen symbol
	loadingSurface = SDL_LoadBMP("./images/white_queen.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->white_queen_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->white_queen_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the black queen symbol
	loadingSurface = SDL_LoadBMP("./images/black_queen.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->black_queen_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->black_queen_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white king symbol
	loadingSurface = SDL_LoadBMP("./images/white_king.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->white_king_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->white_king_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the black king symbol
	loadingSurface = SDL_LoadBMP("./images/black_king.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->black_king_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->black_king_Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create restart button
	loadingSurface = SDL_LoadBMP("./images/restart.bmp");
	if (loadingSurface == NULL ) {
		destroyGameWindow(res);
		printf("couldn't create restart.bmp surface\n");
		return NULL ;
	}
	res->restartTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->restartTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyGameWindow(res);
		printf("couldn't create restart.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create save button
	loadingSurface = SDL_LoadBMP("./images/save.bmp");
	if (loadingSurface == NULL ) {
		destroyGameWindow(res);
		printf("couldn't create save.bmp surface\n");
		return NULL ;
	}
	res->saveTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->saveTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyGameWindow(res);
		printf("couldn't create save.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create load button
	loadingSurface = SDL_LoadBMP("./images/load.bmp");
	if (loadingSurface == NULL ) {
		destroyGameWindow(res);
		printf("couldn't create load.bmp surface\n");
		return NULL ;
	}
	res->loadTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->loadTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyGameWindow(res);
		printf("couldn't create load.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create undo button
	loadingSurface = SDL_LoadBMP("./images/undo.bmp");
	if (loadingSurface == NULL ) {
		destroyGameWindow(res);
		printf("couldn't create undo.bmp surface\n");
		return NULL ;
	}
	res->undoTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->undoTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyGameWindow(res);
		printf("couldn't create undo.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create main menu button
	loadingSurface = SDL_LoadBMP("./images/main.bmp");
	if (loadingSurface == NULL ) {
		destroyGameWindow(res);
		printf("couldn't create undo.bmp surface\n");
		return NULL ;
	}
	res->mainTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->mainTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyGameWindow(res);
		printf("couldn't create main.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create quit button
	loadingSurface = SDL_LoadBMP("./images/quit.bmp");
	if (loadingSurface == NULL ) {
		destroyGameWindow(res);
		printf("couldn't create quit.bmp surface\n");
		return NULL ;
	}
	res->quitTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->quitTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyGameWindow(res);
		printf("couldn't create quit.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//Create a texture for the purple square
		loadingSurface = SDL_LoadBMP("./images/purple_square.bmp");
		if (loadingSurface == NULL ) {
			printf("Could not create a surface: %s\n", SDL_GetError());
			destroyGameWindow(res);
			return NULL ;
		}
		//We use SetColorKey to make texture background transparent
		//This function will make the magenta background transparent
		SDL_SetColorKey(loadingSurface, SDL_TRUE,
				SDL_MapRGB(loadingSurface->format, 255, 255, 255));
		res->purple_square_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
		if (res->purple_square_Texture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(res);
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface);

		//Create a texture for the yellow square
		loadingSurface = SDL_LoadBMP("./images/yellow_square.bmp");
		if (loadingSurface == NULL ) {
			printf("Could not create a surface: %s\n", SDL_GetError());
			destroyGameWindow(res);
			return NULL ;
		}
		//We use SetColorKey to make texture background transparent
		//This function will make the magenta background transparent
		SDL_SetColorKey(loadingSurface, SDL_TRUE,
				SDL_MapRGB(loadingSurface->format, 255, 255, 255));
		res->yellow_square_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
		if (res->yellow_square_Texture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(res);
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface);

		//Create a texture for the red square
		loadingSurface = SDL_LoadBMP("./images/red_square.bmp");
		if (loadingSurface == NULL ) {
			printf("Could not create a surface: %s\n", SDL_GetError());
			destroyGameWindow(res);
			return NULL ;
		}
		//We use SetColorKey to make texture background transparent
		//This function will make the magenta background transparent
		SDL_SetColorKey(loadingSurface, SDL_TRUE,
				SDL_MapRGB(loadingSurface->format, 255, 255, 255));
		res->red_square_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
		if (res->red_square_Texture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(res);
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface);

		//Create a texture for the green square
		loadingSurface = SDL_LoadBMP("./images/green_square.bmp");
		if (loadingSurface == NULL ) {
			printf("Could not create a surface: %s\n", SDL_GetError());
			destroyGameWindow(res);
			return NULL ;
		}
		//We use SetColorKey to make texture background transparent
		//This function will make the magenta background transparent
		SDL_SetColorKey(loadingSurface, SDL_TRUE,
				SDL_MapRGB(loadingSurface->format, 255, 255, 255));
		res->green_square_Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
		if (res->green_square_Texture == NULL ) {
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(res);
			return NULL ;
		}
	SDL_FreeSurface(loadingSurface);
	return res;
}


void drawGameWindow(ChessGameWin* src) {

	if(src == NULL){
		return;
	}
	SDL_Rect rec = { .x = 0, .y = 0, .w = 600, .h = 600 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &rec);

	int i = 0, j = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			rec.x = j * 75;
			rec.y = 525 - i * 75;
			rec.h = 75;
			rec.w = 75;
			if (src->game->gameBoard[i][j] == 'm') {
				SDL_RenderCopy(src->renderer, src->white_pawn_Texture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == 'M') {
				SDL_RenderCopy(src->renderer, src->black_pawn_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'n')
			{
				SDL_RenderCopy(src->renderer, src->white_knight_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'N')
			{
				SDL_RenderCopy(src->renderer, src->black_knight_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'r')
			{
				SDL_RenderCopy(src->renderer, src->white_rook_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'R')
			{
				SDL_RenderCopy(src->renderer, src->black_rook_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'b')
			{
				SDL_RenderCopy(src->renderer, src->white_bishop_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'B')
			{
				SDL_RenderCopy(src->renderer, src->black_bishop_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'q')
			{
				SDL_RenderCopy(src->renderer, src->white_queen_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'Q')
			{
				SDL_RenderCopy(src->renderer, src->black_queen_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'k')
			{
				SDL_RenderCopy(src->renderer, src->white_king_Texture, NULL, &rec);
			}
			else if (src->game->gameBoard[i][j] == 'K')
			{
				SDL_RenderCopy(src->renderer, src->black_king_Texture, NULL, &rec);
			}
		}
	}

	SDL_Rect restartR = { .x = BUTTONS_X_G, .y = RESTART_Y, .w = BUTTONS_WIDTH_G, .h = BUTTONS_HEIGHT_G };
	SDL_Rect saveR = { .x = BUTTONS_X_G, .y = SAVE_Y, .w = BUTTONS_WIDTH_G, .h = BUTTONS_HEIGHT_G };
	SDL_Rect loadR = { .x = BUTTONS_X_G, .y = LOAD_Y, .w = BUTTONS_WIDTH_G, .h = BUTTONS_HEIGHT_G };
	SDL_Rect undoR = { .x = BUTTONS_X_G, .y = UNDO_Y, .w = BUTTONS_WIDTH_G, .h = BUTTONS_HEIGHT_G };
	SDL_Rect mainR = { .x = BUTTONS_X_G, .y = MAIN_Y, .w = BUTTONS_WIDTH_G, .h = BUTTONS_HEIGHT_G };
	SDL_Rect quitR = { .x = BUTTONS_X_G, .y = QUIT_Y, .w = BUTTONS_WIDTH_G, .h = BUTTONS_HEIGHT_G };


	SDL_RenderCopy(src->renderer, src->restartTexture, NULL, &restartR);
	SDL_RenderCopy(src->renderer, src->saveTexture, NULL, &saveR);
	SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
	SDL_RenderCopy(src->renderer, src->undoTexture, NULL, &undoR);
	SDL_RenderCopy(src->renderer, src->mainTexture, NULL, &mainR);
	SDL_RenderCopy(src->renderer, src->quitTexture, NULL, &quitR);

	SDL_RenderPresent(src->renderer);
}

GAME_EVENT handleGameWindowEvent(ChessGameWin* src, SDL_Event* event)
{
	if (event == NULL || src == NULL ) {
		return GAME_INVALID_ARGUMENT;
	}
	extern int move;
	extern int xDif;
	extern int yDif;
	extern char remember;
	extern int fromRow;
	extern int fromCol;
	extern SDL_Rect currRect;
	switch (event->type) {
		case SDL_WINDOWEVENT:
			if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
				return GAME_QUIT;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if ((event->button.x < 600) && (event->button.y < 600) && (event->button.button == SDL_BUTTON_LEFT))
			{
				fromRow = 7 - event->button.y / 75;
				fromCol = event->button.x / 75;
				char curChar = src->game->gameBoard[fromRow][fromCol];
				if (curChar == '_')
					return GAME_NONE;
				currRect.y = 525 - fromRow*75;
				currRect.x = fromCol*75;
				currRect.h = 75;
				currRect.w = 75;
				remember = curChar;
				src->game->gameBoard[fromRow][fromCol] = '_';
				xDif = event->button.x - currRect.x;
				yDif = event->button.y - currRect.y;
				move = 1;
			}
			else if ((event->button.x < 600) && (event->button.y < 600) && (event->button.button == SDL_BUTTON_RIGHT))
			{
				drawGameWindow(src);
				fromRow = 7 - event->button.y / 75;
				fromCol = event->button.x / 75;
				char curChar = src->game->gameBoard[fromRow][fromCol];
				if (curChar == '_')
					return GAME_NONE;
				getMovesGUI(src, fromRow, fromCol);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (move == 1)
			{
				int toRow = 7 - event->button.y / 75;
				int toCol = event->button.x / 75;
				src->game->gameBoard[fromRow][fromCol] = remember;
				CHCommand currCommand;
				currCommand.cmd = CH_PIECE_MOVE;
				currCommand.firstArg = fromRow + 1;
				currCommand.secondArg = fromCol + 'A';
				currCommand.thirdArg = toRow + 1;
				currCommand.fourthArg = toCol + 'A';
				currCommand.validFirstArg = 1;
				currCommand.validSecondArg = 1;
				currCommand.validThirdArg = 1;
				currCommand.validFourthArg = 1;
				CHESS_GAME_MESSAGE msg = gameActions(src->game, currCommand);
				if (msg == CHESS_GAME_SUCCESS || msg == CHESS_GAME_CHECK){
					src->isGameSaved = false;
				}
				drawGameWindow(src);
				move = 0;
				if (msg == CHESS_GAME_DRAW){
					return GAME_TIE;
				} else if (msg == CHESS_GAME_CHECKMATE){
					if (src->game->currentPlayer == 1){
						return GAME_BLACK_WON;
					}
					else{
						return GAME_WHITE_WON;
					}
				} else if (msg == CHESS_GAME_CHECK){
					if (src->game->currentPlayer == 1){
						return GAME_WHITE_CHECKED;
					}
					else{
						return GAME_BLACK_CHECKED;
					}
				}
			} else if (isClickOnRestart(event->button.x, event->button.y)){
				return GAME_RESTART;
			} else if(isClickOnUndo(event->button.x, event->button.y)){
				return GAME_UNDO;
			} else if(isClickOnLoadGameWin(event->button.x, event->button.y)){
				return GAME_LOAD;
			} else if(isClickOnSave(event->button.x, event->button.y)){
				return GAME_SAVE;
			} else if(isClickOnMain(event->button.x, event->button.y)){
				return GAME_MAIN;
			} else if(isClickOnQuitGameWin(event->button.x, event->button.y)){
				return GAME_QUIT;
			}
			break;
		case SDL_MOUSEMOTION:
			if (move && event->button.x <= 600 && event->button.y <= 600) {
				currRect.x = event->button.x - xDif;
				currRect.y = event->button.y - yDif;
				drawGameWindow(src);
				if (remember == 'm') {
					SDL_RenderCopy(src->renderer, src->white_pawn_Texture, NULL, &currRect);
				} else if (remember == 'M') {
					SDL_RenderCopy(src->renderer, src->black_pawn_Texture, NULL, &currRect);
				}
				else if (remember == 'n')
				{
					SDL_RenderCopy(src->renderer, src->white_knight_Texture, NULL, &currRect);
				}
				else if (remember == 'N')
				{
					SDL_RenderCopy(src->renderer, src->black_knight_Texture, NULL, &currRect);
				}
				else if (remember == 'r')
				{
					SDL_RenderCopy(src->renderer, src->white_rook_Texture, NULL, &currRect);
				}
				else if (remember == 'R')
				{
					SDL_RenderCopy(src->renderer, src->black_rook_Texture, NULL, &currRect);
				}
				else if (remember == 'b')
				{
					SDL_RenderCopy(src->renderer, src->white_bishop_Texture, NULL, &currRect);
				}
				else if (remember == 'B')
				{
					SDL_RenderCopy(src->renderer, src->black_bishop_Texture, NULL, &currRect);
				}
				else if (remember == 'q')
				{
					SDL_RenderCopy(src->renderer, src->white_queen_Texture, NULL, &currRect);
				}
				else if (remember == 'Q')
				{
					SDL_RenderCopy(src->renderer, src->black_queen_Texture, NULL, &currRect);
				}
				else if (remember == 'k')
				{
					SDL_RenderCopy(src->renderer, src->white_king_Texture, NULL, &currRect);
				}
				else if (remember == 'K')
				{
					SDL_RenderCopy(src->renderer, src->black_king_Texture, NULL, &currRect);
				}
				SDL_RenderPresent(src->renderer);
			}
			break;
		default:
			return GAME_NONE;
		}

	return GAME_NONE;
}


CHESS_GAME_MESSAGE getMovesGUI(ChessGameWin* src, int fromRow, int fromCol)
{
	if (src == NULL)
		return CHESS_GAME_INVALID_MOVE;

	CHESS_GAME_MESSAGE basicCheck = checkBasicCoord(src->game, fromRow, fromCol);
	if (basicCheck == CHESS_GAME_INVALID_ARGUMENT)
	{
		return CHESS_GAME_INVALID_ARGUMENT;
	}
	else if (basicCheck == CHESS_GAME_INVALID_PIECE)
	{
		return CHESS_GAME_INVALID_PIECE;
	}
	bool flagChangePlayer = false;
	if ((src->game->gameBoard[fromRow][fromCol] >= 'A' && src->game->gameBoard[fromRow][fromCol] <= 'Z' && src->game->currentPlayer == 1) ||
			(src->game->gameBoard[fromRow][fromCol] >= 'a' && src->game->gameBoard[fromRow][fromCol] <= 'z' && src->game->currentPlayer == 0)){
		flagChangePlayer = true;
		changePlayerChess(src->game);
	}
	for (int i = 0; i < CHESS_GAME_N_ROWS; i++)
	{
		for (int j = 0; j < CHESS_GAME_N_COLUMNS; j++)
		{
			if (ChessCheckPieceMove(src->game, fromRow, fromCol, i, j))
			{
				if (!isSafeMoveChess(src->game, fromRow, fromCol, i, j))
					continue;
				char backUpPiece = src->game->gameBoard[i][j];
				src->game->gameBoard[i][j] = src->game->gameBoard[fromRow][fromCol];
				src->game->gameBoard[fromRow][fromCol] = '_';
				SDL_Rect rec;
				rec.w = 75;
				rec.h = 75;
				rec.x = j*75;
				rec.y = 525 - i*75;
				if (isLocationThreatened(src->game, i, j))
				{
					if (backUpPiece != '_')
					{
						SDL_RenderCopy(src->renderer, src->purple_square_Texture, NULL, &rec);
						if (backUpPiece == 'm')
						{
							SDL_RenderCopy(src->renderer, src->white_pawn_Texture, NULL, &rec);
						} else if (backUpPiece == 'M') {
							SDL_RenderCopy(src->renderer, src->black_pawn_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'n')
						{
							SDL_RenderCopy(src->renderer, src->white_knight_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'N')
						{
							SDL_RenderCopy(src->renderer, src->black_knight_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'r')
						{
							SDL_RenderCopy(src->renderer, src->white_rook_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'R')
						{
							SDL_RenderCopy(src->renderer, src->black_rook_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'b')
						{
							SDL_RenderCopy(src->renderer, src->white_bishop_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'B')
						{
							SDL_RenderCopy(src->renderer, src->black_bishop_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'q')
						{
							SDL_RenderCopy(src->renderer, src->white_queen_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'Q')
						{
							SDL_RenderCopy(src->renderer, src->black_queen_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'k')
						{
							SDL_RenderCopy(src->renderer, src->white_king_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'K')
						{
							SDL_RenderCopy(src->renderer, src->black_king_Texture, NULL, &rec);
						}
					}
					else
					{
						SDL_RenderCopy(src->renderer, src->red_square_Texture, NULL, &rec);
					}
				}
				else
				{
					if (backUpPiece != '_')
					{
						SDL_RenderCopy(src->renderer, src->green_square_Texture, NULL, &rec);
						if (backUpPiece == 'm')
						{
							SDL_RenderCopy(src->renderer, src->white_pawn_Texture, NULL, &rec);
						} else if (backUpPiece == 'M') {
							SDL_RenderCopy(src->renderer, src->black_pawn_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'n')
						{
							SDL_RenderCopy(src->renderer, src->white_knight_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'N')
						{
							SDL_RenderCopy(src->renderer, src->black_knight_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'r')
						{
							SDL_RenderCopy(src->renderer, src->white_rook_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'R')
						{
							SDL_RenderCopy(src->renderer, src->black_rook_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'b')
						{
							SDL_RenderCopy(src->renderer, src->white_bishop_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'B')
						{
							SDL_RenderCopy(src->renderer, src->black_bishop_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'q')
						{
							SDL_RenderCopy(src->renderer, src->white_queen_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'Q')
						{
							SDL_RenderCopy(src->renderer, src->black_queen_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'k')
						{
							SDL_RenderCopy(src->renderer, src->white_king_Texture, NULL, &rec);
						}
						else if (backUpPiece == 'K')
						{
							SDL_RenderCopy(src->renderer, src->black_king_Texture, NULL, &rec);
						}
					}
					else
					{
						SDL_RenderCopy(src->renderer, src->yellow_square_Texture, NULL, &rec);
					}
				}
				src->game->gameBoard[fromRow][fromCol] = src->game->gameBoard[i][j];
				src->game->gameBoard[i][j] = backUpPiece;
			}
		}
	}
	if (flagChangePlayer)
		changePlayerChess(src->game);
	SDL_RenderPresent(src->renderer);
	return CHESS_GAME_SUCCESS;
}
void showGameWindow(ChessGameWin* src) {
	SDL_ShowWindow(src->window);
}

void hideGameWindow(ChessGameWin* src) {
	SDL_HideWindow(src->window);
}


