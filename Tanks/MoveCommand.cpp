#include "stdafx.h"
#include "MoveCommand.h"

MoveCommand::MoveCommand( Game* game )
	: GameCommand(game)
	, direction_( GlobalDeclarations::North )
{
}

void MoveCommand::Execute()
{
}

void MoveCommand::SetDirection( GlobalDeclarations::Direction dir )
{
	direction_ = dir;
}