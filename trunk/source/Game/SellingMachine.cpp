#include "SellingMachine.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include <iostream>

extern GameEngine* GEngine;

static const irr::f32 acceptable_Distance = 20.0;
static const irr::c8*		SELLING_MACHINE_MODEL  = "media/model/robot2.x";

SellingMachine::SellingMachine( GameWorld& gameWorld, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale )
	:InteractiveActor(gameWorld),
	world(gameWorld)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addMeshSceneNode(smgr.getMeshCache()->getMeshByFilename(SELLING_MACHINE_MODEL), smgr.getRootSceneNode(), -1, defaultPosition, defaultRotation, defaultScale );
}

SellingMachine::~SellingMachine()
{
}

void SellingMachine::interaction(irr::f32 delta)
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

irr::f32 SellingMachine::acceptableDistance()
{
	return acceptable_Distance;
}
