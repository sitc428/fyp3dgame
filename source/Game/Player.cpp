#include "Player.hpp"
#include "Check.hpp"
#include "GameEngine.hpp"
#include <iostream>

// constructor
Player::Player( GameEngine& gameEngine, GameWorld& gameWorld )
	:Actor(gameEngine, gameWorld),
	playerState( state_PLAYER_INACTIVE ),
	aimVector( irr::core::vector3df(0.0f, 0.0f, -1.0f) ),
	faceVector( irr::core::vector3df(0.0f, 0.0f, -1.0f) ),
	translation( irr::core::vector3df(0.0f, 0.0f, 0.0f) ),
	rotation( irr::core::vector3df(0.0f, 0.0f, 0.0f) ),
	health(1000),
	max_health(1000),
	godMode( false )
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
	// update the rotation, the actual node rotation will be applied during Tick
	rotation = rot;
}