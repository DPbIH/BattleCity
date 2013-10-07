#include "stdafx.h"
#include "Game.h"
#include "OpenFireCommand.h"

OpenFireCommand::OpenFireCommand( Game* game )
	: GameCommand(game)
{
}

void OpenFireCommand::Execute()
{
	game_->Player()->Vehicle()->Fire();
}