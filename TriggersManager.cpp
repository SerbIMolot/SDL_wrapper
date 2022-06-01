
#include "TriggersManager.h"


//std::unique_ptr< TriggersManager > TriggersManager::trmInstance = nullptr;

TriggersManager::TriggersManager()
{
}


TriggersManager::~TriggersManager()
{
	trigers.clear();

	//delete trmInstance;
	
}

TriggersManager* TriggersManager::Instance()
{
	static TriggersManager* trmInstance;

	return trmInstance;
}

void TriggersManager::addTrigger(int x, int y, int w, int h, std::string name)
{

	std::shared_ptr< Trigger > tr = std::make_shared< Trigger >( x, y, w, h );

	tr->setName( name );

	trigers.push_back( tr );

	//GPU_Log( "Trigger: %s\n", name.c_str() );

}

void TriggersManager::addTrigger(std::shared_ptr< b2Vec2 > vec, int w, int h, std::string name)
{
	std::shared_ptr< Trigger > tr = std::make_shared< Trigger >( vec, w, h );

	tr->setName( name );

	trigers.push_back( tr );
}

void TriggersManager::Init()
{
	
}

void TriggersManager::collisionDetected( std::shared_ptr< Body > obj )
{

	for ( auto tr : trigers )
	{

		if( strcmp( tr->getName().c_str() , "AiGoal" ) && tr->Trigered() == true 
			&& obj->getType() == btUnknown )
		{

		}

		if ( strcmp(tr->getName().c_str(), "PlGoal") && tr->Trigered() == true 
			&& obj->getType() == btUnknown)
		{


		}



	}


}
