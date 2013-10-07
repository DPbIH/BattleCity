#include "stdafx.h"
#include "GamePauseCommand.h"
#include "MenuCommandsFactory.h"

MenuCommandsFactory::MenuCommandsFactory( Game* game )
	: GameCommandsFactory(game)
{
}

GameCommand::Ptr MenuCommandsFactory::OnKeyEscape()
{
	return GameCommand::Ptr( new GamePauseCommand( game_ ) );
}