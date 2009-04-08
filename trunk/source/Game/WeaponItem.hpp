#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__
#include "WeaponItem.hpp"
#include "Player.h"
#include "Item.hpp"
class Weapon : public Item
{
public:
	Weapon(GameWorld& gameWorld);
	void equip();
	void unEquip();
	bool getEquipState(){return _equipState;};
	bool setEquipState(bool equipState){_equipState = equipState;};
protected:
	~Weapon();
private:
	GameWorld& world;
	bool _equipState;
};

#endif