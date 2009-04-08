#include "CollisionHelper.h"
#include "GameWorld.h"
#include "GameEngine.h"
#include "Monster.h"
#include "TalkativeNPC.hpp"
//#include "Enemy.h"
//#include "EnemyTwo.h"
//#include "EnemyBoss.h"
#include "Camera.h"
#include "Player.h"
#include "MainCharacter.hpp"
#include "Robot.hpp"
#include "SellingMachine.hpp"
#include "TriggerEventItem.hpp"
//#include "SnowballProjectile.h"
//#include "DynamiteProjectile.h"
//#include "LandMine.h"
#include "InputEventReceiver.hpp"
//#include "DynamitePickup.h"
//#include "SnowplowPickup.h"
//#include "DynamiteExplosionEffect.h"
//#include "SnowballExplosionEffect.h"
//#include "EnemyDeathEffect.h"
#include "GameHUD.h"
#include "NodeID.h"
//#include "EnemyWave.h"
#include <cmath>  // for tan(x) function
#include "ParticleSystemEngine.h"


static const irr::c8* LEVEL_FILE = "media/model/scene1.irr";
static const irr::core::vector3df DIRECTIONAL_LIGHT_ROTATION = irr::core::vector3df(90.0f,0.0f,0.f);

static const irr::u32 MAX_SNOWBALLS = 20;
static const irr::u32 MAX_DYNAMITE = 20;
static const irr::u32 MAX_LANDMINES = 0;
static const irr::u32 MAX_SNOWBALL_EXPLOSION_EFFECTS = 20;
static const irr::u32 MAX_DYNAMITE_EXPLOSION_EFFECTS = 20;
static const irr::u32 MAX_ENEMY_DEATH_EFFECTS = 20;
static const irr::f32 PLAYER_DEATH_STATE_TIMER = 3.0f;
static const irr::f32 START_LEVEL_STATE_TIMER = 3.0f;
static const irr::f32 GAME_OVER_STATE_TIMER = 5.0f;
static const irr::f32 FENCE_FALL_TIME = 3.f;

extern GameEngine* GEngine;

GameWorld::GameWorld( const GameEngine& Engine ):
	smgr(Engine.GetSceneManager()),
	mainCharacter(NULL),
	robot(NULL),
	bUseOnFootPlayer(true),
	bSwitchPlayers(false),
	camera(NULL),
	levelTriangleSelector(NULL),
	gameHUD(NULL),
	interactingActor(NULL),
	lastEnemySpawn(0),
	totalEnemyOne(0),
	totalEnemyTwo(0),
	totalEnemyBoss(0),
	curEnemyWave(NULL),
	gameMessage(NULL),
	gameOverImg(NULL),
	waveTimer(0),
	spawnsDone(false),
	curLevel(0),
	FenceToFall(NULL),
	FenceFallTime(0.f),
	paused(false)
{
}

void GameWorld::Init()
{
	InitLevel();
	InitLight();
	InitPlayer();
	InitRobot();
	InitCamera();
	InitEnemies();
	InitHUD();
	InitWeapons();
	InitEffects();
	InitPickups();
	InitMusic();

	InitShader();
}

void GameWorld::InitShader()
{
	//mainCharacter->InitShader( & (light->getAbsolutePosition()) );
	
	ParticleSystemEngine* fire = new ParticleSystemEngine(&smgr, core::vector3df(-100,0,0), core::vector3df(2,2,2),
													   core::aabbox3d<f32>(-7,0,-7,7,1,7), core::vector3df(0.0f,0.06f,0.0f),
													   80,100,800,2000, GEngine->GetDriver().getTexture("media/shader/fire.bmp"));
	
	ParticleSystemEngine* fire2 = new ParticleSystemEngine(&smgr, core::vector3df(0,20,-100), core::vector3df(2,2,2),
													   core::aabbox3d<f32>(-7,0,-7,7,1,7), core::vector3df(0.0f,0.06f,0.0f),
													   80,100,800,2000, GEngine->GetDriver().getTexture("media/shader/fire.bmp"));
	
	
}

// loads us the level and sets up the triangle selector used for collision checks with the level
void GameWorld::InitLevel()
{
	// load the scene
	smgr.loadScene( LEVEL_FILE );

	// setup levelTriangleSelector, used for collision detection with the level
	levelTriangleSelector = smgr.createMetaTriangleSelector();

	// add triangle selectors for every mesh node in the level
	irr::core::array<irr::scene::ISceneNode*> outNodes;
	smgr.getSceneNodesFromType( irr::scene::ESNT_MESH, outNodes );
	for( irr::u32 i = 0; i < outNodes.size(); ++i )
	{
		//irr::scene::IMeshSceneNode* meshNode = dynamic_cast<irr::scene::IMeshSceneNode*>(outNodes[i]);
		irr::scene::IMeshSceneNode* meshNode = (irr::scene::IMeshSceneNode*)(outNodes[i]);
		
		// some mesh nodes in the level don't have meshes assigned to them, display a warning when this occurs
		if( meshNode->getMesh() )
		{
			if (meshNode->getID() == NODE_ID_TRI_NEEDED)
			{
				irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( meshNode->getMesh(), meshNode );
				check(meshTriangleSelector);
				meshNode->setTriangleSelector( meshTriangleSelector );
				levelTriangleSelector->addTriangleSelector( meshTriangleSelector );
				meshTriangleSelector->drop();
				meshTriangleSelector = NULL;

				blocks.push_back( meshNode );
				//meshNode->setDebugDataVisible( irr::scene::EDS_BBOX);
			}
		}
	}
	outNodes.clear();

	SellingMachine* sellingMachine1 = new SellingMachine( *this, irr::core::vector3df(0, 30, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10) );
	actors.push_back( sellingMachine1 );

	TriggerEventItem* TriggerEventItem1 = new TriggerEventItem( *this, irr::core::vector3df(200, 30, -30), irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10) );
	actors.push_back( TriggerEventItem1 );

	smgr.getRootSceneNode()->setTriangleSelector( levelTriangleSelector );

	// lock cursor
	//GEngine->LockCursor();

	// set game state
	stateTimer = 0;
	gameState = state_START_LEVEL;

	SetNumLives( 3 );
}

