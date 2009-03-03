#include "EnemyBoss.h"
#include "GameWorld.h"
#include "GameEngine.h"
#include "CollisionHelper.h"
#include "SnowballProjectile.h"
#include "Player.h"
#include "FloorDecalSceneNode.h"
#include "ExplosionEffect.h"


static const irr::c8*		ENEMY_MODEL  = "../art/characters/Snowman/BossSnowman.ms3d";
static const irr::c8*		ENEMY_TEXTURE = "../art/characters/Snowman/BossUV.png";
static const irr::c8*		ENEMY_BOSS_SHADOWTEXTURE = "../art/sfx/Flats/CharacterShadow.png";
static const vector3df		ENEMY_BOSS_SCALE = vector3df(2,2,2);
static const f32			EPSILON = 0.01f;
static const f32			MIN_THROW_POWER = 100.0f;
static const f32			MAX_THROW_POWER = 300.0f;

static const u32			SNOWMAN2_ANIM_WALK_FORWARD_START = 1;
static const u32			SNOWMAN2_ANIM_WALK_FORWARD_END = 20;
static const u32			SNOWMAN2_ANIM_SNOWBALLTHROW_START = 21;
static const u32			SNOWMAN2_ANIM_SNOWBALLTHROW_END = 40;
static const u32			SNOWMAN2_ANIM_FOLLOWTHROUGH_START = 41;
static const u32			SNOWMAN2_ANIM_FOLLOWTHROUGH_END = 42;

extern GameEngine* GEngine;

EnemyBoss::EnemyBoss( GameWorld& gameWorld, const vector3df& position, ITriangleSelector& levelTriangleSelector )
: Actor(gameWorld) 
, node(NULL)
, shadowNode(NULL)
, enemyBossState(state_ENEMY_BOSS_MOVING)
, prevEnemyBossState(state_ENEMY_BOSS_MOVING)
, hitpoints(20)
, rotation(0)
, timeDeltaBetweenThrows(0)
, ThrowAnimEndCallback(NULL)
, FollowthroughAnimEndCallback(NULL)
, sfxTimer(4)
, numThrowsRemaining(0)
, bReadyToThrow(false)
{
	ISceneManager& smgr = world.GetSceneManager();
	IVideoDriver& driver = GEngine->GetDriver();
	// load the animated mesh, and add a new scene graph node for it
	IAnimatedMesh* mesh = smgr.getMesh( ENEMY_MODEL );
	check( mesh );
	node = world.GetSceneManager().addAnimatedMeshSceneNode( mesh );
	check( node );

	node->setScale( ENEMY_BOSS_SCALE );
	node->setPosition( position );
	node->setRotation( vector3df(0,0,0) );
	node->setMaterialFlag(video::EMF_LIGHTING, true);
	node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	node->setMaterialTexture(0, driver.getTexture( ENEMY_TEXTURE ));
	node->updateAbsolutePosition();

	aimVector.set( 0.0f, 0.0f, -1.0f );
	targetVector.set( 0.0f, 0.0f, -1.0f );

	// setup enemy shadow
	shadowNode = GEngine->addFloorDecalSceneNode(node, core::dimension2d<f32>(30, 30));
	check(shadowNode);
	shadowNode->setMaterialFlag(video::EMF_LIGHTING, false);
	shadowNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	shadowNode->setMaterialTexture(0, driver.getTexture(ENEMY_BOSS_SHADOWTEXTURE));

	// setup player collision with the world
	core::aabbox3df box = node->getBoundingBox();
	vector3df radius = box.MaxEdge - box.getCenter();

	scene::ISceneNodeAnimator* anim = world.GetSceneManager().createCollisionResponseAnimator(
		&levelTriangleSelector, node, radius,
		core::vector3df(0,-8.0f,0), // gravity
		core::vector3df(0,-radius.Y,0),		// ellipsoid translation
		0.0001f);					// sliding value
	node->addAnimator(anim);
	anim->drop();

	// create a triangle selector for this enemy mesh
	ITriangleSelector* triangleSelector = world.GetSceneManager().createTriangleSelectorFromBoundingBox( node );
	check( triangleSelector );
	node->setTriangleSelector( triangleSelector );
	triangleSelector->drop();
	triangleSelector = NULL;

	// setup animation
	node->setAnimationSpeed(45);
	node->setFrameLoop(SNOWMAN2_ANIM_WALK_FORWARD_START, SNOWMAN2_ANIM_WALK_FORWARD_END);

	// randomize enemy properties
	speed = 10.0f;
	timeBetweenThrows = 6.0f;

	// initialize sounds to empty
	for( int i=0; i<sound_TOTAL_NUM; i++ )
		sounds[ i ] = NULL;

	// create sounds for this enemy
	ChooseNewSound();

	// setup the throw animation callback
	ThrowAnimEndCallback = new EnemyBossThrowingAnimationEndCallback(*this);
	FollowthroughAnimEndCallback = new EnemyBossFollowthroughAnimationEndCallback(*this);

}

