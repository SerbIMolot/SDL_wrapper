#include "Level1.h"

#include "TextureManager.h"
#include "SceneManager.h"
//#include "Body.h"
//#include "dynBody.h"
#include "SDL_wrapper.h"
//#include "BodyManager.h"
//#include "Vector2d.h"
#include "Constants.h"
//#include "Box2D/Collision/b2Collision.h"
#include "sdl/include/SDL_pixels.h"

//typename struct SDL_Window SDL_Wissndow;
Level1::Level1():
	Scene()
{
	//SceneManager::Instance().changeScene(this);
}

Level1::~Level1()
{
}

void Level1::load()
{
	TextureManager::Instance()->addTexture("Data/BLackFloor.png");
	TextureManager::Instance()->addTexture("Data/BLackWall.png");
	TextureManager::Instance()->addTexture("Data/ButtonHover.png");
	TextureManager::Instance()->addTexture("Data/background.png");
	TextureManager::Instance()->addTexture("Data/bead.png");
	//std::shared_ptr<Body> wallLeft = std::make_shared<Body>( btWall, 50, 500, TextureManager::getTexture( "background.png" ));
	//BodyManager::Instance()->createBody(b2Vec2(0.f, 0.0f), TextureManager::Instance()->getTexture("BLackFloor.png"), "TEST", btWall);
	
	//std::shared_ptr<Body> wallLeft = std::make_shared<Body>(btWall, 0.10f, SCREEN_HEIGHT / 2, TextureManager::getTexture("BLackFloor.png"));
	std::shared_ptr<Body> wallLeft = std::make_shared<Body>( btWall, 0.10f, SCREEN_HEIGHT / 2 , TextureManager::getTexture( "BLackWall.png" ));
	std::shared_ptr<Body> wallRight = std::make_shared<Body>( btWall, SCREEN_WIDTH-0.10f, SCREEN_HEIGHT / 2 , TextureManager::getTexture( "BLackWall.png" ));
	std::shared_ptr<Body> firstFloor = std::make_shared<Body>( btWall, SCREEN_WIDTH / 2, SCREEN_HEIGHT -0.10f, TextureManager::getTexture( "BLackFloor.png" ));
	std::shared_ptr<Body> secondFloor = std::make_shared<Body>(btWall, SCREEN_WIDTH / 2, 0.10f, TextureManager::getTexture("BLackFloor.png"));


	std::shared_ptr<Texture> beadTxt = TextureManager::getTexture("bead.png");
	std::shared_ptr<b2CircleShape> circleShape = std::make_shared<b2CircleShape>();
	circleShape->m_radius = beadTxt->getHeight() / 2;
	for (int i = 1; i < 50; i++) {
		for (int j = 1; j < 10; j++) {
			float xOffset = SCREEN_WIDTH / 5 + (beadTxt->getWidth() + (i*0));
			float yOffset = SCREEN_HEIGHT / 5 + (beadTxt->getHeight() + (j*0));
			std::shared_ptr<dynBody> faller = std::make_shared<dynBody>(btBox, xOffset, yOffset, beadTxt, 0.1f, 0.1f, circleShape);
			//std::string name = "faller" + std::to_string(i)+std::to_string(j);
			addObject("faller", faller);
		}
	}
	
	//wallLeft->getBody()->SetTransform(wallLeft->getBody()->GetPosition(), 90.0f * DEG_TO_RAD);
	//float angle = 90.0f * DEG_TO_RAD;
	//wallRight->getBody()->SetTransform(wallRight->getBody()->GetPosition(), angle);// , 90.0f * DEG_TO_RAD);
	//firstFloor->getBody()->SetTransform(wallLeft->getBody()->GetPosition(), 90.0f * DEG_TO_RAD);
	//secondFloor->getBody()->SetTransform();
	//wallRight->rotateTo( 90.f );
	//secondFloor->rotateTo( 90.f );
	//addObject( "faller", std::dynamic_pointer_cast<Body>(faller));
	addObject( "leftWall", wallLeft );
	addObject( "rightWall", wallRight);
	addObject( "firstFloor", firstFloor);
	addObject( "secondFloor", secondFloor);
	
	//addObject( "wallLeft", wallLeft);
}

void Level1::unload()
{
	Scene::unload();
}

bool Level1::init()
{
	return true;
}

void Level1::update()
{
	Scene::update();
}

void Level1::draw()
{
	SDL_Rect background{ 0, 0, 1920, 1080 };
	SDL_Color backgroundColor{ 225, 225, 225, 225 };
	SDL_wrapper::drawFilledQuad(background, backgroundColor);


	Scene::draw();
}
