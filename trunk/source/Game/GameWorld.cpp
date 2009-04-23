#include <cmath>
#include <fstream>
#include <iostream>

#include <boost/thread.hpp>

#include "Camera.hpp"
#include "DebugInfo.hpp"
#include "GameEngine.hpp"
#include "GameHUD.hpp"
#include "GameWorld.hpp"
#include "HPItem.hpp"
#include "InputEventReceiver.hpp"
#include "Item.hpp"
#include "MainCharacter.hpp"
#include "MDiscItem.hpp"
#include "Monster.hpp"
#include "NodeID.hpp"
#include "ParticleManager.hpp"
#include "Player.hpp"
#include "Robot.hpp"
#include "ShaderFactory.hpp"
#include "SellingMachine.hpp"
#include "TalkativeNPC.hpp"
#include "Tokenizer.hpp"
#include "TriggerEventItem.hpp"
#include "Utils.hpp"
#include "WeaponItem.hpp"
#include "XItem.hpp"

static const irr::core::vector3df DIRECTIONAL_LIGHT_ROTATION = irr::core::vector3df(90.0f,0.0f,0.f);

static const irr::f32 PLAYER_DEATH_STATE_TIMER = 3.0f;
static const irr::f32 START_LEVEL_STATE_TIMER = 25.0f;
static const irr::f32 GAME_OVER_STATE_TIMER = 8.0f;
static const irr::f32 GAME_WIN_STATE_TIMER = 60.0f;

GameWorld::GameWorld( GameEngine& gameEngine )
	: GamePart( gameEngine ),
	smgr(gameEngine.GetSceneManager()),
	mainCharacter(NULL),
	robot(NULL),
	camera(NULL),
	levelTriangleSelector(NULL),
	light(NULL),
	gameHUD(NULL),
	interactingActor(NULL),
	gameMessage(NULL),
	gameOverImg(NULL),
	curLevel(0)
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
	InitEffects();
	InitMusic();
	InitItems();
	InitShader();
	InitNPC();
}

void GameWorld::InitItems()
{
	//Init different kind of items
	//Item* hp = new HPItem(*this, HPITEM, "HP Medicine", 50);
	//Item* md = new MDiscItem(*this, MDISCITEM, "Magic Disc", 1);	
	//Item* xItem = new XItem(*this, XITEM, "X Item", 1);
	//Item* weapon = new WeaponItem(*this, WEAPONITEM1, "Sword", 10);
}

void GameWorld::InitShader()
{
	//mainCharacter->InitShader( & (light->getAbsolutePosition()) );
	//0,20,0
	/*ParticleManager* fire = new ParticleManager(&smgr, irr::core::vector3df(38.114258, 40.000000, 194.928589),
		irr::core::vector3df(30,2,2),
		irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7));

	fire->CreateBoxEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
						   50,80,800,1000, GEngine.GetDriver().getTexture("media/shader/smoke.bmp"));
	
	ParticleManager* fire2 = new ParticleManager(&smgr, irr::core::vector3df(38.114258, 20.000000, 194.928589),
		irr::core::vector3df(30,5,2),
													   irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	fire2->CreateBoxEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
							80,100,800,2000, GEngine.GetDriver().getTexture("media/shader/fire.bmp"));
	 
	ParticleManager* fire3 = new ParticleManager(&smgr, irr::core::vector3df(-186.645462, 0.000000, -0.391444),
		irr::core::vector3df(2,2,20),
		irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	fire3->CreateMeshEmitter(smgr.getMesh("media/model/slime08.x"), irr::core::vector3df(0.0f,0.06f,0.0f),
							10,20,800,2000, GEngine.GetDriver().getTexture("media/shader/fire.bmp"));
*/
	
	/*ParticleManager* Snow = new  ParticleManager(&smgr, irr::core::vector3df(0,100,0), irr::core::vector3df(2,2,2),
														   irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	std::cout<<"----\n";
	Snow->CreateCylinderEmitter(irr::core::vector3df(0,50,0), irr::f32(500.0), irr::core::vector3df(0,0,0),
								irr::f32(200.0), irr::core::vector3df(0.0f,-0.03f,0.0f), 400,500,2500,3000, GEngine.GetDriver().getTexture("media/shader/smoke.bmp"));*/

	/*	irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
															core::aabbox3d<irr::f32>(-7,0,-7,7,1,7),
															core::vector3df(0.0f,0.06f,0.0f),
															80,100,
															video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255),
															800,2000);
*/
}

