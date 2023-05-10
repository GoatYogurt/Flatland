#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( string path, SDL_Renderer* renderer);

		bool loadFromRenderedText ( string textToRender );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( float x, float y, SDL_Rect* clip, SDL_Renderer* renderer );

		//Gets image dimensions
		SDL_FRect getBox();

		SDL_Texture* getTexture();

		void setBox(int w, int h);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

        SDL_FRect mBox;
};

/*
class baseObject
{
public:
    baseObject();
    ~baseObject();

    void SetRect(const int& x, const int& y);
    SDL_Rect GetRect();
    SDL_Texture* GetObject();

    bool loadImg(string path, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, SDL_Rect* clip, bool isFullScreen);
    void free();
protected:
    SDL_Rect rect;
    SDL_Texture* texture;
};
*/

#endif // BASE_H
