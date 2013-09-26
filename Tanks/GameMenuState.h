#pragma once

#include "GameState.h"

class GameMenuState
	: public GameState
{
public:
	GameMenuState( Game* game );
	void Start();
	void Stop();
	void Pause();
	void Resume();

private:
	GameScreen::Ptr Screen();
	GameCommandsFactory::Ptr CommandsFactory();

};