// loads us the level and sets up the triangle selector used for collision checks with the level
void GameWorld::InitLevel()
{
	levelTriangleSelector = smgr.createMetaTriangleSelector();

	LoadSceneConfig(1);
	LoadNPCConfig(1);
	LoadSceneConfig(2);
	LoadMonsterConfig(2);
	//AddScene(NODE_ID_SCENE1);
	//AddScene(NODE_ID_SCENE2);
#ifndef _IRR_WINDOWS_
	//AddScene(NODE_ID_SCENE3);
	//AddScene(NODE_ID_SCENE4);
#endif

	// set game state
	stateTimer = 0;
	gameState = state_START_LEVEL;
}

static float toFloat(const std::string& s)
{
	std::istringstream iss(s);
	float f;
	return (iss >> f).fail() ? 0.0 : f;
}

static int toInt(const std::string& s)
{
	std::istringstream iss(s);
	int i;
	return (iss >> i).fail() ? 0 : i;
}

static std::string sceneNumberString(irr::u32 sceneNum)
{
	if(sceneNum < 10 )
	{
		std::string ret = "000";
		return ret.append( irr::core::stringc(sceneNum).c_str() );
	}
}

void GameWorld::LoadSceneConfig(irr::u32 sceneNum)
{
	std::string sceneConfigFileName = "media/scenes/s" + Utils::toString(sceneNum) + ".rxw";
	std::ifstream sceneConfigFile(sceneConfigFileName.c_str());

	if( sceneConfigFile )
	{
		std::string lines;
		irr::core::stringc sceneIRRFilePath = "";
		irr::core::vector3df pos;
		irr::s32 fallID = -1;
		irr::s32 triID = -1;
		irr::s32 houseID = -1;
		while( !sceneConfigFile.eof() )
		{
			std::getline( sceneConfigFile, lines );

			if( lines != "")
			{
				if( lines == "BEGINSCENE" )
				{
					continue;
				}
				else if( lines == "ENDSCENE" )
				{
					sceneConfigFile.close();
					break;
				}
				else if( lines.substr(0, 3) == "IRR" )
				{
					sceneIRRFilePath = lines.substr(4, lines.length()).c_str();
				}
				else if( lines.substr(0, 3) == "POS" )
				{
					Tokenizer tokenizer( lines.substr(4, lines.length()), "," );

					pos.X = Utils::toFloat(tokenizer.getNextToken());
					pos.Y = Utils::toFloat(tokenizer.getNextToken());
					pos.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if( lines.substr(0, 4) == "FALL" )
				{
					fallID = Utils::toInt( lines.substr(5, lines.length()) );
				}
				else if( lines.substr(0, 3) == "TRI" )
				{
					triID = Utils::toInt( lines.substr(4, lines.length()) );
				}
				else if( lines.substr(0, 5) == "HOUSE" )
				{
					houseID = Utils::toInt( lines.substr(6, lines.length()) );
				}
			}
		}

		LoadScene(sceneIRRFilePath.c_str(), pos, fallID, triID, houseID);
	}
	else
	{
		std::cout << "Error loading scene config file: " << sceneConfigFileName << ", aborting!" << std::endl;
		exit( -1 );
	}
}

void GameWorld::LoadNPCConfig(irr::u32 sceneNum)
{
	std::string NPCConfigFileName = "media/scenes/n" + Utils::toString(sceneNum) + ".rxw";
	std::ifstream NPCConfigFile(NPCConfigFileName.c_str());

	if( NPCConfigFile )
	{
		std::string lines;
		irr::core::stringc modelFilePath = "";
		irr::core::array<irr::core::stringw> dialogs;
		irr::video::ITexture* headerImage;
		irr::u32 acceptable = 20;
		irr::core::vector3df pos;
		irr::core::vector3df rot;
		irr::core::vector3df scale;
		while( !NPCConfigFile.eof() )
		{
			std::getline( NPCConfigFile, lines );

			if( lines != "")
			{
				if( lines == "BEGINNPC" )
				{
					continue;
				}
				else if( lines == "ENDNPC" )
				{
					NPCConfigFile.close();
					break;
				}
				else if( lines.substr(0, 5) == "MODEL" )
				{
					modelFilePath = lines.substr(6, lines.length()).c_str();
				}
				else if( lines.substr(0, 6) == "DIALOG" )
				{
					dialogs.push_back( lines.substr(7, lines.length()).c_str() );
				}
				else if( lines.substr(0, 6) == "HEADER" )
				{
					headerImage = GEngine.GetDriver().getTexture( lines.substr(7, lines.length()).c_str() );
				}
				else if( lines.substr(0, 3) == "POS" )
				{
					Tokenizer tokenizer( lines.substr(4, lines.length()), "," );

					pos.X = Utils::toFloat(tokenizer.getNextToken());
					pos.Y = Utils::toFloat(tokenizer.getNextToken());
					pos.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if( lines.substr(0, 3) == "ROT" )
				{
					Tokenizer tokenizer( lines.substr(4, lines.length()), "," );

					rot.X = Utils::toFloat(tokenizer.getNextToken());
					rot.Y = Utils::toFloat(tokenizer.getNextToken());
					rot.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if( lines.substr(0, 5) == "SCALE" )
				{
					Tokenizer tokenizer( lines.substr(6, lines.length()), "," );

					scale.X = Utils::toFloat(tokenizer.getNextToken());
					scale.Y = Utils::toFloat(tokenizer.getNextToken());
					scale.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if( lines == "ADDNPC" )
				{
					TalkativeNPC* newNPC = new TalkativeNPC(GEngine, *this, modelFilePath.c_str(), dialogs, headerImage, acceptable, pos, rot, scale);
					actors.push_back( newNPC );

					dialogs.clear();
					headerImage = NULL;
					modelFilePath = "";
					acceptable = 20;
					pos = rot = scale = irr::core::vector3df(0, 0, 0);
				}
			}
		}
	}
	else
	{
		std::cout << "Error loading NPC config file: " << NPCConfigFileName << ", aborting!" << std::endl;
		exit( -1 );
	}
}

void GameWorld::LoadMonsterConfig(irr::u32 sceneNum)
{
	typedef irr::core::array< std::pair<Item*, int> > ItemCollection;
	
	std::string MonsterConfigFileName = "media/scenes/m" + Utils::toString(sceneNum) + ".rxw";
	std::ifstream MonsterConfigFile(MonsterConfigFileName.c_str());

	if( MonsterConfigFile )
	{
		std::string lines;
		irr::core::stringc modelFilePath = "";
		irr::core::vector3df pos;
		irr::core::vector3df rot;
		irr::core::vector3df scale;
		irr::core::stringw type;
		irr::u32 exp, hp, attk, def, mattk, mdef, money;

		exp = attk = def = mattk = mdef = money = 0;
		pos = rot = scale = irr::core::vector3df(0, 0, 0);

		ItemCollection monItemBox;
		while( !MonsterConfigFile.eof() )
		{
			std::getline( MonsterConfigFile, lines );

			if( lines != "")
			{
				if( lines == "BEGINMONSTER" )
				{
					continue;
				}
				else if( lines == "ENDMONSTER" )
				{
					MonsterConfigFile.close();
					break;
				}
				else if( lines.substr(0, 5) == "MODEL" )
				{
					modelFilePath = lines.substr(6, lines.length()).c_str();
				}
				else if( lines.substr(0, 3) == "POS" )
				{
					Tokenizer tokenizer( lines.substr(4, lines.length()), "," );

					pos.X = Utils::toFloat(tokenizer.getNextToken());
					pos.Y = Utils::toFloat(tokenizer.getNextToken());
					pos.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if( lines.substr(0, 3) == "ROT" )
				{
					Tokenizer tokenizer( lines.substr(4, lines.length()), "," );

					rot.X = Utils::toFloat(tokenizer.getNextToken());
					rot.Y = Utils::toFloat(tokenizer.getNextToken());
					rot.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if( lines.substr(0, 5) == "SCALE" )
				{
					Tokenizer tokenizer( lines.substr(6, lines.length()), "," );

					scale.X = Utils::toFloat(tokenizer.getNextToken());
					scale.Y = Utils::toFloat(tokenizer.getNextToken());
					scale.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if( lines.substr(0, 3) == "EXP" )
				{
					exp = Utils::toInt( lines.substr(4, lines.length()) );
				}
				else if( lines.substr(0, 2) == "HP" )
				{
					hp = Utils::toInt( lines.substr(3, lines.length()) );
				}
				else if( lines.substr(0, 4) == "ATTK" )
				{
					attk = Utils::toInt( lines.substr(5, lines.length()) );
				}
				else if( lines.substr(0, 3) == "DEF" )
				{
					def = Utils::toInt( lines.substr(4, lines.length()) );
				}
				else if( lines.substr(0, 5) == "MATTK" )
				{
					mattk = Utils::toInt( lines.substr(6, lines.length()) );
				}
				else if( lines.substr(0, 4) == "MDEF" )
				{
					mdef = Utils::toInt( lines.substr(5, lines.length()) );
				}
				else if( lines.substr(0, 4) == "TYPE" )
				{
					type = lines.substr(5, lines.length()).c_str();
				}
				
				else if( lines.substr(0, 5) == "MONEY" )
				{
					money = Utils::toInt( lines.substr(6, lines.length()) );
				}
				else if( lines == "ADDMONSTER" )
				{
					Monster* m = new Monster( GEngine, *this, exp, hp, attk, def, mattk, mdef, monItemBox,pos, type, money);
					actors.push_back(m);
					monsters.push_back(m);
					m->ReSetPosition(pos);

					modelFilePath = "";
					exp = attk = def = mattk = mdef = money = 0;
					pos = rot = scale = irr::core::vector3df(0, 0, 0);
				}
			}
		}
	}
	else
	{
		std::cout << "Error loading monster config file: " << MonsterConfigFileName << ", aborting!" << std::endl;
		exit( -1 );
	}
}

void GameWorld::LoadScene(const irr::c8* sceneFile, irr::core::vector3df offset, irr::s32 fallID, irr::s32 triID, irr::s32 houseID)
{
	smgr.loadScene(sceneFile);

	// add triangle selectors for every mesh node in the level
	irr::core::array< irr::scene::ISceneNode* > outNodes;

	smgr.getSceneNodesFromType( irr::scene::ESNT_MESH, outNodes );

	for( irr::u32 i = 0; i < outNodes.size(); ++i )
	{
		irr::scene::IMeshSceneNode* meshNode = (irr::scene::IMeshSceneNode*)(outNodes[i]);

		// some mesh nodes in the level don't have meshes assigned to them, display a warning when this occurs
		if( meshNode->getMesh() )
		{
			if( meshNode->getID() != fallID )
			{
				if (meshNode->getID() == triID || meshNode->getID() == houseID)
				{
					std::cout << "!!!!" << std::endl;
					meshNode->setPosition(meshNode->getPosition() + offset);
					
					irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( meshNode->getMesh(), meshNode );
					meshNode->setTriangleSelector( meshTriangleSelector );
					levelTriangleSelector->addTriangleSelector( meshTriangleSelector );
					meshTriangleSelector->drop();
					meshTriangleSelector = NULL;
					blocks.push_back( meshNode );
				}
			}
			else if (meshNode->getID() == fallID)
			{
				meshNode->setPosition(meshNode->getPosition() + offset);
			}

			if (meshNode->getID() != NODE_ID_SCENE1_HOUSE)
			{
				meshNode->setMaterialFlag( irr::video::EMF_LIGHTING, true);	
			}
			
			 if(meshNode->getID() == NODE_ID_SCENE1_HOUSE){
				 irr::video::IVideoDriver& driver = GEngine.GetDriver();
				 Shader*	test1 = GEngine.GetShaderFactory().createShader( "media/shader/house.vert", "media/shader/house.frag", 2, irr::video::EMT_SOLID );
				 meshNode->setMaterialType((irr::video::E_MATERIAL_TYPE)test1->GetShaderMaterial());
				 //node->setMaterialType(irr::video::EMT_SOLID);
				 meshNode->setMaterialFlag( irr::video::EMF_LIGHTING, true);
				 meshNode->setMaterialTexture(0, driver.getTexture( "media/model/N2d_000.tga" ));
		
				 meshNode->setMaterialTexture(1, driver.getTexture( "media/model/Maison Texture.png" ));
			 
			 
			 }
			 
		}
	}

	outNodes.clear();

	// set the world's triangleSelector
	smgr.getRootSceneNode()->setTriangleSelector( levelTriangleSelector );

	// add a light for the scene
	offset.Y += 500;
	smgr.addLightSceneNode(0, irr::core::vector3df(0,300,0), irr::video::SColorf(255,255,255,1), 600);
}

// initializes level sounds
void GameWorld::InitMusic()
{
	// load and play music
	GEngine.ChangeBGM("media/music/scene1.mp3");
}

// sets up the light in the world
void GameWorld::InitLight()
{
	// Setup the directional light information
	irr::video::SLight lightInfo;
	lightInfo.CastShadows = true;
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
	mainCharacter = new MainCharacter( GEngine, *this );
	actors.push_back( mainCharacter );
	mainCharacter->SetRotation(irr::core::vector3df(0, 0, 0));
}

void GameWorld::InitRobot()
{
	robot = new Robot( GEngine, *this );
	actors.push_back( robot );
}

// sets up the enemies in the world
void GameWorld::InitEnemies()
{
	typedef irr::core::array< std::pair<Item*, int> > ItemCollection;
	ItemCollection monItemBox1;
	ItemCollection monItemBox2;
//temp use only
	irr::video::ITexture* text = NULL;

	Item* hp = new HPItem(*this, HPITEM, "HP Medicine", 50, "Recover 50 Health Point", text);
	Item* md1 = new MDiscItem(*this, MDISCITEM, "Fire", 10, "Fire Magic of 10 Magical Attack point", text);	
	Item* md2 = new MDiscItem(*this, MDISCITEM, "Ice", 10, "Ice Magic of 10 Magical Attack point", text);
	Item* md3 = new MDiscItem(*this, MDISCITEM, "Lightning", 30, "Lightning Magic of 30 Magical Attack point", text);
	Item* md4 = new MDiscItem(*this, MDISCITEM, "Cyclone", 40, "Cyclone Magic of 40 Magical Attack point", text);
	Item* xItem = new XItem(*this, XITEM, "X Item", 1, "Special Item", text);
	Item* weapon1 = new WeaponItem(*this, WEAPONITEM1, "Knife", 10, "Knife with 10 Physical Attack point", text, "media/model/sword.obj");
	Item* weapon2 = new WeaponItem(*this, WEAPONITEM1, "Sword", 20, "Sword with 20 Physical Attack point", text, "media/model/sword.obj");
	Item* weapon3 = new WeaponItem(*this, WEAPONITEM1, "Long Sword", 30, "Long Sword with 30 Physical Attack point", text, "media/model/sword.obj");
	((WeaponItem*)weapon1)->GetNode()->setVisible( false );
	((WeaponItem*)weapon2)->GetNode()->setVisible( false );
	((WeaponItem*)weapon3)->GetNode()->setVisible( false );
	
	monItemBox1.push_back(std::make_pair(hp, 1));
	monItemBox1.push_back(std::make_pair(md1, 2));

	monItemBox2.push_back(std::make_pair(md2, 1));
	monItemBox2.push_back(std::make_pair(md3, 2));

	Monster* m1 = new Monster( GEngine, *this, 50, 200, 100, 20, 100, 20, monItemBox1,irr::core::vector3df(120,10,100), "Type1", 1000);
	
	//m1->ReSetPosition(irr::core::vector3df(120,10,100));
	
	Monster* m2 = new Monster( GEngine, *this, 50, 300, 100, 20, 100, 20, monItemBox2,irr::core::vector3df(100,10,180), "Type2", 2000);
	
	//m2->ReSetPosition(irr::core::vector3df(100,10,180));
	actors.push_back(m1);
	actors.push_back(m2);
	monsters.push_back( m1 );
	monsters.push_back( m2 );
}

// sets up the camera to be able to look at the scene
void GameWorld::InitCamera()
{
	camera = new Camera( GEngine, *this, *levelTriangleSelector, GetCurrentPlayer() );
	// add the camera to the actor's list so it gets ticked
	actors.push_back( camera );
}

void GameWorld::InitEffects()
{
}

void GameWorld::InitNPC()
{
	////SellingMachine* sellingMachine1 = new SellingMachine( GEngine, *this, irr::core::vector3df(0, 30, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10) );
	////actors.push_back( sellingMachine1 );

	////TriggerEventItem* TriggerEventItem1 = new TriggerEventItem( GEngine, *this, irr::core::vector3df(0, 30, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10) );
	////actors.push_back( TriggerEventItem1 );
}

void GameWorld::InitHUD()
{
	gameHUD = new GameHUD( GEngine.GetDevice() );
	gameHUD->Init();
}

// cleans up the game world
void GameWorld::Exit()
{
	// clean up all the actors
	irr::u32 actorNum = actors.size();
	for( irr::u32 i=0; i < actorNum; ++i )
		Actor::DestroyActor(actors[i]);

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
	GEngine.GetSoundEngine().removeAllSoundSources();

	delete gameHUD;
	gameHUD = NULL;

	// clear scene
	smgr.clear();
}

void GameWorld::UpdateHUD( irr::f32 delta ){
	switch( gameState ){
		case state_GAMEPLAY:
			{
				gameHUD->Update(delta, GetCurrentPlayer());;
			}break;
		case state_INTERACTING:
			{
				gameHUD->Update(delta, GetCurrentPlayer());
				gameHUD->DrawConversation();
			}break;
		case state_PAUSED:
			{
				gameHUD->DrawPauseMenu(GetCurrentPlayer());
				gameHUD->DrawConversation();
			}break;
		case state_START_LEVEL:
		{
			gameHUD->gameStart(delta);
		}break;
		case state_GAME_OVER:
		{
			gameHUD->gameOver(delta);
		}break;
		case state_GAME_VICTORY:
		{
			gameHUD->gameVictory(delta);
		}break;
		default:
			break;
	}
}

void GameWorld::requestInteracting(bool on, InteractiveActor* currentInteractingActor = NULL)
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

void GameWorld::requestGameOver()
{
	gameState = state_GAME_OVER;
}

void GameWorld::requestGameVictory()
{
	gameState = state_GAME_VICTORY;
}

// called every frame with the frame's elapsed time
void GameWorld::Tick( irr::f32 delta )
{
	switch( gameState )
	{
		case state_GAMEPLAY:
		case state_INTERACTING:
		case state_PAUSED:
			DoGameplay( delta );
			break;
		case state_PLAYER_DEAD:
			stateTimer += delta;
			if( stateTimer >= PLAYER_DEATH_STATE_TIMER )
			{
				stateTimer = 0;
				gameState = state_RESTART_LEVEL;
			}
			break;
		case state_GAME_OVER:
			{
				if( stateTimer < GAME_OVER_STATE_TIMER )
				{
					stateTimer += delta;
				}
				else
				{
					stateTimer = 0;
					GEngine.RequestStateChange( state_FRONTEND );
				}
			}break;
		case state_START_LEVEL:
			{
				if(  GEngine.GetReceiver().keyReleased(irr::KEY_SPACE) )
				{
					stateTimer = 0;
					gameState = state_GAMEPLAY;
					gameHUD->GetConversation(L"");
				}
				
				if( stateTimer < START_LEVEL_STATE_TIMER )
				{
					stateTimer += delta;
				}
				else
				{
					stateTimer = 0;
					gameState = state_GAMEPLAY;
					gameHUD->GetConversation(L"");				
				}
			}break;
		case state_GAME_VICTORY:
			{
				if( stateTimer < GAME_WIN_STATE_TIMER )
				{
					stateTimer += delta;
				}
				else
				{
					stateTimer = 0;
					GEngine.RequestStateChange( state_FRONTEND );
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
	// perform an input update
	DoInput();

	if(gameState != state_PAUSED)
	{
		if(gameState != state_INTERACTING)
		{
			// tick all actors
			for( irr::u32 i=0; i < actors.size(); ++i )
				actors[i]->Tick( delta );
		}
		else
		{
			interactingActor->Tick( delta );
		}		
	}

	// update 3d audio information
	DoAudio();

	// clean up
	DoCleanUp();
}

// perform an tick of the input system
void GameWorld::DoInput()
{
	// handle user input for player
	InputEventReceiver& receiver = GEngine.GetReceiver();

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

	static bool cheatWeapon = false;
	static bool debugBoxes = false;
	static bool debugCamera = false;
	if( receiver.keyDown(irr::KEY_KEY_0) )
	{
		if( receiver.keyReleased(irr::KEY_KEY_1) )
			cheatWeapon = !cheatWeapon;
		if( receiver.keyReleased(irr::KEY_KEY_2) )
		{
			if( debugBoxes )
				DebugInfo::enableDebugBBox( *this );
			else
				DebugInfo::disableDebugBBox( *this );
			
			debugBoxes = !debugBoxes;
		}
		if( receiver.keyReleased(irr::KEY_KEY_3) )
		{
			DebugInfo::nextCullingMode( *camera );
		}
		if( receiver.keyReleased(irr::KEY_KEY_4) )
		{
			if( debugCamera )
				DebugInfo::enableDebugCamera( *this, camera );
			else
				DebugInfo::disableDebugCamera( *this );
			
			debugCamera = !debugCamera;
		}
		if( receiver.keyReleased(irr::KEY_KEY_5) )
		{
			DebugInfo::killMainCharacter( *mainCharacter );
		}
	}

	if(cheatWeapon)
	{
		/**
		weapon position and rotation tuning
		**/
		irr::core::vector3df wp = mainCharacter->getWeaponNode()->getPosition();
		irr::core::vector3df wr = mainCharacter->getWeaponNode()->getRotation();
		if( receiver.keyReleased(irr::KEY_F1) )
			wp.X -= 0.1;
		if( receiver.keyReleased(irr::KEY_F2) )
			wp.X += 0.1;
		if( receiver.keyReleased(irr::KEY_F3) )
			wp.Y -= 0.1;
		if( receiver.keyReleased(irr::KEY_F4) )
			wp.Y += 0.1;
		if( receiver.keyReleased(irr::KEY_F5) )
			wp.Z -= 0.1;
		if( receiver.keyReleased(irr::KEY_F6) )
			wp.Z += 0.1;
		if( receiver.keyDown(irr::KEY_F7) )
			wr.X -= 0.1;
		if( receiver.keyDown(irr::KEY_F8) )
			wr.X += 0.1;
		if( receiver.keyDown(irr::KEY_F9) )
			wr.Y -= 0.1;
		if( receiver.keyDown(irr::KEY_F10) )
			wr.Y += 0.1;
		if( receiver.keyDown(irr::KEY_F11) )
			wr.Z -= 0.1;
		if( receiver.keyDown(irr::KEY_F12) )
			wr.Z += 0.1;
		std::cout<<"P:"<<wp.X<<","<<wp.Y<<","<<wp.Z<<std::endl;
		std::cout<<"R:"<<wr.X<<","<<wr.Y<<","<<wr.Z<<std::endl;
		mainCharacter->getWeaponNode()->setRotation(wr);
		mainCharacter->getWeaponNode()->setPosition(wp);
	}

	if( gameState == state_PAUSED || gameState == state_INTERACTING)
		return;
}

// updates and plays 3d audio effects
void GameWorld::DoAudio()
{
	// update 3d position of player
	GEngine.GetSoundEngine().setListenerPosition(GetCurrentPlayer().GetNodePosition(), GetCurrentPlayer().GetFaceVector());
}

// returns the player actor which is currently used
Player& GameWorld::GetCurrentPlayer() const
{
	return *mainCharacter;
}

// unbuffered mouse input 
void GameWorld::OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent )
{
	if( mainCharacter )
	{
		GetCurrentPlayer().OnMouseEvent( mouseEvent );
	}
}

void GameWorld::DoCleanUp()
{
	irr::s32 numberOfActor = actors.size();
	for(irr::s32 i = numberOfActor - 1; i > 0; --i)
	{
		if( actors[i]->GetActorState() == state_ACTOR_DEAD )
		{
			if( actors[i]->GetActorType() & ACTOR_ENEMY )
			{
				std::cout<<"We get the monsters !"<<std::endl;
				irr::u32 j = monsters.linear_search( (Monster*) actors[i] );
				if( j != -1 )
				{
					if( mainCharacter->GetTarget() == monsters[j] )
					{
						mainCharacter->SetTarget( NULL );
					}
					GetLevelTriangleSelector().removeTriangleSelector( monsters[j]->GetNode().getTriangleSelector() );
					monsters.erase( j );
				}
			}
			Actor::DestroyActor( actors[i] );
			actors.erase( i );
		}
	}
}