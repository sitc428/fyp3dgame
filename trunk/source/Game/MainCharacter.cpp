
#include <cmath>
#include <iostream>

#include "CollisionHelper.hpp"
#include "FloorDecalSceneNode.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "HPItem.hpp"
#include "InputEventReceiver.hpp"
#include "Item.hpp"
#include "MainCharacter.hpp"
#include "MDiscItem.hpp"
#include "Monster.hpp"
#include "ProgressCircle.hpp"
#include "ShaderFactory.hpp"
#include "WeaponItem.hpp"
#include "XItem.hpp"
#include "Robot.hpp"

// Parameters specifying default parameters
static const irr::core::vector3df		defaultPosition = irr::core::vector3df(40,20,10);
static const irr::core::vector3df		defaultRotation = irr::core::vector3df(0, 0, 0);

static const irr::c8*		MAIN_CHARACTER_MODEL  = "media/model/Pedro.x";
static const irr::c8*		defaultTexture = "media/model/PedroTexture.png";
static const irr::f32		ANIMATION_SPEED = 24;

static irr::core::vector3df defaultAimVector = irr::core::vector3df(0, 0, -1.0);

// main character's animation information
static const irr::u32		MAIN_CHARACTER_ANIMATION_IDLE_START = 1;
static const irr::u32		MAIN_CHARACTER_ANIMATION_IDLE_END = 1;
static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_FORWARD_START = 4;
static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_FORWARD_END = 30;
static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_BACK_START = 38;
static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_BACK_END = 63;
static const irr::u32		MAIN_CHARACTER_ANIMATION_RUN_START = 80;
static const irr::u32		MAIN_CHARACTER_ANIMATION_RUN_END = 97;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK_START = 126;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK_END = 139;
static const irr::u32		MAIN_CHARACTER_ANIMATION_DEAD_START = 104;
static const irr::u32		MAIN_CHARACTER_ANIMATION_DEAD_END = 124;

