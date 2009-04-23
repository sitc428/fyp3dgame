#include "FontManager.hpp"
#include "GameHUD.hpp"
#include "GameEngine.hpp"
#include "Check.hpp"
#include "Player.hpp"
#include "HPItem.hpp"
#include "XItem.hpp"
#include "WeaponItem.hpp"
#include "MDiscItem.hpp"
#include "MainCharacter.hpp"
#include "CGUITTFont.hpp"
#include "InputEventReceiver.hpp"
#include <iostream>

static const irr::c8*	HEALTH_BAR_FRAME_TEXTURE = "media/HUD/frame_hud.png";
static const irr::c8*	MAGIC_CHARGE_TEXTURE = "media/HUD/circle_bar_hud.png";
static const irr::c8*	MAGIC_LEVEL_TEXTURE = "media/HUD/chargebar_hud_c.png";
static const irr::c8*	CD_TEXTURE = "media/HUD/cd_spinning.png";
static const irr::c8*	STATIC_CD_TEXTURE = "media/HUD/cd_static.png";
static const irr::c8*	HP_TEXTURE = "media/HUD/hp.png";
static const irr::c8*	CONVERSATION_TEXTURE = "media/HUD/conversation.png";
static const irr::c8*	PAUSE_MENU_TEXTURE = "media/HUD/pause_menu.png";
static const irr::c8*	SELECT_ICON_TEXTURE = "media/HUD/cd_icon.png";


static const irr::video::SColor	HUD_FONT_OVERRIDE_COLOR =  irr::video::SColor(255,14,0,89);

static const irr::u32			ELEMENT_HEIGHT = 32;
static const irr::u32			HEALTH_BAR_FRAME_WIDTH = 349;
static const irr::u32			HEALTH_BAR_FRAME_HEIGHT = 134;
static const irr::u32			MAGIC_CHARGE_WIDTH = 133;
static const irr::u32			MAGIC_CHARGE_HEIGHT = 134;
static const irr::u32			HP_WIDTH = 226;
static const irr::u32			HP_HEIGHT = 14;
static const irr::u32			HP_START_X = 105;
static const irr::u32			HP_TEXT_X1 = 170;
static const irr::u32			HP_TEXT_Y1 = 85;
static const irr::u32			HP_TEXT_X2 = 280;
static const irr::u32			HP_TEXT_Y2 = 110;
static const irr::s32			HP_TEXT_WIDTH = 200;
static const irr::s32			HP_TEXT_HEIGHT = 24;
static const irr::s32			HP_Y_OFFSET = 150;
static const irr::u32			CONVERSATION_X1 = 300;
static const irr::u32			CONVERSATION_Y1 = 445;
static const irr::u32			CONVERSATION_X2 = 780;
static const irr::u32			CONVERSATION_Y2 = 575;
static const irr::u32			MENU_ITEM_X1 = 160;
static const irr::u32			MENU_ITEM_Y1 = 70;
static const irr::u32			MENU_ITEM_YOFFSET = 40;
static const irr::u32			MENU_WINDOW_X1 = 370;
static const irr::u32			MENU_WINDOW_Y1 = 70;
static const irr::u32			ITEM_QUANTITY_X1 = 700;
static const irr::u32			ITEM_QUANTITY_Y1 = 70;
static const irr::u32			MENU_WINDOW_YOFFSET = 40;
static const irr::u32			CD_WIDTH = 30;
static const irr::u32			CD_HEIGTH = 30;
static const irr::u32			GAME_START_TIME = 25;
static const irr::u32			FADE_TIME = 4;
static const irr::u32			START_TIME = 4;
static const irr::u32			GAME_OVER_SHOW_TIME = 9;
static const irr::u32			GAME_WIN_SHOW_TIME = 61;

extern GameEngine* GEngine;

