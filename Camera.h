#pragma once
class Camera : public dynBody
{
	static Camera* cInstance;

	b2Vec2* pos;

	int mapX, mapY;
	int screenW, screenH;

	b2AABB* box;

	Body* pivot;

	std::shared_ptr< b2Vec2 > pivotVec;

	BodyType type;

	Camera(int mapX, int mapY, Body* player);
	Camera();
	~Camera();
public:

	void Init();
	void setScene();
	static Camera* Instance();

	static void Release();

	void setPlayer(Body* player);

	b2AABB* const getBox() ;
	BodyType* const getType() ;

	b2Vec2& Pos();

	void updateBox();

	void Update();

};

