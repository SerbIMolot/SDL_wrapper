
#include "dynBody.h"
#include "TextureManager.h"
#include "Box2D.h"

#include "Constants.h"


dynBody::dynBody()
	: Body()
{
	groundBodyDef = new b2BodyDef();
	groundBox = std::make_shared<b2PolygonShape>();
	fixtureDef = new b2FixtureDef();

	groundBodyDef->type = b2_dynamicBody;
	groundBodyDef->position.Set( 1.0f, 1.0f );
	
	groundBody = getWBox2DWorld()->CreateBody( groundBodyDef );

	delete groundBodyDef;
	texture = TextureManager::getTexture("box.jpg");
	groundBox->SetAsBox( ( texture->getWidth() / 2 ) * PtMratio, ( texture->getHeight() / 2 ) * PtMratio );

	fixtureDef->shape = std::move( groundBox.get() );
	fixtureDef->density = 0.65f;
	fixtureDef->friction = 0.3f;

	fixture = groundBody->CreateFixture( fixtureDef );
	delete fixtureDef;
}

dynBody::dynBody( BodyType btype, b2Vec2 vec, std::shared_ptr<Texture> textr, float dencity, float friction, std::shared_ptr<b2Shape> shape)
	: Body()
{
	debug = false;
	this->btype = btype;
	groundBodyDef = new b2BodyDef();;
	groundBox = std::make_shared<b2PolygonShape>();
	fixtureDef = new b2FixtureDef();


	groundBodyDef->type = b2_dynamicBody;
	groundBodyDef->position.Set(PixelToMeter(vec.x), PixelToMeter(vec.y));

	groundBody = getWBox2DWorld()->CreateBody( groundBodyDef );
	delete groundBodyDef;

	if (textr)
	{
		texture = std::move(textr); 
		if (shape == nullptr) {
			groundBox->SetAsBox(PixelToMeter(texture->getWidth() / 2), PixelToMeter(texture->getHeight() / 2));
			shape = std::static_pointer_cast<b2Shape>(groundBox);
		}
		
	}

	fixtureDef->shape = shape.get();
	fixtureDef->density = dencity;
	fixtureDef->friction = friction;

	fixture = groundBody->CreateFixture( fixtureDef  );


	fixture->SetUserData( ( void* ) this );


}

dynBody::dynBody( BodyType btype, float x, float y, std::shared_ptr<Texture> textr, float dencity, float friction, std::shared_ptr<b2Shape> shape)
	: Body()
{
	debug = false;
	this->btype = btype;
	groundBodyDef = new b2BodyDef();
	groundBox = std::make_shared<b2PolygonShape>();
	fixtureDef = new b2FixtureDef();

	groundBodyDef->type = b2_dynamicBody;
	groundBodyDef->position.Set(PixelToMeter(x), PixelToMeter(y));

	groundBody = getWBox2DWorld()->CreateBody( groundBodyDef );
	delete groundBodyDef;

	if ( textr )
	{
		texture = std::move(textr);
		groundBox->SetAsBox( PixelToMeter( texture->getWidth() / 2 ), PixelToMeter( texture->getHeight() / 2 ) );
	}
	else
	{
		texture = nullptr;
		groundBox->SetAsBox( PixelToMeter( 10 ), PixelToMeter( 10 ) );
	}

	fixtureDef->shape = std::move( groundBox.get() );
	fixtureDef->density = dencity;
	fixtureDef->friction = friction;

	fixture = groundBody->CreateFixture( fixtureDef );


	fixture->SetUserData((void*)this);

}



dynBody::~dynBody()
{
	delete fixtureDef;
}

void dynBody::applyForce( b2Vec2 force )
{
	SDL_Log( "type %d", groundBody->GetType() );
	b2Vec2 pos = groundBody->GetWorldCenter();
	groundBody->ApplyForce( force, pos, true );
}

b2Vec2 dynBody::getVelocity()
{
	return groundBody->GetLinearVelocity();
}


void dynBody::setBodyState(BodyState state)
{
	this->state = state;
}

BodyState dynBody::getBodyState()
{
	return state;
}
