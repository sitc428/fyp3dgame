#ifndef Camera_h
#define Camera_h

#include "irrlicht/irrlicht.h"
#include "irrlicht/vector3d.h"
#include "Actor.h"

// forward declares
class Player;

class Camera: public Actor
{
public:
	// constructor
	Camera( GameWorld& gameWorld, IVideoDriver& driver, ITriangleSelector& levelSelector, Player& player );

	// called every frame to update camera
	virtual void Tick( f32 delta );
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const { return *node; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_CAMERA; }
	// changes the look at target for this camera
	void SetAimTarget( Player& player );

	// get camera's target's position
	vector3df GetTarget();

	void SetPosition( vector3df pos ) { node->setPosition( pos ); }

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~Camera();

private:
	// disallow copy constructor from being invoked
	Camera( const Camera& other );

	// scene graph node for camera
	ICameraSceneNode*						node;
	// player target for camera
	Player*									target;
	// level triangle selector for checking collisions
	ITriangleSelector&						levelTriangleSelector;
	// previously hidden node
	ISceneNode*								lastSelectedSceneNode;
};

#endif //Player_h