// destructor, protected to force user to call Actor::DestroyActor
EnemyBoss::~EnemyBoss()
{
	// clean up sounds
	for( int i=0; i<sound_TOTAL_NUM; i++ )
	{
		if( sounds[ i ] )
		{
			sounds[ i ]->stop();
			sounds[ i ]->drop();
			sounds[ i ] = NULL;
		}
	}

	// make sure there are not outstanding callbacks that can be called
	node->setAnimationEndCallback( NULL );

	// clean up the callback objects
	ThrowAnimEndCallback->drop();
	ThrowAnimEndCallback = NULL;

	FollowthroughAnimEndCallback->drop();
	FollowthroughAnimEndCallback = NULL;


	// clean up the node upon enemy deletion
	world.GetSceneManager().addToDeletionQueue( node );
	world.GetSceneManager().addToDeletionQueue( shadowNode );
}

// interface for damaging the enemy
void EnemyBoss::ReceiveDamage( f32 value )
{
	if( state == state_ACTOR_ALIVE )
	{
		check( hitpoints > 0 );
		hitpoints -= value;

		if( hitpoints <= 0 )
		{
			// stop updated 3d sound
			sounds[ sound_ENEMY_ALIVE ]->stop();
			// play death sound effect
			ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/zombiedeath1.mp3", node->getAbsolutePosition(), false, false, true );
			sound->setMinDistance( 40.0f );
			sound->drop();

			// start off the enemy death effect do it three times to get more particles
			ExplosionEffect* pEffect = world.GetFirstAvailableEnemyDeathEffect();
			if( pEffect )
			{
				pEffect->StartEffect(node->getAbsolutePosition());
				pEffect = NULL;
			}
			pEffect = world.GetFirstAvailableEnemyDeathEffect();
			if( pEffect )
			{
				pEffect->StartEffect(node->getAbsolutePosition());
				pEffect = NULL;
			}
			pEffect = world.GetFirstAvailableEnemyDeathEffect();
			if( pEffect )
			{
				pEffect->StartEffect(node->getAbsolutePosition());
				pEffect = NULL;
			}

			// update the player score
			world.GetCurrentPlayer().AddScore(1);
			state = state_ACTOR_DEAD;
		}
		else
		{
			// play pain sound effect
			if( sfxTimer > 3 )
			{
				ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/zombiepain1.wav", node->getAbsolutePosition(), false, false, true );
				sound->setMinDistance( 40.0f );
				sound->drop();
				sfxTimer = 0;
			};
		}
	}
}

void EnemyBoss::ChooseNewSound()
{
	static const s32 MAX_TAUNTS = 2;
	static s32 randomTaunt = ( rand()%MAX_TAUNTS );

	if( sounds[ sound_ENEMY_ALIVE ] )
		sounds[ sound_ENEMY_ALIVE ]->drop();
	ISoundEngine& soundEngine = GEngine->GetSoundEngine();
	switch( randomTaunt )
	{
	case 0:
		sounds[ sound_ENEMY_ALIVE ] = soundEngine.play3D( "../audio/sfx/boss1.mp3", node->getAbsolutePosition(), false, false, true );
		break;
	case 1:
		sounds[ sound_ENEMY_ALIVE ] = soundEngine.play3D( "../audio/sfx/boss2.mp3", node->getAbsolutePosition(), false, false, true );
		break;
	default: break;
	}
	check( sounds[ sound_ENEMY_ALIVE ] );
	sounds[ sound_ENEMY_ALIVE ]->setMinDistance( 60.0f );
	sounds[ sound_ENEMY_ALIVE ]->setVolume( 1.0f );

	if( ++randomTaunt >= MAX_TAUNTS )
		randomTaunt = 0;
}

