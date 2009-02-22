#include "InputEventReceiver.hpp"
#include <iostream>

InputEventReceiver::InputEventReceiver(GameEngine& engine)
 : _engine(engine)
{
	// init keyboard states. 
	for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		keyState[i] = UP;

	// init mouse states.
	for (int i = 0; i < 3; ++i)
		mouse.mouseButtonState[i] = UP;

	mouse._x = 0;
	mouse._y = 0;
	mouse._wheel = 0.0f;
	
	// init handler state, default disabled
	handlerState = DISABLED;
}

InputEventReceiver::~InputEventReceiver()
{
}

void InputEventReceiver::operator()()
{
//	if(keyDown(irr::KEY_KEY_W))
//	{
//		_goc->moveForward();
//	}
//	if(keyUp(irr::KEY_KEY_W))
//	{
//		_goc->stopMove();
//	}
//	
//	if(keyDown(irr::KEY_KEY_S))
//	{
//		_goc->moveBackward();
//	}
//
//	if(keyDown(irr::KEY_KEY_A))
//	{
//		//_goc->moveLeft();
//		_goc->rotateLeft();
//	}
//
//	if(keyDown(irr::KEY_KEY_D))
//	{
//		//_goc->moveRight();
//		_goc->rotateRight();
//	}
//	if(keyDown(irr::KEY_KEY_P))
//	{
//		//_goc->moveRight();
//		_goc->controlMonster();
//	}
//
//	if(keyPressed(irr::KEY_SPACE))
//	{
//		_goc->togglePause();
//	}
}

bool InputEventReceiver::OnEvent(const irr::SEvent& event)
{
	bool eventprocessed = false;

	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		if (handlerState == ENABLED)
		{
			if (event.KeyInput.PressedDown == true) // key is down
				if (keyState[event.KeyInput.Key] != DOWN)
					keyState[event.KeyInput.Key] = PRESSED;
				else 
					keyState[event.KeyInput.Key] = DOWN;
			else // key is not down
				if (keyState[event.KeyInput.Key] != UP)
					keyState[event.KeyInput.Key] = RELEASED;
		}

		eventprocessed = true;
	}
	
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		if (handlerState == ENABLED)
		{
			if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED) // mouse moved
			{
				mouse._y = event.MouseInput.Y;
				mouse._x = event.MouseInput.X;
			}

			if (event.MouseInput.Event == irr::EMIE_MOUSE_WHEEL) // wheel looped
				mouse._wheel += event.MouseInput.Wheel;

			// left mouse button down
			if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
				if (mouse.mouseButtonState[LEFT] == UP || mouse.mouseButtonState[LEFT] == RELEASED)
					mouse.mouseButtonState[LEFT] = PRESSED;
				else 
					mouse.mouseButtonState[LEFT] = DOWN;

			// left mouse button up
			if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
				if (mouse.mouseButtonState[LEFT] != UP)
					mouse.mouseButtonState[LEFT] = RELEASED;

			// middle mouse button down
			if (event.MouseInput.Event == irr::EMIE_MMOUSE_PRESSED_DOWN)
				if (mouse.mouseButtonState[MIDDLE] == UP || mouse.mouseButtonState[MIDDLE] == RELEASED)
					mouse.mouseButtonState[MIDDLE] = PRESSED;
				else 
					mouse.mouseButtonState[MIDDLE] = DOWN;

			// middle mouse button up
			if (event.MouseInput.Event == irr::EMIE_MMOUSE_LEFT_UP)
				if (mouse.mouseButtonState[MIDDLE] != UP)
					mouse.mouseButtonState[MIDDLE] = RELEASED;

			// right mouse button down
			if (event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN)
				if (mouse.mouseButtonState[RIGHT] == UP || mouse.mouseButtonState[RIGHT] == RELEASED)
					mouse.mouseButtonState[RIGHT] = PRESSED;
				else 
					mouse.mouseButtonState[RIGHT] = DOWN;

			// right mouse button down
			if (event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP)
				if (mouse.mouseButtonState[RIGHT] != UP)
					mouse.mouseButtonState[RIGHT] = RELEASED;
		}

		eventprocessed = true;
	}

	return eventprocessed;
}

float InputEventReceiver::wheel() const
{
	return mouse._wheel;
}

int InputEventReceiver::x() const
{
	return mouse._x;
}

int InputEventReceiver::y() const
{
	return mouse._y;
}

bool InputEventReceiver::mouseReleased(mouseButtons mbType) const
{
	return mouse.mouseButtonState[mbType] == RELEASED;
}

bool InputEventReceiver::mouseUp(mouseButtons mbType) const
{
	return mouse.mouseButtonState[mbType] == RELEASED || mouse.mouseButtonState[mbType] == UP;
}

bool InputEventReceiver::mousePressed(mouseButtons mbType) const
{
	return mouse.mouseButtonState[mbType] == PRESSED;
}

bool InputEventReceiver::mouseDown(mouseButtons mbType) const
{
	return  mouse.mouseButtonState[mbType] == PRESSED || mouse.mouseButtonState[mbType] == DOWN;
}

bool InputEventReceiver::keyPressed(keys keycode) const
{
	return keyState[keycode] == PRESSED;
}

bool InputEventReceiver::keyDown(keys keycode) const
{
	return keyState[keycode] == DOWN || keyState[keycode] == PRESSED;
}

bool InputEventReceiver::keyUp(keys keycode) const
{
	return keyState[keycode] == UP || keyState[keycode] == RELEASED;
}

bool InputEventReceiver::keyReleased(keys keycode) const
{
	return keyState[keycode] == RELEASED;
}

void InputEventReceiver::disable()
{
	handlerState = DISABLED;
}

void InputEventReceiver::enable()
{

	handlerState = ENABLED;

	// update keyboard state
	for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
	{
		if (keyState[i] == RELEASED)
			keyState[i] = UP;

		if (keyState[i] == PRESSED)
			keyState[i] = DOWN;
	}
	
	// update mouse button state
	for (int i = 0; i < 3; ++i)
	{
		if (mouse.mouseButtonState[i] == RELEASED)
			mouse.mouseButtonState[i] = UP;

		if (mouse.mouseButtonState[i] == PRESSED)
			mouse.mouseButtonState[i] = DOWN;
	}

	mouse._wheel = 0.0f;
}
