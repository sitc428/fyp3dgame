#include "InteractiveActor.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "InputEventReceiver.hpp"

#include <iostream>

extern GameEngine* GEngine;

InteractiveActor::InteractiveActor( GameWorld& gameWorld )
	:Actor(gameWorld),
	world(gameWorld)
{
}

InteractiveActor::~InteractiveActor()
{
}

void InteractiveActor::Tick( irr::f32 delta )
{
	InputEventReceiver& receiver = GEngine->GetReceiver();
	
	if( receiver.keyDown(irr::KEY_SPACE) )
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	}
}
