#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "SDL_utils.h"

using namespace std;

//thong so man hinh cua man hinh
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 560;

//thong so man hinh cua toan map
const int LEVEL_WIDTH = 1760;
const int LEVEL_HEIGHT = 1136;
const int GRAVITY = 9;
const string WINDOW_TITLE = "Flatland (Fancade)";

extern int frame;

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern TTF_Font* font;

extern Mix_Chunk* jumpSound;
extern Mix_Chunk* dieSound;
extern Mix_Chunk* walkingSound;
extern Mix_Music* gameMusic;

enum dir
{
    left_,
    right_
};

#endif // GAME_H
