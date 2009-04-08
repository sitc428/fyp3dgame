#ifndef __X_ITEM_HPP__
#define __X_ITEM_HPP__
#include "Item.hpp"

class XItem : public Item
{
public:
	XItem(GameWorld& gameWorld, EItemType type, irr::c8* name, irr::u32 value);
	void use();
protected:
	~XItem();
private:
	GameWorld& world;
};

#endif