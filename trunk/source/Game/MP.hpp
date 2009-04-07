#ifndef __MP_HPP__
#define __MP_HPP__
#include "Item.hpp"

class MP : public Item
{
public:
	MP(GameWorld& gameWorld);
	void use();
protected:
	~MP();
private:
	GameWorld& world;
};

#endif