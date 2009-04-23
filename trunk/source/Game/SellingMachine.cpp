#include "Check.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "Item.hpp"
#include "SellingMachine.hpp"
#include <iostream>

static const irr::f32		acceptable_Distance = 50.0;
static const irr::c8*		SELLING_MACHINE_MODEL  = "media/model/sellingmachine08.x";

SellingMachine::SellingMachine( GameEngine& gameEngine, GameWorld& gameWorld, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale, MainCharacter::ItemCollection& items)
	:InteractiveActor(gameEngine, gameWorld),
	state(0)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addAnimatedMeshSceneNode(smgr.getMesh(SELLING_MACHINE_MODEL), smgr.getRootSceneNode());
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);
	node->setScale(defaultScale);

	irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( ((irr::scene::IAnimatedMeshSceneNode*)node)->getMesh(), node );
	node->setTriangleSelector( meshTriangleSelector );
	world.GetLevelTriangleSelector().addTriangleSelector( meshTriangleSelector );
	meshTriangleSelector->drop();
	meshTriangleSelector = NULL;

	for( irr::u32 i = 0; i < items.size(); ++i)
		_items.push_back(items[i]);
}

SellingMachine::~SellingMachine()
{
}

void SellingMachine::interaction(irr::f32 delta)
{
	if(state == 0)
	{
		std::cout << "Activated" << std::endl;
		world.requestBuying();
		++state;
	}
	else if(state == 1)
	{
		std::cout << "Processing" << std::endl;
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

void SellingMachine::finishBuying()
{
	state = 2;
}

void SellingMachine::BuyItem(irr::u32 index)
{
	MainCharacter::ItemCollection& theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
	irr::u32 boxSize = theBox.size();

	EItemType theType = _items[index].first->getItemType();
	irr::core::stringw theName = _items[index].first->getItemName();

	for(irr::u32 i = 0; i < boxSize; ++i)
	{
		if(
			theBox[i].first->getItemType() == theType
			&& theBox[i].first->getItemName() == theName
		)
		{
			++theBox[i].second;
			((MainCharacter&)world.GetCurrentPlayer()).SetMoney(
				((MainCharacter&)world.GetCurrentPlayer()).GetMoney() - _items[index].second
			);
			break;
		}
	}
}
