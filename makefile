game: game.o gameFncs.o
	gcc game.o gameFncs.o -I/usr/include/SDL2 -o game -lSDL2 -lSDL2_image -lSDL2_ttf

game.o: game.c gameFncs.h
	gcc -c game.c -o game.o

gameFncs.o: gameFncs.c gameFncs.h
	gcc -c gameFncs.c -o gameFncs.o

clean:
	rm game

