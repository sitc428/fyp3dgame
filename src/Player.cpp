#include "Player.hpp"

Player::Player(irr::scene::IAnimatedMeshSceneNode* source, irr::core::vector3df position, irr::core::vector3df scale, float speed)
	: _player(source), _speed(speed)
{
	_player->setPosition(position);
	_player->setScale(scale);
	_player->setMaterialFlag(irr::video::EMF_LIGHTING, true);
}

Player::~Player()
{
}

float Player::speed() const
{
	return _speed;
}

irr::scene::IAnimatedMeshSceneNode* Player::getNode()
{
	return _player;
}

irr::core::vector3df Player::getPosition()
{
	return _player->getPosition();
}

void Player::moveForward()
{
}

void Player::moveBackward()
{
}

void Player::moveLeft()
{
}

void Player::moveRight()
{
}
