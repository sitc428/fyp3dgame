#ifndef __MAIN_CHARACTER_HPP__
#define __MAIN_CHARACTER_HPP__

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
#include "Player.h"

class ProgressCircle;

using namespace irrklang;

namespace irr
{
namespace scene
{
	class CFloorDecalSceneNode;
}
}

enum EMainCharacterActionState
{
	EMCAS_IDLE = 0,
	EMCAS_MOVE = 1,
	EMCAS_ROTATE = 2,
	EMCAS_JUMP = 4,
	EMCAS_ATTACK = 8,
	EMCAS_DEFEND = 16,
	EMCAS_DEAD = 1 << 31
};

// player states 
enum EMainCharacterMoveState
{
	EMCMS_IDLE,			// player is not moving
	EMCMS_FORWARD,
	EMCMS_BACK,
	EMCMS_LEFT,
	EMCMS_RIGHT,
	EMCMS_FORWARD_LEFT,
	EMCMS_FORWARD_RIGHT,
	EMCMS_BACK_LEFT,
	EMCMS_BACK_RIGHT
};

enum EMainCharacterRotateState
{
	EMCRS_IDLE,		// player is not rotating
	EMCRS_LEFT,
	EMCRS_RIGHT
};

class MainCharacter: public Player
{
public:
	// constructor
	MainCharacter( GameWorld& gameWorld, irr::video::IVideoDriver& driver );

	// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
	virtual void RecreateCollisionResponseAnimator();

	// called every frame to update player
	virtual void Tick(irr::f32 delta);
	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; }
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_PLAYER; }

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
	//void DoLaunchProjectile();
	
	// damage done to player
	virtual void ReceiveDamage( irr::f32 value );
	// check if the player is dead
	bool IsDead() const { return action == EMCAS_DEAD; }	

	// unbuffered mouse input 
	virtual void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent );

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~MainCharacter();

private:
	// diallow copy constructor from being invoked
	MainCharacter( const MainCharacter& other );

	// updates the power of the throw meter
	void UpdateThrowMeter( irr::f32 delta );

	// updated the player position based on the value of translation set
	void UpdatePosition( irr::f32 delta ); 

	// MAYBE USEFUL!
	// drops a player footprint on the ground
	//! void PlaceRightFootPrint();
	//! void PlaceLeftFootPrint();

	// updates the move state based on the current value of player translation
	void SetMoveState( );

	// updates the move and arms state inside the tick function
	void UpdateRotationState( );
	void UpdateMoveState( irr::f32 delta );

	// scene graph node for player
	irr::scene::IAnimatedMeshSceneNode* node;

	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse* collisionAnimator;
	
	// scene graph node for player's arms
	// irr::scene::IAnimatedMeshSceneNode* arms;
	
	// player's shadow, a simple static texture
	irr::scene::CFloorDecalSceneNode* shadowNode;

	EMainCharacterActionState action;

	// player's move direction
	EMainCharacterMoveState moveState;
	EMainCharacterMoveState prevMoveState;
	// player's rotation direction
	EMainCharacterRotateState rotationState;

	// the frame number where the walking animation was stopped last, used for restarting it from the right spot
	EMainCharacterMoveState walkStopState;
	irr::f32 walkStopFrameNumber;

	// the meter which tracks how long the player is holding the throw button;
	irr::f32 throwFillupTimer;
	
	// whether the throw power should be increased
	bool bDoFillup;

	// player footstep sound effect
	ISound* sfxFootstep;
	irr::f32 sfxTimer;

	irr::s32 _health;
	irr::s32 _maxHealth;

	ProgressCircle* _healthBar;

	GameWorld& world;
};

#endif //__MAIN_CHARACTER_HPP__