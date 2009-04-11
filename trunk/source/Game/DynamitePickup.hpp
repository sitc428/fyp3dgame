#ifndef DynamitePickup_h
#define DynamitePickup_h

#include "Actor.h"

enum EDynamitePickupState
{
	state_DP_ACTIVE,
	state_DP_RESPAWNING,
};

class DynamitePickup: public Actor
{
public:
	// constructor
	DynamitePickup( GameWorld& gameWorld, const vector3df& position, irr::video::IVideoDriver& driver );

	// called every frame to update actor
	virtual void Tick( f32 delta );
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const { return *node; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_DYNAMITE_PICKUP; }
	// whether collision checks should be done by this actor
	virtual bool ShouldPerformCollisionCheck() const;
	// performs collision checks between this actor and other objects in the world
	virtual void DoCollisions( const CollisionInfo& collInfo );

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~DynamitePickup();

private:
	// disallow copy constructor from being invoked
	DynamitePickup( const DynamitePickup& other );

	// animates the pickup, rotates it and moves it up and down
	void Animate( f32 delta );

	// performs a pickup, puts the object in the respawning state
	void DoPickup();

	// scene graph node which contains the visual representation of the pickup
	irr::scene::ISceneNode*			node;
	// the state this projectile is currently in
	EDynamitePickupState			pickupState;
	// counter reset after pickup, which determines when is the pickup going to be active again.
	f32								respawnTimer;
	// the initial, unmodified position of the node
	vector3df						basePosition;
	// keeps track of the vertical translation phase
	f32								vertTranslationPhase;
};

#endif //DynamitePickup_h