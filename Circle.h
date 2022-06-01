#pragma once
#include "Shape.h"
#include "Texture.h"

class engCircle : public Shape
{

	float radius;

public:
	engCircle( std::shared_ptr< Vector2d >, std::shared_ptr< Texture > );

	engCircle(int x, int y, std::shared_ptr< Texture > );

	engCircle(float x, float y, float radius );
	engCircle(int x = 0, int y = 0, int radius = 0 );

	engCircle( std::shared_ptr< Vector2d >, int radius);

	float upperCircle(float x);

	double lowerCircle(float x);


	void setVec( std::shared_ptr< Vector2d > vec );
	std::shared_ptr< Vector2d > getVec();


	void setRadius( float rad );
	void setRadius( int rad );

	float getRadius();
};
