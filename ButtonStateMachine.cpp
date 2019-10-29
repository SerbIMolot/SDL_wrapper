#include "ButtonStateMachine.h"
#include "GPU_setup.h"

ButtonStateMachine::ButtonStateMachine()
	: StateMachine()
{
	pressed = std::make_shared< PressedState >();
	released = std::make_shared< ReleasedState >();

}

void ButtonStateMachine::Init()
{

	Add( std::static_pointer_cast<State>( pressed ).get() );
	Add( std::static_pointer_cast<State>( released ).get() );
	setDefaultState("ReleasedState");

}
ButtonStateMachine::~ButtonStateMachine()
{
}

void ButtonStateMachine::update(std::shared_ptr< Body > body)
{
	getCurrentState()->update(body);
}

void ButtonStateMachine::handleInput( std::shared_ptr<Body> body, std::shared_ptr< Event > event )
{

getCurrentState()->handleInput( body, event );

	/*
	std::shared_ptr< Body > tempBody = std::static_pointer_cast< Body >(body);
	if (key == SDL_SCANCODE_P && getCurrentState() != (State*)released.get())
	{
		changeState("ReleasedState");
		getCurrentState()->handleInput(tempBody, key);
	}
	if (key == SDL_SCANCODE_P && getCurrentState() != (State*)pressed.get())
	{
		changeState("PressedState");
		getCurrentState()->handleInput(tempBody, key);
	}
	*/
}