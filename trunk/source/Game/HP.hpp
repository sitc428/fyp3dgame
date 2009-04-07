#ifndef __HP_HPP__
#define __HP_HPP__
#include "Item.hpp"

class HP : public Item
{
public:
	HP(GameWorld& gameWorld);
	void use();
protected:
	~HP();
private:
	GameWorld& world;

};

#endif