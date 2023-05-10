#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "game.h"
#include "base.h"

enum collisionType
{
    sea,
    rock,
    wall,
    ground,
    spike,
    block,
    flag,
    lava
};

struct collisionRect
{
    SDL_FRect box;
    int type;
};

class Map: public LTexture
{
public:
    vector<collisionRect*> collisionRects;
private:

};

bool checkCollision( SDL_FRect a, SDL_FRect b );
int checkMapCollision ( SDL_FRect a, vector<collisionRect*> collisionRects);

#endif // MAP_H
