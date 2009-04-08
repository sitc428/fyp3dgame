#include "WeaponItem.hpp"
#include "Player.h"
#include "MainCharacter.hpp"

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
	if (!getEquipState())
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() + getItemValue()
			);
		setEquipState(true);
	}
}

void Weapon::unEquip()
{
	if (getEquipState())
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() - getItemValue()
			);
		setEquipState(false);
	}
}