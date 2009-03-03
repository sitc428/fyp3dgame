#ifndef __STARTUP_SCREEN_HPP__
#define __STARTUP_SCREEN_HPP__

#include <irrlicht/irrlicht.h>

class StartupScreen
{
	public:
		// constructor
		StartupScreen();
		// destructor
		~StartupScreen();

		void Init();
		// called every frame with the frame's elapsed time
		void Tick( irr::f32 delta );
		void Exit();

	private:
		// perform an tick of the input system
		void DoInput();

		irr::video::ITexture* LethalIndustryLogoTexture; // texture with the lethalindustry logo
		irr::gui::IGUIImage* LethalIndustryLogoImage; // gui element which contains the lethal industry image
		irr::video::ITexture* EngineLogoTexture; // texture with the irrEngine logo
		irr::gui::IGUIImage* EngineLogoImage; // gui element which contains the background image

		irr::f32 elapsedTime; // keeps track how long the startup screen has been up
};

#endif //__STARTUP_SCREEN_HPP__
