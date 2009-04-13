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

// Parameters specifying default parameters
//static const irr::core::vector3df		defaultPosition = irr::core::vector3df(150,50,20);
static const irr::core::vector3df		defaultPosition = irr::core::vector3df(0,10,450);
static const irr::core::vector3df		defaultRotation = irr::core::vector3df(0, 0, 0);

static const irr::c8*		MAIN_CHARACTER_MODEL  = "media/model/Pedro.x";
static const irr::c8*		MAIN_CHARACTER_SHADOWTEXTURE = "mdeia/model/PedroTexture.png";
static const irr::c8*		MAIN_CHARACTER_vsFileName = "model/shader/trial.vert"; // filename for the vertex shader
static const irr::c8*		MAIN_CHARACTER_psFileName = "model/shader/trial.frag"; // filename for the pixel shader

static const irr::c8*		defaultTexture = "media/model/PedroTexture.png";
static const irr::f32		ANIMATION_SPEED = 24;
static const irr::f32		ANIMATION_TRANSITION_BLEND_TIME = 0.2f;

static irr::core::vector3df defaultAimVector = irr::core::vector3df(0, 0, -1.0);

// main character's animation information
static const irr::u32		MAIN_CHARACTER_ANIMATION_IDLE_START = 1;
static const irr::u32		MAIN_CHARACTER_ANIMATION_IDLE_END = 1;
static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_FORWARD_START = 4;
static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_FORWARD_END = 30;
static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_BACK_START = 38;
static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_BACK_END = 63;
//static const irr::u32		MAIN_CHARACTER_ANIMATION_RUN_START = 72;
static const irr::u32		MAIN_CHARACTER_ANIMATION_RUN_START = 80;
static const irr::u32		MAIN_CHARACTER_ANIMATION_RUN_END = 97;
static const irr::u32		MAIN_CHARACTER_ANIMATION_JUMP_START = -1;
static const irr::u32		MAIN_CHARACTER_ANIMATION_JUMP_END = -1;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK_START = 126;
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK_END = 139;
static const irr::u32		MAIN_CHARACTER_ANIMATION_DEAD_START = 104;
static const irr::u32		MAIN_CHARACTER_ANIMATION_DEAD_END = 124;
//static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_SIDESTEP_LEFT_START = 92;
//static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_SIDESTEP_LEFT_END = 121;
//static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_SIDESTEP_RIGHT_START = 62;
//static const irr::u32		MAIN_CHARACTER_ANIMATION_WALK_SIDESTEP_RIGHT_END = 91;

// frame numbers for footsteps
/*
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_FORWARD_LEFT_FOOTSTEP_FRAME = 2;
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_FORWARD_RIGHT_FOOTSTEP_FRAME = 17;
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_BACK_LEFT_FOOTSTEP_FRAME = 32;
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_BACK_RIGHT_FOOTSTEP_FRAME = 40;
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_BACK_LEFT_FOOTSTEP2_FRAME = 48;
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_SIDESTEP_LEFT_LEFT_FOOTSTEP_FRAME = 120;
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_SIDESTEP_LEFT_RIGHT_FOOTSTEP_FRAME = 107;
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_SIDESTEP_RIGHT_LEFT_FOOTSTEP_FRAME = 90;
static const irr::u32			MAIN_CHARACTER_ANIMATION_WALK_SIDESTEP_RIGHT_RIGHT_FOOTSTEP_FRAME = 75;
static const irr::u32			FOOTSTEP_DURATION = 6000;
*/

