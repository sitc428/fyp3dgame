#ifndef InputEventReceiver_h
#define InputEventReceiver_h

#include "irrlicht/IEventReceiver.h"
#include "irrlicht/Keycodes.h"

using namespace irr;
/*
To receive events like mouse and keyboard input, or GUI events like 
"the OK button has been clicked", we need an object which is derived from the 
IEventReceiver object. There is only one method to override: OnEvent. 
This method will be called by the engine once when an event happens. 
What we really want to know is whether a key is being held down,
and so we will remember the current state of each key.
*/
class InputEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		// Route the mouse input events unbuffered to the engine
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			gameEngine.OnMouseEvent( event.MouseInput );
		}

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	InputEventReceiver( GameEngine& engine )
	: gameEngine( engine )	
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// instance of the engine which own this input receiver
	GameEngine& gameEngine;
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif //InputEventReceiver_h