#include "Body.h"
#include "SDL_wrapper.h"
#include "Texture.h"



Body::Body()
{
	parent = nullptr;
	jointWithParent = nullptr;
	textureFlip = SDL_FLIP_NONE;
}
Body::Body( BodyType btype, b2Vec2 vec, std::shared_ptr<Texture> textr )
{
	debug = true;
	SDL_Log("BODY con");
	this->btype = btype;

	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set( vec.x , vec.y );
	groundBody = SDL_wrapper::world->CreateBody( &groundBodyDef );
	
	if (textr)
	{
		texture = std::move(textr);
		groundBox.SetAsBox(PixelToMeter(texture->getWidth() / 2), PixelToMeter(texture->getHeight() / 2));
	}
	else
	{
		texture = nullptr;
		groundBox.SetAsBox( PixelToMeter(10), PixelToMeter(10) );
	}
	
	groundBody->CreateFixture( &groundBox, 0.0f );
	
	groundBody->SetUserData( ( void* ) this );

	parent = nullptr;
	jointWithParent = nullptr;
	textureFlip = SDL_FLIP_NONE;
}

Body::Body( BodyType btype, float x, float y, std::shared_ptr<Texture> textr )
{
	debug = false;
	SDL_Log("BODY con");
	this->btype = btype;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set( x , y );

	groundBody = SDL_wrapper::world->CreateBody( &groundBodyDef );

	if (textr)
	{
		texture = std::move(textr);
		groundBox.SetAsBox(PixelToMeter(texture->getWidth() / 2), PixelToMeter(texture->getHeight() / 2));
	}
	else
	{
		texture = nullptr;
		groundBox.SetAsBox(PixelToMeter(10), PixelToMeter(10));
	}

	groundBody->CreateFixture( &groundBox, 0.0f )->SetUserData( ( void* ) this );

	parent = nullptr;
	jointWithParent = nullptr;

	textureFlip = SDL_FLIP_NONE;
//	groundBody->GetFixtureList()->SetUserData( ( void* ) this );
	//fixture->;
}


Body::~Body()
{
	//delete groundBody;
}

void Body::Draw()
{
		//printf( "Pos = %f : %f\n", ( groundBody->GetPosition().x) * MtPratio, (groundBody->GetPosition().y ) * MtPratio );

		//printf("Rotation = %f \n", groundBody->GetAngle() * ( 180.0f / 3.141592653589793238463f) );
	//printf( "Pos = %f : %f\n", ( groundBody->GetPosition().x - ( ( texture->getWidth() / 2 ) * PtMratio ) ) * MtPratio, (groundBody->GetPosition().y - ( texture->getHeight() / 2) * PtMratio ) * MtPratio );
	//printf( "POS = %f, %f\n", getPos().x, getPos().y );
	//printf( "POS Pix = %f, %f\n", MeterToPixel( getPos().x ), MeterToPixel( getPos().y ) );
	
	//texture->render( ( groundBody->GetPosition().x  ) * MtPratio, ( groundBody->GetPosition().y ) * MtPratio );
	if ( texture )
	{ 
		texture->render( MeterToPixel( groundBody->GetPosition().x ) - texture->getWidth() / 2  , MeterToPixel( groundBody->GetPosition().y ) - texture->getHeight() / 2 , nullptr, groundBody->GetAngle() * RtDratio, 0.0f, 0.0f, textureFlip );
	}
}

void Body::Update()
{
	
}

BodyType Body::getType()
{
	return btype;
}

bool Body::getCollisionWithParent()
{
	return colisionWithParent;
}

void Body::setParent( std::shared_ptr<Body> par, bool collide )
{
	parent = std::move( par );

	colisionWithParent = collide;
	setRelativePos( parent->getPos() - getPos() );


	//data.center = parent->getPos();

	//groundBody->SetMassData( &data );
	//groundBody->SetTransform( parent->getPos() - relativePosition, groundBody->GetAngle() - relativeAngle );
}

void Body::setCollisionWithParent( bool col )
{
	colisionWithParent = col;
}

void Body::setSkin( std::shared_ptr< Texture > texture )
{
	if ( texture )
	{
		this->texture = std::move( texture );
		groundBox.SetAsBox( PixelToMeter(this->texture->getWidth() / 2), PixelToMeter(this->texture->getHeight() / 2) );
	}
}
std::shared_ptr<Texture> Body::getSkin()
{
	return texture;
}
void Body::setParent( Body* par, bool collide )
{
	parent.reset( par );
	colisionWithParent = collide;
	setRelativePos( parent->getPos() - getPos() );
}

