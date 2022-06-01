#pragma once

#include <vector>
#include <string>
#include "Trigger.h"
#include "Body.h"
class TriggersManager
{
	//static std::shared_ptr< TriggersManager > trmInstance;
	//static std::unique_ptr< TriggersManager > trmInstance;

	std::shared_ptr< Trigger > playerGoal;
	std::shared_ptr< Trigger > aiGoal;

	TriggersManager();
	

public:
	~TriggersManager();

	 std::vector< std::shared_ptr< Trigger > > trigers;


	static TriggersManager* Instance();

	void addTrigger( int x, int y, int w, int h, std::string name );
	void addTrigger( std::shared_ptr< b2Vec2 > vec, int w, int h, std::string name );

	void Init();


	void collisionDetected( std::shared_ptr< Body > obj );

};

