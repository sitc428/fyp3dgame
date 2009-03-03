#include "Engine/GameEngine.h"

// Global Game Engine
GameEngine* GEngine = NULL;

int main(int argc, char* argv[])
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

