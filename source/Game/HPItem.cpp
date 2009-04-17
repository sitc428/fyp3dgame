#include "HPItem.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include "MainCharacter.hpp"
//constructor
HPItem::HPItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value,
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
HPItem::~HPItem()
{
}

bool HPItem::use()
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
		if(box[i].first->getItemType() == HPITEM &&
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