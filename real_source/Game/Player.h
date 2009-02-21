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
	virtual void Tick(f32 delta) = 0;
	// returns the graph node of the actor by const reference
	virtual ISceneNode& GetNode() const = 0;
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const = 0;
	// interface for turning player on/off
	virtual void SetActive( bool bValue ); 
	bool IsActive() const { return playerState == state_PLAYER_ACTIVE; }

	// accessors for player's ammo
	void AddAmmo( s32 value ) { ammo += value; }
	void SetAmmo( s32 value ) { ammo = value; }
	s32 GetAmmo() const { return ammo; }
	// accessors for player's score
	s32 GetScore() const { return score; }
	void SetScore( s32 value ) { score = value; }
	void AddScore( s32 value ) { score += value; }

	// replenishes player's snowplow time
	void AddSnowplowTime( f32 time ) { snowplowTimeRemaining += time; }
	void SetSnowplowTime( f32 time ) { snowplowTimeRemaining = time; }
	// accessor for player's snowplow time
	f32 GetSnowplowTime() const { return snowplowTimeRemaining; }

	// check if the player is dead
	virtual bool IsDead() const = 0;

	// accessor methods for node position and rotation
	virtual vector3df GetNodePosition() const = 0;
	virtual vector3df GetNodeRotation() const = 0;
	virtual void SetNodePosition( const vector3df& vect ) = 0;
	virtual void SetNodeRotation( const vector3df& vect ) = 0;

	virtual void SetTranslation( const vector3df& trans );
	virtual void SetRotation( const vector3df& rot );
	const vector3df& GetTranslation() const { return translation; }
	const vector3df& GetRotation() const { return rotation; }
	const vector3df& GetAimVector() const { return aimVector; }	

	void CopyStateFrom( const Player& other );

	vector3df GetVelApprox() { return velApprox; }

	// unbuffered mouse input 
	virtual void OnMouseEvent( const SEvent::SMouseInput& mouseEvent ) {};

	virtual void PlayRandomCheer();

	virtual void SetHealth( f32 pHealth ) { health = pHealth; }
	f32 GetHealth() const { return health; }

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
	EPlayerState							playerState;
	// target player is aiming at
	vector3df								aimVector;
	// player translation
	vector3df								translation;
	// player rotation
	vector3df								rotation;
	// player's ammo remaining
	s32										ammo;
	// player's current score
	s32										score;
	// player's snowplow time remaining
	f32										snowplowTimeRemaining;
	// approximation of movement velocity used by AI
	vector3df								velApprox;
	// player's health
	f32										health;
	// god mode
	bool									godMode;
};

#endif //Player_h