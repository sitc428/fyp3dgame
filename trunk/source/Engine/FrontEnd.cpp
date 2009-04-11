#include "FrontEnd.h"
#include "GameEngine.hpp"
#include "InputEventReceiver.hpp"
//#include "CGUIStaticTTText.hpp"

extern GameEngine* GEngine;

static const irr::c8* FRONTEND_BACKGROUND_TEXTURE = "media/StartupScreen/startupscreen.png";
//static const irr::c8* FRONTEND_BACKGROUND_TEXTURE_1280x720 = "../art/StartupScreen/1280x720GameSplash.png";
static const irr::c8* FRONTEND_FONT_FILE = "../art/fonts/FEfont.png";
static const irr::video::SColor SELECTED_ITEM_OVERRIDE_COLOR = irr::video::SColor(255,255,0,0);

// dimensions of the text elements in the frontend
static const irr::s32 TEXT_ELEMENT_WIDTH = 200;
static const irr::s32 TEXT_ELEMENT_HEIGHT = 24;
static const irr::s32 FIRST_TEXT_ELEMENT_Y_OFFSET = 150;
static const irr::s32 SECOND_TEXT_ELEMENT_Y_OFFSET = 170;

// constructor
FrontEnd::FrontEnd()
	:FrontEndBackground(NULL),
	BackgroundImage(NULL),
	StartGameText(NULL),
	ExitGameText(NULL),
	currSelectedItem(FE_MENU_ITEM_STARTGAME)
{ 
}

// destructor
FrontEnd::~FrontEnd()
{
	// clear all the frontend resoruces
	GEngine->GetDriver().removeTexture( FrontEndBackground );
	FrontEndBackground = NULL;
}

void FrontEnd::Init()
{
	// load the background image
	FrontEndBackground = GEngine->GetDriver().getTexture( FRONTEND_BACKGROUND_TEXTURE );

	// init the ammo display
	irr::gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();

	irr::core::position2d<irr::s32> backgroundPos = irr::core::position2d<irr::s32>(0,0);

	BackgroundImage = env->addImage( irr::core::rect<irr::s32>(backgroundPos, scrSize) );
	BackgroundImage->setImage( FrontEndBackground );

	env->getSkin()->setFont((irr::gui::IGUIFont*) GEngine->GetFont("media/font/impact.ttf", 24));
	env->getSkin()->setColor( irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 255, 255) );

	// add the text elements
	StartGameText = env->addStaticText(
			L"Start\tGame",
			irr::core::rect<irr::s32>(
				scrSize.Width/2 - TEXT_ELEMENT_WIDTH/2,
				scrSize.Height/2 - TEXT_ELEMENT_HEIGHT/2 + FIRST_TEXT_ELEMENT_Y_OFFSET,
				scrSize.Width/2 + TEXT_ELEMENT_WIDTH/2,
				scrSize.Height/2 + TEXT_ELEMENT_HEIGHT/2 + FIRST_TEXT_ELEMENT_Y_OFFSET),
				false, false, 0, -1, false);
	check(StartGameText);
	StartGameText->setTextAlignment( irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER );

	ExitGameText = env->addStaticText(
			L"Load",
			irr::core::rect<irr::s32>(
				scrSize.Width/2 - TEXT_ELEMENT_WIDTH/2,
				scrSize.Height/2 - TEXT_ELEMENT_HEIGHT/2 + SECOND_TEXT_ELEMENT_Y_OFFSET,
				scrSize.Width/2 + TEXT_ELEMENT_WIDTH/2,
				scrSize.Height/2 + TEXT_ELEMENT_HEIGHT/2 + SECOND_TEXT_ELEMENT_Y_OFFSET),
			false, false, 0, -1, false);

	ExitGameText->setTextAlignment( irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER );

	GetCurrentlySelectedItem()->setOverrideColor( SELECTED_ITEM_OVERRIDE_COLOR );
}

// called every frame with the frame's elapsed time
void FrontEnd::Tick( irr::f32 delta )
{
	// perform an tick of the input system
	DoInput();
}

void FrontEnd::Exit()
{
	// delete all the gui elements
	check( BackgroundImage );
	BackgroundImage->remove();
	BackgroundImage = NULL;

	check( StartGameText );
	StartGameText->remove();
	StartGameText = NULL;

	check( ExitGameText );
	ExitGameText->remove();
	ExitGameText = NULL;
}

// returns the static text item corresponding to the curr selected menu item
irr::gui::IGUIStaticText* FrontEnd::GetCurrentlySelectedItem()
{
	switch(currSelectedItem)
	{
		case FE_MENU_ITEM_STARTGAME:
			{
				return StartGameText;
			}
		case FE_MENU_ITEM_EXIT:
			{
				return ExitGameText;
			}
		default:
			{
				// shouldn't be here
				check( false );
				return NULL;
			}
	}
}

// changes which item is currently highligted
void FrontEnd::SetCurrentlyEnabledItem( EMenuItem item )
{
	// changing selected item to the same item doesn't make sense
	check(item != currSelectedItem);

	// disable highlight color on the previously selected item
	irr::gui::IGUIStaticText* currItem = GetCurrentlySelectedItem();
	currItem->enableOverrideColor(false);

	// change the currently selected item and set the override color on it
	currSelectedItem = item;
	irr::gui::IGUIStaticText* nextSelectedItem = GetCurrentlySelectedItem();
	nextSelectedItem->setOverrideColor(SELECTED_ITEM_OVERRIDE_COLOR);
}

// perform an tick of the input system
void FrontEnd::DoInput()
{
	InputEventReceiver& receiver = GEngine->GetReceiver();

	// perform requested menu item action if the enter key is pressed
	if(receiver.keyDown(irr::KEY_RETURN))
	{
		switch(currSelectedItem)
		{
			case FE_MENU_ITEM_STARTGAME:
				{
					GEngine->RequestStateChange(state_GAME);
					break;
				}
			case FE_MENU_ITEM_EXIT:
				{
					GEngine->RequestStateChange(state_EXIT);
					break;
				}
			default:
				{
					// shouldn't be here
					check( false );
				}
		}
	}
	else if(receiver.keyDown(irr::KEY_UP) || receiver.keyDown(irr::KEY_KEY_W))
	{
		// find what the next selected item should be, don't allow for list iteration wraparound
		EMenuItem nextItem = currSelectedItem;
		if( currSelectedItem == FE_MENU_ITEM_EXIT )
		{
			nextItem = FE_MENU_ITEM_STARTGAME;
		}

		if( nextItem != currSelectedItem )
		{
			SetCurrentlyEnabledItem(nextItem);
		}
	}
	else if(receiver.keyDown(irr::KEY_DOWN) || receiver.keyDown(irr::KEY_KEY_S))
	{
		// find what the next selected item should be, don't allow for list iteration wraparound
		EMenuItem nextItem = currSelectedItem;
		if( currSelectedItem == FE_MENU_ITEM_STARTGAME )
		{
			nextItem = FE_MENU_ITEM_EXIT;
		}

		if( nextItem != currSelectedItem )
		{
			SetCurrentlyEnabledItem(nextItem);
		}
	}
}
