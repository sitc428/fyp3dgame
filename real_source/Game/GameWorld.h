/**
* GameWorld is responsible for initializing, running and exiting gameplay
*/
#ifndef GameWorld_h
#define GameWorld_h

#include <irrlicht/irrlicht.h>
//#include <irrklang/irrKlang.h>

// forward declares
class Actor;
class Camera;
class Player;
class GameEngine;
//class DynamiteProjectile;
//class SnowballProjectile;
//class LandMine;
//class ExplosionEffect;
//class GameHUD;
//class EnemyWave;


using namespace irr;
using namespace irr::scene;
using namespace irr::core;


// different states for the game
enum EGameState
{
	state_START_LEVEL,		// level is starting
	state_RESTART_LEVEL,	// level is restarting
	state_GAME_OVER,		// game over screen
	state_GAMEPLAY,			// game is actively playing
	state_PLAYER_DEAD,		// player has died
	state_WAVE_FINISHED,	// a wave was completed
	state_GAME_VICTORY		// player has finished game
};

class GameWorld
{
public:
	explicit GameWorld( const GameEngine& Engine );

	void Init();
	// called every frame with the frame's elapsed time
	void Tick( f32 delta );
	void Exit();

	ISceneManager& GetSceneManager() { return smgr; }
	IMetaTriangleSelector& GetLevelTriangleSelector() { return *levelTriangleSelector; }
	// provides access to the actors in the world, you can modify the actors, but not the array itself
	const array<Actor*>& GetActors() const { return actors; }
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
	void OnMouseEvent( const SEvent::SMouseInput& mouseEvent );

	// brings the designated fence section down so player can proceed to the second level
	void BringDownDividerFence();
	
	void AdvanceLevel();

	EGameState GetGameState() { return gameState; }

	vector3df GetPlayerSpawn();

	void KillAllEnemies();

private:
	void InitLevel();
	void InitMusic();
	void InitLight();
	void InitPlayer();
	void InitEnemies();
	void InitCamera();
	void InitWeapons();
	void InitEffects();
	void InitPickups();
	void InitHUD();

	// do the actual gameplay
	void DoGameplay( f32 delta );
	// perform an tick of the input system
	void DoInput();
	// updates and plays 3d audio effects
	void DoAudio();
	// perform a physics update, includes collision detection
	void DoPhysics();
	// update AI calculations
	void DoAI( f32 delta );
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

	virtual void SetNumLives( s32 lives ) { numLives = lives; }
	virtual s32 GetNumLives() { return numLives; }

	EGameState					gameState;		// current state of the game

	ISceneManager&				smgr;			// scene manager from the engine
	Player*						playerOnFoot;	// player on foot actor
	Player*						playerOnSnowplow;// player on snowplow actor
	bool						bUseOnFootPlayer; // which player model are we currently using
	bool						bSwitchPlayers;   // whether we should perform the player switch after all players have been ticked
	Camera*						camera;			// camera object
	
	array<Actor*>				actors;			// all the actors that are currently in the world, includes the player and the camera

	IMetaTriangleSelector*		levelTriangleSelector;  // triangle selector for doing collision checks with the level			
//	GameHUD*					gameHUD;		// HUD object

	f32							lastEnemySpawn;	// last time an enemy was spawned
	f32							spawnTimer;		// time till next spawn
	s32							totalEnemyOne;	// total number of enemies of type 1
	s32							totalEnemyTwo;	// number of enemies of type 2
	s32							totalEnemyBoss; // number of boss enemies

	array<ISceneNode*>			spawnNodes;		// array of spawn nodes in the level

	// variables used for waves
//	array<EnemyWave*>			enemyWaves;		// enemy waves
	s32							curEnemyWave;	// the current enemy wave
	f32							waveTimer;
	bool						spawnsDone;

	irr::gui::IGUIStaticText*	gameMessage;	// text used for game messages
	gui::IGUIImage*				gameOverImg;	// background for game over msg 
	f32							stateTimer;		// timer used during state changes

	// members needed to make the section of the fence fall
	IMeshSceneNode*				FenceToFall;
	f32							FenceFallTime;

	// player's lives
	s32							numLives;		// since there is more than one class/object representing the player, it makes sense to put it here instead

	s32							curLevel;
};

// helper struct for passing collision information to actors
struct CollisionInfo
{
	CollisionInfo( const ITriangleSelector& levelTriangleSelector, const array<Actor*>& inActors )
		: LevelTriangleSelector(levelTriangleSelector)
		, Actors(inActors)
	{}

	const ITriangleSelector& LevelTriangleSelector;
	const array<Actor*>& Actors;
};

#endif //GameWorld_h
