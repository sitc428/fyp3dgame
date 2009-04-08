#include "InteractiveActor.hpp"
#include "GameEngine.h"
#include "GameWorld.h"
#include "Player.h"

#include <iostream>

extern GameEngine* GEngine;

InteractiveActor::InteractiveActor( GameWorld& gameWorld )
	:Actor(gameWorld),
	world(gameWorld),
	interacting(false),
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
		if( receiver.keyReleased(irr::KEY_KEY_P) )
		{
			if(node->getPosition().getDistanceFrom(world.GetCurrentPlayer().GetNodePosition()) < acceptableDistance())
			{
				/*
				irr::core::line3df line;
				line.start = world.GetCurrentPlayer().GetNodePosition();
				line.end = line.start - world.GetCurrentPlayer().GetAimVector() * 10000;
				if(world.GetSceneManager().getSceneCollisionManager()->getSceneNodeFromRayBB(line) == node)
				{
				*/
					interacting = true;
					world.requireInteracting(true, this);
					interaction( delta );
				//}
			}
		}
		else
		{
			if (node->getID()== 10 && 
				node->getPosition().getDistanceFrom(world.GetCurrentPlayer().GetNodePosition()) < acceptableDistance())
			{
					std::cout<<"TriggerEventItem node matched"<<std::endl;
					interacting = true;
					world.requireInteracting(true, this);
					interaction( delta );
			}
		}
	}
	else if(interacting)
	{
		interaction( delta );
	}
}

void InteractiveActor::finishAction()
{
	world.requireInteracting(false, NULL);
	interacting = false;
}
