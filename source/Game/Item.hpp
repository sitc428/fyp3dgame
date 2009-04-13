#ifndef __ITEM_HPP__
#define __ITEM_HPP__
#include <string>
#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
#include "GameWorld.hpp"

enum EItemType
{
	WEAPONITEM1 = 1,	//weapon1
	WEAPONITEM2 = 2,	//weapon2
	HPITEM = 4,//HP Item
	MDISCITEM = 8,	//Magic Disc
	XITEM = 16	//itme for solving riddles
};

class Item
{
public:
	Item(GameWorld& gameWorld);
	EItemType getItemType(){return type;};
	irr::core::stringw getItemName(){return name;};
	irr::u32 getItemValue(){return value;};
	irr::core::stringw getItemDescription() {return description;};
	irr::video::ITexture* getItemTexture() {return texture;};
	void setItemType(EItemType t){type = t;};
	void setItemName(irr::core::stringw n){name = n;};
	void setItemValue(irr::u32 v){value = v;};
	void setItemDescription(irr::core::stringw des) {description = des;};
	void setItemTexture(irr::video::ITexture* text){texture = text;};

protected:
	virtual ~Item();

private:
	//Item type
	EItemType type;
	//Item name
	irr::core::stringw name;
	//item value, e.g. +10 HP, +20 M_DISC
	irr::u32 value;
	//Description
	irr::core::stringw description;
	//item texture
	irr::video::ITexture* texture;

	GameWorld& world;
};

#endif