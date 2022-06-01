#pragma once
#include "ButtonState.h"


#define IMAGE_IDLE "ButtonReleased.png"
#define HOVER_NEIGHBORS "ReleasedState"
class IdleState :
	public ButtonState
{
	IdleState( std::string name );
	~IdleState();

	void atStart(std::shared_ptr< Body > body);
	void update(std::shared_ptr< Body > body);
	bool handleInput(std::shared_ptr< Body > body, std::shared_ptr< Event > event);
	bool handleInput(std::shared_ptr< Body > body, std::shared_ptr< GameEvent > event);
};

