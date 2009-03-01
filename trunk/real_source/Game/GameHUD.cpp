#include "GameHUD.h"
#include "GameEngine.h"
#include "Check.h"

static const c8*	FONT_FILE = "../art/fonts/HUDfont.png";  // default font for the HUD
static const c8*	PLAYER_LIFE_TEXTURE = "../art/UI/Head.png";  // icon indicating player life
static const c8*	PLAYER_HEALTH_BAR_TEXTURE = "../art/UI/HealthEmpty.png";
static const c8*	PLAYER_HEALTH_FILL_TEXTURE = "../art/UI/HealthFull.png";
static const SColor		HUD_FONT_OVERRIDE_COLOR =  SColor(255,14,0,89);

static u32			ELEMENT_HEIGHT = 32;
static u32			HEALTH_BAR_WIDTH = 154;
static u32			HEALTH_BAR_FILL_WIDTH = 150;


extern GameEngine* GEngine;

// constructor
GameHUD::GameHUD( IrrlichtDevice& device )
: AmmoDisplay(NULL)
, ScoreDisplay(NULL)
, WaveDisplay(NULL)
, PlayerLives(NULL)
, PlayerLifeTexture(NULL)
, PlayerLife1(NULL)
, PlayerLife2(NULL)
, PlayerLife3(NULL)
, PlayerHealth(NULL)
, PlayerHealthBarTexture(NULL)	
, PlayerHealthFillTexture(NULL)
, PlayerHealthBar(NULL)
, PlayerHealthFill(NULL)
, GodModeDisplay(NULL)
{
	// init the ammo display
	gui::IGUIEnvironment* env = device.getGUIEnvironment();
	IVideoDriver& driver = GEngine->GetDriver();
	check(env);

	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont(FONT_FILE);
	if (font)
	{
		skin->setFont(font);
	}

	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();

	WaveDisplay =  env->addStaticText(
		L"",
		core::rect<irr::s32>(scrSize.Width -155,scrSize.Height -5 -ELEMENT_HEIGHT, scrSize.Width -5,scrSize.Height -5),
		false, true,	0, -1, false);

	check(WaveDisplay);
	WaveDisplay->setTextAlignment( EGUIA_CENTER, EGUIA_CENTER );
	WaveDisplay->setOverrideColor( HUD_FONT_OVERRIDE_COLOR );

	ScoreDisplay = env->addStaticText(
		L"",
		core::rect<irr::s32>(scrSize.Width -155,scrSize.Height -42 -ELEMENT_HEIGHT ,scrSize.Width -5,scrSize.Height -42),
		false, true,	0, -1, false);

	check(ScoreDisplay);
	ScoreDisplay->setTextAlignment( EGUIA_CENTER, EGUIA_CENTER );
	ScoreDisplay->setOverrideColor( HUD_FONT_OVERRIDE_COLOR );

	AmmoDisplay = env->addStaticText(
		L"",
		core::rect<irr::s32>(5,scrSize.Height -42 -ELEMENT_HEIGHT, 155,scrSize.Height -42),
		false, true,	0, -1, false);

	check(AmmoDisplay);
	AmmoDisplay->setTextAlignment( EGUIA_UPPERLEFT, EGUIA_CENTER );
	AmmoDisplay->setOverrideColor( HUD_FONT_OVERRIDE_COLOR );

	PlayerLives = env->addStaticText(
		L"",
		core::rect<irr::s32>(5,scrSize.Height -5 -ELEMENT_HEIGHT , 250,scrSize.Height -5),
		false, true,	0, -1, false);

	check(PlayerLives);
	PlayerLives->setTextAlignment( EGUIA_UPPERLEFT, EGUIA_CENTER );
	PlayerLives->setOverrideColor( HUD_FONT_OVERRIDE_COLOR );

	PlayerLifeTexture = driver.getTexture( PLAYER_LIFE_TEXTURE );
	check(PlayerLifeTexture);

	PlayerHealth = env->addStaticText(
		L"",
		irr::core::rect<irr::s32>(scrSize.Width/2 - 120,scrSize.Height -5 -ELEMENT_HEIGHT , scrSize.Width/2 + 100,scrSize.Height -5),
		false, true,	0, -1, false);
	check(PlayerHealth);
	PlayerHealth->setTextAlignment( EGUIA_UPPERLEFT, EGUIA_CENTER );
	PlayerHealth->setOverrideColor( HUD_FONT_OVERRIDE_COLOR );
	PlayerHealth->setVisible(false);

	PlayerHealthBarTexture = driver.getTexture( PLAYER_HEALTH_BAR_TEXTURE );	
	PlayerHealthFillTexture = driver.getTexture( PLAYER_HEALTH_FILL_TEXTURE );
	check(PlayerHealthBarTexture);
	check(PlayerHealthFillTexture);

	GodModeDisplay = env->addStaticText(
		L"GOD MODE ENABLED",
		irr::core::rect<irr::s32>(16,0,512,32),
		false, true,	0, -1, false);
	check(GodModeDisplay);
	GodModeDisplay->setTextAlignment( EGUIA_UPPERLEFT, EGUIA_CENTER );
	GodModeDisplay->setOverrideColor( SColor( 255, 255, 64, 64 ) );
	GodModeDisplay->setVisible(false);
}

