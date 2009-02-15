#include "Player.hpp"

Player::Player(irr::scene::IAnimatedMeshSceneNode* source, irr::video::ITexture* texture, irr::core::vector3df position, irr::core::vector3df scale, float speed)
	: _player(source), _speed(speed), _movingForward(true), _rotation(0)
{
	_player->setLoopMode(false);
	_player->setMaterialTexture(0, texture);
	_player->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_player->setPosition(position);
	_player->setScale(scale);
	/*_player->setMaterialTexture(0, texture);
	_player->setMaterialType(irr::video::EMT_SOLID);
	_player->setMaterialFlag(irr::video::EMF_LIGHTING, true);*/
}

Player::~Player()
{
}

float Player::speed() const
{
	return _speed;
}

irr::s8 Player::getRotation()
{
	return _rotation;
}

irr::scene::IAnimatedMeshSceneNode* Player::getNode()
{
	return _player;
}

irr::core::vector3df Player::getPosition()
{
	return _player->getPosition();
}

void Player::stopMove()
{
	_player->setLoopMode(false);
}

void Player::moveForward()
{
	_player->setLoopMode(true);
}

void Player::moveBackward()
{
	_player->setLoopMode(true);
}

void Player::moveLeft()
{
}

void Player::moveRight()
{
}

void Player::rotateLeft()
{
	_player->setRotation(irr::core::vector3df(0, (--_rotation < 0) ? 359 : _rotation, 0));
}

void Player::rotateRight()
{
	_player->setRotation(irr::core::vector3df(0, (++_rotation > 359) ? 0 : _rotation, 0));
}
