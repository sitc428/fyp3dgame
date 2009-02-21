#include "SnowballProjectile.h"
#include "Check.h"
#include "GameEngine.h"
#include <irrlicht.h>
#include "ExplosionEffect.h"
#include "GameWorld.h"  // for collision info
#include "CollisionHelper.h"
#include "Player.h"

extern GameEngine* GEngine;

// Parameters specifying default projectile parameters
static const irr::c8*		SNOWBALL_MODEL  = "../art/characters/Snowball/Snowball.ms3d";
static const vector3df		defaultPosition = vector3df(0,-10,0);
static const vector3df		defaultRotation = vector3df(0,0,0);
static const vector3df		defaultScale = vector3df(1.0f,1.0f,1.0f);

static const f32			gravityScaleFactor = 7.0f;
static const vector3df		projectileGravity = vector3df(0.0f, -9.8f, 0.0f) * gravityScaleFactor;

static const u32			EXPLOSION_DURATION = 1000;
static const f32			SNOWBALL_DAMAGE = 1.f;

// constructor
SnowballProjectile::SnowballProjectile( GameWorld& gameWorld,
										IVideoDriver& driver )
:	Actor(gameWorld)
,	node(NULL)
,	state(state_SNOWBALL_IDLE)
,	launchStartPosition(vector3df(0.0f,0.0f,0.0f))
,	launchVelocity(vector3df(0.0f,0.0f,0.0f))
,	launchElapsedTime(0.0f)
{
	ISceneManager& smgr = world.GetSceneManager();
	// construct a scene node which will represent this projectile
	IMesh* snowballMesh = smgr.getMesh( SNOWBALL_MODEL );
	check( snowballMesh );
	node = smgr.addMeshSceneNode( 
		snowballMesh,
		NULL,					// parent
		-1,						// ID of the node
		defaultPosition,		// position
		defaultRotation,		// rotation
		defaultScale );			// scale

	check(node);
	node->setMaterialFlag( video::EMF_LIGHTING, true );
}

SnowballProjectile::~SnowballProjectile()
{
	// clean up the node upon deletion
	world.GetSceneManager().addToDeletionQueue( node );
}

// returns the projectile to the default state
void SnowballProjectile::ResetProjectile()
{
	node->setPosition( defaultPosition );
	node->updateAbsolutePosition();
	launchStartPosition = defaultPosition;
	launchVelocity = vector3df(0.0f,0.0f,0.0f);
	launchElapsedTime = 0.0f;
}

// updates the projectile every frame with the elapsed time since last frame
void SnowballProjectile::Tick( f32 delta )
{
	switch (state)
	{	
		case state_SNOWBALL_IDLE:
		{
			// do nothing, the projectile is waiting to be launched
			break;
		}
		case state_SNOWBALL_MOVING:
		{
			// update the elapsed time since launch
			launchElapsedTime += delta;

			// compute the position of the projectile based on the elapsed time 
			// x(t) = x + v*t + 1/2gt^2
			vector3df newPosition = launchStartPosition + launchVelocity*launchElapsedTime + (f32)0.5 * projectileGravity * launchElapsedTime * launchElapsedTime;
			node->setPosition( newPosition );
			node->updateAbsolutePosition();

			// if we've been moving for more than 4 sec, just stop the projectile simulation
			if( launchElapsedTime > 4 )
			{
				ResetProjectile();
				state = state_SNOWBALL_IDLE;
			}
			break;
		}
		case state_SNOWBALL_EXPLODING:
		{
			// create an explosion particle effect
			CreateParticleExplosion();

			// play explosion sound effect
			ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/snowball.mp3", node->getAbsolutePosition(), false, false, true );
			sound->setMinDistance( 50.0f );
			sound->drop();

			// put the mesh in its original default position
			ResetProjectile();

			state = state_SNOWBALL_IDLE;
			break;
		}
		default:
		{
			// should not be here
			check(FALSE);
		}
	}
}

// launches the projectile, using specified start location, direction, and speed
void SnowballProjectile::Launch( const vector3df& start, const vector3df& direction, f32 speed )
{
	check(state == state_SNOWBALL_IDLE);

	// set the initial position
	node->setPosition( start );
	node->updateAbsolutePosition();

	// set the launch info data
	launchStartPosition = start;
	launchVelocity = direction * speed;
	launchElapsedTime = 0.0f;

	// starnsition to the moving state
	state = state_SNOWBALL_MOVING;
}

// causes an explosion of the projectile
void SnowballProjectile::Explode()
{
	check( state == state_SNOWBALL_MOVING ); // explosions should only happen to moving projectiles

	// change the particle state, tick will perform the explosion on the next frame
	state = state_SNOWBALL_EXPLODING;
}

// whether collision checks should be done on this projectile
bool SnowballProjectile::ShouldPerformCollisionCheck() const
{
	if( state == state_SNOWBALL_MOVING )
	{
		// only check for collisions when this projectile is moving
		return true;
	}

	return false;
}

// performs collision handling with various objects in the world
void SnowballProjectile::DoCollisions( const CollisionInfo& collInfo )
{
	// get the bounding box for the projectile
	aabbox3d<f32> box = node->getTransformedBoundingBox();

	// whether this projectile needs to explode
	bool bExplode = false;

	// check if we collided with the world
	if( CollisionHelper::CheckCollision( collInfo.LevelTriangleSelector, box ) )
	{
		// explode the projectile, don't assign any damage
		bExplode = true;
	}

	// check if we collided with any enemies
	for( u32 i=0; i < collInfo.Actors.size(); ++i )
	{
		if( collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY
			|| collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY_TWO )
		{
			// no damage to enemies
			/*if( CollisionHelper::CheckCollision( collInfo.Actors[i]->GetNode().getTransformedBoundingBox(), box ) )
			{
				// explode the projectile, and assign damage to the enemy
				bExplode = true;
				collInfo.Actors[i]->ReceiveDamage( SNOWBALL_DAMAGE );
			}*/
		}
		else if( ( collInfo.Actors[i]->GetActorType() == ACTOR_PLAYER && world.GetCurrentPlayer().GetActorType() == ACTOR_PLAYER )
			|| ( collInfo.Actors[i]->GetActorType() == ACTOR_PLAYER_ON_SNOWPLOW && world.GetCurrentPlayer().GetActorType() == ACTOR_PLAYER_ON_SNOWPLOW ) )
		{
			if( CollisionHelper::CheckCollision( collInfo.Actors[i]->GetNode().getTransformedBoundingBox(), box ) )
			{
				// explode the projectile, and assign damage to the player
				bExplode = true;
				collInfo.Actors[i]->ReceiveDamage( SNOWBALL_DAMAGE * 35 );
			}
		}
	}

	if( bExplode )
	{
		Explode();
	}
}

// creates the explosion effect
void SnowballProjectile::CreateParticleExplosion()
{
	// create the explosion effect
	ExplosionEffect* pEffect = world.GetFirstAvailableSnowballExplosionEffect();
	if( pEffect )
	{
		pEffect->StartEffect(node->getAbsolutePosition());
	}
}
	
