#ifndef __SELLING_MACHINE_HPP__
#define __SELLING_MACHINE_HPP__

#include "InteractiveActor.hpp"

class SellingMachine: public InteractiveActor
{
public:
	SellingMachine( GameWorld& gameWorld, irr::video::IVideoDriver& driver );

	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; };
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_INTERACTIVE; }
	void interaction();


protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~SellingMachine();

private:
	// scene graph node for robot
	irr::scene::ISceneNode* node;

	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse* collisionAnimator;

	GameWorld& world;
};

#endif // __SELLING_MACHINE_HPP__