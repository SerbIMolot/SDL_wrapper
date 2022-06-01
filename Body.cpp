#include "Body.h"
#include "Texture.h"
#include "Box2D.h"

#include "Constants.h"
#include "EventData.h"


class SDL_wrapper;

Body::Body()
{
	parent = nullptr;
	jointWithParent = nullptr;
	textureFlip = SDL_FLIP_NONE;
}
Body::Body( BodyType btype, b2Vec2 vec, std::shared_ptr<Texture> textr )
{
	debug = true;

	this->btype = btype;
	groundBodyDef = new b2BodyDef();

	groundBox = std::make_shared<b2PolygonShape>();
	groundBodyDef->type = b2_staticBody;
	groundBodyDef->position.Set(PixelToMeter(vec.x) , PixelToMeter(vec.y) );
	groundBody = getWBox2DWorld()->CreateBody( groundBodyDef );

	delete groundBodyDef;
	if (textr)
	{
		texture = std::move(textr);
		groundBox->SetAsBox(PixelToMeter(texture->getWidth() / 2), PixelToMeter(texture->getHeight() / 2));
	}
	else
	{
		texture = nullptr;
		groundBox->SetAsBox( PixelToMeter(10), PixelToMeter(10) );
	}
	
	groundBody->CreateFixture( groundBox.get(), 0.0f);
	
	groundBody->SetUserData( ( void* ) this );

	parent = nullptr;
	jointWithParent = nullptr;
	textureFlip = SDL_FLIP_NONE;
}

Body::Body( BodyType btype, float x, float y, std::shared_ptr<Texture> textr )
{
	debug = false;

	this->btype = btype;
	groundBodyDef = new b2BodyDef();
	groundBox = std::make_shared<b2PolygonShape>();

	groundBodyDef->type = b2_staticBody;
	groundBodyDef->position.Set(PixelToMeter(x), PixelToMeter(y));

	groundBody = getWBox2DWorld()->CreateBody( groundBodyDef );
	
	delete groundBodyDef;

	if (textr)
	{
		texture = std::move(textr);
		groundBox->SetAsBox(PixelToMeter(texture->getWidth() / 2), PixelToMeter(texture->getHeight() / 2));
	}
	else
	{
		texture = nullptr;
		groundBox->SetAsBox(PixelToMeter(10), PixelToMeter(10));
	}

	groundBody->CreateFixture( groundBox.get(), 0.0f)->SetUserData((void*)this);

	parent = nullptr;
	jointWithParent = nullptr;

	textureFlip = SDL_FLIP_NONE;
}


Body::~Body()
{
}

void Body::Draw()
{
	if ( texture )
	{ 
		float angle = groundBody->GetAngle() * RtDratio;
		texture->render( MeterToPixel( groundBody->GetPosition().x ) - texture->getWidth() / 2  , MeterToPixel( groundBody->GetPosition().y ) - texture->getHeight() / 2 , nullptr, angle, 0, 0, textureFlip );
		
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
		groundBox->SetAsBox( PixelToMeter(this->texture->getWidth() / 2), PixelToMeter(this->texture->getHeight() / 2) );
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
		texture->setRGBA( 255, 0, 0 );

		debug = true;

	}
	else if ( debug == true )
	{
		texture->setRGBA( 255, 255, 255 );

		debug = false;
	}
}

b2Body* const Body::getBody() const
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
	if ( nameID  == rhs.nameID )
	{
		return true;
	}
	return false;
}
bool Body::operator==(const Body* rhs)
{
	if ( nameID  == rhs->nameID )
	{
		return true;
	}
	return false;
}


b2Vec2 Body::getPos()
{
	return groundBody->GetPosition();
}

std::shared_ptr< b2Vec2 > Body::getRelativePos()
{
	if ( parent != nullptr )
	{ 
		return relativePosition;
	}
	else
	{
		return nullptr;
	}
}

SDL_RendererFlip Body::getTextureFlip()
{
	return textureFlip;
}

void Body::setTextureFlip( SDL_RendererFlip flip )
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
			getWBox2DWorld()->DestroyJoint( jointWithParent );
		}

		b2RevoluteJointDef* wJoint = new b2RevoluteJointDef();

		relativePosition = std::make_shared< b2Vec2 >(pos);

		setPos( parent->getPos() );

		wJoint->bodyA = parent->getBody();
		wJoint->bodyB = getBody();

		wJoint->localAnchorA = b2Vec2( 0, 0 );
		wJoint->localAnchorB = b2Vec2( 0, 0 );

		wJoint->collideConnected = false;

		jointWithParent = ( b2RevoluteJoint* )getWBox2DWorld()->CreateJoint( wJoint ) ;

		delete wJoint;

	}
}

void Body::setRelativePos( float32 x, float32 y )
{
	if ( parent != nullptr )
	{

		b2RevoluteJointDef* wJoint = new b2RevoluteJointDef();

		if ( jointWithParent != nullptr )
		{ 
			wJoint->collideConnected = jointWithParent->GetCollideConnected();
			getWBox2DWorld()->DestroyJoint( jointWithParent );
		}


		relativePosition = std::make_shared< b2Vec2 >( x, y );
	
		groundBody->SetTransform( parent->getPos() + *relativePosition, groundBody->GetAngle() + relativeAngle );

		wJoint->bodyA = parent->getBody();
		wJoint->bodyB = getBody();

		wJoint->localAnchorA = b2Vec2( 0, 0 );
		wJoint->localAnchorB = b2Vec2( 0, 0 );

		

		jointWithParent = ( b2RevoluteJoint* )getWBox2DWorld()->CreateJoint( wJoint ) ;

		delete wJoint;

	}
}

void Body::setLowerBound( b2Vec2 lwB )
{
	groundBox->SetAsBox( lwB.x, lwB.y );

	currentFixture->shape = groundBox.get();
	groundBody->CreateFixture( currentFixture.get() );
}

void Body::isSensor( bool newSensor )
{

	groundBody->GetFixtureList()->SetSensor( newSensor );
}