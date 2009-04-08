#include "WeaponItem.hpp"
#include "Player.h"
#include "MainCharacter.hpp"

//constructor
WeaponItem::WeaponItem(GameWorld& gameWorld)
	:Item(gameWorld),
	world(gameWorld)
{
}

//destructor
WeaponItem::~WeaponItem()
{
}

void WeaponItem::equip()
{
	if (!getEquipState())
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() + getItemValue()
			);
		setEquipState(true);
	}
}

void WeaponItem::unEquip()
{
	if (getEquipState())
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() - getItemValue()
			);
		setEquipState(false);
	}
}