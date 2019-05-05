#include <stdlib.h>
#include <stdio.h>


#include "ChessLoadWindow.h"

//Inner functions

bool isFileEmpty(char* filePath){
	FILE *fp;
	long size;
	fp = fopen(filePath, "r");
	if(fp){
		fseek (fp, 0, SEEK_END);
		size = ftell(fp);
		if (size == 0){
			return true;
		}
		fclose(fp);
	}
	return false;
}

int isClickOnSlot1(int x, int y) {
	int maxX = BUTTONS_X + BUTTON_WIDTH;
	int maxY = SLOT_1_Y + BUTTON_HEIGHT;
	if ((x >= BUTTONS_X && x <= maxX) && (y >= SLOT_1_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot2(int x, int y) {
	int maxX = BUTTONS_X + BUTTON_WIDTH;
	int maxY = SLOT_2_Y + BUTTON_HEIGHT;
	if ((x >= BUTTONS_X && x <= maxX) && (y >= SLOT_2_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot3(int x, int y) {
	int maxX = BUTTONS_X + BUTTON_WIDTH;
	int maxY = SLOT_3_Y + BUTTON_HEIGHT;
	if ((x >= BUTTONS_X && x <= maxX) && (y >= SLOT_3_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot4(int x, int y) {
	int maxX = BUTTONS_X + BUTTON_WIDTH;
	int maxY = SLOT_4_Y + BUTTON_HEIGHT;
	if ((x >= BUTTONS_X && x <= maxX) && (y >= SLOT_4_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot5(int x, int y) {
	int maxX = BUTTONS_X + BUTTON_WIDTH;
	int maxY = SLOT_5_Y + BUTTON_HEIGHT;
	if ((x >= BUTTONS_X && x <= maxX) && (y >= SLOT_5_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}

int isClickOnBackL(int x, int y) {
	int maxX = BACK_X + BACK_BTN_WIDTH;
	int maxY = BACK_Y + BACK_BTN_HEIGHT;
	if ((x >= BACK_X && x <= maxX) && (y >= BACK_Y && y <= maxY)) {
		return 1;
	}
	return 0;
}


ChessLoadWin* createLoadWindow() {
	ChessLoadWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (ChessLoadWin*) calloc(sizeof(ChessLoadWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}
	//check slots
	res->isSlot1Enabled = !(isFileEmpty(FILE_PATH_1));
	res->isSlot2Enabled = !(isFileEmpty(FILE_PATH_2));
	res->isSlot3Enabled = !(isFileEmpty(FILE_PATH_3));
	res->isSlot4Enabled = !(isFileEmpty(FILE_PATH_4));
	res->isSlot5Enabled = !(isFileEmpty(FILE_PATH_5));
	res->isLoadWindow = true;
	// Create an application window with the following settings:
	res->win = SDL_CreateWindow("Chess Load Window", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			WIN_WIDTH,                               // width, in pixels
			WIN_HEIGHT,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->win == NULL ) {
		destroyLoadWindow(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->winRenderer = SDL_CreateRenderer(res->win, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->winRenderer == NULL ) {
		// In the case that the window could not be made...
		destroyLoadWindow(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//Create slot buttons
	//create slot1 button
	loadingSurface = SDL_LoadBMP(SLOT_1_IMAGE);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot1.bmp surface\n");
		return NULL ;
	}
	res->slot1Texture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot1Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot1 enabled button
	loadingSurface = SDL_LoadBMP(SLOT_1_IMAGE_E);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot1.bmp surface\n");
		return NULL ;
	}
	res->slot1TextureE = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot1TextureE == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot1E.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot2 button
	loadingSurface = SDL_LoadBMP(SLOT_2_IMAGE);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot2.bmp surface\n");
		return NULL ;
	}
	res->slot2Texture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot2Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot2.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot2 enabled button
	loadingSurface = SDL_LoadBMP(SLOT_2_IMAGE_E);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot2E.bmp surface\n");
		return NULL ;
	}
	res->slot2TextureE = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot2TextureE == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot2E.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot3 button
	loadingSurface = SDL_LoadBMP(SLOT_3_IMAGE);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot3.bmp surface\n");
		return NULL ;
	}
	res->slot3Texture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot3Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot3.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot3 enabled button
	loadingSurface = SDL_LoadBMP(SLOT_3_IMAGE_E);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot3E.bmp surface\n");
		return NULL ;
	}
	res->slot3TextureE = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot3TextureE == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot3E.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot4 button
	loadingSurface = SDL_LoadBMP(SLOT_4_IMAGE);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot4.bmp surface\n");
		return NULL ;
	}
	res->slot4Texture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot4Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot4.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot4 enabled button
	loadingSurface = SDL_LoadBMP(SLOT_4_IMAGE_E);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot4E.bmp surface\n");
		return NULL ;
	}
	res->slot4TextureE = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot4TextureE == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot4E.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot5 button
	loadingSurface = SDL_LoadBMP(SLOT_5_IMAGE);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot5.bmp surface\n");
		return NULL ;
	}
	res->slot5Texture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot5Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot5.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	//create slot5 enabled button
	loadingSurface = SDL_LoadBMP(SLOT_5_IMAGE_E);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create slot5E.bmp surface\n");
		return NULL ;
	}
	res->slot5TextureE = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->slot5TextureE == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create slot5E.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//create back button
	loadingSurface = SDL_LoadBMP(BACK);
	if (loadingSurface == NULL ) {
		destroyLoadWindow(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->winRenderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		destroyLoadWindow(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);


	return res;
}


void destroyLoadWindow(ChessLoadWin* src) {
	if (!src) {
		return;
	}
	if (src->slot1Texture != NULL ) {
		SDL_DestroyTexture(src->slot1Texture);
	}
	if (src->slot1TextureE != NULL ){
		SDL_DestroyTexture(src->slot1TextureE);
	}
	if (src->slot2Texture != NULL ) {
		SDL_DestroyTexture(src->slot2Texture);
	}
	if (src->slot2TextureE != NULL ) {
		SDL_DestroyTexture(src->slot2TextureE);
	}
	if (src->slot3Texture != NULL ){
		SDL_DestroyTexture(src->slot3Texture);
	}
	if (src->slot3TextureE != NULL ){
		SDL_DestroyTexture(src->slot3TextureE);
	}
	if (src->slot4Texture != NULL ){
		SDL_DestroyTexture(src->slot4Texture);
	}
	if (src->slot4TextureE != NULL ){
		SDL_DestroyTexture(src->slot4TextureE);
	}
	if (src->slot5Texture != NULL ){
		SDL_DestroyTexture(src->slot5Texture);
	}
	if (src->slot5TextureE != NULL ){
		SDL_DestroyTexture(src->slot5TextureE);
	}
	if (src->backTexture != NULL ){
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->winRenderer != NULL ) {
		SDL_DestroyRenderer(src->winRenderer);
	}
	if (src->win != NULL ) {
		SDL_DestroyWindow(src->win);
	}
	free(src);
}

void drawLoadWindow(ChessLoadWin* src) {
	if(src==NULL){
		return;
	}
	//Creating the rectangles
	SDL_Rect slot1R = { .x = BUTTONS_X, .y = SLOT_1_Y, .h = BUTTON_HEIGHT, .w = BUTTON_WIDTH };
	SDL_Rect slot2R = { .x = BUTTONS_X, .y = SLOT_2_Y, .h = BUTTON_HEIGHT, .w = BUTTON_WIDTH};
	SDL_Rect slot3R = { .x = BUTTONS_X, .y = SLOT_3_Y, .h = BUTTON_HEIGHT, .w = BUTTON_WIDTH};
	SDL_Rect slot4R = { .x = BUTTONS_X, .y = SLOT_4_Y, .h = BUTTON_HEIGHT, .w = BUTTON_WIDTH};
	SDL_Rect slot5R = { .x = BUTTONS_X, .y = SLOT_5_Y, .h = BUTTON_HEIGHT, .w = BUTTON_WIDTH};
	SDL_Rect backR = { .x = BACK_X, .y = BACK_Y, .h = BACK_BTN_HEIGHT, .w = BACK_BTN_WIDTH};

	SDL_SetRenderDrawColor(src->winRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->winRenderer);
	if (src->isSlot1Enabled == true){
		SDL_RenderCopy(src->winRenderer, src->slot1TextureE, NULL, &slot1R);
	}
	else{
	SDL_RenderCopy(src->winRenderer, src->slot1Texture, NULL, &slot1R);
	}
	if (src->isSlot2Enabled == true){
		SDL_RenderCopy(src->winRenderer, src->slot2TextureE, NULL, &slot2R);
	}
	else{
	SDL_RenderCopy(src->winRenderer, src->slot2Texture, NULL, &slot2R);
	}
	if (src->isSlot3Enabled == true){
		SDL_RenderCopy(src->winRenderer, src->slot3TextureE, NULL, &slot3R);
	}
	else{
	SDL_RenderCopy(src->winRenderer, src->slot3Texture, NULL, &slot3R);
	}
	if (src->isSlot4Enabled == true){
		SDL_RenderCopy(src->winRenderer, src->slot4TextureE, NULL, &slot4R);
	}
	else{
	SDL_RenderCopy(src->winRenderer, src->slot4Texture, NULL, &slot4R);
	}
	if (src->isSlot5Enabled == true){
		SDL_RenderCopy(src->winRenderer, src->slot5TextureE, NULL, &slot5R);
	}
	else{
	SDL_RenderCopy(src->winRenderer, src->slot5Texture, NULL, &slot5R);
	}
	//draw back button
	SDL_RenderCopy(src->winRenderer, src->backTexture, NULL, &backR);
	SDL_RenderPresent(src->winRenderer);
}


LOAD_EVENT handleLoadWindowEvent(ChessLoadWin* src, SDL_Event* event) {
	if (!event || !src) {
		return LOAD_INVALID;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnSlot1(event->button.x, event->button.y)) {
			return LOAD_SLOT1;
		} else if (isClickOnSlot2(event->button.x, event->button.y)) {
			return LOAD_SLOT2;
		} else if (isClickOnSlot3(event->button.x, event->button.y)) {
			return LOAD_SLOT3;
		} else if (isClickOnSlot4(event->button.x, event->button.y)) {
			return LOAD_SLOT4;
		} else if (isClickOnSlot5(event->button.x, event->button.y)) {
			return LOAD_SLOT5;
		}
		if (isClickOnBackL(event->button.x, event->button.y)){
			return LOAD_BACK;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return LOAD_QUIT;
		}
		break;
	default:
		return LOAD_NONE;
	}
	return LOAD_NONE;
}


void hideLoadWindow(ChessLoadWin* src) {
	SDL_HideWindow(src->win);
}

void showLoadWindow(ChessLoadWin* src) {
	SDL_ShowWindow(src->win);
}


