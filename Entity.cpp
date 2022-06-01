
#include "Entity.h"
#include "Box2D\Common\b2Math.h"
#include "Box2D\Dynamics\b2Body.h"


Entity::Entity()
	: dynBody()
{

}

Entity::Entity( BodyType btype, b2Vec2 vec, std::shared_ptr<Texture> textr, float dencity, float friction )
	: dynBody( btype, vec, textr, dencity, friction )
{

}

Entity::Entity( BodyType btype, float x, float y, std::shared_ptr<Texture> textr, float dencity, float friction )
	: dynBody( btype, x, y, textr, dencity, friction )
{

}


Entity::~Entity()
{
	delete moveBounds;
}

void Entity::moveTo( b2Vec2 pos )
{
	float speed = getVelocity().LengthSquared();
	float maxSpeedsqrd = getMaxSpeed() * getMaxSpeed();
	SDL_Log( "dist = %f\n", speed );
	SDL_Log( "SqrtSpeed = %f\n", maxSpeedsqrd );
	
	if ( speed < maxSpeedsqrd )
	{ 
		SDL_Log( "Player accelerate\n" );
		groundBody->ApplyLinearImpulse( b2Cross( pos, getMaxSpeed() ), groundBody->GetWorldCenter(), true );
	}
	else
	{ 
		SDL_Log( "Player max speed\n" );
		groundBody->SetLinearVelocity( b2Cross( pos, getMaxSpeed() ) );
	}
}

void Entity::setMoveBounds(b2Vec2 bounds)
{
	*this->moveBounds = bounds;
}

void Entity::setMoveBounds(float x, float y)
{
	this->moveBounds = new b2Vec2( x, y );
}


b2Vec2 Entity::getMoveBounds()
{
	return *moveBounds;
}

float Entity::getMaxSpeed()
{
	return maxSpeed;
}

void Entity::setMaxSpeed( float speed )
{
	maxSpeed = speed;
}


