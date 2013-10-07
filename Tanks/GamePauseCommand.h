#pragma once

#include "GameCommand.h"

class GamePauseCommand
	: public GameCommand
{
public:
	GamePauseCommand( Game* game );
	void Execute();
};