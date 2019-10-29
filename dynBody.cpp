#include "stdafx.h"
#include "dynBody.h"


dynBody::dynBody()
	: Body()
{
	groundBodyDef.type = b2_dynamicBody;
	groundBodyDef.position.Set( 1.0f, 1.0f );
	
	groundBody = SDL_wrapper::world->CreateBody( &groundBodyDef );
	texture = TextureManager::getTexture("box.jpg");
	groundBox.SetAsBox( ( texture->getWidth() / 2 ) * PtMratio, ( texture->getHeight() / 2 ) * PtMratio );

	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.65f;
	fixtureDef.friction = 0.3f;

	fixture = groundBody->CreateFixture( &fixtureDef );

}

dynBody::dynBody( BodyType btype, b2Vec2 vec, std::shared_ptr<Texture> textr, float dencity, float friction)
	: Body()
{
	debug = false;
	this->btype = btype;

	groundBodyDef.type = b2_dynamicBody;
	groundBodyDef.position.Set( vec.x , vec.y );
	
	//SDL_Log("BODY con");

	groundBody = SDL_wrapper::world->CreateBody(&groundBodyDef);

	texture = std::move(textr);
	groundBox.SetAsBox( PixelToMeter( texture->getWidth() / 2 ), PixelToMeter( texture->getHeight() / 2 ) );

	//groundBody->CreateFixture(&groundBox, 0.0f);

	fixtureDef.shape = &groundBox;
	fixtureDef.density = dencity;
	fixtureDef.friction = friction;


	fixture = groundBody->CreateFixture( &fixtureDef );

	fixture->SetUserData( ( void* ) this );

}

dynBody::dynBody( BodyType btype, float x, float y, std::shared_ptr<Texture> textr, float dencity, float friction)
	: Body()
{
	debug = false;
	this->btype = btype;

	SDL_Log("dynBODY con\n");
	groundBodyDef.type = b2_dynamicBody;
	groundBodyDef.position.Set( x, y );

	groundBody = SDL_wrapper::world->CreateBody( &groundBodyDef );
	//texture = textr;
	if ( texture )
	{
		texture = std::move(textr);
		groundBox.SetAsBox( PixelToMeter( texture->getWidth() / 2 ), PixelToMeter( texture->getHeight() / 2 ) );
	}
	else
	{
		texture = nullptr;
		groundBox.SetAsBox( PixelToMeter( 10 ), PixelToMeter( 10 ) );
	}

	fixtureDef.shape = &groundBox;
	fixtureDef.density = dencity;
	fixtureDef.friction = friction;

	fixture = groundBody->CreateFixture(&fixtureDef);

	fixture->SetUserData( ( void* ) this );
	SDL_Log("dynBODY con2\n");

}



dynBody::~dynBody()
{
}

void dynBody::applyForce( b2Vec2 force )
{
	SDL_Log( "type %d", groundBody->GetType() );
	b2Vec2 pos = groundBody->GetWorldCenter();
	groundBody->ApplyForce( force, pos, true );
}

b2Vec2 dynBody::getVelocity()
{
	return groundBody->GetLinearVelocity();
}

void dynBody::handleInput(SDL_Scancode key)
{
}

void dynBody::setBodyState(BodyState state)
{
	this->state = state;
}

BodyState dynBody::getBodyState()
{
	return state;
}
