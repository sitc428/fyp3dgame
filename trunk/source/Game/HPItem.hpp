#ifndef __HPItem_HPP__
#define __HPItem_HPP__
#include "Item.hpp"

class HPItem : public Item
{
public:
	HPItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, 
		irr::u32 value, irr::core::stringw des, irr::video::ITexture* text);
	void use();
protected:
	~HPItem();
private:
	GameWorld& world;

};

#endif