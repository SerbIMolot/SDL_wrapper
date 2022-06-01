
#include "Camera.h"
#include "Box2D\Collision\b2Collision.h"
#include "Constants.h"



Camera* Camera::cInstance = nullptr;

Camera::Camera(int mapW, int mapH, Body* player) {

}

Camera::Camera() {

}

Camera::~Camera() {
	delete pos;
	delete box;
}

void Camera::Init() {

	this->pivot = nullptr;
	this->type = btCamera;


	pos = new b2Vec2();
	this->box = new b2AABB();

	//setMap();
}

void Camera::setScene() {
	if (mapX == 0 && mapY == 0) {
		//GPU_Log( "Sets MAP SIZE CAM\n" );
		//mapX = Map::getMapSize().getX();
		//mapY = Map::getMapSize().getY();
	}
}

Camera * Camera::Instance()
{
	if (cInstance == nullptr) {
		cInstance = new Camera();
	}
	return cInstance;
}

void Camera::Release()
{
	delete cInstance;
}

void Camera::setPlayer(Body* pivot)
{
	//if (player == nullptr) {
	//GPU_Log( "Sets Player\n" );
	
	this->pivot = pivot;
	*pos = pivot->getPos() - b2Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->box = new b2AABB();
	this->box->upperBound = b2Vec2( pos->x, pos->y );
	this->box->lowerBound =  b2Vec2(static_cast< float32 >( SCREEN_WIDTH ), static_cast< float32 >( SCREEN_HEIGHT ) );
	//}
	//else if (player != nullptr) {



}


b2AABB * const Camera::getBox()
{
	return box;
}

BodyType * const Camera::getType()
{
	return &type;
}

b2Vec2& Camera::Pos()
{
	return *pos;
}
void Camera::updateBox() {
	box->upperBound = *pos;
}

void Camera::Update() {

	pos->x =(pivot->getPos().x - (screenW / 2));
	pos->y = (pivot->getPos().y - (screenH / 2));
	updateBox();
	//std::cout << *pos << std::endl;
	//std::cout << "cam up" << std::endl;
	if (box->upperBound.x < 0) {
		//std::cout << " Camera < 0" << std::endl;
		pos->x =(0);
		updateBox();
	}
	if (box->upperBound.y < 0) {
		//std::cout << " Camera > 0" << std::endl;
		pos->y = (0);
		updateBox();
	}
	if (box->lowerBound.x > mapX) {
		pos->x =(-((int)getBox()->lowerBound.x % mapX) / 2);
		updateBox();
	}
	else if (box->upperBound.x > mapX - box->lowerBound.x) {
		//std::cout << " Camera > MAP" << std::endl;
		pos->x =((float)(mapX - box->lowerBound.x));
		updateBox();
	}
	if (box->lowerBound.y > mapY) {
		pos->x =((float)(-((int)getBox()->lowerBound.y % mapY) / 2));
	}
	if (box->upperBound.y > mapY - box->lowerBound.y) {
		//std::cout << " Camera < MAP" << std::endl;
		pos->y = ((float)(mapY - box->lowerBound.y));
		updateBox();
	}

}


