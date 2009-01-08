#ifndef __GAME_OBJECT_COLLECTION_HPP__
#define __GAME_OBJECT_COLLECTION_HPP__

#include <irrlicht/irrlicht.h>
#include "InputEventHandler.hpp"
#include "Player.hpp"

#include <vector>
#include <string>
#include <map>

class GameObjectCollection
{
private:
	GameObjectCollection() {} // no default constructor!

public:
	GameObjectCollection(int width, int height, InputEventHandler* inputEvent);
	~GameObjectCollection();

	irr::IrrlichtDevice* device();
	irr::scene::ISceneManager* sceneManager();
	irr::video::IVideoDriver* videoDriver();
	InputEventHandler* inputEvent();
	irr::scene::IAnimatedMeshSceneNode* currentPlayer();

	bool deviceRunning() const;
	bool isActive() const;
	void idle();

	void move(irr::scene::ISceneNode* obj, irr::core::vector3df const & targetPos);
	
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();

private:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_videoDriver;
	irr::scene::ISceneManager *_smgr;
	irr::gui::IGUIEnvironment *_guienv;
	InputEventHandler* _inputEvent;
	
	irr::scene::ICameraSceneNode* _viewPoint;
	
	//irr::scene::IAnimatedMeshSceneNode* _player;
	Player* _player;
	//std::map<std::string, SceneData*> scenes;
	std::map<std::string, irr::scene::ILightSceneNode*> _lights;
};

#endif //! __GAME_OBJECT_COLLECTION_HPP__

