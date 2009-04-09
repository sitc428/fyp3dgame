#include "TalkativeNPC.hpp"
#include "GameHUD.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include <iostream>

extern GameEngine* GEngine;

TalkativeNPC::TalkativeNPC( GameWorld& gameWorld, irr::core::array<irr::c8*>& dialogs, const irr::c8* mesh, irr::f32 acceptableDistance, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale)
	:InteractiveActor(gameWorld),
	world(gameWorld),
	_dialogs(dialogs),
	acceptable_Distance(acceptableDistance)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addAnimatedMeshSceneNode(smgr.getMesh(mesh), smgr.getRootSceneNode());
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);
	node->setScale(defaultScale);

	irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( ((irr::scene::IAnimatedMeshSceneNode*)node)->getMesh(), node );
	node->setTriangleSelector( meshTriangleSelector );
	world.GetLevelTriangleSelector().addTriangleSelector( meshTriangleSelector );
	meshTriangleSelector->drop();
	meshTriangleSelector = NULL;
}

TalkativeNPC::~TalkativeNPC()
{
}

void TalkativeNPC::interaction(irr::f32 delta)
{
	static int state = 0;
	static int talking = 0;
	static int currentline = 1;
	
	if(state == 0)
	{
		if(talking < _dialogs.size())
		{
			if(currentline <= 0)//_dialogs[talking].size())
			{
				//world.GetGameHUD()->DisplayConversation(subString(0, currentline));
				world.GetGameHUD()->GetConversation(subString(0, currentline));
				++currentline;
			}
			else
			{
				++talking;
				state = 1;
				currentline = 1;
			}
		}
		else
		{
			finishAction();
			talking = 0;
		}
	}
	else if(state == 1)
	{
		InputEventReceiver& receiver = GEngine->GetReceiver();

		if(receiver.keyReleased(irr::KEY_KEY_P))
		{
			state = 0;
		}
	}
}

irr::f32 TalkativeNPC::acceptableDistance()
{
	return acceptable_Distance;
}