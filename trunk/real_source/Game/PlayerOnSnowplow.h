#ifndef PlayerOnSnowplow_h
#define PlayerOnSnowplow_h

#include <irrlicht/irrlicht.h>
//#include <irrklang/irrKlang.h>
#include "Player.h"

//using namespace irrklang;

class ParticleManager;
namespace irr
{
namespace scene
{
	class CFloorDecalSceneNode;
}
}


// when enabled, lets the snowplow move forward_left, and forward_right
#define ENABLE_DIAGONAL_TRANSLATION 1

// player states 
enum EPlayerOnSnowplowMoveState
{
	state_POS_MOVE_IDLE,			// player is not moving
	state_POS_MOVE_FORWARD,
#if ENABLE_DIAGONAL_TRANSLATION
	state_POS_MOVE_FORWARD_LEFT,
	state_POS_MOVE_FORWARD_RIGHT,
	state_POS_MOVE_LEFT,
	state_POS_MOVE_RIGHT,
#endif //ENABLE_DIAGONAL_TRANSLATION
	state_POS_MOVE_BACK,
	state_POS_MOVE_DEAD
};

enum EPlayerOnSnowplowRotationState
{
	state_POS_ROTATE_IDLE,		// player is not rotating
	state_POS_ROTATE_LEFT,
	state_POS_ROTATE_RIGHT,
};

class PlayerOnSnowplow: public Player
{
public:
	// constructor
	PlayerOnSnowplow( GameWorld& gameWorld, IVideoDriver& driver, ParticleManager& InParticleManager );

	// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
	virtual void RecreateCollisionResponseAnimator();

	// called every frame to update player
	virtual void Tick(f32 delta);
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const { return *snowplow; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_PLAYER_ON_SNOWPLOW; }
	// whether collision checks should be done by this actor
	virtual bool ShouldPerformCollisionCheck() const { return playerState == state_PLAYER_ACTIVE; }
	// performs collision checks between this actor and other objects in the world
	virtual void DoCollisions( const CollisionInfo& collInfo );
	// interface for turning player on/off
	virtual void SetActive( bool bValue );

	// set the movement translation vector for player
	virtual void SetTranslation( const vector3df& trans );
	// set the movement rotation vector for player
	virtual void SetRotation( const vector3df& rot );
	// damage done to player
	virtual void ReceiveDamage( f32 value );
	// check if the player is dead
	bool IsDead() const { return moveState == state_POS_MOVE_DEAD; }

	// accessor methods for node position and rotation
	virtual vector3df GetNodePosition() const { snowplow->updateAbsolutePosition(); return snowplow->getAbsolutePosition(); }
	virtual vector3df GetNodeRotation() const { return snowplow->getRotation(); }
	virtual void SetNodePosition( const vector3df& vect ) { snowplow->setPosition(vect); snowplow->updateAbsolutePosition(); }
	virtual void SetNodeRotation( const vector3df& vect ) { snowplow->setRotation(vect); }

	// unbuffered mouse input 
	virtual void OnMouseEvent( const SEvent::SMouseInput& mouseEvent );

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~PlayerOnSnowplow();

private:
	// diallow copy constructor from being invoked
	PlayerOnSnowplow( const PlayerOnSnowplow& other );

	// updated the player position based on the value of translation set
	void UpdatePosition( f32 delta ); 

	// updates the move state based on the current value of player translation
	void SetMoveState( );

	// updates the move and arms state inside the tick function
	void UpdateRotationState( );
	void UpdateMoveState( f32 delta );

	// udpates the snowplow remaining time and signals the player change if time runs out
	void UpdateSnowplowTime( f32 delta );

	// scene graph node for the player on the snowplow
	IAnimatedMeshSceneNode*					snowplow;
	// cached collision response animator
	ISceneNodeAnimatorCollisionResponse*	collisionAnimator;
	// player's shadow, a simple static texture
	irr::scene::CFloorDecalSceneNode*		shadowNode;
	// player's move direction
	EPlayerOnSnowplowMoveState				moveState;
	// player's rotation direction
	EPlayerOnSnowplowRotationState			rotationState;
	// the delta time with which the player got last updated
	f32										currTickDelta;
	// when the player is dealing damage with the plow
	bool									bIsDealingDamage;

	// the node which contains the particle emmiter 
	IParticleSystemSceneNode*				leftParticleNode;
	IParticleSystemSceneNode*				rightParticleNode;
	// the emitter which is currently set on the node
	IParticleEmitter*						leftEmitter;
	IParticleEmitter*						rightEmitter;
	// player footstep sound effect
//	ISound*									sfxSnowplow;
	f32										sfxTimer;
};

#endif //PlayerOnSnowplow_h
