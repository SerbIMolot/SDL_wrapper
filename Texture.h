#pragma once

#include "stdafx.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile( std::string path);

	bool loadFromFile( std::string path, SDL_Color colorKey );

	void free();

	void render( int x, int y, GPU_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, GPU_FlipEnum flip = GPU_FLIP_NONE );
				 
	void render( float x, float y, GPU_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, GPU_FlipEnum flip = GPU_FLIP_NONE );
				 
	void render( std::shared_ptr<Vector2d> vec, GPU_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, GPU_FlipEnum flip = GPU_FLIP_NONE );
				 
	void render( Vector2d& vec, GPU_Rect* clip = nullptr, float angle = 0.0f, float pivotX = 0.0f, float pivotY = 0.0f, GPU_FlipEnum flip = GPU_FLIP_NONE);

	void setRGBA( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255 );

	void setBlendMode( GPU_BlendPresetEnum mode );

	//void render( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
	//void render( float x, float y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
	//void render( std::shared_ptr< Vector2d > vec, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
	//void render( Vector2d& vec, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
	////Color modulation
	//void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Blending
	//void setBlendMode( SDL_BlendMode blending );

	//Alpha modulation
	//void setAlpha( Uint8 alpha );

	float getWidth();
	float getHeight();

private:

	GPU_Image* mTexture;

	float mWidth;
	float mHeight;
};

