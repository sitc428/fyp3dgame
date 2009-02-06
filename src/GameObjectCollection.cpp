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

	_device->setWindowCaption(L"FYP - v0.1 r270");

	// get the device driver;
	_videoDriver = _device->getVideoDriver();

	if(!_videoDriver)
	{
		_device->drop();
		return;
	}
	
	_videoDriver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);

	// get the handler of the scene manager;
	_smgr = _device->getSceneManager();
	
	// get the handler of the gui enviroment;
	_guienv = _device->getGUIEnvironment();

	// get the handler of the GPU Programming Services;
	_gpu = _videoDriver->getGPUProgrammingServices();

	irr::scene::ILightSceneNode* _light = _smgr->addLightSceneNode(0, irr::core::vector3df(0, 10, 4), irr::video::SColorf(), 0);

	irr::c8* vsFileName = "model/shader/trial.vert"; // filename for the vertex shader
	irr::c8* psFileName = "model/shader/trial.frag"; // filename for the pixel shader

	irr::s32 newMaterialType = 0;

	if(_gpu)
	{
		MyShaderCallBack *mc = new MyShaderCallBack(_device, &(_light->getAbsolutePosition()));

		newMaterialType = _gpu->addHighLevelShaderMaterialFromFiles(
			vsFileName, "main", irr::video::EVST_VS_1_1,
			psFileName, "main", irr::video::EPST_PS_1_1,
			mc, irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);

		mc->drop();
	}

	_player = new Player(_smgr->addAnimatedMeshSceneNode(_smgr->getMesh("model/x/fullbodywithSkeletonTexture.x"), _smgr->getRootSceneNode()),
		_videoDriver->getTexture("model/x/fullbodywithSkeleton_polySurfaceShape16.png"),
		irr::core::vector3df(0.0, 1.0, 0.0), irr::core::vector3df(0.05, 0.05, 0.05), 0.05f);
	
	ProgressCircle* pc = new ProgressCircle(_player->getNode(), _smgr, -1, _smgr->getSceneCollisionManager(), 100, 10, irr::core::vector3df(0, 0, 0));

	// add the view point
	_viewPoint = _smgr->addCameraSceneNode(_player->getNode(), irr::core::vector3df(15, 15, 30), _player->getPosition());
	
	// start adding trees.
	srand(time(0));

	std::vector<irr::scene::ISceneNode*> trees(100);
	irr::scene::IAnimatedMesh* treeMesh = _smgr->getMesh("model/x/tree22.x");
	_videoDriver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
	irr::video::ITexture* treeTexture = _videoDriver->getTexture("model/x/leaf tex.png");

	for(int i = 0; i < 100; ++i)
	{
		irr::scene::ISceneNode* tree = _smgr->addAnimatedMeshSceneNode(treeMesh);
		tree->setMaterialTexture(1, treeTexture);

		if(tree)
		{
			tree->setPosition(irr::core::vector3df(rand() % 400 - 200, 0, rand() % 400 - 200));
			tree->setRotation(irr::core::vector3df(0, 15 * (rand() % 24), 0));
			tree->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			tree->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
			//tree->setMaterialType(static_cast<irr::video::E_MATERIAL_TYPE>(newMaterialType));
		}

		trees[i] = tree;
	}
	// End adding trees.

	// monster?
	irr::scene::IAnimatedMesh* monsterMesh = _smgr->getMesh("model/x/dwarf.x");

	_monsters.resize(100);

	for(int i = 0; i < 100; ++i)
	{
		irr::scene::IAnimatedMeshSceneNode* monster = _smgr->addAnimatedMeshSceneNode(monsterMesh);

		if(monster)
		{
			monster->setLoopMode(false);
			monster->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
			monster->setPosition(irr::core::vector3df(rand() % 400 - 200, 0, rand() % 400 - 200));
			monster->setRotation(irr::core::vector3df(0, rand() % 360, 0));
			monster->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		}

		_monsters[i] = monster;
	}
	// End adding.

	irr::scene::ISceneNode* _house = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("model/x/house.x"));
	_house->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	irr::scene::ISceneNode* _forest = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("model/x/forest_2e.x"));
	_forest->setPosition(irr::core::vector3df(-20, 10, -20));
	_forest->setMaterialFlag(irr::video::EMF_LIGHTING, false);	

	irr::scene::ISceneNode* _floor = _smgr->addCubeSceneNode(1000.0);

	if(_floor)
	{
		_floor->setScale(irr::core::vector3df(1.01,0.1,1.01));
		_floor->setPosition(irr::core::vector3df(0,-50,0));
		_floor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_floor->setMaterialTexture(0, _videoDriver->getTexture("img/grass.jpg"));
	}

	irr::scene::IMetaTriangleSelector* metaSelector = _smgr->createMetaTriangleSelector();

	for(std::vector<irr::scene::ISceneNode*>::iterator i = trees.begin();
		i != trees.end(); ++i)
	{
		metaSelector->addTriangleSelector((*i)->getTriangleSelector());
	}

	//metaSelector->addTriangleSelector(_floor->getTriangleSelector());
	metaSelector->addTriangleSelector(_smgr->createTriangleSelectorFromBoundingBox(_floor));

	irr::scene::ISceneNodeAnimator * anim = _smgr->createCollisionResponseAnimator(
		metaSelector, /*_player->getNode()*/ _viewPoint, irr::core::vector3df(1,3,1),
		irr::core::vector3df(0,-1,0), irr::core::vector3df(0,0.05,0));

	//_player->getNode()->addAnimator(anim);
	_viewPoint->addAnimator(anim);

	_player->getNode()->addShadowVolumeSceneNode();

	anim->drop();
	
	irr::video::ITexture* texture = _videoDriver->getTexture("img/sky.jpg");

	irr::scene::ISceneNode* sky = _smgr->addSkyBoxSceneNode(texture,texture,texture,texture,texture,texture);
	
	_face = new irr::gui::CGUITTFace;

	_face->load("font/kochi-gothic-subst.ttf");
	
	_font = new irr::gui::CGUITTFont(_videoDriver);
	
	_font->attach(_face, 24);

	if(_videoDriver->queryFeature(irr::video::EVDF_MULTITEXTURE))
		std::cout<<"we have it!"<<std::endl;
	
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

