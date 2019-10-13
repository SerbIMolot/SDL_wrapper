// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once
#pragma warning (disable: 4244)

#include "targetver.h"

#define DEBUG
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <string>
#include <cstdio>
#include <random>
#include <algorithm> 
#include <thread>
#include <atomic>
#include <chrono>
#include <list>
#include <map>

#include "SDL.h"
#include "SDL_gpu.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_thread.h"
#include "SDL_mixer.h"
#include "SDL_gpu_RendererImpl.h"
#include "SDL_FontCache.h"
#include "Nfont_gpu.h"
#include "GPU_setup.h"

#include "Vector2d.h"
#include "Shape.h"

#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Texture.h"
#include "Animation.h"

#include "CollisionShape.h"

#include "SoundEfx.h"

#include "State.h"

#include "Trigger.h"
#include "Timer.h"
#include "TimerIns.h"
#include "TextureManager.h"


#include "Object.h"
#include "Button.h"
#include "TriggersManager.h"

#include "SoundEfx.h"
#include "SoundManager.h"

#include "Wall.h"

#include "Board.h"

#include "Collision.h"

#include "Mouse.h"


#include "SDL_wrapper.h"
#include "Metronome.h"
 


#include "EventHandle.h"
#pragma warning (default: 4244)


// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