// restarts the current level
void GameWorld::RestartLevel()
{
	for( irr::s32 i = actors.size()-1; i >= 0; --i )
	{
		// delete camera
		if( actors[i]->GetActorType() == ACTOR_CAMERA )
		{
			Actor::DestroyActor(actors[i]);
			actors.erase( i );
		}
		// delete player
		else if( actors[i]->GetActorType() == ACTOR_PLAYER )
		{
			Actor::DestroyActor(actors[i]);
			actors.erase( i );
			//playerOnFoot = NULL;
		}
		// delete player on snowplow
		else if( actors[i]->GetActorType() == ACTOR_ROBOT )
		{
			Actor::DestroyActor(actors[i]);
			actors.erase( i );
			//playerOnSnowplow = NULL;
		}
		// delete enemies
		else if( actors[i]->GetActorType() == ACTOR_ENEMY)
		{
			totalEnemyOne--;
			Actor::DestroyActor(actors[i]);
			actors.erase( i );
		}
		// delete enemy two
		else if( actors[i]->GetActorType() == ACTOR_ENEMY_TWO)
		{
			totalEnemyTwo--;
			Actor::DestroyActor(actors[i]);
			actors.erase( i );
		}
		// delete enemy boss
		else if( actors[i]->GetActorType() == ACTOR_ENEMY_BOSS)
		{
			totalEnemyBoss--;
			Actor::DestroyActor(actors[i]);
			actors.erase( i );
		}
		// else just remove it
		else
		{
			Actor::DestroyActor(actors[i]);
			actors.erase( i );
		}
	}

	waveTimer = 0;
	spawnsDone = false;
	lastEnemySpawn = 0;
	spawnTimer = 6;

	// re-initialize
	InitPlayer();
	InitCamera();

	// if the player just died, don't restart all the waves
	if( gameState != state_RESTART_LEVEL )
		InitEnemies();
	else;
	// enemyWaves[ curEnemyWave ]->ResetSpawnCounter();

	InitWeapons();
	InitEffects();
	InitPickups();
}

// initializes level sounds
void GameWorld::InitMusic()
{
	/* 
	// load and play music
	GEngine->ChangeMusic();

	// play wind sound effect
	ISound *music = GEngine->GetSoundEngine().play2D("../audio/sfx/wind1.wav", true, false, true);
	music->setVolume( 1.5f );
	music->drop();

	// play barking sound effect
	music = GEngine->GetSoundEngine().play2D("../audio/sfx/barkingdog.mp3", true, false, true);
	music->setVolume( 1.5f );
	music->drop();
	*/
}


// sets up the light in the world
void GameWorld::InitLight()
{
	// Setup the directional light information
	irr::video::SLight lightInfo;
	lightInfo.CastShadows = false;
	lightInfo.Type = irr::video::ELT_DIRECTIONAL;
	lightInfo.DiffuseColor = irr::video::SColorf(0.5f,0.5f,0.5f);

	// Add a single directional light in the level
	light = smgr.addLightSceneNode();
	check(light);
	light->setLightData( lightInfo );
	light->setRotation( DIRECTIONAL_LIGHT_ROTATION );
}

// sets up the player model and player collisions with the world
void GameWorld::InitPlayer()
{
	mainCharacter = new MainCharacter( *this, GEngine->GetDriver() );
	actors.push_back( mainCharacter );
	mainCharacter->SetRotation(irr::core::vector3df(0, 0, 0));
	
	irr::core::array<irr::c8*> npc1dialogs;
	npc1dialogs.push_back("Testing line 1");
	npc1dialogs.push_back("My testing 2");
	npc1dialogs.push_back("Ha ha ha ~");
	TalkativeNPC* npc1 = new TalkativeNPC( *this, npc1dialogs, "media/model/slime08.x", 20.0, irr::core::vector3df(30, 10, 90), irr::core::vector3df(0, 60, 0), irr::core::vector3df(1, 1, 1));
	npc1->GetNode().setDebugDataVisible(irr::scene::EDS_BBOX);
	
	actors.push_back(npc1);
}

void GameWorld::InitRobot()
{
	robot = new Robot( *this, GEngine->GetDriver() );
	actors.push_back( robot );
}