void GameObjectCollection::drawText(irr::core::stringw text)
{
	_font->draw(text.c_str(), irr::core::rect<irr::s32>(0,0,100, 40), irr::video::SColor(255,255,64,64), true);
}

void GameObjectCollection::move(irr::scene::ISceneNode* obj, irr::core::vector3df targetPos)
{
	irr::core::vector3df currentPos = obj->getPosition();
	currentPos += targetPos;
	obj->setPosition(currentPos);
}

void GameObjectCollection::Update()
{
	for(int i = 0; i < 100; ++i)
	{
		move(_monsters[i], irr::core::vector3df(0.1, 0, 0.1));
	}
}

void GameObjectCollection::stopMove()
{
	_player->stopMove();
}

void GameObjectCollection::moveForward()
{
	_player->moveForward();
	/*irr::core::vector3df temp = irr::core::vector3df(0, 0, -0.05f);
	temp.rotateXZBy(_player->getRotation(), temp);
	move(_player->getNode(), temp);*/
	move(_player->getNode(), irr::core::vector3df(0, 0, -0.05f));
	_viewPoint->setTarget(_player->getPosition());
}

void GameObjectCollection::moveBackward()
{
	_player->moveBackward();
	move(_player->getNode(), irr::core::vector3df(0, 0, 0.05f));
	_viewPoint->setTarget(_player->getPosition());
}

void GameObjectCollection::moveLeft()
{
	_player->moveLeft();
	move(_player->getNode(), irr::core::vector3df(0.05f, 0, 0));
	_viewPoint->setTarget(_player->getPosition());
}

void GameObjectCollection::moveRight()
{
	_player->moveRight();
	move(_player->getNode(), irr::core::vector3df(-0.05f, 0, 0));
	_viewPoint->setTarget(_player->getPosition());
}

void GameObjectCollection::rotateLeft()
{
	_player->rotateLeft();
}

void GameObjectCollection::rotateRight()
{
	_player->rotateRight();
}
