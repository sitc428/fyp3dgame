#ifndef __HPItem_HPP__
#define __HPItem_HPP__
#include "Item.hpp"

class HPItem : public Item
{
public:
	HPItem(GameWorld& gameWorld);
	void use();
protected:
	~HPItem();
private:
	GameWorld& world;

};

#endif