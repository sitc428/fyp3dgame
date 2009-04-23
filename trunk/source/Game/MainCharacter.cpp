
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
static const irr::c8*		defaultTexture = "media/model/PedroTexture.tga";
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
static const irr::u32		MAIN_CHARACTER_ANIMATION_DEAD_START = 104;
static const irr::u32		MAIN_CHARACTER_ANIMATION_DEAD_END = 124;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK1_START = 126;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK1_END = 139;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK2_START = 140;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK2_END = 154;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK3_START = 155;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK3_END = 167;

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
	endCallBack(NULL),
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
	targetIndicator(NULL),
	magicFlyTime(-1),
	MagicFired(false),
	MagicBonusValue(1.0),
	timeElapsed(0),
	_money(1000)
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
	Item* weapon1 = new WeaponItem(world, WEAPONITEM1, "Knife", 10, "Knife with 10 Physical Attack point", text, "media/model/sword.x");
	Item* weapon2 = new WeaponItem(world, WEAPONITEM1, "Sword", 20, "Sword with 20 Physical Attack point", text, "media/model/sword.obj");
	Item* weapon3 = new WeaponItem(world, WEAPONITEM1, "Long Sword", 30, "Long Sword with 30 Physical Attack point", text, "media/model/sword.obj");

	((WeaponItem*)weapon1)->GetNode()->setVisible( false );
	((WeaponItem*)weapon2)->GetNode()->setVisible( false );
	((WeaponItem*)weapon3)->GetNode()->setVisible( false );

	/*tmpBox.push_back(std::make_pair(hp, 2));
	tmpBox.push_back(std::make_pair(md1, 5));
	tmpBox.push_back(std::make_pair(md2, 10));
	tmpBox.push_back(std::make_pair(md3, 12));
	tmpBox.push_back(std::make_pair(md4, 11));
	tmpBox.push_back(std::make_pair(xItem, 0));
	tmpBox.push_back(std::make_pair(weapon1, 1));
	tmpBox.push_back(std::make_pair(weapon2, 2));
	tmpBox.push_back(std::make_pair(weapon3, 1));*/

	tmpBox.push_back(std::make_pair(hp, 0));
	tmpBox.push_back(std::make_pair(md1, 0));
	tmpBox.push_back(std::make_pair(md2, 0));
	tmpBox.push_back(std::make_pair(md3, 0));
	tmpBox.push_back(std::make_pair(md4, 0));
	tmpBox.push_back(std::make_pair(xItem, 0));
	tmpBox.push_back(std::make_pair(weapon1, 0));
	tmpBox.push_back(std::make_pair(weapon2, 0));
	tmpBox.push_back(std::make_pair(weapon3, 0));

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
	//node->setMaterialType(irr::video::EMT_SOLID);
	node->setMaterialTexture(0, driver.getTexture( defaultTexture ));
	node->setMaterialTexture(1, driver.getTexture( "media/model/PedroTextureShade.tga" ));
	//node->setDebugDataVisible( irr::scene::EDS_BBOX);

	weaponNode = smgr.addMeshSceneNode(
		smgr.getMesh("media/model/swordyy.obj"),//Mastersword_v003.obj or sword.obj
		//node->getJointNode("RightFingerBase"),
		node->getJointNode("RightHandThumb3"),
		0,
		irr::core::vector3df(0,0,0),
		irr::core::vector3df(0,0,0),
		irr::core::vector3df(0.05, 0.05, 0.05)
	);

	irr::scene::ISceneNode* sss = smgr.addSphereSceneNode(0.5);
	sss->setParent(node->getJointNode("RightHandThumb3"));

	Shader* Field = GEngine.GetShaderFactory().createShader( "media/shader/field.vert", "media/shader/field.frag", 1, irr::video::EMT_TRANSPARENT_ADD_COLOR);
	FireBall = GEngine.GetShaderFactory().createShader( "media/shader/fireball_2.vert", "media/shader/fireball_2.frag", 1, irr::video::EMT_SOLID);
	Ice = GEngine.GetShaderFactory().createShader( "media/shader/Ice.vert", "media/shader/Ice.frag", 0, irr::video::EMT_SOLID);
	Lightning = GEngine.GetShaderFactory().createShader( "media/shader/Lightning.vert", "media/shader/Lightning.frag", 1, irr::video::EMT_TRANSPARENT_ADD_COLOR);
	Cyclone = GEngine.GetShaderFactory().createShader( "media/shader/Cyclone.vert", "media/shader/Cyclone.frag", 1, irr::video::EMT_TRANSPARENT_ADD_COLOR);
	irr::scene::IMesh* ATmesh = smgr.addSphereMesh("", (node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter()).getLength() + 1 );
	ATFieldNode = smgr.addMeshSceneNode( ATmesh, node );
	ATFieldNode->setVisible( false );
	
	if(GEngine.GetShaderFactory().ShaderAvailable())
		ATFieldNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Field->GetShaderMaterial());
	else 
		ATFieldNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	
	ATFieldNode->setMaterialTexture(0, driver.getTexture("media/model/portal7.bmp"));
	ATFieldNode->setRotation(irr::core::vector3df(90,-90,0));

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
	endCallBack = new DeathAnimationEndCallBack( world, *this );

	aimVector = defaultAimVector;

	magic_timer = new boost::timer();

	combo_timer = new boost::timer();
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

