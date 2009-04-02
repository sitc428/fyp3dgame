#ifndef __INTERACTIVE_ACTOR_HPP__
#define __INTERACTIVE_ACTOR_HPP__
#include "Actor.h"

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>

class InteractiveActor: public Actor
{
public:
	InteractiveActor( GameWorld& gameWorld );

	// called every frame to update player
	void Tick(irr::f32 delta); // not virtual
	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const = 0;
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_INTERACTIVE; }


protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~InteractiveActor();

private:
	GameWorld& world;
};

#endif // __INTERACTIVE_ACTOR_HPP__