// sets up the enemies in the world
void GameWorld::InitEnemies()
{

	Monster* m1 = new Monster( *this, GEngine->GetDriver());
	actors.push_back(m1);
	m1->ReSetPosition(irr::core::vector3df(-40,0,180));
	
	
	Monster* m2 = new Monster( *this, GEngine->GetDriver());
	actors.push_back(m2);
	m2->ReSetPosition(irr::core::vector3df(50,0,200));
	/*
	irr::scene::IParticleSystemSceneNode* ps =0;
	ps = smgr.addParticleSystemSceneNode(false);
	ps->setPosition(core::vector3df(-100,0,0));
	ps->setScale(core::vector3df(2,2,2));
	ps->setParticleSize(core::dimension2d<f32>(20.0f, 20.0f));
	
	irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
		core::aabbox3d<f32>(-7,0,-7,7,1,7),
		core::vector3df(0.0f,0.06f,0.0f),
		80,100,
		video::SColor(0,255,255,255), video::SColor(0,255,255,255),
		800,2000);
	ps->setEmitter(em);
	em->drop();
	
	scene::IParticleAffector* paf =
	ps->createFadeOutParticleAffector();
	
	ps->addAffector(paf);
	paf->drop();
	
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0,GEngine->GetDriver().getTexture("media/shader/fire.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	*/
	
	
	
}

// sets up the camera to be able to look at the scene
void GameWorld::InitCamera()
{
	camera = new Camera( *this, GEngine->GetDriver(), *levelTriangleSelector, GetCurrentPlayer() );
	// add the camera to the actor's list so it gets ticked
	actors.push_back( camera );
}

// sets up the different weapon actors used by the game
void GameWorld::InitWeapons()
{
	/* for( int i=0; i < MAX_SNOWBALLS; ++i )
	   {
	   SnowballProjectile* projectile = new SnowballProjectile( *this, GEngine->GetDriver() );
	   actors.push_back( projectile );
	   }

	   for( int i=0; i < MAX_DYNAMITE; ++i )
	   {
	   DynamiteProjectile* projectile = new DynamiteProjectile( *this, GEngine->GetDriver() );
	   actors.push_back( projectile );
	   }

	   for( int i=0; i < MAX_LANDMINES; ++i )
	   {
	   LandMine* mine = new LandMine( *this, GEngine->GetDriver(), *levelTriangleSelector );
	   actors.push_back( mine );
	   }
	   */
}

void GameWorld::InitEffects()
{
	/*
	   for( int i=0; i < MAX_SNOWBALL_EXPLOSION_EFFECTS; ++i )
	   {
	   SnowballExplosionEffect* effect = new SnowballExplosionEffect( *this, GEngine->GetParticleManager() );
	   actors.push_back( effect );
	   }

	   for( int i=0; i < MAX_DYNAMITE_EXPLOSION_EFFECTS; ++i )
	   {
	   DynamiteExplosionEffect* effect = new DynamiteExplosionEffect( *this, GEngine->GetParticleManager() );
	   actors.push_back( effect );
	   }

	   for( int i=0; i < MAX_ENEMY_DEATH_EFFECTS; ++i )
	   {
	   EnemyDeathEffect* effect = new EnemyDeathEffect( *this, GEngine->GetParticleManager() );
	   actors.push_back( effect );
	   }
	   */
}

// sets up the weapon/ammo pickup objects used by the game
void GameWorld::InitPickups()
{
	// init the pickups by finding all the pickupspawner nodes in the level
	irr::core::array<irr::scene::ISceneNode*> nodes;
	smgr.getSceneNodesFromType(irr::scene::ESNT_EMPTY, nodes, smgr.getRootSceneNode());

	for( irr::u32 i = 0; i < nodes.size(); ++i )
	{
		/*
		   if( nodes[i]->getID() == NODE_ID_DYNAMITEPICKUP )
		   {
		   irr::core::vector3df pos = nodes[i]->getAbsolutePosition();
		   DynamitePickup* pickup = new DynamitePickup( *this, pos, GEngine->GetDriver() );
		   actors.push_back(pickup);
		   }
		   else if( nodes[i]->getID() == NODE_ID_SNOWPLOWPICKUP )
		   {
		   irr::core::vector3df pos = nodes[i]->getAbsolutePosition();
		   SnowplowPickup* pickup = new SnowplowPickup( *this, pos, GEngine->GetDriver() );
		   actors.push_back(pickup);
		   }
		   */
	}

}

void GameWorld::InitHUD()
{
	gameHUD = new GameHUD( GEngine->GetDevice() );
	gameHUD->Init();
}

// cleans up the game world
void GameWorld::Exit()
{
	// clean up spawn nodes
	spawnNodes.clear();

	// clean up all the actors
	for( irr::u32 i=0; i < actors.size(); ++i )
	{
		Actor::DestroyActor(actors[i]);
	}
	actors.clear();

	mainCharacter = NULL;
	camera = NULL;

	// clean up the triangle selector
	if( levelTriangleSelector )
	{
		levelTriangleSelector->drop();
		levelTriangleSelector = NULL;
	}

	// stop and clean up background audio
	// GEngine->GetSoundEngine().removeAllSoundSources();

	// clean up the HUD
	gameHUD->Exit();
	delete gameHUD;
	gameHUD = NULL;

	// clear scene
	smgr.clear();

	// clear out the global weather effect because it got deleted by smgr.clear call
	GEngine->GlobalWeatherEffect = NULL;
	GEngine->InitGlobalWeatherEffect();
}

