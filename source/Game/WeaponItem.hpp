#ifndef __WEAPON_ITEM_HPP__
#define __WEAPON_ITEM_HPP__
#include "WeaponItem.hpp"
#include "Player.h"
#include "Item.hpp"
class WeaponItem : public Item
{
public:
	WeaponItem(GameWorld& gameWorld);
	void equip();
	void unEquip();
	bool getEquipState(){return _equipState;};
	bool setEquipState(bool equipState){_equipState = equipState;};
protected:
	~WeaponItem();
private:
	GameWorld& world;
	bool _equipState;
};

#endif