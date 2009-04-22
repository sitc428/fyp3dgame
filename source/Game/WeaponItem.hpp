#ifndef __WEAPON_ITEM_HPP__
#define __WEAPON_ITEM_HPP__

#include <irrlicht/irrlicht.h>

#include "WeaponItem.hpp"
#include "Player.hpp"
#include "Item.hpp"

class WeaponItem : public Item
{
public:
	WeaponItem(GameWorld& gameWorld, EItemType type, irr::core::stringw name, irr::u32 value, irr::core::stringw des, irr::video::ITexture* text, irr::c8* meshFile);
	void equip();
	void unEquip();
	irr::scene::IAnimatedMeshSceneNode* GetNode() { return node; }
	//bool getEquipState(){return _equipState;};
	//void setEquipState(bool equipState){_equipState = equipState;};
protected:
	~WeaponItem();
private:
	irr::scene::IAnimatedMeshSceneNode* node;
	GameWorld& world;
	//bool _equipState;
};

#endif