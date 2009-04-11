#ifndef __STARTUP_SCREEN_HPP__
#define __STARTUP_SCREEN_HPP__

#include <irrlicht/irrlicht.h>

class StartupScreen
{
	public:
		// constructor
		StartupScreen( GameEngine& );
		// destructor
		~StartupScreen();

		void Init();
		// called every frame with the frame's elapsed time
		void Tick( irr::f32 delta );
		void Exit();

	private:
		// perform an tick of the input system
		void DoInput();

		irr::video::ITexture* GroupLogoTexture; // texture of the group logo
		irr::gui::IGUIImage* GroupLogoImage; // gui element of the group logo image
		irr::video::ITexture* EngineLogoTexture; // texture of the irrEngine logo
		irr::gui::IGUIImage* EngineLogoImage; // gui element of the irrEngine logo image

		irr::f32 elapsedTime; // keeps track how long the startup screen has been up

		GameEngine& GEngine;
};

#endif //__STARTUP_SCREEN_HPP__
