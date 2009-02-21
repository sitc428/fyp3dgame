#ifndef SnowballProjectile_h
#define SnowballProjectile_h

#include "irrlicht/irrTypes.h"
#include "irrlicht/vector3d.h"
#include "Actor.h"

// forward class declares
class ParticleManager;
struct CollisionInfo;


// snowball state 
enum ESnowballProjectileState
{
	state_SNOWBALL_IDLE,
	state_SNOWBALL_MOVING,
	state_SNOWBALL_EXPLODING
};

class SnowballProjectile: public Actor
{
public:
	// constructor
	SnowballProjectile( GameWorld& gameWorld, irr::video::IVideoDriver& driver );

	// updates the projectile every frame with the elapsed time since last frame
	virtual void Tick( f32 delta );
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const { return *node; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_SNOWBALL; }
	// whether collision checks should be done on this projectile
	virtual bool ShouldPerformCollisionCheck() const;
	// performs collision handling with various objects in the world
	virtual void DoCollisions( const CollisionInfo& collInfo );

	// launches the projectile, using specified start location and direction vector
	void Launch( const vector3df& start, const vector3df& direction, f32 speed );

	// accessor for the snowball state
	ESnowballProjectileState GetSnowballState() const { return state; }

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~SnowballProjectile();

private:
	// disallow copy constructor from being invoked
	SnowballProjectile( const SnowballProjectile& other );

	// returns the projectile to the default position
	void ResetProjectile();

	// causes an explosion of the projectile
	void Explode();

	// creates the explosion effect
	void CreateParticleExplosion();

	// scene graph node which contains the visual representation of the projectile
	IMeshSceneNode*					node;
	// the state this projectile is currently in
	ESnowballProjectileState		state;
	// position from which the projectile was launched
	vector3df						launchStartPosition;
	// projectile's velocity
	vector3df						launchVelocity;
	// current elapsed time since launch
	f32								launchElapsedTime;
};

#endif //SnowballProjectile_h