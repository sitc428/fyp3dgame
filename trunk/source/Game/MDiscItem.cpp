#include "MDiscItem.hpp"
#include "Player.h"
#include <vector>
#include "Item.hpp"
#include "MainCharacter.hpp"

//constructor
MDiscItem::MDiscItem(GameWorld& gameWorld)
	:Item(gameWorld),
	world(gameWorld)
{
}

//destructor
MDiscItem::~MDiscItem()
{
}

void MDiscItem::addDisc()
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
		box[tmp].second++;
	}
}