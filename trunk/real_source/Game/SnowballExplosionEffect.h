#ifndef SnowballExplosionEffect_h
#define SnowballExplosionEffect_h

#include "ExplosionEffect.h"

class SnowballExplosionEffect: public ExplosionEffect
{
public:
	// constructor
	SnowballExplosionEffect( GameWorld& gameWorld, class ParticleManager& InParticleManager );

	// called every frame to update actor
	virtual void Tick( f32 delta );
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_EXPLOSION_EFFECT_SNOWBALL; }

	// starts the explosion effect
	virtual void StartEffect( const vector3df& position );
	// stops an explosion in progress, invalid to call if effect is not in progress
	virtual void StopEffect( );
protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~SnowballExplosionEffect();

private:
	// disallow copy constructor from being invoked
	SnowballExplosionEffect( const SnowballExplosionEffect& other );
};

#endif //DynamiteExplosionEffect_h