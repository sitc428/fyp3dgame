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
static const irr::f32 GAME_WIN_STATE_TIMER = 30.0f;

GameWorld::GameWorld( GameEngine& gameEngine )
	: GamePart( gameEngine ),
	smgr(gameEngine.GetSceneManager()),
	mainCharacter(NULL),
	robot(NULL),
	camera(NULL),
	cutSceneCamera(NULL),
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
	irr::video::IVideoDriver& driver = GEngine.GetDriver();

	//temp use only
	irr::video::ITexture* text = NULL;

	text = driver.getTexture("media/image/de3d76ac771c29b4f04beacb70ebabbd.png");
	hp = new HPItem(*this, HPITEM, "HP Medicine", 50, "Recover 50 Health Point", text);
	text = driver.getTexture("media/image/723e676cab1675f3d47d71960cca50bc.png");
	md1 = new MDiscItem(*this, MDISCITEM, "Fire", 10, "Fire Magic of 10 Magical Attack point", text);	
	text = driver.getTexture("media/image/3f784fc5d3d60b6d1ac56e000061f11c.png");
	md2 = new MDiscItem(*this, MDISCITEM, "Ice", 10, "Ice Magic of 10 Magical Attack point", text);
	text = driver.getTexture("media/image/afc257a5363d544d8daba8904fa9efb0.png");
	md3 = new MDiscItem(*this, MDISCITEM, "Lightning", 30, "Lightning Magic of 30 Magical Attack point", text);
	text = driver.getTexture("media/image/b5388b5a747ce72ede81145817e118eb.png");
	md4 = new MDiscItem(*this, MDISCITEM, "Cyclone", 40, "Cyclone Magic of 40 Magical Attack point", text);
	text = driver.getTexture("media/image/96c91407c63a4c21ce305dfef464954a.png");
	xItem = new XItem(*this, XITEM, "X Item", 1, "Special Item", text);
	text = driver.getTexture("media/image/7a5fcebbc89e005a7794084c9d3583c1.png");
	weapon1 = new WeaponItem(*this, WEAPONITEM1, "Knife", 10, "Knife with 10 Physical Attack point", text, "media/model/sword.obj");
	weapon2 = new WeaponItem(*this, WEAPONITEM1, "Sword", 20, "Sword with 20 Physical Attack point", text, "media/model/sword.obj");
	weapon3 = new WeaponItem(*this, WEAPONITEM1, "Long Sword", 30, "Long Sword with 30 Physical Attack point", text, "media/model/sword.obj");
	((WeaponItem*)weapon1)->GetNode()->setVisible( false );
	((WeaponItem*)weapon2)->GetNode()->setVisible( false );
	((WeaponItem*)weapon3)->GetNode()->setVisible( false );

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
/*	ParticleManager* fire = new ParticleManager(&smgr, irr::core::vector3df(38.114258, 40.000000, 194.928589),
		irr::core::vector3df(30,2,2),
		irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7));

	fire->CreateBoxEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
						   50,80,800,1000, GEngine.GetDriver().getTexture("media/shader/smoke.bmp"));
*/	
	ParticleManager* fire1 = new ParticleManager(&smgr, irr::core::vector3df(40, 0.000000, 120.928589),
		irr::core::vector3df(5,4,4),
													   irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	fire1->CreateBoxEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
							500,530,1500,2000, GEngine.GetDriver().getTexture("media/shader/fire.bmp"));