void GameWorld::UpdateHUD( irr::f32 delta ){
	switch( gameState ){
		case state_GAMEPLAY:
		case state_INTERACTING:
			{
				DoHUD(delta);
			}break;
		case state_PAUSED:
		default:
			break;
	}
}

void GameWorld::requireInteracting(bool on, InteractiveActor* currentInteractingActor = NULL)
{
	if(on && currentInteractingActor != NULL)
	{
		gameState = state_INTERACTING;
		interactingActor = currentInteractingActor;
	}
	else
	{
		gameState = state_GAMEPLAY;
		interactingActor = NULL;
	}
}

// called every frame with the frame's elapsed time
void GameWorld::Tick( irr::f32 delta )
{
	switch( gameState )
	{
		case state_GAMEPLAY:
		case state_INTERACTING:
		case state_PAUSED:
			{
				DoGameplay( delta );
			}break;
		case state_PLAYER_DEAD:
			{
				stateTimer += delta;
				if( stateTimer >= PLAYER_DEATH_STATE_TIMER )
				{
					stateTimer = 0;
					gameState = state_RESTART_LEVEL;
				}
			}break;
		case state_GAME_OVER:
			{
				if( gameMessage == NULL )
				{
					irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();

					irr::gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
					check(env);
					gameOverImg = env->addImage(irr::core::rect<int>(0,0,scrSize.Width,scrSize.Height));
					gameOverImg->setImage( GEngine->GetDriver().getTexture("../art/UI/GameOver/gameover.jpg") );
					gameOverImg->draw();

					// GEngine->GetSoundEngine().play2D("../audio/sfx/gameover.mp3");

					irr::scene::ISceneNode* rootNode = smgr.getRootSceneNode();


					scrSize.Width /= 2;
					scrSize.Height /= 2;

					gameMessage = GEngine->GetDevice().getGUIEnvironment()->addStaticText( L"GAME OVER",
							irr::core::rect<irr::s32>(scrSize.Width-64, scrSize.Height-32, scrSize.Width+128, scrSize.Height+48) );
					check(gameMessage);
					gameMessage->setOverrideColor( irr::video::SColor(255, 255, 255, 255) );
					gameMessage->setOverrideFont( GEngine->GetDevice().getGUIEnvironment()->getFont( "../art/fonts/comicsans.png" ) );
				}
				else if( stateTimer < GAME_OVER_STATE_TIMER )
				{
					stateTimer += delta;
				}
				else
				{
					check(gameMessage);
					gameMessage->remove();
					gameMessage = NULL;

					gameOverImg->remove();
					gameOverImg = 0;

					stateTimer = 0;
					GEngine->RequestStateChange( state_FRONTEND );
				}
			}break;
		case state_WAVE_FINISHED:
			{
				if( gameMessage == NULL )
				{
					camera->Tick(delta);

					irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
					scrSize.Width /= 2;
					scrSize.Height /= 2;

					irr::core::stringw waveString;
					waveString += curEnemyWave+1;
					waveString += "/";
					// waveString += enemyWaves.size();
					waveString += " WAVES COMPLETED!";
					gameMessage = GEngine->GetDevice().getGUIEnvironment()->addStaticText( waveString.c_str(),
							irr::core::rect<irr::s32>(scrSize.Width-128, scrSize.Height-128, scrSize.Width+256, scrSize.Height+48) );
					check(gameMessage);
					gameMessage->setOverrideColor( irr::video::SColor(255, 255, 255, 255) );
					gameMessage->setOverrideFont( GEngine->GetDevice().getGUIEnvironment()->getFont( "../art/fonts/comicsans.png" ) );
				}

				DoGameplay( delta );
			}break;
		case state_RESTART_LEVEL:
			{
				// check for game over
				if( GetNumLives() < 0 )
				{
					gameState = state_GAME_OVER;
					stateTimer = 0;
					return;
				}

				if( gameMessage == NULL )
				{
					irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
					scrSize.Width /= 2;
					scrSize.Height /= 2;

					gameMessage = GEngine->GetDevice().getGUIEnvironment()->addStaticText( L"Get Ready",
							irr::core::rect<irr::s32>(scrSize.Width-64, scrSize.Height-32, scrSize.Width+128, scrSize.Height+48) );
					check(gameMessage);
					gameMessage->setOverrideColor( irr::video::SColor(255, 255, 255, 255) );
					gameMessage->setOverrideFont( GEngine->GetDevice().getGUIEnvironment()->getFont( "../art/fonts/comicsans.png" ) );
					RestartLevel();
					camera->SetPosition( GetCurrentPlayer().GetNodePosition() - GetCurrentPlayer().GetAimVector() * -5.0f );
					camera->Tick(delta);
				}
				else if( stateTimer < START_LEVEL_STATE_TIMER )
				{
					stateTimer += delta;
				}
				else
				{
					check(gameMessage);
					gameMessage->remove();
					gameMessage = NULL;

					// make the player visible
					GetCurrentPlayer().GetNode().setVisible(true);

					stateTimer = 0;
					gameState = state_GAMEPLAY;
				}

			}break;
		case state_START_LEVEL:
			{
				if( gameMessage == NULL )
				{
					camera->Tick(delta);

					irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
					scrSize.Width /= 2;
					scrSize.Height /= 2;

					gameMessage = GEngine->GetDevice().getGUIEnvironment()->addStaticText( L"It Begins...",
							irr::core::rect<irr::s32>(scrSize.Width-64, scrSize.Height-32, scrSize.Width+128, scrSize.Height+48) );
					gameMessage->setOverrideColor( irr::video::SColor(255, 255, 255, 255) );
					gameMessage->setOverrideFont( GEngine->GetDevice().getGUIEnvironment()->getFont( "../art/fonts/comicsans.png" ) );
				}
				/*else if( stateTimer < START_LEVEL_STATE_TIMER )
				{
					stateTimer += delta;
				}*/
				else
				{
					gameMessage->remove();
					gameMessage = NULL;

					stateTimer = 0;
					// make the player visible
					GetCurrentPlayer().GetNode().setVisible(true);
					gameState = state_GAMEPLAY;
				}

			}break;
		case state_GAME_VICTORY:
			{
				if( gameMessage == NULL )
				{
					irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();

					irr::gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
					check(env);
					gameOverImg = env->addImage(irr::core::rect<int>(0,0,scrSize.Width,scrSize.Height));
					gameOverImg->setImage( GEngine->GetDriver().getTexture("../art/UI/GameOver/gameover.jpg") );
					gameOverImg->draw();


					irr::scene::ISceneNode* rootNode = smgr.getRootSceneNode();
					GetCurrentPlayer().PlayRandomCheer();
					// GEngine->ChangeMusic( "../audio/music/plowmusic.mp3" );

					scrSize.Width /= 2;
					scrSize.Height /= 2;

					irr::core::stringw msgString;
					msgString += "                      YOU WIN!\n";
					msgString += "\n\nCREDITS:\n\n";


					gameMessage = GEngine->GetDevice().getGUIEnvironment()->addStaticText( msgString.c_str(),
							irr::core::rect<irr::s32>(scrSize.Width-256, scrSize.Height-128, scrSize.Width+256, scrSize.Height+128) );
					check(gameMessage);
					gameMessage->setOverrideColor( irr::video::SColor(255, 255, 255, 255) );
					gameMessage->setOverrideFont( GEngine->GetDevice().getGUIEnvironment()->getFont( "../art/fonts/comicsans.png" ) );
				}
				else if( stateTimer < 13 )
				{
					stateTimer += delta;
				}
				else
				{
					check(gameMessage);
					gameMessage->remove();
					gameMessage = NULL;

					gameOverImg->remove();
					gameOverImg = 0;

					stateTimer = 0;
					GEngine->RequestStateChange( state_FRONTEND );
				}
			}break;
		default:
			{
				// shouldn't be here
				check( false );
			}
	}
}