void MainCharacter::SetCurrentWeapon(WeaponItem* currentWeapon)
{
	if( weaponNode )
			weaponNode->setVisible( false );

	if( currentWeapon )
	{
		_currentWeapon = currentWeapon;

		weaponNode = _currentWeapon->GetNode();
		weaponNode->setParent( node->getJointNode("RightHandThumb3") );
		weaponNode->setVisible( true );
		//weaponNode->setScale(irr::core::vector3df(0.05, 0.05, 0.05));
	}
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
	static irr::s32 lastCombo = -1;

	if( isAttacking() && lastCombo == GetCombo() )
		return;

	if( attacking )
	{
		action = EMCAS_ATTACK;

		irr::s32 startAttackFrame = -1;
		irr::s32 endAttackFrame = -1;
		switch( GetComboNum() )
		{
		case 1:
			startAttackFrame = MAIN_CHARACTER_ANIMATION_ATTACK1_START;
			endAttackFrame = MAIN_CHARACTER_ANIMATION_ATTACK1_END;
			break;
		case 2:
			startAttackFrame = MAIN_CHARACTER_ANIMATION_ATTACK2_START;
			endAttackFrame = MAIN_CHARACTER_ANIMATION_ATTACK2_END;
			break;
		case 3:
			startAttackFrame = MAIN_CHARACTER_ANIMATION_ATTACK3_START;
			endAttackFrame = MAIN_CHARACTER_ANIMATION_ATTACK3_END;
			break;
		default:
			startAttackFrame = MAIN_CHARACTER_ANIMATION_ATTACK1_START;
			endAttackFrame = MAIN_CHARACTER_ANIMATION_ATTACK1_END;
			break;
		}
		
		node->setCurrentFrame( startAttackFrame );
		node->setFrameLoop( startAttackFrame, endAttackFrame );
		node->setLoopMode( false );
		node->setAnimationEndCallback( attackCallBack );

		ATFieldNode->setVisible( false );
	}
}

void MainCharacter::setCasting( bool casting )
{
	if( isCasting())
		return;

	if( casting && GetCurrentMagic() != NULL && GetCurrentMagic()->use() )
	{
		action = EMCAS_MAGICATTACK;
		
		MagicBonusValue = GetMagicLevel();

		irr::core::vector3df magicPos = world.GetRobot()->GetNodePosition();
		magicPos = world.GetRobot()->GetNodePosition();

		MagicNode->setPosition(magicPos);
		MagicNode->setVisible(true);
		
		irr::scene::ISceneManager& smgr = world.GetSceneManager();
		irr::core::vector3df targetPos = getTargetPos();
		magicFlyTime = (targetPos - magicPos).getLength() / 0.1;
		if(_currentMagic->getItemName() != "Ice"){
			irr::scene::ISceneNodeAnimator* anim = smgr.createFlyStraightAnimator(
				magicPos,
				targetPos,
				magicFlyTime
				);
			MagicNode->addAnimator(anim);
			anim->drop();
		}else{
			MagicNode->setPosition(targetPos);
		}

		

		magic_timer->restart();
		if (monsterTarget)
			MagicFired = true;

		setIdle();
		ATFieldNode->setVisible( false );
	}
}

