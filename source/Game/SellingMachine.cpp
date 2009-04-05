#include "SellingMachine.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include <iostream>

extern GameEngine* GEngine;

static const irr::core::vector3df	defaultPosition = irr::core::vector3df(0,10,0);
static const irr::core::vector3df	defaultRotation = irr::core::vector3df(0, 90, 0);
static const irr::core::vector3df	defaultScale = irr::core::vector3df(1, 5, 1);
static const irr::f32 acceptable_Distance = 20.0;

static const irr::c8*		SELLING_MACHINE_MODEL  = "media/model/robot2.x";

SellingMachine::SellingMachine( GameWorld& gameWorld, irr::video::IVideoDriver& driver )
	:InteractiveActor(gameWorld),
	world(gameWorld)
{
	node = world.GetSceneManager().addCubeSceneNode();
	node->setPosition( defaultPosition );
	node->setRotation( defaultRotation );
	node->setScale( defaultScale );
}

SellingMachine::~SellingMachine()
{
	world.GetSceneManager().addToDeletionQueue( node );
}

void SellingMachine::interaction()
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
		state == 0;
		finishAction();
	}
}

irr::f32 SellingMachine::acceptableDistance()
{
	return acceptable_Distance;
}
