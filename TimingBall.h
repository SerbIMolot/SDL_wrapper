#pragma once
#include "stdafx.h"
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

	void collisionDetected(std::shared_ptr< Object > obj);
};

