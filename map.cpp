#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "include/map.h"
#include "include/game.h"
#include "include/SDL_utils.h"

bool checkCollision( SDL_FRect a, SDL_FRect b )
{
    //The sides of the rectangles
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

int checkMapCollision ( SDL_FRect a, vector<collisionRect*> collisionRects )
{
    for ( auto rect: collisionRects )
    {
        if ( checkCollision(a, rect->box) )
        {
            if ( rect->type == sea || rect->type == spike || rect->type == lava )
            {
                return 2;
            }
            if ( rect->type == flag)
            {
                return 3;
            }
            else return 1;
        }
    }
    return 0;
}
