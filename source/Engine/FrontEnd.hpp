#ifndef __FRONT_END_HPP__
#define __FRONT_END_HPP__

#include <irrlicht/irrlicht.h>

class GameEngine;

enum EMenuItem
{
	FE_MENU_ITEM_STARTGAME,
	FE_MENU_ITEM_EXIT
};

class FrontEnd
{
public:
	// constructor
	FrontEnd( GameEngine& );
	// destructor
	~FrontEnd();

	void Init();

	// called every frame with the frame's elapsed time
	void Tick( irr::f32 delta );
	void Exit();

private:
	// perform an tick of the input
	void DoInput();

	// returns the static text item corresponding to the curr selected menu item
	irr::gui::IGUIStaticText* GetCurrentlySelectedItem();

	// changes which item is currently highligted
	void SetCurrentlyEnabledItem( EMenuItem item );

	irr::video::ITexture* FrontEndBackground; // texture displayed as the background in the frontend
	irr::gui::IGUIImage* BackgroundImage; // gui element which contains the background image
	irr::gui::IGUIStaticText* StartGameText;  // gui element displaying start game text
	irr::gui::IGUIStaticText* ExitGameText;  // gui element displaying exit game text

	EMenuItem currSelectedItem;    // which of the text menu items is currently selected

	GameEngine& GEngine;
};

#endif //__FRONT_END_HPP__
