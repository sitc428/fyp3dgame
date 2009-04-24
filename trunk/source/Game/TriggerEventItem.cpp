#include "TriggerEventItem.hpp"
#include "Check.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "NodeID.hpp"
#include <iostream>
#include <boost/thread.hpp>

static const irr::f32		acceptable_Distance = 30.0;
static const irr::c8*		TRIGGER_EVENT_ITEM_MODEL  = "media/model/box.obj";

TriggerEventItem::TriggerEventItem( GameEngine& gameEngine, GameWorld& gameWorld, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale, TriggerEventItemType type )
	: InteractiveActor(gameEngine, gameWorld),
	enabled(false),
	_type(type)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addAnimatedMeshSceneNode(smgr.getMesh(TRIGGER_EVENT_ITEM_MODEL), smgr.getRootSceneNode());
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);
	node->setScale(defaultScale);
	node->setName("TriggerEventItem");
	node->setID(NODE_ID_TRIGGER_EVENT_ITEM);
	node->setVisible(false);
}

TriggerEventItem::~TriggerEventItem()
{
}

void TriggerEventItem::interaction(irr::f32 delta)
{
	if (!getEnabled())
	{
		setEnabled(true);
		std::cout << _type << std::endl;
		if (_type == SCENE1)
		{
			//boost::thread addSceneThread1( boost::bind(&GameWorld::AddScene, &world, NODE_ID_SCENE1) );
			boost::thread LoadSceneThread( boost::bind(&GameWorld::LoadSceneConfig, &world, 1) );
		}
		else if (_type == SCENE2)
		{
			//boost::thread addSceneThread1( boost::bind(&GameWorld::AddScene, &world, NODE_ID_SCENE2) );
			boost::thread LoadSceneThread( boost::bind(&GameWorld::LoadSceneConfig, &world, 2) );
		}
		else if (_type == SCENE3)
		{
			//boost::thread addSceneThread1( boost::bind(&GameWorld::AddScene, &world, NODE_ID_SCENE3) );
			boost::thread LoadSceneThread( boost::bind(&GameWorld::LoadSceneConfig, &world, 3) );
		}
		else if (_type == SCENE4)
		{
			//boost::thread addSceneThread1( boost::bind(&GameWorld::AddScene, &world, NODE_ID_SCENE4) );
			boost::thread LoadSceneThread( boost::bind(&GameWorld::LoadSceneConfig, &world, 4) );
		}
		else if (_type == MINIGAME1)
		{
			std::cout << "----- Mini Game 1 Start -----" << std::endl;
		}
		else if (_type == MINIGAME2)
		{
			std::cout << "----- Mini Game 2 Start -----" << std::endl;
		}
		else if (_type == MINIGAME3)
		{
			std::cout << "----- Mini Game 3 Start -----" << std::endl;
		}
		else if (_type == CUTSCENE)
		{
			std::cout << "----- CUTSCENE -----" << std::endl;
		}

		//runGameOne();
		std::cout << "===== Finsihed TriggerEventItem =====" << std::endl;
		finishAction();
	}
}

irr::f32 TriggerEventItem::acceptableDistance()
{
	return acceptable_Distance;
}

void TriggerEventItem::runGameOne()
{
	static bool finish = false;
	std::cout << "========== Game One ==========" << std::endl;
	int tmp = 0;
	
}