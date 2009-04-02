#include "SellingMachine.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"

extern GameEngine* GEngine;

static const irr::core::vector3df	defaultPosition = irr::core::vector3df(10,50,10);
static const irr::core::vector3df	defaultRotation = irr::core::vector3df(0, 90, 0);
static const irr::core::vector3df	defaultScale = irr::core::vector3df(0.1, 0.1, 0.1);

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
