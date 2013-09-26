#include "stdafx.h"
#include "Game.h"
#include "GameCommand.h"

GameCommand::GameCommand( Game* game )
	: game_(game)
{
	assert(game_);
}

GameCommand::~GameCommand()
{
}
