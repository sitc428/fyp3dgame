#ifndef __TRIGGER_EVENT_ITEM_HPP__
#define __TRIGGER_EVENT_ITEM_HPP__

#include "InteractiveActor.hpp"

enum TriggerEventItemType
{
	SCENE1,
	SCENE2,
	SCENE3,
	SCENE4,
	MINIGAME1,
	MINIGAME2,
	MINIGAME3,
	CUTSCENE
};

class TriggerEventItem: public InteractiveActor
{
public:
	//! Constructor
	TriggerEventItem( GameEngine&, GameWorld&, const irr::core::vector3df, const irr::core::vector3df, const irr::core::vector3df, TriggerEventItemType );

	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; };
	virtual irr::core::vector3df GetRadius()
	{
		irr::core::vector3df temp = node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter();
		return irr::core::vector3df(temp.X, 0, temp.Z);
	}

	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return (EActorType) (ACTOR_INTERACTIVE | ACTOR_TRIGGER_EVENT_ITEM); }

	void interaction( irr::f32 );
	irr::f32 acceptableDistance();
	void checkDistance();
	bool getEnabled() {return enabled;};
	void setEnabled(bool b) { enabled = b;};
	void runGameOne();

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~TriggerEventItem();

private:
	bool enabled;
	TriggerEventItemType _type;
};

#endif