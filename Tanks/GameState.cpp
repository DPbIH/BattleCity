#include "stdafx.h"
#include "Game.h"
#include "GameState.h"

GameState::GameState( Game* game )
	: game_(game)
{
}

void GameState::OnEnter()
{
	StartEventsHandler();
	OnEnterImpl();
}

void GameState::OnLeave()
{
	StopEventsHandler();
	OnLeaveImpl();
}

void GameState::StartEventsHandler()
{
	if( ! evtHandler_ )
	{
		evtHandler_.reset( new KeyboardEventsHandler( game_->evtListener_, CommandsFactory() ) );
	}

	evtHandler_->Start();
}

void GameState::StopEventsHandler()
{
	assert( evtHandler_ );
	evtHandler_->Stop();
}

void GameState::ChangeState( Ptr nextState )
{
	game_->ChangeState( nextState );
}