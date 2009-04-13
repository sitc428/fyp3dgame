#ifndef __X_ITEM_HPP__
#define __X_ITEM_HPP__
#include "Item.hpp"

class XItem : public Item
{
public:
	XItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value,
		irr::core::stringw des, irr::video::ITexture* text);
	void use();
protected:
	~XItem();
private:
	GameWorld& world;
};

#endif