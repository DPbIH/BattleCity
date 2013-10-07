#include "stdafx.h"
#include "Game.h"
#include "MoveCommand.h"

MoveCommand::MoveCommand( Game* game )
	: GameCommand(game)
	, direction_( GlobalDeclarations::North )
{
}

void MoveCommand::Execute()
{
	game_->Player()->Vehicle()->Move( 1, direction_ );
}

void MoveCommand::SetDirection( GlobalDeclarations::Direction dir )
{
	direction_ = dir;
}