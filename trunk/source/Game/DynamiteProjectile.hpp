#ifndef DynamiteProjectile_h
#define DynamiteProjectile_h

#include "irrlicht/irrTypes.h"
#include "irrlicht/vector3d.h"
#include "Actor.h"

// forward class declares
class ParticleManager;
struct CollisionInfo;


// snowball state 
enum EDynamiteProjectileState
{
	state_DYNAMITE_IDLE,
	state_DYNAMITE_MOVING,
	state_DYNAMITE_ATTACHED,
	state_DYNAMITE_EXPLODE,
};

class DynamiteProjectile: public Actor
{
public:
	DynamiteProjectile( GameWorld& gameWorld,
						irr::video::IVideoDriver& driver );

	// updates the projectile every frame with the elapsed time since last frame
	virtual void Tick( f32 delta );
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const { return *node; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_DYNAMITE; }
	// whether collision checks should be done on this projectile
	virtual bool ShouldPerformCollisionCheck() const;
	// performs collision handling with various objects in the world
	virtual void DoCollisions( const CollisionInfo& collInfo );
	// called whenever a dynamite is affected by another dynamite explosion
	virtual void ReceiveDamage( f32 value );

	// launches the projectile, using specified start location and direction vector
	void Launch( const vector3df& startPos, const vector3df& startRot, const vector3df& direction, f32 speed );

	// accessor for the snowball state
	EDynamiteProjectileState GetDynamiteState() const { return state; }
protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~DynamiteProjectile();

private:
	// disallow copy constructor from being invoked
	DynamiteProjectile( const DynamiteProjectile& other );

	// called to setup the joints to exclude static member
	void InitAttachJoints();

	// animates the projectile, rotates it when thrown
	void Animate( f32 delta );

	// returns the projectile to the default position
	void ResetProjectile();

	// causes an explosion of the projectile
	void Explode();

	// creates the explosion effect
	void CreateExplosionEffect();

	// the outer scene graph node which contains the the projectile
	ISceneNode*						node;
	// the inner scene graph node which contains the the mesh, animated node to be able to access specific joints in it
	IAnimatedMeshSceneNode*			meshNode;
	// spark joint node, where we attach the spark particle effect
	IParticleEmitter*				sparkEmitter;
	// the state this projectile is currently in
	EDynamiteProjectileState		state;
	// position from which the projectile was launched
	vector3df						launchStartPosition;
	// projectile's velocity
	vector3df						launchVelocity;
	// current elapsed time since launch
	f32								launchElapsedTime;							
	// keeps track of how long the explosion has been going on
	f32								explodeElapsedTime;

	// setup a table of joints that we're not supposed to attach the dynamite to
	static array<stringc>		ATTACH_JOINTS;
};

#endif //DynamiteProjectile_h