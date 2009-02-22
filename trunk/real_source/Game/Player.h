#ifndef Player_h
#define Player_h

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

		// accessors for player's ammo
		void AddAmmo( irr::s32 value ) { ammo += value; }
		void SetAmmo( irr::s32 value ) { ammo = value; }
		irr::s32 GetAmmo() const { return ammo; }
		// accessors for player's score
		irr::s32 GetScore() const { return score; }
		void SetScore( irr::s32 value ) { score = value; }
		void AddScore( irr::s32 value ) { score += value; }

		// replenishes player's snowplow time
		void AddSnowplowTime( irr::f32 time ) { snowplowTimeRemaining += time; }
		void SetSnowplowTime( irr::f32 time ) { snowplowTimeRemaining = time; }
		// accessor for player's snowplow time
		irr::f32 GetSnowplowTime() const { return snowplowTimeRemaining; }

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

		void CopyStateFrom( const Player& other );

		irr::core::vector3df GetVelApprox() { return velApprox; }

		// unbuffered mouse input 
		virtual void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent ) {};

		virtual void PlayRandomCheer();

		virtual void SetHealth( irr::f32 pHealth ) { health = pHealth; }
		irr::f32 GetHealth() const { return health; }

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
		// target player is aiming at
		irr::core::vector3df aimVector;
		// player translation
		irr::core::vector3df translation;
		// player rotation
		irr::core::vector3df rotation;
		// player's ammo remaining
		irr::s32 ammo;
		// player's current score
		irr::s32 score;
		// player's snowplow time remaining
		irr::f32 snowplowTimeRemaining;
		// approximation of movement velocity used by AI
		irr::core::vector3df velApprox;
		// player's health
		irr::f32 health;
		// god mode
		bool godMode;
};

#endif //Player_h
