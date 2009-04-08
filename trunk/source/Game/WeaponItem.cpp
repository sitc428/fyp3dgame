#include "WeaponItem.hpp"
#include "Player.h"
#include "MainCharacter.hpp"

//constructor
WeaponItem::WeaponItem(GameWorld& gameWorld, EItemType type, irr::c8* name, irr::u32 value)
	:Item(gameWorld),
	world(gameWorld)
{
	this->setItemType(type);
	this->setItemName(name);
	this->setItemValue(value);
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