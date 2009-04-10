#include "MainCharacter.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
/*#include "DynamiteProjectile.h"
#include "SnowballProjectile.h"
#include "LandMine.h"*/
#include "InputEventReceiver.hpp"
#include "FloorDecalSceneNode.h"
#include "ProgressCircle.hpp"
#include <cmath>
#include <iostream>

extern GameEngine* GEngine;

// Parameters specifying default parameters
static const irr::core::vector3df		defaultPosition = irr::core::vector3df(150,50,20);
static const irr::core::vector3df		defaultRotation = irr::core::vector3df(0, 0, 0);

static const irr::c8*		MAIN_CHARACTER_MODEL  = "media/model/Pedro.x";
static const irr::c8*		MAIN_CHARACTER_SHADOWTEXTURE = "mdeia/model/MainTexutre1.png";
static const irr::c8*		MAIN_CHARACTER_vsFileName = "model/shader/trial.vert"; // filename for the vertex shader
static const irr::c8*		MAIN_CHARACTER_psFileName = "model/shader/trial.frag"; // filename for the pixel shader

static const irr::c8*		defaultTexture = "media/model/MainTexutre1.png";
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
static const irr::u32		MAIN_CHARACTER_ANIMATION_ATTACK_START = 125;
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
MainCharacter::MainCharacter( GameWorld& gameWorld, irr::video::IVideoDriver& driver )
	:Player(gameWorld),node(NULL),
	collisionAnimator(NULL),
	shadowNode(NULL),
	action(EMCAS_IDLE),
	moveState(EMCMS_IDLE),
	prevMoveState(EMCMS_IDLE),
	rotationState(EMCRS_IDLE),
	walkStopState(EMCMS_IDLE),
	walkStopFrameNumber(0.0f),
	throwFillupTimer( 0.0f ),
	bDoFillup( false ),
	world(gameWorld),
	sfxTimer(12),
	_healthBar(NULL),
	attackCallBack(NULL)
{
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
	node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	node->setMaterialTexture(0, driver.getTexture( defaultTexture ));
	node->setDebugDataVisible( irr::scene::EDS_BBOX);

	// setup player collision with the world
	RecreateCollisionResponseAnimator();

	// create a triangle selector for player
	irr::scene::ITriangleSelector* triangleSelector = world.GetSceneManager().createOctTreeTriangleSelector( node->getMesh(), node );
	node->setTriangleSelector( triangleSelector );
	triangleSelector->drop();
	triangleSelector = NULL;

	// setup player shadow
	shadowNode = GEngine->addFloorDecalSceneNode(node, irr::core::dimension2d<irr::f32>(0, 0));
	shadowNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	shadowNode->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	shadowNode->setMaterialTexture(0, driver.getTexture(MAIN_CHARACTER_SHADOWTEXTURE));

	// setup the player health bar
	_healthBar = new ProgressCircle(node, & (world.GetSceneManager()), 2222, world.GetSceneManager().getSceneCollisionManager());

	attackCallBack = new AttackAnimationEndCallBack( *this );

	aimVector = defaultAimVector;

	// setup snow steps sound effect
	//	sfxFootstep = GEngine->GetSoundEngine().play2D( "../audio/sfx/snowstepsrun.mp3", true, false, true );
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
	smgr.addToDeletionQueue( shadowNode );

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

	// set the rotation state
	if(rot.Y > 0.0f)
		rotationState = EMCRS_RIGHT;
	else if(rot.Y < 0.0f)
		rotationState = EMCRS_LEFT;
	else
		rotationState = EMCRS_IDLE;
}

