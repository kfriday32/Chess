// gameFncs.h
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef enum piece {pawn = 1, rook, knight, bishop, king, queen} Piece;
typedef enum {black = 1, white} Color;

typedef struct {
    int x;
    int y;
} SquareLoc;

typedef struct {
    SDL_Texture *whitePawn;
    SDL_Texture *whiteRook;
    SDL_Texture *whiteBishop;
    SDL_Texture *whiteKnight;
    SDL_Texture *whiteKing;
    SDL_Texture *whiteQueen;
    SDL_Texture *blackPawn;
    SDL_Texture *blackRook;
    SDL_Texture *blackBishop;
    SDL_Texture *blackKnight;
    SDL_Texture *blackKing;
    SDL_Texture *blackQueen;
    SquareLoc location;
} Gameboard;

int drawBoard(SDL_Renderer *, Gameboard *);
int runGame(SDL_Event *, SDL_Surface *, SDL_Renderer *, SDL_Window *, int [8][8],
            int [8][8]);
SDL_Texture * renderPiece(SDL_Renderer *i, char *);
void drawPieces(Gameboard *, SDL_Renderer *, int [8][8], int, int [8][8]);
void movePiece(int, int, int [8][8], int [8][8], SDL_Rect);
void showText(int, SDL_Surface *, SDL_Renderer *, TTF_Font *);
int checkValid(int x, int y, int xd, int yd, int [8][8], int [8][8]);
