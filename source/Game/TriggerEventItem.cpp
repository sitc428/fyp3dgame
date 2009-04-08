#include "TriggerEventItem.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include <iostream>

extern GameEngine* GEngine;

static const irr::f32		acceptable_Distance = 30.0;
static const irr::c8*		TRIGGER_EVENT_ITEM_MODEL  = "media/model/sellingmachine08.x";

TriggerEventItem::TriggerEventItem( GameWorld& gameWorld, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale )
	:InteractiveActor(gameWorld),
	world(gameWorld)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addMeshSceneNode(smgr.getMesh(TRIGGER_EVENT_ITEM_MODEL), smgr.getRootSceneNode());
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);
	node->setScale(defaultScale);
	node->setName("TriggerEventItem");
	node->setID(10);

	//irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( ((irr::scene::IMeshSceneNode*)node)->getMesh(), node );
	//node->setTriangleSelector( meshTriangleSelector );
	//world.GetLevelTriangleSelector().addTriangleSelector( meshTriangleSelector );
	//meshTriangleSelector->drop();
	//meshTriangleSelector = NULL;
}

TriggerEventItem::~TriggerEventItem()
{
}

void TriggerEventItem::interaction(irr::f32 delta)
{
	static int state = 0;
	
	if(state == 0)
	{
		std::cout << "Activated TriggerEventItem" << std::endl;
		++state;
	}
	else if(state >= 1 && state <= 100)
	{
		std::cout << "Processing TriggerEventItem" << std::endl;
		++state;
	}
	else
	{
		std::cout << "Finish TriggerEventItem!" << std::endl;
		state = 0;
		finishAction();
	}
}

irr::f32 TriggerEventItem::acceptableDistance()
{
	return acceptable_Distance;
}