void EnemyBoss::SetAimTarget( Actor& target )
{
//	if( state == state_ACTOR_DEAD )
//		return;
	targetActor = &target;

	targetVector = targetActor->GetNode().getAbsolutePosition() - node->getAbsolutePosition();
	targetVector.Y = 0;
	targetVector.normalize();
}

void EnemyBoss::DoCollisions( const CollisionInfo& collInfo )
{
	// check to see if we hit the player
	if( CollisionHelper::CheckProximity( targetActor->GetNode().getAbsolutePosition(), node->getAbsolutePosition(), 10 ) )
	{
		targetActor->ReceiveDamage( 100 );
	}
}

// updates the enemy every frame
void EnemyBoss::Tick( f32 delta )
{
	EEnemyBossState nextState = enemyBossState;

	switch (enemyBossState)
	{	
		case state_ENEMY_BOSS_MOVING:
		{
			// setup animation for this state
			if( prevEnemyBossState != state_ENEMY_BOSS_MOVING )
			{
				node->setFrameLoop(SNOWMAN2_ANIM_WALK_FORWARD_START,SNOWMAN2_ANIM_WALK_FORWARD_END);
				node->setLoopMode(true);
			}

			// update enemy position
			sounds[ sound_ENEMY_ALIVE ]->setPosition( node->getAbsolutePosition() );
			
			// track towards current target
			f32 dot = targetVector.dotProduct( aimVector );
			dot = (dot < -1.0f ? -1.0f : (dot > 1.0f ? 1.0f : dot));
			f32 angle = acos( dot );

			vector3df cross = targetVector.crossProduct( aimVector );
			if( cross.Y > 0.0f )
				angle = -angle;

			rotation -= angle;
				
			aimVector.set( 0, 0, 1 );
			aimVector.rotateXZBy( -rotation, vector3df( 0, 0, 0 ) );
			aimVector.Y = 0;
			aimVector.normalize();

			vector3df pos = node->getAbsolutePosition();
			if( delta < 1.0f )
				pos -= aimVector * delta * speed;
			node->setPosition( pos );
			node->setRotation( vector3df( 0, rotation, 0 ) );

			timeDeltaBetweenThrows += delta;
			if( timeDeltaBetweenThrows > timeBetweenThrows )
			{
				timeDeltaBetweenThrows = 0;
				// put enemy in the throwing state to make him shoot a snowball at the player
				nextState = state_ENEMY_BOSS_THROWING;
			}

			break;
		}
		case state_ENEMY_BOSS_THROWING:
		{
			// setup animation for this state
			if( prevEnemyBossState != state_ENEMY_BOSS_THROWING )
			{
				// play new sound
				ChooseNewSound();

				numThrowsRemaining = 4;
				bReadyToThrow = true;
			}

			if( bReadyToThrow )
			{
				if( numThrowsRemaining > 0 )
				{
					numThrowsRemaining--;
					bReadyToThrow = false;
					node->setFrameLoop(SNOWMAN2_ANIM_SNOWBALLTHROW_START,SNOWMAN2_ANIM_SNOWBALLTHROW_END);
					node->setLoopMode(false);
					node->setAnimationEndCallback( ThrowAnimEndCallback );
				}
				else
				{
					// we finished throwing, go to the moving state
					nextState = state_ENEMY_BOSS_MOVING;
				}
			}
			else
			{
				// do nothing, wait for the throwing animatino to finish
			}
			break;
		}
		case state_ENEMY_BOSS_FOLLOWTHROUGH:
		{
			// setup animation for this state
			if( prevEnemyBossState != state_ENEMY_BOSS_FOLLOWTHROUGH )
			{
				node->setFrameLoop(SNOWMAN2_ANIM_FOLLOWTHROUGH_START,SNOWMAN2_ANIM_FOLLOWTHROUGH_END);
				node->setLoopMode(false);
				node->setAnimationEndCallback( FollowthroughAnimEndCallback );
			}
			break;
		}
		default:
		{
			// should not be here
			check(FALSE);
		}
	}

	prevEnemyBossState = enemyBossState;
	enemyBossState = nextState;
}

