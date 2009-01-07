#include "GameObjectCollection.hpp"
#include <iostream>

GameObjectCollection::GameObjectCollection(int width, int height, InputEventHandler* inputEvent)
{
	_inputEvent = inputEvent;
	_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::s32>(width, height), 16, false, false, false, inputEvent);
	
	if(!_device)
		_device = irr::createDevice(irr::video::EDT_BURNINGSVIDEO, irr::core::dimension2d<irr::s32>(width, height), 16, false, false, false, inputEvent);

	if(!_device)
		return;

	_device->setWindowCaption(L"FYP - v0.1 r23");

	// get the device driver;
	_videoDriver = _device->getVideoDriver();

	// get the handler of the scene manager;
	_smgr = _device->getSceneManager();
	
	// get the handler of the gui enviroment;
	_guienv = _device->getGUIEnvironment();

	/////irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNode(0, irr:vector3df(0, 0, -30), node->getPosition());
	irr::scene::ILightSceneNode* _light = _smgr->addLightSceneNode(0, irr::core::vector3df(0, 10, 4), irr::video::SColorf(), 0);
	
	_player = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("model/x/trial_a.x"));
	
	if(_player)
	{
		_player->setPosition(irr::core::vector3df(0.0,1.0,0.0));
		_player->setScale(irr::core::vector3df(0.05,0.05,0.05));
		_player->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	_viewPoint = _smgr->addCameraSceneNode(_player, irr::core::vector3df(0, 10, 30), _player->getAbsolutePosition());
	
	irr::scene::ISceneNode* _floor = _smgr->addCubeSceneNode(1000.0);

	if(_floor)
	{
		_floor->setScale(irr::core::vector3df(1.01,0.1,1.01));
		_floor->setPosition(irr::core::vector3df(0,-50,0));
		_floor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_floor->setMaterialTexture(0, _videoDriver->getTexture("img/grass.jpg"));
	}
	
	irr::video::ITexture* texture = _videoDriver->getTexture("img/sky.jpg");

	irr::scene::ISceneNode* sky = _smgr->addSkyBoxSceneNode(texture,texture,texture,texture,texture,texture);
}

GameObjectCollection::~GameObjectCollection()
{
	_device->drop();
}

irr::IrrlichtDevice* GameObjectCollection::device()
{
	return _device;
}

irr::scene::ISceneManager* GameObjectCollection::sceneManager()
{
	return _smgr;
}

irr::video::IVideoDriver* GameObjectCollection::videoDriver()
{
	return _videoDriver;
}

InputEventHandler* GameObjectCollection::inputEvent()
{
	return _inputEvent;
}

irr::scene::IAnimatedMeshSceneNode* GameObjectCollection::currentPlayer()
{
	return _player;
}

bool GameObjectCollection::deviceRunning() const
{
	if(_device)
		return _device->run();
	else
		return false;
}

bool GameObjectCollection::isActive() const
{
	if(_device)
		return _device->isWindowActive();
	else
		return false;
}

void GameObjectCollection::idle()
{
	if(_device)
		_device->yield();
}

void GameObjectCollection::moveForward()
{
	irr::core::vector3df v1 = _player->getPosition();
	v1.Z += .05f;
	_player->setPosition(v1);
	_viewPoint->setTarget(_player->getAbsolutePosition());
}
