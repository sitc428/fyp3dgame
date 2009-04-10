#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Actor.h"

enum EPlayerState
{
	state_PLAYER_ACTIVE,   // this player is currently being active and used
	state_PLAYER_INACTIVE  // this player is idle, waiting to be switched to
};

/**
 * Abstract base class for the different players
 */
class Player: public Actor
{
	public:
		// constructor
		Player( GameWorld& gameWorld );

		// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
		virtual void RecreateCollisionResponseAnimator() = 0;

		// called every frame to update player
		virtual void Tick(irr::f32 delta) = 0;
		// returns the graph node of the actor by const reference
		virtual irr::scene::ISceneNode& GetNode() const = 0;
		// interface for identifying the type of actor
		virtual EActorType GetActorType() const = 0;
		// interface for turning player on/off
		virtual void SetActive( bool bValue ); 
		bool IsActive() const { return playerState == state_PLAYER_ACTIVE; }

		// check if the player is dead
		virtual bool IsDead() const = 0;

		// accessor methods for node position and rotation
		virtual irr::core::vector3df GetNodePosition() const = 0;
		virtual irr::core::vector3df GetNodeRotation() const = 0;
		virtual void SetNodePosition( const irr::core::vector3df& vect ) = 0;
		virtual void SetNodeRotation( const irr::core::vector3df& vect ) = 0;

		virtual void SetTranslation( const irr::core::vector3df& trans );
		virtual void SetRotation( const irr::core::vector3df& rot );
		const irr::core::vector3df& GetTranslation() const { return translation; }
		const irr::core::vector3df& GetRotation() const { return rotation; }
		const irr::core::vector3df& GetAimVector() const { return aimVector; } 
		const irr::core::vector3df& GetFaceVector() const { return faceVector; } 

		irr::core::vector3df GetVelApprox() { return velApprox; }

		// unbuffered mouse input 
		virtual void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent ) {};

		virtual void SetHealth( irr::f32 pHealth ) { health = pHealth; }
		irr::u32 GetHealth() const { return health; }
		irr::u32 GetMaxHealth() const { return max_health;}
	
		// god mode
		virtual void SetGodMode( bool enable=true ) { godMode=enable; }
		virtual bool HasGodMode() { return godMode; }

	private:
		// diallow copy constructor from being invoked
		Player( const Player& other );

	protected:
		// destructor, protected to force user to call Actor::DestroyActor
		virtual ~Player();

		// tracks whether this player is currently active
		EPlayerState playerState;

		// player is aiming at
		irr::core::vector3df aimVector;

		// player is facing at
		irr::core::vector3df faceVector;

		// player translation
		irr::core::vector3df translation;
		// player rotation
		irr::core::vector3df rotation;

		// approximation of movement velocity used by AI
		irr::core::vector3df velApprox;

		irr::u32 health;
		irr::u32 max_health;
	
		// god mode
		bool godMode;
};

#endif //__PLAYER_HPP__
