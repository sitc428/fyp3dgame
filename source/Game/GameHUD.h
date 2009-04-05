#ifndef GameHUD_h
#define GameHUD_h

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace irr::gui;
using namespace irr::video;

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
	void Update();
	void Exit();

private:
	/*
	IGUIStaticText* AmmoDisplay;
	IGUIStaticText* ScoreDisplay;
	IGUIStaticText* WaveDisplay;

	IGUIStaticText* PlayerLives;
	ITexture*		PlayerLifeTexture;		// texture with the player face
	IGUIImage*		PlayerLife1;
	IGUIImage*		PlayerLife2;
	IGUIImage*		PlayerLife3;

	IGUIStaticText* PlayerHealth;
	ITexture*		PlayerHealthBarTexture;
	ITexture*		PlayerHealthFillTexture;
	IGUIImage*		PlayerHealthBar;
	IGUIImage*		PlayerHealthFill;
	*/
	//IGUISpriteBank*			HealthBarFrame;
	irr::core::rect<irr::s32>	HPRec;
	ITexture*			HealthBarFrameTexture;
	//IGUISpriteBank*		MagicCharge;
	irr::core::rect<irr::s32>	MagicChargeRec;
	ITexture*			MagicChargeTexture;
	//IGUISpriteBank*			MagicLevel;
	irr::core::rect<irr::s32>	MagicLevelRec;
	ITexture*			MagicLevelTexture;
	//IGUISpriteBank*			CD;
	irr::core::rect<irr::s32>	CDRec;
	ITexture*			CDTexture;
	
	

	//IGUIStaticText* GodModeDisplay;
};

#endif //GameHUD_h