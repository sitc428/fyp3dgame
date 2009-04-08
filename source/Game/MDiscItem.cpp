#include "MDiscItem.hpp"
#include "Player.h"
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

void MDiscItem::use()
{
}