#ifndef __MDiscItem_HPP__
#define __MDiscItem_HPP__
#include "Item.hpp"

class MDiscItem : public Item
{
public:
	MDiscItem(GameWorld& gameWorld, EItemType type, irr::c8* name, irr::u32 value);
	void use();
protected:
	~MDiscItem();
private:
	GameWorld& world;
};

#endif