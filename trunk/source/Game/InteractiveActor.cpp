#include "InteractiveActor.hpp"
#include "InputEventReceiver.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "Player.hpp"
#include "NodeID.hpp"

#include <iostream>

InteractiveActor::InteractiveActor( GameEngine& gameEngine, GameWorld& gameWorld )
	: Actor(gameEngine, gameWorld),
	collisionAnimator(NULL),
	node(NULL),
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
		if( receiver.keyReleased(irr::KEY_KEY_V) && node->getID()!= NODE_ID_TRIGGER_EVENT_ITEM)
		{
			if(node->getPosition().getDistanceFrom(world.GetCurrentPlayer().GetNodePosition()) < acceptableDistance())
			{
				interacting = true;
				world.requestInteracting(true, this);
				interaction( delta );
			}
		}
		else if (node->getID()== NODE_ID_TRIGGER_EVENT_ITEM
			&& node->getPosition().getDistanceFrom(world.GetCurrentPlayer().GetNodePosition()) < acceptableDistance()
		)
        {
			static bool firstTime = true;
			if (firstTime)
			{
				interacting = true;
				world.requestInteracting(true, this);
				interaction( delta );
				firstTime = false;
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
	std::cout << "Inside InteractiveActor::finishAction()" << std::endl;
	world.requestInteracting(false, NULL);
	interacting = false;
	std::cout << "End InteractiveActor::finishAction()" << std::endl;
}
