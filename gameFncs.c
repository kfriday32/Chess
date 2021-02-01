// December 28, 2020
// gameFncs.c

#include "gameFncs.h"


// This function draws the chess board.
int drawBoard(SDL_Renderer *renderer, Gameboard *guiBoard)
{
    SDL_Rect square, area;
    int row, col, x = 0;

    SDL_RenderGetViewport(renderer, &area);

    guiBoard->location.x = 10;
    guiBoard->location.y = 10;

    for(row = 0; row < 8; row++) {
        
        for(col = 0; col < 8; col++) {
            // allow room for borders
            square.w = area.w / 10;
            square.h = area.h / 10;
            square.x = col * square.w + 10;
            square.y = row * square.h + 10;

            if ((col % 2 == 0 && row % 2 == 0) || (col % 2 == 1 && row % 2 == 1)) {
                SDL_SetRenderDrawColor(renderer, 0, 51, 102, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }

            SDL_RenderFillRect(renderer, &square);
        }
    }

    return square.w;
}


// This function loops the board until the user decides to quit.
int runGame(SDL_Event *event, SDL_Surface *surface, SDL_Renderer *renderer, 
            SDL_Window *window, int board[8][8], int colors[8][8])
{
    int pieceSize, player = 1, x, y;
    int xpos, ypos, clicked;

    Gameboard *guiBoard;
    guiBoard = malloc(sizeof(Gameboard));
    SDL_Rect area;

    TTF_Font *font = TTF_OpenFont("./fonts/sans.ttf", 72);
    if(!font) {
        printf("TTF Error: %s\n", TTF_GetError());
        TTF_Quit();
    }

    while(1) {
        SDL_PollEvent(event);
        if(event->type == SDL_QUIT) {
            return 1;
        }
        else if((event->type == SDL_WINDOWEVENT) && 
            event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            SDL_DestroyRenderer(renderer);
            surface = SDL_GetWindowSurface(window);
            renderer = SDL_CreateSoftwareRenderer(surface);
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderClear(renderer);
        }
        else if (event->type == SDL_MOUSEBUTTONDOWN) {
            SDL_RenderGetViewport(renderer, &area);
            SDL_GetMouseState(&x, &y);
            xpos = (x - 10) / (area.w / 10);
            ypos = (y - 10) / (area.h / 10);
            printf("Mouse click\n");
            printf("Coordinate: (%d, %d)\n", xpos, ypos);
            movePiece(xpos, ypos, board, colors, area);
            player = (player == 1) ? 2:1;
        }
        else if (event->type == SDL_MOUSEMOTION) {
            continue;
        }
       
        showText(player, surface, renderer, font);
        pieceSize = drawBoard(renderer, guiBoard);
        drawPieces(guiBoard, renderer, board, pieceSize, colors);
        SDL_UpdateWindowSurface(window);
        SDL_WaitEvent(event);
    }
}


// This function loads the chess pieces using the image files.
SDL_Texture * renderPiece(SDL_Renderer *renderer, char *path)
{
    SDL_Texture *texture;

    SDL_Surface *image = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return texture;
}


// This function draws the rendered pieces to the main board.
void drawPieces(Gameboard *guiBoard, SDL_Renderer *renderer, int board[8][8], int size,
                int colors[8][8])
{
    int row, col;
    SDL_Texture *pieceText;
    int x, y;
    
    guiBoard->blackRook = renderPiece(renderer, "./img/blackRook.png");
    guiBoard->whiteRook = renderPiece(renderer, "./img/whiteRook.png");
    guiBoard->blackBishop = renderPiece(renderer, "./img/blackBishop.png");
    guiBoard->whiteBishop = renderPiece(renderer, "./img/whiteBishop.png");
    guiBoard->blackKnight = renderPiece(renderer, "./img/blackKnight.png");
    guiBoard->whiteKnight = renderPiece(renderer, "./img/whiteKnight.png");
    guiBoard->blackKing = renderPiece(renderer, "./img/blackKing.png");
    guiBoard->whiteKing = renderPiece(renderer, "./img/whiteKing.png");
    guiBoard->blackQueen = renderPiece(renderer, "./img/blackQueen.png");
    guiBoard->whiteQueen = renderPiece(renderer, "./img/whiteQueen.png");
    guiBoard->blackPawn = renderPiece(renderer, "./img/blackPawn.png");
    guiBoard->whitePawn = renderPiece(renderer, "./img/whitePawn.png");

    for(row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
            switch (board[row][col]) {
                case pawn:
                    if (colors[row][col] == 1) {
                        pieceText = guiBoard->blackPawn;
                    }
                    else if (colors[row][col] == 2) { 
                        pieceText = guiBoard->whitePawn;
                    }
                    break;
                case rook:
                    if (colors[row][col] == 1) {
                        pieceText = guiBoard->blackRook;
                    }
                    else if (colors[row][col] == 2) {
                        pieceText = guiBoard->whiteRook;
                    }
                    break;
                case bishop:
                    if (colors[row][col] == 1) {
                        pieceText = guiBoard->blackBishop;
                    }
                    else if (colors[row][col] == 2) {
                        pieceText = guiBoard->whiteBishop;
                    }
                    break;
                case knight:
                    if (colors[row][col] == 1) {
                        pieceText = guiBoard->blackKnight;
                    }
                    else if (colors[row][col] == 2) {
                        pieceText = guiBoard->whiteKnight;
                    }
                    break;
                case king:
                    if (colors[row][col] == 1) {
                        pieceText = guiBoard->blackKing;
                    }
                    else if (colors[row][col] == 2) {
                        pieceText = guiBoard->whiteKing;
                    }
                    break;
                case queen:
                    if (colors[row][col] == 1) {
                        pieceText = guiBoard->blackQueen;
                    }
                    else if (colors[row][col] == 2) {
                        pieceText = guiBoard->whiteQueen;
                    }
                    break;
                default:
                    pieceText = NULL;
                    break;
            }
            
            x = guiBoard->location.x + col * size;
            y = guiBoard->location.y + row * size * 0.9;

            // copy piece texture to game surface
            SDL_Rect destText;
            destText.x = x;
            destText.y = y;
            destText.w = size;
            destText.h = size;

            SDL_RenderCopy(renderer, pieceText, NULL, &destText);
            SDL_RenderPresent(renderer);
        }
    }
}


