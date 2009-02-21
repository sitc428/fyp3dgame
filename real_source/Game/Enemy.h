#ifndef Enemy_h
#define Enemy_h

#include <irrlicht/irrlicht.h>
//#include <irrklang/irrKlang.h>
#include "Actor.h"
#include "Check.h"

//using namespace irrklang;
namespace irr
{
namespace scene
{
	class CFloorDecalSceneNode;
}
}

/**
*	The enemy class represents the AI oponents you are fighting against
*/
class Enemy: public Actor
{
public:
	// constructor
	Enemy( GameWorld& gameWorld, const vector3df& position, ITriangleSelector& levelTriangleSelector );

	// updates the enemy every frame
	virtual void Tick( f32 delta );
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const { return *node; }
	// interface for attaching and detaching external actor, you can specify an optional name of the node to attach to
	virtual void AttachActor( Actor& actorToAttach, const c8* nodeName=NULL );
	virtual void DetachActor( Actor& actorToDetach );
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_ENEMY; }
	// interface for damaging the enemy
	virtual void ReceiveDamage( f32 value );
	// set target actor the enemy attacks
	virtual void SetAimTarget( Actor& targetActor );
	// gets the target node of our enemy
	void const GetAimTarget();
	// perform collision checks
	virtual bool ShouldPerformCollisionCheck() const { return true; }
	// collision check
	virtual void DoCollisions( const CollisionInfo& collInfo );
	// plays a new random sound for the enemy
	virtual void ChooseNewSound();

private:
	// disallow copy constructor from being invoked
	Enemy( const Enemy& other );

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~Enemy();

	// scene graph node which contains the visual representation of the enemy
	IAnimatedMeshSceneNode*			node;
	// enemy shadow, a simple static texture
	irr::scene::CFloorDecalSceneNode*		shadowNode;
	// enemy hitpoints
	f32								hitpoints;
	// current aim vector
	vector3df						aimVector;
	// the aim vector the enemy is trying to achieve
	vector3df						targetVector;
	// the target actor
	Actor*							targetActor;
	// enemy rotation
	f32								rotation;
	// enemy speed
	f32								speed;
	f32								sfxTimer;

	// updated 3d sound effects associated with enemy
	enum EEnemySounds
	{
		sound_ENEMY_ALIVE=0,
		sound_TOTAL_NUM,
	};
//	ISound*							sounds[sound_TOTAL_NUM];						
};

#endif //Enemy_h