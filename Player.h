#pragma once
class Player
	: public Entity
{
public:
	Player();
	Player( b2Vec2 vec );
	Player( float x, float y );
	~Player();
	void Init();
	void jump();

	void move( b2Vec2 dir );
};

