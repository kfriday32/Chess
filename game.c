// December 19, 2020
// game.c

#include "gameFncs.h"

int main()
{
    const int width = 1000;
    const int height = 900;

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *renderer;
    SDL_Event event;

    int board[8][8] = {{rook, knight, bishop, king, queen, bishop, knight, rook},
                       {pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn},
                       {rook, knight, bishop, king, queen, bishop, knight, rook}};

    int colors[8][8] = {{black, black, black, black, black, black, black, black},
                        {black, black, black, black, black, black, black, black},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {white, white, white, white, white, white, white, white},
                        {white, white, white, white, white, white, white, white}};

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    if(!(IMG_Init(IMG_INIT_PNG))) {
        printf("Error: %s\n", IMG_GetError());
        return -1;
    }

    if (TTF_Init() != 0) {
        printf("TTF Error: %s\n", TTF_GetError());
        return -1;
    }
    
    window = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(surface);
    if (!renderer) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    runGame(&event, surface, renderer, window, board, colors);
    SDL_DestroyWindow(window); 
    SDL_Quit();

    return 0;
}
