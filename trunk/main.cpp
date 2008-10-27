#include <irrlicht.h>
#include <iostream>
// The irrlicht namespace
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
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

class MyShaderCallBack : public video::IShaderConstantSetCallBack
{
	public:
		MyShaderCallBack(IrrlichtDevice* _device, core::vector3df* _lightPos) : device(_device), lightPos(_lightPos)
		{
		}

		virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
		{
			//video::IVideoDriver* driver = services->getVideoDriver();

			core::vector3df camPos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
			services->setVertexShaderConstant("view_position", reinterpret_cast<f32*>(&camPos), 3);
			services->setVertexShaderConstant("LightPosition", reinterpret_cast<f32*>(lightPos), 3);
		}
	private:
		IrrlichtDevice* device;
		core::vector3df* lightPos;
};

int main(int argc, char* argv[])
{
	KeyboardEventReceiver keyboardReceiver;
	video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;
	IrrlichtDevice* device = createDevice(driverType, core::dimension2d<s32>(640, 480), 16, false, false, false, &keyboardReceiver);

	if(device == 0)
		return 1;

	device->setWindowCaption(L"FYP - v0.1 r23");

	// get the device driver;
	IVideoDriver *driver = device->getVideoDriver();

	// get the handler of the scene manager;
	ISceneManager *smgr = device->getSceneManager();

	// get the handler of the gui enviroment;
	IGUIEnvironment *guienv = device->getGUIEnvironment();

	c8* vsFileName = "model/trial.vert"; // filename for the vertex shader
	c8* psFileName = "model/trial.frag"; // filename for the pixel shader

	if (!driver->queryFeature(video::EVDF_PIXEL_SHADER_1_1) &&
			!driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1))
	{
		device->getLogger()->log("WARNING: Pixel shaders disabled "\
				"because of missing driver/hardware support.");
		psFileName = 0;
	}

	if (!driver->queryFeature(video::EVDF_VERTEX_SHADER_1_1) &&
			!driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1))
	{
		device->getLogger()->log("WARNING: Vertex shaders disabled "\
				"because of missing driver/hardware support.");
		vsFileName = 0;
	}

	video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();

	//smgr->loadScene("sc.irr");

	s32 newMaterialType = 0;

	ILightSceneNode* light = smgr->addLightSceneNode(0, vector3df(0, 10, 4), video::SColorf(), 0);

	if(gpu)
	{
		MyShaderCallBack* mc = new MyShaderCallBack(device, &(light->getAbsolutePosition()));

		if(1)
		{
			newMaterialType = gpu->addHighLevelShaderMaterialFromFiles(
					vsFileName, "vertexMain", video::EVST_VS_1_1,
					psFileName, "pixelMain", video::EPST_PS_1_1,
					mc, video::EMT_SOLID);
		}
		else
		{
			// create material from low level shaders (asm or arb_asm)
			newMaterialType = gpu->addShaderMaterialFromFiles(vsFileName, psFileName, mc, video::EMT_TRANSPARENT_ADD_COLOR);
		}

		mc->drop();
	}

	//IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("model/trial.obj"));
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("model/dwarf.x"));

	if(node)
	{
		//node->setMaterialTexture(0, driver->getTexture("img/sydney.bmp"));
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialType((video::E_MATERIAL_TYPE)newMaterialType);
	}

	node->setJointMode(EJUOR_CONTROL);

	//IBoneSceneNode* hand = node->getJointNode("manoL");
	
	scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(10.0f,10.0f,10.0f));

	// add a camera at (0, 30, -40) looking at (0, 5, 0);
	ICameraSceneNode* cam = smgr->addCameraSceneNode(0, vector3df(0, 0, -40), vector3df(0, 5, 0));
	
	node->addAnimator(anim);
	anim->drop();

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
		else if(keyboardReceiver.IsKeyDown(irr::KEY_KEY_Z))
		{
			core::vector3df v1 = cam->getPosition();
			core::vector3df v2 = cam->getTarget();
			v1.Y += .5f;
			v2.Y += .5f;
			cam->setPosition(v1);
			cam->setTarget(v2);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else if(keyboardReceiver.IsKeyDown(irr::KEY_KEY_X))
		{
			core::vector3df v1 = cam->getPosition();
			core::vector3df v2 = cam->getTarget();
			v1.Y -= .5f;
			v2.Y -= .5f;
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
		else if(keyboardReceiver.IsKeyDown(irr::KEY_UP))
		{
			core::vector3df v1 = cam->getPosition();
			v1.rotateYZBy(-1, cam->getTarget());
			cam->setPosition(v1);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else if(keyboardReceiver.IsKeyDown(irr::KEY_DOWN))
		{
			core::vector3df v1 = cam->getPosition();
			v1.rotateYZBy(1, cam->getTarget());
			cam->setPosition(v1);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else if(keyboardReceiver.IsKeyDown(irr::KEY_LEFT))
		{
			core::vector3df v1 = cam->getPosition();
			v1.rotateXYBy(-1, cam->getTarget());
			cam->setPosition(v1);
			//node->setMD2Animation (scene::EMAT_RUN);
		}
		else if(keyboardReceiver.IsKeyDown(irr::KEY_RIGHT))
		{
			core::vector3df v1 = cam->getPosition();
			v1.rotateXYBy(1, cam->getTarget());
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

