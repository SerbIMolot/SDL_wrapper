#pragma once
#include "../Metronome - Copy (2)/Scene.h"
//#include "SDL.h"/*
#include "SDL_wrapper.h"
#include "Box2D/Collision/b2Collision.h"
//#include "SDL_video.h"*/
class Level1 :
	public Scene
{
public:
	Level1();
	~Level1();

	void load();
	void unload();

	virtual bool init();

	//void addObj/*ect(std::string name, Body* object);
	//void delet*/eObject(std::string name);

	void update();
	void draw();
};

