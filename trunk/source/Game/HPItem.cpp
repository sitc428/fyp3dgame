#include "HPItem.hpp"
#include "Player.h"

//constructor
HPItem::HPItem(GameWorld& gameWorld)
	:Item(gameWorld),
	world(gameWorld)
{
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





}