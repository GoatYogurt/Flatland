#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "include/game.h"
#include "include/SDL_utils.h"

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if ( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

/*
void renderTexture(SDL_Renderer* renderer, SDL_Texture* textureToDisplay)
{
    SDL_RenderCopy(renderer, textureToDisplay, NULL, NULL);
}
*/

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const string &WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(cout, "SDL_Init", true);
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quit_(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(dieSound);
    Mix_FreeChunk(walkingSound);
}

/**code cua co*/
/*void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}*/

/**code vong lap game tu lazyfoo
SDL_Event e;
bool quit = false;
while( quit == false )
{
    while( SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_QUIT ) quit = true;
    }
}*/
