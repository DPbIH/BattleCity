#pragma once

#include "KeyboardEventsHandler.h"
#include "GameCommandsFactory.h"
#include <boost/shared_ptr.hpp>

class Game;

class GameState
{
public:
	typedef boost::shared_ptr<GameState> Ptr;

	GameState( Game* game );
	virtual ~GameState(){};
	virtual void Update() = 0;
	void OnEnter();
	void OnLeave();
	void ChangeState( GameState::Ptr nextState );

protected:
	//virtual GameScreen::Ptr Screen() = 0;
	virtual void OnEnterImpl(){}
	virtual void OnLeaveImpl(){}

	Game* game_;
	//GameScreen::Ptr screen_;
	KeyboardEventsHandler::Ptr evtHandler_;

private:
	virtual GameCommandsFactory::Ptr CommandsFactory() = 0;
	void StartEventsHandler();
	void StopEventsHandler();

	bool isActive_;

};