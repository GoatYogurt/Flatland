#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "include/game.h"

using namespace std;

SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
TTF_Font* font = nullptr;

Mix_Chunk* jumpSound = nullptr;
Mix_Chunk* dieSound = nullptr;
Mix_Chunk* walkingSound = nullptr;
Mix_Music* gameMusic = nullptr;
