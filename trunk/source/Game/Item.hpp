#ifndef __ITEM_HPP__
#define __ITEM_HPP__
#include <string>
#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
#include "GameWorld.h"
enum EItemType
{
	WEAPONITEM1,	//weapon1
	WEAPONITEM2,	//weapon2
	HPITEM,//HP Item
	MDISCITEM,	//Magic Disc
	XITEM	//itme for solving riddles
};

class Item
{
public:
	Item(GameWorld& gameWorld);
	EItemType getItemType(){return type;};
	irr::c8* getItemName(){return name;};
	irr::u32 getItemValue(){return value;};
	EItemType setItemType(EItemType t){type = t;};
	irr::c8* setItemName(irr::c8* n){name = n;};
	irr::u32 setItemValue(irr::u32 v){value = v;};

protected:
	virtual ~Item();

private:
	//Item type
	EItemType type;
	//Item name
	irr::c8* name;
	//item value, e.g. +10 HP, +20 M_DISC
	irr::u32 value;

	GameWorld& world;
};

#endif