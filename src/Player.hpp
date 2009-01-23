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
	
	void stopMove();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();

private:
	Player() {};
	
	irr::scene::IAnimatedMeshSceneNode *_player;
	ProgressCircle *_progressCircle;
	float _speed;
	bool _movingForward;
};

#endif //! __PLAYER_HPP__