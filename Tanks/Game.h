#pragma once

#include "KeyboardEventsListener.h"
#include "GameState.h"
#include <map>

#include <boost/noncopyable.hpp>

enum StateName{ GameIntroduction, GameMenu, Gameplay };

class Game
	: boost::noncopyable
{
	friend class GameState;

public:
	Game();
	void PushState( StateName name, GameState::Ptr state );
	void SetCurrentState( StateName name );
	void Start();
	void Stop();
	void Pause();
	void Resume();
	void ShowMenu();

private:
	void InitStatesMap();
	GameState::Ptr GetState( StateName name );
	void ChangeState( GameState::Ptr nextState );

	GameState::Ptr currentState_;

	typedef std::map<StateName, GameState::Ptr> StatesMapT;
	StatesMapT gameStates_;
	KeyboardEventsListener::Ptr evtListener_;
};