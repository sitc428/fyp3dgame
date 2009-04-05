#include "GameHUD.h"
#include "GameEngine.h"
#include "Check.h"

/*
static const c8*	FONT_FILE = "../art/fonts/HUDfont.png";  // default font for the HUD
static const c8*	PLAYER_LIFE_TEXTURE = "model/HUD/frame_hud.png";  // icon indicating player life
static const c8*	PLAYER_HEALTH_BAR_TEXTURE = "model/HUD/frame_hud.png";
static const c8*	PLAYER_HEALTH_FILL_TEXTURE = "model/HUD/frame_hud.png";
 */
static const c8*	HEALTH_BAR_FRAME_TEXTURE = "media/HUD/frame_hud.png";
static const c8*	MAGIC_CHARGE_TEXTURE = "media/HUD/circle_bar_hud.png";
static const c8*	MAGIC_LEVEL_TEXTURE = "media/HUD/chargebar_hud_c.png";


static const SColor		HUD_FONT_OVERRIDE_COLOR =  SColor(255,14,0,89);

static u32			ELEMENT_HEIGHT = 32;
static u32			HEALTH_BAR_FRAME_WIDTH = 349;
static u32			HEALTH_BAR_FRAME_HEIGHT = 134;
static u32			MAGIC_CHARGE_WIDTH = 133;
static u32			MAGIC_CHARGE_HEIGHT = 134;


extern GameEngine* GEngine;

// constructor
GameHUD::GameHUD( IrrlichtDevice& device )
: HealthBarFrame(NULL)
, HealthBarFrameTexture(NULL)
, MagicCharge(NULL)
, MagicChargeTexture(NULL)
, MagicLevel(NULL)
, MagicLevelTexture(NULL)
, CD(NULL)
, CDTexture(NULL)
{	
	
	
	
	// init the ammo display
	gui::IGUIEnvironment* env = device.getGUIEnvironment();
	IVideoDriver& driver = GEngine->GetDriver();
	check(env);

	IGUISkin* skin = env->getSkin();
	
	
	HealthBarFrameTexture = driver.getTexture(HEALTH_BAR_FRAME_TEXTURE);
	MagicChargeTexture = driver.getTexture(MAGIC_CHARGE_TEXTURE);
	MagicLevelTexture = driver.getTexture(MAGIC_LEVEL_TEXTURE);
	check(HealthBarFrameTexture);
	check(MagicChargeTexture);
	check(MagicLevelTexture); 
	
}

// destructor
GameHUD::~GameHUD()
{
	GEngine->GetDriver().removeTexture( HealthBarFrameTexture );
	HealthBarFrameTexture = NULL;
	GEngine->GetDriver().removeTexture( MagicChargeTexture );
	MagicChargeTexture = NULL;
	GEngine->GetDriver().removeTexture( MagicLevelTexture );
	MagicLevelTexture = NULL;
}

void GameHUD::Init()
{
	
	gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	
	IVideoDriver& driver = GEngine->GetDriver();
	
	
	//health bar main frame
	irr::core::rect<irr::s32> rectangle = irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(0, scrSize.Height - HEALTH_BAR_FRAME_HEIGHT), irr::core::position2d<irr::s32>(HEALTH_BAR_FRAME_WIDTH,scrSize.Height));
	
	
	irr::core::rect<irr::s32> rectangle1 = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	
	driver.draw2DImage(HealthBarFrameTexture, irr::core::position2d<irr::s32>(0, scrSize.Height - HEALTH_BAR_FRAME_HEIGHT), rectangle, 0, video::SColor(255,255,255,255), true);
	
	
	
	/*
	HealthBarFrame = env -> addEmptySpriteBank(HEALTH_BAR_FRAME_TEXTURE);
	HealthBarFrame->addTexture(HealthBarFrameTexture);
	HealthBarFrame->setTexture(0, HealthBarFrameTexture);
	HealthBarFrame->draw2DSprite(0, irr::core::position2d<irr::s32>(0, scrSize.Height - HEALTH_BAR_FRAME_HEIGHT), &rectangle, video::SColor(255, 255, 255, 255), 0, 0, false, false);
	*/
	//HealthBarFrame->setImage( HealthBarFrameTexture );
	//HealthBarFrame->setUseAlphaChannel(true);
	//HealthBarFrame->setVisible(true);
	//driver.draw2DImage(HealthBarFrameTexture, irr::core::position2d<irr::s32>(0, scrSize.Height - HEALTH_BAR_FRAME_HEIGHT), rectangle1);
	
	
	/*Magic Charge
	rectangle = irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(0, scrSize.Height - MAGIC_CHARGE_HEIGHT), 
																	irr::core::position2d<irr::s32>(MAGIC_CHARGE_WIDTH,scrSize.Height));
	MagicCharge = env->addImage(rectangle);
	MagicCharge->setImage( MagicChargeTexture );
	MagicCharge->setUseAlphaChannel(true);
	MagicCharge->setVisible(true);
	*/
	
	
	
	
	/*Magic Level
	MagicLevel = env->addImage(rectangle);
	MagicLevel->setImage( MagicLevelTexture );
	MagicLevel->setUseAlphaChannel(true);
	MagicLevel->setVisible(true);
	 */
	
}

