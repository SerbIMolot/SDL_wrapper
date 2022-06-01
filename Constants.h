#pragma once
#include "sdl/include/SDL.h"

#undef SDL_GPU_DISABLE_OPENGL
#undef SDL_GPU_DISABLE_OPENGL_1
const SDL_Color BLACK_COLOR{ 0, 0, 0, 255 };
const SDL_Color RED_COLOR{ 255, 0, 0, 255 };
const SDL_Color GREEN_COLOR{ 0, 255, 0, 255 };
const SDL_Color BLUE_COLOR{ 0, 0, 255, 255 };
const SDL_Color WHITE_COLOR{ 255, 255, 255, 255 };

class b2World;
struct GPU_Target;

#define PtMratio 0.05f
#define MtPratio 20.0f
#define PixelToMeter(n) ( n * PtMratio )
#define MeterToPixel(n) ( n * MtPratio )

#define RtDratio 180.0000000000000000f / 3.141592653589793238463f 
#define DtRratio 3.141592653589793238463f / 180.0000000000000000000f 
#define RadianToDegree(n) ( n * RtDratio )
#define DegreeToRadian(n) ( n * DtRratio )

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const float timeStep = 1.0f / 60.0f;
const int velocityIterations = 1;
const int positionIterations = 10;

b2World* getWBox2DWorld();
void setRengerer(SDL_Renderer* renderer);
SDL_Renderer* getRengerer();

