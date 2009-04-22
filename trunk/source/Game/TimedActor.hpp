#ifndef __TIMED_ACTOR_HPP__
#define __TIMED_ACTOR_HPP__

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>

#include <boost/timer.hpp>

#include "Actor.hpp"
#include "ActorTypes.hpp"

/**
 * Timed Actor class
 *
 * The prototype of timed actors in the game.
 */
class TimedActor: public Actor
{
public:
	///! Constructor
	TimedActor( GameEngine&, GameWorld&, bool, irr::f32 );

	//! called every frame to update the actor
	void Tick(irr::f32 delta);

	// returns the node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const = 0;
	virtual irr::core::vector3df GetRadius() = 0;

	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_TIMED; }

	// reaction of interactive objects
	virtual void timeOutAction() = 0;

	void Activate() { activated = true; }
	void Deactivate() { activated = false; }

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~TimedActor();

private:
	bool activated;
	boost::timer theTimer;
	irr::f32 timeout;
};

#endif // __TIMED_ACTOR_HPP__
