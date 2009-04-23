#ifndef __TALKATIVE_NPC_HPP__
#define __TALKATIVE_NPC_HPP__

#include <string>
#include <vector>

#include "InteractiveActor.hpp"

class TalkativeNPC: public InteractiveActor
{
public:
	TalkativeNPC( GameEngine&, GameWorld&, const irr::c8*, irr::core::array<irr::core::stringw>&, irr::video::ITexture*, irr::f32, const irr::core::vector3df, const irr::core::vector3df, const irr::core::vector3df, irr::u32);

	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; };
	virtual irr::core::vector3df GetRadius()
	{
		irr::core::vector3df temp = node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter();
		return irr::core::vector3df(temp.X, 0, temp.Z);
	}

	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return (EActorType) (ACTOR_INTERACTIVE | ACTOR_TALKACTIVE_NPC); }

	// interactions of the actor
	void interaction( irr::f32 );

	// return the acceptable interactive distance
	virtual irr::f32 acceptableDistance();

	virtual void RecreateCollisionResponseAnimator();

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~TalkativeNPC();

private:
	irr::core::array<irr::core::stringw> _dialogs;
	irr::video::ITexture* _header;
	irr::f32 acceptable_Distance;
	irr::u32 _type;
	bool itemTrigger;
	int state;
	int talking;
	int currentline;
	double timeElapsed;
	
};

#endif // __TALKATIVE_NPC_HPP__