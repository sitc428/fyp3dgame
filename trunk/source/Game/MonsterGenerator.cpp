#include "Monster.hpp"
#include "MonsterGenerator.hpp"

MonsterGenerator::MonsterGenerator( GameEngine& gameEngine, GameWorld& gameWorld, bool active, irr::f32 timeOut)
	: TimedActor(gameEngine, gameWorld, active, timeOut),
	node(NULL)
{
}

void MonsterGenerator::registerMonster(Monster* monster)
{
	/*monstersPool.push_back(*monster);*/
}

MonsterGenerator::~MonsterGenerator()
{
}

void MonsterGenerator::timeOutAction()
{
}
