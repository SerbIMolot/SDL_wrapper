#pragma once
#include "Entity.h"

class Player
	: public Entity
{
public:
	Player();
	Player( b2Vec2 vec );
	Player( float x, float y );
	Player(float x, float y, std::shared_ptr<Texture> texture);
	~Player();
	void Init();
	void jump();

	virtual void move( b2Vec2 dir );
};

