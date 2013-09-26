#pragma once

#include "GlobalDeclarations.h"
#include "GameCommandsFactory.h"

class GameplayCommandsFactory
	: public GameCommandsFactory
{
public:
	GameplayCommandsFactory( Game* game );
	GameCommand::Ptr OnKeySpace();
	GameCommand::Ptr OnKeyArrowDown();
	GameCommand::Ptr OnKeyArrowUp();
	GameCommand::Ptr OnKeyArrowLeft();
	GameCommand::Ptr OnKeyArrowRight();
	GameCommand::Ptr OnKeyEscape();

private:
	GameCommand::Ptr GetMoveCommand( GlobalDeclarations::Direction dir );

};