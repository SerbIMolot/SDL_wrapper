#pragma once
class Collision
{

	static std::vector< std::shared_ptr< Object > > Objects;

	std::map< std::shared_ptr< Object >, std::shared_ptr< Object > > collidedObjects;


	int numSimulationUpdates;

	float tSimulationElapsTime;

	int numMaxSimSteps;

public:
	Collision();
	~Collision();

	static void addObject(std::shared_ptr<Object> obj);

	void addCollidedObject(std::shared_ptr<Object> obj1, std::shared_ptr< Object > obj2 );

	void Update();

	bool collisionCheck( std::shared_ptr< Object > obj1, std::shared_ptr< Object > obj2 );

	bool collisionCheck( std::shared_ptr< Trigger > tr, std::shared_ptr< Object > obj );

	bool collisionCheck(std::shared_ptr< Button > button, std::shared_ptr< Object > obj );

	bool circleCollisionCheck( std::shared_ptr< engCircle > circ1, std::shared_ptr< engCircle > circ2 );

	bool RectCollisionCheck( std::shared_ptr< engRectangle > rect, std::shared_ptr< engRectangle > rect2 );

	bool circRectCollisionCheck( std::shared_ptr< engCircle > circ, std::shared_ptr< engRectangle > rect );

	float circleCircleOverlap( std::shared_ptr< engCircle > circ1, std::shared_ptr< engCircle > circ2 );

	float circRectOverlap( std::shared_ptr< engCircle > circ, std::shared_ptr< engRectangle > rect );

	bool pointCircleCollisionCheck( std::shared_ptr< Shape > vec, std::shared_ptr< engCircle > circ );
	
	bool pointRectCollisionCheck( std::shared_ptr< Shape > vec, std::shared_ptr< engRectangle > rect );

	bool lineCircleCollision( std::shared_ptr< engLine > line, std::shared_ptr< engCircle > circ );

	void staticColisionRes();


	void dynamicColisionRes();

	
};

