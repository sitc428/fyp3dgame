#ifndef LandMine_h
#define LandMine_h

#include "Actor.h"

// landmine state 
enum ELandMineState
{
	state_LANDMINE_IDLE,
	state_LANDMINE_ARMING,
	state_LANDMINE_ARMED,
	state_LANDMINE_EXPLODING
};

class LandMine: public Actor
{
public:
	// constructor
	LandMine( GameWorld& gameWorld, irr::video::IVideoDriver& driver, ITriangleSelector& levelTriangleSelector  );

	// updates the actor every frame with the elapsed time since last frame
	virtual void Tick( f32 delta );
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const { return *node; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_LANDMINE; }
	// whether collision checks should be done on this projectile
	virtual bool ShouldPerformCollisionCheck() const;
	// performs collision handling with various objects in the world
	virtual void DoCollisions( const CollisionInfo& collInfo );

	// drops the mine in the start position and puts it in the arming state
	void Place( const vector3df& startPos );

	// accessor for the landmine state
	ELandMineState GetLandMineState() const { return landMineState; }
protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~LandMine();

private:
	// disallow copy constructor from being invoked
	LandMine( const LandMine& other );

	// causes an explosion of the landmine and deals damage to the enemies within the radius
	void Explode();
	// creates the explosion effect
	void CreateExplosionEffect();

	// the scene graph node which contains visual representation of the landmine
	IMeshSceneNode*					node;
	// the state this projectile is currently in
	ELandMineState					landMineState;
	// how long have we spend so far in the arming state
	f32								elapsedTimeInArmingState;
};

#endif //LandMine_h