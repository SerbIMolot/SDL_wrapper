#pragma once
#include <memory>
#include <map>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include "SDL_gpu.h"
#include "State.h"
#include "Body.h"

class StateMachine
	: public std::enable_shared_from_this< StateMachine >
{
	std::map< std::string, State* > states;
	std::unique_ptr< std::list< std::string > > stateQuery;

	std::shared_ptr< Body > stateHolder;

	void Push(std::string stateId);
public:

	StateMachine();
	~StateMachine();

	//void createState( std::string name, std::string neighbors );

	bool isNeighnors(std::string state, std::string secondState);

	bool changeState(std::string name);

	State* getCurrentState();

	void setDefaultState(std::string stateID);

	void Add(State* state);
	bool Remove(std::string id);
	void Clear();

	void setHolder(std::shared_ptr< Body > body);

	virtual void update() { getCurrentState()->update(stateHolder); }
	virtual void handleInput( std::shared_ptr< Event > event ) { getCurrentState()->handleInput( stateHolder, event ); }


	void Pop();

};

