#include "stdafx.h"
#include "Game.h"
#include "GoToMenuCommand.h"

GoToMenuCommand::GoToMenuCommand( Game* game )
	: GameCommand(game)
{
}

void GoToMenuCommand::Execute()
{
	game_->ShowMenu();
}