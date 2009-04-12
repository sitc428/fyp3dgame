#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <irrlicht/irrlicht.h>

#include "Actor.hpp"

// forward declares
class GameEngine;
class GameWorld;
class Player;

class Camera: public Actor
{
public:
	// constructor
	Camera( GameEngine&, GameWorld&, irr::scene::ITriangleSelector&, Player&);

	// called every frame to update camera
	virtual void Tick( irr::f32 delta );
	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; }
	virtual irr::core::vector3df& GetRadius() const { return node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter(); }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_CAMERA; }
	// changes the look at target for this camera
	void SetAimTarget( Player& player );

	// get camera's target's position
	irr::core::vector3df GetTarget();

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~Camera();

private:
	// disallow copy constructor from being invoked
	Camera( const Camera& other );

	void DoInput( irr::f32 );

	irr::core::vector3df translation;
	irr::f32 zoom;

	// scene graph node for camera
	irr::scene::ICameraSceneNode* node;
	// player target for camera
	Player* target;
	// level triangle selector for checking collisions
	irr::scene::ITriangleSelector& levelTriangleSelector;
	// previously hidden node
	irr::scene::ISceneNode* lastSelectedSceneNode;
};

#endif //__CAMERA_HPP__
