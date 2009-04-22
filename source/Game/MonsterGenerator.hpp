#ifndef __MONSTER_GENERATOR_HPP__
#define __MONSTER_GENERATOR_HPP__

#include <irrlicht/irrlicht.h>

#include "TimedActor.hpp"

class Monster;

class MonsterGenerator : public TimedActor
{
public:
	///! Constructor
	MonsterGenerator( GameEngine&, GameWorld&, bool, irr::f32 );

	// returns the node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node;}
	virtual irr::core::vector3df GetRadius()
	{
		irr::core::vector3df temp = node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter();
		return irr::core::vector3df(temp.X, 0, temp.Z);
	}

	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_TIMED; }

	// reaction of interactive objects
	void timeOutAction();

	void registerMonster(Monster*);

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~MonsterGenerator();

private:
	irr::scene::IAnimatedMeshSceneNode* node;
	irr::core::array<Monster> monstersPool;
};

#endif //! __MONSTER_GENERATOR_HPP__
