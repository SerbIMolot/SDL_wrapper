
#include <cmath>

#include "Gun.h"
#include "TextureManager.h"
#include "EventHandle.h"
#include "Box2D\Common\b2Math.h"
#include "Constants.h"


Gun::Gun()
	: dynBody( btGun, 0.0f, 0.0f , TextureManager::getTexture( "gun.png" ), 0.01f, 0.0f )
{
	b2Fixture* fix = groundBody->GetFixtureList();

//	for ( ; fix; fix->GetNext() )
//	{
//		fix->SetSensor( true );
//	}
}


Gun::~Gun()
{
}

void Gun::Init()
{
}



void Gun::setOffset(b2Vec2 offs)
{
	*offset = offs;
}

b2Vec2 Gun::getOffset()
{
	return *offset;
}

void Gun::Update()
{

	
	if ( parent != nullptr )
	{
		
		//float32 determinant = getPos().x * EventHandle::getMouseCoord()->y - getPos().y * EventHandle::getMouseCoord()->x;
		//float angle = EventHandle::getMouseCoord() - getPos();
		//double theta = RadianToDegree( std::atan2( determinant, b2Dot( getPos(), *EventHandle::getMouseCoord() ) ) );
		//double theta = std::atan2( determinant, b2Dot( getPos(), *EventHandle::getMouseCoord() ) );
		float theta;
		b2Vec2 diff = getPos() - *EventHandle::getMouseCoord();

		diff.x *= diff.x;
		diff.y *= diff.y;

		float d = std::abs( std::sqrt( diff.x + diff.y ) );
		if ( getPos().x > EventHandle::getMouseCoord()->x )
		{ 
			theta = -std::atan2( diff.x, diff.y ) + 1.54830f ;
			
			
		}
		else
		{
			theta = std::atan2( diff.x, diff.y ) + 1.54830f;
			
		}
		//0SDL_Log("Obj pos: x - %f, y - %f ", getPos().x , getPos().y );
		//SDL_Log("Mouse pos: x - %f, y - %f ", EventHandle::getMouseCoord()->x, EventHandle::getMouseCoord()->y);
		if (groundBody->GetAngle() > theta - 0.01f && groundBody->GetAngle() < theta + 0.01f )
		{
			groundBody->SetAngularVelocity( 0.0f );
		}
		else
		{ 

				rotateTo(theta);
				previousAngle = theta;
				SDL_Log("theta: %f", RadianToDegree(theta));
				SDL_Log("theta: %f", theta);

				if ( groundBody->GetAngle() > M_PI / 2 )
				{
					setTextureFlip( SDL_FLIP_VERTICAL );
				}
				else
				{
					setTextureFlip( SDL_FLIP_NONE );
				}
				
			
	
		}
		
	}
	SDL_Log( "Angle of gun: %f", groundBody->GetAngle() );
		
}
