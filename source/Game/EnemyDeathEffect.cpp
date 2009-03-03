#include "EnemyDeathEffect.h"
#include "GameWorld.h"
#include "ParticleManager.h"

static const vector3df		defaultPosition = vector3df(0,-20,0);
static const u32			BLAST_DURATION = 200; //100 milliseconds
static const u32			SMOKE_DURATION = 4000; //4000 milliseconds

EnemyDeathEffect::EnemyDeathEffect( GameWorld& gameWorld, ParticleManager& InParticleManager )
:	ExplosionEffect(gameWorld,InParticleManager)
{	
}

EnemyDeathEffect::~EnemyDeathEffect()
{
}

// called every frame to update actor
void EnemyDeathEffect::Tick( f32 delta )
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
			if( explodeElapsedTime > ((f32)BLAST_DURATION/1000) )
			{
				// stop emitting new particles
				emitter->setMinParticlesPerSecond(0);
				emitter->setMaxParticlesPerSecond(0);
			}

			if( explodeElapsedTime > ((f32)SMOKE_DURATION/1000) )
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
void EnemyDeathEffect::StartEffect( const vector3df& position )
{
	// call super implementation
	ExplosionEffect::StartEffect(position);

	// create an emitter for the particle effect
	check(emitter==NULL); // make sure we don't leak an existing emitter
	emitter = particleManager.CreateSnowmanDeathExplosion(*particleEffect, SMOKE_DURATION);
	check(emitter);
}

void EnemyDeathEffect::StopEffect()
{
	// call super implementation
	ExplosionEffect::StopEffect();

	particleEffect->setEmitter( NULL );
	emitter->drop();
	emitter = NULL;
}