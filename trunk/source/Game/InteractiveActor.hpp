#ifndef __INTERACTIVE_ACTOR_HPP__
#define __INTERACTIVE_ACTOR_HPP__

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>

#include "Actor.hpp"

/**
 * Interactive Actor class
 *
 * The prototype of interactive actors in the game.
 */
class InteractiveActor: public Actor
{
public:
	///! Constructor
	InteractiveActor( GameEngine&, GameWorld& );

	//! called every frame to update the actor
	void Tick(irr::f32 delta);

	// returns the node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; }
	virtual irr::core::vector3df GetRadius() { return node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter(); }

	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_INTERACTIVE; }

	// reaction of interactive objects
	virtual void interaction(irr::f32) = 0;

	// acceptable interactive distance
	virtual irr::f32 acceptableDistance() = 0;

	// terminate the interactive action
	void finishAction();

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~InteractiveActor();

	// the node
	irr::scene::ISceneNode* node;

	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse* collisionAnimator;

private:
	bool interacting;
};

#endif // __INTERACTIVE_ACTOR_HPP__