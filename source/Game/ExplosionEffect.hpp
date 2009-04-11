/**
* Explosion effect is responsible for managing a single explosion
*/
#ifndef ExplosionEffect_h
#define ExplosionEffect_h

#include "Actor.h"

// explosion effect state 
enum EExplosionEffectState
{
	state_EXPLOSION_IDLE,
	state_EXPLOSION_EXPLODING
};

class ExplosionEffect: public Actor
{
public:
	// constructor
	ExplosionEffect( GameWorld& gameWorld, class ParticleManager& InParticleManager );

	// called every frame to update actor
	virtual void Tick( irr::f32 delta ) = 0;
	// returns the graph node of the actor by const reference, the derived classes are assumed to all have a node of some kind
	virtual irr::scene::ISceneNode& GetNode() const { return *particleEffect; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const = 0;
	// returns the current explosion state
	EExplosionEffectState GetExplosionState() const { return explosionState; }

	// starts the explosion effect
	virtual void StartEffect( const irr::core::vector3df& position );
	// stops an explosion in progress, invalid to call if effect is not in progress
	virtual void StopEffect( );

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~ExplosionEffect();
	// disallow copy constructor from being invoked
	ExplosionEffect( const ExplosionEffect& other );

	// current state of the effect
	EExplosionEffectState			explosionState;
	// the node which contains the particle emmiter 
	irr::scene::IParticleSystemSceneNode*		particleEffect;
	// the emitter which is currently set on the node, always NULL if the state is state_EXPLOSION_IDLE
	irr::scene::IParticleEmitter*				emitter;
	// keeps track of how long the explosion has been going on
	f32								explodeElapsedTime;
	// particle manager which creates the particle emmiters
	ParticleManager&				particleManager;
};

#endif //ExplosionEffect_h
