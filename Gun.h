#pragma once
#include "stdafx.h"


class Gun : public dynBody
{

	b2Vec2 offset;

	float previousAngle;

public:
	Gun();
	~Gun();
	void Init();
	void setOffset( b2Vec2 offs );

	b2Vec2 getOffset();
	
	void Update();
};

