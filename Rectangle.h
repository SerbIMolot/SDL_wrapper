#pragma once
#include "Texture.h"
class engRectangle : public Shape
{
public:

	float x;
	float y;
	float w;
	float h;

	engRectangle();
	engRectangle( int x, int y, int w, int h );
	engRectangle( float x, float y, float w, float h );
	engRectangle( std::shared_ptr< Vector2d > vec, float w, float h );
	engRectangle( std::shared_ptr< Vector2d > vec, std::shared_ptr<Texture> textr = nullptr);
	~engRectangle();

	std::shared_ptr< Vector2d > getVec();
	void setVec(std::shared_ptr< Vector2d > vec );

	float topSide();

	float BottomSide();

	float LeftSide();

	float RightSide();


	GPU_Rect convertToGPURect();

	NFont::Rectf convertToNFontRect();


};