// This function updates the pieces on the board by calling new moves.
void movePiece(int x, int y, int board[8][8], int colors[8][8], SDL_Rect area)
{
    SDL_Event *event;
    int xdest, ydest;
    int piece, color;
  
    while(SDL_WaitEvent(event)) { 
        SDL_PollEvent(event);
        if(event->type == SDL_QUIT) {
            return;
        }
        else if (event->type == SDL_MOUSEBUTTONUP) {
            SDL_GetMouseState(&xdest, &ydest);
            xdest = (xdest - 10) / (area.w / 10);
            ydest = (ydest - 10) / (area.h / 10);
            printf("Mouse release\n");
            printf("Coordinate: (%d, %d)\n", xdest, ydest);
           
            if (checkValid(x, y, xdest, ydest, board, colors)) {
                piece = board[y][x];
                color = colors[y][x];
                board[y][x] = 0;
                colors[y][x] = 0;
                board[ydest][xdest] = piece;
                colors[ydest][xdest] = color;
                return;
            }
        }
    }
}


// This function displays the text on the game.
void showText(int player, SDL_Surface *main, SDL_Renderer *renderer, TTF_Font *font)
{
    char text[20];
    SDL_Surface *textSurface;
    SDL_Rect dest, area;
    
    SDL_RenderGetViewport(renderer, &area);
    
    SDL_Color color = {0, 0, 0, 255};

    sprintf(text, "Player %d", player);
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);
    textSurface = TTF_RenderText_Solid(font, text, color);

    dest.w = 50;
    dest.h = 50;
    dest.x = 50;
    dest.y = area.h - 100;

    SDL_BlitSurface(textSurface, NULL, main, &dest);
}


// This function determines if a mood is valid.
int checkValid(int x, int y, int xd, int yd, int board[8][8], int colors[8][8])
{
    switch (board[y][x]) {
        case rook:
            break;
        case bishop:
            break;
        case knight:
            break;
        case queen:
            break;
        case king:
            break;
        case pawn:
            break;
        default:
            return 0; 
    }
    
    return 1;
}
