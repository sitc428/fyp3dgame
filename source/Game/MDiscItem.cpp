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

void MDiscItem::getDisc()
{
	(std::vector< std::pair<Item*, int> >)& box = (((MainCharacter&)world.GetCurrentPlayer()).GetItemBox());

}