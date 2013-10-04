#pragma once

#include "GameState.h"

class GameplayState
	: public GameState
{
public:
	GameplayState( Game* game );
	void Update();

private:
	void OnEnterImpl();
	//GameScreen::Ptr Screen();
	GameCommandsFactory::Ptr CommandsFactory();

};