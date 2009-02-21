#include "ExplosionEffect.h"
#include "Check.h"
#include "GameWorld.h"
#include "ParticleManager.h"

static const vector3df		defaultPosition = vector3df(0,-20,0);

ExplosionEffect::ExplosionEffect( GameWorld& gameWorld, ParticleManager& InParticleManager )
:	Actor(gameWorld)
,	explosionState(state_EXPLOSION_IDLE)
,	particleEffect(NULL)
,	emitter(NULL)
,	explodeElapsedTime(0.0f)
,	particleManager(InParticleManager)
{
	ISceneManager& smgr = gameWorld.GetSceneManager();

	// create a particle system node
	particleEffect = smgr.addParticleSystemSceneNode( false, 0, -1, defaultPosition );
}

ExplosionEffect::~ExplosionEffect()
{
	check(particleEffect);
	world.GetSceneManager().addToDeletionQueue( particleEffect );
	particleEffect = NULL;
}

// starts the explosion effect
void ExplosionEffect::StartEffect( const vector3df& position )
{
	check(explosionState == state_EXPLOSION_IDLE);
	check(particleEffect);
	// set the position of the particle effect
	particleEffect->setPosition(position);

	explosionState = state_EXPLOSION_EXPLODING;
	explodeElapsedTime = 0.0f;
}

void ExplosionEffect::StopEffect()
{
	check(explosionState == state_EXPLOSION_EXPLODING);
	particleEffect->setPosition( defaultPosition );
	explosionState = state_EXPLOSION_IDLE;
	explodeElapsedTime = 0.0f;
}
