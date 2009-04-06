#ifndef __TALKATIVE_NPC_HPP__
#define __TALKATIVE_NPC_HPP__

#include "InteractiveActor.hpp"
#include <string>

class TalkativeNPC: public InteractiveActor
{
public:
	TalkativeNPC( GameWorld& gameWorld, const std::string, const irr::c8*, const irr::core::vector3df, const irr::core::vector3df, const irr::core::vector3df);

	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; };
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return (EActorType) (ACTOR_INTERACTIVE | ACTOR_TALKACTIVE_NPC); }
	void interaction( irr::f32 );
	virtual irr::f32 acceptableDistance() = 0;

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~TalkativeNPC();

private:
	GameWorld& world;
	std::string _dialogs;
};

#endif // __TALKATIVE_NPC_HPP__