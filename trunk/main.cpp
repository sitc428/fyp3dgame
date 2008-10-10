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

int main(int argc, char* argv[])
{
	IrrlichtDevice* device =
#ifdef _IRR_OSX_PLATFORM_
	createDevice(video::EDT_OPENGL, dimension2d<s32>(640, 480), 16, false, false, false, 0);
#else
	createDevice(video::EDT_SOFTWARE, dimension2d<s32>(640, 480), 16, false, false, false, 0);
#endif
	
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

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

	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("model/sydney.md2"));

	if(node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation (scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("img/sydney.bmp"));
	}

	// add a camera at (0, 30, -40) looking at (0, 5, 0);
	smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

	// start the main device loop;
	while(device->run())
	{
		// begin scene;
		// things should be drawn after this call;
		driver->beginScene(true, true, SColor(255,100,101,140));

		// draw the things;
		smgr->drawAll();
		guienv->drawAll();

		// nothings should be drawn after this call;
		// screen is presented after this call;
		driver->endScene();
	}

	// call drop() for those object created by create* function;
	device->drop();

	return 0;
}

