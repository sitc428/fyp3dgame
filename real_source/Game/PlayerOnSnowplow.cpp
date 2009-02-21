#include "PlayerOnSnowplow.h"
#include "Check.h"
#include "GameWorld.h"
#include "CollisionHelper.h"
#include "ParticleManager.h"
#include "GameEngine.h"
#include "FloorDecalSceneNode.h"

extern GameEngine* GEngine;

// Parameters specifying default parameters
static const vector3df		defaultPosition = vector3df(0,20,0);
static const vector3df		defaultRotation = vector3df(0,-90,0);

static const irr::c8*		SNOWPLOW_MODEL = "../art/characters/Snowplow/KidPlow.ms3d";
static const irr::c8*		CHARACTER_ON_SNOWPLOW_SHADOWTEXTURE = "../art/sfx/Flats/CharacterShadow.png";

static const f32			SNOWPLOW_SPEED_MULTIPLIER_FAST = 1.8f; // how much faster does the snowplow move compared to walking
static const f32			SNOWPLOW_SPEED_MULTIPLIER_SLOW = 0.3f; // how much slower does the snowplow move when dealing damage
static const f32			SNOWPLOW_DAMAGE_PER_SECOND = 5.f;

static const f32			SNOWPLOW_START_FLICKER_THRESHOLD = 5.f; // if the remaining snowplow time is below this threshold, start to flicker the player

static const f32			ANIMATION_SPEED = 45; // 45 FPS
static const f32			ANIMATION_TRANSITION_BLEND_TIME = 0.2f;

// player animation information
static const u32			PLAYER_ANIM_START = 1;
static const u32			PLAYER_ANIM_END = 30;

static const vector3df		LEFT_PARTICLE_NODE_OFFSET = vector3df(5.0f,5.0f,5.0f);
static const vector3df		RIGHT_PARTICLE_NODE_OFFSET = vector3df(5.0f,5.0f,-5.0f);
static const vector3df		LEFT_PARTICLE_EMITTER_DIRECTION = vector3df(0.0f,0.04f,0.03f);
static const vector3df		RIGHT_PARTICLE_EMITTER_DIRECTION = vector3df(0.0f,0.04f,-0.03f);

// angle in degrees of rotation on the x-axis for player/aiming
static const f32			MIN_XROT_ANGLE = -13.0f;
static const f32			MAX_XROT_ANGLE = 15.0f;

extern GameEngine* GEngine;

// constructor
PlayerOnSnowplow::PlayerOnSnowplow( GameWorld& gameWorld,
			    IVideoDriver& driver,
				ParticleManager& InParticleManager )
:	Player(gameWorld)
,	snowplow(NULL)
,	collisionAnimator(NULL)
,	shadowNode(NULL)
,	moveState(state_POS_MOVE_IDLE)
,	rotationState(state_POS_ROTATE_IDLE)
,	currTickDelta(0.0f)
,	bIsDealingDamage(false)
,	leftParticleNode(NULL)
,	rightParticleNode(NULL)
,	sfxTimer(5)
{
	ISceneManager& smgr = world.GetSceneManager();

	// setup the snowplow animated mesh node
	ISkinnedMesh* snowplowMesh = dynamic_cast<ISkinnedMesh*>(smgr.getMesh( SNOWPLOW_MODEL ));
	check(snowplowMesh);
	snowplow = smgr.addAnimatedMeshSceneNode( snowplowMesh );
	check( snowplow );	
	snowplow->setPosition( defaultPosition );
	snowplow->setRotation( defaultRotation );
	snowplow->setMaterialFlag( video::EMF_LIGHTING, true );

	// setup player shadow
	shadowNode = GEngine->addFloorDecalSceneNode(snowplow, core::dimension2d<f32>(15, 15));
	check(shadowNode);
	shadowNode->setMaterialFlag(video::EMF_LIGHTING, false);
	shadowNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	shadowNode->setMaterialTexture(0, driver.getTexture(CHARACTER_ON_SNOWPLOW_SHADOWTEXTURE));

	RecreateCollisionResponseAnimator();

	// create a triangle selector for player
	ITriangleSelector* triangleSelectorSnowplow = smgr.createTriangleSelectorFromBoundingBox( snowplow );
	check( triangleSelectorSnowplow );
	snowplow->setTriangleSelector( triangleSelectorSnowplow );
	triangleSelectorSnowplow->drop();
	triangleSelectorSnowplow = NULL;

	// setup animations
	snowplow->setJointMode(EJUOR_CONTROL); //To write positions to the mesh on render
	snowplow->setAnimationSpeed(ANIMATION_SPEED);
	snowplow->setTransitionTime(ANIMATION_TRANSITION_BLEND_TIME);
	snowplow->setFrameLoop(PLAYER_ANIM_START,PLAYER_ANIM_END);
/*
	// setup particle effects
	leftParticleNode = smgr.addParticleSystemSceneNode( false, snowplow, -1, LEFT_PARTICLE_NODE_OFFSET );
	leftEmitter = InParticleManager.CreateSnowplowSnowblast( *leftParticleNode, LEFT_PARTICLE_EMITTER_DIRECTION );
	rightParticleNode = smgr.addParticleSystemSceneNode( false, snowplow, -1, RIGHT_PARTICLE_NODE_OFFSET );
	rightEmitter = InParticleManager.CreateSnowplowSnowblast( *rightParticleNode, RIGHT_PARTICLE_EMITTER_DIRECTION );
*/
	// setup snow plow sound effect
//	sfxSnowplow = GEngine->GetSoundEngine().play2D( "../audio/sfx/snowplow.mp3", true, false, true );
//	sfxSnowplow->setVolume( 0 );
}

// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
void PlayerOnSnowplow::RecreateCollisionResponseAnimator()
{
	// drop the current collision response animator
	if( collisionAnimator )  // soft fail which allows us to call RecreateCollisionResponseAnimator to first initialize the non-existing animator
	{
		snowplow->removeAnimator( collisionAnimator );
		collisionAnimator->drop();
		collisionAnimator = NULL;
	}

	// setup snowplow collision with the world
	core::aabbox3df boxSnowplow = snowplow->getBoundingBox();
	vector3df radiusSnowplow = boxSnowplow.MaxEdge - boxSnowplow.getCenter();
	collisionAnimator = world.GetSceneManager().createCollisionResponseAnimator(
		&world.GetLevelTriangleSelector(), snowplow, radiusSnowplow,
		core::vector3df(0,-8.0f,0),					// gravity
		core::vector3df(0,-radiusSnowplow.Y,0),		// ellipsoid translation
		0.0001f);									// sliding value
	snowplow->addAnimator(collisionAnimator);
}

// destructor, protected to force user to call Actor::DestroyActor
PlayerOnSnowplow::~PlayerOnSnowplow()
{
/*	if( sfxSnowplow )
	{
		sfxSnowplow->stop();
		sfxSnowplow->drop();
		sfxSnowplow = NULL;
	}
*/
	collisionAnimator->drop();
	collisionAnimator = NULL;

	ISceneManager& smgr = world.GetSceneManager();
	smgr.addToDeletionQueue( snowplow );
	smgr.addToDeletionQueue( leftParticleNode );
	smgr.addToDeletionQueue( rightParticleNode );
	smgr.addToDeletionQueue( shadowNode );
	// drop reference to the created emitters
	leftEmitter->drop();
	rightEmitter->drop();
	leftEmitter = NULL;
	rightEmitter = NULL;
}

// interface for turning player on/off
void PlayerOnSnowplow::SetActive( bool bValue )
{
	// call super's implementation
	Player::SetActive( bValue );

	// hide all the player nodes when its turned off
	snowplow->setVisible( bValue );

	// turn sound effect on/off
/*	if( bValue )
		sfxSnowplow->setVolume( 1.8f );
	else
		sfxSnowplow->setVolume( 0 );
*/
 }

// set the translation vector for player
void PlayerOnSnowplow::SetTranslation( const vector3df& trans )
{
	// normally snowplow moves faster than player on foot, but it moves slower when dealing damage 
	f32 speedMultiplier;
	if( bIsDealingDamage )
	{
		speedMultiplier = SNOWPLOW_SPEED_MULTIPLIER_SLOW;
	}
	else
	{
		speedMultiplier = SNOWPLOW_SPEED_MULTIPLIER_FAST;
	}


#if ENABLE_DIAGONAL_TRANSLATION
	translation = vector3df(trans.X * speedMultiplier, 0.0f, trans.Z * speedMultiplier);
#else
	// disallow diagonal movement
	translation = vector3df(0.0f, 0.0f, trans.Z * speedMultiplier);
#endif

	SetMoveState();
}

// set the rotation vector for player
void PlayerOnSnowplow::SetRotation( const vector3df& rot )
{
	Player::SetRotation( rot );

	// limit rotation on x-axis
	if( rotation.X < MIN_XROT_ANGLE )
		rotation.X = MIN_XROT_ANGLE;
	else if( rotation.X > MAX_XROT_ANGLE )
		rotation.X = MAX_XROT_ANGLE;

	// rotate player
	snowplow->setRotation( vector3df( 0, rotation.Y, 0 ) );

	// set the rotation state
	if(rot.Y > 0.0f)
	{
		rotationState = state_POS_ROTATE_RIGHT;
	}
	else if(rot.Y < 0.0f)
	{
		rotationState = state_POS_ROTATE_LEFT;
	}
	else
	{
		rotationState = state_POS_ROTATE_IDLE;
	}
}