// constructor
GameHUD::GameHUD( irr::IrrlichtDevice& device )
	: HealthBarFrameTexture(NULL),
	MagicChargeTexture(NULL),
	MagicLevelTexture(NULL),
	CDTexture(NULL),
	StaticCDTexture(NULL),
	HP(NULL),
	HPText(NULL),
	ConversationTexture(NULL),
	ConversationHeader(NULL),
	ConversationString(""),
	ConversationFont(NULL),
	PauseMenuTexture(NULL),
	MenuFont(NULL),
	SelectIconTexture(NULL),
	MenuSelected(STATUS),
	SubMenuIndex(-1),
	driver(GEngine->GetDriver())
{
	//init by loading the textures required
	HealthBarFrameTexture = driver.getTexture(HEALTH_BAR_FRAME_TEXTURE);
	MagicChargeTexture = driver.getTexture(MAGIC_CHARGE_TEXTURE);
	MagicLevelTexture = driver.getTexture(MAGIC_LEVEL_TEXTURE);
	CDTexture = driver.getTexture(CD_TEXTURE);
	StaticCDTexture = driver.getTexture(STATIC_CD_TEXTURE);
	HP = driver.getTexture(HP_TEXTURE);
	ConversationTexture = driver.getTexture(CONVERSATION_TEXTURE);
	PauseMenuTexture = driver.getTexture(PAUSE_MENU_TEXTURE);
	SelectIconTexture = driver.getTexture(SELECT_ICON_TEXTURE);
	check(HealthBarFrameTexture);
	check(MagicChargeTexture);
	check(MagicLevelTexture); 
	check(CDTexture);
	check(StaticCDTexture);
	check(HP);
	check(ConversationTexture);
	check(PauseMenuTexture);
	check(SelectIconTexture);
	
	//initialize the value of time_elapsed
	timeElapsed = 0;
	modTime = 0;
	
	//loading the fonts
	HPText = GEngine->GetFontManager()->getFont("IMPACT", 24);
	ConversationFont = GEngine->GetFontManager()->getFont("IMPACT", 24);
	MenuFont = GEngine->GetFontManager()->getFont("IMPACT", 24);
	GameOverFont = GEngine->GetFontManager()->getFont("IMPACT", 60);
	WinFont = GEngine->GetFontManager()->getFont("IMPACT", 48);
	
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	startGameText.push_back(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
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
	GEngine->GetDriver().removeTexture(CDTexture);
	CDTexture = NULL;
	GEngine->GetDriver().removeTexture(StaticCDTexture);
	StaticCDTexture = NULL;
	GEngine->GetDriver().removeTexture( HP);
	HP = NULL;
	GEngine->GetDriver().removeTexture( ConversationTexture);
	ConversationTexture = NULL;
	GEngine->GetDriver().removeTexture( PauseMenuTexture);
	PauseMenuTexture = NULL;
	GEngine->GetDriver().removeTexture( SelectIconTexture);
	SelectIconTexture = NULL;
}

void GameHUD::Init()
{
	irr::gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();

	//Setting up Rectangles for displaying images
	HPRec = irr::core::rect<irr::s32>(0,0, HEALTH_BAR_FRAME_WIDTH,HEALTH_BAR_FRAME_HEIGHT);
	
	MagicChargeRec = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	MagicLevelRec = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	CDRec = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	HPBar = irr::core::rect<irr::s32>(0, 0, HP_WIDTH,  HP_HEIGHT);
	HPTextRec = irr::core::rect<irr::s32>(HP_TEXT_X1, HP_TEXT_Y1, HP_TEXT_X2, HP_TEXT_Y2);
	ConversationRec = irr::core::rect<irr::s32>(CONVERSATION_X1, CONVERSATION_Y1, CONVERSATION_X2, CONVERSATION_Y2);
	ComboRec = irr::core::rect<irr::s32>(650, 200, 0, 0);

	gameOverTextSize = GameOverFont->getDimension(L"Game Over");
}

void GameHUD::Update( irr::f32 delta , Player& player)
{
	irr::gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	
	//updating the rectangle for different HUD objects
	int magic_charge = ((MainCharacter&)player).GetChargingProgress()/5;	//magic charge % is divided into 20 stages
	int magic_level = ((MainCharacter&)player).GetMagicLevel();		//magic level
	irr::f32 hp_level = float(player.GetHealth())/float(player.GetMaxHealth());		//hp/max hp
	
	if(magic_charge != 0){
		if(magic_charge%5 == 0){
			MagicChargeRec = irr::core::rect<irr::s32>(MAGIC_CHARGE_WIDTH * 4, MAGIC_CHARGE_HEIGHT * ((magic_charge-1)/5), MAGIC_CHARGE_WIDTH * 5,  MAGIC_CHARGE_HEIGHT * ((magic_charge-1)/5+1));

		}
		else{
			MagicChargeRec = irr::core::rect<irr::s32>(MAGIC_CHARGE_WIDTH * (magic_charge%5-1), MAGIC_CHARGE_HEIGHT * ((magic_charge-1)/5), MAGIC_CHARGE_WIDTH * (magic_charge%5),  MAGIC_CHARGE_HEIGHT * ((magic_charge-1)/5+1));

		}
		driver.draw2DImage(MagicChargeTexture, irr::core::position2d<irr::s32>(0, 0), MagicChargeRec, 0, irr::video::SColor(255,255,255,255), true);
	}
		
	if(magic_level != 0){
		MagicLevelRec = irr::core::rect<irr::s32>(MAGIC_CHARGE_WIDTH * (magic_level-1), 0, MAGIC_CHARGE_WIDTH * magic_level,  MAGIC_CHARGE_HEIGHT);
		driver.draw2DImage(MagicLevelTexture, irr::core::position2d<irr::s32>(0, 0), MagicLevelRec, 0, irr::video::SColor(255,255,255,255), true);
	}

	//draw HP
	HPBar = irr::core::rect<irr::s32>(0, 0, HP_WIDTH*hp_level, HP_HEIGHT);
	driver.draw2DImage(HP, irr::core::position2d<irr::s32>(HP_START_X, (MAGIC_CHARGE_WIDTH-HP_HEIGHT)/2), HPBar, 0, irr::video::SColor(255,255,255,255), true);
	
	//the frame draw last
	driver.draw2DImage(HealthBarFrameTexture, irr::core::position2d<irr::s32>(0, 0), HPRec, 0, irr::video::SColor(255,255,255,255), true);

	//spinning CD
	
	if( ((MainCharacter&)player).GetCharging() ){
		//std::cout<<"TRUE"<<std::endl;
		timeElapsed += delta;
		if(timeElapsed > 0.01){
			modTime ++;
			//reseting timeElapsed
			timeElapsed = 0;
		}
		int stage = modTime % 20;
		CDRec = irr::core::rect<irr::s32>(MAGIC_CHARGE_WIDTH * (stage%5), MAGIC_CHARGE_HEIGHT * ((stage)/5), MAGIC_CHARGE_WIDTH * (stage%5+1),  MAGIC_CHARGE_HEIGHT * ((stage)/5+1));
		
		driver.draw2DImage(CDTexture, irr::core::position2d<irr::s32>(0, 0), CDRec, 0, irr::video::SColor(255,255,255,255), true);
		
		//reseting the modtime
		if (modTime >= 20)
			modTime = 0;		
		
	}
	else{
		timeElapsed = 0;
		modTime = 0;
		driver.draw2DImage(StaticCDTexture, irr::core::position2d<irr::s32>(0, 0), CDRec, 0, irr::video::SColor(255,255,255,255), true);
	}

	/*******
	 DRAWING TEXT
	 *******/

	irr::core::stringw outputString = L"";
	outputString+= ((MainCharacter&)player).GetHealth();
	outputString+= L"/";
	outputString+= ((MainCharacter&)player).GetMaxHealth();
	HPTextRec = irr::core::rect<irr::s32>(HP_TEXT_X1+2, HP_TEXT_Y1+2, HP_TEXT_X2, HP_TEXT_Y2);
	HPText->draw(outputString.c_str(), HPTextRec, irr::video::SColor(255,0,0,0), true, true, 0);
	HPTextRec = irr::core::rect<irr::s32>(HP_TEXT_X1, HP_TEXT_Y1, HP_TEXT_X2, HP_TEXT_Y2);
	HPText->draw(outputString.c_str(), HPTextRec, irr::video::SColor(255,255,255,255), true, true, 0);
	
	if( ((MainCharacter&)player).GetCurrentMagic() != NULL){
		outputString = ((MainCharacter&)player).GetCurrentMagic()->getItemName();
		HPText->draw(outputString.c_str(), irr::core::rect<irr::s32>(152, 20+2, 0, 0), irr::video::SColor(255,0,0,0), false, false, 0);
		HPText->draw(outputString.c_str(), irr::core::rect<irr::s32>(150, 20, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
	}
	
	
	if( ((MainCharacter&)player).GetCombo() ){
		int combonumber = ((MainCharacter&)player).GetComboNum();

		if (combonumber >= 2){
		
			outputString = L"";
			outputString += combonumber;
			irr::core::stringw outputString1 = L"  Combo";
			//std::cout<< combonumber <<" COMBO!"<<std::endl;
			HPText->draw(outputString.c_str(), ComboRec, irr::video::SColor(255,255,0,0), false, false, 0);
			HPText->draw(outputString1.c_str(), ComboRec, irr::video::SColor(255,255,255,255), false, false, 0);
		}
		
	}

	
	MenuSelected = STATUS;
	SubMenuIndex = -1;
}

//getting the string to be displayed from interactive actor 
void GameHUD::GetConversation(irr::core::stringw string, irr::video::ITexture* actorTexture)
{
	ConversationString = string;
	ConversationHeader = actorTexture;
}

void GameHUD::DrawConversation()
{
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	
	//draw the frame for conversation
	driver.draw2DImage(ConversationTexture,	irr::core::position2d<irr::s32>(0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),  0, irr::video::SColor(255,255,255,255), true);
	if(ConversationString != ""){
		ConversationFont->draw(ConversationString.c_str(), ConversationRec, irr::video::SColor(255,255,255,255), false, true, 0);
	}
	if(ConversationHeader){
		GEngine->GetDriver().draw2DImage(ConversationHeader, irr::core::position2di(40, 465));
	}
}

void GameHUD::DrawPauseMenu(Player& player)
{
	
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	InputEventReceiver& receiver = GEngine->GetReceiver();
	
	driver.draw2DImage(PauseMenuTexture,irr::core::position2d<irr::s32>(0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),  0, irr::video::SColor(255,255,255,255), true);
	MenuFont->draw(L"Status", irr::core::rect<irr::s32>(MENU_ITEM_X1, MENU_ITEM_Y1, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
	MenuFont->draw(L"Item", irr::core::rect<irr::s32>(MENU_ITEM_X1, MENU_ITEM_Y1+MENU_ITEM_YOFFSET, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
	MenuFont->draw(L"Equip", irr::core::rect<irr::s32>(MENU_ITEM_X1, MENU_ITEM_Y1+MENU_ITEM_YOFFSET*2, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
	MenuFont->draw(L"Magic", irr::core::rect<irr::s32>(MENU_ITEM_X1, MENU_ITEM_Y1+MENU_ITEM_YOFFSET*3, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
	MenuFont->draw(L"Save", irr::core::rect<irr::s32>(MENU_ITEM_X1, MENU_ITEM_Y1+MENU_ITEM_YOFFSET*4, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
	
	/*******
	 GETTING USER INPUT
	 *******/

	if( SubMenuIndex == -1 )
	{	
		if( receiver.keyReleased( irr::KEY_UP) ){
			if( MenuSelected == STATUS )
				MenuSelected = SAVE;
			else
				MenuSelected = (E_MENU_SELECTED)((MenuSelected - 1 )% EMS_COUNT);
			
		}
		else if( receiver.keyReleased( irr::KEY_DOWN) ){
			MenuSelected = (E_MENU_SELECTED)((MenuSelected + 1) % EMS_COUNT);
		}

		if( MenuSelected == ITEM ){
			if( receiver.keyReleased( irr::KEY_RIGHT) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				int j = 0;
				for (int i = 0 ; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == HPITEM || ItemBox[i].first->getItemType() == XITEM)
						j++;
				}
				if (j>0)
					SubMenuIndex = 0;
			}
		}
		else if( MenuSelected == EQUIP ){
			if( receiver.keyReleased( irr::KEY_RIGHT) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				int j = 0;
				for (int i = 0 ; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == WEAPONITEM1)
						j++;
				}
				if (j>0)
					SubMenuIndex = 0;			
			}
		}
		else if( MenuSelected == MAGIC){
			if( receiver.keyReleased( irr::KEY_RIGHT) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				int j = 0;
				for (int i = 0 ; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == MDISCITEM)
						j++;
				}
				if (j>0)
					SubMenuIndex = 0;			
			}
		}
	}
	// else SubMenuIndex != -1
	else{
		if( MenuSelected == ITEM ){
			if( receiver.keyReleased( irr::KEY_UP) ){
				if(SubMenuIndex != 0){
					SubMenuIndex -- ;
				}
			}
			else if ( receiver.keyReleased( irr::KEY_DOWN) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				int j = 0;
				for (int i = 0; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == HPITEM || ItemBox[i].first->getItemType() == XITEM)
						j++;
				}
				if ( SubMenuIndex < j-1 ){
					SubMenuIndex ++;
				}
			}
			else if ( receiver.keyReleased( irr::KEY_LEFT ) ){
				SubMenuIndex = -1;
			}
			
			else if ( receiver.keyReleased( irr::KEY_RETURN ) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				for (int i = 0, j = -1; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == HPITEM || ItemBox[i].first->getItemType() == XITEM){
						j++;
						if (SubMenuIndex == j && j != -1){
							if(ItemBox[i].first->getItemType() == HPITEM){
								((HPItem*)ItemBox[i].first)->use();
							}
							else if(ItemBox[i].first->getItemType() == XITEM){
								((XItem*)ItemBox[i].first)->use();
							}
							break;
						}
					}	
				}
				
			}
			
		}
		
		else if( MenuSelected == EQUIP ){
			if( receiver.keyReleased( irr::KEY_UP) ){
				if(SubMenuIndex != 0){
					SubMenuIndex -- ;
				}
			}
			else if ( receiver.keyReleased( irr::KEY_DOWN) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				int j = 0;
				for (int i = 0; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == WEAPONITEM1){
						j++;
					}
				}
				if ( SubMenuIndex < j-1 ){	
					SubMenuIndex ++;
				}
				
			}
			else if ( receiver.keyReleased( irr::KEY_LEFT) ){
				
				SubMenuIndex = -1;
			}
			else if ( receiver.keyReleased( irr::KEY_RETURN ) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				for (int i = 0, j = -1; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == WEAPONITEM1){
						j++;
						if (SubMenuIndex == j && j != -1){
							((WeaponItem*)ItemBox[i].first)->equip();
							break;
						}
						else{
							((WeaponItem*)ItemBox[i].first)->unEquip();
						}
					}
				}
				
			}
			
		}
		
		else if( MenuSelected == MAGIC){
			if( receiver.keyReleased( irr::KEY_UP) ){
				if(SubMenuIndex != 0){
					SubMenuIndex -- ;
				}				
			}
			else if ( receiver.keyReleased( irr::KEY_DOWN) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				int j = 0;
				for (int i = 0; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == MDISCITEM){
						j++;
					}
				}
				if ( SubMenuIndex < j-1 ){
					SubMenuIndex ++;
				}
			}
			else if ( receiver.keyReleased( irr::KEY_LEFT) ){
				
				SubMenuIndex = -1;
			}
			
			else if ( receiver.keyReleased( irr::KEY_RETURN ) ){
				MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
				for (int i = 0, j = -1; i < ItemBox.size() ; i++){
					if(ItemBox[i].first->getItemType() == MDISCITEM){
						j++;
						if (SubMenuIndex == j && j != -1){
							((MDiscItem*)ItemBox[i].first)->equip();
							break;
						}
						else{
							((MDiscItem*)ItemBox[i].first)->unEquip();
						}
					}
				}
			}	
		}
	}
	
		
	/**********
	 Start drawing the layout and the text
	 ********/
	
	//change the position of the icon according to the selection
	driver.draw2DImage(SelectIconTexture, irr::core::position2d<irr::s32>(MENU_ITEM_X1-50, MENU_ITEM_Y1+MENU_ITEM_YOFFSET*int(MenuSelected)), irr::core::rect<irr::s32>(0, 0, CD_WIDTH, CD_HEIGTH), 0, irr::video::SColor(255,255,255,255), true);

	//draw the right hand side of the menu according to the selection
	if( MenuSelected == STATUS){
		//LEVEL
		irr::core::stringw outputString = L"Level: ";
		outputString+=((MainCharacter&)player).GetLevel();
		MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);

		//EXP
		outputString = L"EXP: ";
		outputString+=((MainCharacter&)player).GetEXP();
		MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*1, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
		
		//HP
		outputString = L"HP: ";
		outputString+= ((MainCharacter&)player).GetHealth();
		outputString+= L"/";
		outputString+= ((MainCharacter&)player).GetMaxHealth();
		MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*2, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
		
		//Attack
		outputString = L"Attack: ";
		outputString+= ((MainCharacter&)player).GetAttackPoint();
		MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*3, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
		
		//Defence
		outputString = L"Defence: ";
		outputString+= ((MainCharacter&)player).GetDefencePoint();
		MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*4, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
		
		//Magic Attack
		outputString = L"Magic Attack: ";
		outputString+= ((MainCharacter&)player).GetMagicAttackPoint();
		MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*5, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
		
		//Magic Defence
		outputString = L"Magic Defence: ";
		outputString+= ((MainCharacter&)player).GetMagicDefencePoint();
		MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*6, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
	
		//Magic Defence
		outputString = L"Money: ";
		outputString+= ((MainCharacter&)player).GetMoney();
		MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*7, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
	
	
	}
	else if ( MenuSelected == ITEM){
		irr::core::stringw outputString = L"";
		MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
		for (int i = 0, j = 0; i < ItemBox.size() ; i++){
				//ItemBox[i].first = item
				//ItemBox[i].second = quantity
				//ItemBox[i].first->GetItemType = get the item type
			//std::cout<<i<<std::endl;
			if(ItemBox[i].first->getItemType() == HPITEM || ItemBox[i].first->getItemType() == XITEM){
				
				//output item name
				outputString = ItemBox[i].first->getItemName();
				MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
				
				//output quantity
				outputString = ItemBox[i].second;
				MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(ITEM_QUANTITY_X1, ITEM_QUANTITY_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
				
				//get the description of the item
				if(SubMenuIndex == j)
				{
					GetConversation(ItemBox[i].first->getItemDescription());
				}
				
				j++;
			}
		}

		if (SubMenuIndex != -1){
			driver.draw2DImage(SelectIconTexture, irr::core::position2d<irr::s32>(MENU_WINDOW_X1-50, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*SubMenuIndex), irr::core::rect<irr::s32>(0, 0, CD_WIDTH, CD_HEIGTH), 0, irr::video::SColor(255,255,255,255), true);
		}
		else
			GetConversation("");
		
	}
	else if ( MenuSelected == EQUIP){
		irr::core::stringw outputString = L"";
		MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
		for (int i = 0, j = 0; i < ItemBox.size() ; i++){
			if(ItemBox[i].first->getItemType() == WEAPONITEM1){
				//output item name
				outputString = ItemBox[i].first->getItemName();
				if(((MainCharacter&)player).GetCurrentWeapon() != NULL){
					if(outputString == ((MainCharacter&)player).GetCurrentWeapon()->getItemName())
						MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,0,0), false, false, 0);
					else
						MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
				}
				else
					MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);

				//output quantity
				outputString = ItemBox[i].second;
				MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(ITEM_QUANTITY_X1, ITEM_QUANTITY_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
				
				//get the description of the item
				if(SubMenuIndex == j)
				{
					GetConversation(ItemBox[i].first->getItemDescription());
				}
				
				j++;
			}
		}
		if (SubMenuIndex != -1){
			driver.draw2DImage(SelectIconTexture, irr::core::position2d<irr::s32>(MENU_WINDOW_X1-50, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*SubMenuIndex), irr::core::rect<irr::s32>(0, 0, CD_WIDTH, CD_HEIGTH), 0, irr::video::SColor(255,255,255,255), true);
		}
		else
			GetConversation("");
	}
	else if ( MenuSelected == MAGIC){
		irr::core::stringw outputString = L"";
		MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
		for (int i = 0, j = 0; i < ItemBox.size() ; i++){
			if(ItemBox[i].first->getItemType() == MDISCITEM){
				
				//output item name
				outputString = ItemBox[i].first->getItemName();
				if(((MainCharacter&)player).GetCurrentMagic() != NULL){
					if(outputString == ((MainCharacter&)player).GetCurrentMagic()->getItemName())
						MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,0,0), false, false, 0);
					else
						MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
				}
				else
					MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
				
				//output quantity
				outputString = ItemBox[i].second;
				MenuFont->draw(outputString.c_str(), irr::core::rect<irr::s32>(ITEM_QUANTITY_X1, ITEM_QUANTITY_Y1+MENU_ITEM_YOFFSET*j, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);
				
				
				//get the description of the item
				if(SubMenuIndex == j)
				{
					GetConversation(ItemBox[i].first->getItemDescription());
				}
					
					
				j++;
			}
		}
		if (SubMenuIndex != -1){
			driver.draw2DImage(SelectIconTexture, irr::core::position2d<irr::s32>(MENU_WINDOW_X1-50, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*SubMenuIndex), irr::core::rect<irr::s32>(0, 0, CD_WIDTH, CD_HEIGTH), 0, irr::video::SColor(255,255,255,255), true);
		}
		else
			GetConversation("");
	}
	else if ( MenuSelected == SAVE){
	}
}

void GameHUD::gameStart(irr::f32 delta){
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255,0,0,0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height) );
	if(timeElapsed < GAME_START_TIME){
		if( timeElapsed > START_TIME){
			for (int i = 0; i < startGameText.size() ; i++){
				//std::cout<<startGameText[i].c_str()<<std::endl;
				MenuFont->draw(startGameText[i].c_str(), irr::core::rect<irr::s32>(0, scrSize.Height+MENU_ITEM_YOFFSET*i-(timeElapsed-START_TIME)*MENU_ITEM_YOFFSET, scrSize.Width, 0), irr::video::SColor(255,255,255,255), true, false, 0);
				//MenuFont->draw(startGameText[i].c_str(), irr::core::rect<irr::s32>(MENU_WINDOW_X1, MENU_ITEM_YOFFSET*i, 0, 0), irr::video::SColor(255,255,255,255), false, false, 0);		
			}
		}
		timeElapsed += delta;
	}
	else
		timeElapsed = 0;
}