// constructor
MainCharacter::MainCharacter( GameEngine& gameEngine, GameWorld& gameWorld )
	:Player(gameEngine, gameWorld),
	node(NULL),
	weaponNode(NULL),
	ATFieldNode(NULL),
	MagicNode(NULL),
	collisionAnimator(NULL),
	action(EMCAS_IDLE),
	bDoFillup( false ),
	_magicChargeProgress(0),
	attackCallBack(NULL),
	_level(1),
	_exp(0),
	_attack(80),
	_defence(50),
	_magicattack(100),
	_magicdefence(80),
	_charging(false),
	_magiclevel(0),
	_currentWeapon(NULL),
	_currentMagic(NULL),
	_combo(false),
	_comboNum(0),
	monsterTarget(NULL),
	targetIndicator(NULL)
{
	test1 = GEngine.GetShaderFactory().createShader( "media/shader/opengl.vert", "media/shader/opengl.frag", 2, irr::video::EMT_SOLID );

	irr::video::IVideoDriver& driver = GEngine.GetDriver();

	ItemCollection tmpBox;
	//temp use only
	irr::video::ITexture* text = NULL;

	Item* hp = new HPItem(world, HPITEM, "HP Medicine", 50, "Recover 50 Health Point", text);
	Item* md1 = new MDiscItem(world, MDISCITEM, "Fire", 10, "Fire Magic of 10 Magical Attack point", text);	
	Item* md2 = new MDiscItem(world, MDISCITEM, "Ice", 10, "Ice Magic of 10 Magical Attack point", text);
	Item* md3 = new MDiscItem(world, MDISCITEM, "Lightning", 30, "Lightning Magic of 30 Magical Attack point", text);
	Item* md4 = new MDiscItem(world, MDISCITEM, "Cyclone", 40, "Cyclone Magic of 40 Magical Attack point", text);
	Item* xItem = new XItem(world, XITEM, "X Item", 1, "Special Item", text);
	Item* weapon1 = new WeaponItem(world, WEAPONITEM1, "Knife", 10, "Knife with 10 Physical Attack point", text);
	Item* weapon2 = new WeaponItem(world, WEAPONITEM1, "Sword", 20, "Sword with 20 Physical Attack point", text);
	Item* weapon3 = new WeaponItem(world, WEAPONITEM1, "Long Sword", 30, "Long Sword with 30 Physical Attack point", text);
	tmpBox.push_back(std::make_pair(hp, 2));
	tmpBox.push_back(std::make_pair(md1, 5));
	tmpBox.push_back(std::make_pair(md2, 10));
	tmpBox.push_back(std::make_pair(md3, 12));
	tmpBox.push_back(std::make_pair(md4, 11));
	tmpBox.push_back(std::make_pair(xItem, 0));
	tmpBox.push_back(std::make_pair(weapon1, 1));
	tmpBox.push_back(std::make_pair(weapon2, 2));
	tmpBox.push_back(std::make_pair(weapon3, 1));
	this->SetItemBox(tmpBox);
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	// load the animated mesh, and add a new scene graph node for it
	irr::scene::ISkinnedMesh* mainCharacterMesh = (irr::scene::ISkinnedMesh*)(smgr.getMesh( MAIN_CHARACTER_MODEL ));
	node = smgr.addAnimatedMeshSceneNode( mainCharacterMesh, smgr.getRootSceneNode() );

	node->setAnimationSpeed( ANIMATION_SPEED );
	node->setFrameLoop( MAIN_CHARACTER_ANIMATION_IDLE_START, MAIN_CHARACTER_ANIMATION_IDLE_END );
	node->setLoopMode( false );
	node->setCurrentFrame( MAIN_CHARACTER_ANIMATION_IDLE_START );
	
	node->setPosition( defaultPosition );
	node->setID( 999 );
	node->setRotation( defaultRotation );
	node->setMaterialFlag(irr::video::EMF_LIGHTING, true );
	node->setMaterialType((irr::video::E_MATERIAL_TYPE)test1->GetShaderMaterial());
	node->setMaterialTexture(0, driver.getTexture( defaultTexture ));
	node->setMaterialTexture(1, driver.getTexture( "media/model/shade_line.png" ));
	//node->setDebugDataVisible( irr::scene::EDS_BBOX);

	weaponNode = smgr.addMeshSceneNode(
		smgr.getMesh("media/model/sword.obj"),//Mastersword_v003.obj or sword.obj
		node->getJointNode("RightFingerBase"),
		0,
		irr::core::vector3df(-3,0,3.5),
		irr::core::vector3df(-433.5,-1833,-12)
	);
	weaponNode->setVisible( false );
	
	weaponNode->setScale(irr::core::vector3df(0.05, 0.05, 0.05));
	Shader* Field = GEngine.GetShaderFactory().createShader( "media/shader/field.vert", "media/shader/field.frag", 1, irr::video::EMT_TRANSPARENT_ADD_COLOR);
	irr::scene::IMesh* ATmesh = smgr.addSphereMesh("", (node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter()).getLength() + 1 );
	ATFieldNode = smgr.addMeshSceneNode( ATmesh, node );
	ATFieldNode->setVisible( false );
	ATFieldNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Field->GetShaderMaterial());
	ATFieldNode->setMaterialTexture(0, driver.getTexture("media/model/portal7.bmp"));
	ATFieldNode->setRotation(irr::core::vector3df(90,-90,0));

	irr::scene::IMesh* Magicmesh = smgr.addSphereMesh("", 140 );
	MagicNode = smgr.addMeshSceneNode( Magicmesh, node );
	MagicNode->setVisible( false );
	MagicNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Field->GetShaderMaterial());
	MagicNode->setMaterialTexture(0, driver.getTexture("media/model/portal7.bmp"));
	//MagicNode->setScale(irr::core::vector3df(0.8,0.8,0.8));

	targetIndicator = smgr.addCubeSceneNode(5);
	targetIndicator->setPosition(irr::core::vector3df(50, 50, 10));
	targetIndicator->setRotation(irr::core::vector3df(45, 0, 45));
	targetIndicator->setMaterialFlag( irr::video::EMF_LIGHTING, false );
	irr::scene::ISceneNodeAnimator* anim = smgr.createRotationAnimator( irr::core::vector3df(5, 0, 5) );
	targetIndicator->addAnimator( anim );
	anim->drop();
	targetIndicator->setVisible( false );

	// setup player collision with the world
	RecreateCollisionResponseAnimator();

	// create a triangle selector for player
	irr::scene::ITriangleSelector* triangleSelector = world.GetSceneManager().createOctTreeTriangleSelector( node->getMesh(), node );
	node->setTriangleSelector( triangleSelector );
	triangleSelector->drop();
	triangleSelector = NULL;

	attackCallBack = new AttackAnimationEndCallBack( world, *this );

	aimVector = defaultAimVector;
}

// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
void MainCharacter::RecreateCollisionResponseAnimator()
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

// destructor, protected to force user to call Actor::DestroyActor
MainCharacter::~MainCharacter()
{
	if(collisionAnimator)
	{
		collisionAnimator->drop();
		collisionAnimator = NULL;
	}
	
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	smgr.addToDeletionQueue( node );

	node->setAnimationEndCallback( NULL );

	attackCallBack->drop();
}

// set the translation vector for player
void MainCharacter::SetTranslation( const irr::core::vector3df& trans )
{
	Player::SetTranslation( trans );
}

// set the rotation vector for player
void MainCharacter::SetRotation( const irr::core::vector3df& rot )
{
	Player::SetRotation( rot );

	// rotate player
	node->setRotation( irr::core::vector3df( 0, rotation.Y + defaultRotation.Y, 0 ) );
}

void MainCharacter::setIdle()
{
	node->setCurrentFrame( MAIN_CHARACTER_ANIMATION_IDLE_START );
	node->setFrameLoop( MAIN_CHARACTER_ANIMATION_IDLE_START, MAIN_CHARACTER_ANIMATION_IDLE_END );
	node->setLoopMode( false );

	ATFieldNode->setVisible( false );

	action = EMCAS_IDLE;
}

void MainCharacter::setDefending( bool defending )
{
	if( isDefending() )
		return;
	
	if( defending )
	{
		action = EMCAS_DEFEND;
		ATFieldNode->setVisible( true );
	}
}

void MainCharacter::setMoving( bool moving, bool backward )
{
	if( !isRunning() && isMoving() )
		return;

	if( moving )
	{
		action = EMCAS_MOVE;

		if( backward )
			node->setFrameLoop( MAIN_CHARACTER_ANIMATION_WALK_BACK_START, MAIN_CHARACTER_ANIMATION_WALK_BACK_END );
		else
			node->setFrameLoop( MAIN_CHARACTER_ANIMATION_WALK_FORWARD_START, MAIN_CHARACTER_ANIMATION_WALK_FORWARD_END );

		node->setLoopMode( true );

		ATFieldNode->setVisible( false );
	}
}

void MainCharacter::setAttacking( bool attacking )
{
	if( isAttacking())
		return;

	if( attacking )
	{
		action = EMCAS_ATTACK;
		node->setCurrentFrame( MAIN_CHARACTER_ANIMATION_ATTACK_START );
		node->setFrameLoop( MAIN_CHARACTER_ANIMATION_ATTACK_START, MAIN_CHARACTER_ANIMATION_ATTACK_END );
		node->setLoopMode( false );
		node->setAnimationEndCallback( attackCallBack );

		ATFieldNode->setVisible( false );
	}
}

void MainCharacter::setCasting( bool casting )
{
	if( isCasting())
		return;

	if( casting )
	{
		action = EMCAS_MAGICATTACK;
		MagicNode->setParent(&(world.GetRobot()->GetNode()));
		static irr::core::vector3df magicPos = MagicNode->getPosition() + irr::core::vector3df(0,70,0);
		MagicNode->setPosition(magicPos);
		MagicNode->setVisible(true);
		
		irr::scene::ISceneManager& smgr = world.GetSceneManager();

		irr::scene::ISceneNodeAnimator* anim = smgr.createFlyStraightAnimator(
			magicPos,
			getTargetPos(),
			2000
			);
		/*std::cout << "Target X:  " << getTargetPos().X << std::endl;
		std::cout << "Target Y:  " << getTargetPos().Y << std::endl;
		std::cout << "Target Z:  " << getTargetPos().Z << std::endl;*/

		MagicNode->addAnimator(anim);
		anim->drop();
		//MagicNode->setVisible(false);

		setIdle();
		ATFieldNode->setVisible( false );
	}
}