irr::core::vector3df MainCharacter::getTargetPos()
{
	if (targetIndicator->isVisible())
	{
		monsterTarget->GetNode().updateAbsolutePosition();
		irr::core::vector3df targetPos = monsterTarget->GetNode().getAbsolutePosition();
		return targetPos;
	}
	else
	{
		return world.GetRobot()->GetNode().getAbsolutePosition() + GetFaceVector() * GetRadius().getLength() * 10;
	}
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

bool MainCharacter::isDieing() const
{
	return action == EMCAS_DIEING;
}

// updates the player every fram with the elapsed time since last frame
void MainCharacter::Tick( irr::f32 delta )
{
	if( IsDead() )
	{
		action = EMCAS_DIEING;
		node->setLoopMode( false );
		node->setCurrentFrame(MAIN_CHARACTER_ANIMATION_DEAD_START);
		node->setFrameLoop(MAIN_CHARACTER_ANIMATION_DEAD_START, MAIN_CHARACTER_ANIMATION_DEAD_END);
		node->setAnimationEndCallback(endCallBack);

		return;
	}
	else if( isDieing() )
	{
		return;
	}

	if( !isAttacking() )
	{
		DoInput(delta);
	}
	if(MagicNode != NULL && _currentMagic->getItemName() == "Ice"){
		if(magic_timer->elapsed()<=5.0)
			MagicNode->setScale(irr::core::vector3df(20,20,20)* magic_timer->elapsed()*5 );
	
		if(magic_timer->elapsed()>7.0){
			MagicNode->setVisible(false);
		}
	}
	node->setRotation( rotation );
	irr::core::vector3df playerPos = node->getPosition();
	playerPos += faceVector * delta * translation.Z;
	node->setPosition( playerPos );
	translation.Z = 0;
}

void MainCharacter::DoInput(irr::f32 delta)
{
	if (combo_timer->elapsed() > 1.0)
		SetCombo(false);
	irr::f32 comboValue;
	switch ( ((MainCharacter&)world.GetCurrentPlayer()).GetComboNum() )
	{
		case 2:
			comboValue = 1.2;
			break;
		case 3:
			comboValue = 1.5;
			break;
		case 4:
			comboValue = 2;
			break;
		default:
			comboValue = 1.0;
	}
	InputEventReceiver& receiver = GEngine.GetReceiver();

	if (magicFlyTime != -1 && magic_timer->elapsed()*1000 > magicFlyTime)
	{
		if (MagicFired)
		{
			MagicNode->setVisible(false);
			Monster* theTarget = monsterTarget;
			irr::s32 playerMAttk = GetMagicAttackPoint() * MagicBonusValue;
			irr::s32 monMDef = theTarget->GetMDef();
			std::cout << "Magic Level = " << GetMagicLevel() << std::endl;
			std::cout << "Player MAttk = " << playerMAttk << std::endl;
			std::cout << "Monster MDefence = " << monMDef << std::endl;
			irr::s32 damage = 0;
			if (playerMAttk - monMDef > 0 )
			{
				damage = playerMAttk - monMDef;
			}
			irr::s32 offset = damage/5 * (rand()%601)/300;
			std::cout << "Combo = " << GetComboNum() << std::endl;
			std::cout << "Damage = " << (damage-offset) * comboValue << std::endl;
			theTarget->ReceiveDamage( (damage-offset) * comboValue);
			SetCombo(false);
			SetComboNum(0);
			MagicFired = false;
		}
	}
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
		if (_magiclevel < 3)
		{
			timeElapsed += delta;
			if (timeElapsed > 0.0001 / (1 + _magiclevel))
			{
				if( ++_magicChargeProgress % 100 == 0)
					++_magiclevel;

				timeElapsed = 0;
			}
		}
	}
	else if( receiver.keyReleased(irr::KEY_KEY_C) )
	{
		if(_magiclevel >= 1 && targetIndicator->isVisible())
		{
			++_comboNum;
			setCasting( true );
		}
		_charging = _magiclevel = _magicChargeProgress = 0;
		return;
	}

	if( receiver.keyReleased(irr::KEY_KEY_Z) )
	{
		if (!GetCombo())
		{
			if (targetIndicator->isVisible())
			{
				SetCombo(true);
				++_comboNum;
				combo_timer->restart();
			}
		}
		else
		{
			if (combo_timer->elapsed() < 1.0)
			{
				if (_comboNum < 3)
				{
					++_comboNum;
					combo_timer->restart();
				}
				else
				{
					SetCombo(false);
					_comboNum = 0;
				}
			}
			else
			{
				SetCombo(false);
				_comboNum = 0;
			}
		}

		setAttacking( true );
		return;
	}

	irr::core::vector3df playerTranslation(0, 0, 0); // translation vector
	irr::core::vector3df playerRotation(0, 0, 0); // rotation vector

	bool move = false; // need to update the player's position?
	bool backward = false; // moving backward?

	//! moving forward if up arrow is hold down.
	if( receiver.keyDown(irr::KEY_UP) )
	{
		//! moving forward left.
		if( receiver.keyDown(irr::KEY_LEFT) && receiver.keyUp(irr::KEY_RIGHT) )
		{
			if( aimVector.getHorizontalAngle().Y - faceVector.getHorizontalAngle().Y != 45 )
			{
				faceVector = aimVector;
				faceVector.rotateXZBy( 45, irr::core::vector3df(0, 0, 0) );
				faceVector.normalize();
			}
		}
		//! moving forward right.
		else if( receiver.keyDown(irr::KEY_RIGHT) && receiver.keyUp(irr::KEY_LEFT) )
		{
			if( aimVector.getHorizontalAngle().Y - faceVector.getHorizontalAngle().Y != -45 )
			{
				faceVector = aimVector;
				faceVector.rotateXZBy( -45, irr::core::vector3df(0, 0, 0) );
				faceVector.normalize();
			}

		}
		//! moving forward directly
		else
		{
			if(faceVector != aimVector)
			{
				faceVector = aimVector;
				faceVector.normalize();
			}
		}
		move = true;
	}
	//! moving backward if down arrow is hold down.
	else if( receiver.keyDown(irr::KEY_DOWN) )
	{
		if( faceVector != aimVector )
		{
			faceVector = aimVector;
			faceVector.normalize();
		}

		backward = move = true;
	}
	// moving left if left arrow is hold down
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
	// moving right if right arrow is hold down
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

	// rotate the view as well as the player to right if D is hold down.
	if( receiver.keyDown(irr::KEY_KEY_D) )
	{
		aimVector.rotateXZBy(-5, irr::core::vector3df(0, 0, 0) );
		aimVector.normalize();
	}
	// rotate the view as well as the player to left if A is hold down.
	else if( receiver.keyDown(irr::KEY_KEY_A) )
	{
		aimVector.rotateXZBy(5, irr::core::vector3df(0, 0, 0) );
		aimVector.normalize();
	}

	// rotate the player
	playerRotation.Y = floor( faceVector.getHorizontalAngle().Y - defaultAimVector.getHorizontalAngle().Y );
	SetRotation( playerRotation );

	if(move)
	{
		// run in the determinted direction if SPACEBAR is hold down.
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

		// make the player move backward by inversing the translation speed.
		if( backward )
			playerTranslation.Z = -playerTranslation.Z;

		SetTranslation( playerTranslation );

		return;
	}

	// if now control key is hold down or pressed, set the player back to idle.
	setIdle();
}

