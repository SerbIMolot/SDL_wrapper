#pragma once
#define DELIMETER ','
class State
{
	std::string name;
	std::vector< std::string > neighbors;
public:
	State( std::string name );
	State( std::string name, std::string neighbors );
	virtual ~State() = 0;

	virtual void update() = 0;
	virtual void handleInput( SDL_Scancode key ) = 0;

	std::string getName() { return name; }
	std::vector< std::string > getNeighbors() { return neighbors; }

	void addNeighbors(std::string newNeighbors);
};

class StateMachine
{
	std::map< std::string , State* > states;
	std::unique_ptr< std::list< std::string > > stateQuery;

	void Push( std::string stateId );
public:

	StateMachine();
	~StateMachine();

	//void createState( std::string name, std::string neighbors );

	bool isNeighnors(std::string state, std::string secondState);

	bool changeState( std::string name );

	State* getCurrentState();

	void setDefaultState( std::string stateID );

	void Add( State* state );
	bool Remove( std::string id );
	void Clear();


	void Pop();

};
