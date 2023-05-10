//#ifndef BASEOBJECT_H
//#define BASEOBJECT_H
//
//#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
//
//#include "mainCharacter.h"
//
//using namespace std;
//
//class Pinky
//{
//public:
//    //Initializes the variables
//    Pinky();
//
//    //Moves the dot and check collision against tiles
//    void move( vector<collisionRect*> rects );
//
//    //Shows the dot on the screen
//    void render( SDL_Rect& camera, int frame);
//
//    bool isDead();
//
//    LTexture getTexture();
//    SDL_FRect getBox();
//private:
//    //Maximum axis velocity of the dot
//    const float PINKY_VEL = 7;
//    const int PINKY_WIDTH = 64;
//    const int PINKY_HEIGHT = 64;
//
//    //Collision box of the dot
//    SDL_FRect box;
//
//    int direction;
//
//    //The velocity of the dot
//    float velX, velY;
//
//    LTexture texture;
//};
//
//#endif // BASEOBJECT_H
