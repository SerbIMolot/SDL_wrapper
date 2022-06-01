#include "ButtonStateMachine.h"
#include "Button.h"

#include"PressedState.h"
#include"ReleasedState.h"
#include"HoverState.h"

ButtonStateMachine::ButtonStateMachine()
	: StateMachine()
{
	pressed = std::make_shared< PressedState >();
	released = std::make_shared< ReleasedState >();
	hover = std::make_shared< HoverState >();
}
ButtonStateMachine::ButtonStateMachine(std::shared_ptr< Body > body)
	: StateMachine(body)
{
	pressed = std::make_shared< PressedState >();
	released = std::make_shared< ReleasedState >();
	hover = std::make_shared< HoverState >();
}

void ButtonStateMachine::Init()
{

	Add( std::static_pointer_cast<State>( pressed ).get() );
	Add( std::static_pointer_cast<State>( hover ).get() );
	Add( std::static_pointer_cast<State>( released ).get() );
	setDefaultState("ReleasedState");

}
ButtonStateMachine::~ButtonStateMachine()
{
}

void ButtonStateMachine::update(std::shared_ptr< Body > body)
{
	getCurrentState()->update(body);

	for (b2ContactEdge* contact = body->getBody()->GetContactList(); contact != nullptr; contact = contact->next)
	{
		Body* a = static_cast<Body*>(contact->other->GetUserData());
		if (a->getType() == btMouse)
		{
			changeState("HoverState");
		}
	}
}

void ButtonStateMachine::handleInput(std::shared_ptr<Body> body, std::shared_ptr< GameEvent > event)
{
	if (event->command == "MouseLMB")
	{
		std::shared_ptr< Button > button = std::static_pointer_cast<Button>(body);

		for (b2ContactEdge* contact = button->getBody()->GetContactList(); contact != nullptr; contact = contact->next)
		{
			Body* a = static_cast<Body*>(contact->other->GetUserData());
			if (a->getType() == btMouse)
			{
				changeState("PressedState");
			}
		}
	}
	else
	{
		getCurrentState()->handleInput(body, event);
	}

}
void ButtonStateMachine::handleInput(std::shared_ptr<Body> body, std::shared_ptr< Event > event)
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