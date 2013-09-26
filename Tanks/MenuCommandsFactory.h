#pragma once

#include "GameCommandsFactory.h"

class MenuCommandsFactory
	: public GameCommandsFactory
{
public:
	MenuCommandsFactory( Game* game );
};