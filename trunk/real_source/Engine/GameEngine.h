#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
#include "Check.h"

class InputEventReceiver;
class StartupScreen;
class FrontEnd;
class GameWorld;
class ParticleManager;

namespace irr
{
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
		void LockCursor( bool lock = true );
	
		irr::core::position2d<irr::s32> GetMouseDelta();

		irr::IrrlichtDevice& GetDevice() const { return *device; }

		irr::video::IVideoDriver& GetDriver() const { return *driver; }

		irr::scene::ISceneManager& GetSceneManager() const { return *smgr; }

		InputEventReceiver& GetReceiver() const { return *receiver; }

		irrklang::ISoundEngine& GetSoundEngine() const { return *soundEngine; }

		ParticleManager& GetParticleManager() { return *particleManager; }

		const irr::core::dimension2d<irr::s32>& GetScreenSize() const { return screenSize; }

		irr::u32 GetRealTime() const { return GetDevice().getTimer()->getTime(); }

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
		void ChangeMusic( const irr::c8* name = NULL );

		void InitGlobalWeatherEffect();

	private:
		// perform the main tick update for the current state
		void TickCurrentState( irr::f32 delta );

		// private helpers used in state transitions
		void CleanupCurrentState();

		void GoToStartupScreen();
		void GoToFrontEnd();
		void GoToGameplay();
		void GoToExit();

		// perform a state transition if one was requested
		void HandleRequestedStateChange();

		irr::IrrlichtDevice* device;
		irr::video::IVideoDriver* driver;
		irr::scene::ISceneManager* smgr;
		InputEventReceiver* receiver;
		irrklang::ISoundEngine* soundEngine;
		ParticleManager* particleManager; // particle manager for easy creation of particle effects 

		irr::core::dimension2d<irr::s32> screenSize;

		bool cursorLock;
		irr::core::position2d<irr::s32> lastCursorPosition;
		irr::core::position2d<irr::s32> scrMid; // coordinates for middle of screen
		irr::u32 lastTime; // used to get elapsed time

		EEngineState state; // the state the engine is in
		EEngineState requestedNextState; // requested next state we want to transition to 

		StartupScreen* startupScreen;
		FrontEnd* frontEnd;
		GameWorld* world;

		irrklang::ISound* gameMusic;
		// HACK
	public:
		irr::scene::IParticleSystemSceneNode* GlobalWeatherEffect;  // global weather effect
	private:

		bool PromptForDriverType( irr::video::E_DRIVER_TYPE& outDriverType );
		bool PromptForScreenSize( irr::core::dimension2d<irr::s32>& outScreensize, bool& outIsFullscreen );
		irr::f32  CalcElapsedTime();
		void DisplayFPS();
};

#endif //__GAME_ENGINE_HPP__
