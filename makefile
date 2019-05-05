CC = gcc
OBJS = main.o ChessGUIManager.o ChessSettingsWindow.o ChessGameWindow.o ChessLoadWindow.o ChessMainWindow.o CHAux.o CHMinimax.o ChessGame.o CHMovesHistory.o CHParser.o
EXEC = chessprog
COMP_FLAG = -std=c99 -g -Wall -Wextra \
-Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

all: $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o chessprog
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
CHParser.o: CHParser.c CHParser.h
	$(CC) $(COMP_FLAG) -c $*.c
CHMovesHistory.o: CHMovesHistory.c CHMovesHistory.h
	$(CC) $(COMP_FLAG) -c $*.c
ChessGame.o: ChessGame.c ChessGame.h CHMovesHistory.h
	$(CC) $(COMP_FLAG) -c $*.c	
CHMinimax.o: CHMinimax.c CHMinimax.h ChessGame.h
	$(CC) $(COMP_FLAG) -c $*.c
CHAux.o: CHAux.c CHAux.h CHMinimax.h CHParser.h
	$(CC) $(COMP_FLAG) -c $*.c
#ChessWindow.o: ChessWindow.h
#	$(CC) $(COMP_FLAG) 
ChessMainWindow.o: ChessMainWindow.c ChessMainWindow.h ChessWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessLoadWindow.o: ChessLoadWindow.c ChessLoadWindow.h ChessWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessSettingsWindow.o: ChessSettingsWindow.c ChessSettingsWindow.h ChessWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGameWindow.o: ChessGameWindow.c ChessGameWindow.h CHAux.h ChessWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGUIManager.o: ChessGUIManager.c ChessGUIManager.h ChessGameWindow.h ChessSettingsWindow.h ChessMainWindow.h ChessLoadWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
main.o: main.c ChessGUIManager.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) 