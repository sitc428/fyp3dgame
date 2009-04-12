#ifndef __INPUT_EVENT_RECEIVER_HPP__
#define __INPUT_EVENT_RECEIVER_HPP__

#include <irrlicht/irrlicht.h>

class InputEventReceiver : public irr::IEventReceiver 
{
public:
	enum mouseButtons {LEFT = 0, MIDDLE = 1, RIGHT = 2};

	typedef irr::EKEY_CODE keys;

	InputEventReceiver();
	~InputEventReceiver();

	bool OnEvent(const irr::SEvent& event);

	irr::f32 wheel() const;
	irr::s32 x() const;
	irr::s32 y() const;
	bool mouseReleased(mouseButtons mbType) const;
	bool mouseUp(mouseButtons mbType) const;
	bool mousePressed(mouseButtons mbType) const;
	bool mouseDown(mouseButtons mbType) const;
	bool keyPressed(keys keycode) const;
	bool keyDown(keys keycode) const;
	bool keyUp(keys keycode) const;
	bool keyReleased(keys keycode) const;
	void disable();
	void enable();

private:
	// key/mouse button states
	enum keyStates {UP, DOWN, PRESSED, RELEASED};

	// handler states
	enum handlerStates {DISABLED, ENABLED};

	// mouse x/y coordinates, wheel data and mouse button state
	struct mouseData 
	{
		int _x;
		int _y;
		float _wheel;
		
		// mouse button states
		keyStates mouseButtonState[3];
	} mouse;

	// keyboard key states.
	keyStates keyState[irr::KEY_KEY_CODES_COUNT];

	handlerStates handlerState;
};

#endif //! __INPUT_EVENT_RECEIVER_HPP__
