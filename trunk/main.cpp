#include <irrlicht.h>

// The irrlicht namespace
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class KeyboardEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	KeyboardEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main(int argc, char* argv[])
{
	KeyboardEventReceiver keyboardReceiver;
	
	IrrlichtDevice* device =
#ifdef _IRR_OSX_PLATFORM_
		createDevice(video::EDT_OPENGL, dimension2d<s32>(640, 480), 16, false, false, false, &keyboardReceiver);
#else
	createDevice(video::EDT_OPENGL, dimension2d<s32>(640, 480), 16, false, false, false, &keyboardReceiver);
#endif

	if(device == 0)
		return 1;

	device->setWindowCaption(L"FYP - v0.1 r14");

	// get the device driver;
	IVideoDriver *driver = device->getVideoDriver();

	// get the handler of the scene manager;
	ISceneManager *smgr = device->getSceneManager();

	// get the handler of the gui enviroment;
	IGUIEnvironment *guienv = device->getGUIEnvironment();

	/*
	   We add a hello world label to the window, using the GUI environment.
	   */
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
			rect<s32>(10,10,260,22), true);

	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("model/trial.md2"));

	smgr->addCubeSceneNode(5);

	if(node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setMD2Animation (scene::EMAT_STAND);
		//node->setMaterialTexture(0, driver->getTexture("img/sydney.bmp"));
		//node->setJointMode(EJUOR_CONTROL);
		//IBoneSceneNode* right_arm = node->getJointNode("Arm_R");
		//node->setAnimationSpeed(15);
		//node->setFrameLoop(1, 10);
		//node->animateJoints(true);
	}

	// add a camera at (0, 30, -40) looking at (0, 5, 0);
	ICameraSceneNode* cam = smgr->addCameraSceneNode(0, vector3df(0, 0, -40), vector3df(0, 5, 0));

	//ILightSceneNode* light = smgr->addLightSceneNode(0, vector3df(0,40,-40));

	int lastFPS = 0;
	// start the main device loop;
	while(device->run())
	{
		if(keyboardReceiver.IsKeyDown(irr::KEY_KEY_W))
		{
			core::vector3df v1 = cam->getPosition();
			core::vector3df v2 = cam->getTarget();
			v1.Z += .5f;
			v2.Z += .5f;
			cam->setPosition(v1);
			cam->setTarget(v2);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else if(keyboardReceiver.IsKeyDown(irr::KEY_KEY_S))
		{
			core::vector3df v1 = cam->getPosition();
			core::vector3df v2 = cam->getTarget();
			v1.Z -= .5f;
			v2.Z -= .5f;
			cam->setPosition(v1);
			cam->setTarget(v2);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		if(keyboardReceiver.IsKeyDown(irr::KEY_KEY_A))
		{
			core::vector3df v1 = cam->getPosition();
			core::vector3df v2 = cam->getTarget();
			v1.X -= .5f;
			v2.X -= .5f;
			cam->setPosition(v1);
			cam->setTarget(v2);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else if(keyboardReceiver.IsKeyDown(irr::KEY_KEY_D))
		{
			core::vector3df v1 = cam->getPosition();
			core::vector3df v2 = cam->getTarget();
			v1.X += .5f;
			v2.X += .5f;
			cam->setPosition(v1);
			cam->setTarget(v2);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else if(keyboardReceiver.IsKeyDown(irr::KEY_KEY_E))
		{
			core::vector3df v1 = cam->getPosition();
			v1.rotateXZBy(1, cam->getTarget());
			cam->setPosition(v1);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else if(keyboardReceiver.IsKeyDown(irr::KEY_KEY_Q))
		{
			core::vector3df v1 = cam->getPosition();
			v1.rotateXZBy(-1, cam->getTarget());
			cam->setPosition(v1);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else
		{
			//node->setMD2Animation (scene::EMAT_STAND);
		}
		
		// begin scene;
		// things should be drawn after this call;
		driver->beginScene(true, true, SColor(255,128,128,128));

		// draw the things;
		smgr->drawAll();
		guienv->drawAll();

		int fps = driver->getFPS();

		if(lastFPS != fps)
		{
			core::stringw str = L"FYP - v0.1 r14 [FPS:";
			str += fps;
			str += "]";

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}

		// nothings should be drawn after this call;
		// screen is presented after this call;
		driver->endScene();
	}

	// call drop() for those object created by create* function;
	device->drop();

	return 0;
}

