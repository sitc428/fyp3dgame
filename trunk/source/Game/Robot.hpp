#ifndef __ROBOT_HPP__
#define __ROBOT_HPP__

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>

#include "Actor.hpp"

class Robot: public Actor
{
public:
	Robot( GameEngine&, GameWorld& );

	// called every frame to update player
	virtual void Tick(irr::f32 delta);
	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; }
	virtual irr::core::vector3df GetRadius() { return node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter(); }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_ROBOT; }
	virtual void RecreateCollisionResponseAnimator();

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~Robot();

private:
	// scene graph node for robot
	irr::scene::IAnimatedMeshSceneNode* node;

	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse* collisionAnimator;
};
	
#endif // __ROBOT_HPP__