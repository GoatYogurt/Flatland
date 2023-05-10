#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "include/game.h"
#include "include/SDL_utils.h"
#include "include/player.h"
#include "include/base.h"
#include "include/map.h"

using namespace std;

int main( int argc, char* argv[] )
{
    int frame = 0;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    font = TTF_OpenFont("res/font/minecraft.ttf", 36);

    Mix_OpenAudioDevice(44000, MIX_DEFAULT_FORMAT, 4, 9000, NULL,
                    SDL_AUDIO_ALLOW_FREQUENCY_CHANGE |
                    SDL_AUDIO_ALLOW_CHANNELS_CHANGE);
    jumpSound = Mix_LoadWAV("res/sound/jump.wav");
    dieSound = Mix_LoadWAV("res/sound/die.wav");
    walkingSound = Mix_LoadWAV("res/sound/walking.wav");

    LTexture background;
    background.loadFromFile("res/gfx/background1760x1136.png", renderer);

    LTexture whiteBackground;
    whiteBackground.loadFromFile("res/gfx/whiteBackground.png", renderer);

    LTexture nightBackground;
    nightBackground.loadFromFile("res/gfx/nightBackground1760x1136.png", renderer);

    Player player;

    SDL_Rect camera{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // level 1 information
    Map level1;
    level1.loadFromFile("res/map/level1.png", renderer);

    int LEVEL1_COLLISION_RECTS_NUMBER = 28;
    collisionRect lv1Rects[LEVEL1_COLLISION_RECTS_NUMBER] =
    {
        ///floor 3
        {{0,26*8+8,199*8,8*8},ground},
        {{44*8,24*8,4*8,2*8},spike},
        {{83*8,24*8,4*8,2*8},spike},
        {{124*8,25*8,6*8,2*8},rock},
        {{159*8,24*8, 4*8,2*8},spike},
        {{184*8,25*8,6*8,2*8},rock},

        ///floor 2
        {{24*8, 76*8+8, 195*8, 8*8},ground},
        {{197*8,74*8,22*8,2*8},spike},
        {{166*8,74*8,4*8,2*8},spike},
        {{87*8,74*8,4*8,2*8},spike},
        {{54*8,74*8,4*8,2*8},spike},
        {{166*8, 53*8, 4*8, 3*8},spike},
        {{64*8, 53*8, 19*8, 3*8},spike},
        {{122*8, 74*8,6*8,2*8},rock},
        {{25*8, 74*8,6*8,2*8},rock},

        ///floor 1
        {{0, 134*8+8, 1760, 64},ground},
        {{24*8,132*8,4*8,2*8},spike},
        {{49*8,132*8,6*8,2*2},rock},
        {{73*8,128*8,3*8,5*8},spike},
        {{76*8, 126*8+8,64,64},block},
        {{84*8, 128*8,3*8,5*8},spike},
        {{110*8,132*8,32,16},spike},
        {{150*8,128*8,3*8,5*8},spike},
        {{153*8,126*8+8,64,64},block},
        {{158*8,120*8,3*8,5*8},spike},
        {{161*8,118*8+8,64,128},block},
        {{171*8,132*8,32,16},spike},
        {{212*8,126*8,7*8,8*8},flag},
    };

    //level 2 information
    Map level2;
    level2.loadFromFile("res/map/level2.png", renderer);
    const int LEVEL2_COLLISION_RECTS_NUMBER = 43;
    collisionRect lv2Rects[LEVEL2_COLLISION_RECTS_NUMBER] =
    {
        ///floor 1
        {{0,126*8+8,65*8,16*8},ground},
        {{520,1072,128,0},sea},
        {{648,1016,256,0}, ground},
        {{904,1072,136,0},sea},
        {{1040,1016,64,0}, ground},
        {{1104,1072,120,0},sea},
        {{1224,1016,63,0},ground},
        {{1288,1072,128,0},sea},
        {{1416,1016,344,0},ground},
        {{178*8,124*8,5*8,3*8},rock},
        {{212*8, 118*8+8, 64-8-8, 64},block},

        ///floor 2
        {{203*8,102*8+8,64,64-8-8-8},block},
        {{212*8,86*8+8,64,64-8-8-8},block},
        {{195*8,80*8+8,8*8-8,32*8-8-8-8},wall},
        {{800,640+8,320,64},ground},
        {{1248,624,48-8,16},rock},
        {{1120,648+8,15*8,3*8},lava},
        {{1240,640+8,320,64},ground},
        {{77*8,71*8+8,64,64},block},//block duoi
        {{88*8,76*8+8,64,64},block},//block duoi
        {{88*8,49*8,64,64},block},//block tren
        {{90*8, 57*8, 32, 16},spike},
        {{78*8,42*8,64,64},block},//block tren
        {{80*8, 50*8, 32, 16},spike},
        {{66*8,37*8,64,64},block},//block tren
        {{68*8, 45*8, 32, 16},spike},
        {{51*8, 66*8+8, 23*8, 8*8},ground},
        {{8*8, 90*8+8, 55*8, 8*8},ground},
        {{34*8, 88*8, 7*8, 2*8},spike},
        {{0, 82*8+8, 64, 64},block},

        ///floor 3
        {{14*8, 65*8+8, 64-8-8, 64-8-8},block},
        {{1*8, 47*8+8, 64-8, 64-8-8},block},
        {{14*8, 31*8+8, 64-8, 64-8-8},block},
        {{23*8, 26*8+8, 8*8-8, 48*8},wall},
        {{43*8, 26*8+8, 8*8-8, 28*8},wall},
        {{51*8, 26*8+8, 179*8, 64},ground},
        {{57*8, 24*8, 32, 16},spike},
        {{99*8, 24*8, 3*8, 5*8},spike},
        {{100*8, 18*8+8, 64, 64},block},
        {{108*8, 19*8, 16*8, 6*8},lava},
        {{124*8, 18*8+8, 64, 64},block},
        {{132*8, 19*8,3*8, 7*8},spike},
        {{212*8, 18*8, 7*8, 8*8},flag}
    };

    SDL_Event event;
    int a = 0;
    bool quit = false;
    while( !quit )
    {
        //start game
        if (a == 0)
        {
            while( SDL_PollEvent( &event ) )
            {
                LTexture waitingScreenText;
                waitingScreenText.loadFromRenderedText( "Press Enter to start Level 1!" );
                if ( event.type == SDL_QUIT )
                {
                    quit = true;
                }
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, whiteBackground.getTexture(), NULL, NULL);
                waitingScreenText.render( ( SCREEN_WIDTH - waitingScreenText.getBox().w ) / 2, ( SCREEN_HEIGHT - waitingScreenText.getBox().h ) / 2, NULL, renderer);
                SDL_RenderPresent(renderer);
                if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN )
                {
                    a = 2;
                    SDL_RenderClear(renderer);
                    waitingScreenText.free();
                }
            }
        }
        // pause screen
        else if (a == 1)
        {
            LTexture pauseScreenText;
            pauseScreenText.loadFromRenderedText("ESC: Continue  X: Menu");

            while( SDL_PollEvent( &event ) )
            {
                if ( event.type == SDL_QUIT )
                {
                    quit = true;
                }
                SDL_RenderCopy(renderer, whiteBackground.getTexture(), NULL, NULL);
                pauseScreenText.render( ( SCREEN_WIDTH - pauseScreenText.getBox().w ) / 2, ( SCREEN_HEIGHT - pauseScreenText.getBox().h ) / 2, NULL, renderer);
                SDL_RenderPresent(renderer);
                if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE )
                {
                    a = 2;
                }
                if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x )
                {
                    a = 0;
                    pauseScreenText.free();
                    player.restart(0, 0);
                }
            }
        }
        //level 1
        else if (a == 2)
        {
            for (int i = 0; i < LEVEL1_COLLISION_RECTS_NUMBER; ++i)
            {
                level1.collisionRects.push_back(&lv1Rects[i]);
            }
            while( SDL_PollEvent( &event ) )
            {
                if ( event.type == SDL_QUIT )
                {
                    quit = true;
                    level1.free();
                }
                if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE )
                {
                    a = 1;
                }
                player.handleEvent(event);
            }
            player.move(level1.collisionRects);
            player.setCamera(camera);
            SDL_RenderClear(renderer);
            background.render(0, 0, &camera, renderer);
            level1.render(0, 0, &camera, renderer);
            player.render(camera, frame);
            SDL_RenderPresent(renderer);
            ++frame;
            if ( frame / 6 >= 4 )
            {
                frame = 0;
            }
            if ( player.win(level1.collisionRects) )
            {
                a = 3;
                SDL_RenderClear(renderer);
            }
            if (player.isDead(level1.collisionRects))
            {
                a = 5;
            }
        }

        //waiting screen level 1 -> level 2
        else if (a == 3)
        {
            LTexture waitingScreen2Text;
            waitingScreen2Text.loadFromRenderedText("You won! Press Enter to start Level 2.");

            while( SDL_PollEvent( &event ) )
            {
                if ( event.type == SDL_QUIT )
                {
                    quit = true;
                }
                SDL_RenderCopy(renderer, whiteBackground.getTexture(), NULL, NULL);
                waitingScreen2Text.render( ( SCREEN_WIDTH - waitingScreen2Text.getBox().w ) / 2, ( SCREEN_HEIGHT - waitingScreen2Text.getBox().h ) / 2, NULL, renderer);
                SDL_RenderPresent(renderer);
                if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x )
                {
                    a = 0;
                    waitingScreen2Text.free();
                    player.restart(0, 0);
                }
                if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN )
                {
                    a = 4;
                    SDL_RenderClear(renderer);
                    waitingScreen2Text.free();
                    player.restart(16, 872);
                }
            }
        }

        // level 2
        else if (a == 4)
        {
            for (int i = 0; i < LEVEL2_COLLISION_RECTS_NUMBER; ++i)
            {
                level2.collisionRects.push_back(&lv2Rects[i]);
            }
            while( SDL_PollEvent( &event ) )
            {
                if ( event.type == SDL_QUIT )
                {
                    quit = true;
                    level2.free();
                }
                if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE )
                {
                    a = 1;
                }
                player.handleEvent(event);
            }
            player.move(level2.collisionRects);
            player.setCamera(camera);
            SDL_RenderClear(renderer);
            nightBackground.render(0, 0, &camera, renderer);
            level2.render(0, 0, &camera, renderer);
            player.render(camera, frame);
            SDL_RenderPresent(renderer);
            ++frame;
            if ( frame / 6 >= 4 )
            {
                frame = 0;
            }
            if (player.isDead(level2.collisionRects))
            {
                a = 5;
            }
            if (player.win(level2.collisionRects))
            {
                a = 0;
                player.restart(0, 0);
            }
        }

        //game over
        else if (a == 5)
        {
            LTexture gameOverText;
            gameOverText.loadFromRenderedText("Game Over! Press Enter to Play Again!");

            while( SDL_PollEvent( &event ) )
            {
                if ( event.type == SDL_QUIT )
                {
                    quit = true;
                }
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, whiteBackground.getTexture(), NULL, NULL);
                gameOverText.render( ( SCREEN_WIDTH - gameOverText.getBox().w ) / 2, ( SCREEN_HEIGHT - gameOverText.getBox().h ) / 2, NULL, renderer);
                SDL_RenderPresent(renderer);
                if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN )
                {
                    a = 0;
                    player.restart(0,0);
                }
            }
        }
    }

    player.getTexture().free();

    background.free();
    whiteBackground.free();
    nightBackground.free();

    level1.free();
    level2.free();

    quit_(window, renderer);
    return 0;
}