// performs actual gameplay
void GameWorld::DoGameplay( irr::f32 delta )
{
	if(gameState != state_PAUSED)
	{
		// check for early exit
		if( gameState == state_RESTART_LEVEL )
			return;

		// perform an input update
		DoInput();

		if(gameState != state_INTERACTING)
		{
			// tick all actors
			for( irr::u32 i=0; i < actors.size(); ++i )
				actors[i]->Tick( delta );
		}
		else
		{
			for( irr::u32 i=0; i < actors.size(); ++i )
				if(actors[i]->GetActorType() & ACTOR_INTERACTIVE)
					actors[i]->Tick( delta );
		}

		// update 3d audio information
		DoAudio(); 

		// deletes all the dead actors
		DoCleanup();
	}
	else
	{
		DoInput();
	}
}

// perform an tick of the input system
void GameWorld::DoInput()
{
	// handle user input for player
	InputEventReceiver& receiver = GEngine->GetReceiver();

	if(receiver.keyReleased(irr::KEY_ESCAPE))
	{
		if( gameState == state_PAUSED )
		{
			gameState = gameStateBeforePause;
		}
		else
		{
			gameStateBeforePause = gameState;
			gameState = state_PAUSED;
		}
	}

	if( gameState == state_PAUSED || gameState == state_INTERACTING)
		return;
	
	if(receiver.keyDown(irr::KEY_KEY_M))
	{
		((MainCharacter&)GetCurrentPlayer()).setDefending( true );
		return;
	}
	else
	{
		((MainCharacter&)GetCurrentPlayer()).setDefending( false );
	}

	if(receiver.keyReleased(irr::KEY_SPACE) || receiver.mousePressed(InputEventReceiver::LEFT))
	{
		((MainCharacter&)GetCurrentPlayer()).setAttacking( true );
		return;
	}
	else
	{
		((MainCharacter&)GetCurrentPlayer()).setAttacking( false );
	}

	irr::core::vector3df playerTranslation(0, 0, 0);
	irr::core::vector3df playerRotation(0, 0, 0);

	if(receiver.keyDown(irr::KEY_KEY_W))
	{ 
		playerTranslation.Z = -20;
	}
	else if(receiver.keyDown(irr::KEY_KEY_S))
	{
		playerTranslation.Z = 20;
	}
	if(receiver.keyDown(irr::KEY_KEY_A))
	{
		playerRotation.Y = 3;
	}
	else if(receiver.keyDown(irr::KEY_KEY_D))
	{
		playerRotation.Y = -3;
	}
	
	if(receiver.keyDown(irr::KEY_SHIFT))
	{
		playerTranslation *= 2;
		((MainCharacter&)GetCurrentPlayer()).setRunning( true );
	}
	else
	{
		((MainCharacter&)GetCurrentPlayer()).setRunning( false );
	}

	GetCurrentPlayer().SetRotation( playerRotation );
	GetCurrentPlayer().SetTranslation( playerTranslation );

	/*if(receiver.keyPressed(irr::KEY_RETURN) || receiver.mousePressed(InputEventReceiver::LEFT))
	{
		for( irr::u32 i=0; i < actors.size(); ++i )
		{
			if( actors[i]->GetActorType() != ACTOR_ENEMY)
				continue;
			
			if(
				CollisionHelper::CheckProximity2D(
					mainCharacter->GetNodePosition(),
					actors[i]->GetNode().getPosition(),
					25.0f
				)
			)
				actors[i]->ReceiveDamage(10);
		}
	}*/
}

