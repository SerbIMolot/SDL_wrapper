#pragma once

class Animation
{
	std::vector< GPU_Rect > spriteClips;

	int frames;

	std::shared_ptr< Texture > spriteSheet;

	Vector2d frameSize;

	int currentFrame = 0;

	float frameDevider = 4;

	bool loop;
	bool stop;
	bool ended;
public:
	Animation();
	Animation( int frames, std::shared_ptr< Texture > spriteSheet, Vector2d frameDimentions );
	~Animation();

	void drawFrame( std::shared_ptr< Vector2d > point, bool isLooped = true );
	void drawFrame( Vector2d point, bool isLooped = true );
	void drawFrame( int x, int y, bool isLooped = true );

	void drawAnimationOnce( std::shared_ptr< Vector2d > point );
	void drawAnimationOnce( Vector2d point );
	void drawAnimationOnce( int x, int y );

	void reset();

	int getCurrentFrame();
	void setCurrentFrame( int frame );

	int getFrames();

	//How much ticks one frame would be shown
	float getDevider();
	void setDevider( float devider );

	bool isEnded();

	void setSpriteSheet( int frames, std::shared_ptr< Texture > spriteSheet, Vector2d frameDimentions );

};