void MainCharacter::ReceiveDamage( irr::f32 value )
{
	// if the player is in god mode, no damage will be received.
	if( godMode )
		return;

	// boundary check
	if( health - value < 0 )
	{
		health = 0;

		// the player died
		action = EMCAS_DEAD;
	}
	else
	{
		health -= value;

		// randomly shout for hurt.
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
	// the next target to be locked
	Monster* nextTarget = NULL;

	// get all the monsters
	int numberOfMonster = world.GetMonsters().size();

	int currentTargetPos = -1;

	// find the current target in the monster array, if needed
	if( monsterTarget )
	{
		// hide the health bar as the next target is possibly not the current target.
		monsterTarget->setHealthBarVisible( false );

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
				world.GetMonsters()[(currentTargetPos+j)%numberOfMonster]->GetRadius().getLength() + GetRadius().getLength() * 10)
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

		nextTarget->setHealthBarVisible( true );
	}
	else
	{
		monsterTarget = NULL;
		targetIndicator->setParent( world.GetSceneManager().getRootSceneNode() );
		targetIndicator->setVisible( false );
	}
}

void MainCharacter::SetCurrentMagic(MDiscItem* currentMagic) {	
	_currentMagic = currentMagic;
	irr::video::IVideoDriver& driver = GEngine.GetDriver();
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	if(_currentMagic == NULL)
		return;

	if( _currentMagic->getItemName() == "Fire" ){
		std::cout<<"Fire\n";
		irr::scene::IMesh* Magicmesh = smgr.addSphereMesh("", 10 );
		MagicNode = smgr.addMeshSceneNode( Magicmesh );
		MagicNode->setMaterialFlag( irr::video::EMF_LIGHTING, true );
		MagicNode->setVisible( false );	
		if(GEngine.GetShaderFactory().ShaderAvailable())
			MagicNode->setMaterialType((irr::video::E_MATERIAL_TYPE)FireBall->GetShaderMaterial());
		else
			MagicNode->setMaterialType(irr::video::EMT_SOLID);
		MagicNode->setMaterialTexture(0, driver.getTexture("media/model/FireBase.tga"));
	//	MagicNode->setMaterialTexture(1, driver.getTexture("media/model/Flame.tga"));
	}else if( _currentMagic->getItemName() == "Ice" ){
		std::cout<<"Ice\n";
		
		irr::scene::ISkinnedMesh* Magicmesh = (irr::scene::ISkinnedMesh*)(smgr.getMesh( "media/model/ice.obj" ));
		MagicNode = smgr.addMeshSceneNode( Magicmesh );
		MagicNode->setScale(irr::core::vector3df(10.0,10.0,10.0) );
		MagicNode->setMaterialFlag( irr::video::EMF_LIGHTING, true );
		MagicNode->setVisible( false );	
		if(GEngine.GetShaderFactory().ShaderAvailable())
			MagicNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Ice->GetShaderMaterial());
		else
			MagicNode->setMaterialType(irr::video::EMT_SOLID);
	}else if( _currentMagic->getItemName() == "Lightning" ){
		std::cout<<"Lightning\n";
		irr::scene::IMesh* Magicmesh = smgr.addSphereMesh("", 10 );
		MagicNode = smgr.addMeshSceneNode( Magicmesh );
		MagicNode->setMaterialFlag( irr::video::EMF_LIGHTING, true );
		MagicNode->setVisible( false );	
		if(GEngine.GetShaderFactory().ShaderAvailable())
			MagicNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Lightning->GetShaderMaterial());
		else
			MagicNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		MagicNode->setMaterialTexture(0, driver.getTexture("media/model/base.tga"));
	}else if( _currentMagic->getItemName() == "Cyclone" ){
		std::cout<<"Cyclone\n";
		irr::scene::IMesh* Magicmesh = smgr.addSphereMesh("", 10 );
		MagicNode = smgr.addMeshSceneNode( Magicmesh );
		MagicNode->setMaterialFlag( irr::video::EMF_LIGHTING, true );
		MagicNode->setVisible( false );	
		if(GEngine.GetShaderFactory().ShaderAvailable())
			MagicNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Cyclone->GetShaderMaterial());
		else
			MagicNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		MagicNode->setMaterialTexture(0, driver.getTexture("media/model/water.jpg"));
	}
}

