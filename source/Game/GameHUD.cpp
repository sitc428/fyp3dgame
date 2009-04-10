#include "GameHUD.h"
#include "GameEngine.h"
#include "Check.h"
#include "Player.h"
#include "MainCharacter.hpp"
#include "CGUITTFont.h"
#include "InputEventReceiver.hpp"
#include <iostream>


static const c8*	HEALTH_BAR_FRAME_TEXTURE = "media/HUD/frame_hud.png";
static const c8*	MAGIC_CHARGE_TEXTURE = "media/HUD/circle_bar_hud.png";
static const c8*	MAGIC_LEVEL_TEXTURE = "media/HUD/chargebar_hud_c.png";
static const c8*	CD_TEXTURE = "media/HUD/cd_spinning.png";
static const c8*	STATIC_CD_TEXTURE = "media/HUD/cd_static.png";
static const c8*	HP_TEXTURE = "media/HUD/hp.png";
static const c8*	CONVERSATION_TEXTURE = "media/HUD/conversation.png";
static const c8*	PAUSE_MENU_TEXTURE = "media/HUD/pause_menu.png";
static const c8*	SELECT_ICON_TEXTURE = "media/HUD/cd_icon.png";





static const SColor		HUD_FONT_OVERRIDE_COLOR =  SColor(255,14,0,89);

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
static const irr::u32			MENU_WINDOW_X1 = 360;
static const irr::u32			MENU_WINDOW_Y1 = 70;
static const irr::u32			ITEM_QUANTITY_X1 = 700;
static const irr::u32			ITEM_QUANTITY_Y1 = 70;
static const irr::u32			MENU_WINDOW_YOFFSET = 40;
static const irr::u32			CD_WIDTH = 30;
static const irr::u32			CD_HEIGTH = 30;


extern GameEngine* GEngine;

// constructor
GameHUD::GameHUD( IrrlichtDevice& device )
: HealthBarFrameTexture(NULL)
, MagicChargeTexture(NULL)
, MagicLevelTexture(NULL)
, CDTexture(NULL)
, StaticCDTexture(NULL)
, HP(NULL)
, HPText(NULL)
, ConversationTexture(NULL)
, ConversationString("")
, ConversationFont(NULL)
, PauseMenuTexture(NULL)
, MenuFont(NULL)
, SelectIconTexture(NULL)
, MenuSelected(STATUS)
{	
	//init by loading the textures required
	IVideoDriver& driver = GEngine->GetDriver();

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
	HPText = GEngine->GetFont("media/font/impact.ttf", 24);
	HPText->AntiAlias = true;
	ConversationFont = GEngine->GetFont("media/font/impact.ttf", 24);
	ConversationFont->AntiAlias = true;
	MenuFont = GEngine->GetFont("media/font/impact.ttf", 24);
	MenuFont->AntiAlias = true;
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
	
	gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	
	IVideoDriver& driver = GEngine->GetDriver();
	
	
	//Setting up Rectangles for displaying images
	HPRec = irr::core::rect<irr::s32>(0,0, HEALTH_BAR_FRAME_WIDTH,HEALTH_BAR_FRAME_HEIGHT);
	
	MagicChargeRec = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	MagicLevelRec = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	CDRec = irr::core::rect<irr::s32>(0, 0, MAGIC_CHARGE_WIDTH,  MAGIC_CHARGE_HEIGHT);
	HPBar = irr::core::rect<irr::s32>(0, 0, HP_WIDTH,  HP_HEIGHT);
	HPTextRec = irr::core::rect<irr::s32>(HP_TEXT_X1, HP_TEXT_Y1, HP_TEXT_X2, HP_TEXT_Y2);
	ConversationRec = irr::core::rect<irr::s32>(CONVERSATION_X1, CONVERSATION_Y1, CONVERSATION_X2, CONVERSATION_Y2);
	
}

