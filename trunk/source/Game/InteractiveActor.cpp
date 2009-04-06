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
	interacting(false),
	node(NULL),
	collisionAnimator(NULL)
{
}

InteractiveActor::~InteractiveActor()
{
	world.GetSceneManager().addToDeletionQueue( node );
}

void InteractiveActor::Tick( irr::f32 delta )
{
	if(world.isInteracting() && !interacting)
		return;

	InputEventReceiver& receiver = GEngine->GetReceiver();
	
	if(!interacting)
	{
		if( receiver.keyDown(irr::KEY_KEY_P) )
		{
			if(node->getPosition().getDistanceFrom(world.GetCurrentPlayer().GetNodePosition()) < acceptableDistance())
			{
				interacting = true;
				world.requireInteracting(true, this);
				interaction( delta );
			}
		}
	}
	else if(interacting)
	{
		interaction( delta);
	}
}

void InteractiveActor::finishAction()
{
	world.requireInteracting(false, NULL);
	interacting = false;
}
