#pragma once

#include "GameCommand.h"

class DummyCommand:
	public GameCommand
{
public:
	DummyCommand( Game* game )
		: GameCommand(game)
	{ }

	void Execute()
	{ }
};