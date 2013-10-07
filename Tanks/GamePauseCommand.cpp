#include "stdafx.h"
#include "Game.h"
#include "GamePauseCommand.h"

GamePauseCommand::GamePauseCommand( Game* game )
	: GameCommand(game)
{
}

void GamePauseCommand::Execute()
{
	game_->Pause();
}