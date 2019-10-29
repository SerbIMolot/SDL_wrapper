#pragma once
#include "ButtonState.h"

#define IMAGE_RELEASED "ButtonReleased.png"
#define RELEASED_NEIGHBORS "PressedState"

class Body;

class ReleasedState
	: public ButtonState
{
public:
	ReleasedState(std::string name = "ReleasedState");
	~ReleasedState();

	void atStart( std::shared_ptr< Body > body ) override;
	void update(Body* body);
	void update(std::shared_ptr< Body > body) override;

	void handleInput(Body* body, SDL_Scancode key);
	bool handleInput(std::shared_ptr< Body > body, std::shared_ptr< Event > event) ;

};