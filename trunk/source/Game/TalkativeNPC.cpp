#include "TalkativeNPC.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include <iostream>

extern GameEngine* GEngine;

TalkativeNPC::TalkativeNPC( GameWorld& gameWorld, std::vector<std::string> dialogs, const irr::c8* mesh, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale)
	:InteractiveActor(gameWorld),
	world(gameWorld)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addAnimatedMeshSceneNode(smgr.getMesh(mesh), smgr.getRootSceneNode());

	irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( ((irr::scene::IAnimatedMeshSceneNode*)node)->getMesh(), node );
	node->setTriangleSelector( meshTriangleSelector );
	world.GetLevelTriangleSelector().addTriangleSelector( meshTriangleSelector );
	meshTriangleSelector->drop();
	meshTriangleSelector = NULL;

	int dialogConnt = dialogs.size();
	for(int i = 0; i < dialogConnt; ++i)
		_dialogs.push_back(dialogs[i]);
}

TalkativeNPC::~TalkativeNPC()
{
}

void TalkativeNPC::interaction(irr::f32 delta)
{
	static int state = 0;
	static int talking = 0;
	
	if(state == 0)
	{
		if(talking < _dialogs.size())
		{
			std::cout << _dialogs[talking++] << std::endl;
			state = 1;
		}
		else
		{
			talking = 0;
			finishAction();
		}
	}
	else if(state == 1)
	{
		InputEventReceiver& receiver = GEngine->GetReceiver();

		if(receiver.keyDown(irr::KEY_KEY_P))
			state = 0;
	}
}
