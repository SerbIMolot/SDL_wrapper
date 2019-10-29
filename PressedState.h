#pragma once

#include "ButtonState.h"

#define IMAGE_PRESSED "ButtonPressed2.png"
#define PRESSED_NEIGHBORS "ReleasedState"
class Body;
class PressedState
	: public ButtonState
{
public:
	PressedState(std::string name = "PressedState");
	~PressedState();

	void atStart( std::shared_ptr< Body > body ) override;
	void update( Body* body );
	void update( std::shared_ptr< Body > body ) override;

	void handleInput( Body* body, SDL_Scancode key);
	bool handleInput( std::shared_ptr< Body > body, std::shared_ptr< Event > newEvent ) override;

};

