#pragma once

#include "GlobalDeclarations.h"
#include "GameCommand.h"

class MoveCommand
	: public GameCommand
{
public:
	MoveCommand( Game* game );
	void Execute();
	void SetDirection( GlobalDeclarations::Direction dir );

private:
	GlobalDeclarations::Direction direction_;
};