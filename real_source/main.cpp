/**
	This is the main launch file of the SnowballGame
*/
#include "Engine/GameEngine.h"

// global instance of the game engine
GameEngine* GEngine = NULL;

// main entry point of the program
int main()
{
	// create an instance of the game engine
	GEngine = new GameEngine();
	const bool result = GEngine->Init();

	if( result )
	{
		GEngine->Run();
	}

	GEngine->Exit();
	delete GEngine;
	GEngine = NULL;
	
	return 0;
}

