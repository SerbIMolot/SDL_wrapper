#include "Trigger.h"
#include "Box2d.h"


Trigger::Trigger(std::shared_ptr< b2Vec2 > vec, int w, int h)
	:	Body( btTrigger, *vec )
{
	setLowerBound( b2Vec2( w, h ) );
}

Trigger::Trigger(std::shared_ptr< b2Vec2 > vec, std::shared_ptr<engRectangle> rect)
	:	Body( btTrigger, *vec )
{
	setLowerBound( b2Vec2( rect->w, rect->h ) );
}

Trigger::Trigger(int x, int y, int w, int h)
	:	Body( btTrigger, x, y )
{
	setLowerBound( b2Vec2( w, h ) );
}

void Trigger::setName(std::string str)
{
	name = str;
}

std::string Trigger::getName()
{
	return name;
}

std::shared_ptr<engRectangle> Trigger::getRect()
{
	return rect;
}

Trigger::~Trigger()
{
}

bool Trigger::Trigered()
{
	return triggered;
}

void Trigger::trigger()
{
	triggered = true;
}

void Trigger::reset()
{
	triggered = false;
}
