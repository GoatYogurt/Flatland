#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const string &WINDOW_TITLE);
void logSDLError(ostream& os, const string &msg, bool fatal = false);
void quit_(SDL_Window* window, SDL_Renderer* renderer);
//void waitUntilKeyPressed();
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);
void renderTexture(SDL_Renderer* renderer, SDL_Texture* textureToDisplay);

#endif // SDL_UTILS_H
