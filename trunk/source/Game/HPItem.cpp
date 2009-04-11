#include "HPItem.hpp"
#include "Player.h"
#include "Item.hpp"
#include "MainCharacter.hpp"
//constructor
HPItem::HPItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value)
	:Item(gameWorld),
	world(gameWorld)
{
	this->setItemType(type);
	this->setItemName(name);
	this->setItemValue(value);
}


//destructor
HPItem::~HPItem()
{
}

void HPItem::use()
{
	//if value + HP > Max HP => set HP = Max HP
	if (this->getItemValue()+world.GetCurrentPlayer().GetHealth()>world.GetCurrentPlayer().GetMaxHealth())
		world.GetCurrentPlayer().SetHealth(world.GetCurrentPlayer().GetMaxHealth());
	else
	//else +HP
		world.GetCurrentPlayer().SetHealth(world.GetCurrentPlayer().GetHealth()+this->getItemValue());
	//need to remove the item from player
	irr::core::array< std::pair<Item*, int> > box = (((MainCharacter&)world.GetCurrentPlayer()).GetItemBox());
	int count = 0;
	int tmp = 0;
	for(int i = 0; i < box.size(); ++i)
	{
		if(box[i].first->getItemType() == HPITEM)
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