void MainCharacter::InitShader(irr::core::vector3df* lightPosition)
{
	irr::s32 newMaterialType = 0;

	irr::video::IGPUProgrammingServices* gpuServices = GEngine->GetDriver().getGPUProgrammingServices();
	if(gpuServices)
	{
		MyMainCharacterShaderCallBack *mc = new MyMainCharacterShaderCallBack(&(GEngine->GetDevice()), lightPosition);

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

	action = EMCAS_IDLE;
}

void MainCharacter::setDefending( bool defending )
{
	action = defending ? EMCAS_DEFEND : EMCAS_IDLE;
}

void MainCharacter::setMoving( bool moving )
{
	if( isMoving() )
		return;

	if( moving )
	{
		node->setFrameLoop( MAIN_CHARACTER_ANIMATION_WALK_FORWARD_START, MAIN_CHARACTER_ANIMATION_WALK_FORWARD_END );
		node->setLoopMode( true );

		action = EMCAS_MOVE;
	}
}

void MainCharacter::setAttacking( bool attacking )
{
	if( attacking )
	{
		action = EMCAS_ATTACK;
		node->setCurrentFrame( MAIN_CHARACTER_ANIMATION_ATTACK_START );
		node->setFrameLoop( MAIN_CHARACTER_ANIMATION_ATTACK_START, MAIN_CHARACTER_ANIMATION_ATTACK_END );
		node->setLoopMode( false );
		//node->setAnimationEndCallback( attackCallBack );
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
	DoInput();

	node->setRotation( rotation );
	irr::core::vector3df playerPos = node->getPosition();
	playerPos += faceVector * delta * translation.Z;
	node->setPosition( playerPos );

	/*if( isDefending() )
		return;

	if( isRunning() )
		std::cout << "Still running" << std::endl;

	// player's rotation update, must happen before the position updates
	aimVector.set( 1, 0, 0 );
	aimVector.rotateXZBy( -rotation.Y, irr::core::vector3df( 0, 0, 0 ) );
	aimVector.normalize();

	// player's movement
	switch(moveState)
	{
		case EMCMS_IDLE:
		{
			velApprox.set( 0, 0, 0 );

			// setup animation
			if( prevMoveState != EMCMS_IDLE )
			{
				setIdle();
			}	
			break;
		}
		case EMCMS_FORWARD:
		case EMCMS_BACK:
		{
			irr::core::vector3df playerPos = node->getPosition();

			// calculate "right" vector
			irr::core::vector3df rightVector = aimVector.crossProduct(irr::core::vector3df(0,1,0));
			rightVector.normalize();

			irr::core::vector3df savePos = playerPos;

			// translate player
			playerPos += rightVector * delta * translation.X;
			playerPos += aimVector * delta * translation.Z;
			node->setPosition( playerPos );

			velApprox = playerPos - savePos;

			break;
		}

		default:
			break;
	}*/

	//sfxTimer++;
}

void MainCharacter::DoInput()
{
	InputEventReceiver& receiver = GEngine->GetReceiver();

	irr::core::vector3df playerTranslation(0, 0, 0);
	irr::core::vector3df playerRotation(0, 0, 0);

	bool move = false;

	if( receiver.keyDown(irr::KEY_KEY_W) )
	{
		if(faceVector != aimVector)
		{
			//Player::SetTranslation( irr::core::vector3df(0, 0, 20) );
			faceVector = aimVector;
			faceVector.normalize();
		}

		move = true;
	}
	if( receiver.keyDown(irr::KEY_KEY_S) )
	{
		if(faceVector != -aimVector)
		{
			//Player::SetTranslation( irr::core::vector3df(0, 0, -20) );
			faceVector = aimVector;
			faceVector.rotateXZBy( 180, irr::core::vector3df(0, 0, 0) );
			faceVector.normalize();
		}

		move = true;
	}

	if( receiver.keyDown(irr::KEY_KEY_A) )
	{
		//Player::SetTranslation( irr::core::vector3df(0, 0, 20) );
		if( aimVector.getHorizontalAngle().Y - faceVector.getHorizontalAngle().Y != 90 )
		{
			faceVector = aimVector;
			faceVector.rotateXZBy( 90, irr::core::vector3df(0, 0, 0) );
			faceVector.normalize();
		}

		move = true;
	}

	if( receiver.keyDown(irr::KEY_KEY_D) )
	{
		//Player::SetTranslation( irr::core::vector3df(0, 0, 20) );
		if( aimVector.getHorizontalAngle().Y - faceVector.getHorizontalAngle().Y != -90 )
		{
			faceVector = aimVector;
			faceVector.rotateXZBy( -90, irr::core::vector3df(0, 0, 0) );
			faceVector.normalize();
		}

		move = true;
	}

	if( receiver.keyDown(irr::KEY_KEY_E) )
	{
		aimVector.rotateXZBy(-5, irr::core::vector3df(0, 0, 0) );
		aimVector.normalize();
	}

	if( receiver.keyDown(irr::KEY_KEY_Q) )
	{
		aimVector.rotateXZBy(5, irr::core::vector3df(0, 0, 0) );
		aimVector.normalize();
	}

	if(move)
	{
		if( receiver.keyDown(irr::KEY_SHIFT) )
		{
			playerTranslation.Z = 45;
			setRunning( true );
		}
		else
		{
			playerTranslation.Z = 15;
			setMoving( true );
		}
	}
	else
	{
		setIdle();
	}
	
	playerRotation.Y = floor( faceVector.getHorizontalAngle().Y - defaultAimVector.getHorizontalAngle().Y );

	SetRotation( playerRotation );
	SetTranslation( playerTranslation );

	/*if(receiver.keyDown(irr::KEY_KEY_M))
	{
		setDefending( true );
		return;
	}

	if(receiver.keyReleased(irr::KEY_SPACE) || receiver.mousePressed(InputEventReceiver::LEFT))
	{
		setAttacking( true );
		return;
	}

	irr::core::vector3df playerTranslation(0, 0, 0);
	irr::core::vector3df playerRotation(0, 0, 0);

	if(receiver.keyDown(irr::KEY_KEY_W))
	{ 
		playerTranslation.Z = -20;
		if( !isMoving())
			setMoving( true );
	}
	else if(receiver.keyDown(irr::KEY_KEY_S))
	{
		playerTranslation.Z = 20;
		if( !isMoving())
			setMoving( true );
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
		if( !isRunning() )
			setRunning( true );
	}

	if( receiver.keyReleased( irr::KEY_SHIFT ) )
	{
		setRunning( false );
	}*/
}

// updates the power of the throw meter
void MainCharacter::UpdateThrowMeter( irr::f32 delta )
{
	if( bDoFillup )
	{
		throwFillupTimer += delta;
	}
}

void MainCharacter::ReceiveDamage( irr::f32 value )
{
	if( godMode )
		return;

	if( action == EMCAS_DEFEND )
	{
		std::cout<<"defending"<<std::endl;
		value = value / 4;
	}

	health -= value;

	_healthBar->setProgress( health );

	if( health <= 0 )
	{
		//moveState = EMCMS_DEAD;
		action = EMCAS_DEAD;
		moveState = EMCMS_IDLE;
		rotationState = EMCRS_IDLE;
	}
	else
	{
		switch( rand() % 2 )
		{
		case 0:
//			GEngine->GetSoundEngine().play2D("../audio/sfx/playerhurt1.mp3");
			break;
		case 1:
//			GEngine->GetSoundEngine().play2D("../audio/sfx/playerhurt2.mp3");
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

// unbuffered mouse input 
void MainCharacter::OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent )
{
	// not allow player to throw dynamites except during gameplay
	EGameState gameState = world.GetGameState();
	if( gameState != state_GAMEPLAY && world.GetGameState() != state_WAVE_FINISHED )
		return;

	if( mouseEvent.Event == irr::EMIE_LMOUSE_PRESSED_DOWN )
	{
		// start filling up the throw power meter
		//check( !bDoFillup );
		bDoFillup = true;
	}
	else if( mouseEvent.Event == irr::EMIE_LMOUSE_LEFT_UP )
	{
		// get the first available projectile
/*		DynamiteProjectile* projectile = world.GetFirstAvailableDynamite();
		if( projectile && ammo > 0 )
		{
			// check if we're not throwing too soon
			static irr::u32 lastThrowTime = 0;
			irr::u32 currTime = GEngine->GetRealTime();
			if( currTime - lastThrowTime > MIN_TIME_BETWEEN_THROWS || godMode )
			{
				// calculate the throw power, in percentage points
				irr::f32 power = throwFillupTimer / THROW_METER_FILLUP_TIME;
				ShootDynamite( power, *projectile );
				lastThrowTime = currTime;
			}
		}
 */
		//check(bDoFillup);
		bDoFillup = false;
		throwFillupTimer = 0.0f;
	}
}

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
	CFloorDecalSceneNode* footStepNode = GEngine->addFloorDecalSceneNode(NULL, core::dimension2d<irr::f32>(4.5, 4.5));
	check(shadowNode);
	footStepNode->setMaterialFlag(video::EMF_LIGHTING, false);
	footStepNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	footStepNode->setMaterialTexture(0, GEngine->GetDriver().getTexture(CHARACTER_RIGHT_FOOTSTEP_TEXTURE));
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
	CFloorDecalSceneNode* footStepNode = GEngine->addFloorDecalSceneNode(NULL, core::dimension2d<irr::f32>(4.5, 4.5));
	check(shadowNode);
	footStepNode->setMaterialFlag(video::EMF_LIGHTING, false);
	footStepNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	footStepNode->setMaterialTexture(0, GEngine->GetDriver().getTexture(CHARACTER_LEFT_FOOTSTEP_TEXTURE));
	footStepNode->setRotation(node->getRotation() + irr::core::vector3df(0.f,180.f,0.f));
	footStepNode->setPosition(pos);

	// delete the node after some time
	scene::ISceneNodeAnimator* anim = world.GetSceneManager().createDeleteAnimator( FOOTSTEP_DURATION );
	footStepNode->addAnimator( anim );
}
*/

void MainCharacter::AttackAnimationEndCallBack::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* theNode)
{
	theMainCharacter.setIdle();
	theNode->setCurrentFrame( MAIN_CHARACTER_ANIMATION_IDLE_START );
}