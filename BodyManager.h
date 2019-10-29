#pragma once

#include "Body.h"
#include "Nfont.h"
#include "Box2D.h"

enum JointType
{
	DistanceJoint ,
	FrictionJoint ,
	GearJoint	  ,
	Joint		  ,
	MotorJoint	  ,
	MouseJoint	  ,
	PrismaticJoint,
	PulleyJoint	  ,
	RevoluteJoint ,
	RopeJoint	  ,
	WeldJoint	  ,
	WheelJoint	  ,
};
enum BodyType;
class Player;
class dynBody;
class Gun;

class BodyManager
{
	bool debug;

	static std::shared_ptr< BodyManager > objInstance;

	static std::unique_ptr< Player > player;

	static std::vector< std::shared_ptr< Body > > bodys;


	std::map< std::string, std::shared_ptr< Body > > mBodies;

	NFont* debugFont;

	//returns 0 when there is no such name in array, > 0 if multiple instances
	int checkName(std::string nameID);

public:
	BodyManager();
	~BodyManager();

	static std::shared_ptr< BodyManager > Instance();


	void addBody( std::string name, std::shared_ptr< Body > body, BodyType btype = btUnknown );
	void createBody( std::string name = "body", BodyType btype = btUnknown );

	void createBody( b2Vec2 pos, std::shared_ptr< Texture > textr, std::string name = "body", BodyType btype = btUnknown );
	void createBody( float x, float y, std::shared_ptr< Texture > textr, std::string name = "body", BodyType btype = btUnknown );
	
	void createBody( b2Vec2 pos, std::shared_ptr< Texture > textr, float dencity, float friction, std::string name = "body", BodyType btype = btUnknown );
	void createJoint(JointType jType, std::string a, std::string b);
	void createBody( float x, float y, std::shared_ptr< Texture > textr, float dencity, float friction, std::string name = "body", BodyType btype = btUnknown );

	void createJoint( std::string a, std::string b );
	

	std::shared_ptr< Body > getFirst();

	std::vector< std::shared_ptr< Body > > getBodys();

	std::map< std::string, std::shared_ptr< Body > > getBodies();

	std::shared_ptr < Body > getBody( std::string name = "body" );
	std::shared_ptr < dynBody > getDynBody( std::string name = "body" );

	Player* getPlayer();

	std::vector<std::shared_ptr< dynBody > > getBoxes( std::string name = "body" );

	std::vector< std::shared_ptr<dynBody> > getDynBodies( std::string name = "body" );

	std::vector<std::shared_ptr<Gun>> getGuns();

	std::shared_ptr<Gun> getGun(std::string name);

	std::vector< std::shared_ptr<Body> > getWalls( std::string name = "body" );

	void Draw();

	void Update();
	void handleInput( std::shared_ptr< Event > event );



	void BodyDebug();

	//static addBody();
};

