#include "StartupScreen.h"
#include "GameEngine.h"
#include "InputEventReceiver.h"

static const c8*		STARTUP_LETHALINDUSTRYSTUDIO_TEXTURE = "../art/StartupScreen/LISLogo.png";
static const c8*		STARTUP_IRRLICHT_TEXTURE = "../art/StartupScreen/irrLogo.png";
static const f32		STARTUP_SCREEN_TIME_MAX = 8.5f;  // end of irr logo duration
static const f32		STARTUP_LIS_LOGO_START_TIME = 0.5f;
static const f32		STARTUP_LIS_LOGO_FADE_DURATION = 2.5f;
static const f32		STARTUP_LIS_LOGO_DURATION = 4.f;

static const f32		STARTUP_IRR_LOGO_START_TIME = 4.5f;
static const f32		STARTUP_IRR_LOGO_FADE_DURATION = 2.5f;
static const f32		STARTUP_IRR_LOGO_DURATION = 4.f;

extern GameEngine* GEngine;

// constructor
StartupScreen::StartupScreen()
: LethalIndustryLogoTexture(NULL)				
, LethalIndustryLogoImage(NULL)	
, EngineLogoTexture(NULL)
, EngineLogoImage(NULL)	
, elapsedTime(0.f)
{
	// load all the startup screen resources
	LethalIndustryLogoTexture = GEngine->GetDriver().getTexture( STARTUP_LETHALINDUSTRYSTUDIO_TEXTURE );
	check(LethalIndustryLogoTexture);
	EngineLogoTexture = GEngine->GetDriver().getTexture( STARTUP_IRRLICHT_TEXTURE );
	check(EngineLogoTexture);
}

// destructor
StartupScreen::~StartupScreen()
{
	// clear all the startup screen resoruces
	GEngine->GetDriver().removeTexture( LethalIndustryLogoTexture );
	LethalIndustryLogoTexture = NULL;
	GEngine->GetDriver().removeTexture( EngineLogoTexture );
	EngineLogoTexture = NULL;
}

void StartupScreen::Init()
{
	gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	dimension2d<s32> scrSize = GEngine->GetScreenSize();

	position2d<s32> pos1 = position2d<s32>( scrSize.Width/2 - LethalIndustryLogoTexture->getOriginalSize().Width/2,
											scrSize.Height/2 - LethalIndustryLogoTexture->getOriginalSize().Height/2 );
	LethalIndustryLogoImage = env->addImage( LethalIndustryLogoTexture, pos1 );
	// set the alpha of the image to 0
	LethalIndustryLogoImage->setColor(SColor(0,255,255,255));

	position2d<s32> pos2 = position2d<s32>( scrSize.Width/2 - EngineLogoTexture->getOriginalSize().Width/2,
											scrSize.Height/2 - EngineLogoTexture->getOriginalSize().Height/2 );
	EngineLogoImage = env->addImage( EngineLogoTexture, pos2 );
		// set the alpha of the image to 255
	EngineLogoImage->setColor(SColor(0,255,255,255));
}

// called every frame with the frame's elapsed time
void StartupScreen::Tick( f32 delta )
{
	DoInput();

	elapsedTime += delta;
	if( elapsedTime > STARTUP_SCREEN_TIME_MAX )
	{
		GEngine->RequestStateChange(state_FRONTEND);
	}

	if( elapsedTime > STARTUP_LIS_LOGO_START_TIME )
	{
		f32 elapsedLISLogo = elapsedTime - STARTUP_LIS_LOGO_START_TIME;
		if( elapsedLISLogo < STARTUP_LIS_LOGO_FADE_DURATION )
		{
			u32 alpha = u32( 255 * elapsedLISLogo / STARTUP_LIS_LOGO_FADE_DURATION );
			LethalIndustryLogoImage->setColor(SColor(alpha,255,255,255));
		}

		if( elapsedLISLogo > STARTUP_LIS_LOGO_DURATION )
		{
			LethalIndustryLogoImage->setVisible(false);
		}
	}

	if( elapsedTime > STARTUP_IRR_LOGO_START_TIME )
	{
		f32 elapsedIRRLogo = elapsedTime - STARTUP_IRR_LOGO_START_TIME;
		if( elapsedIRRLogo < STARTUP_IRR_LOGO_FADE_DURATION )
		{
			u32 alpha = u32( 255 * elapsedIRRLogo / STARTUP_IRR_LOGO_FADE_DURATION );
			EngineLogoImage->setColor(SColor(alpha,255,255,255));
		}

		if( elapsedIRRLogo > STARTUP_IRR_LOGO_DURATION )
		{
			EngineLogoImage->setVisible(false);
		}
	}
}

void StartupScreen::Exit()
{
	// delete all the gui elements
	check( LethalIndustryLogoImage );
	LethalIndustryLogoImage->remove();
	LethalIndustryLogoImage = NULL;

	check( EngineLogoImage );
	EngineLogoImage->remove();
	EngineLogoImage = NULL;
}

// perform an tick of the input system
void StartupScreen::DoInput()
{
	// allow for skippking over the startup screen if user presses space or enter
	InputEventReceiver& receiver = GEngine->GetReceiver();
	
	if(receiver.IsKeyDown(irr::KEY_RETURN) || receiver.IsKeyDown(irr::KEY_SPACE))
	{
		GEngine->RequestStateChange(state_FRONTEND);
	}
}