#include "GameEngine.hpp"
#include "GameHUD.hpp"
#include "GameWorld.hpp"
#include "InputEventReceiver.hpp"
#include "TalkativeNPC.hpp"
#include "MainCharacter.hpp"

TalkativeNPC::TalkativeNPC( GameEngine& gameEngine, GameWorld& gameWorld, const irr::c8* mesh, irr::core::array<irr::core::stringw>& dialogs, irr::video::ITexture* header,irr::f32 acceptableDistance, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale, irr::u32 type)
	: InteractiveActor(gameEngine, gameWorld),
	_header(header),
	acceptable_Distance(acceptableDistance),
	_type(type),
	itemTrigger(false)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addAnimatedMeshSceneNode(smgr.getMesh(mesh), smgr.getRootSceneNode());
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);
	node->setScale(defaultScale);

	irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( ((irr::scene::IAnimatedMeshSceneNode*)node)->getMesh(), node );
	node->setTriangleSelector( meshTriangleSelector );
	world.GetLevelTriangleSelector().addTriangleSelector( meshTriangleSelector );
	meshTriangleSelector->drop();
	meshTriangleSelector = NULL;

	int noDialog = dialogs.size();
	for(int i = 0; i < noDialog; ++i)
	{
		_dialogs.push_back(dialogs[i]);
	}

	this->RecreateCollisionResponseAnimator();
}

TalkativeNPC::~TalkativeNPC()
{
}

void TalkativeNPC::RecreateCollisionResponseAnimator()
{
	// drop the current collision response animator
	if( collisionAnimator )  // soft fail which allows us to call RecreateCollisionResponseAnimator to first initialize the non-existing animator
	{
		node->removeAnimator( collisionAnimator );
		collisionAnimator->drop();
		collisionAnimator = NULL;
	}

	// setup torso collision with the world
	irr::core::aabbox3df box = node->getMesh()->getBoundingBox();
	irr::core::vector3df radius = box.MaxEdge - box.getCenter();

	collisionAnimator = world.GetSceneManager().createCollisionResponseAnimator(
		&world.GetLevelTriangleSelector(), node, radius,
		irr::core::vector3df(0,-.08f,0), // gravity
		irr::core::vector3df(0, 0, 0), // ellipsoid translation
		0.0001f); // sliding value

	node->addAnimator(collisionAnimator);
}