void GameHUD::Update()
{
	gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	IVideoDriver& driver = GEngine->GetDriver();
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	irr::core::rect<irr::s32> HPframe = irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(0, 0), irr::core::position2d<irr::s32>(HEALTH_BAR_FRAME_WIDTH,HEALTH_BAR_FRAME_HEIGHT));
	

	driver.draw2DImage(HealthBarFrameTexture, irr::core::position2d<irr::s32>(0, 0), HPframe, 0, video::SColor(255,255,255,255), true);
	/*
	wchar_t buffer[32];
	//swprintf(buffer,L"AMMO: %i", Ammo);
	AmmoDisplay->setText(buffer);

	//swprintf(buffer,L"SCORE: %i", Score);
	ScoreDisplay->setText(buffer);

	//swprintf(buffer,L"WAVE: %i/%i", CurrWave, TotalWaves);
	WaveDisplay->setText(buffer);

	//swprintf(buffer,L"LIVES:");
	PlayerLives->setText(buffer);

	// set visibility of icons based on the number of lives
	if( Lives <= 0 )
	{
		PlayerLife1->setVisible(false);
		PlayerLife2->setVisible(false);
		PlayerLife3->setVisible(false);
	}
	else if( Lives == 1 )
	{
		PlayerLife1->setVisible(true);
		PlayerLife2->setVisible(false);
		PlayerLife3->setVisible(false);
	}
	else if ( Lives == 2 )
	{
		PlayerLife1->setVisible(true);
		PlayerLife2->setVisible(true);
		PlayerLife3->setVisible(false);
	}
	else if ( Lives == 3 )
	{
		PlayerLife1->setVisible(true);
		PlayerLife2->setVisible(true);
		PlayerLife3->setVisible(true);
	}
	else
	{
		check(false); // should not be here
	}

	//swprintf(buffer,L" HEALTH:");
	PlayerHealth->setText(buffer);
	PlayerHealth->setVisible(true);

	//irr::s32 barWidth = irr::s32(HEALTH_BAR_FILL_WIDTH * Health/100);
	//PlayerHealthFill->setRelativePosition( irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(2, 2), irr::core::position2d<irr::s32>(barWidth, ELEMENT_HEIGHT - 2)) );

	//GodModeDisplay->setVisible(godMode);
	 */
}

void GameHUD::Exit()
{
	//HealthBarFrame->drop();
	HealthBarFrame = NULL;
	HealthBarFrameTexture = NULL;
	//MagicCharge->remove();
	MagicCharge = NULL;
	MagicChargeTexture = NULL;
	//MagicLevel->remove();
	MagicLevel = NULL;
	MagicLevelTexture = NULL;
	
	/*
	check(AmmoDisplay);
	AmmoDisplay->remove();
	AmmoDisplay = NULL;
	check(ScoreDisplay);
	ScoreDisplay->remove();
	ScoreDisplay = NULL;
	check(WaveDisplay);
	WaveDisplay->remove();
	WaveDisplay = NULL;

	PlayerLives->remove();
	PlayerLives = NULL;
	
	PlayerLife1 = NULL;
	PlayerLife2 = NULL;
	PlayerLife3 = NULL;

	
	PlayerHealth->remove();
	PlayerHealth = NULL;
	 */
	 
	/*
	check(GodModeDisplay);
	GodModeDisplay->remove();
	GodModeDisplay = NULL;
	*/
}