// shoots a snowball from the current enemy location
void EnemyBoss::ShootSnowball( SnowballProjectile& projectile )
{
	// make sure its ok to throw this projectile
	check(projectile.GetSnowballState() == state_SNOWBALL_IDLE);

	// start position for the snowball, make it the position of the snowball joint node
	IBoneSceneNode* jointNode = node->getJointNode( "Snowball" );
	check(jointNode);
	vector3df startPos = node->getJointNode( "Snowball" )->getAbsolutePosition();//node->getAbsolutePosition() + (direction * 15.0f);

	// calculate direction, accuracy and power of throw
	vector3df direction;

	f32 aimAccuracy = 125; 		// how well the AI guages where the player might move (approximate)

	// factor in player movement
	EActorType actorType = targetActor->GetActorType();
	if( actorType == ACTOR_PLAYER || actorType == ACTOR_PLAYER_ON_SNOWPLOW)
	{
		Player *player = (Player *)targetActor;
		direction = player->GetNodePosition();
		direction -= startPos;
		direction.Y = 0;
		direction.normalize();
	}
	else
	{
		direction = -aimVector;
		direction.Y = 0;
		direction.normalize();
	}

	// to properly take the angle into account, we add tan(angle) to Y, angle is hardcoded for now
	float rad = 15 * PI / 180;
	direction.Y = (f32)tan(rad);
	direction.normalize();

	// find the distance between the player and us to gauge the power of the throw
	f32 dist = node->getPosition().getDistanceFrom( targetActor->GetNode().getPosition() );
	f32 speed = 0;
	if( dist < 50 )
	{
		speed = 50;
	}
	else if( dist < 100 )
	{
		speed = 75;
	}
	else if( dist < 200 )
	{
		speed = 120;
	}
	else
	{
		speed = 150;
	}
	
	projectile.Launch( startPos, direction, speed );

	// play throwing sound
	ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/throw1.mp3", node->getAbsolutePosition(), false, false, true );
	sound->setMinDistance( 40.0f );
	sound->drop();
}

// interface for attaching and detaching external actor
void EnemyBoss::AttachActor( Actor& actorToAttach, const c8* nodeName/*=NULL*/ )
{
	Actor::AttachActor(actorToAttach);

	ISceneNode* parentNode = node;
	// if the node name was specified attach to the specified node, otherwise attach to our local root node
	if(nodeName)
	{
		parentNode = node->getJointNode( nodeName );
	}
	check(parentNode);

	ISceneNode& attachActorNode = actorToAttach.GetNode();
	const vector3df& relativePos = attachActorNode.getAbsolutePosition() - parentNode->getAbsolutePosition();
	attachActorNode.setParent( parentNode );
	attachActorNode.setPosition(relativePos);
	attachActorNode.setRotation(parentNode->getRotation()-attachActorNode.getRotation());
	// due to the boss node scalign the attached actors also get scaled so we must compensate for that
	attachActorNode.setScale(vector3df(1/ENEMY_BOSS_SCALE.X, 1/ENEMY_BOSS_SCALE.Y, 1/ENEMY_BOSS_SCALE.Z));
	attachActorNode.updateAbsolutePosition();
}

void EnemyBoss::DetachActor( Actor& actorToDetach )
{
	Actor::DetachActor(actorToDetach);

	// reattach the node to the root
	ISceneNode& detachActorNode = actorToDetach.GetNode();
	const vector3df& position = detachActorNode.getAbsolutePosition();
	detachActorNode.setParent( world.GetSceneManager().getRootSceneNode() );
	detachActorNode.setPosition(position);
	detachActorNode.setScale(vector3df(1,1,1));
	detachActorNode.updateAbsolutePosition();
}

// gets called when the throw animation has finished
void EnemyBossThrowingAnimationEndCallback::OnAnimationEnd(IAnimatedMeshSceneNode* node)
{
	// make the player throw a snowball, and put him in the followthrough state
	SnowballProjectile* projectile = OwningEnemy.world.GetFirstAvailableSnowball();
	if( projectile )
	{
		OwningEnemy.ShootSnowball( *projectile );
	}
	OwningEnemy.bReadyToThrow = true;
	OwningEnemy.node->setAnimationEndCallback( NULL );

	// putting player back in walking state for now, the followthrough animation doesn't seem to be working
	//OwningEnemy.enemyBossState = state_ENEMY_BOSS_MOVING;
	//OwningEnemy.enemyBossState = state_ENEMY_BOSS_FOLLOWTHROUGH;aa
}

// gets called when the throw animation has finished
void EnemyBossFollowthroughAnimationEndCallback::OnAnimationEnd(IAnimatedMeshSceneNode* node)
{
	// put the player back in the walking state
	OwningEnemy.enemyBossState = state_ENEMY_BOSS_MOVING;
}

