#ifndef GameHUD_h
#define GameHUD_h

#include <irrlicht/irrlicht.h>

class Player;

namespace irr{
	namespace gui{
		class CGUITTFont;
	}
}

enum E_MENU_SELECTED{
	STATUS = 0,
	ITEM = 1,
	EQUIP = 2,
	MAGIC = 3,
	SAVE = 4,
	EMS_COUNT = 5
};

/**
*	Class which is responsible for drawing the Heads Up Display
*/
class GameHUD
{
public:
	// constructor
	explicit GameHUD( irr::IrrlichtDevice& device );
	// destructor
	~GameHUD();

	void Init();
	//drawing HUD elements
	void Update(irr::f32 delta, Player& player );
	
	//drawing conversation block, for gameworld to call drawing conversation during conversation state
	void DrawConversation();	
	
	//for passing the words for conversation
	void GetConversation(irr::core::stringw string, irr::video::ITexture* actorTexture = NULL);
	
	//drawing pause menu, for gameworld to call during pause state
	void DrawPauseMenu(Player& player);	
private:

	//HP, Magic Frame
	irr::core::rect<irr::s32>	HPRec;
	irr::video::ITexture*		HealthBarFrameTexture;
	
	//MagicCharge
	irr::core::rect<irr::s32>	MagicChargeRec;
	irr::video::ITexture*		MagicChargeTexture;
	
	//MagicLevel
	irr::core::rect<irr::s32>	MagicLevelRec;
	irr::video::ITexture*		MagicLevelTexture;
	
	//CDImage
	irr::core::rect<irr::s32>	CDRec;
	irr::video::ITexture*		CDTexture;
	irr::video::ITexture*		StaticCDTexture;
	
	//HPbar
	irr::core::rect<irr::s32>	HPBar;
	irr::video::ITexture*		HP;
	
	//HP Text
	irr::core::rect<irr::s32>	HPTextRec;
	irr::gui::CGUITTFont*		HPText;	//text for displaying the HP
	
	//Conversation frame
	irr::video::ITexture*		ConversationTexture;
	
	//conversation string
	irr::core::stringw			ConversationString;
	irr::video::ITexture*		ConversationHeader;
	irr::gui::CGUITTFont*		ConversationFont;
	irr::core::rect<irr::s32>	ConversationRec;
	
	//NPC image
	irr::video::ITexture*		NPCTexture;
	
	//PauseMenu Attributes
	//Texture and font
	irr::video::ITexture*		PauseMenuTexture;
	irr::gui::CGUITTFont*		MenuFont;
	irr::video::ITexture*		SelectIconTexture;
	//Menu attributes
	E_MENU_SELECTED				MenuSelected;
	irr::s32					SubMenuIndex;

	irr::f32					timeElapsed;
	irr::u32					modTime;

	// cached video driver
	irr::video::IVideoDriver& driver;
};

#endif //GameHUD_h