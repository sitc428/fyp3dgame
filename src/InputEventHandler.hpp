#ifndef __INPUT_EVENT_HANDLER_HPP__
#define __INPUT_EVENT_HANDLER_HPP__

#include <irrlicht/irrlicht.h>

class InputEventHandler : public irr::IEventReceiver 
{
public:
	enum mouseButton {LEFT = 0, MIDDLE = 1, RIGHT = 2};

	InputEventHandler();
	~InputEventHandler();

	bool OnEvent(const irr::SEvent& event);

	float wheel() const;
	int x() const;
	int y() const;
	bool mouseReleased(mouseButton mbType) const;
	bool mouseUp(mouseButton mbType) const;
	bool mousePressed(mouseButton mbType) const;
	bool mouseDown(mouseButton mbType) const;
	bool keyPressed(char keycode) const;
	bool keyDown(char keycode) const;
	bool keyUp(char keycode) const;
	bool keyReleased(char keycode) const;
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

#endif //! __INPUT_EVENT_HANDLER_HPP__