// updates the player every fram with the elapsed time since last frame
void PlayerOnSnowplow::Tick( f32 delta )
{
	// don't tick the player if its inactive
	if( playerState == state_PLAYER_INACTIVE )
		return;
	
	// cache off current delta so it can be used to figure out how much damage to deal
	currTickDelta = delta;

	// when dealing damage, turn on the emitters
	if( bIsDealingDamage )
	{
		leftEmitter->setMinParticlesPerSecond( 50 );
		leftEmitter->setMaxParticlesPerSecond( 50 );
		rightEmitter->setMinParticlesPerSecond( 50 );
		rightEmitter->setMaxParticlesPerSecond( 50 );
	}
	else
	{
		// turn off the particle emitters if we're not dealing damage
		leftEmitter->setMinParticlesPerSecond( 0 );
		leftEmitter->setMaxParticlesPerSecond( 0 );
		rightEmitter->setMinParticlesPerSecond( 0 );
		rightEmitter->setMaxParticlesPerSecond( 0 );
	}

	// player's rotation update, must happen before the position updates
	UpdateRotationState();

	// player's movement
	UpdateMoveState( delta );
	snowplow->animateJoints();

	UpdateSnowplowTime( delta );

	sfxTimer += delta;
}

void PlayerOnSnowplow::UpdateRotationState()
{
	switch(rotationState)
	{
		case state_POS_ROTATE_LEFT:
		case state_POS_ROTATE_RIGHT:
		{			
			// rotate aim vector
			aimVector.set( 1, 0, 0 );
			aimVector.rotateXZBy( -rotation.Y, core::vector3df( 0, 0, 0 ) );
			aimVector.normalize();

			rotationState = state_POS_ROTATE_IDLE;
			break;
		}
		case state_POS_ROTATE_IDLE:
		{
			// do nothing
			break;
		}
		default:
		{
			check(false); // should not be here
		}
	}
}

void PlayerOnSnowplow::UpdateMoveState( f32 delta )
{
	switch(moveState)
	{
		case state_POS_MOVE_IDLE:
		{
			velApprox.set( 0, 0, 0 );
			break;
		}
		case state_POS_MOVE_FORWARD:
		case state_POS_MOVE_BACK:
		{
#if ENABLE_DIAGONAL_TRANSLATION
			// set the rotation again, in case we moved diagonally we need to reset it to the default forward orientation again
			snowplow->setRotation( vector3df( 0, rotation.Y, 0 ) );
#endif //ENABLE_DIAGONAL_TRANSLATION
			UpdatePosition( delta );
			break;
		}
#if ENABLE_DIAGONAL_TRANSLATION
		case state_POS_MOVE_FORWARD_LEFT:
		{
			// add additional 45 degree rotation to the node
			snowplow->setRotation( vector3df( 0, rotation.Y, 0 ) + vector3df(0.0f, -45.f, 0.0f) );
			UpdatePosition( delta );
			break;
		}
		case state_POS_MOVE_FORWARD_RIGHT:
		{
			// add additional 45 degree rotation to the node
			snowplow->setRotation( vector3df( 0, rotation.Y, 0 ) + vector3df(0.0f, 45.f, 0.0f) );
			UpdatePosition( delta );
			break;
		}
		case state_POS_MOVE_LEFT:
		{
			// add additional 45 degree rotation to the node
			snowplow->setRotation( vector3df( 0, rotation.Y, 0 ) + vector3df(0.0f, -90.f, 0.0f) );
			UpdatePosition( delta );
			break;
		}
		case state_POS_MOVE_RIGHT:
		{
			// add additional 45 degree rotation to the node
			snowplow->setRotation( vector3df( 0, rotation.Y, 0 ) + vector3df(0.0f, 90.f, 0.0f) );
			UpdatePosition( delta );
			break;
		}
#endif //ENABLE_DIAGONAL_TRANSLATION
		case state_POS_MOVE_DEAD:
		{
			// do nothing for now
			break;
		}
		default:
		{
			check(false); // should not be here
		}
	}
}