void GameHUD::gameOver(irr::f32 delta){
	irr::core::dimension2di scrSize = GEngine->GetScreenSize();

	if( timeElapsed < GAME_OVER_SHOW_TIME / 2 )
	{
		GEngine->GetDriver().draw2DRectangle(
			irr::video::SColor(255 * timeElapsed / (GAME_OVER_SHOW_TIME / 2), 0, 0, 0),
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height)
		);

		GameOverFont->draw(
			L"Game Over",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * timeElapsed / (GAME_OVER_SHOW_TIME / 2), 255, 255, 255),
			true,
			true
		);
	}
	else if( timeElapsed < GAME_OVER_SHOW_TIME )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		GameOverFont->draw(
			L"Game Over",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - timeElapsed / (GAME_OVER_SHOW_TIME / 2)), 255, 255, 255),
			true,
			true
		);
	}
	else
	{
		timeElapsed = 0;
		return;
	}

	timeElapsed += delta;
}

void GameHUD::gameVictory(irr::f32 delta)
{
	irr::core::dimension2di scrSize = GEngine->GetScreenSize();

	// fade in You Saved the world!
	if( timeElapsed < GAME_WIN_SHOW_TIME / 12 )
	{
		GEngine->GetDriver().draw2DRectangle(
			irr::video::SColor(255 * timeElapsed / (GAME_WIN_SHOW_TIME / 12), 0, 0, 0),
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height)
		);

		WinFont->draw(
			L"You Saved The World!",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * timeElapsed / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);
	}
	// fade out You Saved the world!
	else if( timeElapsed < GAME_WIN_SHOW_TIME / 6 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"You Saved The World!",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (GAME_WIN_SHOW_TIME / 6 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);
	}
	// fade in Cast 1
	else if( timeElapsed < GAME_WIN_SHOW_TIME / 4 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Cast",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height / 2),
			irr::video::SColor(255 * (1 - (GAME_WIN_SHOW_TIME / 4 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"3D Model by Kiron Tsang",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (GAME_WIN_SHOW_TIME / 4 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"3D Scene by Vincent Sit",
			irr::core::rect<irr::s32>(0, 2 * 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (GAME_WIN_SHOW_TIME / 4 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);
	}
	// fade out Cast 1
	else if( timeElapsed < GAME_WIN_SHOW_TIME / 3 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Cast",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height / 2),
			irr::video::SColor(255, 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"3D Model by Kiron Tsang",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (GAME_WIN_SHOW_TIME / 3 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"3D Scene by Vincent Sit",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (GAME_WIN_SHOW_TIME / 3 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);
	}
	// fade in credit 2
	else if( timeElapsed < 5 * GAME_WIN_SHOW_TIME / 12 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Cast",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height / 2),
			irr::video::SColor(255, 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"Shader Effect by Jerry Ip",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (5 * GAME_WIN_SHOW_TIME / 12 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"Sound Effect by Oz Lam",
			irr::core::rect<irr::s32>(0, 2 * 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (5 * GAME_WIN_SHOW_TIME / 12 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);
	}
	// fade out Cast 2
	else if( timeElapsed < GAME_WIN_SHOW_TIME / 2 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Cast",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height / 2),
			irr::video::SColor(255, 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"Shader Effect by Jerry Ip",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (GAME_WIN_SHOW_TIME / 2 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"Sound Effect by Oz Lam",
			irr::core::rect<irr::s32>(0, 2 * 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (GAME_WIN_SHOW_TIME / 2 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);
	}
	// fade in Cast 3
	else if( timeElapsed < 7 * GAME_WIN_SHOW_TIME / 12 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Cast",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height / 2),
			irr::video::SColor(255, 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"Program by Oz Lam and Jerry Ip",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (7 * GAME_WIN_SHOW_TIME / 12 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"Plot by PSAN2",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (7 * GAME_WIN_SHOW_TIME / 12 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);
	}
	// fade out cast 3
	else if( timeElapsed < 2 * GAME_WIN_SHOW_TIME / 3 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Cast",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height - 48 * 1.5),
			irr::video::SColor(255, 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"Program by Oz Lam and Jerry Ip",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (2 * GAME_WIN_SHOW_TIME / 3 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);

		WinFont->draw(
			L"Plot by PSAN2",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (2 * GAME_WIN_SHOW_TIME / 3 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);
	}
	else if( timeElapsed < 3 * GAME_WIN_SHOW_TIME / 4 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Special Thank",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height - 48 * 1.5),
			irr::video::SColor(255 * (1 - (3 * GAME_WIN_SHOW_TIME / 4 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);
		
		WinFont->draw(
			L"Prof. Predo V. Sander",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (3 * GAME_WIN_SHOW_TIME / 4 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);
	}
	else if( timeElapsed < 5 * GAME_WIN_SHOW_TIME / 6 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Special Thank",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height - 48 * 1.5),
			irr::video::SColor(255 * (5 * GAME_WIN_SHOW_TIME / 6 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);
		
		WinFont->draw(
			L"Prof. Predo V. Sander",
			irr::core::rect<irr::s32>(0, 48 * 1.5, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (5 * GAME_WIN_SHOW_TIME / 6 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);
	}
	// fade in Please longed for the release
	else if( timeElapsed < 11 * GAME_WIN_SHOW_TIME / 12 )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Please longed for the release!",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (1 - (11 * GAME_WIN_SHOW_TIME / 12 - timeElapsed) / (GAME_WIN_SHOW_TIME / 12)), 255, 255, 255),
			true,
			true
		);
	}
	// fade out Please longed for the release
	else if( timeElapsed < GAME_WIN_SHOW_TIME )
	{
		GEngine->GetDriver().draw2DRectangle(irr::video::SColor(255, 0, 0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height));

		WinFont->draw(
			L"Please longed for the release!",
			irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),
			irr::video::SColor(255 * (GAME_WIN_SHOW_TIME - timeElapsed) / (GAME_WIN_SHOW_TIME / 12), 255, 255, 255),
			true,
			true
		);
	}

	timeElapsed += delta;
}
