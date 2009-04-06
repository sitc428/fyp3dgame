#include "TalkativeNPC.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include <iostream>

extern GameEngine* GEngine;

TalkativeNPC::TalkativeNPC( GameWorld& gameWorld, const std::string dialogs, const irr::c8* mesh, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale)
	:InteractiveActor(gameWorld),
	world(gameWorld),
	_dialogs(dialogs)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addAnimatedMeshSceneNode(smgr.getMeshCache()->getMeshByFilename(mesh), smgr.getRootSceneNode());

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
	
	if(state == 0)
	{
		std::cout << "Activated" << std::endl;
		++state;
	}
	else if(state >= 1 && state <= 100)
	{
		std::cout << "Processing" << std::endl;
		++state;
	}
	else
	{
		std::cout << "Finish!" << std::endl;
		state = 0;
		finishAction();
	}
}
