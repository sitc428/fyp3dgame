#ifndef EnemyTwo_h
#define EnemyTwo_h

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
#include "Actor.h"
#include "Check.h"

class SnowballProjectile;

using namespace irrklang;
namespace irr
{
namespace scene
{
	class CFloorDecalSceneNode;
}
}

enum EEnemyTwoState
{
	state_ENEMY_TWO_MOVING,
	state_ENEMY_TWO_THROWING,
	state_ENEMY_TWO_FOLLOWTHROUGH
};

// gets called when the throw animation has finished
class EnemyTwoThrowingAnimationEndCallback: public IAnimationEndCallBack
{
public:
	// constructor
	explicit EnemyTwoThrowingAnimationEndCallback( class EnemyTwo& enemy ):
	OwningEnemy(enemy)
	{
	}

	virtual void OnAnimationEnd(IAnimatedMeshSceneNode* node);
private:
	class EnemyTwo& OwningEnemy;
};

// gets called when the followthrough animation has finished
class EnemyTwoFollowthroughAnimationEndCallback: public IAnimationEndCallBack
{
public:
	// constructor
	explicit EnemyTwoFollowthroughAnimationEndCallback( class EnemyTwo& enemy ):
	OwningEnemy(enemy)
	{
	}

	virtual void OnAnimationEnd(IAnimatedMeshSceneNode* node);
private:
	class EnemyTwo& OwningEnemy;
};

/**
*	The enemy class represents the AI oponents you are fighting against
*/
class EnemyTwo: public Actor
{
public:
	// constructor
	EnemyTwo( GameWorld& gameWorld, const vector3df& position, ITriangleSelector& levelTriangleSelector );

	// updates the enemy every frame
	virtual void Tick( f32 delta );
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const { return *node; }
	// interface for attaching and detaching external actor, you can specify an optional name of the node to attach to
	virtual void AttachActor( Actor& actorToAttach, const c8* nodeName=NULL );
	virtual void DetachActor( Actor& actorToDetach );
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_ENEMY_TWO; }
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
	// shoot snowball
	virtual void ShootSnowball( SnowballProjectile& projectile );
	// plays a new random sound for the enemy
	virtual void ChooseNewSound();

private:
	// disallow copy constructor from being invoked
	EnemyTwo( const EnemyTwo& other );

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~EnemyTwo();

	// scene graph node which contains the visual representation of the enemy
	IAnimatedMeshSceneNode*			node;
	// enemy shadow, a simple static texture
	irr::scene::CFloorDecalSceneNode*		shadowNode;
	// current state of the enemy
	EEnemyTwoState					enemyTwoState;
	EEnemyTwoState					prevEnemyTwoState;
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
	// time between throws
	f32								timeDeltaBetweenThrows;
	f32								timeBetweenThrows;
	f32								sfxTimer;

	// updated 3d sound effects associated with enemy
	enum EEnemyTwoSounds
	{
		sound_ENEMY_ALIVE=0,
		sound_TOTAL_NUM,
	};
	ISound*							sounds[sound_TOTAL_NUM];

	// callback used for ending throwing animation
	EnemyTwoThrowingAnimationEndCallback*			ThrowAnimEndCallback;
	EnemyTwoFollowthroughAnimationEndCallback*		FollowthroughAnimEndCallback;

	friend class EnemyTwoThrowingAnimationEndCallback;
	friend class EnemyTwoFollowthroughAnimationEndCallback;
};

#endif //EnemyTwo_h