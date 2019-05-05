#include <stdlib.h>
#include <stdio.h>


#include "ChessSettingsWindow.h"

//Inner functions
int isClickOnOnePlayer(int x, int y) {
	int maxX = ONE_PLAYER_X + PLAYERS_BTN_WIDTH;
	int maxY = PLAYER_Y + PLAYERS_BTN_HEIGHT;
	if ((x >= ONE_PLAYER_X && x <= maxX) && (y >= PLAYER_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnTwoPlayers(int x, int y) {
	int maxX = TWO_PLAYERS_X + PLAYERS_BTN_WIDTH;
	int maxY = PLAYER_Y + PLAYERS_BTN_HEIGHT;
	if ((x >= TWO_PLAYERS_X && x <= maxX) && (y >= PLAYER_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnAmat(int x, int y) {
	int maxX = AMAT_X + SETTINGS_BTN_WIDTH;
	int maxY = DIFF_Y + SETTINGS_BTN_HEIGHT;
	if ((x >= AMAT_X && x <= maxX) && (y >= DIFF_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnEasy(int x, int y) {
	int maxX = EASY_X + SETTINGS_BTN_WIDTH;
	int maxY = DIFF_Y + SETTINGS_BTN_HEIGHT;
	if ((x >= EASY_X && x <= maxX) && (y >= DIFF_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnModer(int x, int y) {
	int maxX = MODER_X + SETTINGS_BTN_WIDTH;
	int maxY = DIFF_Y + SETTINGS_BTN_HEIGHT;
	if ((x >= MODER_X && x <= maxX) && (y >= DIFF_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnHard(int x, int y) {
	int maxX = HARD_X + SETTINGS_BTN_WIDTH;
	int maxY = DIFF_Y + SETTINGS_BTN_HEIGHT;
	if ((x >= HARD_X && x <= maxX) && (y >= DIFF_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnExp(int x, int y) {
	int maxX = EXP_X + SETTINGS_BTN_WIDTH;
	int maxY = DIFF_Y + SETTINGS_BTN_HEIGHT;
	if ((x >= EXP_X && x <= maxX) && (y >= DIFF_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnWhite(int x, int y) {
	int maxX = WHITE_X + COLOR_BTN_WIDTH;
	int maxY = COLOR_Y + COLOR_BTN_HEIGHT;
	if ((x >= WHITE_X && x <= maxX) && (y >= COLOR_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnBlack(int x, int y) {
	int maxX = BLACK_X + COLOR_BTN_WIDTH;
	int maxY = COLOR_Y + COLOR_BTN_HEIGHT;
	if ((x >= BLACK_X && x <= maxX) && (y >= COLOR_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnBackS(int x, int y) {
	int maxX = BACK_X + BACK_BTN_WIDTH;
	int maxY = BACK_Y + BACK_BTN_HEIGHT;
	if ((x >= BACK_X && x <= maxX) && (y >= BACK_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnStart(int x, int y) {
	int maxX = START_X + START_BTN_WIDTH;
	int maxY = START_Y + START_BTN_HEIGHT;
	if ((x >= START_X && x <= maxX) && (y >= START_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}
ChessSettingsWin* createSettingsWindow() {
	ChessSettingsWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (ChessSettingsWin*) calloc(sizeof(ChessSettingsWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	// Create an application window with the following settings:
	res->win = SDL_CreateWindow("Chess Settings Window", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			WIN_WIDTH,                               // width, in pixels
			WIN_HEIGHT,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->win == NULL ) {
		destroySettingsWindow(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->winRenderer = SDL_CreateRenderer(res->win, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->winRenderer == NULL ) {
		// In the case that the window could not be made...
		destroySettingsWindow(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//Create Game mode buttons
	//create one player button
	loadingSurface = SDL_LoadBMP(ONE_PLAYER);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create 1player.bmp surface\n");
		return NULL ;
	}
	res->onePlayerTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->onePlayerTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create 1player.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create one player active button
	loadingSurface = SDL_LoadBMP(ONE_PLAYER_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create 1playerA.bmp surface\n");
		return NULL ;
	}
	res->onePlayerTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->onePlayerTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create 1playerA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create two players button
	loadingSurface = SDL_LoadBMP(TWO_PLAYERS);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create twoplayers.bmp surface\n");
		return NULL ;
	}
	res->twoPlayersTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->twoPlayersTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create twoplayers.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create two players active button
	loadingSurface = SDL_LoadBMP(TWO_PLAYERS_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create twoplayersA.bmp surface\n");
		return NULL ;
	}
	res->twoPlayersTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->twoPlayersTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create twoplayersA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create game difficulty buttons
	//create amateur button
	loadingSurface = SDL_LoadBMP(AMAT);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create amat.bmp surface\n");
		return NULL ;
	}
	res->amatTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->amatTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create amat.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create amateur active button
	loadingSurface = SDL_LoadBMP(AMAT_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create amatA.bmp surface\n");
		return NULL ;
	}
	res->amatTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->amatTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create amatA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create easy button
	loadingSurface = SDL_LoadBMP(EASY);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create easy.bmp surface\n");
		return NULL ;
	}
	res->easyTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->easyTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create easy.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create easy active button
	loadingSurface = SDL_LoadBMP(EASY_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create easyA.bmp surface\n");
		return NULL ;
	}
	res->easyTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->easyTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create easyA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create moderate button
	loadingSurface = SDL_LoadBMP(MODER);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create moder.bmp surface\n");
		return NULL ;
	}
	res->moderTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->moderTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create moder.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create moderate active button
	loadingSurface = SDL_LoadBMP(MODER_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create moderA.bmp surface\n");
		return NULL ;
	}
	res->moderTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->moderTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create moderA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create hard button
	loadingSurface = SDL_LoadBMP(HARD);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create hard.bmp surface\n");
		return NULL ;
	}
	res->hardTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->hardTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create hard.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create hard active button
	loadingSurface = SDL_LoadBMP(HARD_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create hardA.bmp surface\n");
		return NULL ;
	}
	res->hardTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->hardTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create hardA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create expert button
	loadingSurface = SDL_LoadBMP(EXP);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create exp.bmp surface\n");
		return NULL ;
	}
	res->expTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->expTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create exp.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create expert active button
	loadingSurface = SDL_LoadBMP(EXP_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create expA.bmp surface\n");
		return NULL ;
	}
	res->expTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->expTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create expA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create color textures
	//create white button
	loadingSurface = SDL_LoadBMP(WHITE);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create white.bmp surface\n");
		return NULL ;
	}
	res->whiteTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->whiteTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create white.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create white active button
	loadingSurface = SDL_LoadBMP(WHITE_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create whiteA.bmp surface\n");
		return NULL ;
	}
	res->whiteTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->whiteTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create whiteA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create black button
	loadingSurface = SDL_LoadBMP(BLACK);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create black.bmp surface\n");
		return NULL ;
	}
	res->blackTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->blackTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create black.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create black active button
	loadingSurface = SDL_LoadBMP(BLACK_A);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create blackA.bmp surface\n");
		return NULL ;
	}
	res->blackTextureA = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->blackTextureA == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create blackA.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create start button
	loadingSurface = SDL_LoadBMP(START);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create start.bmp surface\n");
		return NULL ;
	}
	res->startTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->startTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create start.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create back active button
	loadingSurface = SDL_LoadBMP(BACK);
	if (loadingSurface == NULL ) {
		destroySettingsWindow(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroySettingsWindow(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);


	return res;
}



void destroySettingsWindow(ChessSettingsWin* src) {
	if (!src) {
		return;
	}
	if (src->onePlayerTexture != NULL ) {
		SDL_DestroyTexture(src->onePlayerTexture);
	}
	if (src->onePlayerTextureA != NULL ){
		SDL_DestroyTexture(src->onePlayerTextureA);
	}
	if (src->twoPlayersTexture != NULL ) {
		SDL_DestroyTexture(src->twoPlayersTexture);
	}
	if (src->twoPlayersTextureA != NULL ) {
		SDL_DestroyTexture(src->twoPlayersTextureA);
	}
	if (src->amatTexture != NULL ){
		SDL_DestroyTexture(src->amatTexture);
	}
	if (src->amatTextureA != NULL ){
		SDL_DestroyTexture(src->amatTextureA);
	}
	if (src->easyTexture != NULL ){
		SDL_DestroyTexture(src->easyTexture);
	}
	if (src->easyTextureA != NULL ){
		SDL_DestroyTexture(src->easyTextureA);
	}
	if (src->moderTexture != NULL ){
		SDL_DestroyTexture(src->moderTexture);
	}
	if (src->moderTextureA != NULL ){
		SDL_DestroyTexture(src->moderTextureA);
	}
	if (src->hardTexture != NULL ){
		SDL_DestroyTexture(src->hardTexture);
	}
	if (src->hardTextureA != NULL ){
		SDL_DestroyTexture(src->hardTextureA);
	}
	if (src->expTexture != NULL ){
		SDL_DestroyTexture(src->expTexture);
	}
	if (src->expTextureA != NULL ){
		SDL_DestroyTexture(src->expTextureA);
	}
	if (src->whiteTexture != NULL ){
		SDL_DestroyTexture(src->whiteTexture);
	}
	if (src->whiteTextureA != NULL ){
		SDL_DestroyTexture(src->whiteTextureA);
	}
	if (src->blackTexture != NULL ){
		SDL_DestroyTexture(src->blackTexture);
	}
	if (src->blackTextureA != NULL ){
		SDL_DestroyTexture(src->blackTextureA);
	}
	if (src->backTexture != NULL ){
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->startTexture != NULL){
		SDL_DestroyTexture(src->startTexture);
	}
	if (src->winRenderer != NULL ) {
		SDL_DestroyRenderer(src->winRenderer);
	}
	if (src->win != NULL ) {
		SDL_DestroyWindow(src->win);
	}
	free(src);
}

void drawSettingsWindow(ChessSettingsWin* src) {
	if(src==NULL){
		return;
	}
	//Creating the rectangles
	SDL_Rect onePlayerR = { .x = ONE_PLAYER_X, .y = PLAYER_Y, .h = PLAYERS_BTN_HEIGHT, .w = PLAYERS_BTN_WIDTH };
	SDL_Rect twoPlayersR = { .x = TWO_PLAYERS_X, .y = PLAYER_Y, .h = PLAYERS_BTN_HEIGHT, .w = PLAYERS_BTN_WIDTH};
	SDL_Rect amatR = { .x = AMAT_X, .y = DIFF_Y, .h = SETTINGS_BTN_HEIGHT, .w = SETTINGS_BTN_WIDTH};
	SDL_Rect easyR = { .x = EASY_X, .y = DIFF_Y, .h = SETTINGS_BTN_HEIGHT, .w = SETTINGS_BTN_WIDTH};
	SDL_Rect moderR = { .x = MODER_X, .y = DIFF_Y, .h = SETTINGS_BTN_HEIGHT, .w = SETTINGS_BTN_WIDTH};
	SDL_Rect hardR = { .x = HARD_X, .y = DIFF_Y, .h = SETTINGS_BTN_HEIGHT, .w = SETTINGS_BTN_WIDTH};
	SDL_Rect expR = { .x = EXP_X, .y = DIFF_Y, .h = SETTINGS_BTN_HEIGHT, .w = SETTINGS_BTN_WIDTH};
	SDL_Rect whiteR = { .x = WHITE_X, .y = COLOR_Y, .h = COLOR_BTN_HEIGHT, .w = COLOR_BTN_WIDTH};
	SDL_Rect blackR = { .x = BLACK_X, .y = COLOR_Y, .h = COLOR_BTN_HEIGHT, .w = COLOR_BTN_WIDTH};
	SDL_Rect backR = { .x = BACK_X, .y = BACK_Y, .h = BACK_BTN_HEIGHT, .w = BACK_BTN_WIDTH};
	SDL_Rect startR = { .x = START_X, .y = START_Y, .h = START_BTN_HEIGHT, .w = START_BTN_WIDTH};

	SDL_SetRenderDrawColor(src->winRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->winRenderer);
	if (src->isOnePlayerActive == true){
		SDL_RenderCopy(src->winRenderer, src->onePlayerTextureA, NULL, &onePlayerR);
	}
	else{
	SDL_RenderCopy(src->winRenderer, src->onePlayerTexture, NULL, &onePlayerR);
	}
	if (src->isTwoPlayersActive == true){
		SDL_RenderCopy(src->winRenderer, src->twoPlayersTextureA, NULL, &twoPlayersR);
	}
	else{
	SDL_RenderCopy(src->winRenderer, src->twoPlayersTexture, NULL, &twoPlayersR);
	}
	if (src->isOnePlayerActive == true){
		//draw difficulty level buttons
		if (src->isAmatActive == true){
			SDL_RenderCopy(src->winRenderer, src->amatTextureA, NULL, &amatR);
		}
		else{
			SDL_RenderCopy(src->winRenderer, src->amatTexture, NULL, &amatR);
		}
		if (src->isEasyActive == true){
			SDL_RenderCopy(src->winRenderer, src->easyTextureA, NULL, &easyR);
		}
		else{
			SDL_RenderCopy(src->winRenderer, src->easyTexture, NULL, &easyR);
		}
		if (src->isModerActive == true){
			SDL_RenderCopy(src->winRenderer, src->moderTextureA, NULL, &moderR);
		}
		else{
			SDL_RenderCopy(src->winRenderer, src->moderTexture, NULL, &moderR);
		}
		if (src->isHardActive == true){
			SDL_RenderCopy(src->winRenderer, src->hardTextureA, NULL, &hardR);
		}
		else{
			SDL_RenderCopy(src->winRenderer, src->hardTexture, NULL, &hardR);
		}
		if (src->isExpActive == true){
			SDL_RenderCopy(src->winRenderer, src->expTextureA, NULL, &expR);
		}
		else{
			SDL_RenderCopy(src->winRenderer, src->expTexture, NULL, &expR);
		}
		//draw color buttons
		if (src->isWhiteActive == true){
			SDL_RenderCopy(src->winRenderer, src->whiteTextureA, NULL, &whiteR);
		}
		else{
			SDL_RenderCopy(src->winRenderer, src->whiteTexture, NULL, &whiteR);
		}
		if (src->isBlackActive == true){
			SDL_RenderCopy(src->winRenderer, src->blackTextureA, NULL, &blackR);
		}
		else{
			SDL_RenderCopy(src->winRenderer, src->blackTexture, NULL, &blackR);
		}

	}
	//draw start button if it should be drawn
	if (src->isTwoPlayersActive == true || isOnePlayerComplete(src) == 1){
		SDL_RenderCopy(src->winRenderer, src->startTexture, NULL, &startR);
	}
	//draw back button
	SDL_RenderCopy(src->winRenderer, src->backTexture, NULL, &backR);
	SDL_RenderPresent(src->winRenderer);
}

int isOnePlayerComplete(ChessSettingsWin* src){
	if (src->isOnePlayerActive == true){
		if (src->isAmatActive == true || src->isEasyActive == true || src->isModerActive == true ||
				src->isHardActive == true || src->isExpActive == true){
			if (src->isBlackActive == true || src->isWhiteActive == true){
				return 1;
			}
		}
	}
	return 0;
}

SETTINGS_EVENT handleSettingsWindowEvent(ChessSettingsWin* src, SDL_Event* event) {
	if (!event) {
		return SETTINGS_INVALID;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnOnePlayer(event->button.x, event->button.y)) {
			src->isTwoPlayersActive = false;
			src->isOnePlayerActive = !(src->isOnePlayerActive);
			return SETTINGS_1_PLAYER;
		} else if (isClickOnTwoPlayers(event->button.x, event->button.y)) {
			src->isTwoPlayersActive = !(src->isTwoPlayersActive);
			src->isOnePlayerActive = false;
			return SETTINGS_2_PLAYERS;
		}
		if (src->isOnePlayerActive == true){
			if(isClickOnAmat(event->button.x, event->button.y)){
			src->isAmatActive = !(src->isAmatActive);
			src->isEasyActive = false;
			src->isModerActive = false;
			src->isHardActive = false;
			src->isExpActive = false;
			return SETTINGS_AMAT;
		} else if (isClickOnEasy(event->button.x, event->button.y)){
			src->isEasyActive = !(src->isEasyActive);
			src->isAmatActive = false;
			src->isModerActive = false;
			src->isHardActive = false;
			src->isExpActive = false;
			return SETTINGS_EASY;
		} else if (isClickOnModer(event->button.x, event->button.y)){
			src->isModerActive = !(src->isModerActive);
			src->isAmatActive = false;
			src->isEasyActive = false;
			src->isHardActive = false;
			src->isExpActive = false;
			return SETTINGS_MODER;
		} else if (isClickOnHard(event->button.x, event->button.y)){
			src->isHardActive = !(src->isHardActive);
			src->isAmatActive = false;
			src->isEasyActive = false;
			src->isModerActive = false;
			src->isExpActive = false;
			return SETTINGS_HARD;
		} else if (isClickOnExp(event->button.x, event->button.y)){
			src->isExpActive = !(src->isExpActive);
			src->isAmatActive = false;
			src->isEasyActive = false;
			src->isModerActive = false;
			src->isHardActive = false;
			return SETTINGS_EXP;
		} else if (isClickOnWhite(event->button.x, event->button.y)){
			src->isWhiteActive = !(src->isWhiteActive);
			src->isBlackActive = false;
			return SETTINGS_WHITE;
		} else if (isClickOnBlack(event->button.x, event->button.y)){
			src->isBlackActive = !(src->isBlackActive);
			src->isWhiteActive = false;
			return SETTINGS_BLACK;
		}
		}
		if (src->isTwoPlayersActive == true || isOnePlayerComplete(src)){
			if (isClickOnStart(event->button.x, event->button.y)){
				return SETTINGS_START;
			}
		}
		if (isClickOnBackS(event->button.x, event->button.y)){
			return SETTINGS_BACK;
		}

		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SETTINGS_QUIT;
		}
		break;
	default:
		return SETTINGS_NONE;
	}
	return SETTINGS_NONE;
}


void hideSettingsWindow(ChessSettingsWin* src) {
	SDL_HideWindow(src->win);
}

void showSettingsWindow(ChessSettingsWin* src) {
	SDL_ShowWindow(src->win);
}


