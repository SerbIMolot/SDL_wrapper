#pragma once
#include "dynBody.h"

struct b2Vec2;

class Gun : public dynBody
{

	b2Vec2* offset;

	float previousAngle;

public:
	Gun();
	~Gun();
	void Init();
	void setOffset( b2Vec2 offs );

	b2Vec2 getOffset();
	
	void Update();
};

