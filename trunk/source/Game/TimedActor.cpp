#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "TimedActor.hpp"

TimedActor::TimedActor( GameEngine& gameEngine, GameWorld& gameWorld, bool active, irr::f32 timeOut )
	: Actor(gameEngine, gameWorld),
	activated(active),
	timeout(timeOut)
{
	theTimer.restart();
}

TimedActor::~TimedActor()
{
}

void TimedActor::Tick( irr::f32 delta )
{
	if( activated && theTimer.elapsed() > timeout )
	{
		timeOutAction();

		theTimer.restart();
	}
}
