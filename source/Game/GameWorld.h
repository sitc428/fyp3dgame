#ifndef __GAME_WORLD_HPP__
#define __GAME_WORLD_HPP__

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>

// forward declares
class Actor;
class Camera;
class Player;
class MainCharacter;
class Robot;
class GameEngine;
//class DynamiteProjectile;
//class SnowballProjectile;
//class LandMine;
//class ExplosionEffect;
class GameHUD;
//class EnemyWave;

// different states for the game
enum EGameState
{
	state_START_LEVEL, // level is starting
	state_RESTART_LEVEL, // level is restarting
	state_GAME_OVER, // game over screen
	state_GAMEPLAY, // game is actively playing
	state_PLAYER_DEAD, // player has died
	state_WAVE_FINISHED, // a wave was completed
	state_GAME_VICTORY // player has finished game
};

class GameWorld
{
	public:
		explicit GameWorld( const GameEngine& Engine );

		void Init();
		// called every frame with the frame's elapsed time
		void Tick( irr::f32 delta );
		void Exit();

		irr::scene::ISceneManager& GetSceneManager() { return smgr; }
		irr::scene::IMetaTriangleSelector& GetLevelTriangleSelector() { return *levelTriangleSelector; }
		// provides access to the actors in the world, you can modify the actors, but not the irr::core::array itself
		const irr::core::array<Actor*>& GetActors() const { return actors; }
		/*
		// return the first available dynamite projectile for throwing, NULL if none are available
		DynamiteProjectile* GetFirstAvailableDynamite() const;
		// return the first available snowball projectile for throwing, NULL if none are available
		SnowballProjectile* GetFirstAvailableSnowball() const;
		// return the first available landmine for arming, NULL if none are available
		LandMine* GetFirstAvailableLandMine() const;
		// return the first available explosion effect, NULL if none are available
		ExplosionEffect* GetFirstAvailableSnowballExplosionEffect() const;
		// return the first available explosion effect, NULL if none are available
		ExplosionEffect* GetFirstAvailableDynamiteExplosionEffect() const;
		// return the first available enemy death effect, NULL if none are available
		ExplosionEffect* GetFirstAvailableEnemyDeathEffect() const;
		*/
		// will perform player switch after all the actors have been ticked
		void RequestPlayerSwitch() { bSwitchPlayers = true; }

		// returns the player actor which is currently used
		Player& GetCurrentPlayer() const;

		// unbuffered mouse input 
		void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent );

		// brings the designated fence section down so player can proceed to the second level
		void BringDownDividerFence();

		void AdvanceLevel();

		EGameState GetGameState() { return gameState; }

		irr::core::vector3df GetPlayerSpawn();

		void KillAllEnemies();

	private:
		void InitLevel();
		void InitMusic();
		void InitLight();
		void InitPlayer();
		void InitRobot();
		void InitEnemies();
		void InitCamera();
		void InitWeapons();
		void InitEffects();
		void InitPickups();
		void InitHUD();
		void InitShader();

		// do the actual gameplay
		void DoGameplay( irr::f32 delta );
		// perform an tick of the input system
		void DoInput();
		// updates and plays 3d audio effects
		void DoAudio();
		// perform a physics update, includes collision detection
		void DoPhysics();
		// update AI calculations
		void DoAI( irr::f32 delta );
		// updates the Heads Up Display
		void DoHUD();
		// deletes all the dead actors
		void DoCleanup();

		// restarts the current level
		void RestartLevel();
		// perform collision checks between the actors
		void CheckCollisions();

		// switches the player models from onFoot to onSnowplow, and notifies all the necessary actors about the change
		void SwitchPlayers( );
		// notifies all the actors that a new player is to be their target
		void NotifyNewPlayerTarget( Player& player ) const;

		virtual void SetNumLives( irr::s32 lives ) { numLives = lives; }
		virtual irr::s32 GetNumLives() { return numLives; }

		EGameState gameState; // current state of the game

		irr::scene::ISceneManager& smgr; // scene manager from the engine
		MainCharacter* mainCharacter; // player on foot actor
		Robot* robot; // the robot following the main character
		bool bUseOnFootPlayer; // which player model are we currently using
		bool bSwitchPlayers;   // whether we should perform the player switch after all players have been ticked
		Camera* camera; // camera object
		irr::scene::ILightSceneNode* light;

		irr::core::array<Actor*> actors; // all the actors that are currently in the world, includes the player and the camera

		irr::scene::IMetaTriangleSelector* levelTriangleSelector;  // triangle selector for doing collision checks with the level 
		GameHUD* gameHUD; // HUD object

		irr::f32 lastEnemySpawn; // last time an enemy was spawned
		irr::f32 spawnTimer; // time till next spawn
		irr::s32 totalEnemyOne; // total number of enemies of type 1
		irr::s32 totalEnemyTwo; // number of enemies of type 2
		irr::s32 totalEnemyBoss; // number of boss enemies

		irr::core::array<irr::scene::ISceneNode*> spawnNodes; // irr::core::array of spawn nodes in the level

		// variables used for waves
		// irr::core::array<EnemyWave*> enemyWaves; // enemy waves
		irr::s32 curEnemyWave; // the current enemy wave
		irr::f32 waveTimer;
		bool spawnsDone;

		irr::gui::IGUIStaticText* gameMessage; // text used for game messages
		irr::gui::IGUIImage* gameOverImg; // background for game over msg 
		irr::f32 stateTimer; // timer used during state changes

		// members needed to make the section of the fence fall
		irr::scene::IMeshSceneNode* FenceToFall;
		irr::f32 FenceFallTime;

		// player's lives
		irr::s32 numLives; // since there is more than one class/object representing the player, it makes sense to put it here instead

		irr::s32 curLevel;

		bool paused;
};

// helper struct for passing collision information to actors
struct CollisionInfo
{
	CollisionInfo( const irr::scene::ITriangleSelector& levelTriangleSelector, const irr::core::array<Actor*>& inActors )
		: LevelTriangleSelector(levelTriangleSelector)
		  , Actors(inActors)
	{}

	const irr::scene::ITriangleSelector& LevelTriangleSelector;
	const irr::core::array<Actor*>& Actors;
};

#endif //__GAME_WORLD_HPP__
