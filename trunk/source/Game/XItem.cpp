#include "XItem.hpp"
#include "MainCharacter.hpp"

//constructor
XItem::XItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value)
	:Item(gameWorld),
	world(gameWorld)
{
	this->setItemType(type);
	this->setItemName(name);
	this->setItemValue(value);
}

//destructor
XItem::~XItem()
{
}

void XItem::use()
{
	irr::core::array< std::pair<Item*, int> > box = (((MainCharacter&)world.GetCurrentPlayer()).GetItemBox());
	int count = 0;
	int tmp = 0;
	for(int i = 0; i < box.size(); ++i)
	{
		if(box[i].first->getItemType() == XITEM)
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