// perform a physics update, includes collision detection
void GameWorld::DoPhysics()
{
	// check collisions between the actors
	CheckCollisions();
}

void GameWorld::AdvanceLevel()
{
	//BringDownDividerFence();

	// if we go past level 2, do game ending state
	if( ++curLevel >= 2 )
	{
		gameState = state_GAME_VICTORY;
		stateTimer = 0;
		return;
	}

	// load in new enemy waves
	InitEnemies();
}

void GameWorld::DoAI( irr::f32 delta )
{
	// check player death
	if( GetCurrentPlayer().IsDead() )
	{
		SetNumLives( GetNumLives() - 1 );
		gameState = state_PLAYER_DEAD;
		stateTimer = 0;
		return;
	}


	// all spawns of the wave were pushed out, see if the player killed off all enemies
	if( spawnsDone )
	{
		if( (totalEnemyOne + totalEnemyTwo + totalEnemyBoss) == 0 )
		{
			gameState = state_WAVE_FINISHED;
			waveTimer = 0;
			GetCurrentPlayer().SetHealth( 100.0f );
			spawnsDone = false;
			GetCurrentPlayer().PlayRandomCheer();
			return;
		}
	}
	// advance to next wave?
	else if( gameState == state_WAVE_FINISHED )
	{
		waveTimer += delta;
		// if( waveTimer >= enemyWaves[curEnemyWave]->GetTimeTillNextWave() )
		{
			// time to start the next wave
			++curEnemyWave;
			check(gameMessage);
			gameMessage->remove();
			gameMessage = NULL;
			gameState = state_GAMEPLAY;
			return;
		}
	}
	else
	{
		// check to see if all waves are completed, then open door to next level...
		/* if( (irr::u32)(curEnemyWave) >= enemyWaves.size() )
		   {
		   lastEnemySpawn = 0;
		   waveTimer = 0;
		   spawnsDone = false;
		   AdvanceLevel();
		   return;
		   }
		   */
		// at this point, spawns still need to be pushed out...
		// spawn enemy waves at the player
		lastEnemySpawn += delta;
		if( lastEnemySpawn >= spawnTimer )
		{
			/*EnemyWave::Spawn& spawn = enemyWaves[curEnemyWave]->GetSpawn();
			  spawnTimer = (irr::f32)spawn.duration;
			  lastEnemySpawn = 0;

			  static irr::s32 spawner = 0;

			  switch( spawn.type )
			  {
			  case ACTOR_ENEMY:
			  for( int i=0; i<spawn.amount; i++ )
			  {
			  irr::core::vector3df pos = spawnNodes[ spawner ]->getAbsolutePosition();
			  if( (irr::u32)++spawner >= spawnNodes.size() )
			  spawner = 0;

			  Enemy *enemy = new Enemy( *this, pos, *levelTriangleSelector );
			  actors.push_back(enemy);
			  totalEnemyOne++;
			  enemy->SetAimTarget( GetCurrentPlayer() );

			// play spawn sound
			ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/spawn.mp3", spawnNodes[spawner]->getAbsolutePosition(), false, false, true );
			sound->setMinDistance( 40.0f );
			sound->drop();
			}
			break;

			case ACTOR_ENEMY_TWO:
			for( int i=0; i<spawn.amount; i++ )
			{
			irr::core::vector3df pos = spawnNodes[ spawner ]->getAbsolutePosition();
			if( (irr::u32)++spawner >= spawnNodes.size() )
			spawner = 0;

			EnemyTwo *enemy = new EnemyTwo( *this, pos, *levelTriangleSelector );
			actors.push_back(enemy);
			totalEnemyTwo++;
			enemy->SetAimTarget( GetCurrentPlayer() );

			// play spawn sound
			ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/spawn.mp3", spawnNodes[spawner]->getAbsolutePosition(), false, false, true );
			sound->setMinDistance( 40.0f );
			sound->drop();
			}
			break;

			case ACTOR_ENEMY_BOSS:
			for( int i=0; i<spawn.amount; i++ )
			{
			irr::core::vector3df pos = spawnNodes[ spawner ]->getAbsolutePosition();
			if( (irr::u32)++spawner >= spawnNodes.size() )
			spawner = 0;

			EnemyBoss *enemy = new EnemyBoss( *this, pos, *levelTriangleSelector );
			actors.push_back(enemy);
			totalEnemyBoss++;
			enemy->SetAimTarget( GetCurrentPlayer() );

			// play spawn sound
			ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/spawn.mp3", spawnNodes[spawner]->getAbsolutePosition(), false, false, true );
			sound->setMinDistance( 40.0f );
			sound->drop();
			}
			break;

			default:
			check(false);
			break;
			}

			// wave finished ?
			if( enemyWaves[curEnemyWave]->AdvanceSpawn() == false )
			{
				spawnsDone = true;
				return;
			}
			*/
		}
	}

	// inform enemies of new player location
	/*
	for( irr::u32 i=0; i < actors.size(); ++i )
	{
		if( actors[i]->GetActorType() == ACTOR_ENEMY )
		{
			Enemy* enemy = (Enemy *)actors[i];
			enemy->SetAimTarget( GetCurrentPlayer() );
		}
		/* else if( actors[i]->GetActorType() == ACTOR_ENEMY_TWO )
		   {
		   EnemyTwo* enemy = (EnemyTwo *)actors[i];
		   enemy->SetAimTarget( GetCurrentPlayer() );
		   }
		   else if( actors[i]->GetActorType() == ACTOR_ENEMY_BOSS )
		   {
		   EnemyBoss* enemy = (EnemyBoss *)actors[i];
		   enemy->SetAimTarget( GetCurrentPlayer() );
		   }
	}
	*/
}

