#pragma once

enum BodyState
{
	stStanding,
	stMoving,
	stInAir,
	stFloat,
	stSwim,
	stUnderwater
};
class dynBody : public Body
{
	BodyState state;

	b2PolygonShape dynamicBox;

	b2FixtureDef fixtureDef;
	b2Fixture* fixture;
public:
	dynBody();
	dynBody( BodyType btype, b2Vec2 vec, std::shared_ptr< Texture > textr, float dencity, float friction );
	dynBody( BodyType btype, float x, float y, std::shared_ptr<Texture> textr, float dencity, float friction );
	~dynBody();
	virtual void Init() {}
	void applyForce( b2Vec2 force );

	b2Vec2 getVelocity();

	void handleInput( SDL_Scancode key );

	void setBodyState( BodyState state );
	BodyState getBodyState();

	friend class Entity;
	
};

