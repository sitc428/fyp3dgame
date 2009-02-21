#ifndef Actor_h
#define Actor_h

#include <irrlicht/irrlicht.h>
#include "ActorTypes.h"
#include "Check.h"

using namespace irr;
using namespace irr::scene;
using namespace irr::core;
using namespace irr::video;

// forward declares
class GameWorld;
struct CollisionInfo;

// different states the actor can have
enum EActorState
{
	state_ACTOR_ALIVE,	// actor exists and should be ticked	
	state_ACTOR_DEAD	// actor needs to be deleted from the actor's list in DoCleanup()
};

/**
*	Actor is an abstract class which encapsulates an entity that can be placed in the world
*/
class Actor
{
public:
	// constructor
	explicit Actor( GameWorld& gameWorld );

	// called every frame to update the actor
	virtual void Tick( f32 delta ) = 0;
	// returns the graph node of the actor by const reference, the derived classes are assumed to all have a node of some kind
	virtual ISceneNode& GetNode() const = 0;
	// interface for attaching and detaching external actor, you can specify an optional name of the node to attach to
	virtual void AttachActor( Actor& actorToAttach, const c8* nodeName=NULL );
	virtual void DetachActor( Actor& actorToDetach );
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_NONE; }
	// get the current state of the actor
	EActorState GetActorState() const { return state; }
	// whether collision checks should be done by this actor
	virtual bool ShouldPerformCollisionCheck() const { return false; }
	// performs collision checks between this actor and other objects in the world
	virtual void DoCollisions( const CollisionInfo& collInfo ) { check(false); }
	// interface for dealing damage to the actor
	virtual void ReceiveDamage( f32 value ) { check(false); }

	// static function that should be used to destroy actors
	static void DestroyActor( Actor*& actorToDestroy );

private:
	// disallow copy constructor from being invoked
	Actor( const Actor& other);

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~Actor() {}
	// cleans up the actor state, _must_ be called right before destruction, you can call virtual functions from here
	void Cleanup();

	// game world this actor belongs to
	GameWorld&				world;
	// current state of the actor
	EActorState				state;
	// keeps track of any externally attached actors
	array<Actor*>			attachActorChildren;
	// the partent that we're currently attached to
	Actor*					attachActorParent;
};

#endif //Actor_h