void TalkativeNPC::interaction(irr::f32 delta)
{
	std::cout << "Check Type" << std::endl;
	MainCharacter::ItemCollection theBox;

	if( itemTrigger == true )
	{
		finishAction();
			return;
	}
	if(_type == 1)
	{
		int needed = 0;
		theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
		for(irr::u32 i = 0; i < theBox.size(); ++i)
		{
			if(
				(theBox[i].first->getItemType() == WEAPONITEM1 && 
				theBox[i].first->getItemName() == "Sword" &&
				theBox[i].second >= 1)
			||
				(theBox[i].first->getItemType() == MDISCITEM && 
				theBox[i].first->getItemName() == "Fire" &&
				theBox[i].second >= 1)
			||
				(theBox[i].first->getItemType() == MDISCITEM && 
				theBox[i].first->getItemName() == "Ice" &&
				theBox[i].second >= 1)
			||
				(theBox[i].first->getItemType() == MDISCITEM && 
				theBox[i].first->getItemName() == "Lightning" &&
				theBox[i].second >= 1)
			||
				(theBox[i].first->getItemType() == MDISCITEM && 
				theBox[i].first->getItemName() == "Cyclone" &&
				theBox[i].second >= 1)
			)
			++needed;
		}
		if( needed == 5 )
		{
			world.GetActors().erase( world.GetActors().linear_search( this ) );
			world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
			node->setVisible( false );
			itemTrigger = true;

			finishAction();
			return;
		}
	}
	else if(_type == 10)
	{
		int needed = 0;
		theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
		for(irr::u32 i = 0; i < theBox.size(); ++i)
		{
			if(
				(theBox[i].first->getItemType() == XITEM && 
				theBox[i].second >= 1)
			)
			needed += theBox[i].second;
		}
		if( needed >= 3 )
		{
			world.GetActors().erase( world.GetActors().linear_search( this ) );
			world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
			node->setVisible( false );
			itemTrigger = true;

			finishAction();
			return;
		}
	}

	static int state = 0;
	static int talking = 0;
	static int currentline = 1;
	static double timeElapsed = 0;
	
	if(state == 0)
	{
		world.requestTalking();
		++state;
	}
	else if(state == 1)
	{
		if(talking < _dialogs.size())
		{
			if(currentline <= _dialogs[talking].size())
			{
				if(timeElapsed > 0.05)
				{
					irr::core::stringw temp  = _dialogs[talking].subString(0, currentline);
					world.GetGameHUD()->GetConversation(temp, _header);
					++currentline;
					timeElapsed = 0;
				}
			}
			else
			{
				++talking;
				++state;
				currentline = 1;
			}
		}
		else
		{
			world.GetGameHUD()->GetConversation("");
			timeElapsed = 0;


			if (_type == 2) //Sword
			{
				theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
				for(irr::u32 i = 0; i < theBox.size(); ++i)
				{
					if(
						(theBox[i].first->getItemType() == WEAPONITEM1 && 
						theBox[i].first->getItemName() == "Sword")
					)
					{
						theBox[i].second += 1;
						((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(theBox);
									world.GetActors().erase( world.GetActors().linear_search( this ) );
					world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
					node->setVisible( false );
					itemTrigger = true;
					}
				}
			}
			else if (_type == 3) //Fire
			{
				theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
				for(irr::u32 i = 0; i < theBox.size(); ++i)
				{
					if(
						(theBox[i].first->getItemType() == MDISCITEM && 
						theBox[i].first->getItemName() == "Fire")
					)
					{
						theBox[i].second += 3;
						((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(theBox);
									world.GetActors().erase( world.GetActors().linear_search( this ) );
					world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
					node->setVisible( false );
					itemTrigger = true;
					}
				}
			}
			else if (_type == 4) //Ice
			{
				theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
				for(irr::u32 i = 0; i < theBox.size(); ++i)
				{
					if(
						(theBox[i].first->getItemType() == MDISCITEM && 
						theBox[i].first->getItemName() == "Ice")
					)
					{
						theBox[i].second += 3;
						((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(theBox);
									world.GetActors().erase( world.GetActors().linear_search( this ) );
					world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
					node->setVisible( false );
					itemTrigger = true;
					}
				}
			}
			else if (_type == 5) //Lightning
			{
				theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
				for(irr::u32 i = 0; i < theBox.size(); ++i)
				{
					if(
						(theBox[i].first->getItemType() == MDISCITEM && 
						theBox[i].first->getItemName() == "Lightning")
					)
					{
						theBox[i].second += 3;
						((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(theBox);
									world.GetActors().erase( world.GetActors().linear_search( this ) );
					world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
					node->setVisible( false );
					itemTrigger = true;
					}
				}
			}
			else if (_type == 6) //Cyclone
			{
				theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
				for(irr::u32 i = 0; i < theBox.size(); ++i)
				{
					if(
						(theBox[i].first->getItemType() == MDISCITEM && 
						theBox[i].first->getItemName() == "Cyclone")
					)
					{
						theBox[i].second += 3;
						((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(theBox);
									world.GetActors().erase( world.GetActors().linear_search( this ) );
					world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
					node->setVisible( false );
					itemTrigger = true;
					}
				}
			}
			else if (_type == 7) //Knife
			{
				theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
				for(irr::u32 i = 0; i < theBox.size(); ++i)
				{
					if(
						(theBox[i].first->getItemType() == MDISCITEM && 
						theBox[i].first->getItemName() == "Knife")
					)
					{
						theBox[i].second += 3;
						((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(theBox);
									world.GetActors().erase( world.GetActors().linear_search( this ) );
					world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
					node->setVisible( false );
					itemTrigger = true;
					}
				}
			}
			else if (_type == 8) //Long Sword
			{
				theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
				for(irr::u32 i = 0; i < theBox.size(); ++i)
				{
					if(
						(theBox[i].first->getItemType() == WEAPONITEM1 && 
						theBox[i].first->getItemName() == "Long Sword")
					)
					{
						theBox[i].second += 3;
						((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(theBox);
									world.GetActors().erase( world.GetActors().linear_search( this ) );
					world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
					node->setVisible( false );
					itemTrigger = true;
					}
				}
			}
			else if (_type == 9) //HP Medicine 
			{
				theBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
				for(irr::u32 i = 0; i < theBox.size(); ++i)
				{
					if(
						(theBox[i].first->getItemType() == HPITEM && 
						theBox[i].first->getItemName() == "HP Medicine")
					)
					{
						theBox[i].second += 5;
						((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(theBox);
						world.GetActors().erase( world.GetActors().linear_search( this ) );
						world.GetLevelTriangleSelector().removeTriangleSelector( node->getTriangleSelector() );
						node->setVisible( false );
						itemTrigger = true;
					}
				}
			}
	

			finishAction();
			talking = 0;
		}
	}
	else if(state == 2)
	{
		InputEventReceiver& receiver = GEngine.GetReceiver();

		if(receiver.keyReleased(irr::KEY_KEY_V))
		{
			state = 1;
		}
	}

	timeElapsed += delta;
}

irr::f32 TalkativeNPC::acceptableDistance()
{
	return acceptable_Distance;
}
