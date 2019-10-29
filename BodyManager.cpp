#include "stdafx.h"
#include "BodyManager.h"

std::shared_ptr< BodyManager > BodyManager::objInstance = nullptr;
std::unique_ptr< Player > BodyManager::player = nullptr;
std::vector< std::shared_ptr< Body > > BodyManager::bodys = std::vector< std::shared_ptr< Body > >();

BodyManager::BodyManager()
{
	debug = false;
	debugFont = new NFont( "Data/FreeSans.ttf", 20, NFont::Color( 0, 0, 255, 255 ) );
	
}

BodyManager::~BodyManager()
{
	debugFont->free();
	delete debugFont;
}

std::shared_ptr<BodyManager> BodyManager::Instance()
{
	if ( objInstance == nullptr )
	{
		objInstance = std::make_shared< BodyManager >();
	}

	return objInstance;

}

int BodyManager::checkName( std::string nameID )
{
	int repeats = 0;

	for (auto body : mBodies)
	{
		if ( body.first[ 0 ] == nameID[ 0 ] && std::strncmp( body.first.c_str(), nameID.c_str(), body.first.size() ) == 0 )
		{
			nameID += std::to_string( repeats );
		}
	}

	return repeats;
}
void BodyManager::addBody(std::string name, std::shared_ptr< Body > body, BodyType btype)
{
	body->Init();
	bodys.push_back(body);
	mBodies[name] = body;
}

void BodyManager::createBody( std::string name, BodyType btype )
{
	if ( btype == btPlayer )
	{
		player = std::make_unique< Player >();
	}
}



void BodyManager::createBody( b2Vec2 pos, std::shared_ptr< Texture > textr, std::string name , BodyType btype )
{
	int nameRepeats = checkName( name );
	if ( nameRepeats > 0 )
	{
		name += std::to_string( nameRepeats );
	}
	if ( btype == btWall )
	{
		std::shared_ptr< Body > temp = std::make_shared< Body >( btype, pos, textr );
		bodys.push_back( temp );
		mBodies[ name ] = temp;
	}
	if ( btype == btBox )
	{
		std::shared_ptr< dynBody > temp = std::make_shared< dynBody >(btype, pos, textr, 0.65f, 0.35f );
		bodys.push_back( temp );
		mBodies[ name ] = temp;
	}
	if ( btype == btPlayer )
	{
		player = std::make_unique< Player >( pos );
	}
	if ( btype == btGun )
	{
		std::shared_ptr< Gun > temp = std::make_shared< Gun >();

		bodys.push_back( temp );
		mBodies[name] = temp;
	}
	GPU_Log("Body: %s\n", name.c_str());
}

void BodyManager::createBody( float x, float y, std::shared_ptr< Texture > textr, std::string name, BodyType btype )
{
	if ( btype == btWall )
	{
		std::shared_ptr< Body > temp = std::make_shared< Body >( btype, x, y, textr );
		bodys.push_back( temp );
		mBodies[ name ] = temp;
	}
	if ( btype == btBox )
	{
		std::shared_ptr< dynBody > temp = std::make_shared< dynBody >(btype, x, y, textr, 0.65f, 0.35f );
		bodys.push_back( temp );
		mBodies[ name ] = temp;
	}
	if ( btype == btPlayer )
	{
		player = std::make_unique< Player >( x, y );
		//createBody( player->getPos(), TextureManager::getTexture("Scope.png"), "gun", btGun);

	}
	if ( btype == btButton )
	{
		std::shared_ptr< Body > temp = std::make_shared< Button >( x, y, 10.0f, 10.0f, "textr" );
		bodys.push_back( temp );
		mBodies[ name ] = temp;
		//createBody( player->getPos(), TextureManager::getTexture("Scope.png"), "gun", btGun);

	}
	if ( btype == btGun )
	{
		std::shared_ptr< Gun > temp = std::make_shared< Gun >( );
		
		//bodys.push_back( temp );
		mBodies[ name ] = temp;
	}
	GPU_Log("Body: %s\n", name.c_str());
}

void BodyManager::createBody(b2Vec2 pos, std::shared_ptr<Texture> textr, float dencity, float friction, std::string name, BodyType btype)
{

}

void BodyManager::createJoint( JointType jType, std::string a, std::string b)
{
	if ( jType == RevoluteJoint )
	{ 
		b2RevoluteJointDef joint;
		joint.Initialize( getBody( a )->getBody() , getBody( b )->getBody(), getBody( a )->getPos() );

	}
}

std::shared_ptr< Body > BodyManager::getFirst()
{
	return mBodies.begin()->second ;
}

std::shared_ptr< Body > BodyManager::getBody( std::string name )
{
	if ( mBodies.find( name ) == mBodies.end() )
	{
		return nullptr;
	}
	else
	{
		return mBodies[name];
	}
	
}

