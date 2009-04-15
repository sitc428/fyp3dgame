#ifndef __GAME_PART_HPP__
#define __GAME_PART_HPP__

#include <irrlicht/irrlicht.h>

class GameEngine;

class GamePart
{
public:
	GamePart( GameEngine& );
	~GamePart();

	// called to initialization of part
	virtual void Init() = 0;
	
	// called every frame with the frame's elapsed time
	virtual void Tick( irr::f32 delta ) = 0;

	// clean up the part
	virtual void Exit() = 0;

protected:
	GameEngine& GEngine;
};

#endif // __GAME_PART_HPP__