// updated the player position based on the value of translation set
void PlayerOnSnowplow::UpdatePosition( f32 delta )
{
	vector3df playerPos = snowplow->getPosition();

	// calculate "right" vector
	vector3df rightVector = aimVector.crossProduct(vector3df(0,1,0));
	rightVector.normalize();

	vector3df savePos = playerPos;

	// translate player
	playerPos += rightVector * delta * translation.X;
	playerPos += aimVector * delta * translation.Z;
	snowplow->setPosition( playerPos );

	velApprox = playerPos - savePos;
}

// udpates the snowplow remaining time and signals the player change if time runs out
void PlayerOnSnowplow::UpdateSnowplowTime( f32 delta )
{
	snowplowTimeRemaining -= delta;
	if( snowplowTimeRemaining <= 0.0f )
	{
		snowplowTimeRemaining = 0.0f;
		world.RequestPlayerSwitch( );
		GEngine->ChangeMusic();
	}

	// if the snowplow time is about to run out, flicker the player on and off
	if( snowplowTimeRemaining < SNOWPLOW_START_FLICKER_THRESHOLD )
	{
		// if it gets rounded up turn the player off, othwerwise keep him on
		if( (s32)(snowplowTimeRemaining*2 + 0.25f) == (s32)(snowplowTimeRemaining*2) )
		{
			snowplow->setVisible(true);
			shadowNode->setVisible(true);
		}
		else
		{
			snowplow->setVisible(false);
			shadowNode->setVisible(false);
		}
	}
}

// updates the move state based on the current value of player translation
void PlayerOnSnowplow::SetMoveState( )
{
	check(translation.Y == 0);

	// if we're dead, remain dead, don't change our state
	if( moveState == state_POS_MOVE_DEAD )
	{
		return;
	}

	// set the player move state based on the received translation
	if( translation.Z > 0.0f )
	{
#if ENABLE_DIAGONAL_TRANSLATION
		if( translation.X > 0.0f )
		{
			moveState = state_POS_MOVE_FORWARD_LEFT;
		}
		else if( translation.X < 0.0f )
		{
			moveState = state_POS_MOVE_FORWARD_RIGHT;
		}
		else
		{
			moveState = state_POS_MOVE_FORWARD;
		}
#else
		moveState = state_POS_MOVE_FORWARD;
#endif //ENABLE_DIAGONAL_TRANSLATION
	}
	else if( translation.Z < 0.0f )
	{
		moveState = state_POS_MOVE_BACK;
	}
	else// trans.Z == 0
	{
#if ENABLE_DIAGONAL_TRANSLATION
		if( translation.X > 0.0f )
		{
			moveState = state_POS_MOVE_LEFT;
		}
		else if( translation.X < 0.0f )
		{
			moveState = state_POS_MOVE_RIGHT;
		}
		else
		{
			moveState = state_POS_MOVE_IDLE;
		}
#else
		moveState = state_POS_MOVE_IDLE;
#endif //ENABLE_DIAGONAL_TRANSLATION
	}
}

void PlayerOnSnowplow::ReceiveDamage( f32 value )
{
	// when on a snowplow, player is immune to damage, do nothing
}

// performs collision checks between this actor and other objects in the world
void PlayerOnSnowplow::DoCollisions( const CollisionInfo& collInfo )
{
	// get the bounding box for the snowplow
	aabbox3d<f32> box = snowplow->getTransformedBoundingBox();

	// snowplow should deal damage if the front of it is touching the enemy
	vector3df edge1 = box.MinEdge;
	vector3df edge2 = box.MaxEdge;
	          edge2 = box.MaxEdge - vector3df(0.0f,0.0f, (box.MaxEdge.Z - box.MinEdge.Z)/10);
	aabbox3d<f32> snowplowDamageBox(edge1,edge2);

	// reset the slow down flag
	bIsDealingDamage = false;

	// check if we collided with any enemies
	for( u32 i=0; i < collInfo.Actors.size(); ++i )
	{
		if( collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY
		||	collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY_TWO
		||	collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY_BOSS )
		{
			if( CollisionHelper::CheckCollision( collInfo.Actors[i]->GetNode().getTransformedBoundingBox(), snowplowDamageBox ) )
			{
				collInfo.Actors[i]->ReceiveDamage( currTickDelta * SNOWPLOW_DAMAGE_PER_SECOND );
				// set the flag that we are dealing damage, to slow down the plow movement and turning on the particle emitters
				bIsDealingDamage = true;
				if( sfxTimer > 1 )
				{
					PlayRandomCheer();
//					GEngine->GetSoundEngine().play2D( "../audio/sfx/grind.mp3" );
					sfxTimer = 0;
				}
			}
		}
	}
}

// unbuffered mouse input 
void PlayerOnSnowplow::OnMouseEvent( const SEvent::SMouseInput& mouseEvent )
{
	// do nothing for now
}
