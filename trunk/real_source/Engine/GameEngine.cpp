#include "GameEngine.h"
#include <iostream>
#include "InputEventReceiver.h"
#include "GameWorld.h"
#include "StartupScreen.h"
#include "FrontEnd.h"
#include "FloorDecalSceneNode.h"
#include "ParticleManager.h"

#ifdef _IRR_WINDOWS_
#include <windows.h>

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#pragma comment(lib, "freetype.lib")

#endif

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

/**
	Constructor
*/
GameEngine::GameEngine():
device(NULL),
driver(NULL),
smgr(NULL),
//soundEngine(NULL),
receiver(NULL),
screenSize(0,0),
cursorLock(true),
lastCursorPosition(0,0),
scrMid(0,0),
state(state_EXIT), // defaulting to exit state, to be able to shutdown cleanly if the engine initialization failed
requestedNextState(state_EXIT),
startupScreen(NULL),
frontEnd(NULL),
world(NULL),
particleManager(NULL),
GlobalWeatherEffect(NULL)
//gameMusic(NULL)
{
}


/**
	Initializes the engine, creates the device, sets up the driver and the scene manager.
	If the function returns false, the program should exit.
*/
bool GameEngine::Init()
{
	// let user select driver type
	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;

	// prompt the user to select a driver type, if an invalid choice has been specified we should exit the program
	bool result = PromptForDriverType( driverType );	
	if( !result )
	{
		return false;
	}

	bool isFullScreen;
	result = PromptForScreenSize( screenSize, isFullScreen );
	if( !result )
	{
		return false;
	}

	// create an event receiver
	receiver = new InputEventReceiver( *this );
	if( !receiver )
	{
		return false;
	}

	// create the device
	device = createDevice( driverType, screenSize,
		16, isFullScreen, false, false, receiver);

	if( !device )
	{
		return false; // could not create selected driver.
	}

	// setup the driver and the scenemanager
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	// calculate middle of screen
	scrMid.X = screenSize.Width/2;
	scrMid.Y = screenSize.Height/2;

	// create sound engine
	//soundEngine = createIrrKlangDevice();
	/*if( !soundEngine )
		return 0; // error starting up the sound engine
	*/
	 
	// randomize randomize :)
	srand( GetRealTime() );

	// create a particle manager instance
	particleManager = new ParticleManager( *smgr );

	// init the global weather effect
	InitGlobalWeatherEffect();

	// init successfull
	return true;
}

void GameEngine::InitGlobalWeatherEffect()
{
	check(GlobalWeatherEffect == NULL);
	GlobalWeatherEffect = smgr->addParticleSystemSceneNode( false );
	check(GlobalWeatherEffect);
	particleManager->CreateFallingSnowEmitter(*GlobalWeatherEffect);
}

/**
	Shuts down the game engine, properly cleans up the device.
*/
void GameEngine::Exit()
{
	// make sure that the only way to exit the game is through the exit state
	check( state == state_EXIT );
	// make sure all the objects associated with different states have been cleaned up
	check( startupScreen == NULL );
	check( frontEnd == NULL );
	check( world == NULL );

	/*if(soundEngine)
	{
		soundEngine->drop();
		soundEngine = NULL;
	}
	 */

	// clean up the global weather effect
	if(GlobalWeatherEffect)
	{
		// this is cleaned up when game world exits
		smgr->addToDeletionQueue(GlobalWeatherEffect);
		GlobalWeatherEffect = NULL;
	}

	// clean up the particle manager
	delete particleManager;
	particleManager = NULL;

	/*
	In the end, delete the Irrlicht device.
	*/
	if( device )
	{
		device->drop();
		device = NULL;
		driver = NULL;
		smgr = NULL;
	}

	delete receiver;
	receiver = NULL;
}

void GameEngine::InitStartupScreen()
{
	check(startupScreen == NULL);
	startupScreen = new StartupScreen();
	startupScreen->Init();
}

void GameEngine::ExitStartupScreen()
{
	// delete the startupScreen object
	check(startupScreen);
	startupScreen->Exit();
	delete startupScreen;
	startupScreen = NULL;
}

void GameEngine::InitFrontEnd()
{
	check(frontEnd == NULL);
	frontEnd = new FrontEnd();
	frontEnd->Init();

	// load and play music
	//ChangeMusic("../audio/music/track2.mp3");
}

void GameEngine::ExitFrontEnd()
{
	// delete the frontEnd object
	check(frontEnd);
	frontEnd->Exit();
	delete frontEnd;
	frontEnd = NULL;
}

/**
	Sets up the initial gameplay state
*/
void GameEngine::InitGameplay()
{
	lastTime = GetRealTime();

	// create a new game world
	world = new GameWorld( *this );
	world->Init();
	
	// turn off the mouse cursor for gameplay
	device->getCursorControl()->setVisible(false);
}

/**
	Shuts down gameplay
*/
void GameEngine::ExitGameplay()
{
	// delete the gameplay world
	check(world);
	world->Exit();
	delete world;
	world = NULL;
}

