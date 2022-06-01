#pragma once
#include "Body.h"
#include "sdl\include\SDL_scancode.h"

enum BodyState
{
	stStanding,
	stMoving,
	stInAir,
	stFloat,
	stSwim,
	stUnderwater
};

class Texture;
struct b2BodyDef;
class b2Fixture;
struct b2FixtureDef;
class b2Body;
class b2PolygonShape;
class b2RevoluteJoint;
struct b2Vec2;

class dynBody : public Body
{
	BodyState state;

	b2PolygonShape* dynamicBox;

	b2FixtureDef* fixtureDef;
	b2Fixture* fixture;
public:
	dynBody();
	dynBody( BodyType btype, b2Vec2 vec, std::shared_ptr< Texture > textr, float dencity, float friction, std::shared_ptr<b2Shape> shape = nullptr);
	dynBody( BodyType btype, float x, float y, std::shared_ptr<Texture> textr, float dencity, float friction, std::shared_ptr<b2Shape> shape = nullptr);
	~dynBody();
	virtual void Init() {}
	void applyForce( b2Vec2 force );

	b2Vec2 getVelocity();

	//virtual void handleInput(std::shared_ptr< GameEvent > newEvent) {};

	void setBodyState( BodyState state );
	BodyState getBodyState();

	friend class Entity;
	
};

