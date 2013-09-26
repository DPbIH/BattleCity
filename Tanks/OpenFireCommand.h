#pragma once

#include "GameCommand.h"

class OpenFireCommand
	: public GameCommand
{
public:
	OpenFireCommand( Game* game );
	void Execute();

};