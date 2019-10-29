#include "StateMachine.h"

StateMachine::StateMachine()
{
	stateQuery = std::make_unique< std::list< std::string > >();

	stateHolder = nullptr;
}

StateMachine::~StateMachine()
{
}

/*
void StateMachine::createState(std::string name, std::string neighbors)
{
	states[ name ] = std::make_unique< State >( name, neighbors );
}
*/
bool StateMachine::isNeighnors(std::string state, std::string secondState)
{
	std::vector< std::string > tempNeighbors = states.at(state)->getNeighbors();
	std::vector< std::string >::iterator pos = std::find( tempNeighbors.begin(), tempNeighbors.end(), secondState.c_str() );

	try
	{
		if ( pos != tempNeighbors.end() )
		{
			return true;
		}
	}
	catch (std::out_of_range & e)
	{
		GPU_Log("Machiche has no such state. %s", e.what());
		return false;
	}

	return false;
}

bool StateMachine::changeState(std::string name)
{
	if (isNeighnors(getCurrentState()->getName(), name))
	{
		Push(name);
		getCurrentState()->atStart( stateHolder );
		return true;
	}
	return false;
}

State* StateMachine::getCurrentState()
{
	try
	{
		return states.at( stateQuery->front() );
	}
	catch (std::exception & e)
	{
		GPU_Log( "There is no current state: ERROR %s", e.what() );
		return nullptr;
	}
}


void StateMachine::setDefaultState(std::string stateID)
{
	if (states.find(stateID) != states.end())
	{
		stateQuery->push_back(stateID);
	}
	else
	{
		GPU_Log("No such state exist");
	}
}

void StateMachine::Add(State* state)
{
	states[state->getName()] = state;

	states[state->getName()]->setMachine( shared_from_this() );
}

bool StateMachine::Remove(std::string id)
{
	return states.erase(id);
}

void StateMachine::Clear()
{
	states.clear();
	stateQuery->clear();
}

void StateMachine::setHolder(std::shared_ptr< Body > body)
{
	stateHolder = std::move(body);
}

void StateMachine::Push(std::string stateID)
{
	if (states.find(stateID) != states.end())
	{
		stateQuery->push_front(stateID);
	}
	else
	{
		GPU_Log("No such state exist");
	}
}

void StateMachine::Pop()
{
	if (stateQuery->size() != 1)
	{
		stateQuery->pop_front();
	}
}