// perform collision checks between the actors
void GameWorld::CheckCollisions()
{
	// setup a helper structure with information requried for actors to do collision checks
	CollisionInfo collisionInfo(*levelTriangleSelector, actors);

	for( irr::u32 i=0; i < actors.size(); ++i )
	{
		if( actors[i]->ShouldPerformCollisionCheck() )
		{
			actors[i]->DoCollisions( collisionInfo );
		}
	}
}

// deletes all the dead actors
void GameWorld::DoCleanup()
{
	// delete all the dead actors
	if( actors.size() > 0 )
	{
		for( irr::s32 i = actors.size()-1; i >= 0; --i )
		{
			if( actors[i]->GetActorState() == state_ACTOR_DEAD )
			{
				if( actors[i]->GetActorType() == ACTOR_ENEMY )
					totalEnemyOne--;
				else if( actors[i]->GetActorType() == ACTOR_ENEMY_TWO )
					totalEnemyTwo--;
				else if( actors[i]->GetActorType() == ACTOR_ENEMY_BOSS )
					totalEnemyBoss--;

				Actor::DestroyActor(actors[i]);
				actors.erase( i );
			}
		}
	}
}

// updates and plays 3d audio effects
void GameWorld::DoAudio()
{
	// update 3d position of player
	// GEngine->GetSoundEngine().setListenerPosition(GetCurrentPlayer().GetNodePosition(), GetCurrentPlayer().GetAimVector());

}


// draws the HUD, called after the 3d scene has been rendered
void GameWorld::DoHUD(irr::f32 delta)
{
	// Player& p = GetCurrentPlayer();
	// gameHUD->Update( p.GetAmmo(), p.GetScore(), numLives, curEnemyWave+1, enemyWaves.size(), GetCurrentPlayer().GetHealth(), GetCurrentPlayer().HasGodMode() );
	gameHUD->Update(delta, GetCurrentPlayer());
	/* Do the pause here! */
}


void GameWorld::DoConversation(irr::c8 conversation_string){
	
	gameHUD->DisplayConversation(conversation_string);
}


// return the first available dynamite projectile for throwing, NULL if none are available
/*
   DynamiteProjectile* GameWorld::GetFirstAvailableDynamite() const
   {
   for( irr::u32 i=0; i < actors.size(); ++i )
   {
   if( actors[i]->GetActorType() == ACTOR_DYNAMITE )
   {
// a projectile is available if its state is IDLE
DynamiteProjectile* projectile = dynamic_cast<DynamiteProjectile*>(actors[i]);
check(projectile);
if( projectile->GetDynamiteState() == state_DYNAMITE_IDLE )
{
return projectile;
}
}

}

return NULL;
}

// return the first available snowball projectile for throwing, NULL if none are available

SnowballProjectile* GameWorld::GetFirstAvailableSnowball() const
{
for( irr::u32 i=0; i < actors.size(); ++i )
{
if( actors[i]->GetActorType() == ACTOR_SNOWBALL )
{
// a projectile is available if its state is IDLE
SnowballProjectile* projectile = dynamic_cast<SnowballProjectile*>(actors[i]);
check(projectile);
if( projectile->GetSnowballState() == state_SNOWBALL_IDLE )
{
return projectile;
}
}
}

return NULL;
}


// return the first available landmine for arming, NULL if none are available

LandMine* GameWorld::GetFirstAvailableLandMine() const
{
for( irr::u32 i=0; i < actors.size(); ++i )
{
if( actors[i]->GetActorType() == ACTOR_LANDMINE )
{
// a projectile is available if its state is IDLE
LandMine* mine = dynamic_cast<LandMine*>(actors[i]);
check(mine);
if( mine->GetLandMineState() == state_LANDMINE_IDLE )
{
return mine;
}
}
}

return NULL;
}


// return the first available explosion effect, NULL if none are available

ExplosionEffect* GameWorld::GetFirstAvailableSnowballExplosionEffect() const
{
for( irr::u32 i=0; i < actors.size(); ++i )
{
if( actors[i]->GetActorType() == ACTOR_EXPLOSION_EFFECT_SNOWBALL )
{
	// a projectile is available if its state is IDLE
	ExplosionEffect* effect = dynamic_cast<ExplosionEffect*>(actors[i]);
	check(effect);
	if( effect->GetExplosionState() == state_EXPLOSION_IDLE )
	{
		return effect;
	}
}
}

return NULL;
}


// return the first available explosion effect, NULL if none are available

ExplosionEffect* GameWorld::GetFirstAvailableDynamiteExplosionEffect() const
{
	for( irr::u32 i=0; i < actors.size(); ++i )
	{
		if( actors[i]->GetActorType() == ACTOR_EXPLOSION_EFFECT_DYNAMITE )
		{
			// a projectile is available if its state is IDLE
			ExplosionEffect* effect = dynamic_cast<ExplosionEffect*>(actors[i]);
			check(effect);
			if( effect->GetExplosionState() == state_EXPLOSION_IDLE )
			{
				return effect;
			}
		}
	}

	return NULL;
}

// return the first available enemy death effect, NULL if none are available
ExplosionEffect* GameWorld::GetFirstAvailableEnemyDeathEffect() const
{
	for( irr::u32 i=0; i < actors.size(); ++i )
	{
		if( actors[i]->GetActorType() == ACTOR_EXPLOSION_EFFECT_ENEMYDEATH )
		{
			// a projectile is available if its state is IDLE
			ExplosionEffect* effect = dynamic_cast<ExplosionEffect*>(actors[i]);
			check(effect);
			if( effect->GetExplosionState() == state_EXPLOSION_IDLE )
			{
				return effect;
			}
		}
	}

	return NULL;
}
*/