//	fire1->CreateSmokeEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
//							500,530,1500,2000, GEngine.GetDriver().getTexture("media/model/black.png"));
	
	ParticleManager* fire2 = new ParticleManager(&smgr, irr::core::vector3df(-110, 0.000000, -80.928589),
												 irr::core::vector3df(6,6,6),
												 irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	fire2->CreateBoxEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
							500,530,1500,2000, GEngine.GetDriver().getTexture("media/shader/fire.bmp"));

	ParticleManager* fire3 = new ParticleManager(&smgr, irr::core::vector3df(145, 0.000000, 15.928589),
												 irr::core::vector3df(6,8,6),
												 irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	fire3->CreateBoxEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
							400,420,1500,2000, GEngine.GetDriver().getTexture("media/shader/fire.bmp"));
	ParticleManager* fire4 = new ParticleManager(&smgr, irr::core::vector3df(70, 0.000000, -210.928589),
												 irr::core::vector3df(7,7,7),
												 irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	fire4->CreateBoxEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
							420,450,1600,2000, GEngine.GetDriver().getTexture("media/shader/fire.bmp"));

	ParticleManager* Snow = new  ParticleManager(&smgr, irr::core::vector3df(0,100,-3000), irr::core::vector3df(2,2,2),
														   irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	std::cout<<"----\n";
	Snow->CreateCylinderEmitter(irr::core::vector3df(0,100,0), irr::f32(300.0), irr::core::vector3df(0,0,0),
								irr::f32(200.0), irr::core::vector3df(0.0f,-0.03f,0.0f), 400,500,2500,3000, GEngine.GetDriver().getTexture("media/shader/smoke.bmp"));
	
	ParticleManager* Smoke1 = new ParticleManager(&smgr, irr::core::vector3df(40, 100.000000, 120.928589),
												 irr::core::vector3df(3,3,3),
												 irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
	Smoke1->CreateSmokeEmitter(irr::core::vector3df(0.0f,0.06f,0.0f),
							   100,300,100,1000, GEngine.GetDriver().getTexture("media/model/black.png"));

	
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
	LoadNPCConfig(2);
	LoadSceneConfig(3);
	LoadMonsterConfig(3);
	LoadNPCConfig(3);
	LoadSceneConfig(4);
	LoadMonsterConfig(4);
	LoadNPCConfig(4);

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
		irr::s32 houseID1 = -1, houseID2 = -1;
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
				else if( lines.substr(0, 6) == "HOUSE1" )
				{
					houseID1 = Utils::toInt( lines.substr(7, lines.length()) );
				}
				else if( lines.substr(0, 6) == "HOUSE2" )
				{
					houseID2 = Utils::toInt( lines.substr(7, lines.length()) );
				}
			}
		}
		
		//create triggerEventItem in scene 3 to load the cut scene
		if (sceneNum == 3)
		{
			//TriggerEventItem* loadCutScene = new TriggerEventItem( GEngine, *this, irr::core::vector3df(-38.976692, -43.057495, -2495.10015), irr::core::vector3df(0, 0, 0), irr::core::vector3df(8.215017, 16.877583, 1.000000), CUTSCENE );
			TriggerEventItem* loadCutScene = new TriggerEventItem( GEngine, *this, irr::core::vector3df(-321.887726, 128.102417, -2950.451652), irr::core::vector3df(0, 0, 0), irr::core::vector3df(80.000000, 80.000000, 80.000000), CUTSCENE );
			actors.push_back( loadCutScene );
		}
		LoadScene(sceneIRRFilePath.c_str(), pos, fallID, triID, houseID1, houseID2);
	}
	else
	{
		std::cout << "Error loading scene config file: " << sceneConfigFileName << ", aborting!" << std::endl;
		exit( -1 );
	}
}

