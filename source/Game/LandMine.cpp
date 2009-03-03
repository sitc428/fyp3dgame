#include "LandMine.h"
#include "GameWorld.h"
#include "GameEngine.h"
#include "ExplosionEffect.h"
#include "CollisionHelper.h"

#if _DEBUG
#define DEBUG_DRAW_LANDMINE_EXPLOSION 1
#else
#define DEBUG_DRAW_LANDMINE_EXPLOSION 0
#endif

extern GameEngine* GEngine;

static const irr::c8*		LANDMINE_MODEL  = "../art/characters/Dynamite/Dynamite.ms3d";
static const vector3df		defaultPosition = vector3df(0,-10,0);

static const f32			LANDMINE_DAMAGE = 3.f;
static const f32			DAMAGE_RADIUS = 50.f;	
static const f32			LANDMINE_ARMING_TIME = 1.5f; // 1.5 seconds

// constructor
LandMine::LandMine( GameWorld& gameWorld, irr::video::IVideoDriver& driver, ITriangleSelector& levelTriangleSelector )
:	Actor(gameWorld)
,	node(NULL)
,	landMineState(state_LANDMINE_IDLE)
,	elapsedTimeInArmingState(0.0f)
{
	// construct a scene node which will represent this actor
	ISceneManager& smgr = world.GetSceneManager();
	IMesh* landMineMesh = smgr.getMesh( LANDMINE_MODEL );
	check( landMineMesh );

	node = smgr.addMeshSceneNode( 
		landMineMesh,
		NULL,							// parent
		-1,								// ID of the node
		defaultPosition,				// position
		vector3df(0.0f,0.0f,0.0f),		// rotation
		vector3df(10.0f,0.5f,10.0f)		// scale
		);
	check(node);
	node->setMaterialFlag( video::EMF_LIGHTING, false );
}

// destructor, protected to force user to call Actor::DestroyActor
LandMine::~LandMine()
{
	check(node);
	world.GetSceneManager().addToDeletionQueue(node);
}

// updates the actor every frame with the elapsed time since last frame
void LandMine::Tick( f32 delta )
{
	switch (landMineState)
	{	
		case state_LANDMINE_IDLE:
		{
			// do nothing, the landmine is waiting to be placed
			break;
		}
		case state_LANDMINE_ARMING:
		{
			// arm the mine if we spend enough time in the arming state
			elapsedTimeInArmingState += delta;
			if( elapsedTimeInArmingState > LANDMINE_ARMING_TIME )
			{
				landMineState = state_LANDMINE_ARMED;
				elapsedTimeInArmingState = 0.0f;
			}
			break;
		}
		case state_LANDMINE_ARMED:
		{
			// do nothing, collision checking does the work when we're in this state
			break;
		}
		case state_LANDMINE_EXPLODING:
		{
			// create an explosion effect
			CreateExplosionEffect();

			// put the mesh in its original default position
			node->setPosition(defaultPosition);

			// play explosion sound effect
			ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/explode1.mp3", node->getAbsolutePosition(), false, false, true );
			sound->setMinDistance( 50.0f );
			sound->drop();

			landMineState = state_LANDMINE_IDLE;
			break;
		}
		default:
		{
			// should not be here
			check(FALSE);
		}
	}
}

// whether collision checks should be done on this projectile
bool LandMine::ShouldPerformCollisionCheck() const
{
	// only check collisions if the landmine is armed
	return landMineState == state_LANDMINE_ARMED;
}

// performs collision handling with various objects in the world
void LandMine::DoCollisions( const CollisionInfo& collInfo )
{
	// get the bounding box for the landmine
	aabbox3d<f32> box = node->getTransformedBoundingBox();

	// whether this landmine needs to explode
	bool bExplode = false;

	// check if we collided with any enemies
	for( u32 i=0; i < collInfo.Actors.size(); ++i )
	{
		if( collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY
			|| collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY_TWO )
		{
			if( CollisionHelper::CheckCollision( collInfo.Actors[i]->GetNode().getTransformedBoundingBox(), box ) )
			{
				// explode the projectile
				bExplode = true;
				break;
			}
		}
	}

	if( bExplode )
	{	
		Explode();
	}
}

// drops the mine in the start position and puts it in the arming state
void LandMine::Place( const vector3df& startPos )
{
	// we should only be placing mines that are in an idle state
	check(landMineState == state_LANDMINE_IDLE);
	node->setPosition(startPos);
	node->updateAbsolutePosition();

	// begin arming the landmine
	landMineState = state_LANDMINE_ARMING;
}

// causes an explosion of the landmine and deals damage to the enemies within the radius
void LandMine::Explode()
{
	check( landMineState == state_LANDMINE_ARMED ); // explosion should only happen when the landmine is armed
	landMineState = state_LANDMINE_EXPLODING;

	// deal damage to any enemies or players within the blast radius
	const array<Actor*>& actors = world.GetActors();
	for( u32 i=0; i < actors.size(); ++i )
	{
		u32 actorMask = ACTOR_ENEMY | ACTOR_ENEMY_TWO;
		if( (actors[i]->GetActorType() & actorMask) != 0 )
		{
			if( CollisionHelper::CheckProximity( actors[i]->GetNode().getAbsolutePosition(), node->getAbsolutePosition(), DAMAGE_RADIUS ) )
			{
				actors[i]->ReceiveDamage( LANDMINE_DAMAGE );
			}
		}
	}

#if DEBUG_DRAW_LANDMINE_EXPLOSION
	// add a spherenode for debug display purposes
	ISceneNode* debugSphere = world.GetSceneManager().addSphereSceneNode( 
		DAMAGE_RADIUS,			// radius
		8,						// polyCount
		NULL,					// parent
		-1,						// ID of the node
		node->getAbsolutePosition(),	// position
		vector3df(0.0f,0.0f,0.0f),		// rotation
		vector3df(1.0f,1.0f,1.0f)		// scale
		);
	check(debugSphere);

	debugSphere->setMaterialFlag( video::EMF_WIREFRAME, true );
	debugSphere->setMaterialFlag( video::EMF_LIGHTING, false );

	scene::ISceneNodeAnimator* anim = world.GetSceneManager().createDeleteAnimator( 500 );
	debugSphere->addAnimator( anim );
	anim->drop();
#endif //DEBUG_DRAW_LANDMINE_EXPLOSION

}

// creates the explosion effect
void LandMine::CreateExplosionEffect()
{
	// create the explosion effect
	ExplosionEffect* pEffect = world.GetFirstAvailableDynamiteExplosionEffect();
	if( pEffect )
	{
		pEffect->StartEffect(node->getAbsolutePosition());
	}
}