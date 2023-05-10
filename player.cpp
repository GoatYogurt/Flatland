#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "include/game.h"
#include "include/SDL_utils.h"
#include "include/player.h"
#include "include/map.h"

using namespace std;

Player::Player()
{
    box.x = 0;
    box.y = 0;
    box.w = PLAYER_WIDTH;
    box.h = PLAYER_HEIGHT;

    direction = left_;

    texture.loadFromFile("res/gfx/mainCharacter.png", renderer);
    texture.setBox(PLAYER_WIDTH, PLAYER_HEIGHT);

    //Initialize the velocity
    velX = 0;
    velY = 0;
}

void Player::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_a:
            velX -= PLAYER_VEL;
            direction = left_;
            break;
        case SDLK_d:
            velX += PLAYER_VEL;
            direction = right_;
            break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_a:
            velX += PLAYER_VEL;
            break;
        case SDLK_d:
            velX -= PLAYER_VEL;
            break;
        }
    }

    if ( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0 )
    {
        velY += JUMP;
        Mix_PlayChannel( -1, jumpSound, 0 );
    }

    if ( e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0 )
    {
        velY -= JUMP;
    }
}

void Player::move( vector<collisionRect*> collisionRects )
{
    box.x += velX;
    if( ( box.x < 0 ) || ( box.x + PLAYER_WIDTH > LEVEL_WIDTH ) || (checkMapCollision(box, collisionRects) == 1) )
    {
        box.x -= velX;
    }

    box.y += GRAVITY;
    box.y -= velY;

    if( ( box.y < 0 ) || ( box.y + PLAYER_HEIGHT > LEVEL_HEIGHT ) || (checkMapCollision(box, collisionRects) == 1) )
    {
        box.y += velY;
        box.y -= GRAVITY;
    }
}

void Player::setCamera( SDL_Rect& camera )
{
    //Center the camera over the dot
    camera.x = ( box.x + PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( box.y + PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void Player::render( SDL_Rect& camera, int frame )
{
    SDL_Rect clip[4] =
    {
        {0, 0, 64, 64},
        {64, 0, 64, 64},
        {128, 0, 64, 64},
        {192, 0, 64, 64}
    };

    if (velX != 0)
    {
        Mix_PlayChannel( -1, walkingSound, 0 );
        if (direction == left_)
        {
            if (frame > 11)
            {
                texture.render( box.x - camera.x, box.y - camera.y, &clip[(frame - 12) / 6], renderer );
            }
            else
            {
               texture.render( box.x - camera.x, box.y - camera.y, &clip[frame / 6], renderer );
            }
        }
        else
        {
            if (frame <= 11)
            {
                texture.render( box.x - camera.x, box.y - camera.y, &clip[(frame + 12) / 6], renderer );
            }
            else
            {
                texture.render( box.x - camera.x, box.y - camera.y, &clip[frame / 6], renderer );
            }
        }
    }
    else
    {
        if (direction == left_)
        {
            texture.render( box.x - camera.x, box.y - camera.y, &clip[0], renderer );
        }
        else
        {
            texture.render( box.x - camera.x, box.y - camera.y, &clip[2], renderer );
        }
    }
}

bool Player::isDead( vector<collisionRect*> collisionRects )
{
    if ( checkMapCollision(box, collisionRects) == 2 )
    {
        Mix_PlayChannel( -1, dieSound, 0 );
        return true;
    }
    return false;
}

bool Player::win( vector<collisionRect*> collisionRects )
{
    if ( checkMapCollision(box, collisionRects) == 3)
    {
        return true;
    }
    return false;
}

void Player::restart(float x, float y)
{
    velX = 0;
    velY = 0;

    box.x = x;
    box.y = y;
}

LTexture Player::getTexture()
{
    return texture;
}

SDL_FRect Player::getBox()
{
    return box;
}
