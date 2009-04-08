#ifndef __MDiscItem_HPP__
#define __MDiscItem_HPP__
#include "Item.hpp"

class MDiscItem : public Item
{
public:
	MDiscItem(GameWorld& gameWorld);
	void getDisc();
protected:
	~MDiscItem();
private:
	GameWorld& world;
};

#endif