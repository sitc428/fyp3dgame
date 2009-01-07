#ifndef __GAME_OBJECT_COLLECTION_HPP__
#define __GAME_OBJECT_COLLECTION_HPP__

#include <irrlicht/irrlicht.h>
#include "InputEventHandler.hpp"

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

	bool deviceRunning() const;
	irr::IrrlichtDevice* Device();
	irr::scene::ISceneManager* SceneManager();
	irr::video::IVideoDriver* VideoDriver();
	InputEventHandler* InputEvent();

private:
	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *videoDriver;
	irr::scene::ISceneManager *smgr;
	irr::gui::IGUIEnvironment *guienv;
	InputEventHandler* _inputEvent;
	irr::scene::IAnimatedMeshSceneNode* _player;
	//std::map<std::string, SceneData*> scenes;
	std::map<std::string, irr::scene::ILightSceneNode*> lights;
};

#endif //! __GAME_OBJECT_COLLECTION_HPP__

