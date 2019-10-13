#include "stdafx.h"

StateMachine::StateMachine()
{
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
bool StateMachine::isNeighnors( std::string state, std::string secondState )
{

	std::vector< std::string >::iterator pos;

	try
	{
		pos = std::find( states.at( state )->getNeighbors().begin(), states.at( state )->getNeighbors().end(), secondState );

		if ( pos != states.at( state )->getNeighbors().end() )
		{
			return true;
		}
	}
	catch ( std::out_of_range& e )
	{
		GPU_Log("Machiche has no such state. %s", e.what());
		return false;
	}

	return false;
}

bool StateMachine::changeState( std::string name )
{
	if ( isNeighnors( getCurrentState()->getName(), name ) )
	{
		Push( name );
	}
	return false;
}

State* StateMachine::getCurrentState()
{
	try
	{
		return states.at( stateQuery->front() );
	}
	catch ( std::out_of_range& e )
	{
		GPU_Log("There is no current state");
		return nullptr;
	}
}


void StateMachine::setDefaultState( std::string stateID )
{
	if ( states.find( stateID ) != states.end() )
	{
		stateQuery->push_back( stateID );
	}
	else
	{
		GPU_Log("No such state exist");
	}
}

void StateMachine::Add( State* state )
{
	states[ state->getName() ] = state;
}

bool StateMachine::Remove( std::string id )
{
	return states.erase( id );
}

void StateMachine::Clear()
{
	states.clear();
	stateQuery->clear();
}

void StateMachine::Push( std::string stateID )
{
	if ( states.find( stateID ) != states.end() )
	{
		stateQuery->push_front( stateID );
	}
	else
	{
		GPU_Log("No such state exist");
	}
}

void StateMachine::Pop()
{
	if ( stateQuery->size() != 1 )
	{
		stateQuery->pop_front();
	}
}

State::State(std::string name)
{
	this->name = name;
}

State::State( std::string name, std::string neighbors )
{
	this->name = name;

	addNeighbors( neighbors );
}

void State::addNeighbors(std::string newNeighbors)
{
	size_t pos = 0;

	while ( pos != std::string::npos )
	{
		pos = newNeighbors.find( DELIMETER );

		neighbors.push_back( newNeighbors.substr( 0, pos ) );

		newNeighbors.erase( 0, pos + sizeof( DELIMETER ));
	}
}
