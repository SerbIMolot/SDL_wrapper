#pragma once
#include <string>
#include <vector>
#include "Box2D\Box2D.h"
#include "sdl\include\SDL.h"
enum class ButtonEvent
{
	BUTTON_UNKNOWN,
	BUTTON_PRESSED,
	BUTTON_HOLD,
	BUTTON_RELEASE
};

enum class GameEventType
{
	UNKNOWN,
	TOUCH,
	KEY,
	BUTTON,
	STICK,
	TRIGGER,
	MOUSE_MOVEMENT,
	MOUSE_WHEEL_MOVEMENT,
	TOUCH_MOVEMENT,
	JSTICK_MOVEMENT,
	SYSTEM
};
enum class MouseButton
{
	MOUSE_BUTTON_FIRST = SDL_NUM_SCANCODES + 1,
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_X1,
	MOUSE_BUTTON_X2,
	MOUSE_BUTTON_LAST
};
enum class GamepadButton
{
	GAMEPAD_FIRST = static_cast<int> (MouseButton::MOUSE_BUTTON_LAST) + 1,
	GAMEPAD_BUTTON_A,
	GAMEPAD_BUTTON_B,
	GAMEPAD_BUTTON_Y,
	GAMEPAD_BUTTON_X,
	GAMEPAD_STICK_L,
	GAMEPAD_TRIGGER_L,
	GAMEPAD_BUMPER_L,
	GAMEPAD_STICK_R,
	GAMEPAD_TRIGGER_R,
	GAMEPAD_BUMPER_R,
	GAMEPAD_DPAD_UP,
	GAMEPAD_DPAD_DOWN,
	GAMEPAD_DPAD_LEFT,
	GAMEPAD_DPAD_RIGHT,
	START,
	SELECT,
	GAMEPAD_LAST
};

struct Event
{
	std::string nameOfEvent;
	int buttonID;
	ButtonEvent buttonState;
	b2Vec2* pos = nullptr;
};
struct GameEvent
{
public:
	GameEventType type = GameEventType::UNKNOWN;
	ButtonEvent button = ButtonEvent::BUTTON_UNKNOWN;
	std::vector<ButtonEvent> States = std::vector<ButtonEvent>();
	std::string command = "null";
	std::shared_ptr<b2Vec2> pos = std::shared_ptr<b2Vec2>(nullptr);;// = nullptr;
	int buttonID = 0;
	SDL_EventType eventType = SDL_FIRSTEVENT;
};
