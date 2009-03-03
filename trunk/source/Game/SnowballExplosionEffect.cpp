#include "SnowballExplosionEffect.h"
#include "GameWorld.h"
#include "ParticleManager.h"

static const vector3df		defaultPosition = vector3df(0,-20,0);
static const u32			SMOKE_DURATION = 500; //500 milliseconds

SnowballExplosionEffect::SnowballExplosionEffect( GameWorld& gameWorld, ParticleManager& InParticleManager )
:	ExplosionEffect(gameWorld,InParticleManager)
{
}

SnowballExplosionEffect::~SnowballExplosionEffect()
{
}

// called every frame to update actor
void SnowballExplosionEffect::Tick( f32 delta )
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
void SnowballExplosionEffect::StartEffect( const vector3df& position )
{
	ExplosionEffect::StartEffect(position);

	// create an emitter for the particle effect
	check(emitter==NULL); // make sure we don't leak an existing emitter
	emitter = particleManager.CreateSnowballExplosion(*particleEffect, SMOKE_DURATION);
	check(emitter);
}

void SnowballExplosionEffect::StopEffect()
{
	ExplosionEffect::StopEffect();

	particleEffect->setEmitter( NULL );
	emitter->drop();
	emitter = NULL;
}