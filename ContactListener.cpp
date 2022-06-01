
#include "ContactListener.h"
#include "Trigger.h"

std::shared_ptr< ContactListener > ContactListener::conInstance = nullptr;

class Trigger;
class Gun;

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
	
}

void ContactListener::EndContact(b2Contact * contact)
{
	Body* a = static_cast<Body*>(contact->GetFixtureA()->GetUserData());
	Body* b = static_cast<Body*>(contact->GetFixtureB()->GetUserData());
	if (a != nullptr && b != nullptr)
	{
		if (a->getType() == btTrigger)
		{
			static_cast<Trigger*>(a)->reset();
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
			contact->SetEnabled( false );
		}
		if ( a->getType() == btGun || b->getType() == btGun )
		{
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
bool ContactListener::BeginContactImmediate(b2Contact* contact, uint32 threadId)
{
	return true;
}
bool ContactListener::EndContactImmediate(b2Contact* contact, uint32 threadId)
{
	return true;
}
bool ContactListener::PreSolveImmediate(b2Contact* contact, const b2Manifold* oldManifold, uint32 threadId)
{
	return true;
}
bool ContactListener::PostSolveImmediate(b2Contact* contact, const b2ContactImpulse* impulse, uint32 threadId)
{
	return true;
}
bool ContactListener::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB, uint32 threadId)
{
	const b2Filter& filterA = fixtureA->GetFilterData();
	const b2Filter& filterB = fixtureB->GetFilterData();
	Body* a = static_cast<Body*>(fixtureA->GetUserData());
	Body* b = static_cast<Body*>(fixtureB->GetUserData());

	if (b->ShouldCollide(a) || a->ShouldCollide(b)) {
		return true;
	}
	if (filterA.groupIndex == filterB.groupIndex && filterA.groupIndex != 0)
	{
		return filterA.groupIndex > 0;
	}
	bool collide = (filterA.maskBits & filterB.categoryBits) != 0 &&
		(filterA.categoryBits & filterB.maskBits) != 0;
	return collide;
}