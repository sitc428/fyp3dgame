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
static const c8*	HP_TEXTURE = "media/HUD/hp.png";



static const SColor		HUD_FONT_OVERRIDE_COLOR =  SColor(255,14,0,89);

static u32			ELEMENT_HEIGHT = 32;
static u32			HEALTH_BAR_FRAME_WIDTH = 349;
static u32			HEALTH_BAR_FRAME_HEIGHT = 134;
static u32			MAGIC_CHARGE_WIDTH = 133;
static u32			MAGIC_CHARGE_HEIGHT = 134;
static u32			HP_WIDTH = 225;
static u32			HP_HEIGHT = 10;
static u32			HP_START_X = 105;


extern GameEngine* GEngine;

// constructor
GameHUD::GameHUD( IrrlichtDevice& device )
: HealthBarFrameTexture(NULL)
, MagicChargeTexture(NULL)
, MagicLevelTexture(NULL)
, CDTexture(NULL)
, HP(NULL)
{	
	//init by loading the textures required
	IVideoDriver& driver = GEngine->GetDriver();

	HealthBarFrameTexture = driver.getTexture(HEALTH_BAR_FRAME_TEXTURE);
	MagicChargeTexture = driver.getTexture(MAGIC_CHARGE_TEXTURE);
	MagicLevelTexture = driver.getTexture(MAGIC_LEVEL_TEXTURE);
	HP = driver.getTexture(HP_TEXTURE);
	check(HealthBarFrameTexture);
	check(MagicChargeTexture);
	check(MagicLevelTexture); 
	check(HPTexture);
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
	GEngine->GetDriver().removeTexture( HP);
	HP = NULL;
}

void GameHUD::Init()
{
	
	gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	
	IVideoDriver& driver = GEngine->GetDriver();
	
	
	//health bar main frame
	HPRec = irr::core::rect<irr::s32>(0,0, HEALTH_BAR_FRAME_WIDTH,HEALTH_BAR_FRAME_HEIGHT);
	
	MagicChargeRec = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	MagicLevelRec = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	HPBar = irr::core::rect<irr::s32>(0, 0, HP_WIDTH,  HP_HEIGHT);
		
	
	
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

void GameHUD::Update( irr::f32 delta , Player& player)
{
	gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	IVideoDriver& driver = GEngine->GetDriver();
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	
	MagicChargeRec = irr::core::rect<irr::s32>(MAGIC_CHARGE_WIDTH, 0, MAGIC_CHARGE_WIDTH*2,  MAGIC_CHARGE_HEIGHT);
	MagicLevelRec = irr::core::rect<irr::s32>(MAGIC_CHARGE_WIDTH, 0, MAGIC_CHARGE_WIDTH*2,  MAGIC_CHARGE_HEIGHT);
	HPBar = irr::core::rect<irr::s32>(0, 0, HP_WIDTH, HP_HEIGHT);
	
	
	driver.draw2DImage(HealthBarFrameTexture, irr::core::position2d<irr::s32>(0, 0), HPRec, 0, video::SColor(255,255,255,255), true);
	driver.draw2DImage(MagicChargeTexture, irr::core::position2d<irr::s32>(0, 0), MagicChargeRec, 0, video::SColor(255,255,255,255), true);
	driver.draw2DImage(MagicLevelTexture, irr::core::position2d<irr::s32>(0, 0), MagicLevelRec, 0, video::SColor(255,255,255,255), true);
	driver.draw2DImage(HP, irr::core::position2d<irr::s32>(HP_START_X, (MAGIC_CHARGE_WIDTH-HP_HEIGHT)/2), HPBar, 0, video::SColor(255,255,255,255), true);
	
	
	
	
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

	HealthBarFrameTexture = NULL;
	MagicChargeTexture = NULL;
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
