#include "Weapon.hpp"

//constructor
Weapon::Weapon(GameWorld& gameWorld)
	:Item(gameWorld),
	world(gameWorld)
{
}

//destructor
Weapon::~Weapon()
{
}

void Weapon::equip()
{
}

void Weapon::unEquip()
{
}