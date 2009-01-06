#include "GameObjectCollection.hpp"
#include <iostream>

GameObjectCollection::GameObjectCollection(int width, int height, InputEventHandler* inputEvent)
{
	device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::s32>(width, height), 16, false, false, false, (irr::IEventReceiver*)inputEvent);
	
	if(!device)
		device = irr::createDevice(irr::video::EDT_BURNINGSVIDEO, irr::core::dimension2d<irr::s32>(width, height), 16, false, false, false, (irr::IEventReceiver*)inputEvent);
	
	if(!device)
		return;

	device->setWindowCaption(L"FYP - v0.1 r23");

	// get the device driver;
	videoDriver = device->getVideoDriver();

	// get the handler of the scene manager;
	smgr = device->getSceneManager();
	
	// get the handler of the gui enviroment;
	guienv = device->getGUIEnvironment();

	/////irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNode(0, irr:vector3df(0, 0, -30), node->getPosition());
	irr::scene::ILightSceneNode* light = smgr->addLightSceneNode(0, irr::core::vector3df(0, 10, 4), irr::video::SColorf(), 0);
	
	irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, -30), irr::core::vector3df(0, 0, 0));

	//irr::scene::ISceneNode* node = smgr->addCubeSceneNode(10);
	
	
	irr::scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("model/x/trial_a.x"));

	if(node)
	{
		node->setPosition(irr::core::vector3df(0.0,-1.0,0.0));
		node->setScale(irr::core::vector3df(0.05,0.05,0.05));
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}
	
	irr::scene::ISceneNode* floor = smgr->addCubeSceneNode(1000.0);

	if(floor)
	{
		floor->setScale(irr::core::vector3df(1.01,0.1,1.01));
		floor->setPosition(irr::core::vector3df(0,-50,0));
		floor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		floor->setMaterialTexture(0, videoDriver->getTexture("img/grass.jpg"));
	}
}

GameObjectCollection::~GameObjectCollection()
{
	device->drop();
}

bool GameObjectCollection::deviceRunning() const
{
	if(device)
		return device->run();
	else
		return false;
}

irr::IrrlichtDevice* GameObjectCollection::Device()
{
	return device;
}

irr::scene::ISceneManager* GameObjectCollection::SceneManager()
{
	return smgr;
}

irr::video::IVideoDriver* GameObjectCollection::VideoDriver()
{
	return videoDriver;
}
