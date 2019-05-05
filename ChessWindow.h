#ifndef CHESSWINDOW_H_
#define CHESSWINDOW_H_
#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct chess_window_t ChessWin;
struct chess_window_t {
	SDL_Window* window;
	SDL_Renderer* renderer;
	void (*drawWindow)(ChessWin* src);
	void (*destroyWindow)(ChessWin* src);
};

void destroyWindow(ChessWin* src);

#endif