irr::core::vector3df MainCharacter::getTargetPos()
{
	irr::core::array<Actor*> actors = world.GetActors();
	irr::u32 actorsNum = actors.size();

	/*irr::core::line3df line;
	line.start = GetNodePosition();
	line.end = line.start - GetFaceVector() * GetRadius().getLength();*/
	std::cout << actorsNum << std::endl;
	for( irr::u32 i=0; i < actorsNum; ++i )
	{
		if( actors[i]->GetActorType() != ACTOR_ENEMY)
			continue;
		
		std::cout << "Target X:  " << actors[i]->GetNode().getPosition().X << std::endl;
		std::cout << "Target Y:  " << actors[i]->GetNode().getPosition().Y << std::endl;
		std::cout << "Target Z:  " << actors[i]->GetNode().getPosition().Z << std::endl;
		//for testing
		return actors[i]->GetNode().getPosition();

		if(
			CollisionHelper::CheckProximity2D(
				world.GetCurrentPlayer().GetNodePosition(),
				actors[i]->GetNode().getPosition(),
				//GetRadius().getLength() + actors[i]->GetRadius().getLength() +
				GetRadius().getLength() * 5
			)
			//world.GetSceneManager().getSceneCollisionManager()->getSceneNodeFromRayBB(line)
		)
		{
			/*irr::s32 playerAttk = theMainCharacter.GetAttackPoint();
			irr::s32 monDef = ((Monster*)actors[i])->GetDef();
			std::cout << "Player Attk = " << playerAttk << std::endl;
			std::cout << "Monster Defence = " << monDef << std::endl;
			irr::s32 damage = 0;
			if (playerAttk - monDef > 0 )
			{
				damage = playerAttk - monDef;
			}
			irr::s32 offset = damage/5 * (rand()%601)/300;
			std::cout << "Damage = " << damage-offset << std::endl;
			actors[i]->ReceiveDamage(damage-offset);*/
			//return actors[i]->GetNode().getPosition();
			//return actors[i]->GetNode().getPosition();
		}
	}
	return world.GetRobot()->GetFaceVector() * GetRadius() * 200;
}

void MainCharacter::setRunning( bool running )
{
	if( isRunning() )
		return;

	if( running )
	{
		node->setFrameLoop( MAIN_CHARACTER_ANIMATION_RUN_START, MAIN_CHARACTER_ANIMATION_RUN_END );
		node->setLoopMode( true );

		action = EMCAS_RUNNING;

		ATFieldNode->setVisible( false );
	}
}

bool MainCharacter::isIdle() const
{
	return action == EMCAS_IDLE;
}

bool MainCharacter::isDefending() const
{
	return action == EMCAS_DEFEND;
}

bool MainCharacter::isAttacking() const
{
	return action == EMCAS_ATTACK;
}

bool MainCharacter::isCasting() const
{
	return action == EMCAS_MAGICATTACK;
}

bool MainCharacter::isMoving() const
{
	return action == EMCAS_MOVE || action == EMCAS_RUNNING;
}

bool MainCharacter::isRunning() const
{
	return action == EMCAS_RUNNING;
}

// updates the player every fram with the elapsed time since last frame
void MainCharacter::Tick( irr::f32 delta )
{
	if( !(isAttacking() || IsDead()) )
		DoInput();

	node->setRotation( rotation );
	irr::core::vector3df playerPos = node->getPosition();
	playerPos += faceVector * delta * translation.Z;
	node->setPosition( playerPos );
	translation.Z = 0;
}

