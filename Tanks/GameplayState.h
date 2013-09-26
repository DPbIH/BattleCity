#pragma once

#include "GameState.h"

class GameplayState
	: public GameState
{
public:
	GameplayState( Game* game );
	void Start();
	void Stop();
	void Pause();
	void Resume();

private:
	GameScreen::Ptr Screen();
	GameCommandsFactory::Ptr CommandsFactory();

};