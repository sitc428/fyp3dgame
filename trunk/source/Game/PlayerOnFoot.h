#ifndef PlayerOnFoot_h
#define PlayerOnFoot_h

#include <irrlicht/irrlicht.h>
//#include <irrklang/irrKlang.h>
#include "Player.h"

//using namespace irrklang;

class DynamiteProjectile;
class SnowballProjectile;
namespace irr
{
namespace scene
{
	class CFloorDecalSceneNode;
}
}

// player states 
enum EPlayerMoveState
{
	state_PLAYER_MOVE_IDLE,			// player is not moving
	state_PLAYER_MOVE_FORWARD,
	state_PLAYER_MOVE_BACK,
	state_PLAYER_MOVE_LEFT,
	state_PLAYER_MOVE_RIGHT,
	state_PLAYER_MOVE_FORWARD_LEFT,
	state_PLAYER_MOVE_FORWARD_RIGHT,
	state_PLAYER_MOVE_BACK_LEFT,
	state_PLAYER_MOVE_BACK_RIGHT,
	state_PLAYER_MOVE_DEAD
};

enum EPlayerRotationState
{
	state_PLAYER_ROTATE_IDLE,		// player is not rotating
	state_PLAYER_ROTATE_LEFT,
	state_PLAYER_ROTATE_RIGHT,
};

enum EPlayerArmsState
{
	state_PLAYER_ARMS_IDLE,
	state_PLAYER_ARMS_WALKING,
	state_PLAYER_ARMS_THROW,
	state_PLAYER_ARMS_THROWING,
};

// gets called when the throw animation has finished
class ThrowingAnimationEndCallback: public irr::scene::IAnimationEndCallBack
{
public:
	// constructor
	explicit ThrowingAnimationEndCallback( class PlayerOnFoot& player ):
	OwningPlayer(player)
	{
	}

	virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node);
private:
	class PlayerOnFoot& OwningPlayer;
};

class PlayerOnFoot: public Player
{
public:
	// constructor
	PlayerOnFoot( GameWorld& gameWorld, irr::video::IVideoDriver& driver );

	// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
	virtual void RecreateCollisionResponseAnimator();

	// called every frame to update player
	virtual void Tick(irr::f32 delta);
	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_PLAYER; }
	// interface for turning player on/off
	virtual void SetActive( bool bValue ); 

	// set the movement translation vector for player
	virtual void SetTranslation( const irr::core::vector3df& trans );
	// set the movement rotation vector for player
	virtual void SetRotation( const irr::core::vector3df& rot );

	// accessor methods for node position and rotation
	virtual irr::core::vector3df GetNodePosition() const { node->updateAbsolutePosition(); return node->getAbsolutePosition(); }
	virtual irr::core::vector3df GetNodeRotation() const { return node->getRotation(); }
	virtual void SetNodePosition( const irr::core::vector3df& vect ) { node->setPosition(vect); node->updateAbsolutePosition(); }
	virtual void SetNodeRotation( const irr::core::vector3df& vect ) { node->setRotation(vect); }

	// sets the player into firing state
	void DoLaunchProjectile();
	
	// damage done to player
	virtual void ReceiveDamage( irr::f32 value );
	// check if the player is dead
	bool IsDead() const { return moveState == state_PLAYER_MOVE_DEAD; }	

	// unbuffered mouse input 
	virtual void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent );

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~PlayerOnFoot();

private:
	// diallow copy constructor from being invoked
	PlayerOnFoot( const PlayerOnFoot& other );

	// updates the power of the throw meter
	void UpdateThrowMeter( irr::f32 delta );

	// updated the player position based on the value of translation set
	void UpdatePosition( irr::f32 delta ); 

	// drops a player footprint on the ground
	void PlaceRightFootPrint();
	void PlaceLeftFootPrint();

	// updates the move state based on the current value of player translation
	void SetMoveState( );
	// updates the arms state based on the current move state
	void SetArmsState( );

	// updates the move and arms state inside the tick function
	void UpdateRotationState( );
	void UpdateMoveState( irr::f32 delta );
	void UpdateArmsState( );

	// makes the player throw the dynamite
	void ShootDynamite( irr::f32 power, DynamiteProjectile& projectile );
	// makes the player throw a snowball
	void ShootSnowball( irr::f32 power, SnowballProjectile& projectile );
	// makes the player put a landmine on the ground
	void PlaceMine( class LandMine& mine );

	// scene graph node for player
	irr::scene::IAnimatedMeshSceneNode*					node;
	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse*	collisionAnimator;
	// scene graph node for player's arms
	irr::scene::IAnimatedMeshSceneNode*					arms;
	// player's shadow, a simple static texture
	irr::scene::CFloorDecalSceneNode*		shadowNode;
	// player's move direction
	EPlayerMoveState						moveState;
	EPlayerMoveState						prevMoveState;
	// player's rotation direction
	EPlayerRotationState					rotationState;
	// state of the arms, action that the arms are executing. i.e throwing
	EPlayerArmsState						armsState;
	EPlayerArmsState						prevArmsState;
	// the frame number where the walking animation was stopped last, used for restarting it from the right spot
	EPlayerMoveState						walkStopState;
	irr::f32										walkStopFrameNumber;
	irr::f32										armsStopFrameNumber;

	// the meter which tracks how long the player is holding the throw button;
	irr::f32										throwFillupTimer;
	// whether the throw power should be increased
	bool									bDoFillup;
	// player footstep sound effect
//	ISound*									sfxFootstep;
	irr::f32										sfxTimer;

	// callback used for ending throwing animation
	irr::scene::IAnimationEndCallBack*					ThrowAnimEndCallback;
	GameWorld&								world;

	friend class ThrowingAnimationEndCallback;
};

#endif //PlayerOnFoot_h