void MainCharacter::DoInput()
{
	InputEventReceiver& receiver = GEngine.GetReceiver();

	if( receiver.keyReleased(irr::KEY_TAB) )
	{
		lockNextTarget();
		return;
	}

	if( receiver.keyDown(irr::KEY_KEY_X) )
	{
		SetCharging(false);
		SetChargingProgress(0);
		SetMagicLevel(0);
		setDefending( true );
		return;
	}

	if( receiver.keyDown(irr::KEY_KEY_C) )
	{
		SetCharging( true );
		if (GetMagicLevel()<3)
		{
			SetChargingProgress(GetChargingProgress()+1);
			if (GetChargingProgress()%100 == 0)
				SetMagicLevel(GetMagicLevel()+1);
		}
	}
	else if( receiver.keyReleased(irr::KEY_KEY_C) )
	{
		if (GetMagicLevel()>=1)
			setCasting( true );
		SetCharging( false );
		SetChargingProgress(0);
		SetMagicLevel(0);
		return;
	}

	if( receiver.keyReleased(irr::KEY_KEY_Z) )
	{
		setAttacking( true );
		return;
	}

	irr::core::vector3df playerTranslation(0, 0, 0);
	irr::core::vector3df playerRotation(0, 0, 0);

	bool move = false;
	bool backward = false;

	if( receiver.keyDown(irr::KEY_UP) )
	{
		if( receiver.keyDown(irr::KEY_LEFT) && receiver.keyUp(irr::KEY_RIGHT) )
		{
			if( aimVector.getHorizontalAngle().Y - faceVector.getHorizontalAngle().Y != 45 )
			{
				faceVector = aimVector;
				faceVector.rotateXZBy( 45, irr::core::vector3df(0, 0, 0) );
				faceVector.normalize();
			}

			move = true;
		}
		else if( receiver.keyDown(irr::KEY_RIGHT) && receiver.keyUp(irr::KEY_LEFT) )
		{
			if( aimVector.getHorizontalAngle().Y - faceVector.getHorizontalAngle().Y != -45 )
			{
				faceVector = aimVector;
				faceVector.rotateXZBy( -45, irr::core::vector3df(0, 0, 0) );
				faceVector.normalize();
			}

			move = true;
		}
		else
		{
			if(faceVector != aimVector)
			{
				faceVector = aimVector;
				faceVector.normalize();
			}

			move = true;
		}
	}
	else if( receiver.keyDown(irr::KEY_DOWN) )
	{
		if( faceVector != aimVector )
		{
			faceVector = aimVector;
			faceVector.normalize();
		}

		backward = move = true;
	}
	else if( receiver.keyDown(irr::KEY_LEFT) )
	{
		if( aimVector.getHorizontalAngle().Y - faceVector.getHorizontalAngle().Y != 90 )
		{
			faceVector = aimVector;
			faceVector.rotateXZBy( 90, irr::core::vector3df(0, 0, 0) );
			faceVector.normalize();
		}

		move = true;
	}
	else if( receiver.keyDown(irr::KEY_RIGHT) )
	{
		if( aimVector.getHorizontalAngle().Y - faceVector.getHorizontalAngle().Y != -90 )
		{
			faceVector = aimVector;
			faceVector.rotateXZBy( -90, irr::core::vector3df(0, 0, 0) );
			faceVector.normalize();
		}

		move = true;
	}

	if( receiver.keyDown(irr::KEY_KEY_D) )
	{
		aimVector.rotateXZBy(-5, irr::core::vector3df(0, 0, 0) );
		aimVector.normalize();
	}

	if( receiver.keyDown(irr::KEY_KEY_A) )
	{
		aimVector.rotateXZBy(5, irr::core::vector3df(0, 0, 0) );
		aimVector.normalize();
	}

	playerRotation.Y = floor( faceVector.getHorizontalAngle().Y - defaultAimVector.getHorizontalAngle().Y );
	SetRotation( playerRotation );

	if(move)
	{
		if( receiver.keyDown(irr::KEY_SPACE) && !backward )
		{
			playerTranslation.Z = 45;
			setRunning( true );
		}
		else
		{
			playerTranslation.Z = 15;
			setMoving( true, backward );
		}

		if( backward )
			playerTranslation.Z = -playerTranslation.Z;

		SetTranslation( playerTranslation );

		return;
	}

	setIdle();
}

void MainCharacter::ReceiveDamage( irr::f32 value )
{
	if( godMode )
		return;

	if( health - value < 0 )
		health = 0;
	else
		health -= value;

	if( health <= 0 )
	{
		action = EMCAS_DEAD;
	}
	else
	{
		switch( rand() % 3 )
		{
			case 0:
				GEngine.PlaySE("media/se/playerhurt.mp3", GetNodePosition());
				break;
			case 1:
			case 2:
				break;
		}
	}
}

