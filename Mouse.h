#pragma once

#include "Body.h"
#include "TextureManager.h"

class Mouse : public Body
{

	std::shared_ptr< Body > grabbedObj;

	bool LMBHold;
	bool RMBHold;

public:
	Mouse();
	~Mouse();
	void Init();

	void grabObj( std::shared_ptr< Body > obj );
	void releaseObj();

	void UpdateStats( int x, int y, bool isReleased, int button );

	void Update();

	void Draw();

	void collisionDetected( std::shared_ptr < Body > obj );

	bool isLMBHold();

	bool isRMBHold();

};

