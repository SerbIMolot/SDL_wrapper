#pragma once
#include <string>
#include <memory>
#include "State.h"
#include "NFont.h"

class PressedState;
class ReleasedState;

class Body;
class Button;


class ButtonState
	: public State
{
	std::string text;
	std::unique_ptr< NFont > buttonFont;
public:

	ButtonState( std::string name, std::string neighbors ) : State( name, neighbors ) {}
	virtual ~ButtonState() {};

	virtual void atStart( std::shared_ptr< Body > body ) = 0;
	virtual void update( std::shared_ptr< Body > body ) = 0;
	virtual bool handleInput( std::shared_ptr< Body > body, std::shared_ptr< Event > event ) = 0;
	virtual bool handleInput( std::shared_ptr< Body > body, std::shared_ptr< GameEvent > event ) = 0;

	void setText(std::string text)
	{
		this->text = text;
	}

	friend class PressedState;
	friend class ReleasedState;
	friend class HoverState;
};





