#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "game.h"
#include "SDL_utils.h"
#include "base.h"
#include "map.h"

using namespace std;

class Player
{
public:
    //Initializes the variables
    Player();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot and check collision against tiles
    void move( vector<collisionRect*> rects );

    //Centers the camera over the dot
    void setCamera( SDL_Rect& camera );

    //Shows the dot on the screen
    void render( SDL_Rect& camera, int frame);

    bool isDead( vector<collisionRect*> rects );
    bool win(  vector<collisionRect*> rects );

    void restart(float x , float y);

    LTexture getTexture();
    SDL_FRect getBox();
private:
    //Maximum axis velocity of the dot
    const float PLAYER_VEL = 9;
    const float JUMP = 23;
    const int PLAYER_WIDTH = 64;
    const int PLAYER_HEIGHT = 64;

    //Collision box of the dot
    SDL_FRect box;

    int direction;
    //The velocity of the dot
    float velX, velY;

    LTexture texture;
};

#endif // PLAYER_H
