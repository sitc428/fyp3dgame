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
	void Update( s32 Ammo, s32 Score, s32 Lives, s32 CurrWave, s32 TotalWaves, f32 Health, bool godMode );
	void Exit();

private:

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

	IGUIStaticText* GodModeDisplay;
};

#endif //GameHUD_h