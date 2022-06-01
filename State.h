#pragma once

#include <vector>
#include <unordered_set>
#include "EventData.h"

#define DELIMETER ','

 class StateMachine;
class Body;

class State
{
	std::string name;
	std::unordered_set< std::string > neighbors;
	
	std::shared_ptr< StateMachine > stateMachine = nullptr;
public:
	State( std::string name, std::shared_ptr< StateMachine > stateMach = nullptr )
		: name( name ), stateMachine( stateMach )  {}
	State( std::string name, std::string neighbors, std::shared_ptr< StateMachine > stateMach = nullptr )
		: name( name ), stateMachine( stateMach )
	{
		addNeighbors( neighbors );
	}

	virtual ~State() {}

	virtual bool checkPreCondition() { return true; }

	virtual void atStart( std::shared_ptr< Body > body ) = 0;
	virtual void update( std::shared_ptr< Body > body ) = 0;
	virtual bool handleInput( std::shared_ptr< Body > body, std::shared_ptr< Event > newEvent ) = 0;
	virtual bool handleInput( std::shared_ptr< Body > body, std::shared_ptr< GameEvent > newEvent ) = 0;

	std::string getName() { return name; }
	std::unordered_set< std::string > getNeighbors() { return neighbors; }

	bool isNeighbors( std::string stateName ) 
	{
		return neighbors.find( stateName ) != neighbors.end();
	}

	void addNeighbors(std::string newNeighbors)
	{
		size_t pos = 0;

		while (pos != std::string::npos)
		{
			pos = newNeighbors.find(DELIMETER);

			neighbors.insert(newNeighbors.substr(0, pos));

			newNeighbors.erase(0, pos + sizeof(DELIMETER));
		}
	}

	void setMachine( std::shared_ptr < StateMachine > stateMachine ) { this->stateMachine = std::move( stateMachine ); }

	std::shared_ptr< StateMachine > getMachine() { return this->stateMachine; }
};

