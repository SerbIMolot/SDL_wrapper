#include "stdafx.h"
#include "Rectangle.h"

engRectangle::engRectangle()
	: Shape( sBox ) 
{

	w = 0;
	h = 0;

}

engRectangle::engRectangle(int x, int y, int w, int h) 
	: Shape( static_cast<float>(x), static_cast<float>(y), sBox)
{
	this->x = static_cast<float>(x);
	this->x = static_cast<float>(y);
	this->w = static_cast<float>(w);
	this->h = static_cast<float>(h);

}

engRectangle::engRectangle(float x, float y, float w, float h) 
	: Shape( x, y, sBox )
{

	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

}

engRectangle::engRectangle(std::shared_ptr<Vector2d> vec, float w, float h)
	: Shape( vec, sBox )
{
	this->x = vec->getX();
	this->y = vec->getY();
	this->w = w;
	this->h = h;
}

engRectangle::engRectangle(std::shared_ptr< Vector2d > vec, std::shared_ptr<Texture> texture) 
	: Shape( vec, sBox )
{
	this->x = vec->getX();
	this->y = vec->getY();
	if (texture == nullptr) {
		w = 0;
		h = 0;
	}
	else {
		w = static_cast<float>(texture->getWidth());
		h = static_cast<float>(texture->getHeight());
	}

}

engRectangle::~engRectangle() { }


float engRectangle::topSide()
{
	return y;
}

float engRectangle::BottomSide()
{
	return y + h;
}

float engRectangle::LeftSide()
{
	return x;
}

float engRectangle::RightSide()
{
	return x + w;
}

GPU_Rect engRectangle::convertToGPURect()
{
	GPU_Rect buf = { x, y, w, h };
	return buf;

}

NFont::Rectf engRectangle::convertToNFontRect()
{
	NFont::Rectf buf = { x, y, w, h };
	return buf;

}

