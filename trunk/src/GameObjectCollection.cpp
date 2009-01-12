#include "GameObjectCollection.hpp"
#include "ProgressCircle.hpp"
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

	//_player = new Player(_smgr->addAnimatedMeshSceneNode(_smgr->getMesh("model/x/trial_a.x"), _smgr->getRootSceneNode()), irr::core::vector3df(0.0,1.0,0.0), irr::core::vector3df(0.05,0.05,0.05), 0.05f);
	_player = new Player(_smgr->addAnimatedMeshSceneNode(_smgr->getMesh("model/x/walk.x"), _smgr->getRootSceneNode()), irr::core::vector3df(0.0,1.0,0.0), irr::core::vector3df(0.05,0.05,0.05), 0.05f);

	ProgressCircle* pc = new ProgressCircle(_player->getNode(), _smgr, -1, _smgr->getSceneCollisionManager(), 100, 10, irr::core::vector3df(0, 0, 0));
	_viewPoint = _smgr->addCameraSceneNode(_player->getNode(), irr::core::vector3df(15, 15, 30), _player->getPosition());
	
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
	
	_face = new irr::gui::CGUITTFace;

	_face->load("font/kochi-gothic-subst.ttf");
	
	_font = new irr::gui::CGUITTFont(_videoDriver);
	
	_font->attach(_face, 24);
	
	//_guienv->getSkin()->setFont(_font);
}

GameObjectCollection::~GameObjectCollection()
{
	delete _player;
	_device->drop();
	_font->drop();
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

irr::gui::IGUIEnvironment* GameObjectCollection::guiEnv()
{
	return _guienv;
}

InputEventHandler* GameObjectCollection::inputEvent()
{
	return _inputEvent;
}

irr::scene::IAnimatedMeshSceneNode* GameObjectCollection::currentPlayer()
{
	return (irr::scene::IAnimatedMeshSceneNode*)_player;
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

void GameObjectCollection::drawText()
{
	_font->draw(L"Hello TrueType", irr::core::rect<irr::s32>(0,240,640,240), irr::video::SColor(255,255,64,64), true);
}

void GameObjectCollection::move(irr::scene::ISceneNode* obj, irr::core::vector3df const & targetPos)
{
	irr::core::vector3df currentPos = obj->getPosition();
	currentPos += targetPos;
	obj->setPosition(currentPos);
}

void GameObjectCollection::moveForward()
{
	move(_player->getNode(), irr::core::vector3df(0, 0, -0.05f));
	_viewPoint->setTarget(_player->getPosition());
}

void GameObjectCollection::moveBackward()
{
	move(_player->getNode(), irr::core::vector3df(0, 0, 0.05f));
	_viewPoint->setTarget(_player->getPosition());
}

void GameObjectCollection::moveLeft()
{
	move(_player->getNode(), irr::core::vector3df(0.05f, 0, 0));
	_viewPoint->setTarget(_player->getPosition());
}

void GameObjectCollection::moveRight()
{
	move(_player->getNode(), irr::core::vector3df(-0.05f, 0, 0));
	_viewPoint->setTarget(_player->getPosition());
}
