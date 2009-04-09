#include "TalkativeNPC.hpp"
#include "GameHUD.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include <iostream>

extern GameEngine* GEngine;

TalkativeNPC::TalkativeNPC( GameWorld& gameWorld, irr::core::array<irr::core::stringw>& dialogs, const irr::c8* mesh, irr::f32 acceptableDistance, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale)
	:InteractiveActor(gameWorld),
	world(gameWorld),
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

	int noDialog = dialogs.size();
	for(int i = 0; i < noDialog; ++i)
	{
		_dialogs.push_back(dialogs[i]);
	}
}

TalkativeNPC::~TalkativeNPC()
{
}

void TalkativeNPC::interaction(irr::f32 delta)
{
	static int state = 0;
	static int talking = 0;
	static int currentline = 1;
	static double timeElapsed = 0;
	
	if(state == 0)
	{
		if(talking < _dialogs.size())
		{
			if(currentline <= _dialogs[talking].size())
			{
				if(timeElapsed > 0.05)
				{
					irr::core::stringw temp  = _dialogs[talking].subString(0, currentline);
					std::cout << temp.c_str() << std::endl;
					world.GetGameHUD()->GetConversation(temp);
					++currentline;
					timeElapsed = 0;
				}
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
			timeElapsed = 0;
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

	timeElapsed += delta;
}

irr::f32 TalkativeNPC::acceptableDistance()
{
	return acceptable_Distance;
}
