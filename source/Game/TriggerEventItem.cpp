#include "TriggerEventItem.hpp"
#include "Check.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "NodeID.hpp"
#include <iostream>
#include <boost/thread.hpp>

static const irr::f32		acceptable_Distance = 30.0;
static const irr::c8*		TRIGGER_EVENT_ITEM_MODEL  = "media/model/sellingmachine08.x";

TriggerEventItem::TriggerEventItem( GameEngine& gameEngine, GameWorld& gameWorld, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale )
	: InteractiveActor(gameEngine, gameWorld),
	enabled(false)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addMeshSceneNode(smgr.getMesh(TRIGGER_EVENT_ITEM_MODEL), smgr.getRootSceneNode());
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);
	node->setScale(defaultScale);
	node->setName("TriggerEventItem");
	node->setID(NODE_ID_TRIGGER_EVENT_ITEM);
}

TriggerEventItem::~TriggerEventItem()
{
}

void TriggerEventItem::interaction(irr::f32 delta)
{
	if (!getEnabled())
	{
		std::cout << "----- Mini Game Start -----" << std::endl;
		setEnabled(true);
		boost::thread addSceneThread1( boost::bind(&GameWorld::AddScene, &world, NODE_ID_SCENE2) );
		//boost::thread addSceneThread3( boost::bind(&GameWorld::AddScene, &world, NODE_ID_SCENE3) );
		runGameOne();
		std::cout << "finsihed runGameOne()" << std::endl;
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
	do
	{
		/*int random = rand()%3+1;
		std::cout << random << std::endl;
		int input;
		std::cin >> input;

		if (input == random)*/
		//if (tmp > 200)
			finish = true;
		//tmp++;
	}while(!finish);
	
}