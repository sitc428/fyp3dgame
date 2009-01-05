#include "GameObjectCollection.hpp"

GameObjectCollection::GameObjectCollection(int width, int height)
{
	device = createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::s32>(width, height), 16, false, false, false, &inputEvent);
	
	if(!device)
		device = createDevice(irr::video::EDT_BURNINGSVIDEO, irr::core::dimension2d<irr::s32>(width, height), 16, false, false, false, &inputEvent);
	
	if(!device)
		return;

	// get the device driver;
	videoDriver = device->getVideoDriver();

	// get the handler of the scene manager;
	smgr = device->getSceneManager();
	
	// get the handler of the gui enviroment;
	guienv = device->getGUIEnvironment();

	/////irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNode(0, irr:vector3df(0, 0, -30), node->getPosition());
	irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, -30), irr::core::vector3df(0, 0, 0));
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
