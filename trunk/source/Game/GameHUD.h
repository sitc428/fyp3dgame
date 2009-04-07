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
	void Update(irr::f32 delta, Player& player );
	void DisplayConversation(irr::c8 conversation_string);
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
	
	//HPbar
	irr::core::rect<irr::s32>	HPBar;
	ITexture*					HP;
	
	//HP Text
	irr::core::rect<irr::s32>	HPTextRec;
	irr::gui::CGUITTFont*		HPText;	//text for displaying the HP
	
	
	double						timeElapsed;
	int							modTime;
};

#endif //GameHUD_h