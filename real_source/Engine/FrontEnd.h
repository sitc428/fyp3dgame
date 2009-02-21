#ifndef FrontEnd_h
#define FrontEnd_h

#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::gui;

enum EMenuItem
{
	FE_MENU_ITEM_STARTGAME,
	FE_MENU_ITEM_EXIT
};

class FrontEnd
{
public:
	// constructor
	FrontEnd();
	// destructor
	~FrontEnd();

	void Init();
	// called every frame with the frame's elapsed time
	void Tick( f32 delta );
	void Exit();

private:

	// perform an tick of the input system
	void DoInput();
	// returns the static text item corresponding to the curr selected menu item
	IGUIStaticText* GetCurrentlySelectedItem();
	// changes which item is currently highligted
	void SetCurrentlyEnabledItem( EMenuItem item );

	ITexture*		FrontEndBackground;  // texture displayed as the background in the frontend
	IGUIImage*		BackgroundImage;	 // gui element which contains the background image
	IGUIStaticText* StartGameText;		 // gui element displaying start game text
	IGUIStaticText* ExitGameText;		 // gui element displaying exit game text

	EMenuItem		currSelectedItem;    // which of the text menu items is currently selected
};

#endif //FrontEnd_h