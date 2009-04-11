#include "MDiscItem.hpp"
#include "Player.h"
#include <vector>
#include <utility>
#include "Item.hpp"
#include "MainCharacter.hpp"

//constructor
MDiscItem::MDiscItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value)
	:Item(gameWorld),
	world(gameWorld)
{
		this->setItemType(type);
	this->setItemName(name);
	this->setItemValue(value);
}

//destructor
MDiscItem::~MDiscItem()
{
}

void MDiscItem::use()
{
	irr::core::array< std::pair<Item*, int> > box = (((MainCharacter&)world.GetCurrentPlayer()).GetItemBox());
	int count = 0;
	int tmp = 0;
	for(int i = 0; i < box.size(); ++i)
	{
		if(box[i].first->getItemType() == MDISCITEM)
		{
			count++;
			tmp = i;
		}
	}
	if (count!=0)
	{
		box[tmp].second--;
	}
	if (box[tmp].second>=0)
		((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(box);
}

void MDiscItem::equip()
{
	((MainCharacter&)world.GetCurrentPlayer()).SetCurrentMagic(this);
	/*if (!getEquipState())
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() + getItemValue()
			);
		setEquipState(true);
	}*/
}

void MDiscItem::unEquip()
{
	if ( ((MainCharacter&)world.GetCurrentPlayer()).GetCurrentMagic() == this)
		((MainCharacter&)world.GetCurrentPlayer()).SetCurrentMagic(NULL);
	/*if (getEquipState())
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() - getItemValue()
			);
		setEquipState(false);
	}*/
}