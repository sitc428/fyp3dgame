#include "SellingMachine.hpp"
#include "Check.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include <iostream>

static const irr::f32		acceptable_Distance = 50.0;
static const irr::c8*		SELLING_MACHINE_MODEL  = "media/model/sellingmachine08.x";
//static const irr::c8*		SELLING_MACHINE_TEXTURE = "media/model/sellingmachine.png";

SellingMachine::SellingMachine( GameEngine& gameEngine, GameWorld& gameWorld, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale )
	:InteractiveActor(gameEngine, gameWorld)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addMeshSceneNode(smgr.getMesh(SELLING_MACHINE_MODEL), smgr.getRootSceneNode());
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);
	node->setScale(defaultScale);

	irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( ((irr::scene::IMeshSceneNode*)node)->getMesh(), node );
	node->setTriangleSelector( meshTriangleSelector );
	world.GetLevelTriangleSelector().addTriangleSelector( meshTriangleSelector );
	meshTriangleSelector->drop();
	meshTriangleSelector = NULL;
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
