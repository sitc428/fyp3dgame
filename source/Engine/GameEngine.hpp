#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include <irrklang/irrKlang.h>
#include <irrlicht/irrlicht.h>

#include <string>
#include <map>

#include "Check.h"

const irr::f64 PI = 3.14159265;

class FrontEnd;
class GameWorld;
class InputEventReceiver;
class ParticleManager;
class StartupScreen;

namespace irr
{
	namespace gui
	{
		class CGUITTFace;
		class CGUITTFont;
	}

	namespace scene
	{
		class CFloorDecalSceneNode;
	}
}

enum EEngineState
{
	state_STARTUP, // game intro sequence
	state_FRONTEND, // game is in the main menu front end
	state_GAME, // game is actively playing
	state_EXIT // game is exiting
};

/**
 * Engine class responsible for driver initialization and shutdown.
 * It also keeps track of some vital global variables
 */
class GameEngine
{
public:
	GameEngine();

	bool Init();
	void Exit();
	void Run();

	void InitStartupScreen();
	void ExitStartupScreen();
	void InitFrontEnd();
	void ExitFrontEnd();
	void InitGameplay();
	void ExitGameplay();

	// accessor, should be self-explained by function name
	irr::IrrlichtDevice& GetDevice() const { return *device; }
	irr::video::IVideoDriver& GetDriver() const { return *driver; }
	irr::scene::ISceneManager& GetSceneManager() const { return *smgr; }
	InputEventReceiver& GetReceiver() const { return *receiver; }
	irrklang::ISoundEngine& GetSoundEngine() const { return *soundEngine; }
	ParticleManager& GetParticleManager() { return *particleManager; }
	irr::gui::CGUITTFont* GetFont(std::string fontName, int fontSize) { return _fonts[std::pair<std::string, int>(fontName, fontSize)]; }
	const irr::core::dimension2d<irr::s32> & const GetScreenSize() const { return screenSize; }

	irr::u32 GetRealTime() const {
#if defined _IRR_WINDOWS_
		return GetDevice().getTimer()->getRealTime();
#else
		return GetDevice().getTimer()->getTime();
#endif
	}

	// unbuffered mouse input 
	void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent );

	//! Adds a floor decal billboard scene node to the scene. This scene node has a texture which always faces up
	/** 
	  \param parent: Parent scene node of the billboard. Can be null. If the parent moves,
	  the billboard will move too.
	  \param position: Position of the space relative to its parent
	  where the billboard will be placed.
	  \param size: Size of the billboard. This size is 2 dimensional because a billboard only has
	  width and height.
	  \param id: An id of the node. This id can be used to identify the node.
	  \param shade_top: vertex color top
	  \param shade_down: vertex color down
	  \return Returns pointer to the billboard if successful, otherwise NULL.
	  This pointer should not be dropped. See IReferenceCounted::drop() for more information. */

	irr::scene::CFloorDecalSceneNode* addFloorDecalSceneNode(irr::scene::ISceneNode* parent = 0,
			const irr::core::dimension2d<irr::f32>& size = irr::core::dimension2d<irr::f32>(10.0f, 10.0f),
			const irr::core::vector3df& position = irr::core::vector3df(0,0,0), irr::s32 id=-1,
			irr::video::SColor shade_top = 0xFFFFFFFF, irr::video::SColor shade_down = 0xFFFFFFFF);

	// controls for state transitions
	void RequestStateChange( EEngineState newState );

	// changes the music playing
	void ChangeBGM( const irr::c8* name = NULL );

private:
	// perform the main tick update for the current state
	void TickCurrentState( irr::f32 delta );
	void TickHUD( irr::f32 delta);

	// private helpers used in state transitions
	void CleanupCurrentState();

	void GoToStartupScreen();
	void GoToFrontEnd();
	void GoToGameplay();
	void GoToExit();

	// perform a state transition if one was requested
	void HandleRequestedStateChange();

	// calculate the elapse time
	irr::f32  CalcElapsedTime();

	// display the fps
	void DisplayFPS();

	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* smgr;
	InputEventReceiver* receiver;
	irrklang::ISoundEngine* soundEngine;
	ParticleManager* particleManager; // particle manager for easy creation of particle effects 

	std::map<std::string, irr::gui::CGUITTFace*> _faces; // face cache ( ttf files )
	std::map< std::pair<std::string, int>, irr::gui::CGUITTFont* > _fonts; // the font

	irr::core::dimension2d<irr::s32> screenSize;

	irr::u32 lastTime; // used to get elapsed time

	EEngineState state; // the state the engine is in
	EEngineState requestedNextState; // requested next state we want to transition to 

	StartupScreen* startupScreen;
	FrontEnd* frontEnd;
	GameWorld* world;

	irrklang::ISound* gameMusic;
};

#endif //__GAME_ENGINE_HPP__
