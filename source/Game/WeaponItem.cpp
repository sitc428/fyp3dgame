#include "WeaponItem.hpp"
#include "Player.h"
#include "MainCharacter.hpp"

//constructor
WeaponItem::WeaponItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value)
	:Item(gameWorld),
	world(gameWorld)
{
	setItemType(type);
	setItemName(name);
	setItemValue(value);
}

//destructor
WeaponItem::~WeaponItem()
{
}

void WeaponItem::equip()
{
	((MainCharacter&)world.GetCurrentPlayer()).SetCurrentWeapon(this);
	/*if (!getEquipState())
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() + getItemValue()
			);
		setEquipState(true);
	}*/
}

void WeaponItem::unEquip()
{
	if ( ((MainCharacter&)world.GetCurrentPlayer()).GetCurrentWeapon() == this)
		((MainCharacter&)world.GetCurrentPlayer()).SetCurrentWeapon(NULL);
	/*if (getEquipState())
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() - getItemValue()
			);
		setEquipState(false);
	}*/
}