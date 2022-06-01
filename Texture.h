#pragma once

#include "sdl\include\SDL.h"
#include <string>
#include <memory>

struct SDL_Rect;
struct GPU_Image;
class Vector2d;
struct b2Vec2;
typedef uint32_t Uint32;
typedef uint8_t Uint8;


class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile( std::string path);

	bool loadFromFile( std::string path, SDL_Color colorKey );

	void free();

	void render( int x, int y, SDL_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, Uint32 flip = 0x0);
				 
	void render( float x, float y, SDL_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, Uint32 flip = 0x0);
				 
	void render( std::shared_ptr<Vector2d> vec, SDL_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, Uint32 flip = 0x0);
	void render( std::shared_ptr< b2Vec2 > vec, SDL_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, Uint32 flip = 0x0);
				 
	void render( Vector2d& vec, SDL_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, Uint32 flip = 0x0);
	void render( b2Vec2* vec, SDL_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setRGBA( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255 );
	void scale( float newH, float newW );

	void setBlendMode( SDL_BlendMode mode );

	void setAlpha(Uint8 alpha);

	float getWidth();
	float getHeight();

private:

	SDL_Texture* sTexture;

	float mWidth;
	float mHeight;
	float scaleFactorW = 0.0f;
	float scaleFactorH = 0.0f;
};

