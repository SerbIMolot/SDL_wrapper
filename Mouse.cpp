#include "Mouse.h"


Mouse::Mouse()
	: Body( btMouse, -10.0f, -10.0f, TextureManager::getTexture("Scope.png") )
{
	//getColShape()->addShape( -10, -10 );

	grabbedObj = nullptr;
	LMBHold = false;
	isSensor( true );
	
}


Mouse::~Mouse()
{
}

void Mouse::Init()
{
}

void Mouse::grabObj( std::shared_ptr< Body > obj )
{
	grabbedObj = std::move( obj );
}

void Mouse::releaseObj()
{
	grabbedObj.reset();
}


void Mouse::UpdateStats( int x, int y, bool isReleased, int button )
{
	setPos( static_cast< float >( x ) , static_cast< float >( y ) );

	if ( isReleased == false && button == SDL_BUTTON_LEFT )
	{
		LMBHold = true;
		
	}
	else if ( isReleased == true && button == SDL_BUTTON_LEFT )
	{
		LMBHold = false;

		releaseObj();
	}
	if ( isReleased == false && button == SDL_BUTTON_RIGHT )
	{
		RMBHold = true;
	}
	else if ( isReleased == true && button == SDL_BUTTON_RIGHT )
	{
		RMBHold = false;
	}

	//getColShape()->Update( Pos() );
	
}

void Mouse::Update()
{

	//if (grabbedObj != nullptr && LMBHold == true)
	//{
	//	grabbedObj->setPos( getPos().x, getPos().y );
	//}


	//getColShape()->Update( Pos() );


}

void Mouse::Draw()
{
	Body::Draw();



}

void Mouse::collisionDetected( std::shared_ptr < Body > obj )
{

	if( obj->getType() == btButton && LMBHold == true )
	{
		
	}
}

bool Mouse::isLMBHold()
{
	return LMBHold;
}
bool Mouse::isRMBHold()
{
	return RMBHold;
}



