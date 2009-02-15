#ifndef __GAME_OBJECT_COLLECTION_HPP__
#define __GAME_OBJECT_COLLECTION_HPP__

#include <irrlicht/irrlicht.h>
#include "InputEventHandler.hpp"
#include "CGUITTFont.h"
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
	irr::gui::IGUIEnvironment* guiEnv();
	InputEventHandler* inputEvent();
	irr::scene::IAnimatedMeshSceneNode* currentPlayer();

	bool deviceRunning() const;
	bool isActive() const;
	void idle();

	void togglePause();
	bool isPaused() const;
	
	irr::gui::CGUITTFont* getFont(std::string fontName, int size);

	void drawText(irr::core::stringw text, irr::core::rect<irr::s32> rect, irr::gui::CGUITTFont* font, irr::video::SColor color = irr::video::SColor(0, 0, 0, 0));

	void move(irr::scene::ISceneNode* obj, irr::core::vector3df targetPos);
	
	void Update();

	void stopMove();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void rotateLeft();
	void rotateRight();

private:
	class MyShaderCallBack : public irr::video::IShaderConstantSetCallBack
	{
		public:
			MyShaderCallBack(irr::IrrlichtDevice* device, irr::core::vector3df* lightPos) : _device(device), _lightPos(lightPos)
			{
			}

			virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData)
			{
				irr::core::vector3df camPos = _device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
				services->setVertexShaderConstant("view_position", reinterpret_cast<irr::f32*>(&camPos), 3);
				services->setVertexShaderConstant("LightPosition", reinterpret_cast<irr::f32*>(_lightPos), 3);
			}
		private:
			irr::IrrlichtDevice* _device;
			irr::core::vector3df* _lightPos;
	};
	
	
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_videoDriver;
	irr::scene::ISceneManager *_smgr;
	irr::gui::IGUIEnvironment *_guienv;
	InputEventHandler* _inputEvent;
	irr::video::IGPUProgrammingServices *_gpu;

	bool _paused;
	
	irr::scene::ICameraSceneNode* _viewPoint;
	
	//irr::scene::IAnimatedMeshSceneNode* _player;
	Player* _player;
	//std::map<std::string, SceneData*> scenes;
	std::map<std::string, irr::scene::ILightSceneNode*> _lights;

	std::vector<irr::scene::IAnimatedMeshSceneNode*> _monsters;
	
	std::map<std::string, irr::gui::CGUITTFace*> _faces;
	std::map< std::pair<std::string, int>, irr::gui::CGUITTFont* > _fonts;
};

#endif //! __GAME_OBJECT_COLLECTION_HPP__

