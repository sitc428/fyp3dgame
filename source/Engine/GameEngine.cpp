#include "FontManager.hpp"
#include "FrontEnd.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "InputEventReceiver.hpp"
#include "ParticleManager.hpp"
#include "ShaderFactory.hpp"
#include "StartupScreen.hpp"

#include <boost/thread.hpp>
#include <fstream>

#ifdef _IRR_WINDOWS_

#include <windows.h>

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#pragma comment(lib, "freetype.lib")

#endif

/**
  Constructor
  */
GameEngine::GameEngine()
	:device(NULL),
	driver(NULL),
	smgr(NULL),
	receiver(NULL),
	shaderFactory(NULL),
	soundEngine(NULL),
	fmgr(NULL),
	screenSize(800, 600),
	lastTime(0),
	state(state_EXIT), // defaulting to exit state, to be able to shutdown cleanly if the engine initialization failed
	requestedNextState(state_EXIT),
	startupScreen(NULL),
	frontEnd(NULL),
	world(NULL),
	gameMusic(NULL)
{
}


/**
  Initializes the engine, creates the device, sets up the driver and the scene manager.
  If the function returns false, the program should exit.
  */
bool GameEngine::Init()
{
	// let user select driver type
	irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;

	// create an event receiver
	receiver = new InputEventReceiver();
	if( !receiver )
		return false;

	// create the device
	device = irr::createDevice( driverType, screenSize, 32, false, false, false, receiver );

	if( !device )
		return false; // could not create selected driver.

	// setup the driver and the scenemanager
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	device->getFileSystem()->addZipFileArchive("media.zip");

	fmgr = new FontManager( driver );

	// create sound engine
	soundEngine = irrklang::createIrrKlangDevice();
	if( !soundEngine )
		return 0; // error starting up the sound engine

	// randomize randomize :)
	srand( GetRealTime() );

	// create the shader factoty
	shaderFactory = new ShaderFactory( *this );

	// print out wraning message if the shader is not available
	if( !shaderFactory->ShaderAvailable() )
		std::cout << "Shader Not Available, all shadering effect will be disabled." << std::endl;

	// start preloading all the media into cache, using thread if possible
#ifdef _IRR_WINDOWS_
	//boost::thread textureThread( boost::bind(&GameEngine::PreloadTexture, this) );
	PreloadTexture();
	PreloadModel();
#else
	#ifdef MACOSX
	PreloadTexture();
	PreloadModel();
	#endif
#endif

	// init successfull
	return true;
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

	if(soundEngine)
	{
		soundEngine->drop();
		soundEngine = NULL;
	}

	if( shaderFactory )
	{
		delete shaderFactory;
		shaderFactory = NULL;
	}

	if( receiver )
	{
		delete receiver;
		receiver = NULL;
	}

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
}

void GameEngine::InitStartupScreen()
{
	check(startupScreen == NULL);
	startupScreen = new StartupScreen( *this );
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
	frontEnd = new FrontEnd( *this );
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
		receiver->disable();

		// calculate elapsed time per frame
		irr::f32 frameDelta = CalcElapsedTime();

		driver->beginScene(true, true, irr::video::SColor(255,0,0,0));

		// perform the main tick update for the current state
		TickCurrentState( frameDelta );
		
		// draw the 3d scene
		smgr->drawAll();

		// draw all UI elements after the 3d scene
		device->getGUIEnvironment()->drawAll();
		TickHUD(frameDelta);

		driver->endScene();

		receiver->enable();

		// perform a state transition if one was requested
		HandleRequestedStateChange();

		DisplayFPS();
	}

	// if the game wasn't shut down by pressing ESCAPE, then we still need to do some cleanup
	if(state != state_EXIT)
	{
		GoToExit();
	}
}

void GameEngine::PreloadTexture()
{
	std::ifstream textureList("media/model/TextureList.rxw");

	if( textureList )
	{
		std::string texturePath = "";
		while( !textureList.eof() )
		{
			std::getline( textureList, texturePath );

			if( texturePath != "" )
			{
				driver->getTexture( texturePath.c_str() );
				texturePool.push_back( driver->getTexture( texturePath.c_str() ) );
			}
		}
	}

	textureList.close();

#ifdef _IRR_WINDOWS_
	//boost::thread modelThread( boost::bind(&GameEngine::PreloadModel, this) );
#endif
}

void GameEngine::PreloadModel()
{
	std::ifstream modelList("media/model/ModelList.rxw");

	if( modelList )
	{
		std::string modelPath;
		while( !modelList.eof() )
		{
			std::getline( modelList, modelPath );

			if( modelPath != "")
			{
				smgr->getMesh( modelPath.c_str() );
				modelMeshPool.push_back( smgr->getMesh( modelPath.c_str() ) );
			}
		}
	}

	modelList.close();
}

void GameEngine::TickHUD(irr::f32 delta)
{
	switch( state )
	{
		case state_GAME:
		case state_PAUSED:
		{
			check( world );
			world->UpdateHUD( delta );
			break;
		}
		default:
		{
			break;
		}
	}
	
}


// perform the main tick update for the current state
void GameEngine::TickCurrentState( irr::f32 delta )
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
  Calculates elapsed time for each frame iteration
  */
irr::f32 GameEngine::CalcElapsedTime()
{
#ifdef _IRR_WINDOWS_
	static __int64 gTime, gLastTime;
	__int64 freq;
	QueryPerformanceCounter((LARGE_INTEGER *)&gTime);
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
	irr::f32 elapsedTime = ( ( irr::f32 )( gTime - gLastTime )/( irr::f32 )freq );
	gLastTime = gTime;
	if( elapsedTime > 1.0f ) // watch for crazy numbers
		elapsedTime = 0;
	return elapsedTime;

#else

	// get elapsed time per frame (dTime)
	irr::u32 time = GetRealTime();
	irr::s32 dTime = time - lastTime;
	lastTime = time;
	
	return dTime / 1000.0f;
#endif
}

/**
  Displays current frames per second
  */
void GameEngine::DisplayFPS()
{
	static irr::s32 lastFPS = -1;

	irr::s32 fps = driver->getFPS();
	if (lastFPS != fps)
	{
		irr::core::stringw str = L"RxW [";
		str += driver->getName();
		str += "] FPS:";
		str += fps;
		str += " Tri Count:";
		str += driver->getPrimitiveCountDrawn();

		device->setWindowCaption(str.c_str());
		lastFPS = fps;
	}
}

// unbuffered mouse input 
void GameEngine::OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent )
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

void GameEngine::ChangeBGM( const irr::c8* name )
{
	if( gameMusic )
	{
		gameMusic->stop();
		gameMusic->drop();
		gameMusic = NULL;
	}

	if( name )
	{
		// load and play music
		gameMusic = soundEngine->play2D(name, true, false, true);
		gameMusic->setVolume( 0.65f );
	}

}

void GameEngine::PlaySE(const irr::c8* SEFilePath, irr::core::vector3df pos)
{
	if( SEFilePath )
	{
		soundEngine->play3D(SEFilePath, pos);
	}
}