void GameHUD::Update( irr::f32 delta , Player& player)
{

	gui::IGUIEnvironment* env = GEngine->GetDevice().getGUIEnvironment();
	check(env);
	IVideoDriver& driver = GEngine->GetDriver();
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
		driver.draw2DImage(MagicChargeTexture, irr::core::position2d<irr::s32>(0, 0), MagicChargeRec, 0, video::SColor(255,255,255,255), true);
	}
		
	if(magic_level != 0){
		MagicLevelRec = irr::core::rect<irr::s32>(MAGIC_CHARGE_WIDTH * (magic_level-1), 0, MAGIC_CHARGE_WIDTH * magic_level,  MAGIC_CHARGE_HEIGHT);
		driver.draw2DImage(MagicLevelTexture, irr::core::position2d<irr::s32>(0, 0), MagicLevelRec, 0, video::SColor(255,255,255,255), true);
	}
		
	
	//draw HP
	HPBar = irr::core::rect<irr::s32>(0, 0, HP_WIDTH*hp_level, HP_HEIGHT);
	driver.draw2DImage(HP, irr::core::position2d<irr::s32>(HP_START_X, (MAGIC_CHARGE_WIDTH-HP_HEIGHT)/2), HPBar, 0, video::SColor(255,255,255,255), true);
	
	//the frame draw last
	driver.draw2DImage(HealthBarFrameTexture, irr::core::position2d<irr::s32>(0, 0), HPRec, 0, video::SColor(255,255,255,255), true);
	
	
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
		
		driver.draw2DImage(CDTexture, irr::core::position2d<irr::s32>(0, 0), CDRec, 0, video::SColor(255,255,255,255), true);
		
		//reseting the modtime
		if (modTime >= 20)
			modTime = 0;		
		
	}
	else{
		timeElapsed = 0;
		modTime = 0;
		driver.draw2DImage(StaticCDTexture, irr::core::position2d<irr::s32>(0, 0), CDRec, 0, video::SColor(255,255,255,255), true);
	}
	
		
	/*******
	 DRAWING TEXT
	 *******/
	
	irr::core::stringw outputString = L"";
	outputString+= ((MainCharacter&)player).GetHealth();
	outputString+= L"/";
	outputString+= ((MainCharacter&)player).GetMaxHealth();
	HPText->draw(outputString.c_str(), HPTextRec, video::SColor(255,255,255,255), true, true, 0);
	//	virtual void draw(const wchar_t* text, const core::rect<irr::s32>& position, irr::video::SColor color, bool hcenter=false, bool vcenter=false, const core::rect<irr::s32>* clip=0);
	
	//driver.draw2DImage(ConversationTexture,	irr::core::position2d<irr::s32>(0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),  0, video::SColor(255,255,255,255), true);

	
}



//getting the string to be displayed from interactive actor 
void GameHUD::GetConversation(irr::core::stringw string, ITexture* actorTexture){	
	ConversationString = string;
}

void GameHUD::DrawConversation(){
	IVideoDriver& driver = GEngine->GetDriver();
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	
	//draw the frame for conversation
	driver.draw2DImage(ConversationTexture,	irr::core::position2d<irr::s32>(0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),  0, video::SColor(255,255,255,255), true);
	if(ConversationString != ""){
		ConversationFont->draw(ConversationString.c_str(), ConversationRec, video::SColor(255,255,255,255), false, true, 0);
	}

}


