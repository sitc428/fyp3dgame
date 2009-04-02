#ifndef __ROBOT_HPP__
#define __ROBOT_HPP__

#include "Actor.h"

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>

class Robot: public Actor
{
public:
	Robot( GameWorld& gameWorld, irr::video::IVideoDriver& driver );

	// called every frame to update player
	virtual void Tick(irr::f32 delta);
	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_ROBOT; }


protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~Robot();

private:
	// scene graph node for robot
	irr::scene::IAnimatedMeshSceneNode* node;

	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse* collisionAnimator;

	GameWorld& world;
};
	
#endif // __ROBOT_HPP__