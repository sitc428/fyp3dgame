#ifndef __GAME_WORLD_HPP__
#define __GAME_WORLD_HPP__

#include <irrklang/irrKlang.h>
#include <irrlicht/irrlicht.h>

#include "GamePart.hpp"

// forward declares
class Actor;
class Camera;
class GameEngine;
class GameHUD;
class InteractiveActor;
class MainCharacter;
class Player;
class Robot;

// different states for the game
enum EGameState
{
	state_START_LEVEL, // level is starting
	state_RESTART_LEVEL, // level is restarting
	state_GAME_OVER, // game over screen
	state_GAMEPLAY, // game is actively playing
	state_PLAYER_DEAD, // player has died
	state_WAVE_FINISHED, // a wave was completed
	state_GAME_VICTORY, // player has finished game
	state_INTERACTING,
	state_PAUSED
};

class GameWorld : public GamePart
{
public:
	explicit GameWorld( GameEngine& );

	void Init();
	
	// called every frame with the frame's elapsed time
	void Tick( irr::f32 delta );
	
	void UpdateHUD( irr::f32 delta);
	
	void DoConversation(irr::core::stringw conversation_string);
	
	void Exit();
	
	irr::scene::ISceneManager& GetSceneManager() { return smgr; }

	irr::scene::IMetaTriangleSelector& GetLevelTriangleSelector() { return *levelTriangleSelector; }
	
	// provides access to the actors in the world
	irr::core::array<Actor*>& GetActors() { return actors; }

	// returns the player actor which is currently used
	Player& GetCurrentPlayer() const;
	
	// return the HUD unit
	GameHUD* GetGameHUD() { return gameHUD; };

	irr::core::array<irr::scene::IMeshSceneNode*>& GetBlocking() { return blocks; }

	// unbuffered mouse input 
	void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent );

	// return the current game state
	EGameState GetGameState() { return gameState; }

	// interface for interactive actor to request the world change into interactive mode
	void requestInteracting(bool, InteractiveActor*);

	// tell the world and actors is the world in interactive mode
	bool isInteracting() const { return gameState == state_INTERACTING; };

	// add scene to the world
	void AddScene(irr::s32);

	Robot* GetRobot() {return robot;};

private:
	// should be self-explained by the function name
	void InitCamera();
	void InitEffects();
	void InitEnemies();
	void InitHUD();
	void InitItems();
	void InitLevel();
	void InitLight();
	void InitMusic();
	void InitNPC();
	void InitPlayer();
	void InitRobot();
	void InitShader();

	// do the actual gameplay
	void DoGameplay( irr::f32 delta );

	// perform an tick of the input system
	void DoInput();

	// updates and plays 3d audio effects
	void DoAudio();

	virtual void SetNumLives( irr::s32 lives ) { numLives = lives; }
	virtual irr::s32 GetNumLives() { return numLives; }

	EGameState gameState; // current state of the game
	EGameState gameStateBeforePause; // the state right before pasued;

	irr::scene::ISceneManager& smgr; // scene manager from the engine

	MainCharacter* mainCharacter; // player node
	Robot* robot; // the robot following the main character
	Camera* camera; // camera object
	irr::scene::ILightSceneNode* light; // light node

	irr::core::array<Actor*> actors; // all the actors that are currently in the world, includes the player and the camera
	irr::core::array<irr::scene::IMeshSceneNode*> blocks; // all the objects that are blocking the movement, includes the monsters

	irr::scene::IMetaTriangleSelector* levelTriangleSelector;  // triangle selector for doing collision checks with the level 
	
	GameHUD* gameHUD; // HUD object

	InteractiveActor* interactingActor; // the interacting interactive actor

	irr::gui::IGUIStaticText* gameMessage; // text used for game messages
	irr::gui::IGUIImage* gameOverImg; // background for game over msg 
	irr::f32 stateTimer; // timer used during state changes

	// player's lives
	irr::s32 numLives; // since there is more than one class/object representing the player, it makes sense to put it here instead

	irr::s32 curLevel;
};

#endif //__GAME_WORLD_HPP__
