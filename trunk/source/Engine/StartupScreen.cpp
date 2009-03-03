#include "StartupScreen.h"
#include "GameEngine.h"
#include "InputEventReceiver.hpp"

static const irr::c8* STARTUP_LETHALINDUSTRYSTUDIO_TEXTURE = "media/StartupScreen/psan2logo.png";
static const irr::c8* STARTUP_IRRLICHT_TEXTURE = "media/StartupScreen/irrLogo.png";
static const irr::f32 STARTUP_SCREEN_TIME_MAX = 14.5f;  // end of irr logo duration
static const irr::f32 STARTUP_LIS_LOGO_START_TIME = 0.5f;
static const irr::f32 STARTUP_LIS_LOGO_FADE_DURATION = 2.5f;
static const irr::f32 STARTUP_LIS_LOGO_DURATION = 7.f;

static const irr::f32 STARTUP_IRR_LOGO_START_TIME = 7.5f;
static const irr::f32 STARTUP_IRR_LOGO_FADE_DURATION = 2.5f;
static const irr::f32 STARTUP_IRR_LOGO_DURATION = 7.f;

extern GameEngine* GEngine;

// constructor
StartupScreen::StartupScreen()
	:LethalIndustryLogoTexture(NULL),
	LethalIndustryLogoImage(NULL),
	EngineLogoTexture(NULL),
	EngineLogoImage(NULL),
	elapsedTime(0.f)
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
	irr::gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();

	irr::core::position2d<irr::s32> pos1 = irr::core::position2d<irr::s32>( scrSize.Width/2 - LethalIndustryLogoTexture->getOriginalSize().Width/2,
			scrSize.Height/2 - LethalIndustryLogoTexture->getOriginalSize().Height/2 );
	LethalIndustryLogoImage = env->addImage( LethalIndustryLogoTexture, pos1 );
	// set the alpha of the image to 0
	LethalIndustryLogoImage->setColor(irr::video::SColor(0,255,255,255));

	irr::core::position2d<irr::s32> pos2 = irr::core::position2d<irr::s32>( scrSize.Width/2 - EngineLogoTexture->getOriginalSize().Width/2,
			scrSize.Height/2 - EngineLogoTexture->getOriginalSize().Height/2 );
	EngineLogoImage = env->addImage( EngineLogoTexture, pos2 );
	// set the alpha of the image to 0
	EngineLogoImage->setColor(irr::video::SColor(0,255,255,255));
}

// called every frame with the frame's elapsed time
void StartupScreen::Tick( irr::f32 delta )
{
	DoInput();

	elapsedTime += delta;
	//std::cout<<elapsedTime<<" "<<delta<<std::endl;
	if( elapsedTime > STARTUP_SCREEN_TIME_MAX )
	{
		EngineLogoImage->setVisible(false);
		GEngine->RequestStateChange(state_FRONTEND);
	}

	if( elapsedTime > STARTUP_LIS_LOGO_START_TIME )
	{
		irr::f32 elapsedLISLogo = elapsedTime - STARTUP_LIS_LOGO_START_TIME;
		if( elapsedLISLogo < STARTUP_LIS_LOGO_FADE_DURATION )
		{
			irr::u32 alpha = irr::u32( 255 * elapsedLISLogo / STARTUP_LIS_LOGO_FADE_DURATION );
			LethalIndustryLogoImage->setColor(irr::video::SColor(alpha,255,255,255));
		}
		else if ( elapsedLISLogo > STARTUP_LIS_LOGO_DURATION - STARTUP_LIS_LOGO_FADE_DURATION)
		{
			irr::u32 alpha = irr::u32( 255 * (STARTUP_LIS_LOGO_DURATION-elapsedLISLogo) / STARTUP_LIS_LOGO_FADE_DURATION );
			LethalIndustryLogoImage->setColor(irr::video::SColor(alpha,255,255,255));
		}
		else
		{
			LethalIndustryLogoImage->setVisible(true);
		}
	}

	if( elapsedTime > STARTUP_IRR_LOGO_START_TIME )
	{
		LethalIndustryLogoImage->setVisible(false);
		irr::f32 elapsedIRRLogo = elapsedTime - STARTUP_IRR_LOGO_START_TIME;
		if( elapsedIRRLogo < STARTUP_IRR_LOGO_FADE_DURATION )
		{
			irr::u32 alpha = irr::u32( 255 * elapsedIRRLogo / STARTUP_IRR_LOGO_FADE_DURATION );
			EngineLogoImage->setColor(irr::video::SColor(alpha,255,255,255));
		}
		else if ( elapsedIRRLogo > STARTUP_IRR_LOGO_DURATION - STARTUP_IRR_LOGO_FADE_DURATION)
		{
			irr::u32 alpha = irr::u32( 255 * (STARTUP_IRR_LOGO_DURATION-elapsedIRRLogo) / STARTUP_IRR_LOGO_FADE_DURATION );
			EngineLogoImage->setColor(irr::video::SColor(alpha,255,255,255));
		}
		else
		{
			EngineLogoImage->setVisible(true);
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

	if(receiver.keyDown(irr::KEY_RETURN) || receiver.keyDown(irr::KEY_SPACE))
	{
		GEngine->RequestStateChange(state_FRONTEND);
	}
}