void GameWorld::LoadParticleConfig(irr::u32 sceneNum)
{
	std::string ParticleConfigFileName = "media/scenes/p" + Utils::toString(sceneNum) + ".rxw";
	std::ifstream ParticleConfigFile(ParticleConfigFileName.c_str());
	
	if( ParticleConfigFile )
	{
		std::string lines;
		irr::core::stringc TexturePath = "";
		std::string type;
		irr::core::vector3df direction;
		irr::core::vector3df pos;
		irr::core::vector3df center;
		float radius;
		
		while( !ParticleConfigFile.eof() )
		{
			std::cout<<"new\n";
			std::getline( ParticleConfigFile, lines );
			
			if( lines != "")
			{
				std::cout<<lines<<"\n";
				if( lines == "BEGINPARTICLE" )
				{
					continue;
				}
				else if( lines == "ENDPARTICLE" )
				{
					ParticleConfigFile.close();
					break;
				}
				else if( lines.substr(0, 3) == "POS" )
				{
					Tokenizer tokenizer( lines.substr(4, lines.length()), "," );
					
					pos.X = Utils::toFloat(tokenizer.getNextToken());
					pos.Y = Utils::toFloat(tokenizer.getNextToken());
					pos.Z = Utils::toFloat(tokenizer.getNextToken());
					//std::cout<<pos.X<<" "<<pos.Y<<" "<<pos.Z<<"\n";
				}
				else if( lines.substr(0, 5) == "MODEL" )
				{
					TexturePath = lines.substr(6, lines.length()).c_str();
					//std::cout<<lines.substr(6, lines.length()).c_str()<<"\n";
				}
				else if( lines.substr(0, 9) == "DIRECTION" )
				{
					Tokenizer tokenizer( lines.substr(10, lines.length()), "," );
					
					direction.X = Utils::toFloat(tokenizer.getNextToken());
					direction.Y = Utils::toFloat(tokenizer.getNextToken());
					direction.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if( lines.substr(0, 6) == "CENTER" )
				{
					Tokenizer tokenizer( lines.substr(7, lines.length()), "," );
					
					center.X = Utils::toFloat(tokenizer.getNextToken());
					center.Y = Utils::toFloat(tokenizer.getNextToken());
					center.Z = Utils::toFloat(tokenizer.getNextToken());
				}
				else if(lines.substr(0,4) == "TYPE"){
					type = lines.substr(5, lines.length()).c_str();
					std::cout<<type<<"\n";
				}
				else if( lines.substr(0, 6) == "RADIUS" )
				{
					radius = Utils::toFloat( lines.substr(7, lines.length()) );
				}
				
				/*	else if( lines.substr(0, 5) == "SCALE" )
				 {
				 Tokenizer tokenizer( lines.substr(6, lines.length()), "," );
				 
				 scale.X = Utils::toFloat(tokenizer.getNextToken());
				 scale.Y = Utils::toFloat(tokenizer.getNextToken());
				 scale.Z = Utils::toFloat(tokenizer.getNextToken());
				 }*/
				else if( lines == "ADDPARTICLE" )
				{
					
					std::cout<<"new1\n";
					ParticleManager* newParticle = new ParticleManager(&smgr, pos, irr::core::vector3df(2,2,2),
																	   irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
					if(type == "Box"){
						newParticle->CreateBoxEmitter(direction, 20,50,400,500,  GEngine.GetDriver().getTexture(TexturePath.c_str()));
						std::cout<<"new2\n";
					}else if( type == "Cylinder")
						newParticle->CreateCylinderEmitter(center, radius, center, 500, direction, 500,600, 1000,2000,  GEngine.GetDriver().getTexture(TexturePath.c_str()));
					
				}
			}
		}
	}
	else
	{
		std::cout << "Error loading particle config file: " << ParticleConfigFileName << ", aborting!" << std::endl;
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
		irr::u32 acceptable = 20, type = 0;
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
				else if( lines.substr(0, 10) == "ACCEPTABLE" )
				{
					acceptable = atoi(lines.substr(11, lines.length()).c_str());
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
				else if( lines.substr(0, 4) == "TYPE" )
				{
					type = Utils::toInt( lines.substr(5, lines.length()) );
				}
				else if( lines == "ADDNPC" )
				{
					TalkativeNPC* newNPC = new TalkativeNPC(GEngine, *this, modelFilePath.c_str(), dialogs, headerImage, acceptable, pos, rot, scale, type);
					actors.push_back( newNPC );

					dialogs.clear();
					headerImage = NULL;
					modelFilePath = "";
					acceptable = 20;
					type = 0;
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
		irr::u32 exp, health, attk, def, mattk, mdef, money;

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
					health = Utils::toInt( lines.substr(3, lines.length()) );
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
				else if( lines.substr(0, 4) == "ITEM" )
				{
					Tokenizer tokenizer( lines.substr(5, lines.length()), "," );
					std::string itemType = tokenizer.getNextToken();
					int itemAmount = Utils::toInt( tokenizer.getNextToken() );

					if( itemType == "HP" )
					{
						monItemBox.push_back( std::make_pair(hp, itemAmount) );
					}
					else if( itemType == "MD1" )
					{
						monItemBox.push_back( std::make_pair(md1, itemAmount) );
					}
					else if( itemType == "MD2" )
					{
						monItemBox.push_back( std::make_pair(md2, itemAmount) );
					}
					else if( itemType == "MD3" )
					{
						monItemBox.push_back( std::make_pair(md3, itemAmount) );
					}
					else if( itemType == "MD4" )
					{
						monItemBox.push_back( std::make_pair(md4, itemAmount) );
					}
					else if( itemType == "XITEM" )
					{
						monItemBox.push_back( std::make_pair(xItem, itemAmount) );
					}
					else if( itemType == "WEAPON1" )
					{
						monItemBox.push_back( std::make_pair(weapon1, itemAmount) );
					}
					else if( itemType == "WEAPON2" )
					{
						monItemBox.push_back( std::make_pair(weapon2, itemAmount) );
					}
					else if( itemType == "WEAPON3" )
					{
						monItemBox.push_back( std::make_pair(weapon3, itemAmount) );
					}
				}
				else if( lines == "ADDMONSTER" )
				{
					Monster* m = new Monster( GEngine, *this, exp, health, attk, def, mattk, mdef, monItemBox,pos, type, money);
					actors.push_back(m);
					monsters.push_back(m);
					m->ReSetPosition(pos);

					monItemBox.clear();
					modelFilePath = "";
					health = exp = attk = def = mattk = mdef = money = 0;
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

void GameWorld::LoadScene(const irr::c8* sceneFile, irr::core::vector3df offset, irr::s32 fallID, irr::s32 triID, irr::s32 houseID1, irr::s32 houseID2)
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
				if (
					meshNode->getID() == triID || meshNode->getID() == houseID1 || meshNode->getID() == houseID2 )
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
			
			 if(meshNode->getID() == NODE_ID_SCENE1_HOUSE2){
				 irr::video::IVideoDriver& driver = GEngine.GetDriver();
				 Shader*	test1 = GEngine.GetShaderFactory().createShader( "media/shader/house.vert", "media/shader/house.frag", 2, irr::video::EMT_SOLID );
				 meshNode->setMaterialType((irr::video::E_MATERIAL_TYPE)test1->GetShaderMaterial());
				 //node->setMaterialType(irr::video::EMT_SOLID);
				 meshNode->setMaterialFlag( irr::video::EMF_LIGHTING, true);
				 meshNode->setMaterialTexture(0, driver.getTexture( "media/model/N2d_000.tga" ));
		
				 meshNode->setMaterialTexture(1, driver.getTexture( "media/model/WOOD058.png" ));
			 
			 
			 }

			 if( meshNode->getID() == 334 )
			 {
				 meshNode->setMaterialFlag( irr::video::EMF_LIGHTING, false );
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

	monItemBox1.push_back(std::make_pair(hp, 1));
	monItemBox1.push_back(std::make_pair(md1, 2));

	monItemBox2.push_back(std::make_pair(md2, 1));
	monItemBox2.push_back(std::make_pair(md3, 2));

	ItemCollection itemsToSell;

	itemsToSell.push_back( std::make_pair(hp, 100) );
	itemsToSell.push_back( std::make_pair(md1, 1000) );
	itemsToSell.push_back( std::make_pair(md2, 2000) );
	itemsToSell.push_back( std::make_pair(md3, 3000) );
	itemsToSell.push_back( std::make_pair(md4, 4000) );

	SellingMachine* sellingMachine1 = new SellingMachine( GEngine, *this,
		irr::core::vector3df(73.453423, 52.957031, -2081.661796),
		irr::core::vector3df(0, -69, 0),
		irr::core::vector3df(8, 8, 8), itemsToSell );
	actors.push_back( sellingMachine1 );
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
		case state_INTERACTING:
		case state_GAMEPLAY:
		case state_CUT_SCENE:
			{
				gameHUD->Update(delta, GetCurrentPlayer());;
			}break;
		case (state_INTERACTING | state_TALKING):
			{
				gameHUD->Update(delta, GetCurrentPlayer());
				gameHUD->DrawConversation();
			}break;
		case (state_INTERACTING | state_BUYING):
			{
				gameHUD->DrawBuyingMenu((SellingMachine*)interactingActor, GetCurrentPlayer());
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

void GameWorld::requestBuying()
{
	gameState = (EGameState) (state_INTERACTING | state_BUYING);
}

void GameWorld::requestTalking()
{
	gameState = (EGameState) (state_INTERACTING | state_TALKING);
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
		case (state_INTERACTING | state_TALKING):
		case (state_INTERACTING | state_BUYING):
		case state_INTERACTING:
		case state_PAUSED:
			DoGameplay( delta );
			break;
		case state_CUT_SCENE:
			if(  GEngine.GetReceiver().keyReleased(irr::KEY_SPACE) )
			{
				GetSceneManager().setActiveCamera( (irr::scene::ICameraSceneNode*)(&(camera->GetNode())) );
				stateTimer = 0;
				gameState = state_GAMEPLAY;
				//gameHUD->GetConversation(L"");
			}
			else
				DoEvent(  delta );
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
					gameState = state_CUT_SCENE;
					gameHUD->GetConversation(L"");
				}
				
				if( stateTimer < START_LEVEL_STATE_TIMER )
				{
					stateTimer += delta;
				}
				else
				{
					stateTimer = 0;
					gameState = state_CUT_SCENE;
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
		if( gameState & state_INTERACTING )
		{
			interactingActor->Tick( delta );
		}
		else
		{
			// tick all actors
			for( irr::u32 i=0; i < actors.size(); ++i )
				actors[i]->Tick( delta );
		}
	}

	// update 3d audio information
	DoAudio();

	// clean up
	DoCleanUp();
}

void GameWorld::DoEvent( irr::f32 delta )
{
	if(cutSceneCamera == NULL){
		cutSceneCamera = GetSceneManager().addCameraSceneNode(0, irr::core::vector3df(200, 60, 0) , irr::core::vector3df(0, 60, 0));
		GetSceneManager().setActiveCamera( cutSceneCamera );
	}

	robot->Tick(delta);
	
	stateTimer+=delta;
	
	if( stateTimer <= 10){
		cutSceneCamera->setPosition(irr::core::vector3df(200, 60, -50+stateTimer*10));
		cutSceneCamera->setTarget(irr::core::vector3df(0, 60, -50+stateTimer*10));
	}
	else if( stateTimer > 10 && stateTimer <= 20 )
	{
		cutSceneCamera->setPosition(irr::core::vector3df(200 - (stateTimer-10)*40, 200, 50));
		cutSceneCamera->setTarget(irr::core::vector3df(200 - (stateTimer-10)*40, 0, 50));
	}
	else if ( stateTimer > 20 && stateTimer <= 25 ){
		cutSceneCamera->setPosition(irr::core::vector3df(40, (stateTimer-20)*5, 0));
		cutSceneCamera->setTarget(irr::core::vector3df(40, (stateTimer-20)*5, 10));
	}
	else if ( stateTimer > 25 && stateTimer <= 30 ){
		cutSceneCamera->setPosition(irr::core::vector3df(40, 25 + (stateTimer - 25)*9, 0 - (stateTimer - 25)*10));
		cutSceneCamera->setTarget(irr::core::vector3df(40, 25, 10));
	}
	else if (stateTimer < 33)
	{
		cutSceneCamera->setTarget(irr::core::vector3df(40, 20, 10));
		cutSceneCamera->setPosition(irr::core::vector3df(40+sin((stateTimer-30)/3*PI)*40, 70, 10 - cos((stateTimer - 30)/3*PI)*50));
	}
	else {
		GetSceneManager().setActiveCamera( (irr::scene::ICameraSceneNode*)(&(camera->GetNode())) );
		stateTimer = 0;
		gameState = state_GAMEPLAY;
	}
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

	static bool debugBoxes = false;
	static bool debugCamera = false;
	if( receiver.keyDown(irr::KEY_KEY_0) )
	{
		if( receiver.keyReleased(irr::KEY_KEY_1) )
		{
			if( debugBoxes )
				DebugInfo::enableDebugBBox( *this );
			else
				DebugInfo::disableDebugBBox( *this );
			
			debugBoxes = !debugBoxes;
		}
		if( receiver.keyReleased(irr::KEY_KEY_2) )
		{
			if( debugCamera )
				DebugInfo::enableDebugCamera( *this, camera );
			else
				DebugInfo::disableDebugCamera( *this );
			
			debugCamera = !debugCamera;
		}
		if( receiver.keyReleased(irr::KEY_KEY_3) )
		{
			DebugInfo::teleportPlayer( *mainCharacter );
		}
		if( receiver.keyReleased(irr::KEY_KEY_4) )
		{
			DebugInfo::addExp( *mainCharacter );
		}
		if( receiver.keyReleased(irr::KEY_KEY_9) )
		{
			DebugInfo::killMainCharacter( *mainCharacter );
		}
	}

	if( gameState == state_PAUSED || gameState & state_INTERACTING)
		return;
}

// updates and plays 3d audio effects
void GameWorld::DoAudio()
{
	static int playing_brid = 0;
	// update 3d position of player
	GEngine.GetSoundEngine().setListenerPosition(GetCurrentPlayer().GetNodePosition(), GetCurrentPlayer().GetFaceVector());

	switch( rand() % 10 )
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		break;
	case 6:
		--playing_brid;
		break;
	case 7:
	case 8:
	case 9:
		if( playing_brid < 10 )
		{
			GEngine.PlaySE("media/se/bird.wav", false, irr::core::vector3df(-1000 + rand() % 2000, 90 + rand() % 30, -1800 + rand() % 500)); 
			++playing_brid;
		}
		break;
	}
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