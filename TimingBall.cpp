#include "TimingBall.h"
#define RADIUS 10.0f
TimingBall::TimingBall( float posX, float posY )
	:Body( btTimingBall,  posX, posY, TextureManager::getTexture("Ball.png") )
{
	//getColShape()->addShape( Pos(), getSkin()->getWidth() / 2 );
	angle = 0.0f;
	velOfRotation = 10.0f;
}

TimingBall::~TimingBall()
{
}

void TimingBall::Update()
{
	angle += velOfRotation;
	GPU_Log("angle %f", angle);
	setPos( ( (float) (getParent()->getPos().x + std::cos(angle / RADIUS) * RADIUS) ) ,
			( (float) (getParent()->getPos().y + std::sin(angle / RADIUS ) * RADIUS ) ) );

}

void TimingBall::Draw()
{
	Body::Draw();
}

void TimingBall::collisionDetected(std::shared_ptr<Object> obj)
{
}
