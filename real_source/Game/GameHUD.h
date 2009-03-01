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
	void Update( irr::s32 Ammo, irr::s32 Score, irr::s32 Lives, irr::s32 CurrWave, irr::s32 TotalWaves, irr::f32 Health, bool godMode );
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
	IGUIImage*		HealthBarFrame;
	ITexture*		HealthBarFrameTexture;
	IGUIImage*		MagicCharge;
	ITexture*		MagicChargeTexture;
	IGUIImage*		MagicLevel;
	ITexture*		MagicLevelTexture;
	IGUIImage*		CD;
	ITexture*		CDTexture;
	
	

	//IGUIStaticText* GodModeDisplay;
};

#endif //GameHUD_h