void GameHUD::DrawPauseMenu(Player& player){
	IVideoDriver& driver = GEngine->GetDriver();
	irr::core::dimension2d<irr::s32> scrSize = GEngine->GetScreenSize();
	InputEventReceiver& receiver = GEngine->GetReceiver();
	
	driver.draw2DImage(PauseMenuTexture,irr::core::position2d<irr::s32>(0, 0), irr::core::rect<irr::s32>(0, 0, scrSize.Width, scrSize.Height),  0, video::SColor(255,255,255,255), true);
	MenuFont->draw(L"Status", irr::core::rect<s32>(MENU_ITEM_X1, MENU_ITEM_Y1, 0, 0), video::SColor(255,255,255,255), false, false, 0);
	MenuFont->draw(L"Item", irr::core::rect<s32>(MENU_ITEM_X1, MENU_ITEM_Y1+MENU_ITEM_YOFFSET, 0, 0), video::SColor(255,255,255,255), false, false, 0);
	MenuFont->draw(L"Equip", irr::core::rect<s32>(MENU_ITEM_X1, MENU_ITEM_Y1+MENU_ITEM_YOFFSET*2, 0, 0), video::SColor(255,255,255,255), false, false, 0);
	MenuFont->draw(L"Magic", irr::core::rect<s32>(MENU_ITEM_X1, MENU_ITEM_Y1+MENU_ITEM_YOFFSET*3, 0, 0), video::SColor(255,255,255,255), false, false, 0);
	MenuFont->draw(L"Save", irr::core::rect<s32>(MENU_ITEM_X1, MENU_ITEM_Y1+MENU_ITEM_YOFFSET*4, 0, 0), video::SColor(255,255,255,255), false, false, 0);
	
	if( receiver.keyReleased( irr::KEY_UP) )
	{
		MenuSelected == STATUS? MenuSelected = SAVE : MenuSelected = MENU_SELECTED(MenuSelected - 1);
	}
	else if( receiver.keyReleased( irr::KEY_DOWN) )
	{
		MenuSelected == SAVE? MenuSelected = STATUS : MenuSelected = MENU_SELECTED(MenuSelected + 1);
	}
	
	//change the position of the icon according to the selection
	driver.draw2DImage(SelectIconTexture, irr::core::position2d<s32>(MENU_ITEM_X1-50, MENU_ITEM_Y1+MENU_ITEM_YOFFSET*int(MenuSelected)), irr::core::rect<s32>(0, 0, CD_WIDTH, CD_HEIGTH), 0, video::SColor(255,255,255,255), true);
	

	//draw the right hand side of the menu according to the selection
	
	if( MenuSelected == STATUS){
		
		
		//LEVEL
		irr::core::stringw outputString = L"Level: ";
		outputString+=((MainCharacter&)player).GetLevel();
		MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1, 0, 0), video::SColor(255,255,255,255), false, false, 0);
		
		
		//EXP
		outputString = L"EXP: ";
		outputString+=((MainCharacter&)player).GetEXP();
		MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*1, 0, 0), video::SColor(255,255,255,255), false, false, 0);
		
		//HP
		outputString = L"HP: ";
		outputString+= ((MainCharacter&)player).GetHealth();
		outputString+= L"/";
		outputString+= ((MainCharacter&)player).GetMaxHealth();
		MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*2, 0, 0), video::SColor(255,255,255,255), false, false, 0);
		
		//Attack
		outputString = L"Attack: ";
		outputString+= ((MainCharacter&)player).GetAttackPoint();
		MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*3, 0, 0), video::SColor(255,255,255,255), false, false, 0);
		
		//Defence
		outputString = L"Defence: ";
		outputString+= ((MainCharacter&)player).GetDefencePoint();
		MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*4, 0, 0), video::SColor(255,255,255,255), false, false, 0);
		
		//Magic Attack
		outputString = L"Magic Attack: ";
		outputString+= ((MainCharacter&)player).GetMagicAttackPoint();
		MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*5, 0, 0), video::SColor(255,255,255,255), false, false, 0);
		
		//Magic Defence
		outputString = L"Magic Defence: ";
		outputString+= ((MainCharacter&)player).GetMagicDefencePoint();
		MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*6, 0, 0), video::SColor(255,255,255,255), false, false, 0);
	
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
				MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), video::SColor(255,255,255,255), false, false, 0);
				
				//output quantity
				outputString = ItemBox[i].second;
				MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(ITEM_QUANTITY_X1, ITEM_QUANTITY_Y1+MENU_ITEM_YOFFSET*j, 0, 0), video::SColor(255,255,255,255), false, false, 0);
				j++;
			}
				
		}
			
		
	}
	else if ( MenuSelected == EQUIP){
		irr::core::stringw outputString = L"";
		MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
		for (int i = 0, j = 0; i < ItemBox.size() ; i++){
			if(ItemBox[i].first->getItemType() == WEAPONITEM1){
				
				//output item name
				outputString = ItemBox[i].first->getItemName();
				MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), video::SColor(255,255,255,255), false, false, 0);
				
				//output quantity
				outputString = ItemBox[i].second;
				MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(ITEM_QUANTITY_X1, ITEM_QUANTITY_Y1+MENU_ITEM_YOFFSET*j, 0, 0), video::SColor(255,255,255,255), false, false, 0);
				j++;
			}
			
		}
	}
	else if ( MenuSelected == MAGIC){
		irr::core::stringw outputString = L"";
		MainCharacter::ItemCollection& ItemBox = ((MainCharacter&)player).GetItemBox();
		for (int i = 0, j = 0; i < ItemBox.size() ; i++){
			if(ItemBox[i].first->getItemType() == MDISCITEM){
				
				//output item name
				outputString = ItemBox[i].first->getItemName();
				MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(MENU_WINDOW_X1, MENU_WINDOW_Y1+MENU_ITEM_YOFFSET*j, 0, 0), video::SColor(255,255,255,255), false, false, 0);
				
				//output quantity
				outputString = ItemBox[i].second;
				MenuFont->draw(outputString.c_str(), irr::core::rect<s32>(ITEM_QUANTITY_X1, ITEM_QUANTITY_Y1+MENU_ITEM_YOFFSET*j, 0, 0), video::SColor(255,255,255,255), false, false, 0);
				j++;
			}
			
		}
	}
	else if ( MenuSelected == SAVE){
		
	}
}


void GameHUD::Exit()
{

	HealthBarFrameTexture = NULL;
	MagicChargeTexture = NULL;
	MagicLevelTexture = NULL;
	CDTexture = NULL;
	StaticCDTexture = NULL;
	HP = NULL;
	ConversationTexture = NULL;
	PauseMenuTexture = NULL;
}
