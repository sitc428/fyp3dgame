#ifndef DynamiteExplosionEffect_h
#define DynamiteExplosionEffect_h

#include "ExplosionEffect.h"

class DynamiteExplosionEffect: public ExplosionEffect
{
public:
	// constructor
	DynamiteExplosionEffect( GameWorld& gameWorld, class ParticleManager& InParticleManager );

	// called every frame to update actor
	virtual void Tick( f32 delta );
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_EXPLOSION_EFFECT_DYNAMITE; }

	// starts the explosion effect
	virtual void StartEffect( const vector3df& position );
	// stops an explosion in progress, invalid to call if effect is not in progress
	virtual void StopEffect( );
protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~DynamiteExplosionEffect();

private:
	// disallow copy constructor from being invoked
	DynamiteExplosionEffect( const DynamiteExplosionEffect& other );

	// the node which contains the explosion sphere mesh
	IMeshSceneNode*					explosionSphere;
};

#endif //DynamiteExplosionEffect_h