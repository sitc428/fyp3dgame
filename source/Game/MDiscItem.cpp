#include "MDiscItem.hpp"
#include "Player.hpp"
#include <vector>
#include <utility>
#include "Item.hpp"
#include "MainCharacter.hpp"
#include <iostream>

//constructor
MDiscItem::MDiscItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value,
					 irr::core::stringw des, irr::video::ITexture* text)
	:Item(gameWorld),
	world(gameWorld)
{
	setItemType(type);
	setItemName(name);
	setItemValue(value);
	setItemDescription(des);
	setItemTexture(text);
}

//destructor
MDiscItem::~MDiscItem()
{
}

bool MDiscItem::use()
{
	irr::core::array< std::pair<Item*, int> > box = (((MainCharacter&)world.GetCurrentPlayer()).GetItemBox());
	int count = 0;
	int tmp = 0;
	for(int i = 0; i < box.size(); i++)
	{
		if(box[i].first->getItemType() == MDISCITEM && 
			box[i].first->getItemName() == ((MainCharacter&)world.GetCurrentPlayer()).GetCurrentMagic()->getItemName()
		)
		{
			count++;
			tmp = i;
		}
	}
	if (count!=0)
	{
		box[tmp].second--;
		std::cout << box[tmp].second << std::endl;
	}

	if (box[tmp].second>=0)
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(box);
		return true;
	}
	else
	{
		return false;
	}
}

void MDiscItem::equip()
{
	((MainCharacter&)world.GetCurrentPlayer()).SetCurrentMagic(this);
	((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
		((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() + getItemValue()
	);
}

void MDiscItem::unEquip()
{
	if ( ((MainCharacter&)world.GetCurrentPlayer()).GetCurrentMagic() == this)
	{
		((MainCharacter&)world.GetCurrentPlayer()).SetCurrentMagic(NULL);
		((MainCharacter&)world.GetCurrentPlayer()).SetAttackPoint(
			((MainCharacter&)world.GetCurrentPlayer()).GetAttackPoint() - getItemValue()
		);
	}
}