// constructor
MainCharacter::MainCharacter( GameEngine& gameEngine, GameWorld& gameWorld )
	:Player(gameEngine, gameWorld),
	node(NULL),
	weaponNode(NULL),
	ATFieldNode(NULL),
	collisionAnimator(NULL),
	action(EMCAS_IDLE),
	//throwFillupTimer( 0.0f ),
	bDoFillup( false ),
	world(gameWorld),
	_magicChargeProgress(0),
	sfxTimer(12),
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
	_currentMagic(NULL)
{
	//test1 = new Shader(&(GEngine.GetDevice()),"media/shader/opengl.vert", "media/shader/opengl.frag", 2, irr::video::EMT_SOLID, "MainCharacter");
	test1 = GEngine.GetShaderFactory().createShader( "media/shader/opengl.vert", "media/shader/opengl.frag", 2, irr::video::EMT_SOLID );

	irr::video::IVideoDriver& driver = GEngine.GetDriver();

	ItemCollection tmpBox;
	Item* hp = new HPItem(world, HPITEM, "HP Medicine", 50);
	Item* md1 = new MDiscItem(world, MDISCITEM, "Fire Ball", 10);	
	Item* md2 = new MDiscItem(world, MDISCITEM, "Ice Ball", 10);
	Item* md3 = new MDiscItem(world, MDISCITEM, "Lightning", 30);
	Item* md4 = new MDiscItem(world, MDISCITEM, "Cyclone", 40);
	Item* xItem = new XItem(world, XITEM, "X Item", 1);
	Item* weapon1 = new WeaponItem(world, WEAPONITEM1, "Knife", 10);
	Item* weapon2 = new WeaponItem(world, WEAPONITEM1, "Sword", 20);
	Item* weapon3 = new WeaponItem(world, WEAPONITEM1, "Long Sword", 30);
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
	node->setDebugDataVisible( irr::scene::EDS_BBOX);

	weaponNode = smgr.addMeshSceneNode(
		smgr.getMesh("media/model/sword.x"),
		node->getJointNode("RightFingerBase")
	);
	
	weaponNode->setScale(irr::core::vector3df(0.05, 0.05, 0.05));
	weaponNode->setRotation(irr::core::vector3df(5.000000, 20.000000, -90.000000));
	weaponNode->setPosition(irr::core::vector3df(-5.5, 2.5, -5.5));
	Shader* Field = GEngine.GetShaderFactory().createShader( "media/shader/field.vert", "media/shader/field.frag", 1, irr::video::EMT_TRANSPARENT_ADD_COLOR);
		//new Shader(&(GEngine.GetDevice()),"media/shader/field.vert", "media/shader/field.frag", 0, video::EMT_TRANSPARENT_ADD_COLOR, "field");
	irr::scene::IMesh* ATmesh = smgr.addSphereMesh("", (node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter()).getLength() + 1 );
	ATFieldNode = smgr.addMeshSceneNode( ATmesh, node );
	ATFieldNode->setVisible( false );
	ATFieldNode->setMaterialType((irr::video::E_MATERIAL_TYPE)Field->GetShaderMaterial());
	ATFieldNode->setMaterialTexture(0, driver.getTexture("media/model/portal7.bmp"));
	ATFieldNode->setRotation(irr::core::vector3df(90,-90,0));
	// setup player collision with the world
	RecreateCollisionResponseAnimator();

	// create a triangle selector for player
	irr::scene::ITriangleSelector* triangleSelector = world.GetSceneManager().createOctTreeTriangleSelector( node->getMesh(), node );
	node->setTriangleSelector( triangleSelector );
	triangleSelector->drop();
	triangleSelector = NULL;

	attackCallBack = new AttackAnimationEndCallBack( world, *this );

	aimVector = defaultAimVector;

	// setup snow steps sound effect
	//	sfxFootstep = GEngine.GetSoundEngine().play2D( "../audio/sfx/snowstepsrun.mp3", true, false, true );
	//	sfxFootstep->setVolume( 0 );
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
/*	if( sfxFootstep )
	{
		sfxFootstep->stop();
		sfxFootstep->drop();
		sfxFootstep = NULL;
	}
*/
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

void MainCharacter::InitShader(irr::core::vector3df* lightPosition)
{
	irr::s32 newMaterialType = 0;

	irr::video::IGPUProgrammingServices* gpuServices = GEngine.GetDriver().getGPUProgrammingServices();
	if(gpuServices)
	{
		MyMainCharacterShaderCallBack *mc = new MyMainCharacterShaderCallBack(&(GEngine.GetDevice()), lightPosition);

		newMaterialType = gpuServices->addHighLevelShaderMaterialFromFiles(
			MAIN_CHARACTER_vsFileName, "main", irr::video::EVST_VS_1_1,
			MAIN_CHARACTER_psFileName, "main", irr::video::EPST_PS_1_1,
			mc, irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);

		mc->drop();
	}

	node->setMaterialType( (irr::video::E_MATERIAL_TYPE) newMaterialType );
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

	if( receiver.keyDown(irr::KEY_KEY_X) )
	{
		setDefending( true );
		return;
	}

	if( receiver.keyReleased(irr::KEY_KEY_Z) )
	{
		setAttacking( true );
		return;
	}

	if( receiver.keyDown(irr::KEY_KEY_C) )
	{
		//std::cout << "Magic Level: " << GetMagicLevel() << std::endl;
		SetCharging( true );
		if (GetMagicLevel()<3)
		{
			SetChargingProgress(GetChargingProgress()+1);
			if (GetChargingProgress()%100==0)
				SetMagicLevel(GetMagicLevel()+1);
		}
	}
	else
	{
		SetCharging( false );
		SetChargingProgress(0);
		SetMagicLevel(0);
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
		//if(faceVector != -aimVector)
		if( faceVector != aimVector )
		{
			faceVector = aimVector;
			//faceVector.rotateXZBy( 180, irr::core::vector3df(0, 0, 0) );
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
		if( receiver.keyDown(irr::KEY_SHIFT) && !backward )
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

	/*if( action == EMCAS_DEFEND )
	{
		std::cout<<"defending"<<std::endl;
		value = value / 4;
	}*/

	health -= value;

	if( health <= 0 )
	{
		//moveState = EMCMS_DEAD;
		action = EMCAS_DEAD;
	}
	else
	{
		switch( rand() % 2 )
		{
		case 0:
//			GEngine.GetSoundEngine().play2D("../audio/sfx/playerhurt1.mp3");
			break;
		case 1:
//			GEngine.GetSoundEngine().play2D("../audio/sfx/playerhurt2.mp3");
			break;
		}
	}
}

/*
// shoots a snowball from the current player location
void MainCharacter::ShootDynamite( irr::f32 power, DynamiteProjectile& projectile )
{
	check( ammo > 0 );
	if( !godMode )
		ammo--;

	// make sure its ok to throw this projectile
	check(projectile.GetDynamiteState() == state_DYNAMITE_IDLE);

	// make sure the power is between 0 and 1
	check( 0 <= power && power <= 1 );

	// start position for the dynamite
	irr::core::vector3df startPos = Position() + PROJECTILE_START_OFFSET;
	// start rotation for the dynamite
	irr::core::vector3df startRot = node->getRotation();

	// direction of the throw is the vector in the XZ plane from the player position to the camera aim target.
	// vector needs to be normalized
	irr::core::vector3df direction = GetAimVector();
	direction.Y = 0;
	direction.normalize();

	// to properly take the angle into account, we add tan(angle) to Y
	float rad = ( -MIN_XROT_ANGLE + rotation.X ) * ( PI / 180 ) * 0.8f;

	direction.Y = (irr::f32)tan(rad);
	direction.normalize();

	check(MAX_THROW_POWER > MIN_THROW_POWER);
	const irr::f32 speed = MIN_THROW_POWER + power * (MAX_THROW_POWER - MIN_THROW_POWER);
	projectile.Launch( startPos, startRot, direction, speed );
	DoLaunchProjectile();	
}
*/

/*
// shoots a snowball from the current player location
void MainCharacter::ShootSnowball( irr::f32 power, SnowballProjectile& projectile )
{
	// make sure its ok to throw this projectile
	check(projectile.GetSnowballState() == state_DYNAMITE_IDLE);

	// make sure the power is between 0 and 1
	check( 0 <= power && power <= 1 );

	// start position for the snowball
	irr::core::vector3df startPos = GetNodePosition() + PROJECTILE_START_OFFSET;
	// direction of the throw is the vector in the XZ plane from the player position to the camera aim target.
	// vector needs to be normalized
	irr::core::vector3df direction = GetAimVector();
	direction.Y = 0;
	direction.normalize();

	// to properly take the angle into account, we add tan(angle) to Y
	float rad = ( -MIN_XROT_ANGLE + rotation.X ) * ( PI / 180 );
	direction.Y = (irr::f32)tan(rad);
	direction.normalize();

	check(MAX_THROW_POWER > MIN_THROW_POWER);
	const irr::f32 speed = MIN_THROW_POWER + power * (MAX_THROW_POWER - MIN_THROW_POWER);
	projectile.Launch( startPos, direction, speed );
	DoLaunchProjectile();	
}
*/

/*
// makes the player put a landmine on the ground
void MainCharacter::PlaceMine( LandMine& mine )
{
	// make sure its ok to place this landmine
	check(mine.GetLandMineState() == state_LANDMINE_IDLE);
	// start position from where the landmine is dropped
	irr::core::vector3df startPos = GetNodePosition();
	mine.Place( startPos );

	// play a sound effect and do an animation
	DoLaunchProjectile();
}
*/

/*
// drops a player footprint on the ground
void MainCharacter::PlaceRightFootPrint()
{
	irr::core::vector3df forwardVector = aimVector*2;
	irr::core::vector3df rightVector = aimVector.crossProduct(irr::core::vector3df(0,1,0));
	// add some additioal scaling to the right vector so it falls in the place where the foot is
	rightVector *= 1.5;
	irr::core::vector3df pos = node->getAbsolutePosition() - rightVector + forwardVector;

	// create the texture node to paste on the ground
	CFloorDecalSceneNode* footStepNode = GEngine.addFloorDecalSceneNode(NULL, core::dimension2d<irr::f32>(4.5, 4.5));
	check(shadowNode);
	footStepNode->setMaterialFlag(video::EMF_LIGHTING, false);
	footStepNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	footStepNode->setMaterialTexture(0, GEngine.GetDriver().getTexture(CHARACTER_RIGHT_FOOTSTEP_TEXTURE));
	footStepNode->setRotation(node->getRotation() + irr::core::vector3df(0.f,180.f,0.f));
	footStepNode->setPosition(pos);

	// delete the node after some time
	scene::ISceneNodeAnimator* anim = world.GetSceneManager().createDeleteAnimator( FOOTSTEP_DURATION );
	footStepNode->addAnimator( anim );
}
*/

/*
void MainCharacter::PlaceLeftFootPrint()
{
	irr::core::vector3df forwardVector = aimVector*2;
	irr::core::vector3df rightVector = aimVector.crossProduct(irr::core::vector3df(0,1,0));
	// add some additioal scaling to the right vector so it falls in the place where the foot is
	rightVector *= 1.5;
	irr::core::vector3df pos = node->getAbsolutePosition() + rightVector + forwardVector;

	// create the texture node to paste on the ground
	CFloorDecalSceneNode* footStepNode = GEngine.addFloorDecalSceneNode(NULL, core::dimension2d<irr::f32>(4.5, 4.5));
	check(shadowNode);
	footStepNode->setMaterialFlag(video::EMF_LIGHTING, false);
	footStepNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	footStepNode->setMaterialTexture(0, GEngine.GetDriver().getTexture(CHARACTER_LEFT_FOOTSTEP_TEXTURE));
	footStepNode->setRotation(node->getRotation() + irr::core::vector3df(0.f,180.f,0.f));
	footStepNode->setPosition(pos);

	// delete the node after some time
	scene::ISceneNodeAnimator* anim = world.GetSceneManager().createDeleteAnimator( FOOTSTEP_DURATION );
	footStepNode->addAnimator( anim );
}
*/

void MainCharacter::AttackAnimationEndCallBack::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* theNode)
{
	irr::core::array<Actor*> actors = world.GetActors();
	irr::u32 actorsNum = actors.size();

	irr::core::line3df line;
	line.start = theMainCharacter.GetNodePosition();
	line.end = line.start - theMainCharacter.GetFaceVector() * theMainCharacter.GetRadius().getLength();

	for( irr::u32 i=0; i < actorsNum; ++i )
	{
		if( actors[i]->GetActorType() != ACTOR_ENEMY)
			continue;

		if(
			/*CollisionHelper::CheckProximity2D(
				theMainCharacter.GetNodePosition(),
				actors[i]->GetNode().getPosition(),
				theMainCharacter.GetRadius().getLength() + actors[i]->GetRadius().getLength() - 5.0
			)*/
			world.GetSceneManager().getSceneCollisionManager()->getSceneNodeFromRayBB(line)
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
	}

	theMainCharacter.setIdle();
	theNode->setCurrentFrame( MAIN_CHARACTER_ANIMATION_IDLE_START );
}