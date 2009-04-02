#include "Enemy.h"
#include "GameWorld.h"
#include "GameEngine.h"
#include "CollisionHelper.h"
#include "Player.h"
#include "FloorDecalSceneNode.h"
//#include "ExplosionEffect.h"


static const irr::c8* ENEMY_MODEL  = "../art/characters/Snowman/Snowman2.ms3d";
static const irr::c8* ENEMY_TEXTURE = "../art/characters/Snowman/SnowmanUV.png";
static const irr::c8* ENEMY_SHADOWTEXTURE = "../art/sfx/Flats/CharacterShadow.png";
static const irr::f32 EPSILON = 0.01f;

extern GameEngine* GEngine;

	Enemy::Enemy( GameWorld& gameWorld, const irr::core::vector3df& position, irr::scene::ITriangleSelector& levelTriangleSelector )
	: Actor(gameWorld) 
	, node(NULL)
	, shadowNode(NULL)
	, hitpoints(3)
	, rotation(0)
	  , sfxTimer(4)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	irr::video::IVideoDriver& driver = GEngine->GetDriver();
	// load the animated mesh, and add a new scene graph node for it
	irr::scene::IAnimatedMesh* mesh = smgr.getMesh( ENEMY_MODEL );
	check( mesh );
	node = world.GetSceneManager().addAnimatedMeshSceneNode( mesh );
	check( node ); 

	node->setPosition( position );
	node->setRotation( irr::core::vector3df(0,0,0) );
	node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	node->setMaterialTexture(0, driver.getTexture( ENEMY_TEXTURE ));
	node->setAnimationSpeed(30);
	node->updateAbsolutePosition();

	// setup enemy shadow
	shadowNode = GEngine->addFloorDecalSceneNode(node, irr::core::dimension2d<irr::f32>(12, 12));
	check(shadowNode);
	shadowNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	shadowNode->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	shadowNode->setMaterialTexture(0, driver.getTexture(ENEMY_SHADOWTEXTURE));

	aimVector.set( 0.0f, 0.0f, -1.0f );
	targetVector.set( 0.0f, 0.0f, -1.0f );

	// setup player collision with the world
	irr::core::aabbox3df box = node->getBoundingBox();
	irr::core::vector3df radius = box.MaxEdge - box.getCenter();

	irr::scene::ISceneNodeAnimator* anim = world.GetSceneManager().createCollisionResponseAnimator(
			&levelTriangleSelector, node, radius,
			irr::core::vector3df(0,-8.0f,0), // gravity
			irr::core::vector3df(0,-radius.Y,0), // ellipsoid translation
			0.0001f); // sliding value
	node->addAnimator(anim);
	anim->drop();

	// create a triangle selector for this enemy mesh
	irr::scene::ITriangleSelector* triangleSelector = smgr.createTriangleSelectorFromBoundingBox( node );
	check( triangleSelector );
	node->setTriangleSelector( triangleSelector );
	triangleSelector->drop();
	triangleSelector = NULL;

	// give this enemy a movement speed
	speed = (rand()%10) + 6.0f;

	// initialize sounds to empty
	// for( int i=0; i<sound_TOTAL_NUM; i++ )
	// sounds[ i ] = NULL;

	// create sounds for this enemy
	ChooseNewSound();
}

// destructor, protected to force user to call Actor::DestroyActor
Enemy::~Enemy()
{
	// clean up sounds
	/* for( int i=0; i<sound_TOTAL_NUM; i++ )
	   {
	   if( sounds[ i ] )
	   {
	   sounds[ i ]->stop();
	   sounds[ i ]->drop();
	   sounds[ i ] = NULL;
	   }
	   }
	   */
	// clean up the node upon enemy deletion
	world.GetSceneManager().addToDeletionQueue( node );
	world.GetSceneManager().addToDeletionQueue( shadowNode );
}

// updates the enemy every frame
void Enemy::Tick( irr::f32 delta )
{
	switch (state)
	{ 
		case state_ACTOR_ALIVE:
			{
				// update enemy position
				// sounds[ sound_ENEMY_ALIVE ]->setPosition( node->getAbsolutePosition() );

				// track towards current target
				irr::f32 dot = targetVector.dotProduct( aimVector );
				dot = (dot < -1.0f ? -1.0f : (dot > 1.0f ? 1.0f : dot));
				irr::f32 angle = acos( dot );

				irr::core::vector3df cross = targetVector.crossProduct( aimVector );
				if( cross.Y > 0.0f )
					angle = -angle;

				rotation -= angle;

				aimVector.set( 0, 0, 1 );
				aimVector.rotateXZBy( -rotation, irr::core::vector3df( 0, 0, 0 ) );
				aimVector.Y = 0;
				aimVector.normalize();

				irr::core::vector3df pos = node->getAbsolutePosition();
				if( delta < 1.0f )
					pos -= aimVector * delta * speed;
				node->setPosition( pos );
				node->setRotation( irr::core::vector3df( 0, rotation, 0 ) );
				sfxTimer += delta;

				// play sounds intermittently
				static irr::f32 sfxGroanTimer = ( 15.0f + (irr::f32)(rand()%15) );
				static irr::f32 sfxGroanTick = 0;
				sfxGroanTick += delta;
				if( sfxGroanTick > sfxGroanTimer )
				{
					sfxGroanTick = 0;
					sfxGroanTimer = ( 25.0f + (irr::f32)(rand()%15) );
					ChooseNewSound();
				}
				break;
			}
		case state_ACTOR_DEAD:
			{
				// enemy is dead, it is going to be deleted from the world
				break;
			}
		default:
			{
				// should not be here
				check(FALSE);
			}
	}
}

