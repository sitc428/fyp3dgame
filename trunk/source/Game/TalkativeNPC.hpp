#ifndef __TALKATIVE_NPC_HPP__
#define __TALKATIVE_NPC_HPP__

#include "InteractiveActor.hpp"
#include <string>
#include <vector>

class TalkativeNPC: public InteractiveActor
{
public:
	TalkativeNPC( GameWorld& gameWorld, std::vector<std::string>, const irr::c8*, irr::f32, const irr::core::vector3df, const irr::core::vector3df, const irr::core::vector3df);

	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; };
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return (EActorType) (ACTOR_INTERACTIVE | ACTOR_TALKACTIVE_NPC); }
	void interaction( irr::f32 );
	virtual irr::f32 acceptableDistance();

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~TalkativeNPC();

private:
	GameWorld& world;
	std::vector<std::string> _dialogs;
	irr::f32 acceptable_Distance;
};

#endif // __TALKATIVE_NPC_HPP__