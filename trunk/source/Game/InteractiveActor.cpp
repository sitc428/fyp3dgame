#include "InteractiveActor.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "Player.hpp"

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
		if( receiver.keyReleased(irr::KEY_KEY_P) && node->getID()!=10)
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
		else if (node->getID()== 10 && 
				node->getPosition().getDistanceFrom(world.GetCurrentPlayer().GetNodePosition()) < acceptableDistance())
		{
			//std::cout<<"TriggerEventItem node matched"<<std::endl;
			static bool firstTime = true;
			if (firstTime)
			{
				interacting = true;
				world.requestInteracting(true, this);
				interaction( delta );
				//firstTime = false;
				//std::cout << firstTime << std::endl;
				//if( receiver.keyReleased(irr::KEY_KEY_P))
				//{
					//std::cout << "???" << std::endl;
					firstTime = false;
				//}
			}
			//static bool tmpFirst = true;
			//if (tmpFirst)
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

/*void InteractiveActor::startAction()
{

}*/