std::shared_ptr<Body> Body::getParent()
{
	return parent;
}

void Body::Debug()
{
	if ( debug == false )
	{
		GPU_Log("ON\n");
		texture->setRGBA( 255, 0, 0 );

		debug = true;

	}
	else if ( debug == true )
	{
		
		GPU_Log("OFF\n");
		texture->setRGBA( 255, 255, 255 );

		debug = false;
	}
}

b2Body * const Body::getBody() const
{
	return groundBody;
}

void Body::rotateTo(float angle)
{
	
	float nextAngle = groundBody->GetAngle() + groundBody->GetAngularVelocity() / 60.0f;

	float totalRotation = angle - nextAngle;
	
	while ( totalRotation < -180 * DtRratio ) totalRotation += 360 * DtRratio;
	while ( totalRotation >  180 * DtRratio ) totalRotation -= 360 * DtRratio;
	
	groundBody->ApplyTorque( totalRotation < 0.0 ? -0.005f : 0.005f, true );
}

void Body::setID(std::string ID)
{
	nameID = ID;
}

std::string Body::getID() const
{
	return nameID;
}


void Body::handleInput( std::shared_ptr< Event > newEvent )
{
}

bool Body::operator==(const Body& rhs)
{
	if ( *shared_from_this() == rhs )
	return false;
}
bool Body::operator==(const Body* rhs)
{
	if ( *shared_from_this() == rhs )
	return false;
}


b2Vec2 Body::getPos()
{
	return groundBody->GetPosition();
}

b2Vec2* Body::getRelativePos()
{
	if ( parent != nullptr )
	{ 
		return &relativePosition;
	}
	else
	{
		return nullptr;
	}
}

GPU_FlipEnum Body::getTextureFlip()
{
	return textureFlip;
}

void Body::setTextureFlip( GPU_FlipEnum flip )
{
	textureFlip = flip;
}


void Body::setPos( b2Vec2 pos )
{
	getBody()->SetTransform( pos, groundBody->GetAngle() );
}

void Body::setPos( float posX, float posY )
{
	getBody()->SetTransform( b2Vec2( posX, posY ), groundBody->GetAngle() );
}

void Body::setRelativePos( b2Vec2 pos )
{
	if ( parent != nullptr )
	{ 

		if ( jointWithParent != nullptr )
		{ 
			SDL_wrapper::world->DestroyJoint( jointWithParent );
		}

		b2RevoluteJointDef* wJoint = new b2RevoluteJointDef();

		relativePosition = pos;
	
		//groundBody->SetTransform( parent->getPos() + relativePosition, groundBody->GetAngle() + relativeAngle );

		setPos( parent->getPos() );

		wJoint->bodyA = parent->getBody();
		wJoint->bodyB = getBody();

		wJoint->localAnchorA = b2Vec2( 0, 0 );
		wJoint->localAnchorB = b2Vec2( 0, 0 );

		wJoint->collideConnected = false;

		jointWithParent = ( b2RevoluteJoint* )SDL_wrapper::world->CreateJoint( wJoint );

		delete wJoint;

	}
}

void Body::setRelativePos( float32 x, float32 y )
{
	if ( parent != nullptr )
	{

		if ( jointWithParent != nullptr )
		{ 
			SDL_wrapper::world->DestroyJoint( jointWithParent );
		}

		b2RevoluteJointDef* wJoint = new b2RevoluteJointDef();

		relativePosition = b2Vec2( x, y );

		SDL_wrapper::world->DestroyJoint( jointWithParent );
	
		groundBody->SetTransform( parent->getPos() + relativePosition, groundBody->GetAngle() + relativeAngle );

		wJoint->bodyA = parent->getBody();
		wJoint->bodyB = getBody();

		wJoint->localAnchorA = b2Vec2( 0, 0 );
		wJoint->localAnchorB = b2Vec2( 0, 0 );

		wJoint->collideConnected = jointWithParent->GetCollideConnected();

		jointWithParent = ( b2RevoluteJoint* )SDL_wrapper::world->CreateJoint( wJoint );

		delete wJoint;

	}
}

void Body::setLowerBound( b2Vec2 lwB )
{
	groundBox.SetAsBox( lwB.x, lwB.y );

	currentFixture.shape = &groundBox;
	groundBody->CreateFixture( &currentFixture);
}

void Body::isSensor( bool newSensor )
{

	groundBody->GetFixtureList()->SetSensor( newSensor );
}