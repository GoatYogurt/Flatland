#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "include/game.h"
#include "include/SDL_utils.h"
#include "include/base.h"

using namespace std;

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mBox.x = 0;
    mBox.y = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( string path, SDL_Renderer* renderer)
{
    //Get rid of preexisting texture
    free();

    mTexture = loadTexture(path, renderer);
    //SDL_QueryTexture(mTexture, NULL, NULL, &mBox.w, &mBox.h);

    return (mTexture != NULL);
}

bool LTexture::loadFromRenderedText(string textToRender)
{
    //Get rid of preexisting texture
    free();
    SDL_Color nigga = {0, 0, 0};
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textToRender.c_str(), nigga );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mBox.w = textSurface->w;
            mBox.h = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
    }
}

void LTexture::render(  float x, float y, SDL_Rect* clip, SDL_Renderer* renderer )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mBox.w, mBox.h };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy( renderer, mTexture, clip, &renderQuad );
}

SDL_FRect LTexture::getBox()
{
    return mBox;
}

SDL_Texture* LTexture::getTexture()
{
    return mTexture;
}

void LTexture::setBox(int w, int h)
{
    mBox.w = w;
    mBox.h = h;
}

/*
baseObject::baseObject()
{
    texture = nullptr;
    rect.x = 0;
    rect.y = 0;
    rect.h = 0;
    rect.w = 0;
}

baseObject::~baseObject()
{

}

void baseObject::SetRect(const &x, const &y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 64;
    rect.h = 64;
}

bool baseObject::loadImg(string path, SDL_Renderer* renderer)
{
    texture = loadTexture(path, renderer);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    return (texture != nullptr);
}

void baseObject::render(SDL_Renderer* renderer, SDL_Rect* clip, bool isFullScreen)
{
    if (isFullScreen == true)
    {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    }
    else
    {
        SDL_Rect renderquad = {rect.x, rect.y, rect.w, rect.h};
        SDL_RenderCopy(renderer, texture, clip, &renderquad);
    }
}

void baseObject::free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        rect.w = 0;
        rect.h = 0;
    }
}
*/
