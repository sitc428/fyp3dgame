#include "Player.h"
#include "Check.h"
#include "GameEngine.h"

extern GameEngine* GEngine;

// constructor
	Player::Player( GameWorld& gameWorld )
	: Actor(gameWorld)
	, playerState( state_PLAYER_INACTIVE ) 
	, aimVector( irr::core::vector3df(0.0f,0.0f,1.0f) )
	, translation( irr::core::vector3df(0.0f,0.0f,0.0f) ) 
	, rotation( irr::core::vector3df(0.0f,-90.0f,0.0f) )
	,   ammo( 20 )
	, score( 0 )
	, snowplowTimeRemaining( 0.0f )
	, velApprox(0,0,0)
	, health( 100 )
	  , godMode( false )
{
}

// destructor, protected to force user to call Actor::DestroyActor
Player::~Player()
{
}

// interface for turning player on/off
void Player::SetActive( bool bValue )
{
	if( bValue )
	{
		playerState = state_PLAYER_ACTIVE;
	}
	else
	{
		playerState = state_PLAYER_INACTIVE;
	}
}

// set the translation vector for player
void Player::SetTranslation( const irr::core::vector3df& trans )
{
	translation = trans;
}

// set the rotation vector for player
void Player::SetRotation( const irr::core::vector3df& rot )
{
	// we only support rotation about the Y axis for now
	//check(rot.X == 0.0f && rot.Z == 0.0f);

	// update the rotation, the actual node rotation will be applied during Tick
	rotation -= rot;
}

void Player::CopyStateFrom( const Player& other )
{
	translation = other.translation;
	rotation = other.rotation;
	ammo = other.ammo;
	score = other.score;
	health = other.health;
	snowplowTimeRemaining = other.snowplowTimeRemaining;
	aimVector = other.aimVector;

	SetNodeRotation(rotation);
}

void Player::PlayRandomCheer()
{
	/* static const irr::s32 MAX_CHEERS = 4;
	   static irr::s32 randomCheer = ( rand()%MAX_CHEERS );

	   switch( randomCheer )
	   {
	   case 0:
	   GEngine->GetSoundEngine().play2D("../audio/sfx/cheer1.wav");
	   break;
	   case 1:
	   GEngine->GetSoundEngine().play2D("../audio/sfx/cheer2.wav");
	   break;
	   case 2:
	   GEngine->GetSoundEngine().play2D("../audio/sfx/cheer3.wav");
	   break;
	   case 3:
	   GEngine->GetSoundEngine().play2D("../audio/sfx/cheer4.mp3");
	   break;
	   default: check( false ); break;
	   }

	   if( ++randomCheer >= MAX_CHEERS )
	   randomCheer = 0;
	   */
}
