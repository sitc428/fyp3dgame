#ifndef StartupScreen_h
#define StartupScreen_h

#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::gui;


class StartupScreen
{
public:
	// constructor
	StartupScreen();
	// destructor
	~StartupScreen();

	void Init();
	// called every frame with the frame's elapsed time
	void Tick( f32 delta );
	void Exit();

private:
	// perform an tick of the input system
	void DoInput();

	ITexture*		LethalIndustryLogoTexture;		// texture with the lethalindustry logo
	IGUIImage*		LethalIndustryLogoImage;		// gui element which contains the lethal industry image
	ITexture*		EngineLogoTexture;				// texture with the irrEngine logo
	IGUIImage*		EngineLogoImage;				// gui element which contains the background image

	f32				elapsedTime;					// keeps track how long the startup screen has been up
};

#endif //StartupScreen