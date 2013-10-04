#pragma once

#include "GameState.h"

class GameMenuState
	: public GameState
{
public:
	GameMenuState( Game* game );
	void Update();

private:
	//GameScreen::Ptr Screen();
	GameCommandsFactory::Ptr CommandsFactory();

};