void MainCharacter::lockNextTarget()
{
	Monster* nextTarget = NULL;
	int numberOfMonster = world.GetMonsters().size();

	int currentTargetPos = -1;

	if( monsterTarget )
	{
		for(int i = 0; i < numberOfMonster; ++i)
		{
			if( monsterTarget == world.GetMonsters()[i] )
			{
				currentTargetPos = i;
				break;
			}
		}
	}

	for(int j = 1; j <= numberOfMonster; ++j)
	{
		if( CollisionHelper::CheckProximity2D(
				world.GetMonsters()[(currentTargetPos+j)%numberOfMonster]->GetNode().getPosition(),
				node->getPosition(),
				GetRadius().getLength() * 10)
		)
		{
			nextTarget = world.GetMonsters()[(currentTargetPos+j)%numberOfMonster];
			break;
		}
	}

	if( nextTarget )
	{
		irr::core::vector3df diff = nextTarget->GetNode().getPosition() - node->getPosition();
		if( aimVector.getHorizontalAngle().Y - diff.getHorizontalAngle().Y != 0)
		{
			aimVector.rotateXZBy( aimVector.getHorizontalAngle().Y - diff.getHorizontalAngle().Y, irr::core::vector3df(0, 0, 0));
			aimVector.normalize();
			faceVector = aimVector;
			faceVector.normalize();
			SetRotation( irr::core::vector3df( 0, floor( faceVector.getHorizontalAngle().Y - defaultAimVector.getHorizontalAngle().Y ), 0) );
		}

		monsterTarget = nextTarget;
		targetIndicator->setParent( &monsterTarget->GetNode() );
		targetIndicator->setPosition( irr::core::vector3df(0, monsterTarget->GetNode().getBoundingBox().MaxEdge.Y + 5, 0 ) );
		targetIndicator->setVisible( true );
	}
	else
	{
		monsterTarget = NULL;
		targetIndicator->setParent( world.GetSceneManager().getRootSceneNode() );
		targetIndicator->setVisible( false );
	}
}

void MainCharacter::AttackAnimationEndCallBack::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* theNode)
{
	/*irr::core::array<Actor*> actors = world.GetActors();
	irr::u32 actorsNum = actors.size();

	irr::core::line3df line;
	line.start = theMainCharacter.GetNodePosition();
	line.end = line.start - theMainCharacter.GetFaceVector() * theMainCharacter.GetRadius().getLength();

	for( irr::u32 i=0; i < actorsNum; ++i )
	{
		if( actors[i]->GetActorType() != ACTOR_ENEMY)
			continue;

		if(
			CollisionHelper::CheckProximity2D(
				theMainCharacter.GetNodePosition(),
				actors[i]->GetNode().getPosition(),
				theMainCharacter.GetRadius().getLength() + actors[i]->GetRadius().getLength() - 1.0
			)
			//world.GetSceneManager().getSceneCollisionManager()->getSceneNodeFromRayBB(line)
		)
		{
			irr::s32 playerAttk = theMainCharacter.GetAttackPoint();
			irr::s32 monDef = ((Monster*)actors[i])->GetDef();
			std::cout << "Player Attk = " << playerAttk << std::endl;
			std::cout << "Monster Defence = " << monDef << std::endl;
			irr::s32 damage = 0;
			if (playerAttk - monDef > 0 )
			{
				damage = playerAttk - monDef;
			}
			irr::s32 offset = damage/5 * (rand()%601)/300;
			std::cout << "Damage = " << damage-offset << std::endl;
			actors[i]->ReceiveDamage(damage-offset);
		}
	}*/

	Monster* theTarget = theMainCharacter.monsterTarget;
	if( theTarget )
	{
		if( CollisionHelper::CheckProximity2D(
			theTarget->GetNode().getPosition(),
			theMainCharacter.GetNodePosition(),
			theTarget->GetRadius().getLength() + theMainCharacter.GetRadius().getLength() - 5
			)
		)
		{
			irr::s32 playerAttk = theMainCharacter.GetAttackPoint();
			irr::s32 monDef = theTarget->GetDef();
			std::cout << "Player Attk = " << playerAttk << std::endl;
			std::cout << "Monster Defence = " << monDef << std::endl;
			irr::s32 damage = 0;
			if (playerAttk - monDef > 0 )
			{
				damage = playerAttk - monDef;
			}
			irr::s32 offset = damage/5 * (rand()%601)/300;
			std::cout << "Damage = " << damage-offset << std::endl;
			theTarget->ReceiveDamage(damage-offset);
		}
	}

	theMainCharacter.setIdle();
	theNode->setCurrentFrame( MAIN_CHARACTER_ANIMATION_IDLE_START );
}
