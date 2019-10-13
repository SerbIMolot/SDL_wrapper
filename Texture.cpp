#include "stdafx.h"



Texture::Texture()
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}


Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile( std::string path )
{
	
	//Delete pre existing texture
	free();

	GPU_Image* newTexture = nullptr;

	//Load image at path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		GPU_Log("Unable to load image %s! SDL_Image error: %s\n", path.c_str(), IMG_GetError());
			GPU_PushErrorCode( "loadFromFile { IMG_Load() }", GPU_ERROR_DATA_ERROR, "Unable to create surface from % s!SDL Error;", path.c_str() );
	}
	else
	{

		newTexture = GPU_CopyImageFromSurface( loadedSurface );


		if (newTexture == nullptr)
		{
			GPU_LogInfo("Unable to create texture from %s! GPU Error;\n", path.c_str() );
			GPU_PushErrorCode( "loadFromFile { GPU_CopyImageFromSurface() }", GPU_ERROR_DATA_ERROR, "Unable to create texture from % s!GPU Error;", path.c_str() );

		}
		else
		{
			mWidth = static_cast< float >( loadedSurface->w );
			mHeight = static_cast< float >( loadedSurface->h );

		}

		SDL_FreeSurface(loadedSurface);

	}


	mTexture = newTexture;

	return mTexture != nullptr;
}

bool Texture::loadFromFile( std::string path, SDL_Color colorKey )
{
	//Delete pre existing texture
	free();

	GPU_Image* newTexture = nullptr;

	//Load image at path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if (loadedSurface == nullptr)
	{
		printf( "Unable to load image %s! SDL_Image error: %s\n", path.c_str(), IMG_GetError() );
	} else
	{

		if ( SDL_SetColorKey( loadedSurface, SDL_TRUE, 
							  SDL_MapRGB( loadedSurface->format, colorKey.r, colorKey.g, colorKey.b ) < 0 ) )
		{
			printf("Unable to ser colorKey for %s! SDL Error error: %s\n", path.c_str(), SDL_GetError());
		}

		newTexture = GPU_CopyImageFromSurface( loadedSurface );


		if ( newTexture == nullptr)
		{
			printf( "Unable to create texture from %s! SDL Error; %s\n", path.c_str(), SDL_GetError() );
		
		}
		else
		{
			mWidth = static_cast< float >( loadedSurface->w );
			mHeight = static_cast< float >( loadedSurface->h );
		
		}

		SDL_FreeSurface( loadedSurface );

	}

	mTexture = newTexture;

	return mTexture != nullptr;
}

void Texture::free()
{
	if ( mTexture != nullptr ) 
	{
		GPU_FreeImage( mTexture );
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}

}


void Texture::render( int x, int y, GPU_Rect * clip, float angle, float pivotX, float pivotY, GPU_FlipEnum flip )
{
	//Set rendering space and render to screen
	GPU_Rect renderQuad = { static_cast< float >( x ), static_cast< float >( y ), mWidth, mHeight };

	if (clip != nullptr)
	{
		GPU_BlitRectX( mTexture, clip, SDL_wrapper::gRenderer, &renderQuad, angle, pivotX, pivotY, flip );
	}
	else
	{
		GPU_BlitRectX( mTexture, nullptr, SDL_wrapper::gRenderer, &renderQuad, angle, pivotX, pivotY, flip );
	}

}

void Texture::render( float x, float y, GPU_Rect * clip, float angle, float pivotX, float pivotY, GPU_FlipEnum flip )
{
	//Set rendering space and render to screen
	GPU_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		GPU_BlitRectX( mTexture, clip, SDL_wrapper::gRenderer, &renderQuad, angle, pivotX, pivotY, flip );
	}
	else
	{
		GPU_BlitRectX( mTexture, nullptr, SDL_wrapper::gRenderer, &renderQuad, angle, pivotX, pivotY, flip );
	}
//	SDL_RenderCopyEx(SDL_wrapper::gRenderer, mTexture, clip, &renderQuad, angle, center, flip);

}

void Texture::render(std::shared_ptr< Vector2d > vec, GPU_Rect* clip, float angle, float pivotX, float pivotY, GPU_FlipEnum flip )
{
	//Set rendering space and render to screen
	GPU_Rect renderQuad = { vec->getX(), vec->getY(), mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		GPU_BlitRectX( mTexture, clip, SDL_wrapper::gRenderer, &renderQuad, angle, pivotX, pivotY, flip );
	}
	else
	{
		GPU_BlitRectX( mTexture, nullptr, SDL_wrapper::gRenderer, &renderQuad, angle, pivotX, pivotY, flip );
	}

}

void Texture::render( Vector2d& vec, GPU_Rect* clip, float angle, float pivotX, float pivotY, GPU_FlipEnum flip )
{
	//Set rendering space and render to screen
	GPU_Rect renderQuad = {  vec.getX(),  vec.getY(), mWidth, mHeight };

	if (clip != nullptr)
	{
		GPU_BlitRectX(mTexture, clip, SDL_wrapper::gRenderer, &renderQuad, angle, pivotX, pivotY, flip);
	}
	else
	{
		GPU_BlitRectX(mTexture, nullptr, SDL_wrapper::gRenderer, &renderQuad, angle, pivotX, pivotY, flip);
	}

}

void Texture::setRGBA( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha )
{
	GPU_SetRGBA( mTexture, red, green, blue, alpha );
	//Modulate texture
	//SDL_SetTextureColorMod( mTexture, red, green, blue );

}

void Texture::setBlendMode( GPU_BlendPresetEnum mode )
{
	GPU_SetBlendMode( mTexture, mode );
	//SDL_SetTextureBlendMode( mTexture, blending );
}
/*
void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
*/
float Texture::getWidth()
{
	return mWidth;
}

float Texture::getHeight()
{
	return mHeight;
}
