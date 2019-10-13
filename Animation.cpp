#include "stdafx.h"


Animation::Animation()
{

	frames = 0;

	spriteSheet = nullptr;

	frameSize = Vector2d( 0.0f, 0.0f );
}

Animation::Animation( int frames, std::shared_ptr< Texture > spriteSheet, Vector2d frameDimentions )
{

	setSpriteSheet( frames, spriteSheet, frameDimentions );

}


Animation::~Animation()
{
}

void Animation::drawFrame( std::shared_ptr< Vector2d > point, bool isLooped )
{
	if ( ended && isLooped )
	{
		reset();
	}

	if ( !ended )
	{
		spriteSheet->render( point, &spriteClips[ currentFrame / static_cast< int >( ceil( frameDevider ) ) ] );
		currentFrame++;

		if ( currentFrame / frameDevider >= frames )
		{
			ended = true;
		}
	}

}
/*
void Animation::drawFrame( std::shared_ptr< Vector2d > point, bool isLooped )
{
	spriteSheet->render( point, &spriteClips[ currentFrame / frameDevider ] );

	currentFrame++;

	if ( currentFrame / frameDevider >= frames )
	{
		currentFrame = 0;
	}

}
*/
void Animation::drawFrame( Vector2d point, bool isLooped )
{

	if ( ended && isLooped )
	{
		reset();
	}

	if ( !ended )
	{
		spriteSheet->render( point, &spriteClips[ currentFrame / static_cast<int>(ceil( frameDevider ) ) ] );
		currentFrame++;

		if ( currentFrame / frameDevider >= frames )
		{
			ended = true;
		}
	}

}

void Animation::drawFrame( int x, int y, bool isLooped )
{
	if ( ended && isLooped )
	{
		reset();
	}
	
	if ( !ended )
	{
		spriteSheet->render( x, y, &spriteClips[ currentFrame / static_cast<int>( ceil( frameDevider ) ) ] );
		currentFrame++;

		if ( currentFrame / frameDevider >= frames )
		{
			ended = true;
		}
	}

}

void Animation::reset()
{
	currentFrame = 0;
	ended = false;
}

int Animation::getCurrentFrame()
{
	return currentFrame;
}

void Animation::setCurrentFrame(int frame)
{
	currentFrame = frame;
}

int Animation::getFrames()
{
	return frames;
}

float Animation::getDevider()
{
	return frameDevider;
}

void Animation::setDevider( float devider )
{
	frameDevider = devider;
}

bool Animation::isEnded()
{
	return ended;
}


void Animation::setSpriteSheet( int frames, std::shared_ptr< Texture > spriteSheet, Vector2d frameDimentions )
{
	
	this->spriteSheet = std::move( spriteSheet );
	
	this->frames = frames;

	frameSize = frameDimentions;


	Vector2d leftBound{ 0.0f , 0.0f };

	for ( int i = 0; i < frames; i++ )
	{
		GPU_Log(" size of clip:\n x = %d, y = %d \n w = %d, h = %d.", static_cast< int >( leftBound.getX() ), static_cast< int >( leftBound.getY() ), 
																	static_cast< int >( frameDimentions.getX() ), static_cast< int >( frameDimentions.getY() ) );
		spriteClips.push_back( GPU_Rect{ leftBound.getX(), leftBound.getY() , frameDimentions.getX(), frameDimentions.getY() } );

		if ( leftBound.getX() + frameDimentions.getX() > this->spriteSheet->getWidth() - frameDimentions.getX() )
		{

			leftBound.setX( 0.0f );

			if ( leftBound.getY() + frameDimentions.getY() > this->spriteSheet->getHeight() - frameDimentions.getY() )
			{
				return;
			}
			else
			{
				leftBound.addY( frameDimentions.getY() );
			}

		}
		else
		{
			leftBound.addX( frameDimentions.getX() );
		}

		
	}

}
