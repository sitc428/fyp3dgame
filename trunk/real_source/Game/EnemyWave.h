#pragma once

#include <irrlicht/irrlicht.h>


class EnemyWave
{
public:
	EnemyWave( const s32* spawnArray, s32 pNumSpawns, s32 pTimeTillNextWave  ):
		curSpawn(0),
		numEnemies(0)
	{
		numSpawns = pNumSpawns;
		timeTillNextWave = pTimeTillNextWave;

		for( int i=0; i<pNumSpawns*3; i+=3 )
		{
			spawns.push_back( Spawn( spawnArray[i], spawnArray[i+1], spawnArray[i+2] ) );
			numEnemies += spawnArray[i+1];
		}

	}

	// load from xml file
//	EnemyWave( const c8* xmlName );

	virtual ~EnemyWave(void)
	{
	}

	// spawn class
	class Spawn
	{
	public:
		Spawn( s32 pType, s32 pAmount, s32 pDuration ):
			type(pType),
			amount(pAmount),
			duration(pDuration)
		{}

		s32					type;			// type of enemy
		s32					amount;			// amount of enemy
		s32					duration;		// duration (seconds) till next spawn
	};

	// accessor methods
	s32 GetNumberofEnemies() { return numEnemies; }
	s32 GetNumberofSpawns() { return spawns.size(); }
	s32 GetTimeTillNextWave() { return timeTillNextWave; }
	Spawn& GetSpawn() { return ( curSpawn < numSpawns ) ? spawns[ curSpawn ] : spawns[ numSpawns-1 ]; }

	// advances to the next spawn
	// returns false if wave is finished
	bool AdvanceSpawn()
	{
		++curSpawn;
		
		if( curSpawn >= numSpawns )
		{
			return false;
		}
		else
			return true;
	}

	// resets the spawn counter to the first spawn
	void ResetSpawnCounter() { curSpawn = 0; }

protected:
	array<Spawn>			spawns;			// array of spawns
	u32						numSpawns;
	u32						curSpawn;
	u32						timeTillNextWave;
	u32						numEnemies;
};
