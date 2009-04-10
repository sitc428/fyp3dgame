#ifndef GameHUD_h
#define GameHUD_h

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace irr::gui;
using namespace irr::video;

class Player;

namespace irr{
	namespace gui{
		class CGUITTFont;
	}
}

enum MENU_SELECTED{
	STATUS = 0,
	ITEM = 1,
	EQUIP = 2,
	MAGIC = 3,
	SAVE = 4
};

/**
*	Class which is responsible for drawing the Heads Up Display
*/
class GameHUD
{
public:
	// constructor
	explicit GameHUD( IrrlichtDevice& device );
	// destructor
	~GameHUD();

	void Init();
	//drawing HUD elements
	void Update(irr::f32 delta, Player& player );
	
	//drawing conversation block, for gameworld to call drawing conversation during conversation state
	void DrawConversation();	
	
	//for passing the words for conversation
	void GetConversation(irr::core::stringw string, ITexture* actorTexture = NULL);
	
	//drawing pause menu, for gameworld to call during pause state
	void DrawPauseMenu(Player& player);	
	
	void Exit();
private:
	//HP, Magic Frame
	irr::core::rect<irr::s32>	HPRec;
	ITexture*					HealthBarFrameTexture;
	
	//MagicCharge
	irr::core::rect<irr::s32>	MagicChargeRec;
	ITexture*					MagicChargeTexture;
	
	//MagicLevel
	irr::core::rect<irr::s32>	MagicLevelRec;
	ITexture*					MagicLevelTexture;
	
	//CDImage
	irr::core::rect<irr::s32>	CDRec;
	ITexture*					CDTexture;
	ITexture*					StaticCDTexture;
	
	//HPbar
	irr::core::rect<irr::s32>	HPBar;
	ITexture*					HP;
	
	//HP Text
	irr::core::rect<irr::s32>	HPTextRec;
	irr::gui::CGUITTFont*		HPText;	//text for displaying the HP
	
	//Conversation frame
	ITexture*					ConversationTexture;
	
	//conversation string
	irr::core::stringw			ConversationString;
	irr::gui::CGUITTFont*		ConversationFont;
	irr::core::rect<irr::s32>	ConversationRec;
	
	//NPC image
	ITexture*					NPCTexture;
	
	//PauseMenu Attributes
	//Texture and font
	ITexture*					PauseMenuTexture;
	irr::gui::CGUITTFont*		MenuFont;
	ITexture*					SelectIconTexture;
	//Menu attributes
	MENU_SELECTED				MenuSelected;
	
	
	
	double						timeElapsed;
	int							modTime;
	

	
};

#endif //GameHUD_h