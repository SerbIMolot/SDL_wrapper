#pragma once
#include "Box2d.h"
class ContactListener : public b2ContactListener, public b2ContactFilter
{

	static std::shared_ptr< ContactListener > conInstance;

public:
	ContactListener();
	~ContactListener();

	static std::shared_ptr< ContactListener > Instance();

	void BeginContact( b2Contact* contact ) override;

	void EndContact( b2Contact* contact ) override;

	void PreSolve( b2Contact* contact , const b2Manifold* oldManifold ) override;

	void PostSolve( b2Contact* contact, const b2ContactImpulse* impulse ) override;

	bool BeginContactImmediate(b2Contact* contact, uint32 threadId) override;

	bool EndContactImmediate(b2Contact* contact, uint32 threadId) override;

	bool PreSolveImmediate(b2Contact* contact, const b2Manifold* oldManifold, uint32 threadId) override;

	virtual bool PostSolveImmediate(b2Contact* contact, const b2ContactImpulse* impulse, uint32 threadId) override;

	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB, uint32 threadId) override;
};

