#pragma once

#include <memory>
#include <vector>

#include "EventData.h"
#include "EventManager.h"


enum MouseB
{
	mLeft,
	mRight,
	mWheel
};
//static std::unique_ptr< bool[] > KEYS = std::make_unique< bool[] >( 322 );
// bool[]( 322 );

class SDL_wrapper;

#define STATIC_INT( x ) static_cast< int >( x )

class EventHandle
{
	SDL_Event e;
	static std::shared_ptr< b2Vec2 > mouseCoord;

public:
	static bool  KEYS[322];
	EventHandle();
	EventHandle(std::shared_ptr< SDL_wrapper > gameCopy);
	~EventHandle();
	
	void Update();

	static std::shared_ptr< b2Vec2 > const getMouseCoord();
};

