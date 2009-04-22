#include "WeaponItem.hpp"
#include "Player.hpp"
#include "MainCharacter.hpp"

//constructor
WeaponItem::WeaponItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value,
					   irr::core::stringw des, irr::video::ITexture* text, irr::c8* meshFile)
	:Item(gameWorld),
	world(gameWorld),
	node(NULL)
{
	setItemType(type);
	setItemName(name);
	setItemValue(value);
	setItemDescription(des);
	setItemTexture(text);
	node = world.GetSceneManager().addAnimatedMeshSceneNode(
		world.GetSceneManager().getMesh(meshFile));
}

//destructor
WeaponItem::~WeaponItem()
{
	world.GetSceneManager().addToDeletionQueue( node );
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