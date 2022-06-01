#pragma once
#include "StateMachine.h"

class PressedState;
class ReleasedState;
class HoverState;

class ButtonStateMachine :
	public StateMachine
{
		std::shared_ptr< PressedState > pressed;
		std::shared_ptr< ReleasedState > released;
		std::shared_ptr< HoverState > hover;

	public:
		ButtonStateMachine();
		ButtonStateMachine(std::shared_ptr< Body > body);
		void Init();
		~ButtonStateMachine();

		void update(std::shared_ptr< Body > body);
		void handleInput(std::shared_ptr< Body > body, std::shared_ptr< GameEvent > event );
		void handleInput(std::shared_ptr< Body > body, std::shared_ptr< Event > event );

};