// destructor
GameHUD::~GameHUD()
{
	check(AmmoDisplay == NULL);

	// clear all the HUD resoruces
	GEngine->GetDriver().removeTexture( PlayerLifeTexture );
	PlayerLifeTexture = NULL;
	GEngine->GetDriver().removeTexture( PlayerHealthBarTexture );
	PlayerHealthBarTexture = NULL;
	GEngine->GetDriver().removeTexture( PlayerHealthFillTexture );
	PlayerHealthFillTexture = NULL;
}

void GameHUD::Init()
{
	gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	irr::core::rect<irr::s32> rectangle = irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(100, 0), irr::core::position2d<irr::s32>(132,32));
	PlayerLife1 = env->addImage( rectangle, PlayerLives );
	PlayerLife1->setImage( PlayerLifeTexture );
	PlayerLife1->setScaleImage(true);
	PlayerLife1->setUseAlphaChannel(true);
	PlayerLife1->setVisible(false);

	rectangle = irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(137, 0), irr::core::position2d<irr::s32>(169,32));
	PlayerLife2 = env->addImage( rectangle, PlayerLives );
	PlayerLife2->setImage( PlayerLifeTexture );
	PlayerLife2->setScaleImage(true);
	PlayerLife2->setUseAlphaChannel(true);
	PlayerLife2->setVisible(false);

	rectangle = irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(174, 0), irr::core::position2d<irr::s32>(206,32));
	PlayerLife3 = env->addImage( rectangle, PlayerLives );
	PlayerLife3->setImage( PlayerLifeTexture );
	PlayerLife3->setScaleImage(true);
	PlayerLife3->setUseAlphaChannel(true);
	PlayerLife3->setVisible(false);

	check(PlayerLife1);
	check(PlayerLife2);
	check(PlayerLife3);

	rectangle = irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(120, 0), irr::core::position2d<irr::s32>(120 + HEALTH_BAR_WIDTH,ELEMENT_HEIGHT));
	PlayerHealthBar = env->addImage( rectangle, PlayerHealth );
	PlayerHealthBar->setImage( PlayerHealthBarTexture );
	PlayerHealthBar->setScaleImage(true);
	PlayerHealthBar->setUseAlphaChannel(true);
	check(PlayerHealthBar);

	rectangle = irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(2, 2), irr::core::position2d<irr::s32>(HEALTH_BAR_FILL_WIDTH,ELEMENT_HEIGHT - 2));
	PlayerHealthFill = env->addImage( rectangle, PlayerHealthBar );
	PlayerHealthFill->setImage( PlayerHealthFillTexture );
	PlayerHealthFill->setScaleImage(true);
	PlayerHealthFill->setUseAlphaChannel(true);
	check(PlayerHealthFill);
}

void GameHUD::Update( irr::s32 Ammo, irr::s32 Score, irr::s32 Lives, irr::s32 CurrWave, irr::s32 TotalWaves, irr::f32 Health, bool godMode )
{
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

	irr::s32 barWidth = irr::s32(HEALTH_BAR_FILL_WIDTH * Health/100);
	PlayerHealthFill->setRelativePosition( irr::core::rect<irr::s32>(irr::core::position2d<irr::s32>(2, 2), irr::core::position2d<irr::s32>(barWidth, ELEMENT_HEIGHT - 2)) );

	GodModeDisplay->setVisible(godMode);
}

void GameHUD::Exit()
{
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

	check(GodModeDisplay);
	GodModeDisplay->remove();
	GodModeDisplay = NULL;
}