/**
	This is where the main loop is executed
*/
void GameEngine::Run()
{
	// start by going to the startupscreen state
	GoToStartupScreen();

	/*
	Game Loop
	*/
	while( device->run() && state != state_EXIT )
	{
		// calculate elapsed time per frame
		f32 frameDelta = CalcElapsedTime();

		driver->beginScene(true, true, video::SColor(255,0,0,0));

		// perform the main tick update for the current state
		TickCurrentState( frameDelta );

		// draw the 3d scene
		smgr->drawAll(); 

		// draw all UI elements after the 3d scene
		device->getGUIEnvironment()->drawAll();

		driver->endScene();

		// if ESCAPE was pressed, request a game exit
		if( receiver->IsKeyDown(irr::KEY_ESCAPE) )
		{
			RequestStateChange(state_EXIT);
		}

		// perform a state transition if one was requested
		HandleRequestedStateChange();
	
#if _DEBUG
		// display current FPS of the game
		DisplayFPS();
#endif
	}

	// if the game wasn't shut down by pressing ESCAPE, then we still need to do some cleanup
	if(state != state_EXIT)
	{
		GoToExit();
	}
}

// perform the main tick update for the current state
void GameEngine::TickCurrentState( f32 delta )
{
	switch( state )
	{
		case state_STARTUP:
		{
			check( startupScreen );
			startupScreen->Tick( delta );
			break;
		}
		case state_FRONTEND:
		{
			check( frontEnd );
			frontEnd->Tick( delta );
			break;
		}
		case state_GAME:
		{
			check( world );
			world->Tick( delta );
			break;
		}
		default:
		{
		  // shouldn't be here
		  check( false );
		}
	}
}

/**
	Displays a message to the console prompting the user to select a display driver type, and reads in the input.
	Function returns true if valid driver has been specified, and stores the result in the outDriverType.
	Returns false if an invalid choice has been specified.	
*/
bool GameEngine::PromptForDriverType( video::E_DRIVER_TYPE& outDriverType )
{
	printf("Please select the driver you want for this example:\n"\
		" (a) Direct3D 9.0c\n (b) Direct3D 8.1\n (c) OpenGL 1.5\n"\
		" (d) Software Renderer\n (e) Burning's Software Renderer\n"\
		" (f) NullDevice\n (otherKey) exit\n\n");

	char i;
	std::cin >> i;

	switch(i)
	{
		case 'a': outDriverType = video::EDT_DIRECT3D9;break;
		case 'b': outDriverType = video::EDT_DIRECT3D8;break;
		case 'c': outDriverType = video::EDT_OPENGL;   break;
		case 'd': outDriverType = video::EDT_SOFTWARE; break;
		case 'e': outDriverType = video::EDT_BURNINGSVIDEO;break;
		case 'f': outDriverType = video::EDT_NULL;     break;
		default: return false;
	}	

	return true;
}

/**
	Displays a message to the console prompting the user to select a display size
*/
bool GameEngine::PromptForScreenSize( dimension2d<s32>& outScreensize, bool& outIsFullscreen )
{
	printf("\n\nPlease select the display size:\n"\
		" (a) 800x600 windowed\n (b) 1280x720 fullscreen\n (c) 800x600 fullscreen\n (d) 1280x720 windowed\n (otherKey) exit\n\n");

	char i;
	std::cin >> i;

	switch(i)
	{
		case 'a': outScreensize = dimension2d<s32>(800,600); outIsFullscreen = false; break;
		case 'b': outScreensize = dimension2d<s32>(1280,720); outIsFullscreen = true; break;
		case 'c': outScreensize = dimension2d<s32>(800,600); outIsFullscreen = true; break;
		case 'd': outScreensize = dimension2d<s32>(1280,720); outIsFullscreen = false; break;
		default: return false;
	}	

	return true;
}

/**
	Calculates elapsed time for each frame iteration
*/
f32 GameEngine::CalcElapsedTime()
{
#ifdef WIN32
    static __int64 gTime, gLastTime;
    __int64 freq;
    QueryPerformanceCounter((LARGE_INTEGER *)&gTime);
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
	f32 elapsedTime = ( ( f32 )( gTime - gLastTime )/( f32 )freq );
	gLastTime = gTime;
	if( elapsedTime > 1.0f )	// watch for crazy numbers
		elapsedTime = 0;
	return elapsedTime;

#else

	// get elapsed time per frame (dTime)
	u32 time = GetRealTime();
	s32 dTime = time - lastTime;
	lastTime = time;

	return dTime / 1000.0f;
#endif
}

/**
	Displays current frames per second
*/
void GameEngine::DisplayFPS()
{
	static s32 lastFPS = -1;
	
	s32 fps = driver->getFPS();
	if (lastFPS != fps)
	{
		core::stringw str = L"SnowballGame [";
		str += driver->getName();
		str += "] FPS:";
		str += fps;

		device->setWindowCaption(str.c_str());
		lastFPS = fps;
	}
}