void MainCharacter::SetTarget( Monster* newTarget )
{
	if( monsterTarget )
	{
		monsterTarget = newTarget;
		if( monsterTarget )
		{
			targetIndicator->setParent( &monsterTarget->GetNode() );
			targetIndicator->setPosition( irr::core::vector3df(0, monsterTarget->GetNode().getBoundingBox().MaxEdge.Y + 5, 0 ) );
		}
		else
		{
			targetIndicator->setParent( world.GetSceneManager().getRootSceneNode() );
			targetIndicator->setVisible( false );
		}
	}
}

void MainCharacter::AttackAnimationEndCallBack::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* theNode)
{
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

			irr::f32 comboValue;
			switch ( ((MainCharacter&)world.GetCurrentPlayer()).GetComboNum() )
			{
				case 2:
					comboValue = 1.2;
					break;
				case 3:
					comboValue = 1.5;
					break;
				case 4:
					comboValue = 2;
					break;
				default:
					comboValue = 1.0;
			}

			std::cout << "Combo = " << ((MainCharacter&)world.GetCurrentPlayer()).GetComboNum() << std::endl;
			std::cout << "Damage = " << (damage-offset) * comboValue << std::endl;
			theTarget->ReceiveDamage( (damage-offset) * comboValue);
		}
	}
	else
	{
		irr::core::array<Monster*> monsters = world.GetMonsters();
		irr::u32 numberOfMonsters = monsters.size();

		irr::core::vector3df diff;
		irr::core::vector3df faceVector = theMainCharacter.GetFaceVector();
		irr::s32 faceVectorHY = faceVector.getHorizontalAngle().Y;
		irr::s32 angleDiff = -40;
		irr::s32 damageByLevel = theMainCharacter.GetLevel();
		irr::s32 damage = damageByLevel;

		for( irr::u32 i = 0; i < numberOfMonsters; ++i )
		{
			if( CollisionHelper::CheckProximity2D(
				monsters[i]->GetNode().getPosition(),
				theMainCharacter.GetNodePosition(),
				monsters[i]->GetRadius().getLength() + theMainCharacter.GetRadius().getLength() - 1
				)
			)
			{
				diff = monsters[i]->GetNode().getPosition() - theMainCharacter.GetNodePosition();

				angleDiff = faceVectorHY - diff.getHorizontalAngle().Y;
				
				if( angleDiff < 10 && angleDiff > -10 )
				{
					damage = damageByLevel * 2;
				}
				else
				{
					damage = damageByLevel;
				}
				
				irr::s32 offset = damage / 5 * ( rand()%601 ) / 300;

				irr::f32 comboValue;
				switch ( ((MainCharacter&)world.GetCurrentPlayer()).GetComboNum() )
				{
					case 2:
						comboValue = 1.2;
						break;
					case 3:
						comboValue = 1.5;
						break;
					case 4:
						comboValue = 2;
						break;
					default:
						comboValue = 1.0;
				}

				std::cout << "Combo = " << ((MainCharacter&)world.GetCurrentPlayer()).GetComboNum() << std::endl;
				std::cout << "Damage = " << (damage - offset) * comboValue << std::endl;
				monsters[i]->ReceiveDamage( (damage-offset) * comboValue );
			}
		}
	}

	theMainCharacter.setIdle();
	theNode->setCurrentFrame( MAIN_CHARACTER_ANIMATION_IDLE_START );
}

void MainCharacter::DeathAnimationEndCallBack::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* theNode)
{
	world.requestGameOver();
	//world.requestGameVictory();
}
