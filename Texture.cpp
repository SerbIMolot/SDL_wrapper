//
#include "Texture.h"
#include "Vector2d.h"
#include "Box2d.h"
#include "SDL_image.h"
#include "TextureManager.h"

Texture::Texture()
{
	sTexture = nullptr;
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

	SDL_Texture* newTexture = nullptr;

	//Load image at path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
			SDL_Log( "loadFromFile { IMG_Load() } Unable to create surface from % s!SDL Error;", path.c_str() );
	}
	else
	{

		//newTexture = GPU_CopyImageFromSurface( loadedSurface );
		newTexture = SDL_CreateTextureFromSurface(TextureManager::sRenderer, loadedSurface);

		if (newTexture == nullptr)
		{
			SDL_Log("Unable to create texture from %s! SDL Error;\n", path.c_str());

		}
		else
		{
			mWidth = static_cast< float >( loadedSurface->w );
			mHeight = static_cast< float >( loadedSurface->h );

		}

		SDL_FreeSurface(loadedSurface);

	}


	sTexture = newTexture;

	return sTexture != nullptr;
}

bool Texture::loadFromFile( std::string path, SDL_Color colorKey )
{
	free();
	
	SDL_Texture* newTexture = nullptr;
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

		newTexture = SDL_CreateTextureFromSurface( TextureManager::sRenderer, loadedSurface );


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

	sTexture = newTexture;
	
	return sTexture != nullptr;
}

void Texture::free()
{
	if ( sTexture != nullptr ) 
	{
		SDL_DestroyTexture( sTexture );
		sTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}

}


void Texture::render( int x, int y, SDL_Rect * clip, float angle, float pivotX, float pivotY, Uint32 flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { static_cast< float >( x ), static_cast< float >( y ), mWidth, mHeight };

	if (clip != nullptr)
	{
		SDL_RenderCopy(TextureManager::sRenderer, sTexture, NULL, NULL);
	}

}

void Texture::render( float x, float y, SDL_Rect * clip, float angle, float pivotX, float pivotY, Uint32 flip )
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	SDL_Rect* clio = NULL;
	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		clio = new SDL_Rect();
		clio->x = clip->x;
		clio->y = clip->y;
		clio->w = clip->w;
		clio->h = clip->h;
	}
	SDL_Point center = { pivotX, pivotY };


	if (SDL_RenderCopyEx(TextureManager::sRenderer, sTexture, clio, &renderQuad, angle, NULL, SDL_FLIP_NONE))
	{
		printf("Error rendering texture! SDL Error %s\n", SDL_GetError());
	}
	delete clio;

}

void Texture::render(std::shared_ptr< Vector2d > vec, SDL_Rect* clip, float angle, float pivotX, float pivotY, Uint32 flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { vec->getX(), vec->getY(), mWidth, mHeight };


	SDL_RenderCopy(TextureManager::sRenderer, sTexture, NULL, NULL);


}
void Texture::render( std::shared_ptr< b2Vec2 > vec, SDL_Rect* clip, float angle, float pivotX, float pivotY, Uint32 flip )
{
	SDL_Rect renderQuad = { vec->x, vec->y, mWidth, mHeight };

	SDL_RenderCopy(TextureManager::sRenderer, sTexture, NULL, NULL);

}

void Texture::render( Vector2d& vec, SDL_Rect* clip, float angle, float pivotX, float pivotY, Uint32 flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {  vec.getX(),  vec.getY(), mWidth, mHeight };

	SDL_RenderCopy(TextureManager::sRenderer, sTexture, NULL, NULL);


}
void Texture::render( b2Vec2* vec, SDL_Rect* clip, float angle, float pivotX, float pivotY, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {  vec->x,  vec->y, mWidth, mHeight };

	SDL_RenderCopy(TextureManager::sRenderer, sTexture, NULL, NULL);

}

void Texture::setRGBA( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha )
{
	SDL_SetTextureColorMod( sTexture, red, green, blue );

}

void Texture::scale( float newH, float newW )
{
	mWidth = newH;
	mHeight = newW;
}

void Texture::setBlendMode(SDL_BlendMode mode )
{
	SDL_SetTextureBlendMode( sTexture, mode);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod( sTexture, alpha );
}
float Texture::getWidth()
{
	return mWidth;
}

float Texture::getHeight()
{
	return mHeight;
}
