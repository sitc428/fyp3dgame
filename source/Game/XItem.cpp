#include "XItem.hpp"

//constructor
XItem::XItem(GameWorld& gameWorld)
	:Item(gameWorld),
	world(gameWorld)
{
}

//destructor
XItem::~XItem()
{
}
