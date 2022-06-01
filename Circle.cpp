
#include "Circle.h"

engCircle::engCircle(std::shared_ptr<Vector2d> vec, std::shared_ptr<Texture> textr )
	: Shape( vec, sCircle )
{

	setRadius( textr->getHeight() / 2 );

}

engCircle::engCircle(int x, int y, std::shared_ptr<Texture> textr)
	: Shape( static_cast<float>( x ), static_cast<float>( y ), sCircle )
{

	setRadius( textr->getHeight() / 2 );

}

engCircle::engCircle(float x, float y, float radius)
	: Shape( x, y, sCircle)
{

		setRadius(radius);
}

engCircle::engCircle(int x, int y, int radius)
	: Shape( static_cast< float >( x ), static_cast< float >( y ), sCircle )
{

	setRadius( radius );

}

engCircle::engCircle(std::shared_ptr<Vector2d> vec, int radius)
	: Shape( vec, sCircle )
{

	setRadius( radius );

}

float engCircle::upperCircle( float x )
{
	return Pos()->getY() - sqrtf( ( getRadius() * getRadius() ) - ( ( x - Pos()->getX() ) * ( x - Pos()->getX() ) ) );
}

double engCircle::lowerCircle( float x )
{
	return Pos()->getY() + sqrtf( ( getRadius() * getRadius() ) - ( ( x - Pos()->getX() ) * (x - Pos()->getX() ) ) );
}

void engCircle::setVec(std::shared_ptr<Vector2d> vec)
{
	Update( vec );
}

std::shared_ptr<Vector2d> engCircle::getVec()
{
	return Pos();
}

void engCircle::setRadius( float rad )
{
	radius = rad;
}

void engCircle::setRadius( int rad )
{
	radius = static_cast< float >( rad );
}

float engCircle::getRadius()
{
	return radius;
}
