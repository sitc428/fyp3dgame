#include <iostream>
#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
#endif

/*!
 * Doxygen format comment
 * Try it out by yourself~
 */
int main(int argc, char* argv[])
{
	IrrlichtDevice *device =

#ifdef _IRR_OSX_PLATFORM_
		createDevice( video::EDT_OPENGL, dimension2d<s32>(640, 480), 16, false, false, false, 0);
#else
		createDevice( video::EDT_SOFTWARE, dimension2d<s32>(640, 480), 16, false, false, false, 0);
#endif
	device->setWindowCaption(L"Game Name");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Game Name", rect<s32>(10,10,260,22), true);

	IAnimatedMesh* mesh = smgr->getMesh("sydney.md2");
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation ( scene::EMAT_STAND );
		node->setMaterialTexture( 0, driver->getTexture("sydney.bmp") );
	}

	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
	
		driver->endScene();
	}

	device->drop();

	return 0;
}

