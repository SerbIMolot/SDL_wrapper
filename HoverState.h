#pragma once
#include "ButtonState.h"

#define IMAGE_HOVER "ButtonHover.png"
#define HOVER_NEIGHBORS "ReleasedState"

class HoverState :
	public ButtonState
{
public:
	HoverState( std::string name = "HoverState");
	~HoverState();

	void atStart(std::shared_ptr< Body > body);
	void update(std::shared_ptr< Body > body);
	bool handleInput(std::shared_ptr< Body > body, std::shared_ptr< Event > event);
	bool handleInput(std::shared_ptr< Body > body, std::shared_ptr< GameEvent > event);
};

