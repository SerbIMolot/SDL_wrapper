#include "stdafx.h"
#include "Player.h"


Player::Player()
	: Entity( btPlayer, PixelToMeter( SCREEN_WIDTH / 2), PixelToMeter(SCREEN_HEIGHT / 2), TextureManager::getTexture("plStand.png"), 0.20f, 0.30f )
{
	SDL_Log("PLAYER CON");
	maxSpeed = 10.0f;
	groundBody->SetFixedRotation( true );

	//gun
	/*
	BodyManager::Instance()->createBody( getPos(), TextureManager::getTexture("Scope.png"), "gun", btGun );
	std::shared_ptr< Gun > gun = std::static_pointer_cast< Gun>( BodyManager::Instance()->getBody( "gun" ) );
	
	std::shared_ptr< Player > player( this );
	gun->setParent( player );
	*/
	//gun = std::shared_ptr < dynBody >( btGun, getPos(), TextureManager::getTexture("Scope.png"), 0, 0 );
	//gun->getBody()->
}

Player::Player( b2Vec2 vec )
	: Entity( btPlayer, vec, TextureManager::getTexture("plStand.png"), 0.20f, 0.30f)
{
	maxSpeed = 2.0f;
	groundBody->SetFixedRotation(true);
}

Player::Player( float x, float y )
	: Entity( btPlayer, x, y, TextureManager::getTexture("plStand.png"), 0.20f, 0.30f)
{
	maxSpeed = 2.0f;
	groundBody->SetFixedRotation(true);
}


Player::~Player()
{
}

void Player::Init()
{
}

void Player::jump()
{
	applyForce( b2Vec2( 0, -10 ) );
}


void Player::move( b2Vec2 dir )
{

	groundBody->SetLinearVelocity( b2Cross( dir, getMaxSpeed() ) );
	//applyForce( b2Cross( dir, getMaxSpeed() ) );

}