std::shared_ptr<dynBody> BodyManager::getDynBody( std::string name )
{
	std::shared_ptr< dynBody > tempDynBod;

	if ( mBodies.find( name ) == mBodies.end() )
	{
		return nullptr;
	}
	else
	{
		
		tempDynBod = std::static_pointer_cast< dynBody > ( mBodies[ name ] );
		
		return tempDynBod;
	
	}
}

std::vector< std::shared_ptr< Body > > BodyManager::getBodys()
{
	return bodys;
}

Player* BodyManager::getPlayer()
{
	return player.get();
}

std::vector< std::shared_ptr< dynBody > > BodyManager::getBoxes( std::string name )
{
	std::shared_ptr< dynBody > box;

	std::vector< std::shared_ptr< dynBody > > boxes;

	for ( auto body : mBodies )
	{

		box = std::static_pointer_cast< dynBody > ( body.second );

		if ( box != nullptr && box->getType() == btBox )
		{
			boxes.push_back( box );
		}

	}

	return boxes;

}

std::vector< std::shared_ptr< dynBody > > BodyManager::getDynBodies( std::string name )
{
	std::shared_ptr< dynBody > tempDynBod;

	std::vector< std::shared_ptr< dynBody > > dynBodies;

	for ( auto body : mBodies )
	{

		tempDynBod = std::static_pointer_cast< dynBody > ( body.second );

		if ( tempDynBod != nullptr )
		{
			dynBodies.push_back( tempDynBod );
		}

	}

	return dynBodies;

}

std::vector< std::shared_ptr< Gun > > BodyManager::getGuns()
{
	std::shared_ptr< Gun > tempGun;

	std::vector< std::shared_ptr< Gun > > guns;

	for ( auto gun : mBodies )
	{

		tempGun = std::static_pointer_cast< Gun > ( gun.second );

		if ( tempGun != nullptr )
		{
			guns.push_back( tempGun );
		}

	}

	return guns;

}

std::shared_ptr< Gun > BodyManager::getGun( std::string name ) 
{
	for ( auto gun : mBodies )
	{
		if ( gun.second->getType() == btGun )
		{
			if ( gun.first.compare( name ) == 0 )
			{
				return std::static_pointer_cast< Gun >( gun.second );
			}
		}
	}

	return nullptr;
}

std::vector< std::shared_ptr< Body > > BodyManager::getWalls( std::string name )
{
	std::shared_ptr< Body > wall;

	std::vector< std::shared_ptr< Body > > walls;

	for ( auto body : mBodies )
	{

		wall = std::static_pointer_cast< Body > ( body.second );

		if ( wall != nullptr && body.second->getType() == btWall )
		{
			walls.push_back( wall );
		}

	}

	return walls;

}

void BodyManager::Draw()
{

	for ( auto body : mBodies )
	{

		body.second->Draw();

		if ( body.second->getType() == btGun )
		{
			std::static_pointer_cast< Gun > ( body.second )->Update();
		}


		if (debug == true)
		{
			//debugFont->draw( TextureManager::gRenderer, 100, 100, "IJDFOISJDOFIJSDOFIJSDOIFJOSDJFOSDJFOISDJFOISDJFOISDJFOSDJFOSDJFOISDJFOSDFJOSDFJ" );
			SDL_Log( " name: %s\n", body.first.c_str() );
			debugFont->draw( TextureManager::gRenderer, MeterToPixel( body.second->getPos().x ), MeterToPixel( body.second->getPos().y ), body.first.c_str() );
			debugFont->drawBox( TextureManager::gRenderer, NFont::Rectf( body.second->getPos().x, body.second->getPos().y, 0.2f, 0.2f ), "" );
		}

	}
	if ( player )
	{
		player->Draw();
	}
}

void BodyManager::Update()
{
	for ( auto bod : mBodies )
	{
		bod.second->Update();
	}
}

void BodyManager::handleInput( std::shared_ptr< Event > event )
{
	for( auto body : mBodies )
	{
		body.second->handleInput( event );
	}
}


void BodyManager::BodyDebug()
{
	if ( debug == false )
	{ 

		for (auto body : mBodies)
		{
			body.second->Debug();
		}

		debug = true;

	}
	else if ( debug == true )
	{ 

		for (auto body : mBodies)
		{
			body.second->Debug();
		}

		debug = false;

	}
}

// find object by type
/*	
	std::shared_ptr< Player > pl;

	for ( auto body : bodys )
	{
		 
		pl = std::static_pointer_cast< Player > ( body );

		if ( pl != nullptr )
		{
			return pl;
		}
	
	}

	return nullptr;
*/