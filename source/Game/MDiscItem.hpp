#ifndef __MDiscItem_HPP__
#define __MDiscItem_HPP__
#include "Item.hpp"

class MDiscItem : public Item
{
public:
	MDiscItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value,
		irr::core::stringw des, irr::video::ITexture* text);
	bool use();
	void equip();
	void unEquip();
protected:
	~MDiscItem();
private:
	GameWorld& world;
};

#endif