#include "stdafx.h"
#include "CollisionShape.h"


CollisionShape::CollisionShape()
{
	colShape = std::vector< std::shared_ptr< Shape > >();
	std::list< int > test;

}


CollisionShape::~CollisionShape()
{
}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec)
{
	std::shared_ptr< Shape > point = std::make_shared< Shape >( vec, sPoint );
	colShape.push_back( point );
}

void CollisionShape::addShape(int x, int y)
{
	std::shared_ptr< Shape > point = std::make_shared< Shape >( static_cast< float >( x ), static_cast< float >( y ), sPoint );
	colShape.push_back( point );
}

void CollisionShape::addShape( float x, float y, float w, float h )
{
	std::shared_ptr< Shape > rect = std::make_shared< engRectangle >( x, y, w, h );
	colShape.push_back( rect );

}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, float w, float h)
{
	std::shared_ptr< Shape > rect = std::make_shared< engRectangle >(vec, w, h );
	colShape.push_back(rect);

}

void CollisionShape::addShape(float x, float y, float r)
{
	std::shared_ptr< Shape > circ = std::make_shared< engCircle >( x, y, r );
	colShape.push_back( circ );

}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, float r)
{
	std::shared_ptr< Shape > circ = std::make_shared< engCircle >( vec, r );
	colShape.push_back( circ );

}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, std::shared_ptr<Texture> textr, cShape shType)
{
	
	if ( shType == sCircle )
	{
		std::shared_ptr< Shape > circ = std::make_shared< engCircle >(vec, textr);
		colShape.push_back( circ );

	}
	if ( shType == sBox )
	{
		std::shared_ptr< Shape > rect = std::make_shared< engRectangle >( vec, textr );
		colShape.push_back( rect );

	}
}

void CollisionShape::Update( std::shared_ptr< Vector2d > vec )
{
	for( auto sh : colShape )
	{
		sh->Update( vec );
	}
}

void CollisionShape::Update(float x, float y)
{
	for (auto sh : colShape)
	{
		sh->Update( x, y );
	}
}

std::vector< std::shared_ptr< Shape > > CollisionShape::getShapes()
{
	return colShape;
}

std::shared_ptr< Shape > CollisionShape::getFirst()
{

	return colShape.front();

}

std::shared_ptr< engCircle > CollisionShape::getCircle( int index )
{
	if ( index >= 0 )
	{
		if ( colShape[ index ]->getType() != sCircle )
		{
			return nullptr;
		}

		return std::static_pointer_cast< engCircle >( colShape[ index ] );
	
	}

	return nullptr;

}

std::shared_ptr< engRectangle > CollisionShape::getRectangle( int index )
{
	if (index >= 0)
	{
		if ( colShape[index]->getType() != sBox )
		{
			return nullptr;
		}
		
		return std::static_pointer_cast< engRectangle >( colShape[ index ] );

	}

	return nullptr;

}

std::shared_ptr< Shape > CollisionShape::getPoint( int index )
{
	if ( index >= 0 )
	{
		if ( colShape[ index ]->getType() != sPoint )
		{
			return nullptr;
		}

		return std::static_pointer_cast< Shape >( colShape[ index ] );

	}

	return nullptr;

}