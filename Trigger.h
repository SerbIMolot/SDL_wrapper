#pragma once
#include "Body.h"
#include "Rectangle.h"
class b2Fixture;

class Trigger : public Body
{
	static int triggerCount;
	int id;

	std::string name;
	std::unique_ptr< b2FixtureDef > fixtureDef;
	std::unique_ptr< b2Fixture > fixture;
	std::shared_ptr< b2Vec2 > pos;

	std::shared_ptr< engRectangle > rect;

	bool triggered;

public:
	Trigger( std::shared_ptr< b2Vec2 > vec, int w, int h );
	Trigger( std::shared_ptr< b2Vec2 > vec, std::shared_ptr< engRectangle > rect );
	Trigger( int x, int y, int w, int h );

	void setName( std::string str );
	std::string getName(  );

	std::shared_ptr< engRectangle > getRect();


	~Trigger();

	bool Trigered();
	void trigger();

	void reset();


};



