#pragma once
#include <cmath>
#include "Body.h"
#include "TextureManager.h"

class TimingBall :
	public Body
{
	float angle;
	float velOfRotation;
public:

	TimingBall( float posX, float posY );
	~TimingBall();

	void Update();

	void Draw() override;

	void collisionDetected(std::shared_ptr< Body > obj);
};

