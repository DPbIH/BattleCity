#pragma once

#include "GameCommand.h"

class GoToMenuCommand
	: public GameCommand
{
public:
	GoToMenuCommand( Game* game );
	void Execute();
};