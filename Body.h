#pragma once
#include <memory>
#include <string>
#include "Box2D.h"
#include "SDL_gpu.h"
#include "EventData.h"
#include "Constants.h"



struct Event;

enum BodyType
{
	btUnknown,
	btTrigger,
	btWall,
	btBox,
	btPlayer,
	btGun,
	btCamera,
	btTimingBall,
	btMouse,
	btButton
};

class Texture;

class Body
	: public std::enable_shared_from_this < Body >
{
	std::string nameID;
	bool debug;

	GPU_FlipEnum textureFlip;

	//b2Vec2 pos;
	BodyType btype;

	b2BodyDef groundBodyDef;
	b2FixtureDef currentFixture;

	b2Body* groundBody;

	b2PolygonShape groundBox;

	std::shared_ptr< Body > parent;
	b2RevoluteJoint* jointWithParent;
	b2Vec2 relativePosition;
	float relativeAngle;

	bool colisionWithParent;

	std::shared_ptr< Texture > texture;

public:
	Body();
	Body( BodyType btype, b2Vec2 vec, std::shared_ptr<Texture> textr = nullptr );
	Body( BodyType btype, float x, float y, std::shared_ptr<Texture> textr = nullptr );
	~Body();

	virtual void Init() {}
	b2Vec2 getPos();
	b2Vec2* getRelativePos();

	GPU_FlipEnum getTextureFlip();

	
	void setTextureFlip( GPU_FlipEnum flip );

	void setPos( b2Vec2 pos );
	void setPos(float posX, float posY);
	void setRelativePos( b2Vec2 pos );
	void setRelativePos( float32 x, float32 y );
	void setLowerBound( b2Vec2 lvB );
	void setSkin(std::shared_ptr<Texture> texture);
	std::shared_ptr< Texture > getSkin();

	void isSensor(bool newSensor);


	virtual void Draw();

	virtual void Update();

	BodyType getType();
	bool getCollisionWithParent();

	void setParent( std::shared_ptr<Body> par, bool collide = false );
	void setCollisionWithParent( bool col );

	void setParent( Body * par, bool collide = false );

	std::shared_ptr<Body> getParent();

	void Debug();

	b2Body* const getBody() const;

	void rotateTo( float angle );

	void setID( std::string ID );
	std::string getID() const ;

	//virtual void handleInput( SDL_Scancode key );
	
	virtual void handleInput( std::shared_ptr< Event > newEvent );

	bool operator==( const Body& rhs );

	bool operator==(const Body* rhs);

	friend class Trigger;
	friend class dynBody;
	friend class Entity;
	friend class Player;
	friend class Gun;
};

