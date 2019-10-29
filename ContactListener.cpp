#include "stdafx.h"
#include "ContactListener.h"

std::shared_ptr< ContactListener > ContactListener::conInstance = nullptr;



ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}

std::shared_ptr< ContactListener > ContactListener::Instance()
{
	
	if ( conInstance == nullptr )
	{
		conInstance = std::make_unique< ContactListener >();
	}

	return conInstance;
}

void ContactListener::BeginContact(b2Contact * contact)
{
	Body* a = static_cast< Body* >( contact->GetFixtureA()->GetUserData() );
	Body* b = static_cast< Body* >( contact->GetFixtureB()->GetUserData() );

	if ( a != nullptr && b != nullptr )
	{
		if ( a->getType() == btTrigger )
		{
			dynamic_cast< Trigger* >( a )->trigger();
		}
		if ( b->getType() == btTrigger )
		{
			dynamic_cast< Trigger* >( b )->trigger();
		}
	}
	

	
	
	//std::cout << a->getType()  << "\n";
	//std::cout << b->getType() << "\n";
	// contact->GetFixtureB();
}

void ContactListener::EndContact(b2Contact * contact)
{
	Body* a = static_cast<Body*>(contact->GetFixtureA()->GetUserData());
	Body* b = static_cast<Body*>(contact->GetFixtureB()->GetUserData());
	if (a != nullptr && b != nullptr)
	{
		if (a->getType() == btTrigger)
		{
			dynamic_cast<Trigger*>(a)->reset();
		}
		if (b->getType() == btTrigger)
		{
			dynamic_cast<Trigger*>(b)->reset();
		}
	}
}

void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	Body* a = static_cast<Body*>(contact->GetFixtureA()->GetUserData());
	Body* b = static_cast<Body*>(contact->GetFixtureB()->GetUserData());

	if (a != nullptr && b != nullptr)
	{


		if (a->getType() == btPlayer && b->getType() == btGun
			|| b->getType() == btPlayer && a->getType() == btGun)
		{
			SDL_Log("Collision of Gun and player disabled");
			contact->SetEnabled( false );
		}
		if ( a->getType() == btGun || b->getType() == btGun )
		{
			SDL_Log("Collision of Gun and Gun disabled");
			contact->SetEnabled( false );
		}
	}	
}

void ContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	Body* a = static_cast<Body*>(contact->GetFixtureA()->GetUserData());
	Body* b = static_cast<Body*>(contact->GetFixtureB()->GetUserData());

	if (a != nullptr && b != nullptr)
	{

	}
}
bool ContactListener::ShouldCollide(b2Fixture * fixtureA, b2Fixture * fixtureB)
{
		const b2Filter& filterA = fixtureA->GetFilterData();
		const b2Filter& filterB = fixtureB->GetFilterData();
		Body* a = static_cast<Body*>( fixtureA->GetUserData() );
		Body* b = static_cast<Body*>( fixtureB->GetUserData() );

		if (a->getType() == btPlayer && b->getType() == btGun
			|| b->getType() == btPlayer && a->getType() == btGun )
		{
			SDL_Log("Collision of parent and child disabled");
			return false;
		}
		if (filterA.groupIndex == filterB.groupIndex && filterA.groupIndex != 0)
		{
			return filterA.groupIndex > 0;
		}
		bool collide = (filterA.maskBits & filterB.categoryBits) != 0 &&
			(filterA.categoryBits & filterB.maskBits) != 0;
		return collide;
}