// returns the player actor which is currently used
Player& GameWorld::GetCurrentPlayer() const
{
	return *mainCharacter;
}

// switches the player models from onFoot to onSnowplow, and notifies all the necessary actors about the change
void GameWorld::SwitchPlayers( )
{ 
	// transfer the position, rotation and ammo information from old player to the new
	// this is so any pickups picked up will transfer to the other one
	/*Player* oldPlayer = bUseOnFootPlayer ? playerOnFoot : playerOnSnowplow;
	Player* newPlayer = bUseOnFootPlayer ? playerOnSnowplow: playerOnFoot;

	newPlayer->SetNodePosition( oldPlayer->GetNodePosition() );
	newPlayer->CopyStateFrom( *oldPlayer );
	// recreate the collision animator, otherwise it will think that the new player moved a huge amount of distance in one tick 
	// this is causing problems with not positioning the player where he should be 
	newPlayer->RecreateCollisionResponseAnimator();

	newPlayer->SetActive( true );
	oldPlayer->SetActive( false );

	bUseOnFootPlayer = !bUseOnFootPlayer;
	NotifyNewPlayerTarget( GetCurrentPlayer() );*/
}

// notifies all the actors that a new player is to be their target
void GameWorld::NotifyNewPlayerTarget( Player& player ) const
{
	// notify the camera actor about the target change
	camera->SetAimTarget( player );

	// notify the enemies about the target player change
	/*
	for( irr::u32 i=0; i < actors.size(); ++i )
	{
		if( actors[i]->GetActorType() == ACTOR_ENEMY )
		{
			Enemy* enemy = dynamic_cast<Enemy*>(actors[i]);
			enemy->SetAimTarget( player );
		}
		else if( actors[i]->GetActorType() == ACTOR_ENEMY_TWO )
		   {
		   EnemyTwo* enemy2 = dynamic_cast<EnemyTwo*>(actors[i]);
		   enemy2->SetAimTarget( player );
		   }
		   else if( actors[i]->GetActorType() == ACTOR_ENEMY_BOSS )
		   {
		   EnemyBoss* enemyBoss = dynamic_cast<EnemyBoss*>(actors[i]);
		   enemyBoss->SetAimTarget( player );
		   }
	}
	*/
}

// unbuffered mouse input 
void GameWorld::OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent )
{
	if( mainCharacter )
	{
		GetCurrentPlayer().OnMouseEvent( mouseEvent );
	}
}

// kills all enemies that are currently spawned
void GameWorld::KillAllEnemies()
{
	// just do a lot of damage to all the current enemy actors
	for( irr::u32 i=0; i < actors.size(); ++i )
	{
		if( actors[i]->GetActorType() == ACTOR_ENEMY
				||  actors[i]->GetActorType() == ACTOR_ENEMY_TWO
				||  actors[i]->GetActorType() == ACTOR_ENEMY_BOSS )
		{
			actors[i]->ReceiveDamage( 100 );
		}
	}
}

irr::core::vector3df GameWorld::GetPlayerSpawn()
{
	irr::s32 playerSpawnID;

	switch( curLevel )
	{
		case 0:
			playerSpawnID = NODE_ID_PLAYERSPAWN_ONE;
			break;
		case 1:
			playerSpawnID = NODE_ID_PLAYERSPAWN_TWO;
			break;
		default:
			check( false );
			break;
	}

	// find player spawn depending on level
	irr::core::array<irr::scene::ISceneNode*> nodes;
	smgr.getSceneNodesFromType(irr::scene::ESNT_EMPTY, nodes, smgr.getRootSceneNode());
	for( irr::u32 i = 0; i < nodes.size(); ++i )
	{
		if( nodes[i]->getID() == playerSpawnID )
			return nodes[i]->getAbsolutePosition();
	}

	return irr::core::vector3df( 0, 20, 0 );
}
