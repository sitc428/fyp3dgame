#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <irrlicht/irrlicht.h>

class ProgressCircle;

class Player
{
public:
	Player(irr::scene::IAnimatedMeshSceneNode* source, irr::video::ITexture* texture, irr::core::vector3df position, irr::core::vector3df scale, float speed);
	~Player();
	
	irr::scene::IAnimatedMeshSceneNode* getNode();

	float speed() const;
	
	irr::core::vector3df getPosition();

	irr::s8 getRotation();
	
	void stopMove();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void rotateLeft();
	void rotateRight();

private:
	Player() {};
	
	irr::scene::IAnimatedMeshSceneNode *_player;
	ProgressCircle *_progressCircle;
	float _speed;
	bool _movingForward;
	irr::s8 _rotation;
};

#endif //! __PLAYER_HPP__