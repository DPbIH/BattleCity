// Tanks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "GameplayState.h"
#include "GameMenuState.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Game game;
	game.Init();

	game.PushState( Gameplay, GameState::Ptr( new GameplayState(&game) ) );
	game.PushState( GameMenu, GameState::Ptr( new GameMenuState(&game) ) );
	game.SetCurrentState( Gameplay );

	game.Run();

	return 0;
}

