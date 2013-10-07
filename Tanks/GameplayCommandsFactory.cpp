#include "stdafx.h"
#include "Game.h"
#include "OpenFireCommand.h"
#include "MoveCommand.h"
#include "GamePauseCommand.h"
#include "GameplayCommandsFactory.h"

GameplayCommandsFactory::GameplayCommandsFactory( Game* game )
	: GameCommandsFactory(game)
{
}

GameCommand::Ptr GameplayCommandsFactory::OnKeySpace()
{
	return GameCommand::Ptr( new OpenFireCommand(game_) );
}

GameCommand::Ptr GameplayCommandsFactory::OnKeyArrowDown()
{
	return GetMoveCommand( GlobalDeclarations::South );
}

GameCommand::Ptr GameplayCommandsFactory::OnKeyArrowUp()
{
	return GetMoveCommand( GlobalDeclarations::North );
}

GameCommand::Ptr GameplayCommandsFactory::OnKeyArrowLeft()
{
	return GetMoveCommand( GlobalDeclarations::West );
}

GameCommand::Ptr GameplayCommandsFactory::OnKeyArrowRight()
{
	return GetMoveCommand( GlobalDeclarations::East );
}

GameCommand::Ptr GameplayCommandsFactory::GetMoveCommand( GlobalDeclarations::Direction dir )
{
	MoveCommand* cmd = new MoveCommand(game_);
	cmd->SetDirection(dir);
	return GameCommand::Ptr(cmd);
}

GameCommand::Ptr GameplayCommandsFactory::OnKeyEscape()
{
	return GameCommand::Ptr( new GamePauseCommand(game_) );
}