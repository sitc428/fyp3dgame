#ifndef __SELLING_MACHINE_HPP__
#define __SELLING_MACHINE_HPP__

#include "InteractiveActor.hpp"

class GameEngine;

class SellingMachine: public InteractiveActor
{
public:
	SellingMachine( GameEngine&, GameWorld&, const irr::core::vector3df, const irr::core::vector3df, const irr::core::vector3df );

	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; };
	virtual irr::core::vector3df GetRadius()
	{
		irr::core::vector3df temp = node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter();
		return irr::core::vector3df(temp.X, 0, temp.Z);
	}

	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return (EActorType) (ACTOR_INTERACTIVE | ACTOR_SELLING_MACHINE); }
	void interaction( irr::f32 );
	irr::f32 acceptableDistance();


protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~SellingMachine();
};

#endif // __SELLING_MACHINE_HPP__