#pragma once


class Wall : public Object
{

public:
	Wall( std::shared_ptr< Vector2d > vec, std::shared_ptr< engRectangle > rect );
	Wall( float x, float y, std::shared_ptr< engRectangle > rect );
	Wall( float x, float y, std::shared_ptr< Texture > text );
	Wall( std::shared_ptr< Vector2d > vec, std::shared_ptr< Texture > text );
	Wall( std::shared_ptr< Vector2d > vec, engRectangle &rect );
	~Wall();

	//void Draw();
	//	void collisionDetected( std::shared_ptr< Object > obj ) ;

	//void move();

	//void moveTo(float x1, float y1, float x2, float y2);
	void Draw();
	void Update(std::shared_ptr< Object > obj = nullptr);

	void collisionDetected(std::shared_ptr< Object > obj) override;
};

