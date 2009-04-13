#include "InteractiveActor.hpp"
#include "InputEventReceiver.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "Player.hpp"

#include <iostream>

InteractiveActor::InteractiveActor( GameEngine& gameEngine, GameWorld& gameWorld )
	: Actor(gameEngine, gameWorld),
	collisionAnimator(NULL),
	interacting(false)
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

	InputEventReceiver& receiver = GEngine.GetReceiver();

	if(!interacting)
	{
		if( receiver.keyReleased(irr::KEY_KEY_V) && node->getID()!=10)
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
					//startAction();
					interacting = true;
					world.requestInteracting(true, this);
					interaction( delta );
				//}
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
	world.requestInteracting(false, NULL);
	interacting = false;
}
