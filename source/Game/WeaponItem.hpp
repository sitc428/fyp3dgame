#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__
#include "WeaponItem.hpp"
#include "Player.h"
class Weapon : public Item
{
public:
	Weapon(GameWorld& gameWorld);
	void equip();
	void unEquip();
protected:
	~Weapon();
private:
	GameWorld& world;
};

#endif