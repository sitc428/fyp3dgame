#include "DynamiteExplosionEffect.h"
#include "GameWorld.h"
#include "ParticleManager.h"

static const irr::c8*		DYNAMITE_EXPLOSION_SPHERE_MODEL = "../art/sfx/BlastSphere/BlastSphere.ms3d";

static const vector3df		defaultPosition = vector3df(0,-20,0);
static const vector3df		startExplosionScale = vector3df(1.0f,1.0f,1.0f);
static const vector3df		endExplosionScale = vector3df(25.0f,25.0f,25.0f);

static const u32			BLAST_DURATION = 100; //100 milliseconds
static const u32			SMOKE_DURATION = 1000; //1000 milliseconds

DynamiteExplosionEffect::DynamiteExplosionEffect( GameWorld& gameWorld, ParticleManager& InParticleManager )
:	ExplosionEffect(gameWorld,InParticleManager)
,	explosionSphere(NULL)
{
	ISceneManager& smgr = gameWorld.GetSceneManager();

	// crate the explosion sphere scene node
	IMesh* explosionSphereMesh = smgr.getMesh( DYNAMITE_EXPLOSION_SPHERE_MODEL );
	check(explosionSphereMesh);
	explosionSphere = smgr.addMeshSceneNode( 
		explosionSphereMesh,
		NULL,							// parent
		-1,								// ID of the node
		defaultPosition,				// position
		vector3df(0.0f,0.0f,0.0f),		// rotation
		startExplosionScale				// scale
		);

	explosionSphere->setMaterialFlag( video::EMF_LIGHTING, false );
	explosionSphere->setMaterialType( video::EMT_TRANSPARENT_ADD_COLOR );
}

DynamiteExplosionEffect::~DynamiteExplosionEffect()
{
	check(explosionSphere);
	world.GetSceneManager().addToDeletionQueue( explosionSphere );
	explosionSphere = NULL;
}

// called every frame to update actor
void DynamiteExplosionEffect::Tick( f32 delta )
{
	switch(explosionState)
	{
		case state_EXPLOSION_IDLE:
		{
			// do nothing
			break;
		}
		case state_EXPLOSION_EXPLODING:
		{
			explodeElapsedTime += delta;
			if( explodeElapsedTime < ((f32)BLAST_DURATION/1000) )
			{
				// scaling the blast sphere up proportional to the elapsed explosion time
				vector3df explScale = startExplosionScale + (endExplosionScale - startExplosionScale) * explodeElapsedTime/((f32)BLAST_DURATION / 1000) ;
				explosionSphere->setScale( explScale );
			}
			else
			{
				// return the blast sphere back to the original position and restore the default scale
				explosionSphere->setPosition( defaultPosition );
				explosionSphere->setScale( startExplosionScale );

				// stop emitting new particles
				emitter->setMinParticlesPerSecond(0);
				emitter->setMaxParticlesPerSecond(0);
			}

			if( explodeElapsedTime < ((f32)SMOKE_DURATION/1000) )
			{
				// do nothing, don't stop the effect until we passed the smoke duration
			}
			else
			{
				StopEffect();
			}
			break;
		}
		default:
		{
			// should not be here
			check(false);
		}
	}
}

// starts the explosion effect
void DynamiteExplosionEffect::StartEffect( const vector3df& position )
{
	// call super implementation
	ExplosionEffect::StartEffect(position);

	explosionSphere->setPosition(position);
	// create an emitter for the particle effect
	check(emitter==NULL); // make sure we don't leak an existing emitter
	emitter = particleManager.CreateDynamiteExplosion(*particleEffect, SMOKE_DURATION);
	particleManager.CreateSnowExplosion(position, SMOKE_DURATION);
	check(emitter);
}

void DynamiteExplosionEffect::StopEffect()
{
	// call super implementation
	ExplosionEffect::StopEffect();

	particleEffect->setEmitter( NULL );
	emitter->drop();
	emitter = NULL;
	explosionSphere->setPosition( defaultPosition );
	explosionSphere->setScale( startExplosionScale );

}