#include "InteractiveActor.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "Player.h"
#include "InputEventReceiver.hpp"

#include <iostream>

extern GameEngine* GEngine;

InteractiveActor::InteractiveActor( GameWorld& gameWorld )
	:Actor(gameWorld),
	world(gameWorld),
	interacting(false)
{
}

InteractiveActor::~InteractiveActor()
{
}

void InteractiveActor::Tick( irr::f32 delta )
{
	InputEventReceiver& receiver = GEngine->GetReceiver();
	
	if(!interacting)
	{
		if( receiver.keyDown(irr::KEY_KEY_P) )
		{
			if(node->getPosition().getDistanceFrom(world.GetCurrentPlayer().GetNodePosition()) < acceptableDistance())
			{
				interacting = true;
				interaction();
			}
		}
	}
	else if(interacting)
	{
		interaction();
	}
}
