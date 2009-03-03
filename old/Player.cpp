#include "Player.hpp"
#include "ProgressCircle.hpp"

Player::Player(irr::scene::IAnimatedMeshSceneNode* source, irr::video::ITexture* texture, irr::core::vector3df position, irr::core::vector3df scale, float speed)
	: _player(source), _health(100), _speed(speed), _movingForward(true), _rotation(0), _progressCircle(0)
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
	_player->setRotation(irr::core::vector3df(0, --_rotation, 0));
}

void Player::rotateRight()
{
	_player->setRotation(irr::core::vector3df(0, ++_rotation, 0));
}

void Player::setHealthBar(ProgressCircle *pc)
{
	if(!pc)
		return;

	if(_progressCircle)
	{
		delete _progressCircle;
	}

	_progressCircle = pc;
}

void Player::reduceHealth(int amount)
{
	if(amount <= 0)
		return;

	_health -= amount;

	if(_health < 0)
		_health = 0;

	_progressCircle->setProgress(_health);
}
