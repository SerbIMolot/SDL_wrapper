#pragma once
#include "StateMachine.h"
#include "PressedState.h"
#include "ReleasedState.h"

class ButtonStateMachine :
	public StateMachine
{
		std::shared_ptr< PressedState > pressed;
		std::shared_ptr< ReleasedState > released;

	public:
		ButtonStateMachine();
		void Init();
		~ButtonStateMachine();

		void update(std::shared_ptr< Body > body);
		void handleInput(std::shared_ptr< Body > body, std::shared_ptr< Event > event );

};

