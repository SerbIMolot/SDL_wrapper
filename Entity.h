#pragma once
class Entity : public dynBody
{

	float maxSpeed;

	b2Vec2 moveBounds;

public:
	Entity();
	Entity( BodyType btype, b2Vec2 vec, std::shared_ptr<Texture> textr, float dencity, float friction);
	Entity( BodyType btype, float x, float y, std::shared_ptr<Texture> textr, float dencity, float friction);
	~Entity();

	void moveTo( b2Vec2 pos );

	void setMoveBounds( b2Vec2 bounds );
	void setMoveBounds( float x, float y );

	b2Vec2 getMoveBounds();

	float getMaxSpeed();

	void setMaxSpeed( float speed );

	friend class Player;
	
	//b2Vec2 getVelocity();


	//virtual void move();

	//virtual void Update( std::shared_ptr< dynBody > obj );

};