void Enemy::ChooseNewSound()
{
	static const irr::s32 MAX_TAUNTS = 4;
	static irr::s32 randomTaunt = ( rand()%MAX_TAUNTS );

	// if( sounds[ sound_ENEMY_ALIVE ] )
	/// sounds[ sound_ENEMY_ALIVE ]->drop();
	// ISoundEngine& soundEngine = GEngine->GetSoundEngine();
	/* switch( randomTaunt )
	   {
	   case 0:
	   sounds[ sound_ENEMY_ALIVE ] = soundEngine.play3D( "../audio/sfx/zombiegroan1.mp3", node->getAbsolutePosition(), false, false, true );
	   break;
	   case 1:
	   sounds[ sound_ENEMY_ALIVE ] = soundEngine.play3D( "../audio/sfx/zombiegroan2.mp3", node->getAbsolutePosition(), false, false, true );
	   break;
	   case 2:
	   sounds[ sound_ENEMY_ALIVE ] = soundEngine.play3D( "../audio/sfx/zombiegroan3.mp3", node->getAbsolutePosition(), false, false, true );
	   break;
	   case 3:
	   sounds[ sound_ENEMY_ALIVE ] = soundEngine.play3D( "../audio/sfx/zombiegroan4.mp3", node->getAbsolutePosition(), false, false, true );
	   break;
	   default: break;
	   }
	   check( sounds[ sound_ENEMY_ALIVE ] );
	   sounds[ sound_ENEMY_ALIVE ]->setMinDistance( 60.0f );
	   sounds[ sound_ENEMY_ALIVE ]->setVolume( 1.0f );
	   */
	if( ++randomTaunt >= MAX_TAUNTS )
		randomTaunt = 0;
}

// interface for damaging the enemy
void Enemy::ReceiveDamage( irr::f32 value )
{
	if( state == state_ACTOR_ALIVE )
	{
		check( hitpoints > 0 );
		hitpoints -= value;

		if( hitpoints <= 0 )
		{
			// stop updated 3d sound
			// sounds[ sound_ENEMY_ALIVE ]->stop();
			// play death sound effect
			// ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/zombiedeath1.mp3", node->getAbsolutePosition(), false, false, true );
			// sound->setVolume( 0.7f );
			// sound->setMinDistance( 40.0f );
			// sound->drop();

			// update the player score
			//world.GetCurrentPlayer().AddScore(1);

			// start off the enemy death effect if the player was killed with a dynamite
			if( world.GetCurrentPlayer().GetActorType() != ACTOR_ROBOT )
			{
				/* ExplosionEffect* pEffect = world.GetFirstAvailableEnemyDeathEffect();
				   if( pEffect )
				   {
				   pEffect->StartEffect(node->getAbsolutePosition());
				   }
				   */
			}

			state = state_ACTOR_DEAD;
		}
		else
		{
			// play pain sound effect
			/* if( sfxTimer > 3 )
			   {
			   ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/zombiepain1.wav", node->getAbsolutePosition(), false, false, true );
			   sound->setMinDistance( 40.0f );
			   sound->drop();
			   sfxTimer = 0;
			   }
			   */
		}
	}
}

void Enemy::SetAimTarget( Actor& target )
{
	// if( state == state_ACTOR_DEAD )
	// return;
	targetActor = &target;

	targetVector = targetActor->GetNode().getAbsolutePosition() - node->getAbsolutePosition();
	targetVector.Y = 0;
	targetVector.normalize();
}

void Enemy::DoCollisions( const CollisionInfo& collInfo )
{
	// check to see if we hit the player

	irr::core::aabbox3d<irr::f32> box = node->getTransformedBoundingBox();

	if( CollisionHelper::CheckCollision( targetActor->GetNode().getTransformedBoundingBox(), box ) )
	{
		check((dynamic_cast<Player*>(targetActor))->IsActive());
		targetActor->ReceiveDamage( 100 );
	}
}

// interface for attaching and detaching external actor
void Enemy::AttachActor( Actor& actorToAttach, const irr::c8* nodeName/*=NULL*/ )
{
	Actor::AttachActor(actorToAttach);

	irr::scene::ISceneNode* parentNode = node;
	// if the node name was specified attach to the specified node, otherwise attach to our local root node
	if(nodeName)
	{
		parentNode = node->getJointNode( nodeName );
	}
	check(parentNode);

	irr::scene::ISceneNode& attachActorNode = actorToAttach.GetNode();
	const irr::core::vector3df& relativePos = attachActorNode.getAbsolutePosition() - parentNode->getAbsolutePosition();
	attachActorNode.setParent( parentNode );
	attachActorNode.setPosition(relativePos);
	attachActorNode.setRotation(parentNode->getRotation()-attachActorNode.getRotation());
	attachActorNode.updateAbsolutePosition();
}

void Enemy::DetachActor( Actor& actorToDetach )
{
	Actor::DetachActor(actorToDetach);

	// reattach the node to the root
	irr::scene::ISceneNode& detachActorNode = actorToDetach.GetNode();
	const irr::core::vector3df& position = detachActorNode.getAbsolutePosition();
	detachActorNode.setParent( world.GetSceneManager().getRootSceneNode() );
	detachActorNode.setPosition(position);
	detachActorNode.updateAbsolutePosition();
}