/**
	Locks cursor to the middle of the screen when using camera view, or unlocks it when you need to move the cursor around
*/
void GameEngine::LockCursor( bool lock )
{
	gui::ICursorControl* cursor = device->getCursorControl();
	cursor->grab();

	if( !lock )
	{
		cursorLock = false;
		lastCursorPosition = cursor->getPosition();
	}
	else
	{
		cursorLock = true;
		// put cursor into middle of screen to prepare it for next GetMouseDelta call
		cursor->setPosition(scrMid);
	}

	cursor->drop();
}

/**
	Calculates mouse movement using cursor displacement
*/
position2d<s32> GameEngine::GetMouseDelta()
{
	gui::ICursorControl* cursor = device->getCursorControl();
	cursor->grab();

	position2d<s32> mouseOffset;

	if( cursorLock )
	{
		// calculate relative offset from center of screen
		mouseOffset = (scrMid - cursor->getPosition());

		// put cursor back into center of the screen
		cursor->setPosition(scrMid);
	}
	else
	{
		mouseOffset = lastCursorPosition - cursor->getPosition();
		lastCursorPosition = cursor->getPosition();
	}

	cursor->drop();

	
	return mouseOffset;
}

// unbuffered mouse input 
void GameEngine::OnMouseEvent( const SEvent::SMouseInput& mouseEvent )
{
	// route the unbuffered mouse input events to the game world if it exists
	if( world )
	{
		world->OnMouseEvent( mouseEvent );
	}
}

// controls for state transitions
void GameEngine::RequestStateChange( EEngineState newState )
{
	requestedNextState = newState;
}

// depending on what state we're in we must do different cleanup, after this function is called you must initialize and enter another state
void GameEngine::CleanupCurrentState()
{
	switch( state )
	{
		case state_STARTUP:
		{
			ExitStartupScreen();
			break;
		}
		case state_FRONTEND:
		{
			ExitFrontEnd();
			break;
		}
		case state_GAME:
		{
			ExitGameplay();
			break;
		}
		case state_EXIT:
		{
			// no cleanup required for this state
			break;
		}
		default:
		{
			// shouldn't be here
			check( false );
		}
	}
}

// controls for state transitions
void GameEngine::GoToStartupScreen()
{
	// assuming the engine gets constructed with the EXIT as a default for state and requestedNextState
	// and we don't transition to startupscreen state via HandleRequestedStateChange
	check(state == state_EXIT);
	check(requestedNextState == state_EXIT);
	CleanupCurrentState();

	InitStartupScreen();
	state = state_STARTUP;
	requestedNextState = state_STARTUP;
}		  
		  
void GameEngine::GoToFrontEnd()
{
	// we're only allowing transition to frontend from the startup or gameplay
	check( state == state_GAME || state == state_STARTUP )
	CleanupCurrentState();

	InitFrontEnd();
	state = state_FRONTEND;
}
void GameEngine::GoToGameplay()
{
	// we're only allowing transition to gameplay from the frontend state
	check( state == state_FRONTEND )
	CleanupCurrentState();

	InitGameplay();
	state = state_GAME;
}
void GameEngine::GoToExit()
{
	CleanupCurrentState();
	state = state_EXIT;
}

// perform a state transition if one was requested
void GameEngine::HandleRequestedStateChange()
{
	if( requestedNextState != state )
	{
		switch( requestedNextState )
		{
			case state_STARTUP:
			{
				check(false);  // transition back to the startup state doesnt make sense?
				break;
			}
			case state_FRONTEND:
			{
				GoToFrontEnd();
				break;
			}
			case state_GAME:
			{
				GoToGameplay();
				break;
			}
			case state_EXIT:
			{
				GoToExit();
				break;
			}
			default:
			{
				check(false);  // should not be here
			}
		}

		// make sure the state has been properly updated
		check(requestedNextState == state);
	}
}

//! Adds a floor decal billboard scene node to the scene. This scene node has a texture which always faces up
CFloorDecalSceneNode* GameEngine::addFloorDecalSceneNode(ISceneNode* parent,
	const core::dimension2d<f32>& size, const core::vector3df& position, s32 id,
	video::SColor shade_top, video::SColor shade_down )
{
	if (!parent)
		parent = smgr->getRootSceneNode();

	CFloorDecalSceneNode* node = new CFloorDecalSceneNode(parent, smgr, id, position, size,
		shade_top, shade_down);
	node->drop();

	return node;
}
/*

void GameEngine::ChangeMusic( const c8* name )
{
	if( gameMusic )
	{
		gameMusic->stop();
		gameMusic->drop();
		gameMusic = NULL;
	}

	if( name == NULL )
	{
		// load and play music
		gameMusic = GetSoundEngine().play2D("../audio/music/track1.mp3", true, false, true);
		check(gameMusic);
		gameMusic->setVolume( 0.15f );
	}
	else
	{
		// load and play music
		gameMusic = GetSoundEngine().play2D(name, true, false, true);
		check(gameMusic);
		gameMusic->setVolume( 0.65f );
	}

}*/