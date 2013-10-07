#pragma once

#include "KeyboardEventsListener.h"
#include "GameState.h"
#include "Level.h"
#include <map>
#include <boost/noncopyable.hpp>

enum StateName{ GameIntroduction, GameMenu, Gameplay };

class Game
	: boost::noncopyable
{
	friend class GameState;
	friend class GameplayState;
	friend class GameMenuState;

public:
	Game();
	void Init();
	void PushState( StateName name, GameState::Ptr state );
	void SetCurrentState( StateName name );
	void Run();
	void Pause();
	void Stop();
	Player::Ptr Player();

private:
	void Update();
	GameState::Ptr GetState( StateName name );
	void ChangeState( GameState::Ptr nextState );
	void LoadRandomLevel();
	void StartKeyboardListener();

	GameState::Ptr currentState_;

	typedef std::map<StateName, GameState::Ptr> StatesMapT;
	StatesMapT gameStates_;
	KeyboardEventsListener::Ptr evtListener_;
	Level::Ptr currentLevel_;

	bool running_;
	bool paused_;

};