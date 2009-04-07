#ifndef __X_ITEM_HPP__
#define __X_ITEM_HPP__
#include "Item.hpp"

class XItem : public Item
{
public:
	XItem(GameWorld& gameWorld);
protected:
	~XItem();
private:
	GameWorld& world;
};

#endif